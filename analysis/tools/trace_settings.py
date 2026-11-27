"""Exercise original settings validation with synthetic flash records."""

import argparse
import csv
import hashlib
import struct
import sys
from pathlib import Path

from unicorn import (Uc, UC_ARCH_ARM, UC_HOOK_CODE, UC_MODE_MCLASS,
                     UC_MODE_THUMB, UC_PROT_EXEC, UC_PROT_READ)
from unicorn.arm_const import UC_ARM_REG_SP

from trace_ui_dispatch import BASE, EXPECTED_SHA256, SRAM, STACK

PAGE = 0x0801F000
COPY = 0x200001C8
BLOCKS = ((0x14, 0x1C, 0x08015FD8), (0x30, 0x70, 0x08015F68))
REPAIR, ACCEPT = 0x08012EE0, 0x08012EE4


def sealed(data):
    return struct.pack("<I", sum(data[4:]) & 0xFF) + data[4:]


def flash_input(app, scenario):
    page = bytearray(b"\xff" * 0x1000)
    if scenario != "erased":
        for offset, size, default in BLOCKS:
            data = app[default - BASE:default - BASE + size]
            page[offset:offset + size] = sealed(data)
    if scenario == "valid-custom":
        offset, size, _ = BLOCKS[1]
        page[offset + 8] = 5
        page[offset:offset + size] = sealed(page[offset:offset + size])
    if scenario == "bad-checksum":
        page[0x14] ^= 1
    if scenario == "bad-length":
        offset, size, _ = BLOCKS[1]
        page[offset + 4] ^= 1
        page[offset:offset + size] = sealed(page[offset:offset + size])
    return bytes(page)


def boot_preferences(app):
    page = bytearray(flash_input(app, "valid"))
    journal_address = ((0x3F * 0x800) + 0x08000000) - PAGE
    default_journal = 0x08015FF4 - BASE
    page[journal_address:journal_address + 12] = sealed(app[default_journal:default_journal + 12])
    return bytes(page)


def observe(app, page):
    machine = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    machine.mem_map(BASE, 0x18000)
    machine.mem_write(BASE, app)
    machine.mem_protect(BASE, 0x18000, UC_PROT_READ | UC_PROT_EXEC)
    machine.mem_map(PAGE, 0x1000)
    machine.mem_write(PAGE, page)
    machine.mem_protect(PAGE, 0x1000, UC_PROT_READ)
    machine.mem_map(SRAM, 0x6000)
    machine.reg_write(UC_ARM_REG_SP, STACK)
    stops = []
    restored = []

    def checkpoint(emu, address, _size, _data):
        if address in (0x08012E66, 0x08012EB4):
            restored.append(address)
        if address in (REPAIR, ACCEPT):
            stops.append(address)
            emu.emu_stop()

    machine.hook_add(UC_HOOK_CODE, checkpoint)
    machine.emu_start(0x08012E39, BASE + len(app), count=12000)
    if len(stops) != 1:
        raise RuntimeError("Settings validation did not reach a decision")
    return stops[0], restored, bytes(machine.mem_read(COPY, 0xA0))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("payload", type=Path)
    args = parser.parse_args()
    app = args.payload.read_bytes()
    if hashlib.sha256(app).hexdigest() != EXPECTED_SHA256:
        raise ValueError("Payload differs from the audited baseline")
    writer = csv.writer(sys.stdout, delimiter="\t", lineterminator="\n")
    writer.writerow(("scenario", "repetition", "decision_pc", "restored_blocks", "ram_sha256"))
    for scenario, expected_restores in (
        ("erased", [0x08012E66, 0x08012EB4]),
        ("valid", []),
        ("valid-custom", []),
        ("bad-checksum", [0x08012E66]),
        ("bad-length", [0x08012EB4]),
    ):
        page = flash_input(app, scenario)
        for repetition in range(1, 4):
            stop, restored, current = observe(app, page)
            if restored != expected_restores or stop != (REPAIR if restored else ACCEPT):
                raise AssertionError(f"Unexpected validation decision for {scenario}")
            for offset, size, default in BLOCKS:
                baseline = sealed(app[default - BASE:default - BASE + size])
                if scenario == "valid-custom":
                    baseline = page[offset:offset + size]
                if current[offset:offset + size] != baseline:
                    raise AssertionError(f"Unexpected RAM for {scenario} at offset {offset:#x}")
            writer.writerow((scenario, repetition, f"0x{stop:08x}",
                             ",".join(f"0x{entry:08x}" for entry in restored),
                             hashlib.sha256(current).hexdigest()))


if __name__ == "__main__":
    main()
