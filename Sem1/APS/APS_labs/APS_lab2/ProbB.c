/**

Favourite Drink

Shivam loves the famous drink "Pepsi", which can be bought in n different shops in the city. It's known that the price of one bottle in the shop i is equal to xi coins.

He plans to buy his favourite drink for q consecutive days. He knows, that on i-th day he will be able to spend mi coins. Now for each of the days he want to know in how many different shops he can buy a bottle of "Pepsi"?

Input Format:
The first line of the input contains a single integer n (1 ≤ n ≤ 10^5) — the number of shops in the city that sell Shivam's favourite drink.
The second line contains n sorted integers xi (1 ≤ xi≤ 10^9) — prices of the bottles of the drink in the i-th shop. (sorted in non-dcreasing order)
The third line contains a single integer q (1 ≤ q ≤ 10^5) — the number of days Shivam plans to buy the drink.
Next line has q integers mi (1 ≤ mi ≤ 10^9) — the number of coins Shivam can spent on the i-th day.

Output Format:
Print q integers. The i-th of them should be equal to the number of shops where Shivam will be able to buy a bottle of the drink on the i-th day.

Sample Input:
5
3 6 8 11 12
5
1 4 11 8 6

Sample Output:
0
1
4
3
2

Explanation:

Day 1 Shivam has 1 coin only, so he cannot buy Pepsi in any shop

Day 2 Shivam has 4 coins he can buy in the 0th shop

Day 3 Shivam has 11 coins he can buy from first 4 shops

Day 4 Shivam has 8 coins he can buy from first 3 shops

***/


#include <stdio.h>

int shop_search(long int coin, long int shop_price[],int tot_shops){
 	int low =0,high = tot_shops-1,mid;
 //	int count =0;
 	while(low <= high){

 		mid = low +(high-low)/2;

 //		printf("The low ,mid and high right now are %d  %d  %d\n",low,mid ,high);

 		if(shop_price[mid] > coin){
 			high = mid -1;
 		}
 		else {

 			low = mid+1; 			
 		}
 	}

 //	 		printf("The low ,mid and high right now are %d  %d  %d\n",low,mid ,high);


 	return high;
}


int main(){
	int i,n,m,index;
	scanf("%d",&n);

	long int shop_price [n];

	for(i=0;i<n;i++){
		scanf("%ld",&shop_price[i]);
	}

	scanf("%d",&m);

	long int coin;

	for(i=0;i<m;i++){
		scanf("%ld",&coin);
		index = shop_search(coin,shop_price,n);
		printf("%d\n", index+1);
	}

	return 0;
}