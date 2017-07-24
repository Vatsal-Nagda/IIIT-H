#include <string>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


using namespace std;

void echo(string line){

	line = line.substr(4);
	int i=0;

	bool flag_dub_quote = false;
	bool flag_sing_quote = false;

	char *ip_arr = new char[line.length()+1];
	memset(ip_arr,'\0',line.length()+1);
	strcpy(ip_arr,line.c_str());

	string buffer="";

	while(ip_arr[i]!= '\0'){

		if((ip_arr[i] == '"') || (ip_arr[i] == '\'')){ 

			if(ip_arr[i] == '"'){
				i++;
				while(ip_arr[i] != '\0'){
					if(ip_arr[i] == '"')
						break;
					buffer += ip_arr[i];
					i++;
				}
			}

			if(ip_arr[i] == '\''){
				i++;
				while(ip_arr[i] != '\0'){
					if(ip_arr[i] == '\'')
						break;
					buffer += ip_arr[i];
					i++;
				}
			}
		}
		else{

			if(ip_arr[i] ==' ' && ip_arr[i+1]==' ')
				ip_arr[i] = '\0';
			else{

				char env_var [86] ={'\0'};
				int m=0;
				if(ip_arr[i] =='$'){
					i++;
					while(ip_arr[i]!=' '){
						env_var[m] = ip_arr[i];
						m++;
						i++;
					}

					env_var[m] = '\0';
					if(getenv(env_var) != NULL){
						
						char *result = (char *)malloc(sizeof(char)*512);
						memset(result,'\0',512);
						strcpy(result,getenv(env_var));
						string abc(result);
						buffer += abc+" ";
					}
					else{
						cout<<endl;
						exit(0);
					}
				}
				else{
					buffer += ip_arr[i];
				}			
			}
		}

		i++;
	}
	cout << buffer<<endl;
}