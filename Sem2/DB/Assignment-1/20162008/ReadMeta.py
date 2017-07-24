import csv
import sys
import re

def readMetadata(Schema_dictionary):
	f = open('metadata.txt','r')
	flag = False				#to check if a new table has come or not
	tableName=""	
	for row in f:
		#print row.strip()
		if row.strip() == '<begin_table>':
			flag = True
			continue
		if flag == True:			# a new table has come
			flag = False
			tableName=row.strip()
			Schema_dictionary[tableName]=[]
			continue
		if row.strip() != '<end_table>':
			Schema_dictionary[tableName].append(row.strip())
	return Schema_dictionary