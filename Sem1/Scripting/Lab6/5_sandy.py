import sys

string=sys.argv[1]
key=sys.argv[2]
cipher=""
k=0
for s in string:
	cipher+=key[k%len(key)]
	k=k+1

k=0
encrypted_text=""
for s in string:
	encrypted_text+=chr(((ord(string[k])+ord(cipher[k]))%26)+65)
	k=k+1
print encrypted_text
