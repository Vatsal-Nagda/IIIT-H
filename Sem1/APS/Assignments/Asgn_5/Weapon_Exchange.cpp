#include <bits/stdc++.h>
#define MODULUS 1000000007

using namespace std;

long long Union_Find(long long *Root, long long u){		//path compression
	
	if (Root[u] != u)
		Root[u] = Union_Find(Root,Root[u]);
	return Root[u];
}

void Union(long long *Root,long long *Rank,long long u, long long v){
	long long r_u = Union_Find(Root,u);
	long long r_v = Union_Find(Root,v);

	if(Rank[r_u] > Rank[r_v]){
		Root[r_v] = r_u;
	}
	else if(Rank[r_u] < Rank[r_v]){
		Root[r_u] = r_v;
	}
	else{	//same rank
		Root[r_v] = r_u;
		Rank[r_u]++;
	}
}

long long factorial(long long n){
	long long fact=1;
	for(long long i=1;i<=n;i++)
		fact = ((fact)%MODULUS*i)%MODULUS;
	return fact;
}

int main(){

	long long N,C;
	cin >>N>>C;
	map <long long , long long > hash_verteices;
	long long Root[N];
	long long Rank[N];
	
	for(long long i=0;i<N;i++){
		Root[i] = i;
		Rank[i] = 0; 
	}		

	long long x,y;
	for(long long i=0;i<C;i++){
		cin>>x>>y;
		if(x != y)
			Union(Root,Rank,x,y);
	}

	for(long long i=0;i<N;i++){
		x = Union_Find(Root,i);
		  // cout<<"i : "<<i<<" root(i) :"<<x<<endl;
		if(hash_verteices.find(x) != hash_verteices.end())
			hash_verteices[x] ++;
		else
			hash_verteices[x] = 1;
	}

	map <long long ,long long > ::iterator map_itr;
	long long answer=1;
	long long val;
	for(map_itr=hash_verteices.begin();map_itr != hash_verteices.end();map_itr++){
		val = map_itr->second;
		answer = (answer%MODULUS *factorial(val)%MODULUS)%MODULUS;
		 // cout<<"Key :"<<map_itr->first<<" Value : "<<map_itr->second<<endl;
	}

	cout<<answer<<endl;
	return 0;
}