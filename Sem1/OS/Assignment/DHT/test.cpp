#include "ip-test.cpp"
#include "hash.cpp"
#include <iostream>
#include <string>

using namespace std;

int main(){

	cout<<"Hash for ip is : "<<hash_value(find_ip_addr());
	return 0;
}