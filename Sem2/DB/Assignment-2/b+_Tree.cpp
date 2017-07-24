#include <bit/stdc++.h>
#include <iostream>

using namespace std;

struct TreeNode{
	int val;										//		value of the data at this node
	vector<int> keys;								//		List of keys present at the current node
	vector <struct TreeNode*> childs;				//		vector of pointers to children nodes
	bool isLeaf;									//		Is the current node a leaf node or a noon-leaf node
	int num_keys;									//		NO of keys currently stored at the node
	int min_deg;									//		Minimum Degree of the Node

};

bool Search(struct TreeNode* root, int search_key){
	int i=1;

	while(i <= root->num_keys &&  search_key > root->keys[i]){		//finding the smallest i such that search_key < keys[i]
		i++;													
	}
}

int main(){



	return 0;
}