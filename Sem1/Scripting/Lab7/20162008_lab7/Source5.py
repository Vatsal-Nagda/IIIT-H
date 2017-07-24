#!/usr/bin/python

d = {'Name': 'Vatsal','rollno.': '20162008'}

try:
	print d['Age']
	
except KeyError, e:
	print type(e)
