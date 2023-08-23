#include <stdio.h>
#include <string.h>

void echo(char* string)
{
	char buffer[200];
	strcpy(buffer, string);
	printf("You entered: %s\n", buffer);	
}

int main(int argc, char *argv[])
{
	echo(argv[1]);

	return 0;
}