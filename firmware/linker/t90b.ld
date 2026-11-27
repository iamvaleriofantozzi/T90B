/* Linker script for ALIENTEK T90B (N32L403 Cortex-M4) application firmware.
 * Application base: 0x08005000 (bootloader occupies 0x08000000-0x08004FFF).
 * Preferences/calibration pages at 0x0801F000-0x0801FFFF are reserved and excluded.
 */
ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08005000, LENGTH = 104K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 24K
}

_estack = ORIGIN(RAM) + LENGTH(RAM) - 0x1000;

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  /* ALIENTEK T90B bootloader writes 8-byte boot-valid metadata at 0x08005800.
   * Keep 0x08005800-0x08005807 reserved (00 00 00 00 00 FF FF FF). */
  .boot_meta 0x08005800 :
  {
    BYTE(0x00); BYTE(0x00); BYTE(0x00); BYTE(0x00);
    BYTE(0x00); BYTE(0xFF); BYTE(0xFF); BYTE(0xFF);
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } > FLASH

  .data : AT(_etext)
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM

  _sidata = LOADADDR(.data);

  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM
}

ASSERT(_ebss <= _estack - 0x1000, "T90B RAM must leave 4 KiB for the stack")
