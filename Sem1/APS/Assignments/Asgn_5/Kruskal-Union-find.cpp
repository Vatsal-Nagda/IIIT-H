/**

Connecting Cities

Given N cities we need to connect them through a rail network in such a way that the cost of laying out the network is minimum. A city X is connected to city Y if their exist a path between X and Y.


Input Format
First line has two integers N and M ,N denoting the number of cities and M, denoting the number of possible paths between the cities.
The next M lines each consist of three space separated integers x y r, where x and y denote the two cities between which the path can be constructed, r denotes the cost of constructing this path.
Constraints

    2<=N<= 3000
    1<=M<= N*(N-1)/2
    1<=x,y<= N
    0<=r<=10^5 



Output Format
Print a single integer denoting the minimum cost of laying out the network.
Sample Input
4 6
1 2 5
1 3 3
4 1 6
2 4 7
3 2 4
3 4 5

Sample Output
12

Question Setter: Ayush

**/


#include <bits/stdc++.h>
#include <malloc.h>

using namespace std;

int root(int *Root,int u){
	while(u != Root[u]){
		u = Root[u];
	}
	return u;
}

void Union(int *Root,int u, int v){
	int r_u = root(Root,u);
	int r_v = root(Root,v);

	Root[r_v] = r_u;
}

bool Union_find(int *Root, int u, int v){
	return root(Root,u)==root(Root,v); 
}

struct Graph {
	int size;
	priority_queue<pair<int, pair<int, int> >,vector< pair<int, pair<int, int> > >, greater< pair<int, pair<int, int> > > > min_heap;

};

void input_edge(struct Graph *g,int M){
	int x,y,r;
	for(int i=0;i<M;i++){
		cin>>x>>y>>r;
		pair <int,int > p = make_pair(x,y);
		pair <int, pair <int,int > > p1 = make_pair(r,p);

		g->min_heap.push(p1);
	}
		
}

void krsukals(struct Graph *g){
	int size = g->size;
	int *Root = (int *)malloc(sizeof(int)*(size+1));
	for (int i=0;i<=size;i++)
		Root[i] = i;

	priority_queue<pair<int, pair<int, int> >,vector< pair<int, pair<int, int> > >, greater< pair<int, pair<int, int> > > > heap = g->min_heap;
	int count=0;
	int cost=0;
	pair<int, pair<int, int> > min;
	pair<int, int> coord;

	while(!heap.empty() && count != size-1){
		min = heap.top();
		coord= min.second;
		heap.pop();

		if(!Union_find(Root,coord.first,coord.second)){		//are they forming cycle?
			cost += min.first;
			count++;
			Union(Root,coord.first,coord.second);
		}
	}

	cout<<cost<<endl;
}

int main(){
	int N,M;
	cin >>N>>M;
	Graph g;
	g.size=N;
	input_edge(&g,M);
	krsukals(&g);

	return 0;
}