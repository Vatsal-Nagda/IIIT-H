#include <string>
#include <iostream>

using namespace std;

int main(){
	string str = "No mirrors available now";
	size_t found = str.find("No mirrors");

	if(found != std::string::npos){
		cout<<"No Mirrors available"<<endl;
	}
	else
		cout<<"Ample mirrors\n";

	return 0;
}