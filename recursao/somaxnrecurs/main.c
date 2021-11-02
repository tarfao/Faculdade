#include <stdio.h>
#include <stdlib.h>

int somax (int c[], int i, int f)
{
    if (i<f)
    {
        return(c[i] + somax(c,i+1,f));
    }
    else
    {
        return 0;
    }
}


int main()
{
    int c[10] = {10,10,10,10,10,10,10,10,10,10};

    printf("%d",somax(c,0,5));


    return 0;
}
