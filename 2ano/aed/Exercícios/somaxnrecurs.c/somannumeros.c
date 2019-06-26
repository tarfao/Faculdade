#include <stdio.h>

void somanumeros (int c[], int i, int f, int *s)
{
	if (i<f)
		*s = *s + c[i];

}

int soman (int c[], int f)
{
	int i;
	int soma=0;

	for (i=0;i<f;i++)
		soma += c[i];

	return (soma);
}

int main ()
{
	int s=0;
	int c[4] = {3,4,6,2};

	somanumeros(c,0,4,&s);
	printf("-->%d\n",s);


	return 0;
}