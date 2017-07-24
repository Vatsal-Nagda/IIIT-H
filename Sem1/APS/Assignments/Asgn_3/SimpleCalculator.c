#include <stdio.h>
#include <malloc.h>

struct stck{
	char arr[100001];
	int top;
};

void push(struct stck* stack, char expr){
	stack->arr[++stack->top] = expr;
}

char peep(struct stck stack){

	if(stack.top != -1)
		return	stack.arr[stack.top] ;

	return '0';
}

char pop(struct stck* stack){
	
	if(stack->top != -1){
		char c = stack->arr[stack->top];
		stack->arr[stack->top--] = '\0';
		return	c ;
	}

	return '0';
}

int isEmpty(struct stck stack){
	if(stack.top == -1)
		return 1;

	return 0;
}

int precedence(char c){
	if(c == '-' || c =='+')
		return 1;
	return 0;
}


void infix_postfix(char* expr,char* oprnd){

	struct stck stack;
	stack.top = -1;
	int  i,j=0;

	for(i=0;expr[i]!= '\0';i++){

		// printf("\n%c :", expr[i]);

		if(expr[i] >= '0' && expr[i] <= '9'){ 
			oprnd[j++] = expr[i];
		//	printf("%c is operand which put directly in final answer\n",expr[i] );
		}
		
		else if(expr[i] == '('){
			push(&stack,'(');
			// printf("Pushing ( into the stack\n");
		}
		
		else if(expr[i] == '+' || expr[i] == '-'){

			while(!isEmpty(stack) && precedence(expr[i]) <= precedence(peep(stack))){
				oprnd[j++] = pop(&stack);	
				// printf("Popping %c from the stack\n",oprnd[j-1] );			
			}
			push(&stack,expr[i]);
			// printf("Pushing %c into the stack\n",expr[i] );
		}
		else{
			while(!isEmpty(stack) && peep(stack)!= '('){
				oprnd[j++] = pop(&stack);
				// printf("Popping %c from the stack\n",oprnd[j-1] );
			}	
			pop(&stack);
			//printf("Popping %c from stack\n",c );
		}

	}	

		while(!isEmpty(stack))
			oprnd[j++] = pop(&stack);

		oprnd[j] = '\0';

}


struct stck_int{
	int arr[100001];
	int top;
};


void push_int(struct stck_int* stack, int dig){
	stack->arr[++stack->top] = dig;
}

int pop_int(struct stck_int* stack){
	
	if(stack->top != -1){
		return	stack->arr[stack->top--];
	}

	return -900009;
}

int eval_postfix(char* postfix){
	//int ans = 0;
	int oprnd1,oprnd2;
	int i=0;
	struct stck_int stack;
	stack.top = -1;

	for(i=0;postfix[i]!= '\0';i++){

		//printf("Content of stack right now :%s\n",stack.arr );
		// printf("=Stack contents\n");
		// for(j=0;j<stack.top;j++)
		// 	printf("%d ",stack.arr[j] );
		// printf("\n");
		if(postfix[i] >= '0' && postfix[i] <='9')
			push_int(&stack,postfix[i]-'0');
		else{
			oprnd2 = pop_int(&stack);
			oprnd1 = pop_int(&stack);

			if(postfix[i] =='+'){
				push_int(&stack,oprnd1+oprnd2);
				 // printf("%d + %d = %d\n",oprnd1,oprnd2 ,oprnd1+oprnd2);
			}
			else{
				push_int(&stack,oprnd1-oprnd2);
				 // printf("%d - %d = %d\n",oprnd1,oprnd2 ,oprnd1-oprnd2);
			}
		}
	}

	return pop_int(&stack);

}

int main(){

	int i,ans,N;
	scanf("%d",&N);

	for(i=0;i<N;i++){
		
		char *expr  = (char *)malloc(sizeof(char)*100001);
		char oprnd [100001] ;

		scanf("%s",expr);

		infix_postfix(expr,oprnd);

		 // printf("The postfix expression is %s\n",oprnd );

		ans = eval_postfix(oprnd);

		printf("%d\n",ans );

		free(expr);
	}

	return 0;
}