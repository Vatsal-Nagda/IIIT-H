//============================================================================
// Name        : Hash.cpp
// Author      : Vatsal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <stdio.h>
using namespace std;

vector < int > final_data;

int cal_hash(int x,int n){
	int temp = pow(2,ceil(log2(n)));
	while(x < 0)
		x = x + temp;
	// cout<<"cal_hash "<<x<<" "<<n<<" "<<temp<<" "<<x%temp<<endl;
	return x % temp;
}

int flip(int a){
	int i = ceil(log2(a));
	return (a - pow(2,i-1));
}


void reshuffle(vector <vector< int > > &Buckets, int *n, vector<int> &data_till_now){
	Buckets.clear();
	*n = *n+1;

	Buckets.resize(*n);
	// cout<<"New size "<<*n<<endl;
	// cout<<"All the inputs till now"<<endl;
	int length = data_till_now.size();
	for(int i=0;i<length;i++){
		int itr = data_till_now[i];
		
		//check if not a duplicate
		int m = cal_hash(itr,*n);

		if( m >= *n)
			m = flip(m);
		// bool flag = false;
		
		// cout<<itr<<" "<<m<<endl;

		if(find(Buckets[m].begin(),Buckets[m].end(),itr) == Buckets[m].end()){
			// cout<<"just in reshuffle"<<" "<<itr<<" "<<m<<" "<<*n<<endl;
			Buckets[m].push_back(itr);
			// cout<<itr<<" "<<m<<endl;
		}

	}

	// //cout<<"Buckets contents : "<<endl;
	// for(int s=0;s< *n;s++){
	// 	//cout<<s<<" ";
	// 	int len = Buckets[s].size();
	// 	for(int j=0;j<len;j++)
	// 		//cout<<Buckets[s][j]<<" ";
	// 	//cout<<endl;
	// }


}

void calculate_adjust_hash( vector <vector< int > > &Buckets,vector< int > &data_till_now,int B, int a, int *n, int *r){
	data_till_now.push_back(a);
	int ro = B/4;
	int m = cal_hash(a,*n);

	if( m >= *n)
		m = flip(m);

	if(find(Buckets[m].begin(),Buckets[m].end(),a) == Buckets[m].end()){
		// cout<<a<<endl;
		// cout<<"Bucket index "<<m<<" n: "<<*n<<endl;
		*r = *r + 1;
		// cout<<"occupancy "<<(*r)/float(ro*(*n))<<endl;
		Buckets[m].push_back(a);
		final_data.push_back(a);
	}

	if((*r)/float(ro*(*n)) > 0.75){
		// cout<<"Going to reshuffle"<<endl;
		reshuffle(Buckets,n,data_till_now);
	}

}

void Hashing(string fileName,int M,int B){
	int n = 2;
	int r= 0;
	vector < vector < int > > Buckets (n);
	vector< int > data_till_now;

	Buckets.clear();


	ifstream infile(fileName.c_str());
	int a;
	while(infile >> a){
		calculate_adjust_hash(Buckets,data_till_now,B,a,&n,&r);
	}

	infile.close();


	// //cout<<"Buckets contents : "<<endl;
	// for(int s=0;s<n;s++){
	// 	//cout<<s<<" ";
	// 	int len = Buckets[s].size();
	// 	for(int j=0;j<len;j++)
	// 		//cout<<Buckets[s][j]<<" ";
	// 	//cout<<endl;
	// }

	ofstream outfile;
   	outfile.open("output.txt");

	int len = final_data.size();

	for(int i =0;i<len;i++){
		outfile<< final_data[i]<<endl;
	}

	outfile.close();
}


int main(int argc, char const *argv[])
{
	if ( argc != 4){
		cout<<"Argument format ./a.out filename M B"<<endl;
		//to exit function
	}

	string fileName = string(argv[1]);
	int M = atoi(argv[2]);
	int B = atoi(argv[3]);

	Hashing(fileName,M,B);

	return 0;
}
