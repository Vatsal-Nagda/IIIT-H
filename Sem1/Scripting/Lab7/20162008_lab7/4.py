import sys

f = open('urls.txt')
hash_map={}

for lines in f:
	lines = lines[lines.index('//')+2:]
	if lines.find('/') != -1:
		lines = lines[0:lines.index('/')]
	else:
		lines = lines[0:lines.index("\n")]
	#print lines

	if lines not in hash_map:
		hash_map[lines] = 1
	else:
		hash_map[lines] += 1

#print hash_map

key_list=[]
val=[]
for key in sorted(hash_map,key=hash_map.get,reverse=True):
	key_list.append(key)
	val.append(hash_map[key])
	sys.stdout.write(key+" : "+str(hash_map[key])+"\n")
	
prev_start=0
prev_end = 0

i=1
temp =[]

for i in range(1,len(val)):
	if val[i] == val[prev_end]:
		prev_end += 1
	else:
		temp.append(sorted(key_list[prev_start:prev_end+1]))
#		print sorted(key_list[prev_start:prev_end+1])
		prev_start , prev_end = prev_end+1,prev_end+1 
		#print i,prev_start,prev_end

temp.append(sorted(key_list[prev_start:prev_end+1]))

print '\nMost frequently visited URLs :\n'
for item in temp:
	#sys.stdout.write(item+" : "+str(hash_map[item])+"\n")
	for i in item:
		if hash_map[i] == val[0]:
			sys.stdout.write(i+"\n")