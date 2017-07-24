#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

	int t;
	cin>>t;
	while(t--){
		int hash[26];
		int visited [26];

		for(int i=0;i<26;i++)
			visited[i]=hash[i]=-1;

		vector< char > final_pos;
		vector <char> ::iterator v_itr=final_pos.begin();		
		string str;
		cin>>str;
		int len = str.length();
		//cout<<len<<endl;
		for(int i=0;i<len;i++){
			if(hash[str[i]-97] == -1)
				hash[str[i]-97] = 1;
			else{				
				hash[str[i]-97]++;
			}
		}

		vector <char > ::reverse_iterator vec_it;
		for(int i=0;i<len;i++){
			int index= str[i]-97;
			hash[index]--;
			if(visited[index] == -1){
				final_pos.push_back(str[i]);
				visited[index] = 1;

				int k=0;
				for(vec_it = final_pos.rbegin();vec_it!=final_pos.rend();vec_it++){
					k++;	
					char temp = *vec_it;
					if(temp > str[i]){	//greater than current char
						if(hash[temp-97] > 0){
							visited[temp-97] = -1;
							final_pos.erase(final_pos.end()-k);
							k--;
						}
						else
							break;
					}
				}
			}
		}

		v_itr=final_pos.begin();		
		for(;v_itr!=final_pos.end();v_itr++)
			cout<<*v_itr;
		cout<<endl;
	}

	return 0;
}