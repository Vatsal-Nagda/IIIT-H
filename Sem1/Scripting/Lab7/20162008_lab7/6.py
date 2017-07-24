import sys
import glob

list_lines=[]

for filename in glob.glob('HTMLPages/*.html'):
	f_read = open(filename,'r')
	list_lines.extend(f_read.readlines())	
hash_map ={}

for line in list_lines:
	s = line
	ind = s.find('a href="')
	if ind != -1:
		s = s[ind+8:]
		ind = s.find('"') 
		s = s[0:ind]
		if s in hash_map:
			hash_map[s] += 1
		else:
			hash_map[s] = 1

f_write = open('pageFreq','w')

for key in sorted(hash_map):
	f_write.write(key+"=>"+str(hash_map[key])+"\n")
