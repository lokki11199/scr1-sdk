#!/bin/bash

riscv64-unknown-elf-objcopy -O verilog --verilog-data-width 4 --reverse-bytes=4 -S build.arty_scr1.tcm.o2/uart.elf mem.mem

awk 'NF { for(i=1; i<=NF; i++) print $i }' mem.mem > mem_formatted.mem

grep "\S" mem_formatted.mem  >> uart.mem && rm mem_formatted.mem && rm mem.mem
