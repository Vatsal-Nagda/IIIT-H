source ./1a.sh

circle $@
ans=$?
if [[ $ans -eq 255 ]]; then
	echo "circle area :NOT POSSIBLE"
else
	echo -n "circle  : "
	echo $ans
fi


square $@
ans=$?
#echo $ans
if [[ $ans -eq 255 ]]; then
	echo "square area :NOT POSSIBLE"
else
	echo -n "square : "
	echo $ans
fi

rectangle $@
ans=$?
#echo $ans
if [[ $ans -eq 255 ]]; then
	echo "rectangle area :NOT POSSIBLE"
else
	echo -n "rectangle: "
	echo $ans
fi

r_triangle $@
ans=$?
#echo $ans
if [[ $ans -eq 255 ]]; then
	echo "r_triangle area :NOT POSSIBLE"
else
	echo -n "r_triangle : "
	echo $ans
fi

a_triangle $@
ans=$?
#echo $ans
if [[ $ans -eq 255 ]]; then
	echo "a_triangle area :NOT POSSIBLE"
else
	echo -n "In a_triangle : "
	echo $ans
fi

trapezium $@
ans=$?
#echo $ans
if [[ $ans -eq 255 ]]; then
	echo "trapezium area :NOT POSSIBLE"
else
	echo -n "In trapezium : "
	echo $ans
fi