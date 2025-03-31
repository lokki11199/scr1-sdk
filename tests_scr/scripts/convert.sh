#!/bin/bash

app=$1

elf_path=$(find $(pwd)/build* -name "*.elf")

riscv64-unknown-elf-objcopy -O verilog --verilog-data-width 4 --strip-debug -S $elf_path mem.mem --reverse-bytes=4

awk 'NF { for(i=1; i<=NF; i++) print $i }' mem.mem > mem_formatted.mem

grep "\S" mem_formatted.mem  >> $app.mem && rm mem_formatted.mem && rm mem.mem

sed -i 's/^@F/@0/' $app.mem
