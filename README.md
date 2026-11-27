# 🔥 OpenT90B — Freeing the ALIENTEK T90B Soldering Iron

An open-source, clean-room firmware reconstruction and reverse-engineering project for the **ALIENTEK T90B** smart USB-C soldering iron.

> 🎯 **Ultimate Goal:** Liberate the T90B from its closed-source stock firmware and build a **safe, hackable, open-source firmware** with a **modern, improved UI/UX**! ✨

---

## ⚠️ Safety First

- **Default builds keep the heater DISABLED** (`T90B_HEATER_ENABLED=0`, forcing `TIM1_CCDAT1=0` and `TIM1_BKDT.MOE=0`).
- Closed-loop thermal control and full-power soldering calibration are still a work in progress.
- **Always keep a copy of your stock `t90.atk`** in the repo root so you can restore the official firmware anytime using `./scripts/flash-original.sh`.

---

## 🛠️ What We've Done So Far

### 1. 🔍 Reverse Engineering & Hardware Mapping
- Analyzed the stock application binary (`0x08005000` load base) using **Ghidra**, mapping **415 functions** and **17,824 instructions** ([`analysis/functions.tsv`](analysis/functions.tsv), [`docs/reconstruction/`](docs/reconstruction/)).
- Identified the **NSING N32L403** (ARM Cortex-M4) MMIO peripherals, pinout, and runtime behavior via Unicorn emulation traces ([`analysis/tools/`](analysis/tools/)):
  - **Display:** 40×160 RGB565 SPI LCD (`GC9106`/`GC9107` on `SPI1` — `PB3` SCK, `PB5` MOSI, `PA10` CS, `PD0` DC, `PA6` BL)
  - **Buttons:** `PA15` (Button A) & `PB4` (Button B), active-low
  - **ADC1 (Injected):** `Vin` voltage (`CH2`), Tip temperature (`CH4` / `CH3` depending on channel map), NTC cold-junction sensing
  - **Heater PWM:** `PA7` (`TIM1_CH1`)

### 2. 🔓 Bootloader Unlock & Custom Flashing
- Reverse-engineered the **USB HID bootloader** (`VID 0x19F5`, `PID 0x3245`, `ATK-T90`) and the `.atk` firmware container format (13-byte header + `0xFF`-XORed payload).
- Discovered the **8-byte boot validation record** at `0x08005800` (`.boot_meta` in [`firmware/linker/t90b.ld`](firmware/linker/t90b.ld)), allowing custom-compiled firmware to boot natively without touching the stock bootloader.
- Built [`firmware/tools/pack_atk.py`](firmware/tools/pack_atk.py) and [`firmware/tools/flash_atk.py`](firmware/tools/flash_atk.py) for effortless macOS/cross-platform flashing over USB HID.

### 3. 🧱 Clean-Room C Firmware & Hardware Bring-Up
Implemented a modular, warning-free (`-Wall -Wextra -Werror`) C11 firmware in [`firmware/src/`](firmware/src/) and verified key milestones on **real T90B hardware**:
- ✅ **Safe Boot & Watchdog:** `Reset_Handler`, `.data`/`.bss` init, `TIM1` heater-off enforcement in `board_init()`, and `IWDG` reload.
- ✅ **RGB565 Framebuffer & UI:** 12,800-byte RAM framebuffer rendered over 16-bit `SPI1`, verified on-screen with custom glyphs, boot logo, standby screen, and 16-item menu navigation (`A` + `B`).
- ✅ **Live Sensing & Safety Gates:** Hardware-verified `Vin` undervoltage (`VOL LOW`), tip detection (`NO TIP` vs `HEATER OFF`), NTC/tip ADC response, and fault latching/arming logic in [`firmware/src/heater.c`](firmware/src/heater.c).
- ✅ **Automated Testing:** Host unit tests ([`firmware/tests/test_ui.c`](firmware/tests/test_ui.c)) and Unicorn CPU differential verification ([`firmware/sim/verify_differential.py`](firmware/sim/verify_differential.py)).

---

## 📁 Repository Structure

```text
├── analysis/
│   ├── ghidra/          # Ghidra scripts for seeding, annotating & exporting symbols
│   ├── tools/           # Unicorn-based behavioral & peripheral trace scripts
│   └── functions.tsv    # Mapped function index
├── docs/
│   ├── plans/           # Firmware reconstruction plan & milestones
│   └── reconstruction/  # Pinout, register maps, SPI/ADC/DMA traces & release notes
├── firmware/
│   ├── include/         # Shared headers (t90b.h)
│   ├── linker/          # Linker script with 0x08005000 base & .boot_meta section
│   ├── sim/             # Unicorn & Renode verification scripts
│   ├── src/             # Clean-room C firmware (startup, board, ui, heater, main)
│   ├── tests/           # Host unit test suite
│   ├── tools/           # .atk packer & USB HID flasher
│   └── Makefile         # Build & test targets
└── scripts/
    ├── flash-custom.sh  # Flash custom firmware build via USB HID
    └── flash-original.sh# Restore stock t90.atk firmware via USB HID
```

---

## 🚀 Getting Started

### Prerequisites
- `arm-none-eabi-gcc` (see [`firmware/toolchain.lock`](firmware/toolchain.lock))
- `cc` (host C compiler for unit tests)
- Python 3 + [`uv`](https://docs.astral.sh/uv/) (for `unicorn` emulation and `hidapi` flashing)

### Build & Test
```sh
# Build the firmware (.elf, .bin, .atk)
make -C firmware clean all

# Run host unit tests (UI & heater safety state machine)
make -C firmware test

# Verify safe TIM1 / boot state in Unicorn emulator
uv run --with unicorn==2.1.4 python3 firmware/sim/verify_differential.py

# Inspect connected T90B over USB HID
uv run --with hidapi python3 firmware/tools/flash_atk.py --info
```

### Flashing
> 💡 Place your stock `t90.atk` in the repository root if you want to use `flash-original.sh` as a fallback.

```sh
# Flash custom firmware
./scripts/flash-custom.sh

# Restore stock firmware
./scripts/flash-original.sh
```

---

## 🗺️ Roadmap

- [x] Reverse-engineer stock firmware, memory map, and `.atk` bootloader protocol
- [x] Build clean-room C firmware with safe heater-off hardware bring-up
- [x] Verify LCD framebuffer, buttons, `Vin`, tip detection, and fault latching on hardware
- [ ] Complete closed-loop thermal calibration & safe PID heater control
- [ ] Design and implement the **new & improved UI/UX** (cleaner typography, better temperature/power feedback, smoother menu ergonomics, and custom presets) 🎨✨

---

## 📜 Note on Proprietary Files

Original vendor binaries (`t90.atk`, `analysis/t90-app.bin`), device EEPROM/bootloader dumps, and local Ghidra project databases are intentionally excluded via `.gitignore`.
