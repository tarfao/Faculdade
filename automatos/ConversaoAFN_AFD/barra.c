#include <stdio.h>
#include <string.h>

int main ()
{
	char string[10];
	fgets(string,10,stdin);
	printf("%ld",strlen(string));
	return 0;
}
