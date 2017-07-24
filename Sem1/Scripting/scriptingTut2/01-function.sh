#!/bin/bash

# demo of defining and calling a function 
# Function definition should precede the calling

function func1()                  # or just func1()  
{
  echo "Inside func1"
}




func1                  # calling...

echo $?					#remember me($?) ?

# Now, try calling func2 instead of func1
func2()
{
echo "Hello"
}