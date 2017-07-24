#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int updateMe = 0;
int main() {
	
	char buf[32];
	char *input = NULL;

	input = getenv("MALICIOUS");

	if(input == NULL) {
		printf("Try Again! \nSet the MALICIOUS environment variable\n");
		exit(1);
	}

	strcpy(buf, input);


	if(updateMe == 0x61626364) {
		printf("updateMe successfully updated!\n");
	}
	else {
		 printf("Try Again  \nValue at updateMe is 0x%08x\n", updateMe);		
	}
}
