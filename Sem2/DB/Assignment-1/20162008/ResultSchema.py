import csv
import sys
import re
from ReadCSV import ReadCSV_data

def result_schema(Schema_dictionary,from_tables):
	tableName = from_tables[0]+'.csv'
	result = ReadCSV_data(tableName)
	result_schema=[]
	for items in Schema_dictionary[from_tables[0]]:			#create a resultant schema and save it
			result_schema.append(from_tables[0]+'.'+items)


	for i in xrange(1,len(from_tables)):
	#	print len(Schema_dictionary[from_tables[i]])
		for items in Schema_dictionary[from_tables[i]]:			#create a resultant schema and save it
			result_schema.append(from_tables[i]+'.'+items)

		tableName = from_tables[i]+'.csv'
		table = ReadCSV_data(tableName)
		temp=[]
		for tuple_res in result:
			for tuple_table in table:
				temp.append(tuple_res+tuple_table)
		result = temp
	
	Schema_dictionary['result'] = result_schema
	#print 'before returning the tuples in resultant schema'
	#print result
	return result