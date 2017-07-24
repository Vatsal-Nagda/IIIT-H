#include <stdio.h>

 int main(){
 	int i,j,t,n;
 	scanf("%d",&t);

 	for(i=0;i<t;i++){
 		scanf("%d",&n);
 		
 		unsigned long int height[n];
 		unsigned long int ans=0;

 		for(j=0;j<n;j++){
 			scanf("%lu",&height[j]);
 		}

 		int small=0,big=0,current=0;

 		while(big < n){
 			while(height[small] < height[small+1])
 				small++;

 			big = small +1;
 			 //printf("Big :%d\n",big );


 			while((height[big] < height[small]) && big < n){
 				big++;
 				//printf("Big :%d\n",big );
 			}
 				

 			//printf("Small :%d    Big : %d\n", small,big);
 			
 			if(big < n){
 				for(current = small+1; current<big; current++){
	 				ans += height[small] - height[current];
	 				//printf("added %lu - %lu\n",height[small],height[current] );
 				}
 			}

 			small = big;
 		}
 	//	printf("%lu\nNow going reverse\n",ans );
 		
 		small = n-1;
 		while(big > 0){
 			while(height[small] < height[small-1])
 				small--;

 			big = small -1;

 			while((height[big] <= height[small]) && big > 0)
 				big--;

 			// printf("Small :%d    Big : %d\n", small,big);

 			if(big > 0){
 				for(current = small-1;current>big;current--){
	 				ans += height[small] - height[current];
	 				//printf("added %lu - %lu\n",height[small],height[current] );
 				}
 			}
 			small = big;
 		}

 		printf("%ld\n",ans );
 	}

return 0;
}