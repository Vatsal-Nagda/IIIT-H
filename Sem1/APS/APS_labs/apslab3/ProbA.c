/****

 IIIT-Hyd is offering many courses. Students can take any number of courses. Now Sonam is lazy to fill her registration form. Tell in how many ways she can fill the form.
Everyone has to take atleast one course.

Input Format
First line of the input has an integer T. T cases follow.
An integer N, representing the no. of courses.

Output Format
For each test case in a single line,Output the no. of ways the form can be filled.

As the answer can be large, print the answer modulo 10^9+7

Constraints

    1<=T<=10^5
    1<=N<=10^12 

Sample Input
2
1
2

Sample Output
1
3

Prob Setter: Vanaja

***/


#include <stdio.h>
//#include <math.h>

unsigned long int pow_2(unsigned long int n){
	
	if(n == 1)
		return 2L;

	unsigned long int temp =1;

		temp = pow_2(n/2);

		if(n%2 == 0)
			return (((temp%1000000007)*(temp%1000000007))%1000000007);

	return ((2*(temp%1000000007)*(temp%1000000007))%1000000007); 
}


int main(){
	
	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		unsigned long int ans=1,n;//,iterations,rem;
		scanf("%lu",&n);
/*
		while(n >= 1000000007)
			 n = n/1000000007;
*/
		//printf("n after modification is :%lu\n",n );	 		
		/*iterations = n/32;
		rem = n%32;

		for(j=1;j<=iterations;j++){
			ans = (ans << 32)%(1000000007);
		}

		if(rem != 0){
			ans = (ans << rem)%(1000000007);
		}*/
			ans = pow_2(n);

/*		if(ans == 1)
			ans =2;
*/
		printf("%lu\n",ans-1);
	}

	return 0;
}
