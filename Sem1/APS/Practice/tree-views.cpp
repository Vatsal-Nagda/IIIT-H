#include <iostream>
#include <map>
#include <vector>
#include <malloc.h>

using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
};

void preorder(struct Node *root,int column,map<int, vector<int> > &lvl){

	if(root !=NULL){
		lvl[column].push_back(root->data);
		preorder(root->left,column-1,lvl);
		preorder(root->right,column+1,lvl);	
	}
}

int main(){

	struct Node *root= (struct Node*)malloc(sizeof(struct Node));
	root->data=1;
	root->left = (struct Node*)malloc(sizeof(struct Node));
	root->left->data = 2;
	root->right= (struct Node*)malloc(sizeof(struct Node));
	root->right->data = 7;
	root->left->left= (struct Node*)malloc(sizeof(struct Node));
	root->left->left->data=3;
	root->left->right= (struct Node*)malloc(sizeof(struct Node));
	root->left->right->data=4;
	root->right->left= (struct Node*)malloc(sizeof(struct Node));
	root->right->left->data=5;
	root->right->right= (struct Node*)malloc(sizeof(struct Node));
	root->right->right->data=8;
	root->right->left->left= (struct Node*)malloc(sizeof(struct Node));
	root->right->left->left->data=6;
	root->right->left->left->left= (struct Node*)malloc(sizeof(struct Node));
	root->right->left->left->left->data=9;
	root->right->left->left->left->left= (struct Node*)malloc(sizeof(struct Node));
	root->right->left->left->left->left->data=10;

	map<int, vector<int> > lvl;

	preorder(root,0,lvl);

	map<int, vector<int> > ::iterator map_itr;

	cout<<"vertical order\n";
	for(map_itr=lvl.begin();map_itr!= lvl.end();map_itr++){
		 vector<int> ::iterator vec_itr;
		 for(vec_itr=map_itr->second.begin();vec_itr!=map_itr->second.end();vec_itr++)
		 	cout<<*vec_itr<<" ";
		 cout<<"\n"		;
	}

	cout<<"Top view\n";
	for(map_itr=lvl.begin();map_itr!= lvl.end();map_itr++){
		 vector<int> ::iterator vec_itr=map_itr->second.begin(); 
		 	cout<<*vec_itr<<" ";
	}

	cout<<"\nBottom view\n";
	for(map_itr=lvl.begin();map_itr!= lvl.end();map_itr++){
		 vector<int> ::reverse_iterator vec_itr=map_itr->second.rbegin(); 
		 	cout<<*vec_itr<<" ";
	}
	return 0;
}