#include <stdio.h>
#include <malloc.h>

struct Node{
	int data;
	struct Node *left;
	struct Node *right;
};

void MakeTree(struct Node **root, int value){
	struct Node *prev= NULL;
	struct Node *curr= *root;

	if(*root == NULL){
		*root =  (struct Node*)malloc(sizeof(struct Node));
		(*root)->data = value;
	}
	else{
		while(curr != NULL){
		prev = curr;
		if(value < curr->data )
			curr = curr->left;
		else if(value > curr->data)
			curr = curr->right;
		}

		struct Node *new = (struct Node*)malloc(sizeof(struct Node));
		new->data = value;	

		if(value > prev->data)
			prev->right = new;
		else
			prev->left = new;
	}
}

void preorder(struct Node* root){
	if (root != NULL){
		preorder(root->left);
		printf("%d ",root->data );
		preorder(root->right);
	}
}

int pappa(struct Node* root, int P, int Q){

	while(root != NULL){
		if((root->data == P) || (root->data == Q) || ((root->data > P) && (root->data < Q)) || ((root->data > Q) && (root->data < P)) )
			break;//return root->data;
		else if((root->data > P) &&(root->data > Q))
			root = root->left;
		else if((root->data < P) &&(root->data < Q))
			root = root->right;
	}

	return root->data;
}


int main(){
	int t;
	scanf("%d",&t)	;

	while(t--){

		int n,q;
		scanf("%d%d",&n,&q);

		int* blocks = (int*)malloc(sizeof(int)*n);

		int i;
		for(i=0;i<n;i++){
			scanf("%d",&blocks[i]);
		}

		struct Node *root = NULL;

		for(i=0;i<n;i++){
			MakeTree(&root,blocks[i]);
		}

	//	preorder(root);
		int P,Q;

		for(i=0;i<q;i++){
			scanf("%d%d",&P,&Q);
			printf("%d\n", pappa(root,P,Q));
		}

	}

	return 0;
}