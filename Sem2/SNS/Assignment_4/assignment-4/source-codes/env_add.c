#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char *addr = getenv(argv[1]);
	printf("Shell add is %p\n",addr);
	
	return 1;
}