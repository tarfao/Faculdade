#include <stdio.h>
#include <stdlib.h>


//----------------------------------------------------------------------
//objetivo: verificar o que foi digitado no cpf
//parametro: o cpf
//retorno: retorna V, que se for 0 estara tudo ok, se for difrente de 0 não
//-----------------------------------------------------------------------
int lecpf(char cpf[])
{
    int v, cont=0;
    int i;

    v=0;
        //printf("%d\n",cpf[1]);
        //printf("%d\n",cpf[2]);
        //printf("%d\n",cpf[3]);
        //system("pause");
    for(i=0;i<11;i++)
    {
        //verifica se o que o usuario digitou foram só numeros
        if ((cpf[i]!= '0') &&  (cpf[i]!= '1') && (cpf[i]!= '2') && (cpf[i]!= '3') && (cpf[i]!= '4') && (cpf[i]!= '5') && (cpf[i]!= '6') && (cpf[i]!= '7') && (cpf[i]!= '8') && (cpf[i]!= '9') )
        {
            v++;//esse contador irah validar caso o usuario digite alguma letra
        }
    }
    for(i=0;i<11;i++)
    {
        //verifica se os numeros digitados sao todos iguais, pois
        //a expressao desenvolvida para o calculo com os numeros
        //iguais ocorre a validação do cpf
        if (cpf[0]==cpf[i])
        {
            cont++;//contador atualiza caso os numeros forem iguais
        }
        if (cont==11) //se todos os 11 numeros forem iguais,
                     // atualiza o verificador do que foi digitado no cpf
        {
            v=1;
        }
    }

    return (v); //
}

int main ()
{
    char cpf[11];
    //int ver;
    printf("DIGITE O SEU CPF:\n");
    scanf("%s",&cpf);
    //ver = lecpf(cpf);
    if (lecpf(cpf)==0)
    {
        printf("blz");
    }
    else{
        printf("nn");
    }

    return 0;
}


