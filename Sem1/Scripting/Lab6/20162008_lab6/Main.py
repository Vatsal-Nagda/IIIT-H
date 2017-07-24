import sys
import Primes

n=sys.argv[1];
n= int(n);
func=sys.argv[2];

if(func == "countOddPrimes"):
	count = Primes.countOddPrimes(n);
	print(count)
else:
	result = []
	result=Primes.getOddPrimes(n)
	result.sort()
	result.reverse();

	for ele in range(len(result)-1):
		sys.stdout.write(str(result[ele])+',')
	sys.stdout.write(str(result[len(result) -1 ])+'\n')