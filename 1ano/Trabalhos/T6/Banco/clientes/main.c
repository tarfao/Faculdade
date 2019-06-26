#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define ACC 4
#define DIG 12

void AdicionaConta (int j)
{
    char nume[11], ac[6];

    printf("\n\tCPF: \n\t");
    scanf("%s",&nume);
    if (lecpf(nume)==0)
    {
        if (Verifica_Cpf(nume)==0)
        {
            printf("\n\tNUMERO DA CONTA: \n\t");
            scanf("%s",&ac);
            if (lecpf(ac)==0)
            {
                cpf_cliente[quantiaclientes]=nume;
                acc_clientes[quantiaclientes]=ac;
                quantiaclientes++;
            }
        }

    }
}
