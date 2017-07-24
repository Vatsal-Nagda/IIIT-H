
import collections
import string

f_r = open('tweets.txt','r')
str1 = f_r.read()

emoticons = [':)',':-)',':D',':(',':-|',':\'(',':-\'(',':o',':-o','<3',':x']
remove = list(string.punctuation)

freq={}

for emo in emoticons:
	c = str1.count(emo)
	if c not in freq and c > 0:
		freq[emo] = c
	str1 = str1.replace(emo,'')

for r in remove:
	str1=str1.replace(r,'')

for wrd in str1.split():
	c = str1.count(wrd)
	if c not in freq:
		freq[wrd]=c

f_write = open('words.txt','w')

for key in sorted(freq,key=freq.get,reverse=True):
	f_write.write(str(key)+" : "+str(freq[key])+"\n")
	#print key,':',freq[key]
f_write.close()
