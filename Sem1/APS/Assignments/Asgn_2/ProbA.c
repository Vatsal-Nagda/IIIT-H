#include <stdio.h>

/*struct process
{
	int start;
	int end;
};*/


/*void merge(struct process arr[],int low,int mid,int high){
	int i=low,j=mid+1,k=0;
	struct process temp [high-low+1];

	while(i<=mid && j<= high){
		if(arr[i].start < arr[j].start)
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

void mergeSort(struct process arr[],int low,int high){
	if(low < high){
		int mid = low +(high-low)/2;

		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1,high);
		merge(arr,low,mid,high);
	}
}*/


void merge(int arr[],int low,int mid,int high){
	int i=low,j=mid+1,k=0;
	int temp [high-low+1];

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

void mergeSort(int arr[],int low,int high){
	if(low < high){
		int mid = low +(high-low)/2;

		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1,high);
		merge(arr,low,mid,high);
	}
}


int main(){
	
	int i,j,n,k,t;
	int strt_pos,end_pos;

	scanf("%d",&t);

	for(i=0;i<t;i++){

		scanf("%d",&n);
		int start[n];
		int end[n];

		for(j=0;j<n;j++)
			scanf("%d",&start[j]);

		for(j=0;j<n;j++)
			scanf("%d",&end[j]);

		mergeSort(start,0,n-1);
		mergeSort(end,0,n-1);

		scanf("%d",&k);

		if(k == 0){	
			printf("0\n");
			continue;
		}

		for(strt_pos=0,end_pos=0 ;  strt_pos<n  &&  end_pos<n  ; ){

			if(start[strt_pos] < end[end_pos]){
				k--;
				//printf("%d is < %d\nnew K is %d\n", start[strt_pos] ,end[end_pos],k);
				strt_pos++;
			}
			else{
				k++;
			//	printf("%d is >= %d\nnew K is %d\n", start[strt_pos] ,end[end_pos],k);
				end_pos++;
			}

			if(k < 0){
				//printf("0\n");
				break;
			}
		}

		if(k >= 0 )
			printf("1\n");
		else
			printf("0\n");
/*
	  for(j=0;j<n;j++){
			printf("%d ",start[j]);
		}
	
		printf("\n");

		for(j=0;j<n;j++){
			printf("%d ",end[j]);
		}
*/
	}

	return 0;
}