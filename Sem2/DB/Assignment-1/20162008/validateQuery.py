import sys
import re
import sqlparse

def validate(s):	
	query=[]
	state =1 

	for y in sqlparse.parse(s):
		state=1									#deonte the state of the query processsed
		flag=False								#to denote the presence of distinct clause

		for literal in y.tokens:
			literal = str(literal).strip()
			#print literal
			if not literal == '':
				query.append(literal)
				if state == 1 and (literal != 'select'): #or literal != 'SELECT'):
					print "ERROR !!! in the syntax of SELECT"
					sys.exit(0)
				elif state == 2 and (literal==  'distinct' ):#or literal=='DISTINCT'):
					flag = True
					#print "distinct clause found"
				state +=1

	return query