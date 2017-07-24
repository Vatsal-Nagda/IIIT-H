#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
using namespace std;

int main(){
	string IP;
	IP = "127.0.0.1";
	string temp,res;
	char tmp[1024];
	int base16,base4,base10=0,i;

	FILE *hash=popen(("echo "+IP+"|md5sum").c_str(),"r");

	fgets(tmp,1024,hash);
	temp = string(tmp);

	res = temp.substr(0,4);
return 0;}