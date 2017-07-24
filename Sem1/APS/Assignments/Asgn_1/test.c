#include <stdio.h>

unsigned int dig(int diff){
	unsigned int i=1,j=0;

	while(i < diff){
		j++;
		i = i*2;
	}

	return j;
}


int main(){

	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		unsigned int a,b;
		scanf("%u%u",&a,&b);

		unsigned int diff = b-a +1;
		unsigned int digits = dig(diff);
		//printf("The diff is :%d\t Digits required are:%d\n",diff,digits );
		printf("%u\n",(b>>digits)<<digits);
		//printf("%u\n",(b&(b<<digits)));
	}

	return 0;
}