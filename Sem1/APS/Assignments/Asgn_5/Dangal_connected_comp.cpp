#include <bits/stdc++.h>

int count_node;

using namespace std;

struct Graph{
	int size;
	list <int > *adj_normal;
	list <int > *adj_reverse;
	bool *visited;
};

void DFS_rev(Graph *g,int vertex){

	g->visited[vertex] = true;
	//cout <<vertex <<" ";
	count_node++;
	list <int> ::iterator itr;
	for(itr = g->adj_reverse[vertex].begin();itr!=g->adj_reverse[vertex].end();itr++){
		if(!g->visited[*itr])
			DFS_rev(g,*itr);
	}
}

void DFS_normal(Graph *g,int vertex){

	g->visited[vertex] = true;
	//cout <<vertex <<" ";
	count_node++;
	list <int> ::iterator itr;
	for(itr = g->adj_normal[vertex].begin();itr!=g->adj_normal[vertex].end();itr++){
		if(!g->visited[*itr])
			DFS_normal(g,*itr);
	}
}

void initialise(Graph *g){
	for(int i=0;i<=g->size;i++)
		g->visited[i] = false;
}

void DFS_revinit(Graph *g,int v){
	initialise(g);
	DFS_rev(g,v);
}

void DFS_fwdinit(Graph *g,int v){
	initialise(g);
	DFS_normal(g,v);
}

int main(){
	int t;
	cin >>t;
	while (t--){
		int n;
		cin>>n;

		Graph g;
		g.size = n;
		g.adj_normal = new list <int> [n+1];
		g.adj_reverse = new list <int> [n+1];
		g.visited = new bool [n+1];

		for(int i=1;i<=n;i++){
			int num;
			cin >>num;

			for(int j=1;j<=num;j++){
				int src;
				cin>>src;
				g.adj_normal[i].push_back(src);
				////cout<<"inserted "<<src<<" in rev_adj of "<<j<<endl;
				g.adj_reverse[src].push_back(i);
			}
		}


		/**   DFS_rev on REVERSE GRAPH **/

		int node_to_start=0;

		for(int i=1;i<=n;i++){
			count_node=0;
			//cout<<"\nDFS_rev from "<<i<<" : ";
			DFS_revinit(&g,i);
			//<<"No of visited nodes : "<<count_node<<endl;
			if(count_node == n){
				node_to_start = i;
				break;
			}
		}

		if(node_to_start == 0)
			cout<<"0\n";
		else{
			count_node =0;
			//cout<<"In normal Graph DFS_rev";
			DFS_fwdinit(&g,node_to_start);
			//cout<<"\n";
			cout<<count_node<<endl;
		}

	}

	return 0;
}