#include <iostream>
#include <stdlib.h>

using namespace std;

void change_dir(char ** argv){

	if(argv[1] == NULL  ||  *argv[1] == '~'){			//to be redirected to  home directory
		if(chdir(getenv("HOME")) == -1){	
			perror("");
		}
	}
	else{
		if(chdir(argv[1]) < 0){		//some incorrect operation
			perror("Incorrect command given");
		}
	}
	setenv("PWD",getcwd(NULL,0),1);
}