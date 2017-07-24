#include <iostream>
#include <queue>

using namespace std;

int main(){
	
	int t;
	cin>>t;
	while (t--){
		bool flag = false;
		int f,s,g,u,d,chck,count;
		cin>>f>>s>>g>>u>>d;

		if(g == s)
			cout <<"0"<<endl;
		else{
			queue <int> Q;
			Q.push_back(s);
			count=0;
			
			while(!Q.empty()){
				chck = Q.front();
				Q.pop_front();
				count++;

				if(chck == g){
					flag = true;
					break;
				}					
				if(chck + u <= g)
					Q.push_back(chck+u);
				else
					Q.push_back(chck-d);
			}

			if(flag)
				cout<<count<<endl;
			else
				cout<<"USE THE STAIRS\n";
		}

	}

	return 0;
}