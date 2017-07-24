#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct trie{
	
	struct trie *arr [10];
	char terminated;	
};

int main(){
	
	int t;
	scanf("%d",&t);	

	while(t--){

		struct trie *root = (struct trie*)malloc(sizeof(struct trie));
		int i,flag=0;
		for(i=0;i<10;i++)
			root->arr[i] = NULL;
			//root->terminated ='';
		//root.arr = (int *) malloc(sizeof(int)*10)
		struct trie *current ;

		int j,n;
		scanf("%d",&n);

		for(j=0;j<n;j++){
			int flag_1 = 0;		//no new node created

			char *str = (char *)malloc(sizeof(char)*100001);
			scanf("%s",str);

			int len = strlen(str);
			current = root;

			for(i=0;i<len;i++){

				char c = str[i];
				if(current->arr[c-'0'] == NULL){
					struct trie *node = (struct trie*)malloc(sizeof(struct trie));
					node->terminated = 'n';
					current->arr[c-'0'] = node;
					current = node;
					flag_1 = 1;		//new node created

					 // printf("Created node %c\n",c );
				}
				else{
					current = current->arr[c-'0'];
					 // printf("traversed node %c\n", c);
				}

				if(current->terminated == 'y'){
					flag = 1;
					// printf("NO\n");
					break;
				}
			}

			if(i==len && flag_1== 1)
				current->terminated = 'y';			
			else if(i==len && flag_1== 0)
				flag = 1;

			free(str);
		}

		if(flag == 0)
			printf("YES\n");
		else
			printf("NO\n");

		free(root);
	}
	
	return 0;
}