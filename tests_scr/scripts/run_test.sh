#!/bin/bash

app=$1

compliance_dir=$(pwd)/../riscv_compliance

# make -C $compliance_dir/$app clean --silent
# make -C $compliance_dir/$app --silent

exetutable=$(find $compliance_dir/$app/build* -name "$app.elf")

output=$(riscv64-unknown-elf-gdb -ex "file $exetutable" \
                        -ex "target extended-remote localhost:3333" \
                        -ex "set confirm off" \
                        -ex "load" \
                        -ex "b test_exit" \
                        -ex "c" \
                        -ex "p/x \$t0" \
                        -ex "quit"
)

exit_code=$(echo "$output" | grep -oP '\$1 = \K0x[0-9a-f]+')

echo "Test name: $app | EXIT CODE: $exit_code"
