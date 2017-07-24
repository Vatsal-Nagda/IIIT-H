#!/bin/bash

# The 'until' construct is similar to 'while'. 
# It executes the statements as long as the condition remains false (i.e. until the condition becomes true)
# Same as adding the logical 'not'  (!) to the while condition

i=1

until  [ $i -ge 11 ]
do
   echo $i
   let i+=1  		  # also: ((i++)) or i=`expr $i + 1`
done

exit 0