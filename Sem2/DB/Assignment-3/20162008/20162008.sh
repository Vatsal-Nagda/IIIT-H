#!/bin/bash 

if [ "$#" -eq 2 ]; then
    python 20162008_1.py $1 $2
fi
if [ "$#" -eq 1 ]; then
	python 20162008_2.py $1 
fi
