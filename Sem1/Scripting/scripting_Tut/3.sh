#!/bin/bash

# How to know the exit status of last command

echo -e "Enter the word to be searched : \c"
read word
echo -e "Enter the file name : \c"
read fileName

grep $word $fileName

echo $?

# if exit status is 0 then everything went fine
# if exit status is > 0 then something went wrong