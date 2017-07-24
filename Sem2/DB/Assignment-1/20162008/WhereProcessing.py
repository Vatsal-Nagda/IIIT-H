import csv
import sys
import re

def where_clause(wherestring,result,Schema_dictionary,from_tables):
	#print wherestring
	Whereclause = re.match(r"where (.*)",wherestring).group(1)
	#print Whereclause

	matchObj = re.match( r'(.*) (or|OR|and|AND) (.*)', Whereclause, re.M|re.I)
	first_condition=""
	second_condition = ""
	if matchObj:
	#	print "AND / OR present"
		first_condition = matchObj.group(1)
		optr1=""
		if first_condition.find('>=') >= 0:
			optr1 = '>='
		elif first_condition.find('<=') >= 0:
			optr1 = '<='
		elif first_condition.find('!=') >= 0:
			optr1 = '!='
		elif first_condition.find('>') >= 0:
			optr1 = '>'
		elif first_condition.find('<') >= 0:
			optr1 = '<'
		elif first_condition.find('=') >= 0:
			optr1 = '='

		joining_condition = matchObj.group(2)
	
		second_condition = matchObj.group(3)
		optr2=""
		if second_condition.find('>=') >= 0:
			optr2 = '>='
		elif second_condition.find('<=') >= 0:
			optr2 = '<='
		elif second_condition.find('!=') >= 0:
			optr2 = '!='
		elif second_condition.find('>') >= 0:
			optr2 = '>'
		elif second_condition.find('<') >= 0:
			optr2 = '<'
		elif second_condition.find('=') >= 0:
			optr2 = '='
	
		first_tables = re.split('[<><=>=!==]',first_condition)
		second_tables = re.split('[<><=>=!==]',second_condition)
		first_tables = filter(None,first_tables)
		second_tables = filter(None,second_tables)
	#	print first_tables,second_tables,joining_condition
		second_tables = [inner.strip() for inner in second_tables]
		first_tables = [inner.strip() for inner in first_tables]

		flag = False
	 	for i in xrange(len(first_tables)):
		#		print columns[i]
			if first_tables[i].isdigit() == False:
				if first_tables[i] not in Schema_dictionary['result']:	#columns name and not a no.
				#	print "column name in fromat of original table"
					#for key,value in Schema_dictionary.iteritems():
					for key in from_tables:
						if first_tables[i] in Schema_dictionary[key]:
							first_tables[i] = key+'.'+first_tables[i]
							# flag = True
							break
				# else:
				# 	flag =True 									# check if column is valid or not
	#	print first_tables



		# if flag == False:	
		# 	print "column name not found"
			#to do for handling wrong column name


		col_num=[]
		for i in xrange(len(first_tables)):													# prints the column headings
			if first_tables[i].isdigit() == False:
				if Schema_dictionary['result'].index(first_tables[i]) >= 0:
					col_num.append(Schema_dictionary['result'].index(first_tables[i]))
	#	print col_num


		flag = False
		for i in xrange(len(second_tables)):
			if second_tables[i].isdigit() == False:
		#		print columns[i]
				if second_tables[i] not in Schema_dictionary['result']:	#columns name and not a no.
				#	print "column name in fromat of original table"
					for key,value in Schema_dictionary.iteritems():
						if second_tables[i] in Schema_dictionary[key]:
							second_tables[i] = key+'.'+second_tables[i]
							# flag = True
							break
				# else:
				# 	flag = True
	#	print second_tables
		# if flag == False:	
		# 	print "column name not found"
		# 	#to do for handling wrong column name

		col_num2=[]
		for i in xrange(len(second_tables)):													# prints the column headings
			if second_tables[i].isdigit() == False:
				if Schema_dictionary['result'].index(second_tables[i]) >= 0:
					col_num2.append(Schema_dictionary['result'].index(second_tables[i]))
		#print col_num2

		result = executeANDOR(result,col_num,col_num2,Schema_dictionary,first_tables,second_tables,optr1,optr2,joining_condition)



	else:															# NO AND / OR pressent in clause
	#	print "AND / OR  NOT present"
		optr=""
		if Whereclause.find('>=') >= 0:
			optr = '>='
		elif Whereclause.find('<=') >= 0:
			optr = '<='
		elif Whereclause.find('!=') >= 0:
			optr = '!='
		elif Whereclause.find('>') >= 0:
			optr = '>'
		elif Whereclause.find('<') >= 0:
			optr = '<'
		elif Whereclause.find('=') >= 0:
			optr = '='

		first_tables = re.split('[<><=>=!==]',Whereclause)
		first_tables = filter(None,first_tables)
		first_tables = [inner.strip() for inner in first_tables]
		print first_tables
 		print from_tables
		flag = False
		print Schema_dictionary['result']
	 	for i in xrange(len(first_tables)):
		#		print columns[i]
			if first_tables[i].isdigit() == False:
				if first_tables[i] not in Schema_dictionary['result']:	#columns name and not a no.
				#	print "column name in fromat of original table"
					#for key,value in Schema_dictionary.iteritems():
					for key in from_tables:
						if first_tables[i] in Schema_dictionary[key]:
							first_tables[i] = key+'.'+first_tables[i]
							# flag = True
							break
				# else:
				# 	flag =True 									# check if column is valid or not
		print 'After naming columns',first_tables



		# if flag == False:	
		# 	print "column name not found"
		# 	#to do for handling wrong column name


		col_num=[]
		for i in xrange(len(first_tables)):													# prints the column headings
			if first_tables[i].isdigit() == False:
				if Schema_dictionary['result'].index(first_tables[i]) >= 0:
					col_num.append(Schema_dictionary['result'].index(first_tables[i]))
	#	print col_num

		result = execute(result,col_num,Schema_dictionary,first_tables,optr)

	return result



def execute(result,col_index,Schema_dictionary,tables,optr):
	answer=[]
	if len (col_index) == 1:				# comparision with a number
		value = Schema_dictionary['result'][col_index[0]]
	#	print "value",value	
		index = tables.index(value)
	#	print "value",value	
		value = tables[1-index]
		#print "value",value	
		#print "In where clause single case"
		#print optr
		for row in result:
			#print row[index]
			if optr == '>=':
				if int(row[index]) >= int(value):
					answer.append(row)
			elif optr == '<=':
				if int(row[index]) <= int(value):
					answer.append(row)
			elif optr == '>':
				if int(row[index]) > int(value):
					answer.append(row)
			elif optr == '<':
				if int(row[index]) < int(value):
					answer.append(row)
			elif optr == '!=':
				if int(row[index]) != int(value):
					answer.append(row)
			elif optr == '=':
				if int(row[index]) == int(value):
					answer.append(row)
		return answer
	else:									#join to be used
		#print "Inside where join process ",tables
		#print col_index[0],col_index[1]
		#print optr
		for row in result:
			#print row[col_index[0]],row[col_index[1]]
			if optr == '>=':
				if int(row[col_index[0]]) >= int(row[col_index[1]]):
					answer.append(row)
			elif optr == '<=':
				if int(row[col_index[0]]) <= int(row[col_index[1]]):
					answer.append(row)
			elif optr == '>':
				if int(row[col_index[0]]) > int(row[col_index[1]]):
					answer.append(row)
			elif optr == '<':
				if int(row[col_index[0]]) < int(row[col_index[1]]):
					answer.append(row)
			elif optr == '!=':
				if int(row[col_index[0]]) != int(row[col_index[1]]):
					answer.append(row)
			elif optr == '=':
				if int(row[col_index[0]]) == int(row[col_index[1]]):
					answer.append(row)


		return answer

def executeANDOR(result,col_index1,col_index2,Schema_dictionary,first_tables,second_tables,optr1,optr2,joining_condition):
	answer=[]
	#print joining_condition
	#print col_index1[0],col_index1[1],col_index2[0]#,col_index2[1]
	#print optr1,optr2
	for row in result:
		t1 = int(row[col_index1[0]])
		if len(col_index1 ) == 1:		#a vlaue to ve compared
			t2 = int(first_tables[1])
		else:
			t2 = int(row[col_index1[1]])

		p1 = int(row[col_index2[0]])
		if len(col_index2 ) == 1:		#a vlaue to ve compared
			p2 = int(second_tables[1])
		else:
			p2 = int(row[col_index2[1]])


		bool1=False
		bool2=False

		if optr1 == '>=':
			if t1 >= t2:
				bool1=True
		elif optr1 == '<=':
			if t1 <= t2:
				bool1=True
		elif optr1 == '>':
			if t1 > t2:
				bool1=True
		elif optr1 == '<':
			if t1 < t2:
				bool1=True
		elif optr1 == '!=':
			if t1 != t2:
				bool1=True
		elif optr1 == '=':
			if t1 == t2:
				bool1=True

		if optr2 == '>=':
			if p1 >= p2:
				bool2=True
		elif optr2 == '<=':
			if p1 <= p2:
				bool2=True
		elif optr2 == '>':
			if p1 > p2:
				bool2=True
		elif optr2 == '<':
			if p1 < p2:
				bool2=True
		elif optr2 == '!=':
			if p1 != p2:
				bool2=True
		elif optr2 == '=':
			if p1 == p2:
				bool2=True

		if joining_condition == 'and' or joining_condition== 'AND':
			if (bool1 and bool2 ) == True:
				answer.append(row)
		else:
			if (bool1 or bool2 ) == True:
				answer.append(row)
	return answer