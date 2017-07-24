#include <stdlib.h>
#include <iostream>

using namespace std;

void get_working_directory(char **argv){

	char Pre_dir[2500];
	if(getcwd(Pre_dir,sizeof(Pre_dir)) != NULL )
		printf("%s\n",Pre_dir );
	else
		perror("error in present directory command");
}