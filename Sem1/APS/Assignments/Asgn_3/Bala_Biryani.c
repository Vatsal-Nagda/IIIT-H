#include <stdio.h>
#define	MAX 2500

int main(){
	int i,j,t;
	scanf("%d",&t);
	char A[2001];
	char B[2001];

	while(t--){

		scanf("%s",A);
		scanf("%s",B);
		int ans[MAX]={0};
		int len_A=0;
		int len_B=0;
		int term=0;

		while(A[len_A]!='\0')
			len_A++;

		while(B[len_B]!='\0')
			len_B++;

		len_A--;
		len_B--;

		int index =0;
		int next_index_to_start=0;
		int carry=0;
		
		for(i=len_B;i>=0;i--){

			index = next_index_to_start;
			carry=0;

			for(j=len_A;j>=0;j--){

				term = (A[j]-'0')*(B[i]-'0') + carry + ans[index] ;
				carry = (term/10);

				ans[index] = term%10;
				// printf("term:%d\n",ans[index] );
				index++;
			}			

			if(carry !=0){
				ans[index] = carry;
				// printf("term:%d\n",ans[index] );

			}
			//printf("\n");

			next_index_to_start++;

		}

//		printf("last index :%d\n",index );

		int chck = index;
		int flag = 0;			//indicates no zeros

		while(chck >= 0){
			if(ans[chck--]!=0)
				flag = 1;
		}

		if(flag == 0)	
			printf("0");
		else{

			while(index>=0){
				if(ans[index]== 0)
					index--;
				else
					break;
			}

			while(index >=0){
				printf("%d",ans[index] );
				index--;
			}
		}

		printf("\n");
	}


	return 0;
}