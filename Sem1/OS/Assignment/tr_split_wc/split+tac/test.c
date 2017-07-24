//#include <syscalls.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char*argv[]){
	int i=0,input_fd,output_fd;
	ssize_t len_in =0;//,len_out=0;
	char buffer [1];
	//char op_buff [1];

	input_fd = open(argv[1],O_RDONLY);
	output_fd = open(argv[2], O_RDWR | O_CREAT, 0777);
	
	int temp =0;
	i=0;
	while((len_in = read (input_fd, &buffer,1)) > 0){
		//while(buffer[i] != EOF){
			if(buffer[i] == '\n')
				temp ++;
			write(output_fd,&buffer,1);	
			//printf("%c",buffer[i] );
				//i++;
			if(temp == 3){
					//create new file and write there
				//close(output_fd);
				//output_fd = open();
				temp =0;
				printf("after 20 lines\n");
				char str[20];
				int hours = 16;
				sprintf(str, "%d:%02d", hours, 5);
				printf("%s\n",str );
			}
	}
	/*
	while((len = read(0,buffer,16) > 0)(c= getchar())!= EOF){
		while(buffer[i] != EOF)
			printf("%c",(char)buffer[i++]);
			//write(1,buffer,16);
	}*/
	return 0;
}