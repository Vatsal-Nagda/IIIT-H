#include <iostream>

using namespace std;

int H,W;
int count;
int max_count;

void DFS(char **cities,int i,int j){
	int k;
	count++;
	if(count > max_count)
		max_count= count;

	if(cities[i][j] == 'Z'){
		max_count=26;
		return;
	}
		

//same row
	k=i;
	if((j-1 >= 0) && (cities[k][j-1] == cities[i][j] +1)){
		DFS(cities,k,j-1);
	}	// left
		
	if((j+1 < W) &&(cities[k][j+1] == cities[i][j] +1)){
		//cout<<"same row right\n";
		DFS(cities,k,j+1);
		//cout<<count<<endl;
	}	// right
		

	if(i-1 >= 0){		//upper row
		k=i-1;
		if((j-1 >= 0) && (cities[k][j-1] == cities[i][j] +1) ){
			DFS(cities,k,j-1);
		}	//upper left
			
		if((j+1 < W) &&(cities[k][j+1] == cities[i][j] +1)){
			DFS(cities,k,j+1);
		}	//upper right
			
		if(cities[k][j] == cities[i][j]+1){
			DFS(cities,k,j);
		}		//upper			
	}
	
	if(i+1 < H){		//lower row
		k=i+1;
		if((j-1 >= 0) && (cities[k][j-1] == cities[i][j] +1)){
			DFS(cities,k,j-1);
		}	//lower left
			
		if((j+1 < W) &&(cities[k][j+1] == cities[i][j] +1)){
			DFS(cities,k,j+1);
		}	//lower right
			
		if(cities[k][j] == cities[i][j]+1){
			DFS(cities,k,j);
		}		//lower			
	}

	count--;
	cities[i][j] ='1';		
}

int main(){
	cin>>H>>W;

	while (H !=0 && W!=0){
		char **cities;
		cities = new char*[H];
		for(int i=0;i<H;i++)
			cities[i] = new char[W];

		for (int i=0;i<H;i++)
			for(int j=0;j<W;j++)
				cin>>cities[i][j];

		count=max_count=0;
		for(int i=0;i<H;i++){
			for(int j=0;j<W;j++){
				count=0;
				if(cities[i][j] =='A')
					DFS(cities,i,j);

				if(max_count == 26)
					break;
			}				
		}

		cout<<max_count<<endl;

		for(int i=0;i<H;i++)
			delete [] cities[i];
		delete [] cities;
		cin>>H>>W;
	}

	return 0;
}