#!/bin/bash

# How to use take input from command line arguments, and knowing the PID of current shell
#Give 2 command line arguments with this scripts

echo "Name of the Script is " $0

echo "Number of Command Line Arguments " $#

echo "Command Line Argument 1 " $1

echo "Command Line Argument 2 " $2


# Prints PID of cureent shell
echo "PID of current shell " $$

exit 0