#include <stdio.h>

int main(){
	int i,j,n,count;
	scanf("%d",&n);
	//int flag = 0;

	//char stack[1000000]={''};
	char str[1000000];
	//char temp;

	for(i=0;i<n;i++){
		count=0;
	scanf("%s",str);
		j=0;
		//temp = str[j];

		while(str[j]  != '\0'){
		
			if(str[j]  == '(')
				count++;
			else if(str[j] == ')'){
				count--;
				if (count == -1){
					break;
				}
			}	
			j++;		
		}

		if(count == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}