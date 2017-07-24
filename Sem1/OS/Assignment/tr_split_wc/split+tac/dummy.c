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

void split(char *src_dir,int lines){
	DIR *dp;
	struct dirent *ep;
	char *file_path = (char *)malloc(sizeof(strlen(src_dir))); 		//file path of file to b opened
	char *op_filename = (char *)malloc(sizeof(strlen(file_path)));
	char *ip_filename = (char *)malloc(sizeof(strlen(file_path)));
	//char tac_buffer[lines][1000];
	//printf("src_dir :%s\n", src_dir);
	//*file_path = *src_dir;
	dp = opendir(src_dir);

	if(dp != NULL){
		while((ep = readdir(dp))!=NULL){			//reading a file
			
			if(strcmp(ep->d_name,".")== 0 || strcmp(ep->d_name,"..")== 0)
				continue;

			if( ep->d_type == DT_REG){       //if it is a regular file then
				int i=1,k=0;					// file numbr counter
				int l,m;
				int temp=0,flag=0;					//no of iines counter
				
				strcpy(file_path,src_dir);
				strcat(file_path,ep->d_name);
				
				printf("file_path :%s\tDirectory :%s\n",file_path,src_dir );
				sprintf(op_filename,"%s_%d",ep->d_name,i++);

				char buffer[1];
				
				int fd = open(file_path,O_RDONLY) ;
				int output_fd = open(op_filename, O_RDWR | O_CREAT, 0777);
				
				printf("After creation and reading of file\n");
				ssize_t len;
				while((len = read(fd,buffer,1))!= 0){
					//printf("Inside While of a file %s\n",ip_filename);
					//tac_buffer[temp][k++] = buffer[0];

					if(buffer[0] == '\n'){
						//tac_buffer[temp][k] = buffer[0];
						temp++;
						k=0;
					}

					/*if(flag == 1 && temp ==0){
						output_fd = open(op_filename, O_RDWR | O_CREAT, 0777); 
					}*/
					//printf("Just before Write of a file\n");
					write(output_fd,&buffer,1);	

					if(temp == lines){
						//printf("Into the new file now\n");
						temp =0;
						flag =1;

						/*for(l=lines-1;l>=0;l--){
							for(m=0;tac_buffer[l][m] != '\n' && tac_buffer[l][m] != EOF;m++){
								//printf("%c",tac_buffer[l][m] );
								write(output_fd,&tac_buffer[l][m],1);	
							}

							write(output_fd,&tac_buffer[l][m],1);
//							printf("\n");
						}*/

						//printf("Inside While of a file %s\t%s\n",ep->d_name,op_filename);
						close(output_fd);
						sprintf(op_filename,"%s_%d",ep->d_name,i);
						output_fd = open(op_filename, O_RDWR | O_CREAT, 0777); 

						i++;						
					}
					
				}
				if (temp<lines)
				{
					/*(l=lines-1;l>=0;l--){
							for(m=0;tac_buffer[l][m] != '\n' && tac_buffer[l][m] != EOF;m++){
								//printf("%c",tac_buffer[l][m] );
								write(output_fd,&tac_buffer[l][m],1);	
							}

							write(output_fd,&tac_buffer[l][m],1);
							memset(tac_buffer[l],'\0',1000);
//							printf("\n");
						}*/
				}
			}
		}
	}
	else{
		printf("No such file or directory\n");
	}

}

int main(int argc, char *argv[]){
	int num_lines = atoi(argv[3]);

	split(argv[1],num_lines);

	return 0;
}