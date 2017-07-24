#!/bin/bash

# demo of the for loop construct 

# IFS='-'
for i in 1 2 3 4 5                   
do                                    
 echo $i 
done


# What is going on here? Uncomment each and see

#for file in "$@"		      # and if you use "$*" instead ?? 
#do
#   mv $file ${file}.txt
#done


# We can specify ranges also 

# for i in {1..20..2}             # for i in `seq  1 2 20`  seq start increment end
# do 				# display in descending order ??
#   echo $i
# done


# Also, C-like flavor

# for ((i=1;i<=20;i+=2))
# do
#   echo $i
# done

exit 0

