#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int dir_check(char *src_path){
	struct stat buffer;
	return stat(src_path,&buffer);
}

int main(int argc, char*argv[]){

	char *op_filename = (char *)malloc(sizeof(strlen(argv[1])*2));

	int i,j=0;

	for(i=0;i<strlen(argv[1]);i++){
		if(argv[1][i] != '/'){
			op_filename[j++] = argv[1][i];
		}
		else{
			//printf("%s\n",op_filename );
			op_filename[j++] = '/';
			//if(dir_check(op_filename) != 0){  //directory does not exists
				mkdir(op_filename,0777);
				//printf("%s\n",op_filename );
			//}
			
		}
	}
			op_filename[j++] = '/';
			mkdir(op_filename,S_IRWXU);
}