#!/bin/bash

# Doing integer arithmetic using the 'let'  and the ((...)) constructs
# 'let' is a less complex version of 'expr' 
# 'let' requires that there be NO space anywhere in the expression    e.g. "let y= $x + 2" is error. 
# Everything in ((...)) is treated as quoted and it allows C-style manipulation of variables

let X=5                       

let X-=2

let X++

echo "X = $X"

let Y=X*10

let Y--

echo "Y = $Y"



echo "========== ((...)) ================="

(( a=5 ))			# C-style, setting a value 

(( a++ ))

echo "a = $a"

echo $((20+30))                     # expr 20 + 30

echo $(($X + 4))                    # expr $x + 4 

echo "==============================="

exit 0