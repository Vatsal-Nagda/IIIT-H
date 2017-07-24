#!/bin/sh

# difference between $@ and $*

star_count=0
at_count=0

for TOKEN in "$*"
do
   echo $TOKEN
   star_count=$(($star_count+1))
done

echo "There are $star_count elements in \$*"

for TOKEN in "$@"
do
   echo $TOKEN
   at_count=$(($at_count+1))
done

echo "There are $at_count elements in \$@"


exit 0