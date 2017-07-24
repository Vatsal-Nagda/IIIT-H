#!/bin/sh

# Use of Logical operators && and || - Conditional execution

if [ $# -ne 2 ] ; then
	echo "Invalid Number of arguments passed"
	exit 2
fi

#Remember '/dev/null' file ? its a Black hole !!!
grep "$1" $2 >/dev/null && echo "Pattern found"

# So in && command2 executes only if Command1 executes successfully


#Remember '2>' ?
grep $2 "$1" 2>/dev/null || echo "Pattern Not found"

# So in || command2 executes only if Command1 is unsuccessful


exit 0 #Always use me buddy!!!!