import sys
import glob

flag =0
visited = []
adj = {}

def DFS(node ):
	global flag
	visited.append(node)
	if node in adj:
		for items in adj[node]:
			if items in visited:
				flag = 1
			else:
				DFS(items)


html_files1 = []
html_files2 = []

graph= []

names=['HTMLPages1/','HTMLPages2/']

op1= ['<!DOCTYPE html>\n','<html>\n','<body>\n','<h1>Output</h1>\n','<p>Cycle Present</p>\n','</body>\n','</html>']
op2= ['<!DOCTYPE html>\n','<html>\n','<body>\n','<h1>Output</h1>\n','<p>Cycle Not Present</p>\n','</body>\n','</html>']

for name in names:
	for file_name in sorted(glob.glob(name+'*.html')):
		f_read = open(file_name,'r')
		html_files1 = f_read.readlines()
		temp = []
		for line in html_files1:
			s = line		
			ind = s.find('a href="')
			if ind != -1:
				s = s[ind+8:]
				ind = s.find('"') 
				s = s[0:ind]
				if s not in temp:
					temp.append(s)
		adj[file_name[11:]] = temp

	DFS(adj.keys()[0])

	if flag == 1:
		f_write = open(name+'output1.html','w')
		for items in op1:
			f_write.write(items)
		f_write.close()
	else:
		f_write = open(name+'output2.html','w')
		for items in op2:
			f_write.write(items)
		f_write.close()
	flag =0
	visited = []
	adj = {}
