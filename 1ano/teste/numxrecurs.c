#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int searchx (int c[], int x, int i, int f)
{
	
	if (i<f){
		if (c[i]==x)
		{
			return 1;
		}
		else
		{
			return (searchx(c,x,i+1,f));
		}
	}
	else
	{
		return 0;
	}

}

int main ()
{
	int c[10] ={1,2,3,4,5,6,7,8,9,10};

	if(searchx(c,10,0,10))
		printf("Achou!!\n");


	return 0;
}