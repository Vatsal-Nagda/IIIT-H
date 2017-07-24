#!/bin/bash

#String comparison operators and if statement


#Below are some string comparison operators
# s1 = s2 string S1==S2
# s1 != s2 string s1 is not equal to s2
# -n stg String stg is not null
# -z stg String stg is null
# stg String stg is assigned and not null
# s1 == s2 string S1=S2(works is korn and Bash shells)


#General structure of if
# if cmd 
# then
# //Do some work
# elif cmd
# then
# //Do some other stuff
# else
# //atleast do something
# fi


x="john cena"

#try removing double quotes from "$x", and invite troble
if [ "$x" = "john cena" ]
	then
	echo "You Can't see me!!!"
fi


y=""

if [ -z "$y" ];	then
	echo "I'm NULL"
fi

if [ "$x" != "$y" ]
	then
	echo "Hum dono hai alag alag"
fi

if [ -z "$x" ]
	then
	echo "I'm NULL"
elif [ "$x" ]
	then
	echo "I'm assigned and not NULL"
fi

# To-Do 
#Read File attributes

exit 0

