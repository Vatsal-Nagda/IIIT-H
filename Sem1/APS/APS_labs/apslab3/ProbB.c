/****

 As Vanaja taught PG1 some interesting Number Theory concepts in last Tutorial , so your other TA decided to check if PG1 is able to apply those concepts in the given problem.

He gives you a range [X, Y] and wants to know the total of all the differences of square of two adjacent non-intersecting paired numbers

i.e total of all the differences of square of pairs : [X+1,X] ,[X+3,X+2],[X+5,X+4]... till Y
If there exists any unpaired number ,just add its square to the total value.

As your final sum might go very large,and he is not interested in such a large sum. So he wants you to output only the number that remains after :(final sum)%1000000007
Input

    Line 1 : T
    the no. of test cases
    Next T lines : X Y
    the ranges [X,Y]

Constraints

    T <= 106
    0 <= X <= Y <= 1018

Output

    Corresponding to each test case output the required number.

Example
Input
3
1 4
2 4
3 9
Output
10
21
114
Explanation
For X=1 , Y=4 , you need to find 22-12+42-32.
Prob setter : Sunil Kandari 

****/

#include <stdio.h>

int main(){
	unsigned long int x,y,diff=0;
	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%lu%lu",&x,&y);
		diff = (y-x)+1;
		unsigned long int sum=0,sum_e=0;
		
		/*for(j=x;j<=diff;j+=2){
		//	sum += ((((j+1)%1000000007)*(j+1)%1000000007) - ((j)%1000000007)*(j)%1000000007)%1000000007;
			sum += (j+1)* (j+1) - (j)*(j);
		}

		if(diff %2 != 0)
			sum = (sum + (y%1000000007)*(y%1000000007));*/

		sum = (2*(x%1000000007)*((diff/2)%1000000007 ))%1000000007 ;
		//printf("diff : %lu   2n*diff : %lu\n",diff,sum );
		
		/*for(j=0;j<diff/2;j++)	
			sum_e = (sum_e%1000000007 + (1+4*j)%1000000007)%1000000007 ;
*/
		sum_e =(2*((diff/2)%1000000007)*((diff/2)%1000000007) - ((diff/2)%1000000007)) ;	
		//printf(" n is :%lu  2n^2-n : %lu\n",(diff/2),sum_e );

		sum = (sum%1000000007 + sum_e%1000000007)%1000000007;
		if(diff %2 != 0)
			sum = (sum + (y%1000000007)*(y%1000000007))%1000000007;

		printf("%lu\n",sum );
	}

	return 0;
}