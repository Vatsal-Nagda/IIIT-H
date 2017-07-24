#include <iostream>
#include <algorithm>
#include <malloc.h>

using namespace std;

struct AVLTree{
	int data;
	AVLTree* left;
	AVLTree* right;
	int height;
};

typedef struct AVLTree* Position;
typedef struct AVLTree* Tree;

int Height(Position P){
	if(P == NULL){
		return -1;
	}
	else
		return P->height;
}

/***********************       SINGLE ROTATE LEFT FUNCTION        ******************************************/

Position SingleRotateLeft(Position K2){

	Position K1 = K2->left;
	K2->left = K1 ->right;
	K1->right = K2;

	K2->height = max(Height(K2->left),Height(K2->right)) +1;
	K1->height = max(Height(K1->left),Height(K1->right)) +1;

	return K1;
}

/***********************       SINGLE ROTATE RIGHT FUNCTION        *****************************************/

Position SingleRotateRight(Position K1){

	Position K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1 ;
	
	K2->height = max(Height(K2->left),Height(K2->right)) +1;
	K1->height = max(Height(K1->left),Height(K1->right)) +1;

	return K2;
}

/***********************       DOUBLE ROTATE LEFT FUNCTION        ******************************************/

Position DoubleRotateLeft(Position K3){
	K3->left = SingleRotateRight(K3->left);
	return SingleRotateLeft(K3);
}


/***********************       DOUBLE ROTATE RIGHT FUNCTION        *****************************************/

Position DoubleRotateRight(Position K1){
	K1->right = SingleRotateLeft(K1->right);
	return SingleRotateLeft(K1);
}



bool flag_insert = true;
bool flag_delete = true;

/***********************       INSERT FUNCTION        ******************************************************/

Tree Insert(int X, Tree T){
	if(T == NULL){
		T = (struct AVLTree*)malloc(sizeof(struct AVLTree));

		if(T == NULL){
			// no memory
			flag_insert = false;
		}
		else{				
			T->data = X;
			T->left = T->right = NULL;
			T->height= 0;	
		}
	}
	else 
		if(X < T->data){
			T->left = Insert(X,T->left);

			if(Height(T->left) - Height(T->right) == 2){	//imbalance occurs on left side
				if(X < T->left->data)
					T= SingleRotateLeft(T);
				else
					T=DoubleRotateLeft(T);
			}
		}
		else if(X > T->data){
			T->right = Insert(X,T->right);

			if(Height(T->right) - Height(T->left) == 2){		//imbalance occurs on right side
				if(X > T->right->data)
					T= SingleRotateRight(T);
				else
					T = DoubleRotateRight(T);
			}
		}
		else{
			//already in the tree
			flag_insert = false;
		}
	
	T->height = max(Height(T->left),Height(T->right)) +1;
	return T;	
}

Tree Search(int data,Tree root){
	if(root == NULL)
		return NULL;
	else if(data < root->data)
		return Search(data,root->left);
	else if(data > root->data)
		return Search(data,root->right);
	//else if(data == root->data)
		return root;
}

int Height_Node(int data, Tree T){
	Tree temp = Search(data,T);
	if(temp == NULL)
		return -1;
	else
		return Height(temp);
}


int main(){

	int n;
	cin>>n;

	struct AVLTree *root = NULL;

	while(n--){
		char option;
		cin >>option;
		int data;
		cin >>data;

		flag_insert = flag_delete = true;

		if (option == 'I'){
			root = Insert(data,root);
			if(flag_insert == true)
				cout <<"true"<<endl;
			else
				cout<<"false"<<endl;
		}
		else if(option == 'H'){
			cout<<Height_Node(data,root);
		}

		//fflush(cin);
	}
	return 0;
}