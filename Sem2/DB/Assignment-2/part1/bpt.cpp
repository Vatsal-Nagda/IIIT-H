/*
 * btp.cpp
 *
 *  Created on: 04-Mar-2017
 *      Author: gaurav
 */
#include <bits/stdc++.h>

using namespace std;
enum ntype { L, R, I};
typedef struct node Node;
typedef struct node{
	ntype type;
	int n;
	int *keys;
	Node **child_ptr;
}Node;

Node* root = NULL;
int order;
Node *prev, *nxt;

Node* initialize(){
	Node* np = (Node*)malloc(sizeof(Node));
	np->keys = (int*)malloc(sizeof(int)*(order - 1));
	if(np->keys == NULL)
		cout<<"Out of Memory\n"<<order -1;
	np->child_ptr = (Node**)malloc(sizeof(Node*)*order);
	np->type = L;
	np->n = 0;
	for(int i=0; i<order; i++){
		np->child_ptr[i] = NULL;
	}
	return np;
}
int getPtrLocation(int k, int* arr, int N){
	if(N == 0){
		cout<<"Error: Node is empty\n\n";
		return -1;
	}
	if(k >= arr[N-1])
		return N;
	else if(k < arr[0])
		return 0;
	else
		for(int i = 1; i<N; i++){
			if( k >= arr[i-1] && k < arr[i])
				return i;
		}
	return -1;
}
vector<Node*> Search(int k, Node* root){
	vector <Node *> stack;
	stack.push_back(root);
	Node *x = root;
	while(x->type != L){
		int i = getPtrLocation(k, x->keys, x->n);
		stack.push_back((Node*)x->child_ptr[i]);
		x = stack.back();
	}
	return stack;
}
void insertInArray(int tk[], Node* tc[], int sk[], Node* sc[], int N, int key, Node* prev, Node* nxt, ntype t){
	int m , n, ik, ic;
	m = ik = N-1;
	n = ic= N;
	while(ik >=0 && sk[ik] >key){
		tk[m+1] = sk[ik];
		m--;
		ik--;
		if(t != L){
			tc[n+1] = sc[ic];
			ic--;
			n--;
		}

	}
	tk[m+1] = key;
	if(t != L){
		tc[n+1] = nxt;
		sc[ic] = prev;
	}
	while(ik>=0){
		tk[m] = sk[ik];
		m--;
		ik--;
		if(t != L){
			tc[n] = sc[ic];
			ic--;
			n--;
		}
	}
	if(t != L)
		tc[n] = sc[ic];
	for(int i = 0; i<=N; i++){
		//cout<<tk[i]<<" ";

	}
	//cout<<endl;
}
int split_add(Node* x, int key){
	int *ar = (int*)malloc(sizeof(int)*order);
	Node **ptrs = (Node**)malloc(sizeof(Node*)*(order+1));
	insertInArray(ar, ptrs, x->keys, x->child_ptr, x->n, key, prev, nxt, x->type);
	x->n++;
	Node *np = initialize();
	np->type = x->type;
	int i;
	int ex = order>>1;
	int snp = ex;
	if(np->type != L){
		snp++;
	}
	int k = 0;
	for(i = 0; i<ex; i++, k++){
		x->keys[k] = ar[i];
		x->child_ptr[k] = ptrs[i];
	}
	x->child_ptr[k] = ptrs[i];
	x->n = ex;
	k = 0;
	for(i = snp; i<order; i++, k++){
		np->keys[k] = ar[i];
		np->child_ptr[k] = ptrs[i];
	}
	if(np->type == L){
		np->child_ptr[k] = NULL;
	}
	else
		np->child_ptr[k] = ptrs[i];
	np->n = order - snp;
	if(np->type == L){
		np->child_ptr[order-1] = x->child_ptr[order-1];
		x->child_ptr[order-1] = np;
	}
	free(ar);
	free(ptrs);
	prev = x;
	nxt = np;
	return ar[ex];
}

void insertion(int k){
	prev = nxt = NULL;
	vector <Node *> stack = Search(k, root);
	bool flag = false;
	do{
		Node* x = stack.back();
		if(x->n == order - 1){
			k = split_add(x, k);
			stack.pop_back();
		}
		else{
			/*Add the Key and Break*/
			insertInArray(x->keys, x->child_ptr, x->keys, x->child_ptr, x->n, k, prev, nxt, x->type);
			x->n++;
			flag = true;
		}
	}while(!flag && !stack.empty());
	if(flag == false){
		/*We Have to create a new Root Node*/
		root = initialize();
		root->type = I;
		Node* x = root;
		insertInArray(x->keys, x->child_ptr, x->keys, x->child_ptr, x->n, k, prev, nxt, x->type);
		x->n++;
	}
}
string find(int k){
	Node* leaf = Search(k, root).back();
	for(int i = 0; i<leaf->n; i++){
		if(leaf->keys[i] == k){
			return "YES";
		}
	}
	return "NO";
}
int range(int s, int e){
	Node* leaf = Search(s, root).back();
	int i;
	int count = 0;
	for(i = 0; i<leaf->n; i++){
		if(leaf->keys[i] >= s)
			break;
	}
	do{
		for(; i<leaf->n && leaf->keys[i] <= e; i++){
			/*Uncomment below to print the elements in range*/
			//cout<<leaf->keys[i]<<" ";
			count++;
		}
		leaf = leaf->child_ptr[order -1];
		i = 0;
	}while(leaf != NULL);
	//cout<<endl;
	return count;
}
void traverse(Node * root){
	/*Traverse and print the Keys in all the nodes*/
	if(root->type == L){
		for(int i = 0; i< root->n; i++){
			cout<<root->keys[i]<<" ";
		}
		cout<<endl;
	}
	else{
		for(int i = 0; i< root->n; i++){
					cout<<root->keys[i]<<" ";
		}
		cout<<endl;
		for(int i=0; i<= root->n; i++){
			traverse(root->child_ptr[i]);
		}
	}
}
void controller(vector <string> queries)
{
	for(int i =0; i<queries.size(); i++){
		istringstream iss(queries[i]);
		string t;
		iss>>t;
		if(t == "INSERT"){
			int k;
			iss>>k;
			insertion(k);
		}
		else if(t == "COUNT"){
			int k;
			iss>>k;
			cout<<range(k, k)<<endl;
		}
		else if(t == "FIND"){
			int k;
			iss>>k;
			cout<<find(k)<<endl;
		}
		else if(t == "RANGE"){
			int a, b;
			iss>>a>>b;
			cout<<range(a, b)<<endl;
		}
	}
}
int main(int argc, char *argv[])
{
	if(argc != 4){
		cout<<"Correct Input Format\n";
		cout<<"./a.out filepath NoOfBlocks BlockSize\n";
		return 0;
	}
	char* fname = argv[1];
	int bSize = atoi(argv[3]);
	int N = atoi(argv[2]);
	order = (bSize + sizeof(int))/(sizeof(int) + sizeof(void *));
	root = initialize();

	vector <string> in;
	ifstream is(fname);
	string query;
	while(getline(is, query)){
			in.push_back(query);
			if(in.size() == N-1){
				/*Process the input*/
				controller(in);
				in.clear();
			}
	}
	if(in.size() != 0){
		controller(in);
	}
	return 0;
}
