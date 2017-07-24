#!/usr/bin/sh

num=$(ls $1 2>/dev/null | grep -c . )
if [ $# -ne 2 ];then
	echo "Error: Invalid number of arguments!"
	exit
fi

directory=$(stat $1 2>/dev/null | grep -c directory)
if [ $directory -eq 0 ];then
	echo "Error: Invalid Input!"
	exit
else
	cnt=$(ls -ld $1 2>/dev/null | grep -c -E "^dr")
	if [ $cnt -eq 0 ];then
		echo "Error: Access denied!"
		exit
	fi 
fi

for i in `seq 1 $num`;do
	file_to_accesed=$(ls $1 | head -$i | tail -1)
	directory=$(stat $1/$file_to_accesed | grep -c directory)
	if [ $directory -eq 0 ];then
		cp $1/$(ls $1 | head -$i | tail -1) $2/
	elif [ $directory -eq 1 ];then
		mkdir $2/$file_to_accesed
		bash 2_4.sh $1/$file_to_accesed $2/$file_to_accesed
	fi
done