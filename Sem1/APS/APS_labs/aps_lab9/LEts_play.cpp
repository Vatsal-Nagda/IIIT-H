/**

 There is a Computer Game in which computer shows you a list of N items with their point value.

The rules of this game are :

    You and Computer play the game in alternate moves,in which you play the first move.
    When it is your turn,you have 3 choices of picking the items from the list. i.e either pick top 1 or top 2 or top 3 items in the list.
    In the next move Computer will also pick the same number of items you picked
    If the list has less number of items than the number of items you picked . Computer will pick the remaining items.

Can you play this game optimally such that you get the maximum points.


Input Format
First Line : T ,number of time you play the game.
First line of each game : N ,number of items
Second line of each game : Space separated point value of each item.
Output Format
Print the newline separated maximum points you can make for each game

Constraints
1 <= T <= 10000
1 <= N <= 100000
1 <= point value of each item <= 1000000

Example 1
Input
2
4
5 4 3 2
6
10 8 7 11 15 20
Note : Top here means the first item remaining in the list
Output
12
53

Prob setter : Sunil Kandari


**/
#include <iostream>
#include <malloc.h>
#include <algorithm>

using namespace std;

int main(){

	int N,t;
	cin>>t;
	while(t--){
		cin>>N;
		int points[N];
		long long dp[N+3];

		for(long long i=0;i<N;i++)
			cin>>points[i];

		long long sum_1;
		long long sum_2;
		long long sum_3;

		dp[N]=dp[N+1]=dp[N+2]=0;
		dp[N-1]=points[N-1];
		dp[N-2]=points[N-1] + points[N-2];
		dp[N-3]=points[N-1] + points[N-2] + points[N-3];

		for(int i = N-4;i>=0;i--){
			sum_1 = points[i] + dp[i+2];
			sum_2 = points[i] + points[i+1] + dp[i+4];
			sum_3 = points[i] + points[i+1] + points[i+2] + dp[i+6];
			dp[i] = max(sum_1,max(sum_2,sum_3));
		}

		cout<<dp[0]<<endl;
	}

	return 0;
}