#!/bin/bash

# Method 1: via the default exit status 
# This script tests the exit status of a function for a return value.  
# This is the status returned by the LAST COMMAND in the function. 
# What if you want to know the status of the rest of the commands in the function? 

function func1()
{
ls -l IExistNot.txt
echo -e "Trying to display a non-existent file...\n"			# swap the lines and see
# ls -l IExistNot.txt 
}


echo -e "Calling func1...\n"

func1				# function  call 

echo "The exit status is: $?"
