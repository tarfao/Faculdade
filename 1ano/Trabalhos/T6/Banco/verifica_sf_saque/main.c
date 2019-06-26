#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cont;
    int posi;
    int verifica_sf_saque[2];

    cont = 2;
    verifica_sf_saque[0]=0;
    verifica_sf_saque[1]=1;

    scanf("%d",&posi);

    if (verifica_cliente_e_saque(posi)>0)
    {
        printf("fs");
    }
    else
    {
        printf("nfs");
    }

    return 0;
}

int verifica_cliente_e_saque(int cliente){

    int a=0,i;

    for (i=0;i<cont;i++){
        if (verifica_sf_saque[i] == cliente)
        {
            a++;
        }
    }

    return a;
}


