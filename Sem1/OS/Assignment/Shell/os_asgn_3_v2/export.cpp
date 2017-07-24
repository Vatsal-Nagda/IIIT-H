#include <string>
#include <iostream>

using namespace std;

void do_export(char** argv){
	if(setenv(argv[1],argv[3],1) < 0){
		perror("");
	}
}