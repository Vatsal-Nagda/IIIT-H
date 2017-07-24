#!/bin/bash

#Array index and array size

# !array[@] --> gives array indexes
# #array[@] --> gives array size 




array=( item1  item2 item3 )

# Uncomment the below two lines and see the outputs 

array[40]="item4"
#echo ${!array[*]}



for index in ${!array[@]}; do
    #echo -n $index/${#array[@]}
    echo "$index -> ${array[$index]}"
done