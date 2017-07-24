#include <stdio.h>

int main(){
	int i,j,t,n;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d",&n);

		unsigned long int arr[n];

		unsigned long int max =0,max_left=0,max_right=0;
		int max_pos=0 ,max_left_pos=0,max_right_pos=0;

		for(j=0;j<n;j++){
			scanf("%Lf",&arr[j]);
			if(arr[j] > max){
				max = arr[j];
				max_pos = j;
			}				
		}

		for(j=0;j<max_pos;j++){
			if(arr[j] > max_left){
				max_left = arr[j];
				max_left_pos = j;
			}	
		}


		for(j=max_pos;j<n;j++){
			if(arr[j] > max_right){
				max_right = arr[j];
				max_right_pos = j;
			}	
		}

		unsigned long answer=0,min=0;

		if(max_left > max){
			min = max;
		}
		else
			min  max_left;

		for(j=0)

	}

}