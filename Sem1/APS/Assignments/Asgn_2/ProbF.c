#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>

void get_primes(int primes[],int prm[], long long sqr_rt){

	int i,j;

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

}


int main(){
	long long LOW,HIGH;
	long long j,count=0;
	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%lld %lld",&LOW,&HIGH);
		count =0;

		int arr[HIGH-LOW+2];

		for(j=0;j<=HIGH-LOW+1;j++)
			arr[j] =0;

		long long sqr_rt = sqrt(HIGH);
		int primes [sqr_rt+1];
		int prm [sqr_rt+1];

		get_primes(prm,primes,sqr_rt);
		//memset(arr,0,sizeof(arr));

/*		printf("\nprinting the array \n");

		for(j=1;j<=HIGH-LOW+1;j++)
			printf("%d  ",arr[j] );*/

		/*for(j=0;primes[j]!=0;j++){
			printf("%d ",primes[j] );
		}*/	

		int k=0;

		for(j=primes[k];j*j<=HIGH && primes[k]!=0;j=primes[++k]){

			//printf("j: %lld ", j);
			//scanf("%lld",&j);
			long long chck = (LOW/j)*j;

			if(chck < LOW)
				chck += j;
			if(chck == j)
				chck += j;

			//printf("\nLOW %ld\tHIGH %ld\tchck %ld\n",LOW,HIGH,chck );

			//printf("Before while for num :%d\n",j);
			while(chck <= HIGH){
				arr[chck-LOW+1] = 1;				
			//	printf("chck :%ld arr[] :%ld\t",chck,chck-LOW+1 );
				chck += j;
			}
			//printf("Outside while for num :%d\n",j);

		}
	/*	printf("\nprinting the array \n");

		for(j=1;j<=HIGH-LOW+1;j++)
			printf("%d  ",arr[j] );
		printf("\n");
*/
		for(j=1;j<=HIGH-LOW+1;j++){
			if(arr[j] !=1){
				count++;
			//	printf("%d \t",LOW+j-1/*,arr[j]*/);
			}
		}

		if(LOW == 1)
			count--;

		printf("%lld\n",count );
	}


	return 0;
}