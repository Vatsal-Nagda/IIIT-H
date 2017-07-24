import sys

f_read = open('corpus.txt','r')
line_list = f_read.readlines()

list_remove = ['the', 'an', 'a', 'has', 'to', 'of', 'as', 'is', 'in', 'if']

list_final=[]

for i in range(len(line_list)):
	list_final.extend(line_list[i].split(' '))

print
print "checking for the peices now"

for piece in list_remove:
	v = list_final.count(piece)
	if v > 0:
		print "count of",piece,"is",v
	else:
		print "count of",piece,"is 0"
