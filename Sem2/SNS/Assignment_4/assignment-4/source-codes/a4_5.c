#include<stdio.h>
#include<string.h>

void executeme() {
	printf("executeme sucessfully executed\n");
}

int main() {
	char buf[32];

	//gets(buf);
        fgets(buf, 32, stdin);

	return 0;
}
