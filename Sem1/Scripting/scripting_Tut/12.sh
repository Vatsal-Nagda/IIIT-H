#!/bin/bash

#Switch Case and basic arithmetic operations with expr
#expr performs basic arithmetic operations, but it handles only int



echo -e "Enter x \c"
read x
echo -e "Enter y \c"
read y
echo -e "Select the operation :"
echo -e "Enter 1 for +"
echo -e "Enter 2 for -"
echo -e "Enter 3 for *"
echo -e "Enter 4 for /"
echo -e "Enter 5 for %"
read op
case $op in
	1) z=`expr $x + $y`;; #why are we using ` ? 
	2) z=`expr $x - $y`;;
	3) z=`expr $x \* $y`;; #why we escaped * ?
	4) z=`expr $x / $y`;;
	5) z=`expr $x % $y`;;
	*) echo "Wrong operation selected";;
esac

# expr $x + $y
echo $z

#      ToDo
#try evaluating arithmetic expression using $(()) also





#Demo of OR
echo -e "Enter day of week (first 3 letters in Caps) \c"
read day

case $day in
	SAT|SUN) echo "It's a weekend!!!";; #see we can use | --> OR in case, we can also use regex here. Give it a try
	*) echo "Damn it, it's a weekday";;
esac

exit 0 