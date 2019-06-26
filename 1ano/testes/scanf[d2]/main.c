#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*
    char sentence []="Rudolph is 12 years old.";
    char str1[20], str2[20], str3[20], str4[20];
    int i;

    sscanf(sentence,"%s %s %d %s %s",str1,str2,&i,str3,str4);
    printf("%s %s %d %s %s\n",str1,str2,i,str3,str4);

    return 0;
    */

    /*máximo de 20 caracteres + \0
    char calculo[21];
    float operando1;
    float operando2;
    char operacao;

    /* número máximo de caracteres é 20*/
    /*fgets(calculo, 21, stdin);
    printf("Calculo é: %s", calculo);

    if(sscanf(calculo, "%f %1[+-/*] %f", &operando1, &operacao, &operando2) == 3)
    {
        printf("-> Operando 1: %.2f\n", operando1);
        printf("-> Operando 2: %.2f\n", operando2);
        printf("-> Operação: %c\n", operacao);
    }
    else
        printf("Erro no sscanf!\n");

    return 0;*/

    char nome[20];
    float n1;
    float n2;
    char op;

    fgets(nome,10,stdin);

    sscanf(nome, "%f %1[-*+/] %f", &n1,&op,&n2);

    printf("\n%.2f\n%c\n%.2f", n1, op, n2);

}
