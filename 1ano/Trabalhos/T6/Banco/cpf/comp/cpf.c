#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char cpf[11];
    int i,v;
    int soma=0, n1=10, n2=11;
    int ver1, cont=0;
    int validade;

    //printf("%d\n",cpf[1]);
    //printf("%d\n",cpf[2]);
    //printf("%d\n",cpf[3]);
    //system("pause");

    do{
        v=0;
        scanf("%s",&cpf);
        //printf("%d\n",cpf[1]);
        //printf("%d\n",cpf[2]);
        //printf("%d\n",cpf[3]);
        //system("pause");
        for(i=0;i<11;i++)
        {
            if ((cpf[i]!= '0') &&  (cpf[i]!= '1') && (cpf[i]!= '2') && (cpf[i]!= '3') && (cpf[i]!= '4') && (cpf[i]!= '5') && (cpf[i]!= '6') && (cpf[i]!= '7') && (cpf[i]!= '8') && (cpf[i]!= '9') )
            {
                v++;
            }
            cpf[i]=cpf[i]-48;
        }
        for(i=0;i<11;i++)
        {
            if (cpf[0]==cpf[i])
            {
                cont++;
            }
            if (cont==11)
            {
                v=1;
            }
        }
        if (v!=0)
        {
            printf("cpf invalido:\ntente novamente\n");
        }
    }while(v!=0);
    //system("pause");
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
            validade = 1;
            printf("CPF VALIDO\n");
        }
        else{
            printf("cpf invalido 2\n");
            validade = 0;
        }

    }
    else{
        validade = 0;
        printf("cpf invalido  1\n");
    }
    for (i=0;i<11;i++)
    {
        printf("%d",cpf[i]);
    }


    return validade;
}
