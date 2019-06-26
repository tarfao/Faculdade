/*
Desenvolver um sistema para saques de um caixa eletr�nico que dever� liberar o menor n�mero de c�dulas
para um valor solicitado pelo cliente. Esse cliente dever� ter seu n�mero de conta corrente e CPF (v�lido)
em um cadastro.  As c�dulas armazenadas no caixa s�o de 200, 100, 50, 40, 20, 10, 5, 2 e 1 real.

O caixa eletr�nico � abastecido com as quantidade m�ximas de c�dulas sempre que o gerente acionar a funcionalidade
�abastecer�.  Essas quantidades m�ximas de c�dulas s�o: 100 (c�dulas) de 200; 200 de 100;  400 de 50; 500 de 40;
600 de 20; 700 de 10; 800 de 5; 1.500 de 2 e 2.000 de 1 real.

Para sacar dinheiro o cliente deve fornecer sua conta corrente e caso ela exista no cadastro o sistema liberar� a quantidade
de cada c�dula e imprimir� o valor do saque por extenso.

Para o gerente o sistema deve informar cada valor sacado e o CPF de quem sacou, o valor total sacado, o valor do saldo
existente e a quantidade de cada c�dula armazenada no caixa eletr�nico, quando acionado pelo gerente. O valor total sacado,
o valor do saldo existente e a quantidade de c�dulas existentes devem ser informadas, al�m de seu valor num�rico, o valor por
extenso.

O menu de op��es deve ser o seguinte:

MENU PRINCIPAL
1-Cliente
2-Saque
3-Gerente
4-Finalizar

MENU CLIENTE
1-Cadastrar um cliente
2-Mostrar todos clientes
3-Alterar um cliente
4-Apagar um cliente
5-Voltar ao menu principal

MENU GERENTE
1-Abastecer
2-Valores sacados
3-Valor total sacado
4-Valor do saldo existente
5-Quantidade de c�dulas existentes
6-Voltar ao menu principal

�S� ser� poss�vel alterar ou apagar um cliente caso n�o exista nenhum saque dele.
�Para a constru��o do sistema use m�dulos e estruturas de dados homog�neas

*/

#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------
//objetivo: verificar o que foi digitado no cpf
//parametro: o cpf
//retorno: retorna V, que se for 0 estara tudo ok, se for difrente de 0 n�o
//-----------------------------------------------------------------------
int lecpf(char cpf[], int j)
{
    int v, cont=0;
    int i;

    v=0;
        //printf("%d\n",cpf[1]);
        //printf("%d\n",cpf[2]);
        //printf("%d\n",cpf[3]);
        //system("pause");
    for(i=0;i<j;i++)
    {
        //verifica se o que o usuario digitou foram s� numeros
        if ((cpf[i]!= '0') &&  (cpf[i]!= '1') && (cpf[i]!= '2') && (cpf[i]!= '3') && (cpf[i]!= '4') && (cpf[i]!= '5') && (cpf[i]!= '6') && (cpf[i]!= '7') && (cpf[i]!= '8') && (cpf[i]!= '9') )
        {
            v++;//esse contador irah validar caso o usuario digite alguma letra
        }
    }
    for(i=0;i<j;i++)
    {
        //verifica se os numeros digitados sao todos iguais, pois
        //a expressao desenvolvida para o calculo com os numeros
        //iguais ocorre a valida��o do cpf
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

void AdicionaConta ()
{
    char nume[11], ac[6];

    printf("\n\tCPF: \n\t");
    scanf("%s",&nume);
    if (lecpf(nume,11)==0)
    {
        if (Verifica_Cpf(nume)==0)
        {
            printf("\n\tNUMERO DA CONTA: \n\t");
            scanf("%s",&ac);
            if (lecpf(ac,6)==0)
            {
                cpf_cliente[quantiaclientes]=nume;
                acc_clientes[quantiaclientes]=ac;
                quantiaclientes++;
            }
        }

    }
}
int main()
{
    char menup, menuc, menug; //Auxilia os menu's, respectivamente, menu principal, cliente e gerente
    char n[11], ac[6]; //n representa um cpf digitado, e ac uma conta
    int quantiaclientes=0; //altera conforme a quantia de clientes aumenta
    char cpf_cliente[50][11];
    char acc_clientes[50][6]; //cpf clientes armazena os cpf do cliente paralelo a sua conta (acc_clientes)
    //int saque_clientes[50]; //armazena os saques dos clientes
    int verifica_se_ha_cadastro_semelhante=0;

    //menu principal e suas funcoes
    do{
        system("cls");
        printf("\n\tMENU PRINCIPAL\n\n");
        printf("\t1 - CLIENTE\n");
        printf("\t2 - SAQUE\n");
        printf("\t3 - GERENTE\n");
        printf("\t4 - FINALIZAR\n\n\t");
        scanf("%s",&menup);
        system("cls");

        //menu cliente
        if (menup == '1')
        {
            do{
                system("cls");
                printf("\n\tMENU CLIENTE\n\n");
                printf("\t1 - CADASTRAR UM CLIENTE\n");
                printf("\t2 - MOSTRAR TODOS OS CLIENTES\n");
                printf("\t3 - ALTERAR UM CLIENTE\n");
                printf("\t4 - APAGAR UM CLIENTE\n");
                printf("\t5 - VOLTAR AO MENU PRINCIPAL\n\n\t");
                scanf("%c",&menuc);
            }while(menuc!='5');
            if (menuc==1)
            {
                AdicionaConta();
            }
        }

        //saque
        if (menup == '2')
        {
            printf("\n\tCPF: ");
            scanf("%s",&n);
            if (lecpf(n,11)==0)
            {
                if (Verifica_Cpf(&n)==0)
                {
                    printf("\n\tblz\n\n");
                }
                else{
                    printf("\n\tnn\n\n");
                }
            }
            else{
                printf("\n\tCPF INVALIDO\n\n");
            }
            system("\tpause");
        }

        //menu gerente
        if (menup == '3')
        {
            do{
                system("cls");
                printf("\n\tMENU GERENTE\n\n");
                printf("\t1 - ABASTECER\n");
                printf("\t2 - VALORES SACADOS\n");
                printf("\t3 - VALOR TOTAL SACADO\n");
                printf("\t4 - VALOR DO SALDO EXISTENTE\n");
                printf("\t5 - QUANTIDADE DE CEDULAS EXISTENTES\n");
                printf("\t6 - VOLTAR AOO MENU PRINCIPAL\n\n\t");
                scanf("%c",&menug);
            }while(menug!= '6');

        }
    }while(menup!= '4');
    return 0;
}
