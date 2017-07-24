#include <stdio.h>

int search(unsigned long int key,unsigned long int arr[]){
	int i=0;
	while(1){
		if(arr[i++] == key)
			break;
	}

	return i;
}

int main(){
	int i,n,m;
	scanf("%d%d",&n,&m);
	unsigned long int chngd [n];

	 for(i=0;i<n;i++){
	 	scanf("%lu",&chngd[i]);
	 }
	 unsigned long int temp;
	 scanf("%lu",temp);		//read first character of O.G.array

	int index =	search(temp,chngd);

	for(i=1;i<n;i++)
		scanf("%lu",&temp;)  //just read input

	char dir,c;
	unsigned long int steps;
	int count =0;

	for(i=0;i<m;i++){

		scanf("%c",&dir);	//R or L
		scanf("%c",&c);		// for space
		scanf("%lu",steps);	// read integer
		scanf("%c",&c);		//read spaces

		if(dir == 'R'){
			index = (index + steps)%n;
			count++;
		}
		else{
			index = (index - steps)%n;
			count++;
		}

		if(index == 0)
			break;

	}
	printf("%d\n",index );

	 return 0;
}
