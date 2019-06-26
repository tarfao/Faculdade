#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[30],nome[10];
    int chars;

    fgets(nome,10,stdin);
    chars = sprintf(name,"ESSE EH O NOME: %s",nome);
    printf("%d\n",chars);
    puts(name);

    return 0;
}
