#include <stdio.h>

/*int gcd(int num1,int num2){

	int temp1,temp2;

	if(num1 > num2)
	{
		temp1 = num1;
		temp2 = num2;
	}
	else
	{
		temp2 = num1;
		temp1 = num2;	
	}

	while(temp2 !=0)
	{	
		int temp;
		temp1 = temp1-temp2;
		if(temp1 == temp2)
			break;
		if(temp2 > temp1)
		{
			temp = temp1;
			temp1 = temp2;
			temp2 = temp;
		}
	}

	return temp2;
}
*/

int main(){

	int i,t,x,y,z;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d%d%d",&x,&y,&z);

		int diff = x-y;

		if(diff < 0)
			diff = diff*-1;

		if(diff != 0){
			if(z % diff == 0)		// if Z is a multiple of Gcd(x,y) then only it is possible to pour 
				printf("1\n");
			else
				printf("0\n");
		}
		else{
			if(x == y && y == z)
				printf("1\n");
			else
				printf("0\n");
		}
			
	}

	return 0;
}