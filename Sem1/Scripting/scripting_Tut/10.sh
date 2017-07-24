#!/bin/bash

#Evaluate expressions and numeric comparison operators


#Below are some numeric comparison operators
# -eq 	Equal to
# -ne 	Not Equal to
# -gt 	greater than
# -lt 	less than
# -ge 	greater than or equal to
# -le 	less than or equal to


x=15
y=7

test $x -gt $y
echo $?

#shorthand for test []

[ $x -gt $y ] #take care of spaces, each of these fellas needs some space
echo $?

exit 0

