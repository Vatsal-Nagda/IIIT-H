import sys
import csv
import re

def printvar(var):
	s=""
	for i in var:
		s=s+str(i)+" "+str(var[i])+" "
	print s
	return

def doMath(op, op1, op2):
    if op == "*":
        return op1 * op2
    elif op == "/":
        return op1 / op2
    elif op == "+":
        return op1 + op2
    else:
        return op1 - op2

def evaluate(operation,tempvar):
	
	return

def main():
	k=int(sys.argv[1])

	results=[]
	t=[]
	file=open("input.txt","r")
	for line in file:
		if line == "\n":
			results.append(t)
			t=[]
		else:
			line=line.strip()
			t.append(line)
	results.append(t)

	i=0
	t=results[0][0].split()
	# print t
	var={}
	varf={}
	while i < len(t):
		var[t[i]]=t[i+1]
		varf[t[i]]=t[i+1]
		i=i+2

	results.pop(0)

	i=0
	f=0
	tempvar={}

	while i < len(results):
		tempvar[i]={}
		i=i+1

	
	while f==0:
		# print "here"
		f=1
		i=0
		while i < len(results):
			trans=results[i]
			j=0
			while j<k and len(trans)>0:
				operation=trans[0]
				# print "cmd",operation
				trans.pop(0)

				if operation.startswith("T"):
					print "<T"+str(i+1)+", start>"
					printvar(var)

				elif operation.startswith("read"):
					cmd=operation[operation.find("(")+1:operation.find(")")]
					x=cmd.split(",")[0]
					y=cmd.split(",")[1]
					tempvar[i][y]=varf[x]
					j=j+1

				elif operation.startswith("write"):
					cmd=operation[operation.find("(")+1:operation.find(")")]
					x=cmd.split(",")[0]
					y=cmd.split(",")[1]
					print "<T"+str(i+1)+", "+x+", "+str(var[x])+">"
					var[x]=tempvar[i][y]
					# print y,tempvar[i][y]
					printvar(var)			
					j=j+1

				elif operation.startswith("output"):
					x=operation[operation.find("(")+1:operation.find(")")]
					varf[x]=var[x]
					j=j+1

				else:
					a=operation.split("=")[0].strip()
					if a[-1] == ":":
						a=a[:-1]
					b=operation.split("=")[1].strip()

					s=""
					for token in b:
						# print token
						if token in ["+","-","*","/"]:
							op=token
							s=s.strip()
							if s in tempvar[i]:
								op1=int(tempvar[i][s])
							else:
								op1=int(s)
							s=""
						else:
							s=s+token
					s=s.strip()
					if s in tempvar[i]:
						op2=int(tempvar[i][s])
					else:
						op2=int(s)
					
						# print op1,op,op2
					a=a.strip()
					tempvar[i][a]=doMath(op,op1,op2)
					j=j+1
					# print tempvar[i]

			if len(trans) == 0:
				print "<T"+str(i+1)+", commit>"
				printvar(var)

			if len(results[i]) > 0:
				f=0
			i=i+1

if __name__ == '__main__':
	main()
