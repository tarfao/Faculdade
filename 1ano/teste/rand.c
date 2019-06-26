#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main()
{
    int *x;
    int i;


    x = ((int*) malloc(5*sizeof(int)));

    for (i=0;i<5;i++)
    {
        x[i] = 0;
    }
    for (i=0;i<5;i++)
    {
        printf("[%d] - %d ",i+1,x[i]);
    }
    /*srand(time(NULL));
    x = rand()%10;
    printf("%d",x);*/

    system("pause");
    return 0;
}
