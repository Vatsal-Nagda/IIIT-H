#include <stdio.h>

int main(){
	int s,e,n;
	scanf("%d%d%d",&s,&e,&n);

	int i,si,ei;
	int count=0;
	for(i=0;i<n;i++){
		scanf("%d%d",&si,&ei);

		if(si < s && ei < s)
			count++;
		else if(si > e && ei >e)
			count++;
	}
	printf("%d\n",count );
	return 0;
}
