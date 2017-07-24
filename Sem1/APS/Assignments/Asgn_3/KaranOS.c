#include <stdio.h>

int main(){
	int i,N,P,K,t,lucky=0,current_size;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		lucky=0;
		scanf("%d%d%d",&N,&P,&K);

		for(current_size=2;current_size<=N;current_size++){
			lucky = ( lucky + K )%current_size;
		}

		lucky = (lucky+P-1)%(current_size-1);
		lucky += 1;
		printf("%d\n",lucky );

	}

	return 0;
}