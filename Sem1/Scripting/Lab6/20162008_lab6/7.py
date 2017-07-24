import sys 

n=sys.argv[1]
n=int(n)
c=sys.argv[2]
c=int(c)

time = raw_input()
time = [ int(i) for i in time.split()]

count=1;
prev=time[0]
for i in range(1,n):
	if time[i]-prev <= c:
		#print'added',time[i],'to list'
		count+=1
	else:
		count=1
	prev=time[i]

print count
