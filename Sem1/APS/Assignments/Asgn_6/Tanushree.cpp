#include <iostream>
#include <stack>
#include <algorithm>
//#include <uti11l>
using namespace std;

struct rect{
	int length;
	int breadth;
	int area;
};

bool compare( struct rect p1,struct rect p2){
	return (p1.area > p2.area);
}

int main(){

	int t;
	cin>>t;

	while(t--){
		int n;
		cin>>n;
		
		struct rect ordr [n];
		int inside_other[n];

		for(int i=0;i<n;i++)
			inside_other[i]=1;

		for(int i=0;i<n;i++){
			int l,b;
			cin>>l>>b;
			ordr[i].length=l;
			ordr[i].breadth=b;
			ordr[i].area = l*b;
		}

		sort(ordr,ordr+n,compare);

		int max=0;
		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(ordr[i].length < ordr[j].length &&  ordr[i].breadth < ordr[j].breadth ){
					if(inside_other[i] < inside_other[j]+1)
						inside_other[i] = inside_other[j]+1;
				}
			}
		}

		for(int i=0;i<n;i++)
			if(inside_other[i] > max)
				max = inside_other[i];

		cout<<max<<endl;
	}
	
	return 0;
}