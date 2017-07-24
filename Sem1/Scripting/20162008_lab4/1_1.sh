#!/bin/bash

read n

second_last=1
last=1

if [[ $n -ge 2 ]]; then
	echo -n "1 "
	echo -n "1 "
	for i in `seq 3 $n` ; do
		((curr = second_last+last))
		echo -n "$curr "
		((second_last = last))
		((last= curr))
	done
elif [ $n -eq 1 ]; then
	echo -n 1
fi

exit 0