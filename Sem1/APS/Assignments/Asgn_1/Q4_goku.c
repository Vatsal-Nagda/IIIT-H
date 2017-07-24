#include <stdio.h>

int main(){
	int i,w;
	scanf("%d",&w);

	for(i=0;i<w;i++){
		//int j=0,flag =0;
		long int start,end,common;
		scanf("%ld%ld",&start,&end);

		common = end;

		while(1){
			if(common<= start)
				break;
			else
				common = common & (common-1); 

		}

		printf("%ld\n",common);
	}

	return  0;
}
