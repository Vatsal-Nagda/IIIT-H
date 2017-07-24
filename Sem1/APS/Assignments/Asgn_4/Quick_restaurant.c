#include <stdio.h>
#include <malloc.h>

struct customer{
	long long arrival;
	long long burst;
};


void merge(struct customer arr[],long long low,long long mid,long long high){
	long long i=low,j=mid+1,k=0;
	struct customer temp [high-low+1];

	while(i<=mid && j<= high){
		if(arr[i].arrival < arr[j].arrival)
			temp[k++] = arr[i++];
		else if((arr[i].arrival == arr[j].arrival) && arr[i].burst < arr[j].burst)
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

void mergeSort(struct customer arr[],long long low,long long high){
	if(low < high){
		long long mid = low +(high-low)/2;

		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1,high);
		merge(arr,low,mid,high);
	}
}


void heapify(struct customer *min_arr,long long size,long long index){
	long long min = index;
	long long left = 2*index+1;
	long long right = 2*index+2;

	 // printf("curr root : %d left :%d  right :%d\n",min,left,right );
	if(right < size && min_arr[right].burst < min_arr[min].burst){
		// printf("%d is < than %d\n", min_arr[right].burst,min_arr[min].burst);
		min = right;
	}
	
	if(left < size && min_arr[left].burst < min_arr[min].burst){
		// printf("%d is < than %d\n", min_arr[left].burst,min_arr[min].burst);
		min = left;
	}

	if(min != index){
		//change arr[index] and arr[max]
		 // printf("Swapped %d and %d\n",min_arr[min].burst,min_arr[index].burst);
		struct customer temp = min_arr[index];
		min_arr[index] = min_arr[min];
		min_arr[min] = temp;

		/*for(long long i=0;i<size;i++)
			printf("%d ",max_arr[i]);
		printf("\n");*/

		heapify(min_arr,size,min);
	}
}

void buildHeap(struct customer *heap,long long size){
	long long i=0;
	long long start = size/2 -1;

	for(i= start ; i>=0;){
		heapify(heap,size,i);

		if(i %2 == 0)
			i = i/2 -1;
		else
			i = i/2;
	}
}

struct customer deletemin(struct customer *heap, long long *heapsize){

	struct customer head = heap[0];
	heap [0] = heap[*heapsize-1];
	heap[*heapsize-1] = head;
	heapify(heap,*heapsize-1,0);
	return head;
}

long long short_job(struct customer *heap, struct customer *cust, long long size){
	long long clock = cust[0].arrival + cust[0].burst;
	// long long curr_burst = cust[0].burst;
	long long heapsize = 0;
	long long i=1;
	long long on_hold_time = cust[0].burst;
	long long curr=1,prev=0,k=0;

	while(i < size){

		// printf("Clock :%d  i :%d\n",clock,i );
		// printf("Prev %d Curr %d\n",prev,curr );
		
		while( curr < size && cust[curr].arrival <= clock){
			curr++;
		}
		curr--;

		// printf("Prev %d Curr %d\n",prev,curr );

		if( curr != size  && curr > prev){	//elements to b inserted into the heap
			
			for(k=prev+1; k <= curr ; k++){
				if(heapsize == 0){
					heap[heapsize++] = cust[k];
				}
				else{
					heap[heapsize++] = cust[k];
					buildHeap(heap,heapsize);

					// printf("HEAP\n");
					// for(long long q=0;q<heapsize;q++){
					// 	printf("%d %d\n",heap[q].arrival,heap[q].burst );
					// }
				}
			}
		}

		// printf(" heapsize %d\n", heapsize);

		 if(heapsize == 0){
		 			clock = cust[i].arrival;
					heap[heapsize++] = cust[i];
					curr = i;
					prev = i;
		}
		 if(heapsize != 0){
			struct customer head = deletemin(heap,&heapsize);
			heapsize--;
			on_hold_time += (clock - head.arrival) + head.burst;
			// printf("on_hold_time : %d for Arr:%d Burst:%d\n",on_hold_time,head.arrival,head.burst );
			clock += head.burst;
		}
		
		prev = curr;
		curr++;
		i++;	
	}

return on_hold_time;
}

int main(){
	
	long long c;
	scanf("%lld",&c);

	long long num =c;
	struct customer *cust = (struct customer *)malloc(sizeof(struct customer)*c);
	struct customer *heap = (struct customer *)malloc(sizeof(struct customer)*c);

	long long i=0;
	while(c--){
		scanf("%lld%lld",&cust[i].arrival,&cust[i].burst);		
		i++;
	}

	mergeSort(cust,0,num-1);

	/*for(i=1;i<num;i++){
		heap[i-1] = cust[i];
	}
*/
	// long long clock=0;
	long long on_hold_time =0;

	on_hold_time = short_job(heap,cust,num);

	printf("%lld\n",on_hold_time/num );

	free(cust);
	free(heap);
	return 0;
}