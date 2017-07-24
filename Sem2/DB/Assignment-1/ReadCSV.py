import csv
import sys
import re

def ReadCSV_data(tableName):
	table=[]
	f= open(tableName,'rb')
	reader = csv.reader(f)
	for row in reader:
		table.append(row)
		#print row
	return table
