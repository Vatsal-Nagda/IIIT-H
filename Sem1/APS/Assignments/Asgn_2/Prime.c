#include <stdio.h>
#include <math.h>

int main(){
	int i;
	long int n;
	scanf("%ld",&n);
	printf("The number you entered is :%ld\n",n );
	int arr[n];

	if(n%2 == 0){
		printf("%ld is not a prime number",n);
		return 0;
	}

	for(i=3;i <= sqrt(n); i+=2){
		if(n % i == 0){
			printf("%ld is not a prime number",n);
			break;
		}
	}

	if(i > sqrt(n))
		printf("%ld is a prime number",n);

	return 0;
}