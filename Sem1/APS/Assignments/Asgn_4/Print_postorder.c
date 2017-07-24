#include <stdio.h>
#include <malloc.h>

struct stck_int{
	int* arr;
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

int check_preoder(int *preorder, int n){
	struct stck_int stack;
	stack.top = -1;
	stack.arr = (int *)malloc(sizeof(int)*n);

	int i=0,root = -1;

	for(i=0;i<n;i++){
		if(preorder[i] < root )
			return 0;

		while(!isEmpty(stack) && preorder[i] > peep(stack)){
			// printf("popped %d from the stack\n",peep(stack) );
			root = pop_int(&stack);
		}

		push_int(&stack,preorder[i]);
		// printf("Pushed %d into the stack\n",preorder[i] );
	}

	return 1;
}

int i;

void post_from_pre(int *preorder,int start,int end,int size){
	int root = preorder[i];
	int index = root -1;

	//printf("\nroot :%d index :%d\n",root,index );

	if(i < size )i++;{
		if(index > start)
			post_from_pre(preorder,start,index-1,size);
		if(index != -1 && index < end)
			post_from_pre(preorder,index+1,end,size);
	}

	printf("%d\n", root);

}

int main(){

	int k,t;
	scanf("%d",&t);
	for(k=0;k<t;k++){
		int j,n;
		scanf("%d",&n);			
		int *preorder = (int *)malloc(sizeof(int)*n);
		
		for(j=0;j<n;j++)
			scanf("%d",&preorder[j]);

		// for(j=0;j<n;j++)
		// 	printf("%d",preorder[j]);

		int flag = check_preoder(preorder,n);

		if(!flag){
			printf("Case %d:\n",k+1 );
			printf("-1\n");
		}
		else{
			// pre order is correct now make inorder
			i=0;
			printf("Case %d:\n",k+1 );
			post_from_pre(preorder,0,n-1,n);
		}

		free(preorder);
	}

	return 0;
}