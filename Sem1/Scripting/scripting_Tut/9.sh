#!/bin/bash

Arr[0]='ek'

Arr[1]='do'

Arr[3]='teen'

x=3
echo "Arr is: $Arr"         	 # ??

echo "The array elements are: ${Arr[0]} and ${Arr[1]} ${Arr[2]} ${Arr[$x]}"	
echo


# Initialization possible 

courses=(SCE APS OS DMA 1 2 3)

echo "My courses are: ${courses[*]}"		#try me also ${courses[@]}

# echo "courses[4] = ${courses[4]}" 		# ??




# The unset command deletes an array variable 

# unset Arr			# possible to delete by index too

# echo $Arr


exit 0

