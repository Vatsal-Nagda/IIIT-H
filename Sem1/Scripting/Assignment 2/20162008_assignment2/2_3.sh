#!/usr/bin/sh 
 
function file_lst()
{
 is_directory=$(stat $1 2>/dev/null | grep -c directory)
 if [ $is_directory -eq 0 ];then 
 	echo 'Error: Invalid File/Directory!'; return;
fi

cd $1
 echo; 
 echo $PWD:; 
 for i in *; do
 	is_directory=$(stat $i 2>/dev/null | grep -c directory)
 	if [ $is_directory -eq 1 ];then 
 		file_lst $i 
		cd ..
 	else
 		echo -n $i;
 	echo;
	fi
 done
}

if [ $# -eq 0 ];then 
	file_lst .
exit
fi

for i in $*;do
 DIR=$1 
 file_lst $DIR
 shift 1
done