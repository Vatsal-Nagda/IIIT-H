#include <string>
#include <iostream>

using namespace std;

void do_export(char** argv){
	
	*argv++;

	while(*argv != NULL){
		string expr(*argv);
		cout <<expr;

		int i=0,j=0;
		char var [50]= {'\0'};
		char value[50] = {'\0'};

		while(expr[i] != '='){
			var[j++] = expr[i++];
		}
		i++;j=0;
		while(expr[i] != '\0'){
			value[j++] = expr[i++];
		}

		if(setenv(var,value,1) < 0){
			perror("");
		}
		
		*argv++;
	}

}