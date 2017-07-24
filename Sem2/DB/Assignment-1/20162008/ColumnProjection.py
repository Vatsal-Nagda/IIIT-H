import csv
import sys
import re
import numpy

def cols_proj(Schema_dictionary,columns,tables,result,others,from_tables):		# Call with schema and tables, cols  to be projected from result
	columns = columns.replace('(',"")
	columns = columns.replace(')',"")
	columns = columns.strip().split(',')
	answer=[]															
	temp=[]
	#print columns
	if columns[0] == '*':									# Project all the columns of the resultant table
		for i in  xrange(len(Schema_dictionary['result'])):
			temp.append(str(Schema_dictionary['result'][i]))
		answer.append(temp)	
		for row in result:
			answer.append(row)
			
	else:
	#	print "Not select *"
		#print len(columns)
		for i in xrange(len(columns)):
	#		print columns[i]
			if columns[i] not in Schema_dictionary['result']:
			#	print "column name in fromat of original table"
				#for key,value in Schema_dictionary.iteritems():
				for key in from_tables:
					if columns[i] in Schema_dictionary[key]:
						columns[i] = key+'.'+columns[i]
						break
			#print columns[i]
		col_num=[]
		for i in xrange(len(columns)):													# prints the column headings
			if Schema_dictionary['result'].index(columns[i]) >= 0:
				col_num.append(Schema_dictionary['result'].index(columns[i]))
		#print col_num		
		temp=[]
		for i in xrange(len(col_num)):												#Actual tuples are printed
			temp.append(str(Schema_dictionary['result'][col_num[i]]))
		
		answer.append(temp)

		for row in result:
			#answer.append(row)
			temp=[]
			for i in xrange(len(col_num)):
				temp.append(str(row[col_num[i]]))
			answer.append(temp)
		
		#print len(answer)
		if others >= 0:			
			a = numpy.array(answer[1:],dtype=int)						
			#print "in agg",answer
			head=""
			validFuncs=['max','MAX','min','MIN','avg','AVG']
			if others == 0 or others == 1:								
				val = a[:,0].max()
				head = 'MAX ('+answer[0][0]+')'
				#print a[:,0].max()
			elif others == 2 or others == 3:
				val = a[:,0].min()
				head = 'MIN ('+answer[0][0]+')'
				# print a[:,0].min()
			elif others == 4 or others == 5:
				val = a[:,0].mean()
				head = 'AVG ('+answer[0][0]+')'
			elif others == 6 or others == 7:
				val = a[:,0].sum()
				head = 'SUM ('+answer[0][0]+')'
				# print a[:,0].mean()
			answer=[]
			answer.append(head)
			answer.append(val)

	return answer

def remove_dup(result):
	non_redundant=[]
	for tuples in result:
		#print 'O.G.',tuples
		if tuples not in non_redundant:
			non_redundant.append(tuples)
	#		print tuples
	#print non_redundant
	return non_redundant

def print_tuples(projected_columns):
	for tuples in projected_columns:
		for i in xrange(len(tuples)-1):
			sys.stdout.write(str(tuples[i])+',')	
		sys.stdout.write(str(tuples[-1])+'\n')	
	
def print_agg(agg_columns):
#	print agg_columns
	for tuples in agg_columns:
		print tuples
	