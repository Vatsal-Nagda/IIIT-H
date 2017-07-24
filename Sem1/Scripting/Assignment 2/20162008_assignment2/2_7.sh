#!/bin/usr/bash
before="$(cat BEFOREleavingLab.tsv | awk '{if(NF > 0 && NR > 1){print $2"  "$(NF-1)}}' | sort)"
after="$(cat AFTERleavingLab.tsv | awk '{if(NF > 0 && NR > 1){print $2"  "$(NF-1)}}' | sort)"


#echo "$before" | while read line; do name="$(echo "$line" | cut -d'_' -f1 | cut -d' ' -f1 )"; marks="$(echo "$line" | cut -d' ' -f2)"; echo "$name" ;echo "$marks" ;done

#echo "$before" | awk ''
count="$(echo "$before"|wc -l | cut -d' ' -f1)"

# for index in `seq 1 $count `
# do
# 	line="$(echo "$before" | head -$index | tail -1)"
# 	val="$(echo "$line" | tr -s " " | cut -d' ' -f2 )"
# 	arr[$index]=$var
# 	echo "$var"
# done
for index in ` seq 1 $count `; do count1="$(echo "$before" | head -$index | tail -1)"; val="$(echo "$count1" | tr -s " " | cut -d' ' -f2 )"; arr[$index]=$val ; done
#echo ${arr[@]}

count_after="$(echo "$after"|wc -l | cut -d' ' -f1)"
for index_after in ` seq 1 $count_after `; do count1_after="$(echo "$after" | head -$index_after | tail -1)"; val_after="$(echo "$count1_after" | tr -s " " | cut -d' ' -f2 )"; name="$(echo "$count1_after" | tr -s " " | cut -d' ' -f1 )"; ((x=$val_after - ${arr[$index_after]})); x=$(echo "$x*0.5" | bc); arr[$index_after]=$(echo "${arr[index_after]}+$x" | bc); echo "$name ${arr[index_after]}"; done

#for index_final in ` seq 1 $count_after `; do count1_final="$(echo "$after" | head -$index_final | tail -1)"; echo "$count1_final" ; done

#echo ${arr[@]}
# for index in `seq 1 $count `
# do
# 	line="$(echo "$before" | head -$index | tail -1)"
# 	val="$(echo "$line" | tr -s " " | cut -d' ' -f2 )"
# 	#((arr[$index]= arr[$index] + $var))
# 	echo "$line ${arr[$index]}"
# done

# for line in ` awk '{printf $1" "$2"\n" }' `
# do
# 	inp="$(echo "$line" | cut -d'_' -f1 |cut -d' ' -f1)"
# 	mrk="$(echo "$line" | cut -d' ' -f2)"
# 	arr[$inp]=$mrk
# done

# for index in ${!arr[@]}; do
#     #	echo -n $index/${#array[@]}
#     echo "$index -> ${arr[$index]}"
# done

# declare -A TOTAL

# for i in "$before";do
# 	#echo "$i"
# 	name="$(echo "$i" | tr -s " " | cut -d'_' -f1 | cut -d' ' -f1)"	
# 	marks="$(echo "$i" | tr -s " " | cut -d' ' -f2)"
# 	#echo "$name $marks"
# 	echo "$marks"
# 	TOTAL[$name]=$marks
# 	#printf "%s\n"$name
# done

# for i in "${!TOTAL[@]}"
# do
# 	echo "$i -> ${TOTAL[$i]}"
# done


# for index in "${!TOTAL[@]}"; do
#    # echo -n "key is : $index"
#     echo " value is ${TOTAL[$index]}"
# done