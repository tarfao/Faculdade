#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE HÁ CONTA COM OS MESMO DIGITOS
//PARAMETRO: A CONTA DIGITADA
//RETORNO: RETORNA 0 SE NÃO HOUVER CONTA, E RETORNA 1 SE HOUVER CONTA
//------------------------------------------------------------------------
int verifica_conta(char conta[6])
{
    int j,i;
    int digito;

    for (j=0;j<qtd_clientes;j++)
    {
        digito=0;
        for(i=0;i<6;i++)
        {
            if (conta[i]==conta_corrente[j][i])
            {
                digito++;
            }
        }
        if (digito==6)
        {
            i=qtd_clientes;
        }
    }
    if (digito==6)
    {
        return 1;
    }
    else{
        return 0;
    }
}
