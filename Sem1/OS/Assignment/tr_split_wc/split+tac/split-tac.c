/***************************************************************************************

			NAME    : VATSAL MANOJ NAGDA
			ROLL NO : 20162008

***************************************************************************************/



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

void split(char *src_dir,char *dest_dir,int lines){
	DIR *dp;
	struct dirent *ep;
	char *file_path = (char *)malloc(sizeof(strlen(src_dir)*2)); 		//file path of file to b opened
	char *op_filename = (char *)malloc(sizeof(strlen(file_path)));		//file name of the output files
	
	char tac_buffer[lines][10000];										// to store input file lines for reversal in Tac

	dp = opendir(src_dir);

	if(dp != NULL){
		while((ep = readdir(dp))!=NULL){			//reading a file
			
			if(strcmp(ep->d_name,".")== 0 || strcmp(ep->d_name,"..")== 0)
				continue;

			if( ep->d_type == DT_REG){      							 	//if it is a regular file then
				int i=1,k=0;												// file numbr counter
				int l;
				int line_count=0,flag=0;											//no of iines counter

				sprintf(file_path, "%s/%s", src_dir, ep->d_name);
				/*printf("Opened file %s\n",file_path );
				
				printf("Opened file %s\n",file_path );*/
				char buffer[1];												//buffer to store input character read
				
				int fd = open(file_path,O_RDONLY) ;							//open file for reading
				
				sprintf(op_filename,"%s/%s_%d",dest_dir,ep->d_name,i++);				

				int output_fd = open(op_filename, O_RDWR | O_CREAT, 0777);  //create file for writing
				//printf("After creation of file %s\n",op_filename);
				ssize_t len;

				while((len = read(fd,buffer,1))!= 0){					//keep on reading till the time input exists
					
					tac_buffer[line_count][k++] = buffer[0];					//store the read character in buffer
					
					if(buffer[0] == '\n'){								//if new line character comes, append the string with
						tac_buffer[line_count][k] = '\0';						//null to delimite it while outputing in to the file
						line_count++;
						k=0;
					}

					if(flag == 1 && line_count ==0){						//create a file only when there is input and the previous file is closed
						output_fd = open(op_filename, O_RDWR | O_CREAT, 0777); 
						flag =0;
					}		
					
					if(line_count == lines){							//if i have read required number of lines then reinitialize
						line_count =0;								//line number to zero
						flag =1;

						for(l=lines-1;l>=0;l--){							//whatever lines are there in buffer write them
								write(output_fd,tac_buffer[l],strlen(tac_buffer[l]));	 //into the file in reverse order
						}

						close(output_fd);								//after writing into the file close the file
						sprintf(op_filename,"%s/%s_%d",dest_dir,ep->d_name,i++); 	//generating name for the next file				
					}
					
				}
				if (line_count < lines)				//number of lines remaining required to be written to the folder separately
				{
					for(l=line_count-1;l>=0;l--){
							write(output_fd,tac_buffer[l],strlen(tac_buffer[l]));	
					}
				}
			}
		}
	}
	else{
		printf("No such file or directory\n");
	}

}

void make_dir(char *dest){											//function to create the destination directory
	char *op_filename = (char *)malloc(sizeof(strlen(dest)*2));		//store the destination directory argument in a variable
	int i,j=0;
	int len = strlen(dest);

	for(i=0;i< len;i++){											//scan path line by and parse it for folder names required
		if(dest[i] != '/'){
			op_filename[j++] = dest[i];
		}
		else{
			op_filename[j++] = '/';
				mkdir(op_filename,0777);							//create the folders
			
		}
	}
			op_filename[j++] = '/';									//create the last remaining folder
			mkdir(op_filename,S_IRWXU);
}


int main(int argc, char *argv[]){
	int num_lines = atoi(argv[3]);

	make_dir(argv[2]);
	split(argv[1],argv[2],num_lines);

	return 0;
}