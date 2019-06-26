#include <stdio.h>
#include <stdlib.h>

int main()
{
    int op;
    int posi,j;

    do{

        printf("\n\t--------SISTEMA BANCARIO/CLIENTE/APAGAR CLIENTE------\n\n");
        printf("\tQUAL USUARIO DESEJA APAGAR?\n\t");
        scanf("%d",&op);

    }while((op<1) || (op>qtd_clientes));

    posi = testa_cpf_apagar(op);

    if (posi==0)
    {
        for (i=0;i<11;i++)
        {
            clientes[op-1][i]= '-';
            if (i<6)
            {
                conta_corrente[i] = '-';
            }
        }
    }

}
//--------------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE HÁ SAQUE DO CLIENTE QUE DESEJA APAGAR
//PARAMETRO: DE ENTRADA QUE É A POSICAO DO CLIENTE QUE SERA APAGADO SE ENCONTRA
//RETORNO; RETORNA 0 SE FEZ ALGUM SAQUE, E RETORNA 1 SE NÃO FEZ NENHUM
//---------------------------------------------------------------------------------
int testa_cpf_apagar(int opcao){

    //DECLARAÇÃO DE VARIAVEIS LOCAIS
    int i,j;//contadores
    int qtd;//conta os digitos iguais

    for (i=0;i<saque_valido;i++)//laço verifica se o cpf informado já possui cadastro
    {
        qtd=0;//ao final de cada linha da matriz a quantidade é reiniciada em 0
        for (j=0;j<12;j++)//faz o controle das colunas
        {
            if (cpf_saque[i][j] == clientes[opcao-1][j]){//toda vez que o digito for existente a quantidade é incrementada
                qtd = qtd+1;
            }
            if (qtd>10)
            {
                i = qtd_clientes;
            }
        }
    }
    if (qtd > 10){
        return 0;
    }
    else{
        return 1;
    }

}
