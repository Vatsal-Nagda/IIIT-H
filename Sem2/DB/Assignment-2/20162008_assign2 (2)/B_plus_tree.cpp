#include <bits/stdc++.h>
#define L 0
#define R 1
#define I 2
using namespace std;
// enum int { L, R, I};
typedef struct BpTreeNode BpTreeNode;
typedef struct BpTreeNode{
	int *keys;
	BpTreeNode **childs;
	int node_type;
	int num_keys;
}BpTreeNode;

BpTreeNode* root = NULL;
int degree_of_BpTree;
BpTreeNode *previous, *next;


BpTreeNode* BpTree_Create();
int Find_Ptr_loc(int k, int* array, int N);
vector<BpTreeNode*> Search_key(int k, BpTreeNode* root);
void Array_store(int temp_array[], BpTreeNode* temp_chilld[], int k_array[], BpTreeNode* s_child[], int N, int key, BpTreeNode* previous, BpTreeNode* next, int t);
int split_add(BpTreeNode* x, int key);
void insertion(int k);
int range(int source, int end);
string find(int k);
void walk_thru_tree(BpTreeNode * root);
int count(int num);
void run_choice(vector <string> queries);


void run_choice(vector <string> queries)
{
	int i=0;
	while(i<queries.size()){
		int strt,end,num;
		istringstream istring(queries[i]);
		string choice;
		istring>>choice;
	

		if(choice == "FIND"){
			istring>>num;
			cout<<find(num)<<endl;
		}
		else if(choice == "COUNT"){			
			istring>>num;
			cout<<count(num)<<endl;
		}		
		else if(choice == "RANGE"){
			istring>>strt>>end;
			cout<<range(strt, end)<<endl;
		}
		else if(choice == "INSERT"){
			istring>>num;
			insertion(num);
		}
		i++;
	}
}


void Array_store(int temp_array[], BpTreeNode* temp_chilld[], int k_array[], BpTreeNode* s_child[], int N, int key_search, BpTreeNode* previous, BpTreeNode* next, int t){
	int m , n, interim_k,interim_c;
	n = interim_c= N;
	m = interim_k = N-1;
	
	while(interim_k >=0 && k_array[interim_k] >key_search){
	
		temp_array[m+1] = k_array[interim_k];	
		interim_k = interim_k -1 ;
		m = m-1;
		if(t != L){
			temp_chilld[n+1] = s_child[interim_c];
			n = n - 1;
			interim_c  = interim_c - 1;
			
		}

	}

	temp_array[m+1] = key_search;
	
	if(t != L){
		temp_chilld[n+1] = next;
		s_child[interim_c] = previous;
	}
	
	while( interim_k >= 0 ){
		temp_array[m] = k_array[interim_k];
		interim_k = interim_k -1;
		m = m-1;

		if(t != L){
			temp_chilld[n] = s_child[interim_c];
			n = n - 1;
			interim_c= interim_c - 1;
			
		}
	}
	if(t != L)
		temp_chilld[n] = s_child[interim_c];
	//cout<<endl;
}

vector<BpTreeNode*> Search_key(int k, BpTreeNode* root){
	vector <BpTreeNode *> trace;	
	BpTreeNode *temp = root;
	trace.push_back(root);

	while(temp->node_type != L){
		int j = Find_Ptr_loc(k, temp->keys, temp->num_keys);
		trace.push_back((BpTreeNode*)temp->childs[j]);
		temp = trace.back();
	}
	return trace;
}

int Find_Ptr_loc(int k, int* array, int num){
	if(num == 0){
		cout<<"Error: BpTreeNode is empty\n\n";
		return -1;
	}
	if(k < array[0])
		return 0;
	else if(k >= array[num-1])
		return num;
	else{
		int i=1;
		while(i < num){
			if( k >= array[i-1] && k < array[i])
				return i;
			i = i+1;
		}
	}
		
	return -1;
}

BpTreeNode* BpTree_Create(){
	BpTreeNode* new_node = (BpTreeNode*)malloc(sizeof(BpTreeNode));
	new_node->keys = (int*)malloc(sizeof(int)*(degree_of_BpTree - 1));
	
	if(new_node->keys == NULL)
		cout<<"No Memory\n"<<degree_of_BpTree -1;
	new_node->num_keys = 0;
	
	new_node->node_type = L;	
	new_node->childs = (BpTreeNode**)malloc(sizeof(BpTreeNode*)*degree_of_BpTree);	
	int j=0;
	while(j < degree_of_BpTree){
		new_node->childs[j] = NULL;
		j = j + 1;
	}
	return new_node;
}


void insertion(int k){
	vector <BpTreeNode *> trace = Search_key(k, root);
	previous = next = NULL;

	bool flag = false;
	do{
		BpTreeNode* temp = trace.back();
		if(temp->num_keys == degree_of_BpTree - 1){
			trace.pop_back();
			k = split_add(temp, k);
			
		}
		else{
			/*Add the Key and Break*/
			Array_store(temp->keys, temp->childs, temp->keys, temp->childs, temp->num_keys, k, previous, next, temp->node_type);
			temp->num_keys = temp->num_keys  + 1;
			flag = true;
		}
	}while(!flag && !trace.empty());
	if(flag == false){
		/*We Have to create a new Root BpTreeNode*/
		root = BpTree_Create();
		root->node_type = I;
		BpTreeNode* temp = root;
		Array_store(temp->keys, temp->childs, temp->keys, temp->childs, temp->num_keys, k, previous, next, temp->node_type);
		temp->num_keys = temp->num_keys +1;
	}
}

int range(int source, int end){
	BpTreeNode* leaf = Search_key(source, root).back();
	int i=0;
	int num_count = 0;
	while( !(i >= leaf->num_keys)){
		if(leaf->keys[i] >= source)
			break;
		i = i+1;
	}
	do{
		while( i<leaf->num_keys && leaf->keys[i] <= end){
			/*Uncomment below to print the elements in range*/
			//cout<<leaf->keys[i]<<" ";
			num_count = num_count+1;
			i = i+1;
		}
		leaf = leaf->childs[degree_of_BpTree -1];
		i = 0;
	}while(leaf != NULL);
	//cout<<endl;
	return num_count;
}

string find(int k){
	BpTreeNode* temp = Search_key(k, root).back();
	int i = 0; 
	while(i < temp->num_keys){
		if(temp->keys[i] == k){
			return "YES";
		}
		i = i+1;
	}
	return "NO";
}


int count(int num){
	BpTreeNode* leaf = Search_key(num, root).back();
	int i=0;
	int num_count = 0;
	while( i<leaf->num_keys){
		if(leaf->keys[i] == num)
			break;
		i = i+1;
	}
	do{
		while(i<leaf->num_keys && leaf->keys[i] == num){
			/*Uncomment below to print the elements in range*/
			//cout<<leaf->keys[i]<<" ";
			num_count = num_count +1;
			i = i+1;
		}
		leaf = leaf->childs[degree_of_BpTree -1];
		i = 0;
	}while(leaf != NULL);
	//cout<<endl;
	return num_count;
}


int split_add(BpTreeNode* x, int key){

	int *ar = (int*)malloc(sizeof(int)*degree_of_BpTree);
	int qw=0;
	BpTreeNode **ptrs = (BpTreeNode**)malloc(sizeof(BpTreeNode*)*(degree_of_BpTree+1));
	qw++;
	Array_store(ar, ptrs, x->keys, x->childs, x->num_keys, key, previous, next, x->node_type);
	x->num_keys = x->num_keys + 1 ;
	qw = qw*2;
	BpTreeNode *np = BpTree_Create();
	int i;
	np->node_type = x->node_type;
	int ex = degree_of_BpTree/2;
	int snp = ex;
	qw = qw/2;
	if(np->node_type != L){
		snp = snp +1 ;
	}
	int k = 0;
	i=0;
	while(i<ex){
		x->keys[k] = ar[i];
		x->childs[k] = ptrs[i];
		i = i+1;
		k = k+1;
	}
	x->num_keys = ex;
	x->childs[k] = ptrs[i];
	
	k = 0;
	i = snp;
	while( i<degree_of_BpTree){
		np->keys[k] = ar[i];
		np->childs[k] = ptrs[i];
		i = i+1;
		k = k+1;
	}
	if(np->node_type == L){
		np->childs[k] = NULL;
	}
	else
		np->childs[k] = ptrs[i];

	np->num_keys = degree_of_BpTree - snp;
	
	if(np->node_type == L){
		np->childs[degree_of_BpTree-1] = x->childs[degree_of_BpTree-1];
		x->childs[degree_of_BpTree-1] = np;
	}
	free(ar);
	free(ptrs);
	previous = x;
	next = np;
	return ar[ex];
}


void walk_thru_tree(BpTreeNode * root){
	/*walk_thru_tree and print the Keys in all the BpTreeNodes*/
	if(root->node_type == L){
		int i=0;
		while(i< root->num_keys){
			cout<<root->keys[i]<<" ";
			i = i+1;
		}
		cout<<endl;
	}
	else{
		int i=0;
		while( i< root->num_keys){
			cout<<root->keys[i]<<" ";
			i = i+1;
		}
		cout<<endl;
		i=0;
		while( i<= root->num_keys){
			walk_thru_tree(root->childs[i]);
			i = i+1;
		}
	}
}


int main(int argc, char *argv[])
{
	if(argc != 4){
		cout<<"Wrong Input\n Corecct format is ";
		cout<<"./a.out file # Blocks BlockSize\n";
		return 0;
	}
	string fileName = string(argv[1]);
	int M = atoi(argv[2]);
	int B = atoi(argv[3]);	
	degree_of_BpTree = (B + 4)/(sizeof(int) + sizeof(void *));
	root = BpTree_Create();

	ifstream istring(fileName.c_str());
	string query;
	vector <string> input;
	
	while(getline(istring, query)){
			input.push_back(query);
			if(input.size() == M-1){
				/*Process the input*/
				run_choice(input);
				input.clear();
			}
	}
	if(input.size() != 0){
		run_choice(input);
	}
	return 0;
}
