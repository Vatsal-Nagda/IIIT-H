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
#include "parser.cpp"
#include "echo.cpp"
#include "separate_command.cpp"
#include "change_directory.cpp"
#include "pwd.cpp"
#include "history.cpp"
#include "export.cpp"

using namespace std;

int main(){

	cout<<"["<<getenv("USER")<<":"<<getenv("PWD")<<"]$ ";
	
	string line;
	while(1){

		getline(cin,line);
		send_to_history(line);
		vector < string > commands ;
		
		parseInput(line,commands);
		//cout<<"The string entered by you is :"<<line;

		cout <<"The commands given are :\n"<<"pipe count :"<<(commands.size()-1)<<endl;

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
			//cout <<*vec_itr<<endl;
			string str = *vec_itr;
			//cout<<"index "<<count<<endl;
			//cout <<str<<"c"<<endl;

			char *ip_arr = new char[str.size()+1];
			strcpy(ip_arr,str.c_str());

/*			for(int i=0;ip_arr[i]!='\0';i++)
				printf("%c",ip_arr[i] );*/

			char *argv[86];
			separate_cmd(ip_arr,argv);

			//send_to_history(str);

			if(strcmp(argv[0],"cd") == 0){
					//cout<<"Inside CD\n";
					change_dir(argv);
				}
			/*else if(strcmp(argv[0],"echo") == 0){
				cout<<"Clling echo";
				echo(str);
			}*/
		//	cout<<argv[0]<<argv[1]<<argv[2]<<"c"<<endl;


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
						//close(pipes[0]);
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


	cout<<"["<<getenv("USER")<<":"<<getenv("PWD")<<"]$ ";

	}


	return 0;
}