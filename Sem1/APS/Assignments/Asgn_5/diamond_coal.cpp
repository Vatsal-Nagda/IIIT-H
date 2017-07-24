#include <iostream>

using namespace std;

int n,m;

void DFS(int **mat,int i,int j){

	mat[i][j] = 0;

	if((i > 0) && (mat[i-1][j] == 1)){		//up
		DFS(mat,i-1,j);
	}
	if((j > 0) && (mat[i][j-1] == 1)){		//left
		DFS(mat,i,j-1);
	}
	if((i+1 < n)  && (mat[i+1][j] == 1)){		//down
		DFS(mat,i+1,j);
	}		
	if((j+1 < m) && (mat[i][j+1] == 1)){		//right
		DFS(mat,i,j+1);
	}

}

int main(){	
	cin>>n>>m;

	int** mat;
	mat = new int* [n];
	char c;
	for(int i=0;i<n;i++)
		mat[i] = new int [m];

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			cin>>c;
			mat[i][j] = c-'0';
		}
			
	
	int count=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if (mat[i][j] == 1){
				DFS(mat,i,j);				
				count++;
			}
		}
	}

	cout<<count<<endl;

	for(int i=0;i<n;i++)
		delete [] mat[i];
	delete mat;
	return 0;
}
