#!/bin/bash 

#IFS=$'\n' read -d '' -r -a lines < SubmittedFiles.txt

i=0
count=0
while read -r data; do
	data[i]=$data
	((i++))
	((count++))
done < SubmittedFiles.txt

random=$(shuf -i 1-$count -n $count)

for index in `seq 1 $count`; do
    numbers[index]=$(echo ${data[$index]}|cut -d'_' -f1)
    #echo ${numbers[$index]}
done
#echo ${data[*]}

echo "size :"$count

TA=(Prabhakar Sheshadri Viplav Akanksha Deeksha Rambabu Harika)

ta_num=0
round=1;

count=1
for i in $random;do
	# if [ $ta_num -eq 0 ];then
	# 	echo
	echo "$count. ${numbers[$i]} - "${TA[$ta_num]}
	((ta_num = ta_num+1))

	if [[ $ta_num -eq 7 ]]; then
		echo "------------------------  ROUND $round   ------------------------"
		((round++))
		((ta_num = ta_num%7))
	fi

	((count++))
	done


#sort -r numbers

#for i in `seq 1 $count`;do
