#!/bin/bash

if [ "$1" = "r" ]
then
openFPGALoader -b arty_a7_100t arty_scr1.bit
fi

sudo ${OOCD_ROOT}/bin/openocd -s ${OOCD_ROOT}/share/openocd/scripts \
-f ${OOCD_ROOT}/share/openocd/scripts/interface/ftdi/digilent-hs2a.cfg \
-f ${OOCD_ROOT}/share/openocd/scripts/target/syntacore_riscv.cfg
