#!/bin/bash

screen -d -m -S UART -L -Logfile ./log.txt /dev/ttyUSB2 115200,cs8,-cstopb

if [ "$1" = "r" ]
then
screen -r UART 
fi
