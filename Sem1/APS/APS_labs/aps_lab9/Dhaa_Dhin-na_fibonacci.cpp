/***

Dhaa-Dhaa-Dhin-Naa, Give me the beats

How about some tabla lessons first !!

Table is one of the main percussion instruments used in Hindustani classical music. In the hands of an expert tabla player, the tabla can make all kinds of fantastic sounds, but there are a couple of dozen commonly produced sounds - dhaa, ga, ge, gi, ka, ke, dhi, dhin, tin, ti, te, Ta, naa, ne, re. These are called bols, and it is these bols that are combined in various ways to get many interesting rhythms (taals).

Ustad Dim Tim is a professional tabla player who has practiced tabla for years. So after so many years our Ustad stumbles across an interesting problem. Ustad is writing a new composition. He is almost done with his composition. But he has last 8 beats left to fill. He can fill the last eight places with only two bols. One bol Dhaa which is one beat bol and the other Dhin-Naa which is a 2 beat bol. So he tries to enumerate it like this.

Ahh! Ustad gives up. He does not like this complicated math. He needs your help !!.
If there are N beats in a composition. In how many ways can you arrange the bols to create new compositions using the above two mentioned bols.

Input:
First line has an integer T, the no. of test cases.
1 <= T <= 10000 Each of the next T lines contains N, the no. of beats in a composition. 1 <= N <= 1000000

Output:
Print the no. of compositions possible for each test case.
Do a mod 10^9+7 of the output.

Sample Input:
2
1
2

Sample Ouput:
1
2
Problem setter : Harshendra Avabratha


**/

#include <iostream>
#define MODULUS 1000000007
#define MAXSIZE 1000000

using namespace std;

int fibonacci[MAXSIZE+1];

void fibo(int n){
	fibonacci[1]=1;
	fibonacci[2]=2;
	fibonacci[3]=3;
	
	for(int i=4;i<=n;i++)
		fibonacci[i] = (fibonacci[i-1]%MODULUS+fibonacci[i-2]%MODULUS)%MODULUS;
}

int main(){
	int n,t;
	cin>>t;
	fibo(MAXSIZE);
	while (t--){
		cin>>n;
		cout<<fibonacci[n]<<endl;
	}
	return 0;
}