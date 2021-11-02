#include <stdio.h>
#include <string.h>

int main()
{
	char string[10];
	int t,i,n;

	fgets(string,10,stdin);

	t=strlen(string);
	n=0;
	for(i=0;i<t-1;i++)
	{
		n = n*10 + (string[i] - '0');
	}
	printf("%d\n",n);
	return 0;
}