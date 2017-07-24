#!/bin/bash

# Demonstrating function variables: global and local
# By default, a shell variable has a global scope. Will it be visible to subshells/child shells ??
# 'local' is used within a function; it makes a variable's visibility restricted to that function and its children (if any)

func1()
{

echo "Value of temp INSIDE func1: $temp"

echo "Value of n INSIDE func1: $n"

result=$(( $temp * 4 ))			# if "result" is local ??

}


temp=4 ; n=10

func1

echo "The result is $result"

echo "Value of temp OUTSIDE func1: $temp"

echo -e "Value of n OUTSIDE func1: $n \n"




# A local variable declared in a function is also visible to functions called by the parent function.


foo()
{
  local n=20

  echo "Within foo(), \$n = $n"

  bar					# calling bar()
}

bar()
{
  echo "Within bar(), \$n = $n"
}


foo             			# calling foo()



exit 0

