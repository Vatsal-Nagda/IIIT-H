#include<stdio.h>
#include<string.h>

int updateMe = 0;
int main() {
	
	char buf[32];

	gets(buf);

	if(updateMe != 0) {
		printf("Successfully overflowed the buffer! \n");
	}
	else {
		printf("Try Again! \n");
	}

	return 0;
}
