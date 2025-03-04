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
  TCM (rwx) : ORIGIN = 0xF0000000, LENGTH = 64K
}

SECTIONS {

  .text.init ORIGIN(TCM) : {
    *(.text.init*)
  } >TCM

  .text : {
    PROVIDE(__TEXT_START__ = .);
    *(.text .text.*)
     PROVIDE(__TEXT_END__ = .);
  } >TCM

  .data : {
    *(.data .data.*)
    . = ALIGN(4);
    PROVIDE(__DATA_END__ = .);
  } >TCM

  .bss : {
    *(.bss .bss.*)
    . = ALIGN(4);
    PROVIDE(__BSS_END__ = .);
  } >TCM

  _end = .;
  PROVIDE(__end = .);
}
