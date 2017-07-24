/***

 Given level order traversal of binary tree, check whether tree is balanced or not.

A binary tree is balanced if:
1) Left subtree is balanced
2) Right subtree is balanced
3) The difference between heights of left and right subtree is less than 2.

Input

    Line 1 : T
    T : Number of test cases

    For each test case,
    Line 1: N
    N : Size of Level Order Traversal
    Line 2: a1 a2 a3 .. aN
    Value of node
    Please note that "-1" indicates NULL.

Output

    True : if tree is balanced
    False : if tree is not balanced

Constraints

    1 <= T <= 1000
    1 <= N <= 106
    -10 8 <= ai <= 109
    ai != -1

Example

Input 1
2
11
1 -2 3 -1 -1 -5 4 -1 -1 -1 -1
7
-10 -3 -1 -2 -1 -1 -1

Output 1
True
False


***/


#include <iostream>
#include <math.h>
#include <vector>
#include <malloc.h>
#include <algorithm>

struct Tree{
	int data;
	struct Tree* left;
	struct Tree* right;
};

bool flag = true;

using namespace std;

int height(struct Tree* root){
	if(root == NULL)
		return -1;

	int left = height(root->left);
	int right = height(root->right);
	int max_height =  max(left,right) +1;

	if(abs(left-right) > 1){
		flag = false;
		// cout<<"Imbalance @ node :"<<root->data<<endl;
	}
	return max_height;
}

void preorder(struct Tree* root){
	if(root != NULL){
		cout<<root->data;
		preorder(root->left);
		preorder(root->right);
	}
}

int main(){

	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;

		flag = true;

		vector < int > level;
		vector < struct Tree* > add;
		
		for(int i=0;i<n;i++){
			int temp_data;
			cin >> temp_data;
			level.push_back(temp_data);
		}

		struct Tree* root = NULL;
		if(level[0] != -1){
			root = (struct Tree*)malloc(sizeof(struct Tree));
			root->data = level[0];
			root->left=root->right = NULL;
			add.push_back(root);					//push new node in vector
		}

		struct Tree* curr=NULL;

		for(int i=1;i<n;){

			if(add.size() != 0){
				curr = add.front();						// pop front of vector
				add.erase(add.begin());	
			}		

			/*if((i+2 < n) && (level[i] == -1 && level[i+1] == -1)){
				i = i+2;
				continue;
			}*/

			if(level[i] != -1){
				struct Tree* node = (struct Tree*)malloc(sizeof(struct Tree));
				node ->data = level[i];
				node->left = node->right = NULL;
				add.push_back(node);
				   // cout<<"New node "<<level[i]<<" created @ left of "<<curr->data<<endl;
				curr->left = node;				
			}
			i++;

			if((i < n) && (level[i] != -1)){
				struct Tree* node = (struct Tree*)malloc(sizeof(struct Tree));
				node ->data = level[i];
				node->left = node->right = NULL;
				add.push_back(node);
				   // cout<<"New node "<<level[i]<<" created @ right of "<<curr->data<<endl;
				curr->right = node;				
			}
			i++;
		}

	 	//preorder(root);
		if(root == NULL){ 
			cout<<"True"<<endl;
		}
		else{
				height(root);

				if(flag == true)
					cout<<"True"<<endl;
				else
					cout<<"False"<<endl;					

		}

		level.clear();
		add.clear();

	}


	return 0;
}