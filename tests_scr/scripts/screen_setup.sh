#!/bin/bash

##############################################################################
#
# Reads the tty while logging the output to file
#
# @author Kirill Zhernov

##############################################################################

screen -L -Logfile test_results.log -d -m -S UART /dev/ttyUSB2 115200,cs8,-cstopb

if [ "$1" = "r" ]
then
screen -r UART 
fi
