/**

 Dim Tim wants to write a paragraph full of just letter 'a'. He wants to generate a total of n characters.

So he starts typing letter 'a' in a text editor. Initially the text editor is empty. It takes x seconds to insert or delete a letter 'a' from the text file and y seconds to copy the contents of the entire text file and duplicate it.

Now your job is to output the minimum amount of time needed for him to create a file on n characters of letter 'a'

Input
First line has an integer T, no. of test cases (1 ≤T ≤100)
Each of the following lines have three integers separated by space – n, x and y
(1 ≤ n ≤ 10^6, 1 ≤ x, y ≤ 10^9)

Output
Print the output in T lines.

Sample input
2
8 1 1
8 1 10

Sample output
4
8

Explanation
First case:
a – 1 sec (1 sec to Insert a new char)
aa – 2 secs (1 sec to Copy the whole file)
aaaa – 3 secs (1 sec to Copy the whole file)
aaaaaaaa – 4 secs (1 sec to Copy the whole file)

Problem Setter : Harshendra Avabratha 

**/
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main(){

	int n,x,y,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&x,&y);
		long long dp[n];
		dp[0]=x;

		// cout<<"i\tdp[i]"<<endl;
		for(int i=1;i<n;i++){
			if(i%2 == 0){		//odd length generated
				dp[i] = min(dp[i-1]+x,min(dp[i/2]+y+x,dp[i/2-1]+y+x));
			}
			else
				dp[i] = min(dp[i-1]+x,dp[i/2]+y);
	// cout<<i<<"\t"<<dp[i]<<endl;
		}
		cout<<dp[n-1]<<endl;
	}
	return 0;
}
