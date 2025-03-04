/*
*  Syntacore SCR* framework
*  @brief Bare metal tests/benchmarks linker script
*  @author mn-sc
*
* Copyright by Syntacore © 2017. ALL RIGHTS RESERVED.
*
*/

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY {
  RAM (rwx) : ORIGIN = 0-64K, LENGTH = 64K
}
STACK_SIZE = 2048;

SECTIONS {

  .text.init ORIGIN(RAM) : {
    *(.text.init*)
  } >RAM

  .text : {
    PROVIDE(__TEXT_START__ = .);
    *(.text .text.*)
     PROVIDE(__TEXT_END__ = .);
  } >RAM

  .data : {
    *(.data .data.*)
    . = ALIGN(4);
    PROVIDE(__DATA_END__ = .);
  } >RAM

  .bss : {
    *(.bss .bss.*)
    . = ALIGN(4);
    PROVIDE(__BSS_END__ = .);
  } >RAM

  _end = .;
  PROVIDE(__end = .);

  /DISCARD/ : {
    *(.eh_frame .eh_frame.*)
  }
}
