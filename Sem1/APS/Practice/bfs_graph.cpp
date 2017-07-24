#include <iostream>
#include <list>

using namespace std;

struct Graph{
	int size;
	list <int> *adj;
}g;

void addEdge(int src,int dest){
	g.adj[src].push_back(dest);
	//g.adj[dest].push_back(src);
}

void printList(){
	for(int i=0;i<g.size;i++){
		cout<<"for node "<<i<<" : ";
		list <int> ::iterator itr;
		for(itr = g.adj[i].begin();itr!=g.adj[i].end();itr++)
			cout << *itr <<" ";	
		cout<<endl;	
	}
}

bool *visited;

void initialise(){
	for(int i=0;i<g.size;i++)
		visited[i] = false;
}

void DFS(int vertex){

	visited[vertex] = true;
	cout <<vertex <<" ";

	list <int> ::iterator itr;

	for(itr = g.adj[vertex].begin();itr!=g.adj[vertex].end();itr++){
		if(!visited[*itr])
			DFS(*itr);
	}
}


// void DFSinit(int v){
// 	initialise();
// 	DFS(v);
// }


void BFS(int vertex){
	initialise();
	list <int > queue;
	visited[vertex] = true;
	queue.push_back(vertex);

	while(!queue.empty()){
		int v = queue.front();
		cout<<v<<" ";
		queue.pop_front();

		list <int> ::iterator i;
		for(i = g.adj[v].begin();i!=g.adj[v].end();i++)
			if(visited[*i] == false){
				visited[*i] = true;
				queue.push_back(*i);
			}
	}
}

int main(){

	int s;
	cin>>s;

	g.size = s;
	g.adj = new list <int> [s];
	visited = new bool [s];

	int num_edges;
	cin>>num_edges;

	for(int i=0;i<num_edges;i++){
		int src,dest;
	//	cout<<"Enter the src and dest"<<endl;
		cin>>src>>dest;
		addEdge(src,dest);
	}
	
	//printList();

	cout<<"enter start vertex for BFS";
	int strt;
	cin >> strt;
	//BFS(strt);

	// cout<<"enter start vertex for DFS";
	// cin>>strt;
	initialise();
	for(int i=0;i<s;i++)
		if(!visited[i])
			DFS(i);

	return 0;
}