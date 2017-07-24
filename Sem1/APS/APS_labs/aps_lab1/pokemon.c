#include <stdio.h>
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

int main(){
	int i,j,t,n;
	scanf("%d",&t);
	int arr[1000001];	
	//int temp;
	for(i=0;i<t;i++){
		scanf("%d",&n);
		//int flag =0;
		/*int ar_p[1000001]={0};
		int ar_n[1000001]={0};*/

		for(j=0;j<n;j++)
			scanf("%d",&arr[j]);

			/*if(temp >= 0)
				ar_p[temp]++;
			else{
				ar_n[-(temp)]++;
			}*/
		
		mergeSort(arr, 0, n-1);

	/*	for(j=0;j<n;j++)
			printf("%d",arr[j]);*/


		for(j=0;j<n;j++){
			if((arr[j] == arr[j+1] && arr[j+1] == arr[j+2]))
				j+=2;
			else{
				printf("%d\n",arr[j] );
				break;
			}
		}
		/*for(j=0;j<1000001;j++){
			if(ar_p[j] %3 != 0){
				printf("%d",j);
				break;
			}
			else if(ar_n[j] %3 != 0){
				printf("%d",(-1*j));
				break;	
			}
		}*/

		/*for(i=0;i<20;i++){
		printf("%d is %d times\n",i,ar_p[i]);
		printf("%d is %d times\n",(-i),ar_n[i]);
	}*/

	}


	return 0;
}