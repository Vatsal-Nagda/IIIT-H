#include <stdio.h>
#include <math.h>

int isPrime(int n){
	int i;
	if(n%2 == 0){
		//printf("%d not a prime\n",n );
		return 0;
	}
	int len = sqrt(n);
	for(i=3;i <= len; i+=2){
		if(n % i == 0){
			//printf("%d not a prime\n",n );
			return 0;
		}
	}

		//printf("%d is a prime number",n);
		return 1;
}


int main(){
	int i,j,t,n;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d",&n);

		for(j=3;j<=(n/2);j++){
			if(isPrime(j) && isPrime(n-j)){
				printf("%d %d\n",j,n-j);
				break;
			}
		}
		if(j > n/2)
			printf("-1\n");

	}

	return 0;
}