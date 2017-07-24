#include <string>
#include <string.h>
#include <stdio.h>	
#include <iostream>
#include <unistd.h>	
#include <sys/types.h>
#include <sys/wait.h>
#include <iterator>
#include <string>
#include <vector>
#include "echo.cpp"
#include "separate_command.cpp"
#include "change_directory.cpp"
#include "pwd.cpp"
#include "history.cpp"
#include "export.cpp"


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

					for(int i=0;i<2*(size-1);i++){
						close(pipes[i]);
					}
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