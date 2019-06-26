#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*char cara[15];
    int i=0;

    fgets (cara,15,stdin);
    while ((isalnum(cara[i])))
    {
        printf ("%c is alphanumeric. Position %d\n",cara[i],i+1);
        i++;
    }
    return 0;*/

    char cara[15];
    int i=0;

    fgets (cara,15,stdin);
    while ((isalnum(cara[i])))
    {
        printf ("%c is alphanumeric. Position %d\n",cara[i],i+1);
        i++;
    }
    return 0;
}
