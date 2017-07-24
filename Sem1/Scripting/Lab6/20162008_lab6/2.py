import sys 

file_in = open('Quotes.txt','r')

for line in file_in:
	hashval={}
	hashlist=[]
	final=[]
	for words in line.split():
		res=""
		for c in words:
			if c!='.' and c!=',' and c!='!':
				res+=c
		if(hashval.has_key(res)):
			hashval[res]+=1
		else:
			hashval[res] =1

		if( res not in hashlist):
			hashlist.append(res)

	for items in hashlist:
		final.append('<'+items+':'+str(hashval[items])+'>')

	for items in range(len(final)-1):
		sys.stdout.write(final[items]+';')
	sys.stdout.write(final[len(final)-1]+'\n')

