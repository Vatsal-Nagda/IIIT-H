#!/bin/bash

# How to take input from User

echo -e "Enter the word to be searched : \c"
read word
echo -e "Enter the file name : \c"
read fileName

grep $word $fileName