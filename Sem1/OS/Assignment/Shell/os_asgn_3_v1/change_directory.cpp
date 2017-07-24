#include <iostream>
#include <stdlib.h>

using namespace std;

void change_dir(char ** argv){

	if(argv[1] == NULL){			//to be redirected to  home directory
		chdir(getenv("HOME"));
	}
	else{
		if(chdir(argv[1]) < 0){		//some incorrect operation
			perror("Incorrect command given");
		}
	}
}