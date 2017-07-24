#include <iostream>
#include <string>

using namespace std;

void separate_cmd(char *ip_arr, char **argv){

	for(int i=0;ip_arr[i]!='\0';i++){
		if(ip_arr[i] == '"')
			ip_arr[i] = ' ';
	}

//	cout<<"Inside separate_cmd\n";

	while(*ip_arr !='\0'){
		//printf("%c",*ip_arr );		

		while(*ip_arr == ' ' || *ip_arr == '\t' || *ip_arr == '"' || *ip_arr == '\n')
			*ip_arr++ = '\0';

		*argv = ip_arr;
		//printf("%s\n",*argv );
		argv++;

		while(*ip_arr != ' ' && *ip_arr != '\0' && *ip_arr != '\t' && *ip_arr != '\n'){
			
			ip_arr++;
		}

	}

	*argv = '\0';
}