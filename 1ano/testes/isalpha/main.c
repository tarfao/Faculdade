#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[10];
    int i=0;

    fgets(nome,10,stdin);
    while(isalpha(nome[i]))
    {
        printf("The letter alphabetic to be position %d\n",i+1);
        i++;
    }
    return 0;
}
