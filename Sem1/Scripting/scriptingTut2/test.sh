#!/bin/bash

IFS="-"
a=$(ls)
echo ${#a[@]}
for i in $a
do
	echo $i
done