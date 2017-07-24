#include <string>
#include <string.h>
#include <stdio.h>	
#include <iostream>
#include <unistd.h>	
#include <sys/types.h>
#include <sys/wait.h>
#include <iterator>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include "echo.cpp"
#include "separate_command.cpp"
#include "change_directory.cpp"
#include "pwd.cpp"
#include "history.cpp"
#include "export.cpp"
#include "parser.cpp"

using namespace std;

void execute(vector < string > &commands);


int main(){

	cout<<"["<<getenv("USER")<<":"<<getenv("PWD")<<"]$ ";
	
	string line;
	while(1){

		getline(cin,line);

		if(line.length() == 0){
			cout<<"["<<getenv("USER")<<":"<<getenv("PWD")<<"]$ ";
			continue;
		}	

		send_to_history(line);
		vector < string > commands ;
		
		parseInput(line,commands);
		//cout<<"The string entered by you is :"<<line;
		execute(commands);

		//cout <<"The commands given are :\n"<<"pipe count :"<<(commands.size()-1)<<endl;

	cout<<"["<<getenv("USER")<<":"<<getenv("PWD")<<"]$ ";

	}


	return 0;
}




void execute(vector < string > &commands){

		vector < string >::iterator vec_itr;

		//make fds for pipes		v.size()-1
		int size = commands.size(); 
		int pipes[size*2];

		for(int i = 0; i < size-1; i++ ){
		    if( pipe(pipes + i*2) < 0 ){
		        perror("Pipes not created");
		        exit(0);
		    }
		}

		if(commands.at(0).compare("exit") == 0)
				exit(0);

		int count=1;
		int status;
		for(vec_itr = commands.begin();vec_itr != commands.end();vec_itr++){
			
			string str = *vec_itr;

			char *ip_arr = new char[str.size()+1];
			strcpy(ip_arr,str.c_str());

			char *argv[86];
			separate_cmd(ip_arr,argv);


			if(strcmp(argv[0],"cd") == 0){
					change_dir(argv);
				}


			pid_t pid = fork();

			if(pid < 0){
				perror("Error creating child");
			}
			else if(pid == 0){

				int k=0;
				int i_o =0;

				while(argv[k] != NULL){
					if(*argv[k] == '<' || *argv[k] == '>'){
						i_o = k;
						cout<<"Found "<<*argv[k] <<"at "<<k<<endl;
						break;
					}
					k++;
				}

				int in_file_des;
				int out_file_des;
				
				if(size != 1){

					if(count == 1){
							// this is first commandshandle separately


						if(dup2(pipes[1],1) < 0){
							perror("Pipe not created for 1st child");
							exit(0);
						}
						
					}
					else if(count == size){
						//last command
						if(dup2(pipes[2*(count-2)],0) < 0){
							perror("Pipe not created for last child");
							exit(0);
						}         //replacing stdin with pipe read
	            		close(pipes[2*(count-1)+1]);
					}
					else{
						//middle commands

						if(dup2(pipes[2*(count-2)],0) < 0){
							perror("Pipe not created for middle childs");
							exit(0);
						}
						if(dup2(pipes[2*(count-1)+1],1) < 0){
							perror("Pipe not created for middle childs");
							exit(0);
						}
					}

					if(i_o != 0){
							//i_o to be redirected
							if(*argv[i_o] == '<' ){
								cout<<"Inside < handler"<<endl;
								//input to be redirected
								in_file_des =open((const char*)argv[i_o+1],O_RDONLY);
								argv[i_o] = NULL;
								argv[i_o+1] = NULL;
								
								if(dup2(in_file_des,0) < 0){
									perror("Pipe not created for I/0 input of 1st child");
									exit(0);
								}								
							}
							if(*argv[i_o] == '>'){
								//output to be redirected
								out_file_des =open((const char*)argv[i_o+1],O_WRONLY | O_CREAT | O_TRUNC,0644);
								argv[i_o] = NULL;
								argv[i_o+1] = NULL;
								
								if(dup2(out_file_des,1) < 0){
									perror("Pipe not created for I/0 output of 1st child");
									exit(0);
								}	
							}
						}

					for(int i=0;i<2*(size-1);i++){
						close(pipes[i]);
					}
					close(in_file_des);
					close(out_file_des);
				}

				else{
					if(i_o != 0){
							//i_o to be redirected
						if(*argv[i_o] == '<' ){
							cout<<"Inside < handler"<<endl;
							//input to be redirected
							in_file_des =open((const char*)argv[i_o+1],O_RDONLY);
							argv[i_o] = NULL;
							argv[i_o+1] = NULL;
							
							if(dup2(in_file_des,0) < 0){
								perror("Pipe not created for I/0 input of 1st child");
								exit(0);
							}								
						}
						if(*argv[i_o] == '>'){
							//output to be redirected
							out_file_des =open((const char*)argv[i_o+1],O_WRONLY|O_CREAT | O_TRUNC,0644);
							argv[i_o] = NULL;
							argv[i_o+1] = NULL;
							
							if(dup2(out_file_des,1) < 0){
								perror("Pipe not created for I/0 output of 1st child");
								exit(0);
							}	
						}
					}

					close(in_file_des);
					close(out_file_des);

				}

				fflush(stdout);

				
				if(strcmp(argv[0],"pwd") == 0){
					cout<<"Inside PWD\n";
				}
				else if(strcmp(argv[0],"export") == 0){
					cout<<"Inside export\n";
					do_export(argv);
				}
				else if(strcmp(argv[0],"history") == 0){
					//cout<<"Inside history\n";
					parse_history(str);
					exit(0);
				}
				else if(strcmp(argv[0],"echo") == 0){
				//	cout<<"Calling echo";
					echo(str);
					exit(0);
				}
				else if(strcmp(argv[0],"cd") != 0){
					fflush(stdout);
					int result = execvp(*argv,argv);
					if(result < 0){
					perror("Command not executed succesfully");
					}
				}				
			}
				
			count++;
		}

		for(int i=0;i<2*(size-1);i++){
				close(pipes[i]);
		}

		for(int i=0;i<(size-1);i++){
				wait(&status);
		}

}