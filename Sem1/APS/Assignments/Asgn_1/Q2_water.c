#include <stdio.h>

int gcd(int num1,int num2){

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
		
		if(temp1 == temp2)
			break;
		if(temp2 > temp1)
		{
			temp = temp1;
			temp1 = temp2;
			temp2 = temp;
		}
		temp1 = temp1-temp2;
	}
	return temp2;
}

int main(){

	int i,t,x,y,z,max,min;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d%d%d",&x,&y,&z);

		if(x > y){
			max = x;
			min = y;
		}
		else{
			max = y;
			min = x;
		}
		
		if(z > max || (max == 0 && z !=0) || (min == 0 && max != z))
			printf("0\n");
		else if(z == 0 || (max == 0 && z !=0) || ((min ==0 && max==z)))
			printf("1\n");
		else {
			if(z % gcd(x,y) == 0)
				printf("1\n");
			else
				printf("0\n");
		}
		
	}

	return 0;
}