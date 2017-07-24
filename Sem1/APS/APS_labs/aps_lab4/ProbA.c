#include <stdio.h>
#define YES 1
#define NO 0

int main(){

	int i,j,test_cases;
	scanf("%d",&test_cases);
	
	for(i=0;i<test_cases;i++){

		char string[100001 ]= {'\0'};
		char stack [50001] = {'\0'};
		int top=-1,flag =YES;

		scanf("%s",string);
		fflush(stdin);

		for(j=0;string[j]!='\0';j++){

			// printf("\n %c :",string[j]);

			if (string[j] == '(' || string[j] == '{'  || string[j] == '[' || string[j] == '<' ){
				stack[++top] = string[j];
				// printf("Pushed '%c' into stack  New top is %d\n",string[j],top );
			}
			else if( string[j] == ')' && stack[top] == '('){
				// printf("Popped '%c' from the stack\n",stack[top] );
				stack[top--] = '\0';
			}
			else if(string[j] == '}' && stack[top] == '{'){
				// printf("Popped '%c' from the stack\n",stack[top] );
				stack[top--] = '\0';
			}
			else if(string[j] == ']' && stack[top] == '['){
				// printf("Popped '%c' from the stack\n",stack[top] );
				stack[top--] = '\0';
			}
			else if(string[j] == '>' && stack[top] =='<'){
				// printf("Popped '%c' from the stack\n",stack[top] );
				stack[top--] = '\0';
			}
			else{
				flag = NO;
				break;
			}

		}
		// printf("Top @ last is %d\n",top );
		if(flag == NO || top !=-1)
			printf("NO\n");
		else
			printf("YES\n");

	}



	return 0;
}