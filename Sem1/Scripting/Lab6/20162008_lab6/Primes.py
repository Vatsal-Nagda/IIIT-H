#!/bin/usr/python

def countOddPrimes(n):
	count=0;
	for i in range(1,n+1):
		if i == 1 or i % 2 == 0:
			pass
		else:
			j=3
			nby2= i/2;
			while( j <= nby2):
				if i%j != 0:
					j = j+2 
				else:
					break;
			if j <= nby2 :
				pass
			else:
				if i%2 !=0:
					count+=1
	return count

def getOddPrimes(n):
	result =[]
	for i in range(1,n+1):
		if i == 1 or i % 2 == 0:
			pass
		else:
			j=3
			nby2= i/2;
			while( j <= nby2):
				if i%j != 0:
					j = j+2 
				else:
					break;
			if j <= nby2 :
				pass
			else:
				if i%2 !=0:
					result.append(i)
	return	result
