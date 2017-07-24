#include <stdio.h>
#define max 3000

int main(){
	
	int t,i,j,k,q,p,term,shift,carry;
	char A[max],B[max];
	scanf("%d",&t);
	while(t--){

		scanf("%s",A);
		scanf("%s",B);
		int C[max] = {0};
		i = 0;
		while(A[i++]!='\0');
		
		j = 0;
		while(B[j++]!='\0');
		
		shift = 0;
		int z,zero = 0;
		for (q = j-2; q >= 0 ; --q)
		{
			carry = 0;
			p = shift;

			for(k = i-2; k >= 0; --k){
				term = carry+C[p]+(A[k]-'0')*(B[q]-'0');
				carry = term/10;
				C[p++] =(term%10);
			}
			if(carry)
			C[p] = carry;
			else
			--p;			

			++shift;
		}
		z = p;
		while(z>=0){
			if(C[z--]!=0)
				zero = 1;
		}
		if(zero==0){
			printf("0\n");
			continue;
		}
		while(p>=0){
			printf("%d",C[p--]);
		}
		printf("\n");
	}

	return 0;
}