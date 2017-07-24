#!/bin/bash

# Simple demo of the while loop statement 

i=1                         # initialization 

while [ $i -le 20 ]  	    # same as: while test $i -le 20
do
  echo "$i"  			  # also printf
  i=$(($i+1))                     # same as   i=`expr $i + 1` or let i+=1 
done 

exit 0