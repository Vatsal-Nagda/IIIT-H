#!/bin/bash

# How to use variables

var="Hakuna Matata"

echo $var


# Uncomment the below 2 lines and see the output of script

# var2 = "Hakuna Matata"
# echo $var2


# above line will produce an error as spaces
# will make shell interpret the line as
# a command var2 called with parameters: = and "Hakuna Matata"


# Uncomment the below 2 lines and see the output of script

# var="Good"
# echo $varNight

#Did the above echo cmd produced any output ? why ?

# try below echo cmd

# echo ${var}Night 


exit 0