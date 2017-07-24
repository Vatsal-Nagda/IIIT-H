#!/bin/bash

# Method 2: using the 'return' command in a function
# We can explicitly set the exit status 

# Two important points: 
#	1. retrieve the return value as soon as the function completes.
#       2. Exit status is b/n [0,255] only. 

function TripleMe
{
echo "Inside the TripleMe function... "

read -p "Enter a value: " value

echo "Tripling the value..."

return $[$value * 3]                 # or $(( $value * 3 ))

}


TripleMe 

echo "The tripled value is $?"        # this statement must follow the function call immediately


# what if value>85 or negative ?
