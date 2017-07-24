for index in *.tar.gz ; do


	echo "Format Check-   "$index

	if [[ $index =~ ^[0-9]{8}\_assignment[0-9]\.tar\.gz$ ]] 
		then
		echo "Archive name in correct format"

	else echo "Wrong Archive name format"
	fi


	sh=0
	file=0

	for j in `tar -tf $index | grep '^.*.sh$'` 
	do
		((sh++))
		if [[ $j =~ ^[0-9]*\_[0-9]*\_[a-z]*\.sh$ ]] 
			then
			echo $j" -OK"

		else echo $j" -Wrong Formating"
		fi
	done


	if [ $sh -eq 0 ]
		then
		echo "Missing .sh files -REJECT";
	fi
	

	for j in `tar -tf $index | grep '^.*.script$'` 
	do
		((file++))
	done

	if [ $file -eq 0 ]
		then
		echo "Missing script file -REJECT";
	else
		echo "script file - ok"
	fi




done
