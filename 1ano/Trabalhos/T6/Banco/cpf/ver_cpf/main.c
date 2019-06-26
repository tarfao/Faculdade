#include <stdio.h>
#include <stdlib.h>

int Verifica_Cpf(char *cpf)
{
    int n1=10, n2=11;
    int i;
    int soma=0;
    int ver1;

    for (i=0;i<11;i++)
    {
        cpf[i] = cpf[i] - 48;
    }

    for (i=0;i<9;i++)
    {
        //printf("%d\n",cpf[i]);
        //printf("%d\n",n1);
        //printf("%d\n",cpf[i]*n1);
        //printf("%d\n",soma);
        //system("pause");
        soma = soma + (cpf[i]*n1);
        n1=n1-1;
    }
    //printf("%1 %d\n",soma);
    ver1 = soma%11;
    //printf("%d\n",ver1);
    ver1 = 11 - ver1;
    //printf("\n\n%d\n",ver1);
    //printf("%d",cpf[9]);
    if (ver1>9)
    {
        ver1 = 0;
    }
    //printf("%d\n",ver1);
    if (ver1 == cpf[9])
    {
        soma = 0;
        for (i=0;i<10;i++)
        {

            soma = soma + (cpf[i]*n2);
            n2--;
        }
        ver1 = soma%11;
        ver1 = 11 - ver1;
        if (ver1>9)
        {
            ver1 = 0;
        }
        if (ver1==cpf[10])
        {
            return 0;
            //printf("CPF VALIDO\n");
        }
        else{
            //printf("cpf invalido 2\n");
            return 1;
        }

    }
    else{
        return 1;
        //printf("cpf invalido  1\n");
    }

}


int main()
{
    char n[11];
    scanf("%s",&n);

    if (Verifica_Cpf(&n)==0)
    {
        printf("Valido");
    }
    else{
        printf("nn");
    }

    return 0;
}

