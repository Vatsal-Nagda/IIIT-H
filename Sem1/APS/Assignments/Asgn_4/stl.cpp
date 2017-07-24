#include <stdio.h>
#include <iostream>

using namespace std;

template <typename T>
T add(T a,T b){
	return a+b;
}

int main(){
	
	cout <<add(5,6)<<endl;
	cout <<add(5.6,7.9)<<endl;
	return 0;	
}