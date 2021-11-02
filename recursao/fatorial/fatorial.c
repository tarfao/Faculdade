#include <stdio.h>

unsigned long int fact (unsigned long int n)
{
	if (n==1)
		return 1;
	else
		return n*fact(n-1);

}

int main ()
{

	printf("%lu\n",fact(30));

	return 0;
}