#include <iostream>
//#include <malloc.h>
#include <queue>

using namespace std;

int main(){
	
	int t;
	cin>>t;
	while (t--){
		bool flag = false;
		bool *visited;
		int *level;
		int f,s,g,u,d,chck;
		cin>>f>>s>>g>>u>>d;
		s--,g--;
		visited = new bool [f];
		for(int i=0;i<f;i++)
			visited[i] = false;
		level = new int [f];
		for(int i=0;i<f;i++)
			level[i] = 0;

			queue < int > Q;
			Q.push(s);
			level[s] = 0;
			visited[s]=true;

			while(!Q.empty()){
				chck = Q.front();
				 // cout<<"visited vertex"<<chck<<" and steps till now "<<count<<endl;
				Q.pop();				

				if(chck == g){
					flag = true;
					break;
				}	

				//count++;
				if((chck + u < f) && !visited[chck + u] ){
						level[chck+u] = level[chck] +1;
						visited[chck+u]=true;
						Q.push(chck+u);
				}
				
				if((chck-d >= 0) && !visited[chck - d]){
						level[chck-d] = level[chck] +1;
						visited[chck-d]=true;
						Q.push(chck-d);
				}										
			}

			if(flag)
				cout<<level[chck]<<endl;
			else
				cout<<"USE THE STAIRS\n";

		//free(visited);
		delete [] visited;
		delete [] level;
	}

	return 0;
}