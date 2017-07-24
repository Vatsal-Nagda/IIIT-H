#include <bits/stdc++.h>

using namespace std;

struct Graph{
	int size;
	list <int> *adj;
};

void topological_sort(struct Graph *g){

	vector <int> degree (g->size +1,0);
	int visited=0;
	//int zero=0;
	bool flag = false;		//no multiple starts
	list <int> ::iterator lst_itr;

	for(int i=1;i<= g->size;i++){
		if(!g->adj[i].empty()){			
			for(lst_itr = g->adj[i].begin();lst_itr !=g->adj[i].end();lst_itr++){
				degree[*lst_itr]++;
			}				
		}		
	}

	queue <int > pq;
	vector <int > topo_odr;

	for(int i=1;i<= g->size;i++)
		if(degree[i] == 0){
			pq.push(i);
			//zero++;
		}

	while(!pq.empty()){
		int top = pq.front();
		pq.pop();	
		visited++;

		if(pq.size() >= 1){
			flag = true;		//multiple possible
		}

		for(lst_itr = g->adj[top].begin();lst_itr !=g->adj[top].end();lst_itr++){
			degree[*lst_itr]--;
			if (degree[*lst_itr] == 0)
				pq.push(*lst_itr);
		}	
		
		topo_odr.push_back(top);			// maintain the topological order
	}

	if(visited != g->size)
		cout<<"valar morghulis\n";
	else{

		if(flag)
			cout<<"valar dohaeris"<<endl;
		else{
			int i;
			int size = topo_odr.size();
			for( i=0;i<size-1;i++)
				cout<<topo_odr[i]<<" ";	
			cout<<topo_odr[i]<<"\n";
		}	
	}
}

int main(){

	int t;
	cin>>t;
	while(t--){
		int n,num_edge;
		cin>>n>>num_edge;
		Graph g;
		g.size = n;
		g.adj = new list<int> [n+1];

		for (int i=0;i<num_edge;i++){
			int src,dest;
			cin>>src>>dest;
			g.adj[src].push_back(dest);
		}
		topological_sort(&g);
	}

	return 0;
}