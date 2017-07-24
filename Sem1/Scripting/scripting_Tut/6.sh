#!/bin/bash

#Difference between $@ and $*
# Run the script with some command-line arguments 
# observe the difference 

# IFS="%"          		# default delimiter <space> changed to '-'

echo "1. Use of \$@ : "	
echo $10
echo "$@"
# $@ is expanded as "arg1" "arg2" ..."arg N"
echo 
 
echo "2. Use of \$* : "        
echo "$*"
# $* is expanded as "arg1 arg2 ... arg N" separated by $IFS
#Stores the complete set of arguments as a single string

exit 0