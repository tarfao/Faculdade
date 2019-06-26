#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverte(char *c, int i, int f)
{
	char aux;

	if (i<f)
	{
		aux = c[i];
		c[i] = c[f];
		c[f] = aux;
		inverte(c,i+1,f-1);
	}

}

int main()
{
	char c[20]= "subinoonibus";

	inverte(c,0,strlen(c)-1);
	printf("%s\n",c);
	

	return 0;
}