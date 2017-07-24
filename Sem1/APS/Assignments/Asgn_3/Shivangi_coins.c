#include <stdio.h>

struct stck_int{
	int arr[10001];
	int top;
};

int peep(struct stck_int stack){

	if(stack.top != -1)
		return	stack.arr[stack.top] ;

	return 0;
}


void push_int(struct stck_int* stack, int dig){
	stack->arr[++(stack->top)] = dig;
}

int pop_int(struct stck_int* stack){
	
	if(stack->top != -1){
		return	stack->arr[(stack->top)--];
	}

	return 0;
}

int isEmpty(struct stck_int stack){
	if(stack.top == -1)
		return 1;

	return 0;
}

int main(){
	
		int i,n;
		scanf("%d",&n);
	while(n!= 0){

		int num_expctd =1;
		int inp_num;
		
		struct stck_int stack2;
		stack2.top = -1;
		for(i=0;i<n;i++){
			scanf("%d",&inp_num);
			if(inp_num == num_expctd){
			//	 printf("%d in the sequence\n",inp_num );
				num_expctd++;
			}
			else{
				while(!isEmpty(stack2) && num_expctd == peep(stack2)){
				//	 printf("%d in the sequence\n",num_expctd );
					num_expctd++;
					pop_int(&stack2);
				}
				if(!isEmpty(stack2)  && peep(stack2) < inp_num){
					i++;
					break;
				}
				push_int(&stack2,inp_num);
			//	 printf("Pushing %d in stack2\n",inp_num);
			}
		}

		for(;i<n;i++){
			
			scanf(" %d",&inp_num);
		//	printf("hello %d\n",inp_num );
		}

		if(num_expctd == pop_int(&stack2)){
			// printf("%d in the sequence\n",num_expctd );
			printf("yes\n");
		}
		else if(num_expctd == n+1)
			
			printf("yes\n");
		else
			printf("no\n");

		scanf("%d",&n);
	}	

	return 0;
}