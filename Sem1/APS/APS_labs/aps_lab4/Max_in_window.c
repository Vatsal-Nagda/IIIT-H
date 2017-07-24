#include <stdio.h>
#include <malloc.h>

int* deque;
int front=0;
int rear=0;
int m;

int empty(){
	if(front == rear)
		return 1;
	return 0;
}

void pop_back(){
	// printf("\n%d popped from rear of Deque\n", deque[rear]);
/*	if(rear > 0){
		//deque[rear-1] = -1;
		rear--;
	}
	else{
		//deque[0] = -1;
		rear = rear-1+m;
	}*/
		rear--;
}

void pop_front(){
	// printf("\n%d popped from front of Deque\n", deque[front]);
	// deque[front] = -1;
	front = (front+1);
}

void push_back(int x){
	deque[rear++] = x;
	// printf("\n%d  pushed back into Deque \n",x );
}

int back(){
/*	if(rear > 0)
		return rear -1;
*/
	return (rear-1);
}

int main(){
	int i,j,n,t;
	int *arr;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d %d",&n,&m);

		arr = (int *)malloc(sizeof(int)*n);
		deque = (int *)malloc(sizeof(int)*m);

		for(j=0;j<n;j++)
			scanf("%d",&arr[j]);

		for(j=0;j<m;j++){
			//scanf("%d",&arr[j]);
			//initial set up of the dequeue
			while(!empty() && arr[j] >= arr[deque[back()]]){
				pop_back();
				/*printf("Pop back called @ i =%d\n",arr[j]);
				printf("front :%d   rear  :%d\n",front,rear );*/
			}

			push_back(j);
			 // printf("front :%d   rear  :%d\n",front,rear );
		}

		for(;j<n;j++){
			//scanf("%d",&arr[j]);
			printf("%d ", arr[deque[front]]);

			while(!empty() && deque[front] <= j-m){
				 // printf("deque[front] :%d\tj-m :%d\n",deque[front],j-m );
				pop_front();
				/*printf("Pop front called @ i =%d\n",arr[j]);
				printf("front :%d   rear  :%d\n",front,rear );*/
			}

			while(!empty() && arr[j] >= arr[deque[back()]]){
				pop_back();
				/*printf("Pop back called @ i =%d\n",arr[j]);
				printf("front :%d   rear  :%d\n",front,rear );*/
			}

			push_back(j);
			 // printf("front :%d   rear  :%d\n",front,rear );
		}
		printf("%d\n", arr[deque[front]]);

		free(deque);
		free(arr);
		front = rear =0;

	}
	return 0;
}