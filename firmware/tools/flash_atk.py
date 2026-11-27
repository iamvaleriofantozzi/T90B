#!/usr/bin/env python3
"""HID bootloader utility for ALIENTEK T90B (VID 0x19F5, PID 0x3245)."""

import argparse
from pathlib import Path
import hid

VID = 0x19F5
PID = 0x3245
ADDR_HOST_TO_DEV = 0xAF
CMD_GET_INFO = 0x10
CMD_SET_FW_INFO = 0x11
CMD_START_DATA = 0x12
CMD_FW_DATA = 0x13
CMD_END_DATA = 0x14
CMD_SET_BOOT = 0x15


def checksum_u8(packet: list[int]) -> int:
    return (-sum(packet)) & 0xFF


def xfer(dev: hid.device, cmd: int, seq: int, data: bytes = b"") -> bytes:
    if len(data) > 59:
        raise ValueError(f"Chunk too large: {len(data)}")
    pkt = [ADDR_HOST_TO_DEV, cmd, seq & 0xFF, len(data)] + list(data)
    pkt.append(checksum_u8(pkt))
    pkt.extend([0] * (64 - len(pkt)))
    dev.write([0x00] + pkt)
    resp = bytes(dev.read(64, timeout_ms=1500))
    if len(resp) < 5:
        raise RuntimeError(f"Short HID response: {resp.hex(' ')}")
    rlen = resp[3]
    return resp[4 : 4 + rlen]


def main() -> None:
    p = argparse.ArgumentParser(description="ALIENTEK T90B HID bootloader tool")
    p.add_argument("--info", action="store_true", help="Read bootloader info (read-only)")
    p.add_argument("--flash", type=Path, help="Flash a .atk file")
    p.add_argument("--yes", action="store_true", help="Confirm flashing")
    args = p.parse_args()

    dev = hid.device()
    dev.open(VID, PID)
    dev.set_nonblocking(0)
    try:
        info = xfer(dev, CMD_GET_INFO, 0)
        print("Device info:", info.hex(" "))
        if args.flash:
            if not args.yes:
                raise SystemExit("Refusing to flash without --yes")
            raw = args.flash.read_bytes()
            if len(raw) <= 13:
                raise SystemExit("Invalid .atk file (too short)")
            hdr, payload = raw[:13], raw[13:]
            print("SET_FW_INFO:", xfer(dev, CMD_SET_FW_INFO, 0, hdr).hex(" "))
            print("START_DATA:", xfer(dev, CMD_START_DATA, 0).hex(" "))
            seq = 0
            for off in range(0, len(payload), 32):
                ack = xfer(dev, CMD_FW_DATA, seq, payload[off : off + 32])
                if not ack or ack[0] != 0:
                    raise RuntimeError(f"Write failed at offset {off}: {ack.hex(' ')}")
                seq = (seq + 1) & 0xFF
            print("END_DATA:", xfer(dev, CMD_END_DATA, 0).hex(" "))
            print("SET_BOOT:", xfer(dev, CMD_SET_BOOT, 0).hex(" "))
            print("Flash complete.")
    finally:
        dev.close()


if __name__ == "__main__":
    main()
