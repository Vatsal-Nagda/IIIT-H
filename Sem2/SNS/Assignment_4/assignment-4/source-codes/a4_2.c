#include<stdio.h>
#include<string.h>

int updateMe = 0;
int main() {
	
	char buf[32];

	printf("Provide input \n");
	gets(buf);

	if(updateMe == 0x41434547) {
		printf("Updatedsuccessfully! \n");
	}
	else {
		printf("Try Again \nValue at updateMe is 0x%08x\n", updateMe);
	}

	return 0;
}
