#!/bin/bash

if [ $# -eq 0 ]
then
	echo "No arguments given"
	echo "You did not enter target directory"
	exit
fi 

if [ $# -eq 1 ]
then 
	echo "You did not enter command file name"
	exit
fi

dir=$1
dir=$(echo "$dir" | sed -e "s/\/$//g" )
temp=$dir
dir=$dir/*.sh
file=$2

if [ ! -d "$temp" ]
then
	echo "Incorrect directory path"
	exit
fi

ls $dir &> /dev/null
if [ $? -ne 0 ]
then
	echo "No scripts found in target"
	exit
fi

for i in $(ls $dir)
do
	echo -n $(echo $i | rev | cut -d '.' -f2 | rev | sed -e "s/^\///g")") "  >> $file
	for j in $(cat $i)
	do
		echo $j >> $file
	done
done

if [ $? -ne 0 ]
then 
	echo "Error"
	exit
fi



