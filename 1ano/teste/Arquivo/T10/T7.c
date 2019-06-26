/*
O sistema deve manter no m�ximo 1000 clientes cadastrados. Ao acionar a op��o 'incluir'
do menu cliente o sistema deve gerar automaticamente um cpf v�lido e um n�mero de conta
corrente nos formatos '999.999.999-99' e '999.999-x', respectivamente, e fazer a
inclus�o do novo cliente no cadastro. Um novo cliente s� pode ser inclu�do se n�o
existir um cpf ou n�mero de conta corrente j� cadastrados. Utilize as rotinas ' void
gera_cpf_valido(char cpf[])' e ' void geraContaCorrente(char c[])' para a gera��o
autom�tica do cpf e conta corrente.  A op��o 'mostrar' do menu cliente deve apresentar
os dados dos clientes cadastrados no sistema. A op��o 'alterar' do menu cliente permite
fazer uma altera��o no cpf ou n�mero da conta corrente. A altera��o somente ser� permitida
se n�o existir nenhum saque realizado por aquele cliente. O sistema dever� preservar os
formatos '999.999.999-99' (do cpf) e '999.999-x' (da conta corrente). A op��o 'excluir' do
menu cliente permite apagar um cliente do cadastro caso n�o h� nenhum saque realizado deste
cliente. O dado de consulta para a altera��o e exclus�o � o n�mero da conta corrente
(formato '999.999-x').  Para sacar dinheiro um cliente deve fornecer seu n�mero de conta
corrente (formato '999.999-x') e caso ela exista no cadastro o sistema liberar� a menor
quantidade de c�dulas para o valor solicitado e imprimir� o valor do saque por extenso.
O caixa eletr�nico deve estar abastecido automaticamente antes do primeiro saque e os valores
m�ximos de cada c�dula s�o: 100 (c�dulas) de 200; 200 de 100;  400 de 50; 500 de 40;
600 de 20; 700 de 10; 800 de 5; 1.500 de 2 e 2.000 de 1 real.


RGM     INTEGRANTES

35029   IURY RODRIGUES PRATES

35043   RONALDO TAFAREL PEREIRA DE SOUZA

35048   ZENALVO BASTOS PINTO J�NIOR

DATA: 20/08/2016
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<ctype.h>


//------------------------------------------------------------------------------------------------------------------------
    void menu_relatorio();
    void insere_pontuacao_cpf();
    void tira_cpf_formato();
    char geraAlfabeto();
    void gera_cpf_valido();
    void insere_pontuacao_cpf();
    void geraContaCorrente();
    void colocando_conta_formato();
//-----------------------------------------------------------------------------------------------------------------------

typedef struct cba {
/*apaga_cliente
testa_conta
altera_cliente
testa_cpf
verifica_conta
verifica_cpf_valido
cadastro_cliente
gera_cpf_valido
obtem_primeiro_digito_verificador
obtem_segundo_digito_verificador
insere_pontuacao_cpf
geraContaCorrente
geraAlfabeto
colocando_conta_formato
verifica_formact_cpf
verifica_formact_conta
tira_cpf_formato*/
    char clientes[15];//matriz que armazenara os cpf's de todos os clientes **definido o maximo como sendo 50 clientes
    char conta_corrente[10];//vetor que armazena dados da conta corrente **maximo 50
    int situacao; //ativo = 1, inativo =2;
    int saque = 1;//nn fez saque = 1, fez saque = 2

}usuario;


typedef struct saq_banco {

    int saques_clientes[1000];//obtem cada saque que um cliente faz
    char conta_saque[10]
    char cpf_saque[15];// obtem o cpf de cada cliente que faz o saque(SUBMETIDO A SER RETIRADO)
    //char obtem_posicao_cliente_cada_saque[1000];
    //int verifica_sf_saque=1;//verifica se um usuario j� fez saque para poder ser alterado (1 n fez, 2 fez)
    //int totsak=0;//totsak eh o total jah sacado depois de varias transa��es
    //int cont=0; // auxlia cada posicao do vetor verifica_sf_saque, que so tem 50 posicoes, que � o numero de cadastros possiveis
            // ou seja ira obter somente 1 vez a posicao de um usuario que fez saque.
    int saque_valido=0;//auxilia o vetor de saques em cada saque valido para ser armazenado

}dados;


typedef struct cedulas{
    int vernot1, vernot2, vernot5, vernot10, vernot20, vernot50, vernot40, vernot100, vernot200;
}notas;

//---------------------------------------------------------------------------------------------------
//PROCEDIMENTO
//OBJETIVO: MOSTRAR POR EXTENSO ALGUM VALOR
//PARAMETRO: DE ENTRADA QUE SERA O VALOR TOTAL DO CAIXA, OU O VALOR DO SAQUE
//---------------------------------------------------------------------------------------------------
void extenso(int saque)
{
    int CM;//CENTENA DE MILHAR
    int DM;//DEZENA DE MILHAR
    int UNM;//UNIDADE DE MILHAR
    int CEN;//CENTENA
    int DEZ;//DEZENA
    int UN;//UNIDADE

    CM = saque/100000 ; // centena de milhar recebe valor do saque dividido por 100000
    DM = (saque - CM*100000)/10000; // dezena de milhar recebe valor do saque menos centena de milhar vezes 100000 dividido por 10000
    UNM = (saque - CM*100000 - DM*10000)/1000; // unidade de milhar recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 dividido por 1000
    CEN = (saque - CM*100000 - DM*10000 - UNM*1000)/100; // centena recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 dividido por 100
    DEZ = (saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100)/10; // dezena recebe daque menos centena de milha vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 dividido por 10
    UN = saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100 - DEZ*10; // unidade recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 menos dezena vezes 10
    if ((CM == 1) && (DM == 0) && (UNM == 0) && (CEN == 0) && (DEZ == 0) && (UN == 0)) // condicao para somente 100.000
    {
        printf("CEM MIL");
    }
    // condicao para imprimir cem mil caso a centena, dezena ou unidade possuir valores diferentes de 0
    if ((CM == 1) && (DM == 0) && (UNM == 0) && ((CEN != 0) || (DEZ != 0) || (UN != 0)))
    {
        printf ("CEM MIL");
    }
    // imprime "cento e" caso a unidade de milhar ou dezena de milhar seja diferente de 0
    if ((CM == 1) && ((DM != 0) || (UNM != 0)))
        printf("CENTO E");
        // imprimir valores da dezena de milhar
        if (DM == 9)
            printf("NOVENTA");
        else{
            if (DM == 8)
                printf ("OITENTA");
            else{
                if (DM == 7)
                    printf ("SETENTA");
                else{
                    if (DM == 6)
                        printf ("SESSENTA");
                    else{
                        if (DM == 5)
                            printf ("CINQUENTA");
                        else{
                            if (DM == 4)
                                printf ("QUARENTA");
                            else{
                                if (DM == 3)
                                    printf ("TRINTA");
                                else{
                                    if (DM == 2)
                                        printf ("VINTE");
                                    else{
                                        if ((DM == 1) && (UNM ==0))
                                            printf ("DEZ");
                                        else{
                                            if (DM ==1)
                                                if (UNM == 9)
                                                    printf ("DEZENOVE");
                                                else{
                                                    if (UNM == 8)
                                                        printf ("DEZOITO");
                                                    else{
                                                        if (UNM == 7)
                                                            printf("DEZESSETE");
                                                        else{
                                                            if (UNM == 6)
                                                                printf ("DEZESSEIS");
                                                            else{
                                                                if (UNM == 5)
                                                                    printf ("QUINZE");
                                                                else{
                                                                    if (UNM == 4)
                                                                        printf ("QUATORZE");
                                                                    else{
                                                                        if (UNM == 3)
                                                                            printf ("TREZE");
                                                                        else{
                                                                            if (UNM == 2)
                                                                                printf ("DOZE");
                                                                            else{
                                                                                if (UNM ==1)
                                                                                    printf ("ONZE");

                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                // condicao para valores de com a dezena de milhar igual a 1, com valores particulares de treze, onze...
                                                if ((CM == 0) && (DM==1))
                                                    printf(" MIL");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
    // imprime "mil" antes do valor da centena, dezena e unidade
    if ((CM != 0) && (DM != 0) && (UNM == 0))
        printf(" MIL");
    else{
        if ((CM==0) && (DM != 0) && (UNM == 0))
            printf(" MIL");
        else{
            if ((DM != 1) && (DM!=0) && (UNM != 0)) // imprime o "e" para separa��o de dezena e unidade, para ex: noventa E tr�s
                printf(" E");
            }
        }
    // para aparecer vinte e tr�s a dezena de milhar tem que ser diferente de 1,
    // se for 1 deveria sair valores como, treze, onze. casos particulares
    if (DM!=1)
    {
        if (UNM == 9)
            printf (" NOVE");
        if (UNM == 8)
            printf (" OITO");
        if (UNM == 7)
            printf(" SETE");
        if (UNM == 6)
            printf (" SEIS");
        if (UNM == 5)
            printf (" CINCO");
        if (UNM == 4)
            printf (" QUATRO");
        if (UNM == 3)
            printf (" TRES");
        if (UNM == 2)
            printf (" DOIS");
        if (UNM ==1)
            printf (" UM");
    }
    // imprime "mil" antes dos valores das centenas, dezenas e unidades
    if ((CM == 0 ) && (DM!=1) && (UNM != 0))
        printf(" MIL");
    if ((CM != 0) && (DM == 0) && (UNM != 0))
    {
        printf(" MIL");
    }
    // aparece o "e" para valores particulares como 1009, 2020, 2300.
    if ((CM==0) && (DM==0) && (UNM!=0) && ((CEN!=0) || (DEZ!=0) || (UN!=0)))
    {
        printf(" E");
    }
    // imprime "mil" antes dos valores das centenas, dezenas e unidades
    if ((CM != 0) && (DM != 0) && (UNM != 0))
    {
        printf(" MIL");
    }
    // imprime "e" para valores com final de dezena e unidade iguais a 0
    if ((CM != 0) && (DM != 0) && (UNM != 0) && (CEN != 0) && (DEZ == 0) && (UN==0))
    {
        printf(" E");
    }
    // imprime valores da centena
    if (CEN == 9)
        printf ("  NOVECENTOS");
    if (CEN == 8)
        printf (" OITOCENTOS");
    if (CEN == 7)
        printf (" SETECENTOS");
    if (CEN == 6)
        printf (" SEISCENTOS");
    if (CEN == 5)
        printf (" QUINHENTOS");
    if (CEN == 4)
        printf (" QUATROCENTOS");
    if (CEN == 3)
        printf (" TREZENTOS");
    if (CEN == 2)
        printf (" DUZENTOS");
    // caso particular para o valor 100
    if ((CEN == 1) && (DEZ==0) && (UN==0))
        printf (" CEM");
    // caso para centena igual a 1 e os demais valores diferentes de 0, pelo ou menos a dezena ou unidade
    if ((CEN == 1) && ((DEZ!=0) || (UN!=0)))
    {
        printf(" CENTO");
    }
    // condicao para imprimir o "e" em casos da centena de milhar e unidade de milhar forem 0,
    // aparece ex: nove mil trezentos "e" oito
    if ((UNM !=0) && (CEN != 0) && (DEZ!=0))
        printf(" E");
    else // caso para centenas
        if ((UNM == 0) && (CEN != 0) && (DEZ!=0))
            printf(" E");
    // imprime valores da dezena
    if (DEZ == 9)
        printf (" NOVENTA");
    if (DEZ == 8)
        printf(" OITENTA");
    if (DEZ == 7)
        printf (" SETENTA");
    if (DEZ == 6)
        printf (" SESSENTA");
    if (DEZ == 5)
        printf (" CINQUENTA");
    if (DEZ ==4)
        printf (" QUARENTA");
    if (DEZ == 3)
        printf (" TRINTA");
    if (DEZ == 2)
        printf (" VINTE");
    // caso particular para o numero 10
    if ((DEZ == 1) && (UN==0))
        printf (" DEZ");
    // casos para dezena igual a 1, aparecendo doze, treze...
    if ((DEZ == 1) && (UN!=0))
    {
        if (UN == 9)
            printf (" DEZENOVE");
        if (UN == 8)
            printf (" DEZOITO");
        if (UN == 7)
            printf (" DEZESSETE");
        if (UN == 6)
            printf (" DEZESSEIS");
        if (UN == 5)
            printf (" QUINZE");
        if (UN == 4)
            printf (" QUATORZE");
        if (UN == 3)
            printf (" TREZE");
        if (UN == 2)
            printf (" DOZE");
        if (UN == 1)
            printf (" ONZE");
    }
    // imprime "e" em valores do tipo cento "e" nove, cento "e" vinte
    if ((CEN!=0) && (DEZ!=1) && (UN != 0))
        printf(" E");
    else{
        if ((DEZ!=1) && (DEZ != 0) && (UN != 0))
            printf(" E");

        }
    // imprime os valores da unidade
    if (DEZ != 1)
    {
        if (UN == 9)
            printf (" NOVE");
        if (UN == 8)
            printf (" OITO");
        if (UN == 7)
            printf (" SETE");
        if (UN == 6)
            printf (" SEIS");
        if (UN == 5)
            printf (" CINCO");
        if (UN == 4)
            printf (" QUATRO");
        if (UN == 3)
            printf (" TRES");
        if (UN == 2)
            printf (" DOIS");
        if (UN == 1)
            printf (" UM");
    }
    printf(" ");

}

//------------------------------------------------------------------------------
//PROCEDIMENTO
//OBJETIVO: APAGAR UM CLIENTE DA LISTA
//PARAMETRO: DE ENTRADA QUE SERA A POSI��O QUE O USUARIO SE ENCONTRA
//------------------------------------------------------------------------------
void apaga_cliente ()
{
    int posicao;//OBTEM A POSICAO DO CLIENTE
    int i,j;//AUXILIARES
    char c[10];//conta do usuario

    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/EXCLUIR-----\n");
    printf("\n\tCOD.\tTITULAR\t\tC/C\n");

    for (i=0;i<qtd_clientes;i++)//imprime lista de clientes
    {
        printf("\t");//espa�amento
        printf("%d\t",i+1);//imprime o c�digo do cliente na lista
        printf("%s",clientes[i]);
        printf("\t");//espa�amento
        printf("%s",conta_corrente[i]);
        printf("\n");//pula uma linha ap�s cada impress�o do cliente e sua respectiva conta
    }
    printf("\n\tINFORME A CONTA DO USUARIO QUE DESEJA EXCLUIR?\n\t(0)VOLTAR\n\t");
    gets(c);
    if (verifica_formact_conta(c)>0)
    {
        posicao = verifica_conta(c); //altera a posicao que aparece para o usuario para a posicao real que o cadastro ocoupa.
        if (posicao>-1){
            if (verifica_cliente_e_saque(posicao)==0){
                //altera a posicao do ultimo cadastro de cpf para a posicao do cliente que sera apagado
                for (i=0;i<15;i++)
                {
                    clientes[posicao][i] = clientes[qtd_clientes-1][i];
                }
                //altera a posicao do ultimo cadastro de conta para a posicao do cliente que sera apagado
                for (i=0;i<10;i++){
                    conta_corrente[posicao][i] = conta_corrente[qtd_clientes-1][i];
                }
                //retira a sua posicao do vetor que verifica quem ja fez saque pois a nova posicao sera ocupada pelo ultimo cliente
                for (i=0;i<cont;i++)
                {
                    if (verifica_sf_saque[i]==posicao)
                    {
                        verifica_sf_saque[i]=verifica_sf_saque[cont];
                        i = cont;//faz a parada imediatamente da verificacao
                    }
                }
                cont--;//RETIRA UMA POSICAO DA VARIAVEL AUXILIAR DO VETOR QUE VERIFICA QUEM JA FEZ SAQUE
                qtd_clientes--;//"retira uma posicao" da quantidade de clientes, que sera reescrevida quando fizer outro cadastro.
                system("cls");
                printf("\n\n\t!! CLIENTE APAGADO COM SUCESSO !!\n");
            }
            else{
                system("cls");
                printf("\n\t!! CLIENTE JA EFETUOU SAQUE !!\n\n");
            }
        }
        else
        {
            system("cls");
            printf("\n\tCONTA NAO EXISTE! ! \n\n");
        }
    }
    else{
        if (posicao<0 || posicao>qtd_clientes)//CASO ELE DIGITE UM NUMERO FORA DOS NUMEROS PRINTADOS PRA ELE
        {
            system("cls");
            printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/APAGA CLIENTE-----\n");
            printf("\n\t!!CONTA NAO ESTA NO FORMATO !!\n\n\t");
            system("pause");
            system("cls");//apaga tela
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUN��O: TESTA_CONTA
//TIPO: COM PASSAGEM DE PAR�METRO E COM RETORNO
//OBJETIVO: VERIFICAR SE A CONTA INFORMADA J� EXISTE
//PARAMETRO: A CONTA CORRENTE DIGITADA PELO USUARIO
//RETORNO: 0 SE NAO EXISTIR, E RETORNA 1 CASA J� EXISTA
//-------------------------------------------------------------------------------------------------------------------------------
int testa_conta(char conta[]){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int i,j,x=0;//contadores
    int qtd;//conta a quantidade de digitos iguais
    //---------------------------------------------

    for (i=0;i<=qtd_clientes;i++)//la�o verifica se a conta corrente informada ja existe para algum cadastro
    {

        if (conta == conta_corrente[i]){//verifica se os digitos s�o os mesmos na conta informada e nas contas cadastradas
            x = 1;//ou seja , ao menos uma conta dentro das cadastradas � igual a nova conta informada
            i = qtd_clientes;
        }

    }

    return (x);

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: QTD_CEDULAS
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA A QUANTIDADE DISPON�VEL PARA SAQUE DE CADA C�DULA
//-------------------------------------------------------------------------------------------------------------------------------
void qtd_cedulas(notas c){

    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/CONTAGEM DE CEDULAS-----\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("RELATORIO 'QUANTIDADE DE CEDULAS EXISTENTES'\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("\n\tVALOR \t\t QTD \n");
    printf("\n\tCEDULAS R$ 1,00   QUANTIDADE %d (",c.vernot1);//mostra a quantidade de cedulas existentes para saque de 1,00
    extenso(c.vernot1);
    printf(")");
    printf("\n\tCEDULAS R$ 2,00   QUANTIDADE %d (",c.vernot2);//mostra a quantidade de cedulas existentes para saque de 2,00
    extenso(c.vernot2);
    printf(")");
    printf("\n\tCEDULAS R$ 5,00   QUANTIDADE %d (",c.vernot5);//mostra a quantidade de cedulas existentes para saque de 5,00
    extenso(c.vernot5);
    printf(")");
    printf("\n\tCEDULAS R$ 10,00   QUANTIDADE %d (",c.vernot10);//mostra a quantidade de cedulas existentes para saque de 10,00
    extenso(c.vernot10);
    printf(")");
    printf("\n\tCEDULAS R$ 20,00   QUANTIDADE %d (",c.vernot20);//mostra a quantidade de cedulas existentes para saque de 20,00
    extenso(c.vernot20);
    printf(")");
    printf("\n\tCEDULAS R$ 40,00   QUANTIDADE %d (",c.vernot40);//mostra a quantidade de cedulas existentes para saque de 40,00
    extenso(c.vernot40);
    printf(")");
    printf("\n\tCEDULAS R$ 50,00   QUANTIDADE %d (",c.vernot50);//mostra a quantidade de cedulas existentes para saque de 50,00
    extenso(c.vernot50);
    printf(")");
    printf("\n\tCEDULAS R$ 100,00   QUANTIDADE %d (",c.vernot100);//mostra a quantidade de cedulas existentes para saque de 100,00
    extenso(c.vernot100);
    printf(")");
    printf("\n\tCEDULAS R$ 200,00   QUANTIDADE %d (",c.vernot200);//mostra a quantidade de cedulas existentes para saque de 200,00
    extenso(c.vernot200);
    printf(")");
    printf("---------------------------------------------------------------------------------\n");


}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: VALOR_SALDO
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA O SALDO DISPON�VEL DO CAIXA
//-------------------------------------------------------------------------------------------------------------------------------
void valor_saldo(notas c){

    int saldo=0;
    saldo = calcula_saldo(c);
    printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/SALDO EXISTENTE-----------\n");
    printf("----------------------------------------------------------------------------\n");
    printf("RELATORIO 'VALOR DO SALDO EXISTENTE'\n");
    printf("----------------------------------------------------------------------------\n");
    printf("R$ %d,00 (",saldo);//vari�vel acumulativa para o saldo dispon�vel
    extenso(saldo);
    printf(" REAIS)\n");
    printf("----------------------------------------------------------------------------\n");
}

//-------------------------------------------------------------------------------------------------------------------------------
//OBJETIVO: CALCULAR O VALOR DO SALDO
//PARAMETRO: c QUE � O CONJUNTO DE NOTAS
//RETORNO: O VALOR DO SALDO
//-------------------------------------------------------------------------------------------------------------------------------
int calcula_saldo (notas c)
{
    int saldo =0;

    saldo += c.vernot100;
    saldo += c.vernot10;
    saldo += c.vernot1;
    saldo += c.vernot200;
    saldo += c.vernot20;
    saldo += c.vernot2;
    saldo += c.vernot40;
    saldo += c.vernot50;
    saldo += c.vernot5;

    return (saldo);
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ABASTECE_CAIXA
//PARAMETRO: c QUE � UM REGISTRO CONTENDO AS NOTAS
//OBJETIVO: ABASTECER O CAIXA ELETRONICO INFORMANDO AS OP�OES DE ESCOLHA DE NOTAS
//-------------------------------------------------------------------------------------------------------------------------------
void abastece_caixa(notas *c){

    //DECLARA��O DE VARI�VEIS LOCAIS
    //int nota1,nota2,nota5,nota10,nota20,nota50,nota40,nota100,nota200;//tipos de cedulas a serem abastecidas
    //int menu;//leitura da op��o da nota
    //int x;//receber� o valor da diferen�a entre a quantidade de notas e o limite do tipo

    //menu de op��es

    *c.vernot1 = 2000;
    *c.vernot2 = 1500;
    *c.vernot5 = 800;
    *c.vernot10 = 700;
    *c.vernot20 = 600;
    *c.vernot40 = 500;
    *c.vernot50 = 400;
    *c.vernot100 = 200;
    *c.vernot200 = 100;

    /*if((vernot1<2000){
        vernot1 = vernot1 + nota1;//atualiza a quantidade de notas de 1,00 que o caixa possui
        if (vernot1 >= 2000){//caso as notas ultrapassem a quantidade limitada
            x = 2000-(vernot1-nota1);
            vernot1=(vernot1-nota1)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
            saldocaixa = saldocaixa+(x*1);//atualizando o caixa com o valor m�ximo de notas de 1
        }
        else{*/
            //saldocaixa = (saldocaixa+c.vernot1);//saldo do caixa aumentando o valor
        /*}
        //l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque

    }

        if (vernot2<1500){//se estiver dentro do intervalo
            vernot2 = vernot2 + nota2;//atualiza a quantidade de notas de 2,00 que o caixa possui
            if (vernot2 >= 1500){//caso as notas ultrapassem a quantidade limitada
                x = 1500-(vernot2-nota2);
                vernot2=(vernot2-nota2)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*2);//atualizando o caixa com o valor m�ximo de notas de 2
            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot2*2);//saldo do caixa aumentando o valor
            /*}
//            l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if (vernot5<800){//se estiver dentro do intervalo
            vernot5 = vernot5 + nota5;//atualiza a quantidade de notas de 5,00 que o caixa possui
            if (vernot5 >= 800){//caso as notas ultrapassem a quantidade limitada
                x = 800-(vernot5-nota5);
                vernot5=(vernot5-nota5)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*5);//atualizando o caixa com o valor m�ximo de notas de 5
            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot5*5);//saldo do caixa aumentando o valor
            /*}
//            l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if (vernot10<700){//se estiver dentro do intervalo
            vernot10 = vernot10 + nota10;//atualiza a quantidade de notas de 10,00 que o caixa possui
            if (vernot10 >= 700){//caso as notas ultrapassem a quantidade limitada
                x = 700-(vernot10-nota10);
                vernot10=(vernot10-nota10)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*10);//atualizando o caixa com o valor m�ximo de notas de 10
            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot10*10);//saldo do caixa aumentando o valor
            /*}
           // l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if ((vernot20<600)){//se estiver dentro do intervalo
            vernot20 = vernot20 + nota20;//atualiza a quantidade de notas de 20,00 que o caixa possui
            if (vernot20 >= 600){//caso as notas ultrapassem a quantidade limitada
                x = 600-(vernot20-nota20);
                vernot20=(vernot20-nota20)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*20);//atualizando o caixa com o valor m�ximo de notas de 20

            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot20*20);//saldo do caixa aumentando o valor

            /*}
           // l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if (vernot40<500){//se estiver dentro do intervalo
            vernot40 = vernot40 + nota40;//atualiza a quantidade de notas de 40,00 que o caixa possui
            if (vernot40 >= 500){//caso as notas ultrapassem a quantidade limitada
                x = 500-(vernot40-nota40);
                vernot40=(vernot40-nota40)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*40);//atualizando o caixa com o valor m�ximo de notas de 40
            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot40*40);//saldo do caixa aumentando o valor
            /*}
          //  l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if (vernot50<400){//se estiver dentro do intervalo
            vernot50 = vernot50 + nota50;//atualiza a quantidade de notas de 50,00 que o caixa possui
            if (vernot50 >= 400){//caso as notas ultrapassem a quantidade limitada
                x = 400-(vernot50-nota50);
                vernot50=(vernot50-nota50)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*50);//atualizando o caixa com o valor m�ximo de notas de 50

            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot50*50);//saldo do caixa aumentando o valor

            /*}
         //   l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }
        if (vernot100<200){//se estiver dentro do intervalo
            vernot100 = vernot100 + nota100;//atualiza a quantidade de notas de 100,00 que o caixa possui
            if (vernot100 >= 200){//caso as notas ultrapassem a quantidade limitada
                x = 200-(vernot100-nota100);
                vernot100=(vernot100-nota100)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*100);//atualizando o caixa com o valor m�ximo de notas de 100
            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot100*100);//saldo do caixa aumentando o valor
            /*}
           // l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }



        if (vernot200<200){//se estiver dentro do intervalo
            vernot200 = vernot200 + nota200;//atualiza a quantidade de notas de 200,00 que o caixa possui
            if (vernot200 >= 100){//caso as notas ultrapassem a quantidade limitada
                x = 100-(vernot200-nota200);
                vernot200=(vernot200-nota200)+x;//faz a atualiza��o da contagem de notas somente com a diferen�a
                saldocaixa = saldocaixa+(x*200);//atualizando o caixa com o valor m�ximo de notas de 200

            }
            else{*/
                //saldocaixa = saldocaixa+(c.vernot200*200);//saldo do caixa aumentando o valor
            /*}
           // l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para libera��o do saque
        }*/

}


//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: MOSTRA_SAQUES_CLIENTES
//OBJETIVO: MOSTRAR O CPF DE CADA SAQUE EFETUADO
//PARAMENTRO: c QUE � O CONJUNTO DE SAQUES DE CADA CLIENTE
//          E q QUE � A QUANTIDADE DE CLIENTES QUE FEZ SAQUE
//-------------------------------------------------------------------------------------------------------------------------------
void mostra_saques_clientes (dados c[], int q){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int i,j;
    //int a;//obtem a posicao do usuario que fez saque
    int saque;//obtem a quantidade total de saque de cada cliente
    int saque_total=0;
    //int ver;//auxilia na impressao para o usuario
    //------------------------------------

    system("cls");
    printf("\n\n\t----SISTEMA BANCARIO/GERENTE/VALORES SACADOS----\n");
    printf("--------------------------------------------------------------------------\n");
    printf("RELATORIO 'VALORES SACADOS'\n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tCONTA-CORRENTE\t\tCPF\t\t\tSAQUE\n");
    //VERIFICA SE JA FOI FEITO ALGUM SAQUE, QUE SERA CONTADO PELO OU MENOS 1 SE SIM
    if (q=!0){
        for (i=0;i<q;i++)
        {
            if (c[i].saque_valido > 0)
            {
                saque = 0;
                printf("\n\t%s\t\t%s",c[i].conta_saque, c[i].cpf_saque);
                for (j=0;j<c[i].saque_valido,j++)
                {
                    printf("\n\t\t\t\t\t\t%d",c[i].saques_clientes[j]);
                    saque += c[i].saques_clientes[j];

                }
                printf("\n\t\t\t\t\t\t\t%d",saque);
                saque_total += saque;
            }
        }
        /*if (saque_valido>0){
    //        printf("\n\tCONTA-CORRENTE\t\tCPF\t\t\tSAQUE\n");
            for (i=0;i<cont;i++)
            {
                ver=0;
                saque = 0;
                a = verifica_sf_saque[i];
                printf("\n\t%s\t\t%s",conta_corrente[a],clientes[a]);
                for (j=0;j<saque_valido;j++)//faz a itera��o at� a quantidade maxima de saques efetuado
                {
                    if ((a==obtem_posicao_cliente_cada_saque[j]) && (ver>0))//verifica se a posicao do cliente � igual a que fez o saque
                    {
                        printf("\t\t\t");
                        printf("\t\t\t\t%d\n",saques_clientes[j]);
                        saque+=saques_clientes[j];//soma os saques
                    }
                    else
                    {
                        if (a==obtem_posicao_cliente_cada_saque[j]){
                            //printf("\t\t");
                            printf("\t\t%d\n",saques_clientes[j]);
                            saque+=saques_clientes[j];//soma os saques
                            ver++;//incrementa para que a nova impressao seja ativa com um \t a mais
                        }
                    }
                }
                printf("\t\t\t");
                printf("\t\t\t\t\t%d",saque);
                saque_total+=saque;
            }
        }*/
    }
    printf("\n--------------------------------------------------------------------------\n");
    printf("TOTAL: R$ %d,00(",saque_total);
    extenso(saque_total);
    printf(" REAIS)");
    printf("\n--------------------------------------------------------------------------\n");
    printf("\n\t");
    system("pause");
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: LIBERAR_NOTAS
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: ATUALIZAR AS NOTAS DO CAIXA E IMPRIMIR O SAQUE
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------------------------------------------------
void liberar_notas(int a200,int a100, int a50, int a40, int a20, int a10, int a5, int a2, int a1, notas *c)//cedulas que vao ser retiradas
{

    //notas de 200
    if (a200>0) {
        printf("\n\t%d NOTA(S) - R$ 200,00",a200); // mostrando as notas que sairam
        *c.vernot200 = *c.vernot200 - a200; // diminuindo a quantidade de notas do caixa
        //saldocaixa = saldocaixa - (a200*200);
        //totsak = totsak + (a200*200);
    }
    //notas de 100
    if (a100>0) {
        printf("\n\t%d NOTA(S) - R$ 100,00",a100); // mostrando as notas que sairam de 100
        *c.vernot100 = *c.vernot100 - a100; // subtraindo o quantidade de notas do caixa
        //saldocaixa = saldocaixa - (a100*100);
        //totsak = totsak + (a100*100);
    }
    //notas de 50
    if (a50>0){
        printf("\n\t%d NOTA(S) - R$ 50,00",a50); // mostrando as notas que foram retiradas
        *c.vernot50 = *c.vernot50 - a50; // diminuindo as notas de 50 do caixa
        //saldocaixa = saldocaixa - (a50*50);
        //totsak = totsak + (a50*50);
    }
    //notas de 40
    if (a40>0){
        printf("\n\t%d NOTA(S) - R$ 40,00",a40); // mostrando as notas que foram retiradas
        *c.vernot40 = *c.vernot40 - a40; // diminuindo as notas de 40 do caixa
        //saldocaixa = saldocaixa - (a40*40);
        //totsak = totsak + (a40*40);
    }
    //notas de 20
    if (a20>0) {
        printf("\n\t%d NOTA(S) - R$ 20,00",a20); // mostra as notas retiradas
        *c.vernot20 = *c.vernot20 - a20; // subtrai-se as notas do caixa com as notas retiradas, para serem retiradas do caixa
        //saldocaixa = saldocaixa - (a20*20);
        //totsak = totsak + (a20*20);
    }
    //notas de 10
    if (a10>0) {
        printf("\n\t%d NOTA(S) - R$ 10,00",a10);
        *c.vernot10 = *c.vernot10 - a10;
        //saldocaixa = saldocaixa - (a10*10);
        //totsak = totsak + (a10*10);
    }
    //notas de 5
    if (a5>0) {
        printf("\n\t%d NOTA(S) - R$ 5,00",a5);
        *c.vernot5 = *c.vernot5 - a5;
        //saldocaixa = saldocaixa - (a5*5);
        //totsak = totsak + (a5*5);
    }
    //notas de 2
    if (a2>0) {
        printf("\n\t%d NOTA(S) - R$ 2,00",a2);
        *c.vernot2 = *c.vernot2 - a2;
        //saldocaixa = saldocaixa - (a2*2);
        //totsak = totsak + (a2*2);
    }
    //notas de 1
    if (a1>0) {
        printf("\n\t%d NOTA(S) - R$ 1,00",a1);
        *c.vernot1 = *c.vernot1 - a1;
        //saldocaixa = saldocaixa - a1;
        //totsak = totsak + a1;
    }
    printf("\n\t");

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUN��O: VER_CAIXA_SAQUE_0
//TIPO: COM PASSAGEM DE PAR�METRO E COM RETORNO
//OBJETIVO: VERIFICAR SE H� NOTAS SUFICIENTES PARA EFETUAR O SAQUE
//PARAMETRO: DE ENTRADA QUE � O SAQUE
//RETORNO: saque_ced, QUE VAI SER 0 SE HOUVER CEDULAS E <> DE 0 SE NAO HOUVER CEDULAS
//-------------------------------------------------------------------------------------------------------------------------------
int Ver_caixa_saque_0(int saq_ced, int *a200, int *a100, int *a50, int *a40, int *a20, int *a10, int *a5, int *a2, int *a1, notas c)
{

    if ((saq_ced/200>0) && (c.vernot200>0)) // caso houver notas suficientes para serem retiradas corretamente
    {

        *a200 = saq_ced/200;
        if (c.vernot200>=*a200)
        {
            saq_ced = (saq_ced - (*a200*200));
        }
        else{
            *a200 = c.vernot200; // como esgtaram as notas de 500, as notas que haviam sairam todas.
            saq_ced = (saq_ced - (*a200*200));
        }
    }
    if ((saq_ced/100>0) && (c.vernot100>0)) // se houver notas de 150 a mais ou igual
    {
        *a100 = saq_ced/100;
        if (c.vernot100>=*a100){
            *a100 = saq_ced/100;
            saq_ced = saq_ced - (*a100*100);
        }
        else{
            *a100 = c.vernot100; // Como as notas do caixa sao menores do que as notas que poderiam ser
                            // retiradas se houvesse mais, as notas retiradas fica com o mesmo valor das notas do caixa
            saq_ced = (saq_ced - (*a100*100));
        }
    }
    if ((saq_ced/50>0) && (c.vernot50>0)) // caso houver notas suficientes para serem retiradas
    {

        *a50 = saq_ced/50;
        if (c.vernot50>=*a50){
            saq_ced = saq_ced - (*a50*50);
        }
        else{
            *a50 = c.vernot50; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (*a50*50));
        }
    }
    if ((saq_ced/40>0) && (c.vernot40>0)) // caso houver notas suficientes para serem retiradas
    {

        *a40 = saq_ced/40;
        if (c.vernot40>=*a40){
            saq_ced = saq_ced - (*a40*40);
        }
        else{
            *a40 = c.vernot40; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (*a40*40));
        }
    }
    if((saq_ced/20>0) && (c.vernot20>0)) // caso as notas de 20 forem suficientes
    {

        *a20 = saq_ced/20;
        if (c.vernot20>=*a20){
            saq_ced = (saq_ced - (*a20*20));
        }
        else{
            *a20 = c.vernot20;
            saq_ced = (saq_ced - (*a20*20));
        }
    }
    if ((saq_ced/10>0) && (c.vernot10>0))
    {

        *a10 = saq_ced/10;
        if (c.vernot10>=*a10){
            saq_ced = saq_ced - (*a10*10);
        }
        else{
            *a10 = c.vernot10;
            saq_ced = (saq_ced - (*a10*10));
        }
    }
    if ((saq_ced/5>0) && (c.vernot5>0))
    {

        *a5 = saq_ced/5;
        if (c.vernot5>=*a5){
            saq_ced = saq_ced - (*a5*5);
        }
        else{
            *a5 = c.vernot5;
            saq_ced = (saq_ced - (*a5*5));
        }
    }
    if ((saq_ced/2>0) && (c.vernot2>0))
    {

        *a2 = saq_ced/2;
        if (c.vernot2>=*a2){
            saq_ced = saq_ced - (*a2*2);
        }
        else{
            *a2 = c.vernot2;
            saq_ced = saq_ced - (*a2*2);
        }
    }
    if (c.vernot1>0)
    {
        *a1 = saq_ced;
        saq_ced = saq_ced - *a1;

    }
    return (saq_ced);

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUN��O: VERIFICA_CONTA
//TIPO: COM PASSAGEM DE PAR�METRO E COM RETORNO
//OBJETIVO: VERIFICAR A POSI��O DA CONTA DENTRO DO VETOR CASO SEJA EXISTENTE
//PARAMETRO: A CONTA DIGITADA
//RETORNO: RETORNA -1 SE N�O HOUVER CONTA, E RETORNA A POSICAO DA CONTA SE HOUVER CONTA CORRENTE IGUAL
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_conta(char conta[]){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int j; //j varia a posic�o da conta

    //--------------------------------------------------------

    for (j=0;j<qtd_clientes;j++)
    {
        if (strcmp(conta,conta_corrente[j])==0)
        {
            return(j);
        }

    }
    return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------
//FUN��O: TESTA_CPF
//TIPO: COM PASSAGEM DE PAR�METRO E COM RETORNO
//OBJETIVO: VERIFICAR SE HA UM CPF JA CADASTRADO
//PARAMETRO: O CPF DIGITADO PELO USUARIO
//RETORNO: 0 SE NAO HOUVER CADASTRO, E RETORNA 1 CASA HAJA O CADASTRO
//-------------------------------------------------------------------------------------------------------------------------------
int testa_cpf(char cpf[]){

    //DECLARA��O DE VARIAVEIS LOCAIS
    int i,j;//contadores
    int qtd;//conta os digitos iguais

    for (i=0;i<qtd_clientes;i++)//la�o verifica se o cpf informado j� possui cadastro
    {
        if (strcmp(cpf,clientes[i]) == 0)
        {
            return 1;
        }
    }
    return 0;

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUN��O: VERIFICA_CLIENTE_E_SAQUE
//TIPO: COM PASSAGEM DE PAR�METRO E COM RETORNO
//OBJETIVO: VERIFICAR SE O CLIENTE JA FEZ ALGUM SAQUE
//PARAMETRO: DE ENTRADA QUE � A POSICAO QUE O CLIENTE SE ENCONTRA
//RETORNO:  1 SE O CLIENTE EFETUOU ALGUM SAQUE CASO CONTRARIO DEVOLVE 0
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_cliente_e_saque(int pos,usuario c[]){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int i;

    //for (i=0;i<q;i++)
    //{
    if (c[pos].saque==1)
    {
            return 1;
    }
    //}

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ALTERA_CLIENTE
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: ALTERAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void altera_cliente()
{

    //DECLARA��O DE VARI�VEIS LOCAIS
    int i,j;
    int x;//recebe o valor retornado pela fun��o testa_cpf ap�s verifica��o se ha um cpf ja cadastrado
    int op2;//op��es durante a execu��o da fun��o
    char ncpf[15];//vetor para receber o cpf no formato 999.999.999-99
    char cpf[15];//recebe o cpf caso queira muda-lo
    char c[10];//faz a leitura da conta que deseja alterar
    char conta[10];//vetores para conta corrente em uma array de caracteres
    int pos; //recebe a posicao do cliente
    int a;// faz a verificacao do formato do cpf


    //---------------------------------------------

    printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
    printf("\n\tCOD.\tTITULAR\t\tCONTA/CORRENTE\n");

    for (i=0;i<qtd_clientes;i++)//imprime lista de clientes
    {
        printf("\t%d\t%s\t%s\n",i+1,clientes[i],conta_corrente[i]);//imprime o c�digo do cliente na lista
    }
    printf("\n\tINFORME A CONTA DO CLIENTE QUE DESEJA ALTERAR..FORMATO (999.999-X)\n\t");
    gets(c);//faz a leitura do codigo do cliente para altera��es

    if (verifica_formact_conta(c)>0){
        pos = verifica_conta(c);//obtendo a posicao do cliente
        if (pos>-1){
            if (verifica_cliente_e_saque(pos)==0){
                while ((op2>2) || (op2<1)){
                    system("cls");
                    printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
                    printf("\n\tCOD.\tTITULAR\t\tCONTA/CORRENTE\n");

                    //for (i=op-1;i<op;i++)//imprime a lista de clientes
                    //{
                    printf("\t");
                    printf("\t");
                        //for (j=0;j<11;j++)
                        //{
                    printf("%s",clientes[pos]);
                        //}

                    printf("\t");//espa�amento

                        //for (j=0;j<6;j++)//imprime os dados da conta-corrente
                        //{
                    printf("%s",conta_corrente[pos]);
                        //}
                    //}
                    printf("\n");

                    printf("\n\tALTERAR:\n\t1.CPF\n\t2.C/C\n\t");
                    scanf("%d",&op2);
                    if ((op2>2) || (op2<1)){
                        system("cls"); // apaga tela
                        printf("\n\tOPCAO INVALIDA..\n\t");
                            //system("pause");
                    }
                    else{
                        //printf("%d",verifica_cliente_e_saque(op2-1));
                        //system("pause");
                        switch(op2){

                            case 1:
                                //system("cls"); // apaga tela
                                printf("\n\tDIGITE O NOVO CPF: (FORMATO: 999.999.999-99)\n\t");
                                gets(cpf);
                                a = verifica_formact_cpf(cpf);
                                if(a>0){
                                    tira_cpf_formato(cpf);//tira o formato do cpf para poder fazer a verificacao de validade
                                    if (verifica_cpf_valido(cpf)==1){
                                        insere_pontuacao_cpf(cpf,ncpf);
                                        x = testa_cpf(ncpf);
                                        if (x == 0){
                                            for (j=0;j<15;j++)
                                            {
                                                clientes[pos][j] = ncpf[j];
                                            }
                                            system("cls");
                                            printf("\n\t!!CPF VALIDO!!\n\tCADASTRO ATUALIZADO!\n");
                                        }
                                        else{
                                            system("cls");
                                            printf("\n\t!! CPF JA CADASTRADO !!\n\n\t");
                                            system("pause");
                                            system("cls");
                                        }
                                    }
                                    else{
                                        system("cls"); // apaga tela
                                        printf("\n\t!!CPF INVALIDO!!\n\t");
                                        system("pause");
                                        system("cls");
                                    }
                                }
                                else
                                {
                                    system("cls");
                                    printf("\n\tCPF NAO ESTA NO FORMATO!!\n\t");
                                    system("pause");
                                    system("cls");
                                }

                            break;
                            case 2:
                                printf("\n\tDIGITE A NOVA CONTA CORRENTE:\n\t");
                                gets(conta);
                                a = verifica_formact_conta(conta);
                                if (a>0){
                                    if (verifica_conta(conta) > -1)
                                    {
                                        system("cls");
                                        printf("\n\t !! CONTA JA POSSUI CADASTRO !!\n\t");
                                        system("pause");
                                        system("cls");
                                    }
                                    else{
                                        for (j=0;j<10;j++)
                                        {
                                            conta_corrente[pos][j] = conta[j];
                                        }
                                        system("cls");
                                        printf("\n\t !! CADASTRO ATUALIZADO !!\n");
                                    }
                                }
                                else
                                {
                                    system("cls");
                                    printf("\n\tCONTA NAO ESTA NO FORMATO!\n");
                                    system("pause");
                                    system("cls");
                                }
                            break;
                        }
                    }
                }
            }
            else{
                system("cls"); // apaga tela
                printf("\n\t!! CLIENTE JA EFETUOU UM SAQUE!!!\n");
            }
        }
        else
        {
            system("cls");
            printf("\n\tNAO EXISTE CLIENTE COM ESSA CONTA! !");
        }
    }
    else
    {
        system("cls");
        printf("\n\tFORMATO NAO ACEITO!!\n");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------
//objetivo:verifica se um cpf no formato 999.999.999-99 e valido
//parametros: cpf:cpf a ser verificado
//retorno: 1 se cpf e valido ou 0 se cpf nao e valido
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_cpf_valido(char cpf[]){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int i;
    int v,qtd=0;
    int valido=1;//ser� o retorno da fun��o
    int cpfi[12];
    //-----------------------------

    for (i=0;i<12;i++)
    {
        cpfi[i] = cpf[i]-48;
    }
    v = cpfi[0];//v recebe primeiro digito do cpf para fazer verifica��o

    for (i=1;i<11;i++)//o la�o ira contar a quantidade de digitos iguais no cpf
    {
        if (cpfi[i] == v)
            qtd = qtd+1;
    }

    if (qtd == 10){//caso todos os digitos sejam o mesmo o cpf � inv�lido
        valido--;
        system("pause");
        return (valido);
    }
    else{
        if (cpfi[9]==obtem_primeiro_digito_verificador(cpf))
        {
            printf("AQUIIII!!!3");
            if (cpfi[10]==obtem_segundo_digito_verificador(cpf))
            {
                printf("AQUIIII!!!4");
                return(valido);
            }
        }
    }
    printf("AQUIIII!!!2");
    system("pause");
    valido--;
    return(valido);
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: CADASTRO_CLIENTE
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: EFETUAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void cadastro_cliente(usuario c[], int *q){

    //DECLARA��O DE VARI�VEIS LOCAIS------------------------------
    char ncpf[15];//vetor armazena CPF
    char conta[10];//vetor armazena dados da conta corrente
    int x,y,z;  //y verifica se ha um cpf ja cadastrado
                //x verifica
    int i,j;//contadoras
    usuario cc;


    //------------------------------------------------------------
    gera_cpf_valido(ncpf);
    strcpy(c[*q].clientes,ncpf);
    Sleep(250);
    geraContaCorrente(conta);
    strcpy(c[*q].conta_corrente,conta);
    printf("\n\t- CLIENTE INCLUIDO COM SUCESSO\n");
    printf("\n\tCPF: %s",c[*q].clientes);
    printf("\n\tCONTA: %s",c[*q].conta_corrente);
    *q++;
    //qtd_clientes++;


}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um cpf valido no formato 999.999.999-99
//parametros: cpf:o cpf onde sera armazenado o cpf valido
//---------------------------------------------------------------------------------
void gera_cpf_valido(char cpf[]) {

    int j;
    char ncpf[15];//obtem cpf no formato
    int y;//verifica se cpf ja existe
    int ver;

    //srand(time(NULL));
    for (j=0;j<9;j++){
        cpf[j]=rand()%9+48;
    }
    srand(time(NULL));
    do{
        cpf[9] = obtem_primeiro_digito_verificador(cpf)+48;
        cpf[10] = obtem_segundo_digito_verificador(cpf)+48;
        insere_pontuacao_cpf(cpf,ncpf);
        y = testa_cpf(ncpf);
    }while(y!=0);
    strcpy(cpf,ncpf);

}

//---------------------------------------------------------------------------------
//objetivo:calcula o primeiro digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: o calculo do primeiro digito verificador
//---------------------------------------------------------------------------------
int obtem_primeiro_digito_verificador(char cpf[]) {

    int digito, result,i, somador=0,cpfi[9];

    for (i=0;i<9;i++)
    {
        cpfi[i] = cpf[i]-48;
    }

    for(i=0;i<9;i++)
    {
        somador =somador+(cpfi[i]*(10-i));
    }

    result=somador%11;

    if(result<2){
        digito=0 ;
    }
    else{
        digito = 11-result;
    }
    return(digito);
}

//---------------------------------------------------------------------------------
//objetivo:calcula o segundo digito verificador de um cpf no formato 999999999
//parametros: cpf:o cpf sem os digitos verificadores
//retorno: o calculo do segundo digito verificador
//---------------------------------------------------------------------------------
int obtem_segundo_digito_verificador(char cpf[]) {
   int digito, somador=0, i, result,cpfi[10];

    for (i=0;i<10;i++)
    {
        cpfi[i] = cpf[i]-48;
    }

    for(i=0;i<10;i++)
    {
        somador= somador + (cpfi[i]*(11-i));
    }

    result=somador%11;

    if(result<2){
        digito=0;
    }
    else{
        digito=11-result;
    }

   return(digito);
}

//------------------------------------------------------------
//objetivo: colocar o cpf no formato 999.999.999-99
//parametro: cpf, que � o cpf do usuario
//-------------------------------------------------------------
void insere_pontuacao_cpf(char cpf_origem[], char cpf_destino[])
{
    int i;
    int cont=0;//auxilia o cpf_destino para pegar
                // as posicoes certas do cpf pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do cpf_origem muda

    for (i=14;i>-1;i--)
    {
        if (i==14)
        {
            cpf_destino[i]='\0';
        }
        else{
            if (i!=3 && i!=7 && i!=11){
                if (cont==0){
                    cpf_destino[i]=cpf_origem[i-3];
                }
                else
                {
                    if(cont==1)
                    {
                        cpf_destino[i]=cpf_origem[i-2];
                    }
                    else{
                        if (cont==2)
                        {
                            cpf_destino[i]=cpf_origem[i-1];
                        }
                        else
                        {
                            if (cont==3)
                            {
                                cpf_destino[i]=cpf_origem[i];
                            }
                        }
                    }
                }
            }
            else
            {
                if (i==11)
                {
                    cpf_destino[i]='-';
                    cont++;
                }
                else
                {
                    if(i==7)
                    {
                        cpf_destino[i]='.';
                        cont++;
                    }
                }
                if (i==3)
                {
                    cpf_destino[i]='.';
                    cont++;
                }
            }
        }
    }
}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero de conta corrente no formato 999.999-X
//parametros: c:onde armazera a conta gerada
//retorno:nenhum
//---------------------------------------------------------------------------------
void geraContaCorrente(char c[]) {

    int i;
    int y;

    Sleep(250);
    srand(time(NULL));
    for (i=0;i<6;i++){
        c[i]=rand()%9+48;
    }
    do{
        c[6] = geraAlfabeto();
        colocando_conta_formato(c);
        y = testa_conta(c);
    }while(y==-1);

}

//---------------------------------------------------------------------------------
//objetivo:escolhe dentre as letras do alfabeto ('a'..'z') uma letra aleatoriamente
//parametros: nenhum
//retorno:a letra do alfabeto
//---------------------------------------------------------------------------------
char geraAlfabeto() {
    int i;
    char letras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    i=rand()%26;
    return(letras[i]-32);
}


//---------------------------------------------------------------------------------
//objetivo: colocar a conta no formato
//parametro: o cpf
//---------------------------------------------------------------------------------
void colocando_conta_formato(char c[])
{
    int i;
    int a=0;//auxilia a variacao de posicoes no cpf
            //pois cada vez que coloca-se um . ou um -
            // as novas posicoes a serem deslocadas
            //serao de outra forma, com outra logica

    for (i=8;i>2;i--)
    {
        if (i!=3 && i!=7)
        {
            if (a==0){
                c[i]=c[i-2];
            }
            else
            {
                c[i]=c[i-1];
            }
        }
        else
        {
            if (i==7)
            {
                c[i]='-';
                a++;
            }
            else
            {
                c[i]='.';
            }
        }
    }
    c[9]='\0';
}

//-----------------------------------------------------------------------
//objetivo: verificar se o cpf esta no formato.
//parametro: o cpf
//retorno: a que ser� 1 para verdadeiro e menor que 1 falso
//-----------------------------------------------------------------------
int verifica_formact_cpf(char cpf[])
{
    int a=-2; //incializo com -2 para atualizar at� no maximo 1
    int i;

    gets(cpf);
    for (i=0;cpf[i]!='\0';i++)
    {
        if (cpf[i]=='.')
        {
            if (i==3)//posicao especifica para o .
            {
                a++;
            }
            if (i==7)//proxima posicao especifica para o .
            {
                a++;
            }
        }
        if(cpf[i]=='-')
        {
            if (i==11)//posicao especifica para o -
            {
                a++;
            }
        }
    }
    //064.524.065-66
    return (a);
}


//-------------------------------------------------------------------------
//objetivo: verifica se a conta esta no formato
//parametro: a conta digitada
//retorno: retorna 1 se estiver no formato, e outro valor se nao estiver
//-------------------------------------------------------------------------
int verifica_formact_conta (char conta[])
{
    int i;
    int a=-2;//incializo com -2 para ir atualizando at� no maximo 1
    char letter;

    gets(conta);

    for (i=0;i<15;i++)
    {
        if (conta[i]=='.')
        {
            if (i==3){//posicao especifica do .
                a++;
            }
        }

        if (conta[i]=='-')
        {
            if (i==7)//posicao especifica para o -
            {
                a++;
            }
        }
    }
    if(isalpha(conta[8]))
    {
        a++;
    }
    return(a);
}

//---------------------------------------------------------------------------------
//objetivo: tirar os pontos e o traco do cpf para fazer verificacao de cpf valido
//parametro: o cpf
//---------------------------------------------------------------------------------
void tira_cpf_formato (char cpf[])
{
    int i;
    int a=0;//auxilia as posicoes do cpf novo

    for (i=0;i<15;i++)
    {
        if (i!=3 && i!=7 && i!=11)
        {
            cpf[a]=cpf[i];
            a++;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: IMPRIME_CLIENTES
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBEJTIVO: IMPRIMIR O CADASTRO DE CADA CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void imprime_clientes(){

    //DECLARA��O DE VARIAVEIS LOCAIS
    int i,j;//contadores
    //--------------------------------

    printf("\n\n\t---SISTEMA BANCARIO/CLIENTE/LISTA DE CLIENTES---\n");//guia usu�rio
    printf("\n\tTITULAR\t\tCONTA/CORRENTE\n");
    for (i=0;i<qtd_clientes;i++)
    {
        printf("\t%s\t%s\n",clientes[i],conta_corrente[i]);
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_CLIENTE
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: OFERECER AS OP��ES DO MENU DA OP��O 'CLIENTE'
//-------------------------------------------------------------------------------------------------------------------------------
void f_cliente(usuario c[], int *q){
    //VARIAVEIS LOCAIS MENU_CLIENTE
    int menu_cli;//leitura da op��o digitada no menu

    menu_cli=0;//inicializa��o da vari�vel menu_cli

    while(menu_cli != 5){
        printf("\n\n\t------SISTEMA BANCARIO/CLIENTE---\n");
        printf("\t- 1...INCLUIR         -\n");
        printf("\t- 2...MOSTRAR           -\n");
        printf("\t- 3...ALTERAR           -\n");
        printf("\t- 4...EXCLUIR            -\n");
        printf("\t- 5...VOLTAR                    -\n");
        printf("\t---------------------------------\n\n");
        printf("\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%d", &menu_cli);

        if (menu_cli == 1){
            system("cls");
            cadastro_cliente(c,&*q);//chamada da fun��o de cadastro do cliente
        }

        if (menu_cli == 2){
            system("cls");
            imprime_clientes();//chamada do procedimento que imprime a lista de clientes
        }

        if (menu_cli == 3){
            system("cls");
            altera_cliente();
        }

        if (menu_cli == 4){
            system("cls");
            apaga_cliente();
        }
        if (menu_cli==5)
        {
            system("cls");
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_SAQUE
//PARAMETRO: c QUE � O CONJUNTO DE REGISTRO DOS SAQUES
//OBJETIVO: OFERECER AO USU�RIO A OP��O DE SAQUE
//-------------------------------------------------------------------------------------------------------------------------------
void f_saque(dados c[], int *q, notas *n){

    //DECLARA��O DE VARI�VEIS LOCAIS
    int a200=0, a100=0, a50=0, a40=0, a20=0, a10=0, a5=0, a2=0, a1=0;//cedulas que vao ser retiradas
    int saque;//faz leitura do saque
    int posi;//recebe a posicao que o usuario esta na matriz
    char cc[10];//conta do usuario
    int i,j;
    int ver;//verifica se a conta esta no formato 999.999-x
    int lugar;//recebe o local que o usuario esta no vetor de dados de saque c
    //---------------------------------------------------------

    system("cls");//apaga tela
    printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");//guia usu�rio
    printf("\n\tSALDO: %d\n",saldocaixa);
    printf("\n\tDIGITE OS DADOS DA CONTA CORRENTE: FORMATO(999.999-X)\n\t");
    gets(cc);
    ver = verifica_formact_conta(cc);
    if (ver>0){
        posi = verifica_conta(cc);                                     //     <-------VERIFICAR ESSA PARTE DEPOIS
                                                                        //     PARA VERIFICAR SE A CONTA EST� CADASTRADA
                                                                        //      ESSA PARTE � DA RAFA! !
        if (posi > -1){
            system("cls");
            printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");
            printf("\t- INFORME O VALOR DO SAQUE..\n\t- (0) VOLTAR \n\t");
            scanf("%d", &saque);// recenbendo o saque
            if (saque == 0){
                system("cls");
            }

            while (saque<0){
                printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                printf("\t- INFORME O VALOR DO SAQUE..\n\t- (0) VOLTAR \n\t");
                scanf("%d",&saque); // fazendo a leitura do saque do usuario
            }

            if (saque > saldocaixa)
            {
                system("cls");
                printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                printf("\n\t !! SALDO INDISPONIVEL !!\n");
                printf("\n\t-NOTAS DE 1,00   = %d",*n.vernot1);
                printf("\n\t-NOTAS DE 2,00   = %d",*n.vernot2);
                printf("\n\t-NOTAS DE 5,00   = %d",*n.vernot5);
                printf("\n\t-NOTAS DE 10,00  = %d",*n.vernot10);
                printf("\n\t-NOTAS DE 20,00  = %d",*n.vernot20);
                printf("\n\t-NOTAS DE 40,00  = %d",*n.vernot40);
                printf("\n\t-NOTAS DE 50,00 = %d",*n.vernot50);
                printf("\n\t-NOTAS DE 100,00 = %d",*n.vernot100);
                printf("\n\t-NOTAS DE 200,00 = %d\n\n\t",*n.vernot200);
                system("pause");
            }

            if (saldocaixa >= saque){
                printf("\tCONTANDO CEDULAS..");
                for (i = 0; i <= 70; i++)
                {
                    printf("  %d%%\r", i);
                    fflush(stdout);
                    for (j = 0; j < i; j++)
                    {
                        if (!j) // Da espaco na barra pra nao enconstar na borda da tela
                            printf("  ");

                        printf("%c", 219);
                        Sleep(0);
                    }
                }
                if (Ver_caixa_saque_0(saque,&a200,&a100,&a50,&a40,&a20,&a10,&a5,&a2,&a1,n)!=0)
                {
                    system("cls"); // apaga tela
                    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                    printf("\n\t !! CEDULAS NECESSARIAS PARA SAQUE INSUFICIENTES !!\n\t");
                }
                else{
                    if (saque != 0){
//                        m++;//incrementa o m para avisar que j� foi efetuado saque!
                        Sleep (1000);
                        printf ("\r \t\t\t\t \n\n\n");
                        system("cls");
                        printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                        printf("\n\tSAQUE EFETUADO COM SUCESSO..");
                        liberar_notas(a200,a100,a50,a40,a20,a10,a5,a2,a1,&n);
                        extenso(saque);
                        printf(" REAIS");
                        if (q==0)
                        {
                            strcpy(c[*q].conta_saque,cc);
                            c[*q].saques_clientes[c[q].saque_valido] = saque;
                            //c[q].totsak += saque;
                            c[*q].saque_valido++;
                            //FALTA O CPF AQ ! ! ! ! !!
                            *q++;
                        }
                        else
                        {
                            lugar = procura_posicao_novetor_saq(cc,c,q);//obtem a posicao do o usuario que deseja fazer um saque
                                                                        //dentro do vetor de dados do saque
                            if (lugar>-1)
                            {
                                c[lugar].saque_valido++;
                                c[lugar].saques_clientes[c.[lugar].saque_valido] = saque;
                                //c[lugar].totsak += saque;
                            }
                            else
                            {
                                strcpy(c[*q].conta_saque,cc);
                                c[*q].saques_clientes[c[q].saque_valido] = saque;
                                //c[q].totsak += saque;
                                c[*q].saque_valido++;
                                *q++;
                                //FALTA O CPF AQ ! ! ! ! !!  (OBS: VAMOS UTILIAR A VARIAVEL posi)
                            }
                        }
                        //obtendo o cpf de quem sacou
                        /*for (i=0;i<11;i++)
                        {
                            cpf_saque[saque_valido][i]=clientes[posi][i];
                        }
                        //obtendo o saque do cliente
                        saques_clientes[saque_valido] = saque;
                        if (cont>0){
                            if (verifica_cliente_e_saque(posi)==0)
                            {
                                verifica_sf_saque[cont]=posi;
                                cont++;
                            }
                        }
                        else
                        {
                            verifica_sf_saque[cont]=posi;
                            cont++;
                        }
                        //obtem_posicao_cliente_cada_saque[saque_valido] = posi;
                        saque_valido++;*/
                    }
                }

            }
        }
        else{
            system("cls"); // apaga tela
            printf("\n\t !! CONTA CORRENTE NAO CADASTRADA NO SISTEMA !!\n\t");
        }
    }
    else
    {
        printf("\n\tFORMATO DA CONTA NAO SUPORTADO!!\n");
    }
}

//---------------------------------------------------------------------------------------------------------
//OBJETIVO: VERIFICA SE UMA CONTA ESTA DENTRO DO VETOR DE DADOS DOS SAQUES
//PARAMETRO: conta, QUE � A CONTA QUE VEREMOS SE ESTA NO CONJUNTO, c � O CONJUNTO DE DADOS DE SAQUE
//          E q QUE � A QUANTIDADE DE PESSOAS QUE J� FEZ SAQUE.
//RETORNO: ver, QUE VAI SER -1 SE NAO ENCONTRAR NO VETOR, OU ALGUM VALOR REPRESENTANDO A POSICAO NO VETOR
//---------------------------------------------------------------------------------------------------------
int procura_posicao_novetor_saq (char conta[], dados c[], int q)
{
    int i;
    int ver=-1;//vai obter a posicao no vetor onde se encontra
                // se � que o cliente dessa conta fez saque.
    for (i=0;i<q;i++)
    {
        if (strcmp(conta,c[i].conta_saque)==0)
        {
            ver = i;
        }
    }
    return (ver)
}
//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: menu_relatorio
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: OFERECER AO USU�RIO A OP��O DO MENU GERENTE
//-------------------------------------------------------------------------------------------------------------------------------
void menu_relatorio(dados c[], int q, notas c){

    //DECLARA�AO DE VARIAVEIS LOCAIS
    int menu2;//menu gerente
    //------------------------------------
    menu2 = 0;//inicializa��o da vari�vel
    system("cls");

    while (menu2 != 4){
                //menu de op��es
        system("cls");
        printf("\n\n\t----------SISTEMA BANCARIO/MENU RELATORIO-----------\n");
        printf("\t- 1...VALORES SACADOS                       -\n");
        printf("\t- 2...VALOR SALDO EXISTENTE                 -\n");
        printf("\t- 3...QUANTIDADE DE CEDULAS EXISTENTES      -\n");
        printf("\t- 4...MENU PRINCIPAL                        -\n");
        printf("\t---------------------------------------------");
        printf("\n\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%d", &menu2);//leitura da op��o digitada pelo usu�rio
        if (menu2==1){
            mostra_saques_clientes(c,q);
        }
        if (menu2 == 2){//op��o2 valor saldo existente
            /*if (l == 0){//verifica se o caixa eletronico j� foi abastecido
                system("cls"); // comando apaga tela
                //caso n�o tenha sido abastecido ainda a mensagem aparecer� na tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/SALDO DO CAIXA-----\n");
                printf("\n\tSALDO = 0,00. ABASTECA O CAIXA..\n\n\t");
                system("pause");
            }*/
            //if (l != 0){//caso o caixa ja tenha sido abastecido ao menos uma vez
            system("cls"); // comando apaga tela
            valor_saldo(c);//chamada do procedimento valor_saldo
            system("pause");
            //}
        }
        if (menu2 == 3){//op��o3 quantidade de c�lulas
                system("cls");//comando apaga tela
                qtd_cedulas(c);//chamada do procedimento
                printf("\n\n\t");
                system("pause");
        }

    }
    system("cls"); // comando apaga tela
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: FINALIZA
//TIPO: SEM PASSAGEM DE PAR�METRO E SEM RETORNO
//OBJETIVO: IMPRIMIR UMA BARRA DE CARREGAMENTO
//-------------------------------------------------------------------------------------------------------------------------------
void finaliza(){

    int i,j;

    printf ("\n\nFINALIZANDO PROGRAMA..\n\n");
    for (i = 0; i <= 70; i++)
    {
        printf ("  %d%%\r", i);
        fflush (stdout);
        for (j = 0; j < i; j++)
        {
            if (!j) // Da espaco na barra pra nao enconstar na borda da tela
            printf ("  ");
            printf ("%c", 219);
            Sleep(0);
        }
    }
    printf ("\n\nEncerrando...");
    Sleep (1000);
    printf ("\r \t\t\t\t \n\n\n");
    system("cls");

}


//PRINCIPAL
int main(){

    //DECLARA��O DE VARI�VEIS
    char menu;//menu principal
    //saques dos clientes
    //----------------------------------------------------------------------
    FILE *filesaque; //arquivo que tem os dados do saque
    dados vdados[1000];//vetor que vai obter tudo do arquivo
    dados rdados;//registro do mesmo tipo do vetor para fazer a copia
    int q=0;//representa quantos registros foram copiados
    //-----------------------------------------------------------------------
    //c�dulas do caixa
    //-----------------------------------------------------------------------
    FILE *filecedula;
    notas rnotas;
    //-----------------------------------------------------------------------
    //CADASTROS DOS CLIENTES
    //-----------------------------------------------------------------------
    FILE *fileclientes
    usuario vcliente[1000];
    usuario rcliente;
    int u=0;
    //-----------------------------------------------------------------------
    int i;
    //-------------------------------

     //ABRINDO O ARQUIVO DOS DADDOS DO SAQUE
    //---------------------------------------------------------------------------------
    if ((fileclientes=fopen("arqusu.dat","r+b")==NULL)
    {
        if ((fileclientes=fopen("arqusu.dat","w+b")==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA GRAVAR NO VETOR (DADOS CLIENTES)! !");
            exit(101);
        }

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    do{
        if (fread(&rcliente,sizeof(usuario),1,fileclientes)==1)
        {
            u++;
            vcliente[u] = rcliente;
        }
    }while(!feof(fileclientes));
    //FECHANDO O ARQUIVO
    fclose(fileclientes)
    //---------------------------------------------------------------------------------

    //ABRINDO O ARQUIVO QUE POSSUI AS NOTAS
    //---------------------------------------------------------------------------------
    if ((filecedula=fopen("arqced.dat","r+b")==NULL)
    {
        if ((filecedula=fopen("arqced.dat","w+b")==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA COPIAR NO VETOR (CEDULAS)! !");
            exit(100);
        }
        abastece_caixa(&rnotas);

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    if (fread(&rnotas,sizeof(notas),1,filecedula)!=1)
    {
        printf("ERRO COPIANDO ARQUIVO (CEDULAS)");
        exit(100);
    }

    //FECHANDO O ARQUIVO
    fclose(filecedula)
    //---------------------------------------------------------------------------------

    //ABRINDO O ARQUIVO DOS DADDOS DO SAQUE
    //---------------------------------------------------------------------------------
    if ((filesaque=fopen("arqsaq.dat","r+b")==NULL)
    {
        if ((filesaque=fopen("arqsaq.dat","w+b")==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA GRAVAR NO VETOR (DADOS DOS SAQUES)! !");
            exit(102);
        }

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    do{
        if (fread(&rdados,sizeof(dados),1,filesaque)==1)
        {
            q++;
            vdados[q] = rdados;
        }
    }while(!feof(filesaque));
    //FECHANDO O ARQUIVO
    fclose(filesaque)
    //---------------------------------------------------------------------------------

    system("color f9");//muda a cor de fundo da tela
    menu = '0'; // incializando o valor da variavel para fazer o looop;
    while (menu != '4') { // enquanto nao for digitado 4 para terminar o processo, o menu fica ate ser digitado 4(ondi��o de sa�da)

        //system("cls");
        printf("\n\n\t----------SISTEMA BANCARIO-------\n");
        printf("\t- 1...CLIENTE                   -\n");
        printf("\t- 2...SAQUE                     -\n");
        printf("\t- 3...RELATORIO                   -\n");
        printf("\t- 4...FINALIZAR                 -\n");
        printf("\t---------------------------------\n\n");
        printf("\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%s", &menu); // lendo a opcao do  menu que o usuario deseja
        system("cls");

        if (menu == '1'){
            system("cls");
            f_cliente(cad,&k);
        }

        if (menu == '2'){ // caso va para o saque

            system("cls"); // comando apaga tela
                f_saque(vdados,q,&rnotas);
        }

        if (menu == '3'){
            menu_relatorio(vdados,q);
        }

        if (menu == '4'){
            system("cls");
            finaliza();
        }

    }

    //RECRIA O ARQUIVO DE DADOS DOS CLIENTES
    //--------------------------------------------------------------------------
    if ((fileclientes=fopen("arqusu.dat","w+b")==NULL)
    {
        printf("\n\tERRO ABRINDO PARA GRAVACAO (DADOS DOS CLIENTES)");
        exit(101);
    }
    //GRAVA OS DADOS ATUALIZADOS DO VETOR NO ARQUIVO
    //for (i=0;i<u;i++)
    //{
        //rcliente = vcliente[i];
    if ((fwrite(&vcliente,sizeof(usuario),u,fileclientes)) != u)
    {
        printf("ERRO GRAVANDO (DADOS DOS CLIENTES)");
        exit(101)
    }
    //}
    fclose(fileclientes)
    //--------------------------------------------------------------------------

    //RECRIA O ARQUIVO DE DADOS DO SAQUE
    //--------------------------------------------------------------------------
    if ((filesaque=fopen("arqsaq.dat","w+b")==NULL)
    {
        printf("\n\tERRO ABRINDO PARA GRAVACAO (DADOS DOS SAQUES)");
        exit(102);
    }
    //GRAVA OS DADOS ATUALIZADOS DO VETOR NO ARQUIVO
    //for (i=0;i<q;i++)
    //{
        //rdados = vdados[i];
    if ((fwrite(&vdados,sizeof(dados),q,filesaque)) != q)
    {
        printf("ERRO GRAVANDO (DADOS DOS SAQUES)");
        exit(102)
    }
    //}
    fclose(filesaque)
    //--------------------------------------------------------------------------

    //RECRIA O ARQUIVO DE CEDULAS
    //--------------------------------------------------------------------------
    if ((filecedula=fopen("arqced.dat","w+b")==NULL)
    {
        printf("\n\tERRO ABRINDO PARA GRAVACAO (CEDULAS)");
        exit(100);
    }
    //GRAVA OS DADOS ATUALIZADOS DO VETOR NO ARQUIVO
    if ((fwrite(&rnotas,sizeof(notas),1,filecedula)) != 1)
    {
        printf("ERRO GRAVANDO (CEDULAS)");
        exit(100);
    }

    fclose(filecedula)
    //--------------------------------------------------------------------------

    return 0;
}
