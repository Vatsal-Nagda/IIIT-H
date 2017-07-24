import sys

n=sys.argv[1]
n = int(n)

for i in range(1,n+1):
	for j in range(n-i,-1,-1):
		print'',
	#for k in range(1,2*i):
	k = 2*i-1
	print'+'*k
	##print' '

for i in range(n-1,0,-1):
	for j in range(n-i,-1,-1):
		print'',
	k = 2*i-1
	print'+'*k
	#print' '
