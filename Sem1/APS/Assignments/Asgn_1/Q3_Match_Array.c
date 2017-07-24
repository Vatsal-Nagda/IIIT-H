#include <stdio.h>

int main(){

	int n,m,i;
	scanf("%d%d",&n,&m);

	long int arr [n];
	
	for(i=0;i<n;i++){
		scanf("%ld",&arr[i]);
	}

	long int chck,temp;

	scanf("%ld",&chck);

	for(i=1;i<n;i++){
		scanf("%ld",&temp);
	}

	char dir;
	char c;
	int steps;

	scanf("%c",&c);
	int index=0,count=0;

	for(i=0;i<m;i++){
		scanf("%c",&dir);		//direction
		scanf("%c",&c);			//space
		scanf("%d",&steps);		//steps in dir
		scanf("%c",&c);			//space

		if(dir == 'R'){
			index = (index-steps)%n;	
			if(index < 0)
				index = (index+n)% n;
			count++;
		}
		else{
			index = (index+steps)%n;
			count++;
		//	printf("Index after decrement is :%d\n",index);
		}

		if(arr[index] == chck){
			break;
		}
	}

	if(i == m){
		printf("-1\n");
		return 0;
	}

	for(;i<m;i++)
		scanf("%ld",&temp);

	printf("%d\n",count);
	return 0;
}