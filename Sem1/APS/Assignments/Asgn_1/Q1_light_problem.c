#include <stdio.h>

int main(){
	int i,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		unsigned int ans=0,n,temp;
		scanf("%u",&n);

		int j=0,k=0;
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				scanf("%u",&temp);
				if((j == k) || (k+j == (n-1)))
					ans = (ans + temp)%(1000000009);
				//else if(k+j == (n-1))
			}
		}
		printf("%u\n",ans );
	}
	return 0;
}
/**Limelight

Limelight is a technique that is used when all four users take place in the cardinal directions. They will then join their strength in the form of four connecting streams above the target area. It will then create a massive ball of lightning powerful enough to incinerate everything within the area of the four users.

Using this technique, the King Kitano plans to create the lightning ball. The fighters form a square shape of size NxN.
And strength of the attack is equal to the sum of all the elements in the connecting streams as shown in the figure.

Compute the strength of the attack (mod 10^9 + 9)

Input Format:

First line contains an integer T, denoting the number of testcases.
Each test case consists of a single integer N followed by NxN matrix which has the strength of the fighters.

Output Format:

Print the strength, each in a new line

Constraints:
1 <= T <= 10^5
1 <= N <= 10^7
1 <= strength of each fighter <= 3 x 10^9 

Ex:
Input:
1
3
1 2 3
4 5 6
7 8 9

Output:
25

Explanation:
Here the strength of each fighter along the cardinal direction is 1,3,5,7 and 9. So the total strength becomes 1 + 3 + 5 + 7 + 9/