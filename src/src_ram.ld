MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 0x3F000 /* 256KB RAM */
}

SECTIONS
{
  .vectors : ALIGN(4)
  {
    KEEP(*(.vectors))
  } > RAM

  .text : ALIGN(4)
  {
    *(.text*)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
  } > RAM

  .data : ALIGN(4)
  {
    *(.data*)
  } > RAM

  .bss : ALIGN(4)
  {
    *(.bss*)
    *(COMMON)
  } > RAM

  _end = .;
  PROVIDE(end = .);
}
