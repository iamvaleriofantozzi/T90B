"""Trace reference behavior scenarios of the original T90B firmware in Unicorn."""

import csv
import hashlib
import struct
import sys
from pathlib import Path

from unicorn import (
    Uc, UC_ARCH_ARM, UC_HOOK_CODE, UC_MODE_MCLASS, UC_MODE_THUMB, UC_PROT_READ
)
from unicorn.arm_const import UC_ARM_REG_PC, UC_ARM_REG_SP

from trace_reset import map_clock_probe
from trace_settings import PAGE, boot_preferences, sealed, BLOCKS
from trace_ui_dispatch import BASE, EXPECTED_SHA256, SRAM

UI_SLOT_ADDR = 0x20000038
MILLIS_ADDR = 0x200000F8
BTN_A_EVENT = 0x2000105C + 1
BTN_B_EVENT = 0x2000106A + 1
TIM1_CCDAT1 = 0x40012C34
SYS_STATE_ERR = 0x200002C4 + 0x1C


def make_boot_prefs(app, factory_ok=True, po_heat=0):
    page = bytearray(boot_preferences(app))
    if factory_ok:
        off0, sz0, _ = BLOCKS[0]
        page[off0 + 5] = 0xAA
        page[off0:off0 + sz0] = sealed(page[off0:off0 + sz0])
    off1, sz1, _ = BLOCKS[1]
    page[off1 + 0x50] = po_heat
    page[off1:off1 + sz1] = sealed(page[off1:off1 + sz1])
    return bytes(page)


def run_scenario(app, scenario_name, max_steps=30_000_000, adc_val=1000, factory_ok=True, po_heat=0, actions=None):
    sp, reset = struct.unpack_from("<II", app)
    uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    uc.mem_map(BASE, 0x18000)
    uc.mem_write(BASE, app)
    settings = make_boot_prefs(app, factory_ok=factory_ok, po_heat=po_heat)
    uc.mem_map(PAGE, len(settings))
    uc.mem_write(PAGE, settings)
    uc.mem_protect(PAGE, len(settings), UC_PROT_READ)
    uc.mem_map(SRAM, 0x6000)
    uc.reg_write(UC_ARM_REG_SP, sp)
    uc.mem_map(0xE000E000, 0x1000)

    access = []
    serial = bytearray()
    dma_writes, adc_writes, spi_writes, timer_writes, watchdog_writes = [], [], [], [], []
    regs = map_clock_probe(
        uc, True, access, "spi", serial,
        dma_writes, adc_writes, spi_writes, timer_writes,
        True, watchdog_writes, True, adc_val
    )

    actions = dict(actions or {})
    trace = []
    last_slot = None
    last_err = None
    tick_ms = 0
    step = 0
    loop_iters = 0

    def hook_code(emu, address, size, _data):
        nonlocal tick_ms, step, loop_iters, last_slot, last_err
        step += 1

        # Virtual microsecond / millisecond tick
        if address == 0x08011EDC:
            cur = struct.unpack("<I", emu.mem_read(MILLIS_ADDR, 4))[0]
            emu.mem_write(MILLIS_ADDR, struct.pack("<I", (cur + 1) & 0xFFFFFFFF))

        # Auto-complete display DMA transfer whenever firmware waits at 0x0801140E
        if address == 0x0801140E:
            emu.mem_write(0x2000011E, b"\x01\x01")

        # Main superloop top (0x080116BE)
        if address == 0x080116BE:
            loop_iters += 1
            tick_ms += 50
            emu.mem_write(MILLIS_ADDR, struct.pack("<I", tick_ms))
            slot = struct.unpack("<I", emu.mem_read(UI_SLOT_ADDR, 4))[0]
            err = struct.unpack("<I", emu.mem_read(SYS_STATE_ERR, 4))[0]
            if slot != last_slot or err != last_err:
                trace.append((tick_ms, "ui_slot", slot, f"err=0x{err:x}"))
                last_slot = slot
                last_err = err
            if loop_iters >= 60:
                emu.emu_stop()

        # Inject button/fault right before ui_dispatch (0x08011744)
        if address == 0x08011744 and loop_iters in actions:
            act = actions[loop_iters]
            if "btnA" in act:
                emu.mem_write(BTN_A_EVENT, bytes([act["btnA"]]))
            if "btnB" in act:
                emu.mem_write(BTN_B_EVENT, bytes([act["btnB"]]))
            if "err" in act:
                emu.mem_write(SYS_STATE_ERR, struct.pack("<I", act["err"]))
            trace.append((tick_ms, "action", str(act), ""))

    uc.hook_add(UC_HOOK_CODE, hook_code)
    try:
        uc.emu_start(reset, BASE + len(app), count=max_steps)
    except Exception as e:
        trace.append((tick_ms, "exception", str(e), ""))

    # Record final TIM1 CCR1 (heater PWM) from timer_writes
    ccdat1 = [v for _, a, v in timer_writes if a == TIM1_CCDAT1]
    last_pwm = ccdat1[-1] if ccdat1 else 0
    return trace, last_pwm, len(serial), len(access)


def main():
    app = Path("analysis/t90-app.bin").read_bytes()
    assert hashlib.sha256(app).hexdigest() == EXPECTED_SHA256

    scenarios = [
        ("boot_factory_untested", dict(factory_ok=False, po_heat=0)),
        ("boot_normal_standby", dict(factory_ok=True, po_heat=0)),
        ("boot_normal_po_heat", dict(factory_ok=True, po_heat=1)),
        ("menu_enter_exit", dict(factory_ok=True, po_heat=0, actions={
            5: {"btnA": 1, "btnB": 1},
            8: {"btnB": 1},
            12: {"btnA": 2},
        })),
        ("tip_missing_fault", dict(factory_ok=True, po_heat=0, actions={
            5: {"err": 0x01},
        })),
        ("sensor_fault", dict(factory_ok=True, po_heat=0, actions={
            5: {"err": 0x02},
        })),
    ]

    for name, kw in scenarios:
        trace, last_pwm, ser_len, acc_len = run_scenario(app, name, **kw)
        print(f"=== {name} (pwm={last_pwm}, serial={ser_len}, unmodeled={acc_len}) ===")
        for t, kind, val, extra in trace:
            print(f"  t={t:4d}ms  {kind:10s}  {val}  {extra}")


if __name__ == "__main__":
    main()
