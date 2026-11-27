#!/usr/bin/env python3
"""Pack a raw T90B application binary (base 0x08005000) into an ALIENTEK .atk file."""

import argparse
import datetime
import struct
from pathlib import Path


def crc16_modbus(data: bytes) -> int:
    crc = 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = ((crc >> 1) ^ 0xA001) if (crc & 1) else (crc >> 1)
    return crc & 0xFFFF


def pack_atk(bin_data: bytes, year: int = 25, month: int = 11, day: int = 27) -> bytes:
    # Align payload to 4-byte boundary
    rem = len(bin_data) % 4
    if rem:
        bin_data = bin_data + (b"\xFF" * (4 - rem))
    # 13-byte T90B header (matches t90.atk):
    # dev_id (0x08, 0x02), ver (0x0a, 0x01), type (0xA0), chunk_len (0x20 = 32),
    # size_u32_le, yy, mm, dd
    header = struct.pack(
        "<BBBBBBIBBB",
        0x08,
        0x02,
        0x0A,
        0x01,
        0xA0,
        0x20,
        len(bin_data),
        year % 100,
        month,
        day,
    )
    payload = bytes(b ^ 0xFF for b in bin_data)
    return header + payload


def main() -> None:
    p = argparse.ArgumentParser(description="Pack T90B .bin into .atk")
    p.add_argument("input_bin", type=Path)
    p.add_argument("output_atk", type=Path)
    args = p.parse_args()

    today = datetime.date.today()
    bin_data = args.input_bin.read_bytes()
    atk_data = pack_atk(bin_data, today.year, today.month, today.day)
    args.output_atk.write_bytes(atk_data)
    print(f"Packed {len(bin_data)} bytes -> {args.output_atk} ({len(atk_data)} bytes)")


if __name__ == "__main__":
    main()
