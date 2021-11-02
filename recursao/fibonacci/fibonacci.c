#include <stdio.h>

unsigned long int fib (unsigned long int n)
{
	if (n<2)
		return n;
	else
		return (fib(n-1) + fib(n-2));

}

int main ()
{

	printf("%lu\n",fib(40));

	return 0;
}