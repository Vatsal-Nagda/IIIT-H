#include <stdio.h>

int main(){
	int i,j,n,m,t;
	scanf("%d",&t);

	for(i=0;i<t;i++){
		scanf("%d%d",&n,&m);

		int arr[n];
		for(j=0;j<n;j++){
			scanf("%d",&arr[j]);
		}

		int max_count=0,min_money=0,count=0,money_left=m,money_spent=0;

		for(j=0;j<n;j++){

			if(arr[j] > m){
				money_left = m;
				count = 0;
				continue;
			}

			money_left -= arr[j];

			if(money_left >= 0)
				count++;
			else{
				/*money_left = m;
				money_left -= arr[j];
				count =1;*/
				while(money_left < 0){
					money_left += arr[j-count];
					count--;

					//printf("Leaving %d\n",arr[j-count] );
				}
				count++;

			}			

			if(count >= max_count){

				money_spent = m - money_left;

				if(count > max_count)
					min_money = money_spent;

				max_count = count;

				if(money_spent < min_money)
					min_money = money_spent;				
			}

				printf("cost:%d \tMoney_left :%d \tcount :%d \tmoney_spent :%d \t min_money :%d\n",arr[j],money_left,count,money_spent,min_money );

		}
		printf("%d %d\n",min_money,max_count);

	}

	return 0;
}