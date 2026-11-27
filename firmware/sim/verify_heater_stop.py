"""Verify the enabled heater control in Unicorn without a physical device."""

import argparse
import struct
import subprocess
from pathlib import Path

from unicorn import UC_ARCH_ARM, UC_MODE_MCLASS, UC_MODE_THUMB, Uc
from unicorn.arm_const import (
    UC_ARM_REG_LR,
    UC_ARM_REG_R0,
    UC_ARM_REG_R1,
    UC_ARM_REG_R2,
    UC_ARM_REG_R3,
    UC_ARM_REG_SP,
)

BASE = 0x08005000
STACK = 0x20005000
CONTROLLER = 0x20004200
UI = 0x20004300
RETURN = 0x08008000
TIMER_MODE = 0x40000018
FORCED_LOW = 0x40
PWM = 0x60

# Cortex-M build layout for t90b_state_t.
UI_FAULTS = 20
UI_TIP_TEMPERATURE = 24


def verify(candidate: Path, pulse_ticks: int = 0, toggle: bool = False, presets: bool = False):
    symbols = {}
    listing = subprocess.check_output(
        ["arm-none-eabi-nm", str(candidate.with_suffix(".elf"))], text=True
    )
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) == 3:
            symbols[fields[2]] = int(fields[0], 16)

    machine = Uc(UC_ARCH_ARM, UC_MODE_MCLASS | UC_MODE_THUMB)
    for address, size in ((BASE, 0x4000), (0x20000000, 0x6000), (0x40000000, 0x1000)):
        machine.mem_map(address, size)
    machine.mem_write(BASE, candidate.read_bytes())

    def call(name, *args, button_b=0):
        machine.reg_write(UC_ARM_REG_SP, STACK)
        machine.reg_write(UC_ARM_REG_LR, RETURN | 1)
        machine.mem_write(STACK, struct.pack("<I", button_b))
        for reg, value in zip((UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3), args):
            machine.reg_write(reg, value)
        machine.emu_start(symbols[name] | 1, RETURN, count=1000)

    def mode():
        return struct.unpack("<I", machine.mem_read(TIMER_MODE, 4))[0]

    def start():
        machine.mem_write(symbols["g_tick_ms"], struct.pack("<I", 1300))
        machine.mem_write(UI, bytes(128))
        call("ui_init", UI, 0xAA, 0)
        machine.mem_write(UI + UI_TIP_TEMPERATURE, struct.pack("<h", 250))
        call("heater_init", CONTROLLER)
        call("heater_ui_step", CONTROLLER, UI, 1300, 0)
        call("heater_ui_step", CONTROLLER, UI, 1300, 1)
        call("SysTick_Handler")
        assert mode() == PWM, "Expected PWM after valid manual start"

    start()
    machine.mem_write(UI + UI_FAULTS, struct.pack("<I", 1))
    call("heater_ui_step", CONTROLLER, UI, 1301, 0)
    assert mode() == FORCED_LOW, "Missing tip did not force the output low"
    machine.mem_write(UI + UI_FAULTS, bytes(4))
    call("heater_ui_step", CONTROLLER, UI, 1302, 0)
    call("SysTick_Handler")
    assert mode() == FORCED_LOW, "Output resumed without manual rearm"
    print("Missing tip and recovery: PASS")

    start()
    call("heater_ui_step", CONTROLLER, UI, 1301, 1 if toggle else 2)
    assert mode() == FORCED_LOW, "Manual stop did not force the output low"
    print("Manual stop: PASS")

    start()
    for _ in range(499):
        call("SysTick_Handler")
    call("SysTick_Handler")
    assert mode() == FORCED_LOW, "SysTick timeout did not force the output low"
    call("board_set_heater_pwm", 20)
    call("SysTick_Handler")
    assert mode() == FORCED_LOW, "Late command bypassed timeout latch"
    print("Timeout and late command: PASS")

    if toggle:
        def sample(temp_dc, now, button=0, faults=0, button_b=0):
            machine.mem_write(UI + UI_TIP_TEMPERATURE, struct.pack("<h", temp_dc))
            machine.mem_write(UI + UI_FAULTS, struct.pack("<I", faults))
            machine.mem_write(symbols["g_tick_ms"], struct.pack("<I", now))
            call("heater_ui_step", CONTROLLER, UI, now, button, button_b=button_b)
            call("SysTick_Handler")
            return machine.mem_read(symbols["pwm_request_pct"], 1)[0]

        for rate in (5, 1, 2):
            start()
            last_full = 250
            snapshot = {}
            for elapsed in range(50, 75000 // rate + 1, 50):
                temp = 250 + elapsed * rate // 100
                now = 1300 + elapsed
                duty = sample(temp, now)
                if duty == 100:
                    last_full = temp
                if temp in (900, 950, 990, 1000):
                    snapshot[temp] = duty
            if rate == 5:
                assert last_full < 850 and snapshot[900] == 0, "Fast rise needs earlier braking"
            elif rate == 2:
                assert last_full >= 940 and 65 <= snapshot[950] <= 85
            else:
                assert last_full >= 950
            assert snapshot[990] == 0, "Moving tip should coast before target"
            print(f"{rate} C/s: last full request at {last_full / 10:.1f} C, "
                  f"request at 95 C = {snapshot[950]}%: PASS")
            assert duty == 0 and mode() == FORCED_LOW
        # A slow profile reaches 99.9 C, then cycles across the target unaided.
        # A constant positive command afterwards must survive both board and UI timers.
        for now in range(38900, 450000, 100):
            temp = 999 if now < 43000 else 995
            duty = sample(temp, now)
            if now > 46000:
                assert duty > 0, "Uncommanded shutdown while maintaining target"
            assert machine.mem_read(UI, 1)[0] == 2, "Unexpected exit from heating screen"
        for temp in (1000, 1002, 999, 995, 1000):
            now += 100
            duty = sample(temp, now)
            if temp >= 1000:
                assert duty == 0 and mode() == FORCED_LOW
            elif temp == 995:
                for _ in range(10):
                    now += 100
                    duty = sample(temp, now)
                assert duty > 0, "No recovery below target"
        assert sample(990, now + 100, 1) == 0 and mode() == FORCED_LOW
        assert sample(900, now + 200) == 0
        assert sample(900, now + 300, 1) > 0
        print("Continuous hold beyond 7 min, cutoff/recovery and manual stop: PASS")

        # Synthetic lag and heat loss exercise the feedback loop with 0.1 C readings.
        for lag_s in (0.5, 1.5, 3.0):
            start()
            temp_c, heat_rate = 25.0, 0.0
            first_target_ms = None
            for elapsed in range(50, 120001, 50):
                measured_dc = round(temp_c * 10)
                duty = sample(measured_dc, 1300 + elapsed)
                if measured_dc >= 1000:
                    assert duty == 0
                    if first_target_ms is None:
                        first_target_ms = elapsed
                heat_rate += (4.5 * duty / 100 - heat_rate) * 0.05 / lag_s
                temp_c += (heat_rate - 0.005 * (temp_c - 25.0)) * 0.05
                assert temp_c < 100.05, "Overshoot in synthetic plant"
            assert first_target_ms is not None and first_target_ms < 40000
            print(f"Synthetic lag {lag_s} s: first indicated 100 C at {first_target_ms / 1000} s")

        start()
        for now in range(1350, 13501, 50):
            duty = sample(250, now)
        assert duty == 0 and mode() == FORCED_LOW
        assert machine.mem_read(UI + UI_FAULTS, 1)[0] & 0x10
        assert sample(260, 13550, 1) == 0
        assert sample(260, 13600, 1) == 100
        assert sample(1050, 13650) == 0 and mode() == FORCED_LOW
        assert sample(1050, 13700, 1) == 0
        assert sample(980, 13750) == 0
        assert sample(980, 13800, 1) == 0
        assert sample(980, 13850, 1) > 0
        for fault in (1, 2, 4, 8):
            start()
            assert sample(350, 1350, faults=fault) == 0 and mode() == FORCED_LOW
            assert sample(350, 1400) == 0
        print("Thermal response, overtemperature, ADC, tip and voltage trips: PASS")

        if presets:
            start()
            now = 1350
            assert sample(250, now, 1) == 0  # Standby, default preset 100.
            for target in (200, 300, 350, 400, 100):
                now += 50
                assert sample(250, now, button_b=1) == 0 and mode() == FORCED_LOW
                now += 50
                assert sample(250, now, 1) == 100
                # Close the loop on the selected target, from cold through maintenance.
                temp_c, heat_rate = 25.0, 0.0
                reached = False
                for step in range(4800):
                    now += 50
                    measured = round(temp_c * 10)
                    duty = sample(measured, now, button_b=int(step == 120))
                    if measured >= target * 10:
                        reached = True
                        assert duty == 0
                    heat_rate += (4.5 * duty / 100 - heat_rate) * 0.05 / 1.5
                    temp_c += (heat_rate - 0.005 * (temp_c - 25.0)) * 0.05
                    assert temp_c < target + 1
                assert reached and abs(temp_c - target) < 1
                now += 50
                assert sample(measured, now, 1) == 0 and mode() == FORCED_LOW
                now += 50
                assert sample(250, now, 1) > 0
                now += 50
                assert sample((target + 5) * 10, now) == 0
                assert machine.mem_read(UI + UI_FAULTS, 1)[0] & 0x10
                now += 50
                assert sample(250, now, 1) == 0
            # Starting at 400 C residual heat on preset 100 allows only cooling.
            now += 50
            assert sample(4000, now, 1) == 0
            for temp in (3990, 3500, 3100, 1900, 1500, 1010, 1000, 980):
                now += 50
                duty = sample(temp, now)
                assert duty > 0 if temp < 1000 else duty == 0
                assert machine.mem_read(UI + UI_FAULTS, 1)[0] == 0
            print("Preset selection, direct PID, manual stop, trips and hot restart: PASS")

    if pulse_ticks:
        start()
        # Keep refreshing the command. The independent pulse limit must still stop it.
        for elapsed in range(2, pulse_ticks):
            if elapsed % 50 == 0:
                call("board_set_heater_pwm", 10)
            call("SysTick_Handler")
        call("SysTick_Handler")
        assert mode() == FORCED_LOW, "Pulse duration limit did not force the output low"
        call("board_set_heater_pwm", 10)
        for _ in range(100):
            call("SysTick_Handler")
            assert mode() == FORCED_LOW, "Pulse restarted without a zero command"
        print(f"Independent {pulse_ticks}-tick pulse limit: PASS")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--pulse", action="store_true", help="Check the hardware probe duration")
    parser.add_argument("--toggle", action="store_true", help="Check continuous 100 C regulation")
    parser.add_argument("--presets", action="store_true", help="Check all selectable targets")
    args = parser.parse_args()
    verify(args.candidate, 1000 if args.pulse else 0, args.toggle or args.presets, args.presets)
