#!/bin/bash 

# demo of the break and continue statements 
# the 'break' statement breaks out of the loop 

echo -e "========= BREAK ============== \n"

for i in `seq 1 5 30`
do
    if [ $(($i%2)) -eq 0 ]
    then
	    break
    fi
    echo $i
done



echo -e "======== CONTINUE ========== \n"

# the 'continue' statement suspends current iteration and skips to the next 

for i in {1..30} 				# or for i in `seq 1 30`
do 
    if [ $(($i%2)) -eq 0 ]
   then
           continue
   fi 
   echo $i
done 

exit 0