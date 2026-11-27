"""Execute the original UI dispatcher under Unicorn 2.1.4.

The harness injects the UI index and observes the first instruction of
the selected callback. It does not emulate the caller or cartridge.
"""

import argparse
import csv
import hashlib
import struct
import sys
from pathlib import Path

from unicorn import Uc, UC_ARCH_ARM, UC_HOOK_CODE, UC_MODE_MCLASS, UC_MODE_THUMB
from unicorn.arm_const import UC_ARM_REG_SP

BASE = 0x08005000
DISPATCH = 0x08014CE0
TABLE = 0x08016100
SLOT_COUNT = 16
SRAM = 0x20000000
INDEX = SRAM + 0x38
STACK = SRAM + 0x5000
EXPECTED_SHA256 = "bc1da48244dddc68dc81d337ca2ef4dda3c477d5853dd6d5853cf4b1b342f125"


def observe_target(app, index):
    machine = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
    machine.mem_map(BASE, 0x18000)
    machine.mem_write(BASE, app)
    machine.mem_map(SRAM, 0x6000)
    machine.mem_write(INDEX, struct.pack("<I", index))
    machine.reg_write(UC_ARM_REG_SP, STACK)
    history = []

    def capture(emu, address, _size, _data):
        history.append(address)
        if not DISPATCH <= address < DISPATCH + 0x12:
            emu.emu_stop()

    machine.hook_add(UC_HOOK_CODE, capture)
    machine.emu_start(DISPATCH | 1, BASE + len(app), count=16)
    if len(history) < 2 or history[-2] != 0x08014CEE:
        raise AssertionError(f"Index {index} did not reach the callback via BLX: {history}")
    return history[-1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("payload", type=Path)
    args = parser.parse_args()
    app = args.payload.read_bytes()
    if hashlib.sha256(app).hexdigest() != EXPECTED_SHA256:
        raise ValueError("Payload differs from the audited baseline")
    writer = csv.writer(sys.stdout, delimiter="\t", lineterminator="\n")
    writer.writerow(("index", "repetition", "table_slot", "target", "result"))
    for index in range(SLOT_COUNT):
        slot = TABLE + index * 4
        pointer, = struct.unpack_from("<I", app, slot - BASE)
        if pointer == 0:
            writer.writerow((index, "", f"0x{slot:08x}", "", "null_slot_not_executed"))
            continue
        for repetition in range(1, 4):
            target = observe_target(app, index)
            if pointer != target | 1:
                raise AssertionError(f"Index {index}: observed {target:#x}, expected {pointer:#x}")
            writer.writerow((index, repetition, f"0x{slot:08x}", f"0x{target:08x}", "observed"))


if __name__ == "__main__":
    main()
