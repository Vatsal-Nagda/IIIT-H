import sys

f_read = open('dataset.csv','r')

line_list = f_read.readlines()

for i in range(len(line_list)):
	line_list[i] = line_list[i].split(',')

#print line_list

num_feild=len(line_list[0])

list_count = [None]*num_feild
count = [0]*num_feild

for items in line_list:
	for i in range(len(items)):
		items[i] = items[i].strip()
		if items[i] == 'NA':
			count[i]+=1
			pass
		else:
			try:
				v=float(items[i])
			except ValueError:
				#not a float means it is a string
				if list_count[i] == None:
					list_count[i] = {}
					list_count[i][items[i]] = 1
				else:
					if items[i] in list_count[i]:
						list_count[i][items[i]] += 1
					else:
						list_count[i][items[i]] = 1
				pass
			else:
				if list_count[i] == None:
					list_count[i] = v
				else:
					list_count[i] += v

for i in range(len(list_count)):
	try:
		v= float(list_count[i])
	except TypeError:
		list_count[i] = sorted(list_count[i],key=list_count[i].get,reverse=True)[0]
		pass
	else:
		div = len(line_list)-count[i]
		list_count[i] = round((list_count[i]/div),1)


#print list_count
f_write = open('new_dataset.csv','w')

for items in line_list:
	for i in range(len(items)):
		if items[i] == 'NA':
			items[i] = list_count[i];

for line in line_list:
		for inp in range(len(line)-1):
			f_write.write(str(line[inp])+',')
		f_write.write(str(line[-1])+"\n")	
#print line_list