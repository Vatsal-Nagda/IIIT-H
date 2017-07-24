#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(long long arr[],long long low,long long mid,long long high){
	long long i=low,j=mid+1,k=0;
	long long temp [high-low+1];

	while(i<=mid && j<= high){
		if(arr[i] < arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while(i <= mid)
		temp[k++] = arr[i++];

	while(j <= high)
		temp[k++] = arr[j++];


	for(i=low,k=0;i<=high;i++,k++)
		arr[i] = temp[k];

}

void mergeSort(long long arr[],long long low,long long high){
	if(low < high){
		long long mid = low +(high-low)/2;

		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1,high);
		merge(arr,low,mid,high);
	}
}

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

	free(primes);
}


int main(){
	long long i,j,l,n,t,k=0;
	scanf("%lld",&t);


		/*int primes [1000001];
		get_primes(primes,1000001);
*/
	for(i=0;i<t;i++){
		scanf("%lld",&n);

		k=0;

		long long primes_factors[2000]={-1};
		long long num,count=0;

		//int p=2;

		for(j=0;j<n;j++){
			scanf("%lld",&num);
			//temp = num;
			/*if(num % 2 == 0)
				primes_factors[k++] =2;*/

			while(num % 2 == 0 )
			{
				num = num/2;
				primes_factors[k++]=2;
			}

			for(l=3; l <= sqrt(num) ;l+=2){
				
				/* if(num % l == 0)
				 	primes_factors[k++] =l;
*/

				while(num % l == 0 )
				{
					primes_factors[k++] =l;
					num = num/l;
				}
					
			}

			if(num > 2)
				primes_factors[k++] =num;				

		/*	printf("Primes for %lld are :\n",temp);

			for(l=0;l<k;l++)
				printf("%lld ",primes_factors[l] );

			printf("\n");*/
		}


		/*for(l=0;l<k;l++)
				printf("%lld ",primes_factors[l] );*/

		mergeSort(primes_factors,0,k-1);
		//printf("\n");

		/*for(l=0;l<k;l++)
				printf("%lld ",primes_factors[l] );
*/
		long long p_u=1;

		count++;

		for(l=1; p_u <=count && l<k;l++){
			if(primes_factors[l] != primes_factors[l-1]){
				count++;
				primes_factors[p_u++] = primes_factors[l];
			}
		}

		printf("%lld\n",count );
		for(l=0;l<count;l++)
			printf("%lld\n",primes_factors[l] );

	}


	return 0;
}