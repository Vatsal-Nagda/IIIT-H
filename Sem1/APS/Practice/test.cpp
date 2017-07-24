#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main(){

	int t,num=0;
	cin>>t;
	cin.ignore();

	while(t--){

		vector< string> ordr;
		string str;
		getline(cin,str);

		stringstream s(str);
		string qwe;

		while(s>>qwe){
			ordr.push_back(qwe);
		//	cout<<qwe<<" ";
		}

		reverse(ordr.begin(),ordr.end());

		vector<string> ::iterator itr = ordr.begin();
		cout<<*itr;

		for(itr=ordr.begin()+1;itr!=ordr.end();itr++)
			cout<<" "<<*itr;
		cout<<endl;

	}

	return 0;
}