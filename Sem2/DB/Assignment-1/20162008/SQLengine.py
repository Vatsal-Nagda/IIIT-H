import csv
import sys
import sqlparse
import re
from collections import OrderedDict
from ReadMeta import readMetadata
from validateQuery import validate
from ReadCSV import ReadCSV_data
from ColumnProjection import cols_proj
from ColumnProjection import remove_dup
from ColumnProjection import print_tuples
from ColumnProjection import print_agg
from WhereProcessing import where_clause
from ResultSchema import result_schema

if __name__ == "__main__":
	Schema_dictionary = {}
	readMetadata(Schema_dictionary)		#Schema_dictionary has the schema for each table as its members with table name as key
	#print Schema_dictionary
	distinct=0
	others=-1
	flag=0
	validFuncs=['max','MAX','min','MIN','avg','AVG','sum','SUM']

	query=validate(sys.argv[1]);

	if query.count('distinct') > 1 or query.count('DISTINCT') > 1:
		print "ERROR !!! MULTPIPLE DISTINCT STATEMENTS !"
		sys.exit(0)
	#print "Query:\t",query		

	if query[1] == 'distinct':
			distinct=1
	else:
		for i in xrange(len(validFuncs)):
			if query[1] == validFuncs[i]:
				others = i
				flag=1
				break
	
	# from_syntax=query[2+distinct+flag]
	# print from_syntax
	# if from_syntax != 'from' or from_syntax != 'FROM':
	# 	print "ERROR !!! Syntax of From wrong"
	# 	sys.exit(0)

	if distinct == 1:
		#columns = query[1+distinct+flag].split('(')
		if '(' in query[1+distinct+flag] or ')' in query[1+distinct+flag]:
			if ',' in query[1+distinct+flag]:
				print "ERROR !!! SYNTAX ERROR DISTINCT"
				sys.exit(0)


	from_tables = query[3+distinct+flag].split(',')
	amb=[]
	for item in from_tables:					
		if Schema_dictionary.has_key(item) == False:
			print "ERROR !!! TABLE NON EXISTANT"
			sys.exit(0)
		else:
			 temp=[]
			 temp = Schema_dictionary[item]
			 for x in temp:
			 	amb.append(x)

	columns = query[1+distinct+flag].split(',')
	for x in columns:
		if x !='*':
			if amb.count(x) > 1:
				print "ERROR !!! AMBIGOUS COLUMN !"
				sys.exit(0)
			# elif x not in amb:
			# 	print "ERROR !!! No such COLUMN !"
			# 	sys.exit(0)

	#print "From Tables:\t",from_tables
	
	result=[]
	result =  result_schema(Schema_dictionary, from_tables)	#add a result schema for the cross product of all tables in From clause
	#print "OBTAINED THE RESULT TO BE PROJECTED"
	#print result

	for item in query:
		if 'where' in item:				#where clause present
			result = where_clause(item,result,Schema_dictionary,from_tables)
			break


	result = cols_proj(Schema_dictionary,query[flag+distinct+1],query[flag+distinct+3],result,others,from_tables)		#Call with schema and tables, cols  to be projected from result

	if distinct==1:
	#	print "inside distinct removal clause"
		result = remove_dup(result)

	if others >= 0:
		print_agg(result)
	else:
		print_tuples(result)