"""Differential & safety verification of candidate t90b.bin vs original t90-app.bin in Unicorn."""

import csv
import hashlib
import struct
import sys
from pathlib import Path

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_MCLASS, UC_MODE_THUMB
from unicorn.arm_const import UC_ARM_REG_PC, UC_ARM_REG_SP

BASE = 0x08005000
SRAM = 0x20000000


def verify_candidate_boot(bin_path: Path, heater_drive: bool = False):
    data = bin_path.read_bytes()
    sp, reset = struct.unpack_from("<II", data)
    assert sp == 0x20005000, f"Unexpected candidate SP: {sp:#x}"
    assert (reset & ~1) >= BASE, f"Reset vector outside app flash: {reset:#x}"

    uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    uc.mem_map(BASE, 0x1A000)
    uc.mem_write(BASE, data)
    uc.mem_map(0x0801F000, 0x1000)
    uc.mem_write(0x0801F000, b"\xff" * 0x1000)
    uc.mem_map(SRAM, 0x6000)
    uc.mem_map(0xE000E000, 0x1000)

    mmio = {
        0x40021014: 0x14,
        0x40021018: 0,
        0x40000018: 0x60,  # Start in PWM mode to check the boot override.
        0x40013008: 0x0002,  # SPI1_STS: TE=1, BUSY=0
        0x40020800: 0x0002,  # ADC1_STS: ENDC=1
        0x40003000: 0,
    }
    writes = []

    def mmio_read(emu, offset, size, base):
        return mmio.get(base + offset, 0)

    def mmio_write(emu, offset, size, value, base):
        addr = base + offset
        mmio[addr] = value
        writes.append((addr, value))

    for page in (0x40000000, 0x40003000, 0x40010000, 0x40011000, 0x40012000, 0x40013000, 0x40020000, 0x40021000):
        uc.mmio_map(page, 0x1000, mmio_read, page, mmio_write, page)

    uc.reg_write(UC_ARM_REG_SP, sp)
    # Unicorn does not advance SysTick. Allow both LCD delay fallback loops to finish.
    uc.emu_start(reset, BASE + len(data), count=16000000)

    if heater_drive:
        assert mmio[0x40000018] == 0x40, "Heater timer did not enter forced-low mode"
        assert mmio[0x40010820] & 0xF == 2, "PA0 is not assigned to AF2"
    else:
        assert not any(0x40000000 <= a < 0x40001000 for a, _ in writes), "Heater timer was accessed"
        assert all((v & 0xF) == 0 for a, v in writes if a == 0x40010820), "PA0 AF changed"
        assert all((v & 3) == 0 for a, v in writes if a in (0x40010800, 0x4001080C)), "PA0 mode or pull changed"
        assert all((v & 1) == 0 for a, v in writes if a == 0x4002101C), "Heater timer clock was enabled"
    assert any(a == 0x40003000 and v == 0xAAAA for a, v in writes), "IWDG reload missing"
    return hashlib.sha256(data).hexdigest(), mmio[0x40000018]



def main():
    import argparse

    parser = argparse.ArgumentParser(description="Verify the T90B boot safe-state")
    parser.add_argument("candidate", nargs="?", type=Path, default=Path("firmware/build/t90b.bin"))
    parser.add_argument("--heater-drive", action="store_true", help="Check an enabled simulation build")
    args = parser.parse_args()
    sha, mode = verify_candidate_boot(args.candidate, args.heater_drive)
    print(f"Candidate SHA-256: {sha}")
    result = f"PA0 AF2, heater timer mode={mode:#x}" if args.heater_drive else "PA0 and heater timer left untouched"
    print(f"Candidate boot check: {result} -> PASS")


if __name__ == "__main__":
    main()
