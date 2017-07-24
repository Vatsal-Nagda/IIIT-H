#include <stdlib.h>
#include <stdio.h>
#include <string.h>

///using namespace std;

int main(){
	
	char * home = (char *)malloc(sizeof(char)*250);
	home = getenv("HOME");
	printf("%s\n",home );
	strcat(home,"/history.txt");
	printf("%s\n",home );
	return 0;
}