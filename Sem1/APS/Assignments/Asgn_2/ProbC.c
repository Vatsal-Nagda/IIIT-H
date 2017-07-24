#include <stdio.h>

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

int binSearch_modified(int coins[],int size, int key){
	int low=0,mid,high=size;

	while(low < high){
		mid = low + (high-low)/2;

		if(coins[mid] >= key)
			high = mid;
		else
			low = mid+1;
	}

	if( low == high && coins[low]!=key)
		return -1;
	else{
		int start = low;
		high = size;

		while(low < high){
			mid = low+ (high+1-low)/2;

			if(coins[mid] == key)
				low = mid;
			else
				high = mid-1;
		}

		return (high - start +1);
	}

	//return count;
}

int main(){
	
	int i,t,j,n,q,element,answer;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d",&n);

		int coins[n];

		for(j=0;j<n;j++){
			scanf("%d",&coins[j]);
		}

		mergeSort(coins,0,n-1);

		scanf("%d",&q);

		for(j=0;j<q;j++){
			scanf("%d",&element);
			answer = binSearch_modified(coins,n,element);
			printf("%d\n",answer );
		}
	}

	return 0;		
}