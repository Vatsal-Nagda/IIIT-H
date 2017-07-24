#!/bin/bash

#String handling with expr

echo -e "Enter any string of length >3 \c"
read str

echo `expr "$str" : '.*'`
#prints the size of str


echo `expr "$str" : '\(..\).*'`
#extracts the last 2 chars from str

exit 0 