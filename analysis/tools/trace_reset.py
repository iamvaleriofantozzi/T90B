"""Run the original reset vector up to the first unmodeled memory access."""

import argparse
import csv
import hashlib
import struct
import sys
from pathlib import Path

from unicorn import (Uc, UcError, UC_ARCH_ARM, UC_HOOK_CODE, UC_HOOK_MEM_INVALID,
                     UC_MEM_FETCH_UNMAPPED, UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED,
                     UC_MEM_WRITE_PROT, UC_MODE_MCLASS, UC_MODE_THUMB, UC_PROT_READ)
from unicorn.arm_const import UC_ARM_REG_LR, UC_ARM_REG_PC, UC_ARM_REG_SP

from trace_settings import PAGE, boot_preferences
from trace_ui_dispatch import BASE, EXPECTED_SHA256, SRAM


def map_clock_probe(machine, hse_ready, events, peripherals, serial, dma_writes, adc_writes, spi_writes, timer_writes, timers, watchdog_writes, watchdog, adc_sample):
    # This probe models selected status transitions, not their elapsed time.
    rcc_control = 0x40021000
    rcc_config = rcc_control + 4
    power_control = 0x40007000
    power_status = power_control + 0x10
    values = {
        rcc_control: 0x40, rcc_config: 0, 0x40021008: 0,
        0x4002101C: 0, 0x40021024: 0x0C00246C,
        0x4002102C: 0, 0x40021030: 0, 0x40021034: 0, 0x40021040: 0,
        power_control: 0, power_status: 3,
        0x40001820: 0, 0x40022000: 0,
    }

    if peripherals:
        values.update({0x40021014: 0x14, 0x40021018: 0})

    gpio_ports = (0x40010800, 0x40010C00, 0x40011000, 0x40011400)
    if peripherals in ("gpio", "usart", "dma", "adc", "spi"):
        gpio_reset = {
            0x00: 0xFFFFFFFF, 0x04: 0, 0x08: 0xFFFF, 0x0C: 0, 0x10: 0, 0x14: 0,
            0x18: 0, 0x20: 0xFFFFFFFF, 0x24: 0xFFFFFFFF, 0x28: 0,
            0x2C: 0x55555555,
        }
        for port in gpio_ports:
            values.update({port + offset: value for offset, value in gpio_reset.items()})
        values.update({
            0x40010800: 0xABFFFFFF, 0x40010C00: 0xFFFFFEBF, 0x40011400: 0xFFFFFFFC,
            0x40010C20: 0xFFF00FFF, 0x40010824: 0x000FFFFF,
        })

    dma = 0x40020000
    if peripherals in ("dma", "adc", "spi"):
        values.update({dma + offset: 0 for offset in range(0, 0xA8, 4)})
        values[0x40021028] = 0

    adc = 0x40020800
    if peripherals in ("adc", "spi"):
        # Result registers are excluded so the probe stops before consuming a sample.
        values.update({adc + offset: 0 for offset in range(0, 0x3C, 4)})
        values.update({adc + 0x50: 0, adc + 0x54: 0, adc + 0x58: 0x43, adc + 0x5C: 0})

    if adc_sample is not None:
        values[adc + 0x3C] = adc_sample

    usart = 0x40013800
    serial_registers = {usart + offset: 0 for offset in range(0, 0x1C, 4)}
    serial_registers[usart] = 0xC0

    spi = 0x40013000
    spi_registers = {spi + offset: 0 for offset in range(0, 0x20, 4)}
    spi_registers[spi + 8] = 2

    timer_registers = {}
    if timers:
        advanced_offsets = (*range(0, 0x50, 4), 0x54, 0x58, 0x5C)
        general_offsets = (*range(0, 0x54, 4), 0x58)
        basic_offsets = (0, 4, 0x0C, 0x10, 0x14, 0x24, 0x28, 0x2C)
        for base, offsets in (
            (0x40012C00, advanced_offsets), (0x40013400, advanced_offsets),
            (0x40000000, general_offsets), (0x40000400, general_offsets),
            (0x40000800, general_offsets), (0x40000C00, general_offsets),
            (0x40003C00, general_offsets), (0x40001000, basic_offsets),
            (0x40001400, basic_offsets),
        ):
            timer_registers.update({base + offset: 0 for offset in offsets})
            timer_registers[base + 0x2C] = 0xFFFF

    lsi_alias = 0x42420480
    watchdog_base = 0x40003000
    if watchdog:
        values[lsi_alias] = values[0x40021024] & 1
        values.update({watchdog_base: 0, watchdog_base + 4: 0,
                       watchdog_base + 8: 0xFFF, watchdog_base + 0xC: 0})
    watchdog_unlocked = False

    def read(emu, offset, size, base):
        address = base + offset
        pc = emu.reg_read(UC_ARM_REG_PC)
        if peripherals in ("usart", "dma", "adc", "spi") and address in serial_registers and size in (2, 4):
            return serial_registers[address]
        if peripherals == "spi" and address in spi_registers and size in (2, 4):
            return spi_registers[address]
        if address in timer_registers and size in (2, 4):
            return timer_registers[address]
        if size != 4 or address not in values:
            events.append((pc, "read", address, size))
            emu.emu_stop()
            return 0
        value = values[address]
        if address == power_status:
            values[address] |= 2
        return value

    def write(emu, offset, size, value, base):
        nonlocal watchdog_unlocked
        address = base + offset
        pc = emu.reg_read(UC_ARM_REG_PC)
        if peripherals in ("usart", "dma", "adc", "spi") and address in serial_registers and size in (2, 4):
            serial_registers[address] = value
            if address == usart + 4:
                serial.append(value & 0xFF)
                serial_registers[usart] |= 0xC0
            return
        if peripherals == "spi" and address in spi_registers and size in (2, 4):
            spi_writes.append((pc, address, value))
            if address != spi + 8:
                spi_registers[address] = value
            return
        if address in timer_registers and size in (2, 4):
            timer_writes.append((pc, address, value))
            register_offset = address & 0x3FF
            if register_offset == 0x10:
                timer_registers[address] &= value
            elif register_offset != 0x14:
                timer_registers[address] = value
            return
        if size != 4 or address not in values:
            events.append((pc, "write", address, size))
            emu.emu_stop()
            return
        if watchdog and address == lsi_alias:
            watchdog_writes.append((pc, address, value))
            values[address] = value & 1
            values[0x40021024] = (values[0x40021024] & ~3) | (3 if value & 1 else 0)
            return
        if watchdog and watchdog_base <= address <= watchdog_base + 0xC:
            watchdog_writes.append((pc, address, value))
            if address == watchdog_base:
                watchdog_unlocked = value == 0x5555
            elif watchdog_unlocked and address in (watchdog_base + 4, watchdog_base + 8):
                values[address] = value & (7 if address == watchdog_base + 4 else 0xFFF)
            return
        if peripherals in ("dma", "adc", "spi") and dma <= address < dma + 0xA8:
            dma_writes.append((pc, address, value))
            if address == dma + 4:
                values[dma] &= ~value
                return
            if address == dma:
                return
        if peripherals in ("adc", "spi") and adc <= address < adc + 0x60:
            adc_writes.append((pc, address, value))
            if adc_sample is not None and address == adc:
                values[address] &= value
                return
            if address == adc + 8:
                if adc_sample is not None and pc == 0x08005EC2 and value & 0x200000:
                    values[adc] |= 4
                if value & 1:
                    values[adc + 0x58] |= 0x20
                else:
                    values[adc + 0x58] &= ~0x20
                value &= ~4
        if address == rcc_control:
            value &= ~(2 | (1 << 17) | (1 << 25))
            if value & 1:
                value |= 2
            if hse_ready and value & (1 << 16):
                value |= 1 << 17
                if value & (1 << 24):
                    value |= 1 << 25
        elif address == rcc_config:
            source = value & 3
            value = (value & ~12) | (source << 2)
        elif address == power_control and (value ^ values[address]) & 0x600:
            values[power_status] &= ~2
        elif peripherals in ("gpio", "usart", "dma", "adc", "spi"):
            port = address & ~0x3FF
            if port in gpio_ports:
                offset = address - port
                if offset == 0x18:
                    set_bits = value & 0xFFFF
                    clear_bits = value >> 16
                    values[port + 0x14] = (values[port + 0x14] & ~clear_bits) | set_bits
                    return
                if offset == 0x28:
                    values[port + 0x14] &= ~(value & 0xFFFF)
                    return
        values[address] = value

    pages = (0x40001000, 0x40007000, 0x40021000, 0x40022000)
    if peripherals in ("gpio", "usart", "dma", "adc", "spi"):
        pages += (0x40010000, 0x40011000)
    if peripherals in ("usart", "dma", "adc", "spi"):
        pages += (0x40013000,)
    if peripherals in ("dma", "adc", "spi"):
        pages += (dma,)
    if timers:
        pages += (0x40000000, 0x40003000, 0x40012000)
    if watchdog:
        pages += (lsi_alias & ~0xFFF,)
    for base in pages:
        machine.mmio_map(base, 0x1000, read, base, write, base)
    return values


def trace_reset(app, core_page, clock_mode=None, peripherals=None, virtual_tick=False, capture_frame=False, complete_display=False, timers=False, watchdog=False, preferences=False, adc_sample=None, frame_index=1):
    sp, reset = struct.unpack_from("<II", app)
    machine = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    machine.mem_map(BASE, 0x18000)
    machine.mem_write(BASE, app)
    if preferences:
        settings = boot_preferences(app)
        machine.mem_map(PAGE, len(settings))
        machine.mem_write(PAGE, settings)
        machine.mem_protect(PAGE, len(settings), UC_PROT_READ)
    machine.mem_map(SRAM, 0x6000)
    machine.reg_write(UC_ARM_REG_SP, sp)
    if core_page or clock_mode:
        machine.mem_map(0xE000E000, 0x1000)
    instructions = []
    access = []
    serial = bytearray()
    dma_writes = []
    adc_writes = []
    spi_writes = []
    timer_writes = []
    watchdog_writes = []
    frame = None
    frame_count = 0
    if clock_mode:
        registers = map_clock_probe(machine, clock_mode == "hse-ready", access, peripherals, serial, dma_writes, adc_writes, spi_writes, timer_writes, timers, watchdog_writes, watchdog, adc_sample)

    display_wait = 0x0801140E
    dma_irq_seen = False
    waiting_for_irq = False

    def record_instruction(emu, address, size, _data):
        nonlocal frame, frame_count, waiting_for_irq
        if complete_display and address == display_wait and not dma_irq_seen:
            waiting_for_irq = True
            emu.emu_stop()
            return
        instructions.append((address, size))
        if capture_frame and address == 0x080113E4:
            frame_count += 1
        if capture_frame and address == 0x080113E4 and frame_count == frame_index:
            registers = {register: value for _, register, value in dma_writes}
            count = registers[0x40020020]
            source = registers[0x40020028]
            destination = registers[0x40020024]
            config = registers[0x4002001C]
            if destination != 0x4001300C or count != 40 * 160 or config & 0xF11 != 0x511:
                raise ValueError("Unexpected display DMA configuration")
            frame = bytes(emu.mem_read(source, count * 2))
        if virtual_tick and address == 0x08011EDC:
            control, = struct.unpack("<I", emu.mem_read(0xE000E010, 4))
            if control & 1:
                elapsed, = struct.unpack("<I", emu.mem_read(0x200000F8, 4))
                emu.mem_write(0x200000F8, struct.pack("<I", (elapsed + 1) & 0xFFFFFFFF))

    def record_unmapped(emu, kind, address, size, _value, _data):
        operation = {
            UC_MEM_READ_UNMAPPED: "read",
            UC_MEM_WRITE_UNMAPPED: "write",
            UC_MEM_WRITE_PROT: "protected_write",
            UC_MEM_FETCH_UNMAPPED: "fetch",
        }[kind]
        access.append((emu.reg_read(UC_ARM_REG_PC), operation, address, size))
        return False

    machine.hook_add(UC_HOOK_CODE, record_instruction)
    machine.hook_add(UC_HOOK_MEM_INVALID, record_unmapped)
    try:
        limit = 128
        if clock_mode:
            limit = 250000
        if peripherals == "spi":
            limit = 3000000 if complete_display else 1500000
        machine.emu_start(reset, BASE + len(app), count=limit)
        if waiting_for_irq:
            context = machine.context_save()
            interrupt_vector, = struct.unpack_from("<I", app, (16 + 12) * 4)
            if interrupt_vector != 0x08009329 or registers[0x4002001C] & 3 != 3:
                raise RuntimeError("Invalid DMA2 handler or channel state")
            registers[0x40020000] |= 0x30
            dma_irq_seen = True
            machine.reg_write(UC_ARM_REG_LR, display_wait | 1)
            machine.emu_start(interrupt_vector, display_wait, count=256)
            if registers[0x40020000] & 0x20 or bytes(machine.mem_read(0x2000011E, 2)) != b"\x01\x01":
                raise RuntimeError("DMA2 handler did not acknowledge transfer completion")
            machine.context_restore(context)
            machine.emu_start(display_wait | 1, BASE + len(app), count=limit - len(instructions))
    except UcError:
        if not access:
            raise
    if complete_display and not dma_irq_seen:
        raise RuntimeError("The first display completion checkpoint was not reached")
    if not access and peripherals == "spi" and len(instructions) == limit:
        access.append((instructions[-1][0], "instruction_limit", None, 0))
    if len(access) != 1 or access[0][0] != instructions[-1][0]:
        raise RuntimeError(f"Unexpected stop: {access}, last instructions {instructions[-5:]}")
    return instructions, access[0], serial, dma_writes, adc_writes, spi_writes, timer_writes, watchdog_writes, frame


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("payload", type=Path)
    parser.add_argument("--core-page", action="store_true",
                        help="map the system-control page as zero-initialized RAM")
    parser.add_argument("--clock-mode", choices=("hse-ready", "hse-timeout"),
                        help="probe both branches of the clock startup model")
    parser.add_argument("--peripheral-clocks", action="store_true",
                        help="include the AHB and APB2 clock gate registers")
    parser.add_argument("--gpio", action="store_true",
                        help="also map GPIO configuration and output latches")
    parser.add_argument("--usart", action="store_true",
                        help="include USART1 with no RX and instantaneous TX")
    parser.add_argument("--serial-output", type=Path,
                        help="save the repeatable USART1 transmit bytes")
    parser.add_argument("--dma", action="store_true",
                        help="include DMA configuration registers without transfers")
    parser.add_argument("--dma-output", type=Path, help="save repeatable DMA writes")
    parser.add_argument("--adc", action="store_true", help="include ADC configuration and calibration flags")
    parser.add_argument("--adc-output", type=Path, help="save repeatable ADC writes")
    parser.add_argument("--spi", action="store_true", help="include SPI1 with instantaneous TX")
    parser.add_argument("--spi-output", type=Path, help="save repeatable SPI1 writes")
    parser.add_argument("--virtual-tick", action="store_true",
                        help="advance the firmware millisecond counter at each timing query")
    parser.add_argument("--frame-output", type=Path, help="save selected full display DMA source buffer")
    parser.add_argument("--complete-display", action="store_true",
                        help="inject first DMA channel 2 completion and run the original handler")
    parser.add_argument("--timers", action="store_true", help="include timer configuration registers")
    parser.add_argument("--timer-output", type=Path, help="save repeatable timer writes")
    parser.add_argument("--watchdog", action="store_true",
                        help="include LSI and watchdog configuration without counting down")
    parser.add_argument("--watchdog-output", type=Path, help="save repeatable LSI and watchdog writes")
    parser.add_argument("--preferences", action="store_true",
                        help="add read-only synthetic valid preference and journal records")
    parser.add_argument("--adc-sample", type=lambda value: int(value, 0),
                        help="provide a fixed synthetic injected conversion code")
    parser.add_argument("--frame-index", type=int, default=1, help="select the full-frame transfer to capture")
    args = parser.parse_args()
    if args.frame_index < 1 or (args.frame_index > 1 and not args.frame_output):
        parser.error("--frame-index must be positive and requires --frame-output for non-default values")
    if args.adc_sample is not None and (not args.preferences or not 0 <= args.adc_sample <= 0xFFF):
        parser.error("--adc-sample requires --preferences and a 12-bit code")
    if args.preferences and not args.watchdog:
        parser.error("--preferences requires --watchdog")
    if args.watchdog and not args.timers:
        parser.error("--watchdog requires --timers")
    if args.watchdog_output and not args.watchdog:
        parser.error("--watchdog-output requires --watchdog")
    if args.timers and not args.complete_display:
        parser.error("--timers requires --complete-display")
    if args.timer_output and not args.timers:
        parser.error("--timer-output requires --timers")
    if args.complete_display and not args.virtual_tick:
        parser.error("--complete-display requires --virtual-tick")
    if args.frame_output and not args.virtual_tick:
        parser.error("--frame-output requires --virtual-tick")
    if args.virtual_tick and not args.spi:
        parser.error("--virtual-tick requires --spi")
    if (args.peripheral_clocks or args.gpio or args.usart or args.dma or args.adc or args.spi) and not args.clock_mode:
        parser.error("peripheral models require --clock-mode")
    peripherals = None
    for enabled, tier in ((args.peripheral_clocks, "clocks"), (args.gpio, "gpio"),
                          (args.usart, "usart"), (args.dma, "dma"), (args.adc, "adc"), (args.spi, "spi")):
        if enabled:
            peripherals = tier
    if args.serial_output and peripherals not in ("usart", "dma", "adc", "spi"):
        parser.error("--serial-output requires --usart, --dma or --adc")
    if args.adc_output and not (args.adc or args.spi):
        parser.error("--adc-output requires --adc")
    if args.dma_output and not (args.dma or args.adc or args.spi):
        parser.error("--dma-output requires --dma or --adc")
    if args.spi_output and not args.spi:
        parser.error("--spi-output requires --spi")
    app = args.payload.read_bytes()
    if hashlib.sha256(app).hexdigest() != EXPECTED_SHA256:
        raise ValueError("Payload differs from the audited baseline")
    writer = csv.writer(sys.stdout, delimiter="\t", lineterminator="\n")
    writer.writerow(("repetition", "step", "pc", "event", "address", "size_bytes"))
    serial_runs = []
    dma_runs = []
    adc_runs = []
    spi_runs = []
    frames = []
    timer_runs = []
    watchdog_runs = []
    for repetition in range(1, 4):
        instructions, (pc, operation, address, size), serial, dma_writes, adc_writes, spi_writes, timer_writes, watchdog_writes, frame = trace_reset(
            app, args.core_page, args.clock_mode, peripherals, args.virtual_tick, bool(args.frame_output), args.complete_display, args.timers, args.watchdog, args.preferences, args.adc_sample, args.frame_index
        )
        frames.append(frame)
        serial_runs.append(serial)
        dma_runs.append(dma_writes)
        adc_runs.append(adc_writes)
        spi_runs.append(spi_writes)
        timer_runs.append(timer_writes)
        watchdog_runs.append(watchdog_writes)
        checkpoints = {0x080052CC, 0x0800A504, 0x0800A538, 0x0800A540,
                       0x0800A5DE, 0x0800A702, 0x080052D0, 0x08005148}
        if args.complete_display:
            checkpoints.update({0x080113E4, 0x08009328, 0x08009362,
                                0x08009366, 0x0801140E, 0x08011416})
        if args.preferences:
            checkpoints.update({0x080116A6, 0x080116AA, 0x08012E38, 0x08012EE4,
                                0x08012F36})
        if args.adc_sample is not None:
            checkpoints.update({0x0800CD04, 0x0800CD5C, 0x080116AE, 0x08014CFC, 0x080116BC})
        for step, (instruction, width) in enumerate(instructions):
            if args.clock_mode and instruction not in checkpoints:
                continue
            writer.writerow((repetition, step, f"0x{instruction:08x}", "instruction", "", width))
        if address is None:
            writer.writerow((repetition, len(instructions), f"0x{pc:08x}", operation, "", ""))
        else:
            writer.writerow((repetition, len(instructions), f"0x{pc:08x}",
                             f"unmodeled_{operation}", f"0x{address:08x}", size))

    if args.frame_output:
        if frames[0] is None or not (frames[0] == frames[1] == frames[2]):
            raise RuntimeError("Display frame was unavailable or differs between repetitions")
        args.frame_output.write_bytes(frames[0])

    if args.serial_output:
        if not (serial_runs[0] == serial_runs[1] == serial_runs[2]):
            raise RuntimeError("USART output differs between repetitions")
        args.serial_output.write_bytes(serial_runs[0])

    for output_path, runs in ((args.dma_output, dma_runs), (args.adc_output, adc_runs), (args.spi_output, spi_runs), (args.timer_output, timer_runs), (args.watchdog_output, watchdog_runs)):
        if not output_path:
            continue
        if not (runs[0] == runs[1] == runs[2]):
            raise RuntimeError(f"Register writes differ between repetitions: {output_path}")
        with output_path.open("w", newline="") as output:
            register_writer = csv.writer(output, delimiter="\t", lineterminator="\n")
            register_writer.writerow(("pc", "address", "value"))
            for write in runs[0]:
                register_writer.writerow(f"0x{value:08x}" for value in write)


if __name__ == "__main__":
    main()
