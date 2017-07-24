#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

struct Graph{
	int size;
	bool *visited;
	vector< vector < pair < int,int > > > adj;
	//adj to b used
};

bool compare(pair<int,int> a, pair<int,int> b){
	if (a.second < b.second)
		return true;
	return false;
}

void initialise(Graph *g,int n){
	g->size = n;
	g->visited = new bool [n];
	g->adj.resize(n+1);
}

void makeAdj(Graph *g, int m){
	map < pair < int,int > ,int> hash;

	int x,y,r;
	for(int i=0;i<m;i++){
		cin>>x>>y>>r;
		pair <int,int > p = make_pair(x,y);
		pair <int,int > p1 = make_pair(y,x);

		if(hash.find(p)!= hash.end()){	//pair already exists in map[]
			hash[p] = r < hash[p] ? r : hash[p];
		}
		else{
			hash[p] = r ;
		}		
		hash[p1] = hash[p];
	}

	map < pair < int,int > ,int> ::iterator map_itr;	
	pair <int,int > p;
	int val;
	for(map_itr = hash.begin();map_itr!=hash.end();map_itr++){
		p = map_itr->first;
		val = map_itr->second;
	//	cout<<"Dist from "<<p.first<<" to "<<p.second<<" is "<<val<<endl;	 
		//cout<<g.adj.size();
		g->adj[p.first].push_back(make_pair(p.second,val));
	}
		//cout<<"Dist from "<<*(map_itr->first->first)<<" to"<<*(map_itr->first->second)<<" is "<<hash[*map_itr]<<endl;
	hash.clear();
}

void srt(Graph *g){
	for(int i=1;i<=g->size;i++){
		sort(g->adj[1].begin(),g->adj[1].end(),compare);
	}
}

void printAdj(Graph g){
		for(int i=1;i<=g.size;i++){

			cout<<"\nDistances from node "<< i <<" : ";

			vector <pair <int,int > > ::iterator vec_itr;
//			pair <int,int > p;
			for(vec_itr = g.adj[i].begin() ; vec_itr != g.adj[i].end() ; vec_itr++){
				cout<< vec_itr->first<<" -> "<<vec_itr->second<<" ";
			}			
		}

}

void Dijkstra(Graph *g,int start){
	int count=0;
	int dist[g->size+1];

	for(int i=0;i<=g->size;i++){
		dist[i] = INT_MAX;
	}

	dist[start] =0;

	priority_queue < pair <int, int>, vector < pair < int, int > >, greater < pair<int, int> > > min_heap;	

	min_heap.push(make_pair(0,start));

	while(!min_heap.empty() ){
		int src = min_heap.top().second;

		min_heap.pop();
		count++;
		vector <pair <int,int > > ::iterator vec_itr;
		for(vec_itr = g->adj[src].begin() ; vec_itr != g->adj[src].end() ; vec_itr++){
			int dest = vec_itr->first;
			int cost = vec_itr->second;

			if(dist[dest] > dist[src] + cost){
				dist[dest] = dist[src] + cost;
				min_heap.push(make_pair(dist[dest],dest));
			}
		}	
	}

	for(int i=1;i<=g->size;i++){
		if(i == start)
			continue;
		if(dist[i] == INT_MAX)
			dist[i] = -1;
		cout<<dist[i]<<" ";
	}
	/*vector <pair <int,int > > ::iterator vec_itr;
	for(vec_itr = g->adj[start].begin() ; vec_itr != g->adj[start].end() ; vec_itr++){
		dist[vec_itr->first] = vec_itr->second;
	}

	for(vec_itr = g->adj[start].begin() ; vec_itr != g->adj[start].end() ; vec_itr++){
		int src = vec_itr->first;

		vector <pair <int,int > > ::iterator vec_itr1;
		for(vec_itr1 = g->adj[src].begin() ; vec_itr1 != g->adj[src].end() ; vec_itr1++){
			int dest = vec_itr1->first;
			int dest_cost = vec_itr1->second;

			if(dist[dest] > dist[src] + dest_cost){
				cout<<"update dist btwn"<< start <<" and "<< dest <<" from "<< dist[dest] <<" to "<< dist[src] + dest_cost <<endl;
				dist[dest] = dist[src] + dest_cost;
			}
				
		}
	}

	for(int i=1;i<=g->size;i++){
		if(i == start)
			continue;
		if(dist[i] == INT_MAX)
			dist[i] = -1;
		cout<<dist[i]<<" ";
	}
*/}

int main(){

	int t;
	cin>>t;
	while(t--){

		Graph g;
		int N,M;
		cin>>N>>M;
		initialise(&g,N);
	//	cout<<"g size "<<g.size;
		makeAdj(&g,M);	//takes input to form adj list
		srt(&g);
		//printAdj(g);

		int start;
		cin>>start;
		Dijkstra(&g,start);
		cout<<"\n";
	}

	return 0;
}