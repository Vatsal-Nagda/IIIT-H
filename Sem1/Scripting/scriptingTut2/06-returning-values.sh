#!/bin/bash

# Method 3: Returning value from a function by assigning output of the function to a shell variable
# This method works for floating point and string values too. 


function DoubleMe
{
read -p "Give me a number to double: " n

echo $(( $n * 2 ))      		    # what if n is floating point? Try it! 

# x=5
# y=6
# echo $x $y
# echo "sgfgfg gsdgdfh"
# return $[$n * 3] 
}

result=`DoubleMe`                           # or $(DoubleMe)
# echo $?
echo "The double is $result"

# echo "$result"


#echo "Double of $n is: $result"	# Figure this out. $n = ??
					# For more, see http://www.tldp.org/LDP/abs/html/localvar.html



# Uncomment these two as well and see what happens

# DoubleMe                         	        # calling the func
# echo "Double of $n is: $result"                # $n = ??




# How would you return multiple values from a function?   

# for i in $result
# do
# echo $i
# done
