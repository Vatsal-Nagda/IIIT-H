#!/bin/bash 

# Demo of passing arrays to/from functions

function func
{
echo "Now inside func(). $# Displaying the passed parameters ... $@"

local temp=$1				  	# try this instead:  temp=(`echo $@`) or temp=($@)

echo "**************** "$1 $2 $3 $4 $5
echo "Still inside func(). The passed array is --> " ${temp[*]}
# ...do something with the array...
echo
echo $2
return 
} 


array=(2 4 /bin /usr/bin)

echo "The given array has ${#array[*]} members and they are: ${array[*]} "

# Now, let's pass the array  
func ${array[*]} "Hello"					# try this instead:  	func ${array[*]}


# How about returning an array from a function?? Try it!  
