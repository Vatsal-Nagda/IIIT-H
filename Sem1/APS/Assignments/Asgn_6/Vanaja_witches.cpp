/**

Vanaja wants to become the next queen of Parijaat forest. For this the existing queen Shivangi sent her to a vicious forest to gain experience. This vicious forest is guarded by n witches. Each ith witch has some strength given by an integer si. Vanaja begin her journey through the vicious forest with S=1 strength points and E=0 experience points. For each undefeated witch i, she can perform either of the following actions:

1. Vanaja stabs the witch i. This increments S by 1 and defeats the witch.
2. Vanaja battles witch i. This increases E by S x Si and defeats the witch.

Each witch can only be defeated once. Witches can be defeated in any order. Find the maximum number of experience points Vanaja can earn from defeating all witches.


Input Format
The first line contains an integer t denoting number of test cases. Each testcase consists of two lines:
1. The first line of each test case contains an integer n denoting the number of witches in forest.
2. The second line contains n space separated integers (s1 s2 .... sn) where si denotes strength of witch i.

Constraints

    1 <= t <= 10^5
    1 <= n <= 10^6
    1 <= si <= 10^7
    The sum of all n's in a single test case is <= 10^6 

Output Format
For each test case, print an integer denoting the maximum number of experience points that Vanaja can earn.

Sample Input
1
3
3 2 2

Sample Output
10

Problem Setter: Tanushri

**/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	int n,t;
	cin>>t;
	while(t--){
		cin>>n;
		int si;
		//long long E,S;
		vector <int> Strength;
		for(int i=0;i<n;i++){
			cin>>si;
			Strength.push_back(si);
		}

		sort(Strength.begin(),Strength.end());

		long long count=n,sum=0,max=0,temp=0;

		for(int i = n-1;i>=0;i--){
			temp += Strength[i]*count;
			sum+=Strength[i];
		//	cout<<"current score: "<<temp<<"\t Stabs "<<count<<"\tSum "<<sum<<endl;
			count--;
			if(temp > max)
				max = temp;
			temp -= sum;
		}

		cout<<max<<endl;
		
	}

	return 0;
}