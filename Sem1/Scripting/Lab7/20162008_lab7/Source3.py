#!/usr/bin/python

Name ="Nagda"
try:
	assert(Name=="Vatsal")
except AssertionError, e:
	print type(e)

else:
 print Name
