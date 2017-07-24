#include <bit/stdc++.h>
#include <iostream>
#include <malloc.h>

using namespace std;

// typedef struct BpTreeNode 

struct BpTreeNode{
	int val;										//		value of the data at this node
	vector<int> *keys;								//		List of keys present at the current node
	vector <struct BpTreeNode*> *childs;				//		vector of pointers to children nodes
	bool isLeaf;									//		Is the current node a leaf node or a non-leaf node
	int num_keys;									//		NO of keys currently stored at the node
};

BpTreeNode* root = NULL;
BpTreeNode* prev, *next;
int degree_of_node;									//		Degree of the Node


bool Search(struct BpTreeNode* root, int search_key){
	int i=0;

	while(i < root->num_keys &&  search_key > root->keys[i]){		//	finding the smallest i such that search_key < keys[i]
		i++;													
	}

	if( i< root->num_keys && search_key == root->keys[i]){
		if(root->isLeaf == true)
			return true;
		else
			return Search(root->childs[i],k);					//always traverse to the leaf node
	}

	if(root->isLeaf == true)
		return false;								//		if the current node is a leaf node then return cz not present here

	// return Search(root->childs[i],k);
}


// struct BpTreeNode* B_Tree_Create(int degree){
// 	struct BpTreeNode* root = (struct BpTreeNode*)malloc(sizeof(struct BpTreeNode));
// 	root->isLeaf = true;
// 	root->min_deg = degree;
// 	root->childs = new vector<struct BpTreeNode*> [2*degree -1];
// 	root->keys = new vector<int> [2*degree-1];
// 	root->num_keys = 0;
// 	return root;
// }


void B_Tree_Split_Child(struct BpTreeNode* parent, int i, struct BpTreeNode *y){	//	splits Y about its median, which is moved up in y's parent 
	
	struct BpTreeNode* z = B_Tree_Create(y->min_deg);			// create a node which will store 1st t-1 keys of y
	z->isLeaf = y->isLeaf;

	z->num_keys = y->min_deg - 1;
	int j=0;
	int t=y->min_deg;
	
	for (j=0;j < t-1;j++){
		z->keys[j] = y->keys[j+t];
	}

	if(y->isLeaf == false){
		for(j=0;j<t;j++){
			z->childs[j] = y->childs[y+t];
		}
	}

	for(j=parent->num_keys;j>=i+1;j--){
		parent->childs[j+1] = parent->childs[j];
	}

	parent->childs[i] = z;				// link new child to parent node

	for(j= parent->num_keys-1;j >= i ;j--)
		parent->keys[j+1] = parent->keys[j];

	parent->keys[i] = y->keys[t-1];
	parent->num_keys += 1;

}

void B_Tree_Insert(struct BpTreeNode** root, int k,int degree){

	if(*root == NULL){						// If tree is empty
		*root = B_Tree_Create(degree);
		root->keys[0] = k;
		root->num_keys = 1;
	}
	else{							// If tree is non empty

		if(root->num_keys == 2*degree - 1){		// root is full, hence tree will grow
			struct BpTreeNode* s = B_Tree_Create(degree);
			s->isLeaf = false;
			s->num_keys = 0;		
			s->childs[0] = *root;	// make old root as child

			B_Tree_Split_Child(s,0,*root);

			int i=0;
			if(s->keys[0] < k)
				i++;

			B_Tree_InsertNonFull(s,k);
			*root = s;
		}
		else
			B_Tree_InsertNonFull(*root,k);
	}

}

BpTreeNode* B_Tree_Create(){
	BpTreeNode *root = (BpTreeNode*)malloc(sizeof(BpTreeNode));
	root->keys = new vector<int> [degree_of_node-1];
	//check if memory overflow
	root->childs = new vector<struct BpTreeNode*> [degree_of_node];
	root->isLeaf = true;
	root->num_keys = 0;
	for(int i=0;i< degree_of_node;i++)
		root->childs[i] = NULL;
	
	return 	root;
}

int main(int argc, char *argv[])
{
	if(argc != 4){
		cout<<"Wrong input\n Correct format is :";
		cout<<"./a.out filepath NoOfBlocks BlockSize\n";
		return 0;
	}
	string fname = string(argv[1]);
	int B = atoi(argv[3]);		//	Buffer size
	int M = atoi(argv[2]);		// 	No of buffers
	degree_of_node = (B-8)/12;

	root = initializeBpTree();

	vector <string> input;
	ifstream is(fname);
	string query;
	while(getline(is, query)){
			in.push_back(query);
			if(in.size() == N-1){
				/*Process the input*/
				run_ip(in);
				in.clear();
			}
	}
	if(in.size() != 0){
		controller(in);
	}
	return 0;
}
