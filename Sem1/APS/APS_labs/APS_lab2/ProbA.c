/**

Given a number N, find its cube root till 6th place of decimal.

Do not use standard libraries to find the cube root.



Input Format
First line contain number of test cases, say 't'.
Next t lines follow each having a single number N.


Constraints

    0<=N<=3x10^8 

Output Format
Print a single line containing the required answer.
Sample Input
2
27
144
Sample Output
3.000000
5.241483

**/

#include <stdio.h>

void cube_root(long double a){

	long double low =0.0,high = a,mid=0;	
	long double eps = 0.0000001L;


	if(a<1){
		low =a;
		high =1L;
	}

	while(1){

		mid = low + (high-low)/2;

		//long double temp = mid*mid*mid;
		long double diff = mid*mid*mid - a;

		//printf("value of low : %.10Lf   value of mid : %.10Lf   value of high : %.10Lf\n",low,mid,high );

		if(diff > eps){
			high = mid;
		}
		else if(diff < 0)
			low = mid ;
		else if(diff < eps){
			break;
		}
	}	
//	printf("value of low : %.10Lf   value of mid : %.10Lf   value of high : %.10Lf\n",low,mid,high );

	//mid = (mid*1000000+1)/1000000;
    printf("%.6Lf\n",mid );
}

int main(){
	
	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		long double N;
		scanf("%Lf",&N);
		cube_root(N);
		//printf("%.6Lf\n",answer );
	}

	return 0;
}