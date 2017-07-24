#!/usr/bin/python

a = 7
b = 0

try:
	c = a/b
except ZeroDivisionError,e:
	print type(e)
else:
	print c
 