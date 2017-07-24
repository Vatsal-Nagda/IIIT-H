#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void get_primes(int prm[], long long sqr_rt){

	int i,j;

	int *primes = (int *)malloc(sizeof(int) *1000001);

	for(i=0;i<=sqr_rt;i++){
		primes[i] = 0;
		prm[i] = 0;
	}

	primes[0] = primes[1] = 1;
	for(i=2;i*i<=sqr_rt;i++){

		for(j=2*i;j<=sqr_rt;j+=i){
			primes[j] =1;
		}

	}

	j=0;
	//printf("Printing primes till root(n)\n");
	for(i=0;i<=sqr_rt;i++){
		if(primes[i] == 0){
			prm[j++] = i;
			//printf("%d \t",prm[j++] );
		}
	}	

	free(primes);
}

int main(){

	long long HIGH ;
	scanf("%lld",&HIGH);

	int primes [1000001];

	get_primes(primes,1000001);

	int i;
	for(i=0;i<10000;i++){
		printf("%d  ", primes[i]);
	}

	return 0;
}