#include <stdio.h>

void kadanes(char *arr){
	int max_left=0,max_right=0;//,left=0;
	int S=-1,Max=-1;

	int i=0,flag =-1;

	for(i=0;arr[i] !='\0';i++){

		if(arr[i] == '0'){
			if(S < 0){
				flag = 1;
				max_left = i;
			//	printf("New left is %d\n",max_left );
				S =0;
			}
			S++;	
			
			if(S > Max){
				Max = S;
				max_right = i;
			//	printf("New right is %d\n",max_right );
			}
		}
		else{			
			S--;
		}
		//		printf("arr[i] :%c\tS: %d\tM :%d\n",arr[i],S,Max );

	}

	if(flag != 1){
		max_right = max_left = -1;
	}

	if(max_left > max_right)
		max_left = max_right;


	printf("%d %d\n",max_left,max_right );
}

int main(){
	int t,i;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		char arr[1000000];
		scanf("%s",arr);

		kadanes(arr);
	}

	return 0;
}