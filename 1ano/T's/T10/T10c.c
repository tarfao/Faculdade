/*
O sistema deve manter no máximo 1000 clientes cadastrados. Ao acionar a opção 'incluir'
 do menu cliente o sistema deve gerar automaticamente um cpf válido e um número de conta
corrente nos formatos '999.999.999-99' e '999.999-x', respectivamente, e fazer a inclusão
do novo cliente no sistema. Um novo cliente só pode ser incluído se não existir um cpf ou
número de conta corrente já cadastrados. Utilize as rotinas ' void gera_cpf_valido(char cpf[])'
e ' void geraContaCorrente(char c[])' para a geração automática do cpf e conta corrente.  A
opção 'mostrar' do menu cliente deve apresentar os dados dos clientes cadastrados no sistema.
A opção 'alterar' do menu cliente permite fazer uma alteração no cpf ou número da conta corrente.
A alteração somente será permitida se não existir nenhum saque realizado por aquele cliente.
O sistema deverá preservar os formatos '999.999.999-99' (do cpf) e '999.999-x' (da conta corrente).
A opção 'excluir' do menu cliente permite apagar um cliente do cadastro caso não há nenhum saque
realizado deste cliente. O dado de consulta para a alteração e exclusão é o número da conta corrente
(formato '999.999-x').  Para sacar dinheiro um cliente deve fornecer seu número de conta corrente
(formato '999.999-x') e caso ela exista no sistema o sistema liberará a menor quantidade de cédulas
para o valor solicitado e imprimirá o valor do saque por extenso. O caixa eletrônico deve estar
abastecido automaticamente antes do primeiro saque e os valores máximos de cada cédula são: 100
(cédulas) de 200; 200 de 100;  400 de 50; 500 de 40; 600 de 20; 700 de 10; 800 de 5; 1.500 de 2 e 2.000 de 1 real.


RGM     INTEGRANTES

35237   RAFAELA DONASSOLO ALVES

35043   RONALDO TAFAREL PEREIRA DE SOUZA

35048   ZENALVO BASTOS PINTO JÚNIOR

DATA: 21/10/2016
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
    char clientes[15];//matriz que armazenara os cpf's de todos os clientes **definido o maximo como sendo 50 clientes
    char conta_corrente[10];//vetor que armazena dados da conta corrente **maximo 50
    int situacao; //ativo = 1, inativo =2;
    int saque; // 1 - nn fez saque, 2 - fez saque.

}usuario;


typedef struct saq_banco {

    int saques_clientes[100];//obtem cada saque que um cliente faz
    char conta_saque[10];
    char cpf_saque[15];// obtem o cpf de cada cliente que faz o saque(SUBMETIDO A SER RETIRADO)
    //char obtem_posicao_cliente_cada_saque[1000];
    //int verifica_sf_saque=1;//verifica se um usuario já fez saque para poder ser alterado (1 n fez, 2 fez)
    //int totsak=0;//totsak eh o total jah sacado depois de varias transações
    //int cont=0; // auxlia cada posicao do vetor verifica_sf_saque, que so tem 50 posicoes, que é o numero de cadastros possiveis
            // ou seja ira obter somente 1 vez a posicao de um usuario que fez saque.
    int saque_valido;//auxilia o vetor de saques em cada saque valido para ser armazenado

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
            if ((DM != 1) && (DM!=0) && (UNM != 0)) // imprime o "e" para separação de dezena e unidade, para ex: noventa E três
                printf(" E");
            }
        }
    // para aparecer vinte e três a dezena de milhar tem que ser diferente de 1,
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

//---------------------------------------------------------------------------------------
//PROCEDIMENTO
//OBJETIVO: APAGAR UM CLIENTE DA LISTA
//PARAMETRO: d QUE O CONJUNTO DE CADASTRO, E pos QUE É A QUANTIDADE DE USUARIO
//----------------------------------------------------------------------------------------
void apaga_cliente (usuario d[], int pos)
{
    int posicao;//OBTEM A POSICAO DO CLIENTE
    int i,j;//AUXILIARES
    char c[10];//conta do usuario

    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/EXCLUIR-----\n");
    printf("\n\tTITULAR\t\tC/C\n");

    for (i=0;i<pos;i++)//imprime lista de clientes
    {
        if(d[i].situacao == 1){
            printf("\t%s",d[i].clientes);
            printf("\t");//espaçamento
            printf("%s",d[i].conta_corrente);
            printf("\n");//pula uma linha após cada impressão do cliente e sua respectiva conta
        }
    }
    printf("\n\tINFORME A CONTA DO USUARIO QUE DESEJA EXCLUIR?\n\t(0)VOLTAR\n\t");
    gets(c);
    if (verifica_formact_conta(c)>0)
    {
        posicao = verifica_conta(c,d,pos); //altera a posicao que aparece para o usuario para a posicao real que o cadastro ocoupa.
        if (posicao>-1){
            if (d[posicao].saque==1){
                d[posicao].situacao = 2;
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
        system("cls");
        printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/APAGA CLIENTE-----\n");
        printf("\n\t!!CONTA NAO ESTA NO FORMATO !!\n\n\t");
        system("pause");
        system("cls");//apaga tela
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: TESTA_CONTA
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE A CONTA INFORMADA JÁ EXISTE
//PARAMETRO: A CONTA CORRENTE DIGITADA PELO USUARIO,
            // O CONJUNTO DE CADASTROS E A SUA QUANTIDADE.
//RETORNO: 0 SE NAO EXISTIR, E RETORNA 1 CASA JÁ EXISTA
//-------------------------------------------------------------------------------------------------------------------------------
int testa_conta(char conta[], usuario c[], int q){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i;//contadores
    //---------------------------------------------

    for (i=0;i<q;i++)//laço verifica se a conta corrente informada ja existe para algum cadastro
    {
        if (c[i].situacao == 1){
            if(strcmp(c[i].conta_corrente,conta)==0)
            {
                return 1;
            }
        }

    }

    return 0;

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: QTD_CEDULAS
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA A QUANTIDADE DISPONÍVEL PARA SAQUE DE CADA CÉDULA
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
    printf("\n---------------------------------------------------------------------------------\n");


}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: VALOR_SALDO
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA O SALDO DISPONÍVEL DO CAIXA
//-------------------------------------------------------------------------------------------------------------------------------
void valor_saldo(notas c){

    int saldo;

    saldo = calcula_saldo(c);

    printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/SALDO EXISTENTE-----------\n");
    printf("----------------------------------------------------------------------------\n");
    printf("RELATORIO 'VALOR DO SALDO EXISTENTE'\n");
    printf("----------------------------------------------------------------------------\n");
    printf("R$ %d,00 (",saldo);//variável acumulativa para o saldo disponível
    extenso(saldo);
    printf(" REAIS)\n");
    printf("----------------------------------------------------------------------------\n");
}

//------------------------------------------------------------------------------------------------
//OBJETIVO: CALCULAR O SALDO
//PARAMETRO: AS NOTAS
//RETORNO: O VALOR DO SALDO
//------------------------------------------------------------------------------------------------
int calcula_saldo (notas c)
{
    int saldo=0;
    saldo = saldo + c.vernot100*100;
    saldo = saldo + c.vernot10*10;
    saldo = saldo + c.vernot1;
    saldo = saldo + c.vernot200*200;
    saldo = saldo + c.vernot20*20;
    saldo = saldo + c.vernot2*2;
    saldo = saldo + c.vernot40*40;
    saldo = saldo + c.vernot50*50;
    saldo = saldo + c.vernot5*5;

    return(saldo);
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ABASTECE_CAIXA
//PARAMETRO: c QUE É UM REGISTRO CONTENDO AS NOTAS
//OBJETIVO: ABASTECER O CAIXA ELETRONICO INFORMANDO AS OPÇOES DE ESCOLHA DE NOTAS
//-------------------------------------------------------------------------------------------------------------------------------
void abastece_caixa(notas *c){

    (*c).vernot1 = 2000;
    (*c).vernot2 = 1500;
    (*c).vernot5 = 800;
    (*c).vernot10 = 700;
    (*c).vernot20 = 600;
    (*c).vernot40 = 500;
    (*c).vernot50 = 400;
    (*c).vernot100 = 200;
    (*c).vernot200 = 100;
}


//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: MOSTRA_SAQUES_CLIENTES
//PARAMETROS: c QUE É O CONJUNTO DE SAQUES, E pos QUE É A QUANTIDADE
//OBJETIVO: MOSTRAR O CPF DE CADA SAQUE EFETUADO
//PARAMENTRO: SEM PARAMETRO DE ENTRADA
//-------------------------------------------------------------------------------------------------------------------------------
void mostra_saques_clientes (dados c[], int pos){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i=0,j,x=0;
    int saque;//obtem a quantidade total de saque de cada cliente
    int saque_total=0;
    //------------------------------------

    system("cls");
    printf("\n\n\t----SISTEMA BANCARIO/GERENTE/VALORES SACADOS----\n");
    printf("--------------------------------------------------------------------------\n");
    printf("RELATORIO 'VALORES SACADOS'\n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tCONTA-CORRENTE\t\tCPF\t\t\tSAQUE\n");
    //VERIFICA SE JA FOI FEITO ALGUM SAQUE, QUE SERA CONTADO PELO OU MENOS 1 SE SIM
    if (pos!=0){
        for(i=0;i<pos;i++){
            if (c[i].saque_valido > 0)
            {
                saque = 0;
                printf("\n\t%s\t\t%s",c[i].conta_saque, c[i].cpf_saque);
                for (j=0;j<c[i].saque_valido;j++)
                {
                    if (x==0){
                        x++;
                        printf("\t\t%d",c[i].saques_clientes[j]);
                        saque += c[i].saques_clientes[j];
                    }
                    else
                    {
                        printf("\n\t\t\t\t\t\t\t%d",c[i].saques_clientes[j]);
                        saque += c[i].saques_clientes[j];
                    }

                }
                printf("\n\t\t\t\t\t\t\t\t%d",saque);
                saque_total += saque;
            }
        }
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
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: ATUALIZAR AS NOTAS DO CAIXA E IMPRIMIR O SAQUE
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------------------------------------------------
void liberar_notas(int a200,int a100, int a50, int a40, int a20, int a10, int a5, int a2, int a1, notas *c)//cedulas que vao ser retiradas
{

    //notas de 200
    if (a200>0) {
        printf("\n\t%d NOTA(S) - R$ 200,00",a200); // mostrando as notas que sairam
        (*c).vernot200 = (*c).vernot200 - a200; // diminuindo a quantidade de notas do caixa
    }
    //notas de 100
    if (a100>0) {
        printf("\n\t%d NOTA(S) - R$ 100,00",a100); // mostrando as notas que sairam de 100
        (*c).vernot100 = (*c).vernot100 - a100; // subtraindo o quantidade de notas do caixa
    }
    //notas de 50
    if (a50>0){
        printf("\n\t%d NOTA(S) - R$ 50,00",a50); // mostrando as notas que foram retiradas
        (*c).vernot50 = (*c).vernot50 - a50; // diminuindo as notas de 50 do caixa
    }
    //notas de 40
    if (a40>0){
        printf("\n\t%d NOTA(S) - R$ 40,00",a40); // mostrando as notas que foram retiradas
        (*c).vernot40 = (*c).vernot40 - a40; // diminuindo as notas de 40 do caixa
    }
    //notas de 20
    if (a20>0) {
        printf("\n\t%d NOTA(S) - R$ 20,00",a20); // mostra as notas retiradas
        (*c).vernot20 = (*c).vernot20 - a20; // subtrai-se as notas do caixa com as notas retiradas, para serem retiradas do caixa
    }
    //notas de 10
    if (a10>0) {
        printf("\n\t%d NOTA(S) - R$ 10,00",a10);
        (*c).vernot10 = (*c).vernot10 - a10;
    }
    //notas de 5
    if (a5>0) {
        printf("\n\t%d NOTA(S) - R$ 5,00",a5);
        (*c).vernot5 = (*c).vernot5 - a5;
    }
    //notas de 2
    if (a2>0) {
        printf("\n\t%d NOTA(S) - R$ 2,00",a2);
        (*c).vernot2 = (*c).vernot2 - a2;
    }
    //notas de 1
    if (a1>0) {
        printf("\n\t%d NOTA(S) - R$ 1,00",a1);
        (*c).vernot1 = (*c).vernot1 - a1;
    }
    printf("\n\t");

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VER_CAIXA_SAQUE_0
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE HÁ NOTAS SUFICIENTES PARA EFETUAR O SAQUE
//PARAMETRO VALOR: DE ENTRADA QUE É O SAQUE, E O REGISTRO DE NOTAS
//PARAMETRO REFERENCIA: AS NOTAS QUE SAIRÃO, a200, a100...
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
//FUNÇÃO: VERIFICA_CONTA
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR A POSIÇÃO DA CONTA DENTRO DO VETOR CASO SEJA EXISTENTE
//PARAMETRO: A CONTA DIGITADA , O VETOR CONTENDO TODAS AS CONTAS E A QUANTIDADE;
//RETORNO: RETORNA -1 SE NÃO HOUVER CONTA, E RETORNA A POSICAO DA CONTA SE HOUVER CONTA CORRENTE IGUAL
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_conta(char conta[], usuario d[], int pos)
{

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int j=0; //j varia a posicão da conta

    //--------------------------------------------------------

    for(j=0;j<pos;j++){

        if (d[j].situacao == 1){
            if (strcmp(conta,d[j].conta_corrente)==0)
            {
                return (j);
            }
        }
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: TESTA_CPF
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE HA UM CPF JA CADASTRADO
//PARAMETRO: O CPF DIGITADO PELO USUARIO, O CONJUNTO DE CADASTROS E A QUANTIDADE
//RETORNO: 0 SE NAO HOUVER CADASTRO, E RETORNA 1 CASA HAJA O CADASTRO
//-------------------------------------------------------------------------------------------------------------------------------
int testa_cpf(char cpf[], usuario c[], int q){

    //DECLARAÇÃO DE VARIAVEIS LOCAIS
    int i,j;//contadores
    int qtd;//conta os digitos iguais

    for (i=0;i<q;i++)//laço verifica se o cpf informado já possui cadastro
    {
        if (c[i].situacao == 1){
            if (strcmp(cpf,c[i].clientes) == 0)
            {
                return 1;
            }
        }
    }
    return 0;

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VERIFICA_CLIENTE_E_SAQUE
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE O CLIENTE JA FEZ ALGUM SAQUE
//PARAMETRO: cc QUE É A CONTA, O VETOR CONTENDO OS CADASTROS,
//          E q QUANTIDADE DE CADASTROS.
//RETORNO:  1 SE O CLIENTE EFETUOU ALGUM SAQUE CASO CONTRARIO DEVOLVE 0
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_cliente_e_saque(char cc[], usuario c[], int q){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i=0;

    do{
        if (c[i].situacao == 1){
            if (strcmp(cc,c[i].conta_corrente) == 0)
            {
                if (c[i].saque == 2){
                    return 1;
                }
            }
        }
        i++;
    }while (i!=q);

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ALTERA_CLIENTE
//PARAMETRO: d QUE É O CONJUNTO DE USUARIOS CADASTRADOS, q QUE É A QUANTIDADE
//OBJETIVO: ALTERAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void altera_cliente(usuario d[], int q)
{

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i,j;
    int x;//recebe o valor retornado pela função testa_cpf após verificação se ha um cpf ja cadastrado
    int op2;//opções durante a execução da função
    char ncpf[15];//vetor para receber o cpf no formato 999.999.999-99
    char cpf[15];//recebe o cpf caso queira muda-lo
    char c[10];//faz a leitura da conta que deseja alterar
    char conta[10];//vetores para conta corrente em uma array de caracteres
    int pos; //recebe a posicao do cliente
    int a;// faz a verificacao do formato do cpf


    //---------------------------------------------

    printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
    printf("\n.\tTITULAR\t\tCONTA/CORRENTE\n");

    for (i=0;i<q;i++)//imprime lista de clientes
    {
        if (d[i].situacao == 1){
            printf("\t%s\t%s\n",d[i].clientes,d[i].conta_corrente);//imprime o código do cliente na lista
        }
    }
    printf("\n\tINFORME A CONTA DO CLIENTE QUE DESEJA ALTERAR..FORMATO (999.999-X)\n\t");
    gets(c);//faz a leitura do codigo do cliente para alterações

    if (verifica_formact_conta(c)>0){
        pos = verifica_conta(c,d,q);//obtendo a posicao do cliente
        if (pos>-1){
            if (d[pos].saque == 1){
                while ((op2>2) || (op2<1)){
                    system("cls");
                    printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
                    printf("\n\tTITULAR\t\tCONTA/CORRENTE\n");
                    printf("\t%s",d[pos].clientes);
                    printf("\t");
                    printf("%s",d[pos].conta_corrente);
                    printf("\n");
                    printf("\n\tALTERAR:\n\t1.CPF\n\t2.C/C\n\t");
                    scanf("%d",&op2);
                    if ((op2>2) || (op2<1)){
                        system("cls"); // apaga tela
                        printf("\n\tOPCAO INVALIDA..\n\t");
                    }
                    else{
                        switch(op2){

                            case 1:
                                printf("\n\tDIGITE O NOVO CPF: (FORMATO: 999.999.999-99)\n\t");
                                gets(cpf);
                                a = verifica_formact_cpf(cpf);
                                if(a>0){
                                    tira_cpf_formato(cpf);//tira o formato do cpf para poder fazer a verificacao de validade
                                    if (verifica_cpf_valido(cpf)==1){
                                        insere_pontuacao_cpf(cpf,ncpf);
                                        x = testa_cpf(ncpf,d,q);
                                        if (x == 0){
                                            strcpy(d[pos].clientes,ncpf); //clientes[pos][j] = ncpf[j];
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
                                    conta[8] = toupper(conta[8]);
                                    if (verifica_conta(conta,d,q) > -1)
                                    {
                                        system("cls");
                                        printf("\n\t !! CONTA JA POSSUI CADASTRO !!\n\t");
                                        system("pause");
                                        system("cls");
                                    }
                                    else{
                                        strcpy(d[pos].conta_corrente,conta);//conta_corrente[pos][j] = conta[j];
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

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i;
    int v,qtd=0;
    int valido=1;//será o retorno da função
    int cpfi[12];
    //-----------------------------

    for (i=0;i<12;i++)
    {
        cpfi[i] = cpf[i]-48;
    }
    v = cpfi[0];//v recebe primeiro digito do cpf para fazer verificação

    for (i=1;i<11;i++)//o laço ira contar a quantidade de digitos iguais no cpf
    {
        if (cpfi[i] == v)
            qtd = qtd+1;
    }

    if (qtd == 10){//caso todos os digitos sejam o mesmo o cpf é inválido
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
//PARAMETRO: d QUE É O CONJUNTO DE CADASTRO E POR REFERENCIA TEMOS pos QUE
            // REPRESENTA A QUANTIDADE DE CADASTROS
//OBJETIVO: EFETUAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void cadastro_cliente(usuario d[], int *pos){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS------------------------------
    char ncpf[15], cpf[15];//vetor armazena CPF
    char conta[10];//vetor armazena dados da conta corrente
    int y;  //y verifica se ha um cpf ja cadastrado e uma conta em outro momento


    //------------------------------------------------------------
    do{
        gera_cpf_valido(cpf);
        y = testa_cpf(cpf,d,*pos);
    }while(y!=0);
    insere_pontuacao_cpf(cpf,ncpf);
    strcpy(d[*pos].clientes,ncpf);
    Sleep(250);
    do{
        geraContaCorrente(conta);
        y = testa_conta(conta,d,*pos);
    }while(y==1);
    strcpy(d[*pos].conta_corrente,conta);
    printf("\n\t- CLIENTE INCLUIDO COM SUCESSO\n");
    printf("\n\tCPF: %s",d[*pos].clientes);
    printf("\n\tCONTA: %s",d[*pos].conta_corrente);
    d[*pos].saque = 1;
    d[*pos].situacao = 1;
    *pos = *pos + 1;

}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um cpf valido no formato 999.999.999-99
//parametros: cpf:o cpf onde sera armazenado o cpf valido
//---------------------------------------------------------------------------------
void gera_cpf_valido(char cpf[]) {

    int j;
    int y;//verifica se cpf ja existe
    int ver;

    srand(time(NULL));
    for (j=0;j<9;j++){
        cpf[j]=rand()%9+48;
    }
    cpf[9] = obtem_primeiro_digito_verificador(cpf)+48;
    cpf[10] = obtem_segundo_digito_verificador(cpf)+48;
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
//parametro: cpf, que é o cpf do usuario
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
void geraContaCorrente(char c[], usuario u[], int q) {

    int i;
    int y;

    //Sleep(250);
    //srand(time(NULL));
    for (i=0;i<6;i++){
        c[i]=rand()%9+48;
    }
    c[6] = geraAlfabeto();
    colocando_conta_formato(c);



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
//retorno: a que será 1 para verdadeiro e menor que 1 falso
//-----------------------------------------------------------------------
int verifica_formact_cpf(char cpf[])
{
    int a=-2; //incializo com -2 para atualizar até no maximo 1
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
    int a=-2;//incializo com -2 para ir atualizando até no maximo 1
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
//PARAMETRO: d QUE É O CONJUNTO DE CADASTROS E POS QUE REPRESENTA A QUANTIDADE
//OBEJTIVO: IMPRIMIR O CADASTRO DE CADA CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void imprime_clientes(usuario d[], int pos){

    //DECLARAÇÃO DE VARIAVEIS LOCAIS
    int i,j;//contadores
    //--------------------------------

    printf("\n\n\t---SISTEMA BANCARIO/CLIENTE/LISTA DE CLIENTES---\n");//guia usuário
    printf("\n\tTITULAR\t\tCONTA/CORRENTE\n");
    for (i=0;i<pos;i++)
    {
        if (d[i].situacao == 1){
            printf("\t%s\t%s\n",d[i].clientes,d[i].conta_corrente);
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_CLIENTE
//PARAMETRO: d CONJUNTO DE CADASTROS
        // REFERENCIA *pos QUANTIDADE DE CLIENTES CADASTRADOS
//OBJETIVO: OFERECER AS OPÇÕES DO MENU DA OPÇÃO 'CLIENTE'
//-------------------------------------------------------------------------------------------------------------------------------
void f_cliente(usuario d[], int *pos){
    //VARIAVEIS LOCAIS MENU_CLIENTE
    int menu_cli;//leitura da opção digitada no menu

    menu_cli=0;//inicialização da variável menu_cli

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
            cadastro_cliente(d,&*pos);//chamada da função de cadastro do cliente
        }

        if (menu_cli == 2){
            system("cls");
            imprime_clientes(d,*pos);//chamada do procedimento que imprime a lista de clientes
        }

        if (menu_cli == 3){
            system("cls");
            altera_cliente(d,*pos);
        }

        if (menu_cli == 4){
            system("cls");
            apaga_cliente(d,*pos);
        }
        if (menu_cli==5)
        {
            system("cls");
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_SAQUE
//PARAMETRO: c QUE É O CONJUNTO DE REGISTRO DOS SAQUES, c QUE É O CONJUNTO DE USUARIOS CADASTRADOS E k QUE É A QUANTIDADE
            //POR REFERENCIA TEMOS q QUE PODE SER ALTERADA NA QUANTIA DE PESSOAS QUE FEZ SAQUE, E N QUE PODE RETIRAR CÉDULAS
//OBJETIVO: OFERECER AO USUÁRIO A OPÇÃO DE SAQUE
//-------------------------------------------------------------------------------------------------------------------------------
void f_saque(dados s[], int *q, notas *n, usuario c[], int k){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int a200=0, a100=0, a50=0, a40=0, a20=0, a10=0, a5=0, a2=0, a1=0;//cedulas que vao ser retiradas
    int saque;//faz leitura do saque
    int posi;//recebe a posicao que o usuario esta na matriz
    char cc[10];//conta do usuario
    int i,j;
    int ver;//verifica se a conta esta no formato 999.999-x
    int lugar;//recebe o local que o usuario esta no vetor de dados de saque c
    int saldocaixa;//RECEBE O SALDO DO CAIXA
    //---------------------------------------------------------

    saldocaixa = calcula_saldo(*n);
    system("cls");//apaga tela
    printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");//guia usuário
    printf("\n\tSALDO: %d\n",saldocaixa);
    printf("\n\tDIGITE OS DADOS DA CONTA CORRENTE: FORMATO(999.999-X)\n\t");
    gets(cc);
    ver = verifica_formact_conta(cc);
    if (ver>0){
        posi = verifica_conta(cc,c,k);
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
                printf("\n\t-NOTAS DE 1,00   = %d",(*n).vernot1);
                printf("\n\t-NOTAS DE 2,00   = %d",(*n).vernot2);
                printf("\n\t-NOTAS DE 5,00   = %d",(*n).vernot5);
                printf("\n\t-NOTAS DE 10,00  = %d",(*n).vernot10);
                printf("\n\t-NOTAS DE 20,00  = %d",(*n).vernot20);
                printf("\n\t-NOTAS DE 40,00  = %d",(*n).vernot40);
                printf("\n\t-NOTAS DE 50,00 = %d",(*n).vernot50);
                printf("\n\t-NOTAS DE 100,00 = %d",(*n).vernot100);
                printf("\n\t-NOTAS DE 200,00 = %d\n\n\t",(*n).vernot200);
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
                if (Ver_caixa_saque_0(saque,&a200,&a100,&a50,&a40,&a20,&a10,&a5,&a2,&a1,*n)!=0)
                {
                    system("cls"); // apaga tela
                    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                    printf("\n\t !! CEDULAS NECESSARIAS PARA SAQUE INSUFICIENTES !!\n\t");
                }
                else{
                    if (saque != 0){
                        Sleep (1000);
                        printf ("\r \t\t\t\t \n\n\n");
                        system("cls");
                        printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                        printf("\n\tSAQUE EFETUADO COM SUCESSO..");
                        liberar_notas(a200,a100,a50,a40,a20,a10,a5,a2,a1,&*n);
                        extenso(saque);
                        printf(" REAIS");
                        if (*q==0)
                        {
                            strcpy(s[*q].conta_saque,cc);
                            strcpy(s[*q].cpf_saque,c[posi].clientes);
                            s[*q].saques_clientes[s[*q].saque_valido] = saque;
                            s[*q].saque_valido = 1;
                            c[posi].saque = 2;
                            *q = *q + 1;
                        }
                        else
                        {
                            lugar = procura_posicao_novetor_saq(cc,s,*q);//obtem a posicao do o usuario que deseja fazer um saque
                                                                        //dentro do vetor de dados do saque
                            if (lugar>-1)
                            {
                                s[lugar].saques_clientes[s[lugar].saque_valido] = saque;
                                s[lugar].saque_valido = s[lugar].saque_valido + 1;
                            }
                            else
                            {
                                c[posi].saque = 2;
                                strcpy(s[*q].conta_saque,cc);
                                strcpy(s[*q].cpf_saque,c[posi].clientes);
                                s[*q].saques_clientes[s[*q].saque_valido] = saque;
                                s[*q].saque_valido=1;
                                *q = *q + 1;
                            }
                        }
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
//PARAMETRO: conta, QUE É A CONTA QUE VEREMOS SE ESTA NO CONJUNTO, c É O CONJUNTO DE DADOS DE SAQUE
//          E q QUE É A QUANTIDADE DE PESSOAS QUE JÁ FEZ SAQUE.
//RETORNO: ver, QUE VAI SER -1 SE NAO ENCONTRAR NO VETOR, OU ALGUM VALOR REPRESENTANDO A POSICAO NO VETOR
//---------------------------------------------------------------------------------------------------------
int procura_posicao_novetor_saq (char conta[], dados c[], int q)
{
    int i;

    for (i=0;i<q;i++)
    {
        if (strcmp(conta,c[i].conta_saque)==0)
        {
            return (i);
        }
    }
    return -1;
}
//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: menu_relatorio
//PARAMETRO: c QUE É O CONJUNTO DE SAQUES, p É A QUANTIDADE DE CLIENTES QUE FEZ SAQUE
//          E n É O REGISTRO CONTENDO AS NOTAS
//OBJETIVO: OFERECER AO USUÁRIO A OPÇÃO DO MENU GERENTE
//-------------------------------------------------------------------------------------------------------------------------------
void menu_relatorio(dados c[], int p, notas n){

    //DECLARAÇAO DE VARIAVEIS LOCAIS
    int menu2;//menu gerente
    //------------------------------------
    menu2 = 0;//inicialização da variável
    system("cls");
    while (menu2 != 4){
                //menu de opções
        system("cls");
        printf("\n\n\t----------SISTEMA BANCARIO/MENU RELATORIO-----------\n");
        printf("\t- 1...VALORES SACADOS                       -\n");
        printf("\t- 2...VALOR SALDO EXISTENTE                 -\n");
        printf("\t- 3...QUANTIDADE DE CEDULAS EXISTENTES      -\n");
        printf("\t- 4...MENU PRINCIPAL                        -\n");
        printf("\t---------------------------------------------");
        printf("\n\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%d", &menu2);//leitura da opção digitada pelo usuário
        if (menu2==1){
            mostra_saques_clientes(c,p);
        }
        if (menu2 == 2){//opção2 valor saldo existente
            system("cls"); // comando apaga tela
            valor_saldo(n);//chamada do procedimento valor_saldo
            system("pause");
        }
        if (menu2 == 3){//opção3 quantidade de células
                system("cls");//comando apaga tela
                qtd_cedulas(n);//chamada do procedimento
                printf("\n\n\t");
                system("pause");
        }

    }
    system("cls"); // comando apaga tela
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: FINALIZA
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
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

    //DECLARAÇÃO DE VARIÁVEIS
    char menu;//menu principal
    //saques dos clientes
    //----------------------------------------------------------------------
    FILE *filesaque; //arquivo que tem os dados do saque
    dados vdados[100];//vetor que vai obter tudo do arquivo
    dados rdados;//registro do mesmo tipo do vetor para fazer a copia
    int q=0;//representa quantos registros foram copiados
    //-----------------------------------------------------------------------
    //cédulas do caixa
    //-----------------------------------------------------------------------
    FILE *filecedula;
    notas rnotas;
    int control=0;
    //-----------------------------------------------------------------------
    FILE *filecadastro;
    usuario vusuario[100];
    usuario rusuario;
    int c=0;// quantidade de usuarios
    //------------------------------------------------------------------------
    int i;
    //-------------------------------

        //ABRINDO O ARQUIVO DOS CADASTROS
    if ((filecadastro=fopen("cadastro.dat","r+b"))==NULL)
    {
        if ((filecadastro=fopen("cadastro.dat","w+b"))==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA GRAVAR NO VETOR (CADASTRO)! !");
            exit(105);
        }

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    fseek(filecadastro,0,SEEK_SET);
    do{
        if ((fread(&rusuario,sizeof(usuario),1,filecadastro))==1)
        {
            vusuario[c] = rusuario;
            c++;
        }
    }while(!feof(filecadastro));
    //FECHANDO O ARQUIVO
    fclose(filecadastro);
    //--------------------------------------------------------------------------------------------------

    //ABRINDO O ARQUIVO DOS DADDOS DO SAQUE
    if ((filesaque=fopen("arqsaq.dat","r+b"))==NULL)
    {
        if ((filesaque=fopen("arqsaq.dat","w+b"))==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA GRAVAR NO VETOR (DADOS DOS SAQUES)! !");
            exit(102);
        }

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    do{
        if ((fread(&rdados,sizeof(dados),1,filesaque))==1)
        {
            vdados[q] = rdados;
            q++;
        }
    }while(!feof(filesaque));
    //FECHANDO O ARQUIVO
    fclose(filesaque);
    //--------------------------------------------------------------------------------------------------

    //ABRINDO O ARQUIVO QUE POSSUI AS NOTAS
    if ((filecedula=fopen("arqced.dat","r+b"))==NULL)
    {
        abastece_caixa(&rnotas);
        control++;
        if ((filecedula=fopen("arqced.dat","w+b"))==NULL)
        {
            printf("\n\tERRO ABRINDO O ARQUIVO PARA COPIAR NO VETOR (CEDULAS)! !");
            exit(100);
        }

    }

    //COPIANDO O ARQUIVO PARA UM VETOR
    if (control == 0){

        if ((fread(&rnotas,sizeof(notas),1,filecedula)) != 1)
        {
            printf("ERRO COPIANDO ARQUIVO (CEDULAS)");
            exit(100);
        }
    }

    //FECHANDO O ARQUIVO
    fclose(filecedula);
    //------------------------------------------------------------------------------------------------
    system("color f9");//muda a cor de fundo da tela
    menu = '0'; // incializando o valor da variavel para fazer o looop;
    while (menu != '4') { // enquanto nao for digitado 4 para terminar o processo, o menu fica ate ser digitado 4(ondição de saída)

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
            f_cliente(vusuario,&c);
        }

        if (menu == '2'){ // caso va para o saque

            system("cls"); // comando apaga tela
            f_saque(vdados,&q,&rnotas,vusuario,c);
        }

        if (menu == '3'){
            menu_relatorio(vdados,q,rnotas);
        }

        if (menu == '4'){
            system("cls");
            finaliza();
        }

    }

    //RECRIA O ARQUIVO DE CADASTROS
    if ((filecadastro=fopen("cadastro.dat","w+b"))==NULL)
    {
        printf("\n\tERRO ABRINDO PARA GRAVACAO (CADASTRO)");
        exit(103);
    }
    //GRAVA OS DADOS ATUALIZADOS DO VETOR NO ARQUIVO
    for (i=0; i < c; i++){
        rusuario = vusuario[i];
        if ((fwrite(&rusuario,sizeof(usuario),1,filecadastro)) != 1)
        {
            printf("ERRO GRAVANDO (CADASTRO)");
            exit(103);
        }
    }
    fclose(filecadastro);

     //RECRIA O ARQUIVO DE DADOS DO SAQUE
    if ((filesaque=fopen("arqsaq.dat","w+b"))==NULL)
    {
        printf("\n\tERRO ABRINDO PARA GRAVACAO (DADOS DOS SAQUES)");
        exit(102);
    }
    //GRAVA OS DADOS ATUALIZADOS DO VETOR NO ARQUIVO
    for (i=0;i<q;i++)
    {
        rdados = vdados[i];
        if ((fwrite(&rdados,sizeof(dados),1,filesaque)) != 1)
        {
            printf("ERRO GRAVANDO (DADOS DOS SAQUES)");
            exit(102);
        }
    }
    fclose(filesaque);;

    //RECRIA O ARQUIVO DE CEDULAS
    if ((filecedula=fopen("arqced.dat","w+b"))==NULL)
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
    fclose(filecedula);

    return 0;
}
