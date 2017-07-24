IFS=$'\n' read -d '' -r -a lines < chatNames.txt

for i in ${!lines[@]};do

	#x=$(echo ${lines[$i]})
	x=`echo ${lines[$i]} | grep -o "." | sort -u | wc -l`
	if ((x%2 == 1));then
		echo "IGNORE HIM!"
	else
		echo "CHAT WITH HER!"
	fi
	#echo $x
done

#echo ${lines[*]}
