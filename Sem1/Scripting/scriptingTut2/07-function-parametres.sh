#!/bin/bash 

# Just like command-line arguments, possible to pass parameters to functions too
# {$FUNCNAME, $1, $2 ...} = {function name, 1st param, 2nd param ...} respectively 

Addition() 
{
if [[ $# -eq 0 || $# -gt 2 ]]			# OR:  if [ $# -eq 0 ] || [ $# -gt 2 ]
then 
echo "Oops! Called with $# argument(s). I need just 1 or 2." 

elif  [ $# -eq 1 ] 
then
echo $(( $1 + $1 ))

else 
echo $[$1 + $2] 
fi 
return
}

echo "sum1 = `Addition` "			# no function parameter

echo "sum2 = $(Addition 5) " 			# $# = 1

echo "sum3 = `Addition 10 20` "			# $# = 2

sum4=$(Addition 1 2 3)
echo $sum4  		# $# = 3

# for token in $sum4
# do
# echo $token
# done

exit 0 
