/**

Given a right angled triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below. Adjacent implies you can either go to diagonal left, diagonal right or straight downwards.

Input Format

The first line indicates the number of test cases, the first line of each test case contains an integer N, which represent the number of rows in the triangle, the next N lines contains positive integers of the triangle, the i-th row of the triangle contains i integers(row number from 1 to N).

Constraints

    1<=t<=10
    1 <= N <= 1000 


Output Format
For each testcase output the minimum sum.

Note:The sum fits in an integer

Sample Test case

Input
1
3
1
1 2
2 1 3
Output
3

Problem setter:Vanaja

**/

#include <iostream>
#include <algorithm>

using namespace std;

int main(){

	int N,t;
	cin>>t;
	while(t--){
		cin>>N;
		int triangle[N+1][N+1];

		for(int i=1;i<=N;i++){
			for(int j=1;j<=i;j++){
				cin>>triangle[i][j];
			}
		}

		for(int i=N-1;i>=1;i--){
			for(int j=1;j<=i;j++){
				int k=j-1;
				if((j-1)==  0) {		//frst column
					k=j;
				}
				triangle[i][j] += min(triangle[i+1][j],min(triangle[i+1][k],triangle[i+1][j+1]));			
			}
		}

		cout<<triangle[1][1]<<endl;
	}
	return 0;
}
