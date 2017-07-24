#include <stdio.h>
#include <malloc.h>

void heapify(int *max_arr,int size,int index){
	int max = index;
	int left = 2*index+1;
	int right = 2*index+2;

	// printf("curr root : %d left :%d  right :%d\n",max,left,right );
	if(right < size && max_arr[right] > max_arr[max]){
		max = right;
	}
	
	if(left < size && max_arr[left] > max_arr[max]){
		max = left;
	}

	if(max != index){
		//change arr[index] and arr[max]
		// printf("Swapped %d and %d\n",max_arr[max],max_arr[index]);
		int temp = max_arr[index];
		max_arr[index] = max_arr[max];
		max_arr[max] = temp;

		/*for(int i=0;i<size;i++)
			printf("%d ",max_arr[i]);
		printf("\n");*/

		heapify(max_arr,size,max);
	}
}


int main(){

	int i,n,m;
	scanf("%d%d",&n,&m);
	int *arr = (int *)malloc(sizeof(int)*n);

	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	for(i=(n/2)-1 ; i>=0 ; i--){
		heapify(arr,n,i);
	}

	//int count =m;
	int ans = 0;

	/*for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");*/

	while(m!=0){
		ans+= arr[0];
		arr[0]--;
		heapify(arr,n,0);

		/*for(i=0;i<n;i++)
		printf("%d ",arr[i]);*/

		// printf("\n");
		m--;
	}

	printf("%d\n",ans );

	// for(i=0;i<n;i++)
	// 	printf("%d ",arr[i]);

	return 0;
}