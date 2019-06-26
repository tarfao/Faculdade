/*Desenvolver um sistema para saques de um caixa eletrônico que deverá liberar o menor
número de cédulas para um valor solicitado pelo cliente. Esse cliente deverá ter seu
número de conta corrente e CPF (válido) em um cadastro. As cédulas armazenadas no
caixa são de 200, 100, 50, 40, 20, 10, 5, 2 e 1 real.
O caixa eletrônico é abastecido com as quantidade máximas de cédulas sempre que o gerente
acionar a funcionalidade “abastecer”. Essas quantidades máximas de cédulas são: 100
(cédulas) de 200; 200 de 100; 400 de 50; 500 de 40; 600 de 20; 700 de 10; 800 de 5;
1.500 de 2 e 2.000 de 1 real.
Para sacar dinheiro o cliente deve fornecer sua conta corrente e caso ela exista no cadastro o
sistema liberará a quantidade de cada cédula e imprimirá o valor do saque por extenso.
Para o gerente o sistema deve informar cada valor sacado e o CPF de quem sacou, o valor
total sacado, o valor do saldo existente e a quantidade de cada cédula armazenada no
caixa eletrônico, quando acionado pelo gerente. O valor total sacado, o valor do saldo
existente e a quantidade de cédulas existentes devem ser informadas, além de seu valor
numérico, o valor por extenso.




RGM     INTEGRANTES

35029   IURY RODRIGUES PRATES

35043   RONALDO TAFAREL PEREIRA DE SOUZA

35048   ZENALVO BASTOS PINTO JÚNIOR

DATA: 29/07/2016
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

//DECLARAÇÃO DE VARIÁVEIS GLOBAIS------------------------------------------------------------------------------------------------
char clientes[50][11];//matriz que armazenara os cpf's de todos os clientes **definido o maximo como sendo 50 clientes
int conta_corrente[50];//vetor que armazena dados da conta corrente **maximo 50
int saques_clientes[100];//obtem cada saque que um cliente faz
char cpf_saque[100][12];// obtem o cpf de cada cliente que faz o saque
int verifica_sf_saque[50];//verifica se um usuario já fez saque para poder ser alterado
int qtd_clientes=0;//conta a quantidade de clientes já cadastrados
int saldocaixa=0;//obtem o total de dinheiro que ha no caixa
int m=0;//verifica se ja foi feito algum saque
int l=0;//verifica se caixa já foi abastecido
int a200, a100, a50, a40, a20, a10, a5, a2, a1;//cedulas que vao ser retiradas
int totsak=0;//totsak eh o total jah sacado depois de varias transações
int vernot1=0, vernot2=0, vernot5=0, vernot10=0, vernot20=0, vernot50=0, vernot40=0, vernot100=0, vernot200=0;
int cont=0; //auxlia cada posicao do vetor verifica_sf_saque, que so tem 50 posicoes, que é o numero de cadastros possiveis
//ou seja ira obter somente 1 vez a posicao de um usuario que fez saque.
int saque_valido=0;//auxilia o vetor de saques em cada saque valido para ser armazenado
//-------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//PROCEDIMENTO
//OBJETIVO: MOSTRAR POR EXTENSO ALGUM VALOR
//PARAMETRO: DE ENTRADA QUE SERA O VALOR TOTAL DO CAIXA, OU O VALOR DO SAQUE
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//PROCEDIMENTO
//OBJETIVO: APAGAR UM CLIENTE DA LISTA
//PARAMETRO: DE ENTRADA QUE SERA A POSIÇÃO QUE O USUARIO SE ENCONTRA
//------------------------------------------------------------------------------
void apaga_cliente ()
{
    int posicao;//OBTEM A POSICAO DO CLIENTE
    int i,j;//AUXILIARES

    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/APAGA CLIENTE-----\n");
    printf("\n\tCOD.\tTITULAR\t\tC/C\n");

    for (i=0;i<qtd_clientes;i++)//imprime lista de clientes
    {
        printf("\t");//espaçamento
        printf("%d\t",i+1);//imprime o código do cliente na lista

        for (j=0;j<11;j++)//laço imprime cpf
        {
            printf("%c",clientes[i][j]);
        }
        printf("\t");//espaçamento
        printf("%d",conta_corrente[i]);
        printf("\n");//pula uma linha após cada impressão do cliente e sua respectiva conta
    }
    printf("\n\tQUAL CLIENTE DESEJA APAGAR?\n\t(0)VOLTAR\n\t");
    scanf("%d",&posicao);
    if (posicao>0 && posicao<qtd_clientes)
    {
        posicao--; //altera a posicao que aparece para o usuario para a posicao real que o cadastro ocoupa.
        if (verifica_cliente_e_saque(posicao)==0){
            //altera a posicao do ultimo cadastro de cpf para a posicao do cliente que sera apagado
            for (i=0;i<11;i++)
            {
                clientes[posicao][i] = clientes[qtd_clientes-1][i];
            }
            //altera a posicao do ultimo cadastro de conta para a posicao do cliente que sera apagado
            conta_corrente[posicao] = conta_corrente[qtd_clientes-1];
            //retira a sua posicao do vetor que verifica quem ja fez saque pois a nova posicao sera ocupada pelo ultimo cliente
            for (i=0;i<cont;i++)
            {
                if (verifica_sf_saque[i]==posicao)
                {
                    verifica_sf_saque[i]=verifica_sf_saque[cont];
                    cont--;//RETIRA UMA POSICAO DA VARIAVEL AUXILIAR DO VETOR QUE VERIFICA QUEM JA FEZ SAQUE
                }
            }
            qtd_clientes--;//"retira uma posicao" da quantidade de clientes, que sera reescrevida quando fizer outro cadastro.
            system("cls");
            printf("\n\n\t!! CLIENTE APAGADO COM SUCESSO !!\n");
        }
        else{
            system("cls");
            printf("\n\t!! CLIENTE JA EFETUOU SAQUE !!\n\n");
        }

    }
    else{
        if (posicao<0 || posicao>qtd_clientes)//CASO ELE DIGITE UM NUMERO FORA DOS NUMEROS PRINTADOS PRA ELE
        {
            system("cls");
            printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/APAGA CLIENTE-----\n");
            printf("\n\t!! POSICAO NAO ENCONTRADA !!\n\n\t");
            system("pause");
            system("cls");//apaga tela
        }
        //se for a ultima posicao, so incrementa o total de cadastros
        if (posicao==qtd_clientes)
        {
            qtd_clientes--;//diminui uma posicao do total de cliente
            //verifica se ele havia feito algum saque e atualiza, pois irah aparecer o ultimo usuario em sua posicao
            for (i=0;i<cont;i++)
            {
                if (verifica_sf_saque[i]==posicao-1)
                {
                    verifica_sf_saque[i]=verifica_sf_saque[cont];
                    cont--;
                }
            }
            system("cls");
            printf("\n\n\t!! CLIENTE APAGADO COM SUCESSO !!\n");
        }

    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: TESTA_CONTA
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE A CONTA INFORMADA JÁ EXISTE
//PARAMETRO: A CONTA CORRENTE DIGITADA PELO USUARIO
//RETORNO: 0 SE NAO EXISTIR, E RETORNA 1 CASA JÁ EXISTA
//-------------------------------------------------------------------------------------------------------------------------------
int testa_conta(int conta){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i,j,x=0;//contadores
    int qtd;//conta a quantidade de digitos iguais
    //---------------------------------------------

    for (i=0;i<=qtd_clientes;i++)//laço verifica se a conta corrente informada ja existe para algum cadastro
    {
        if (conta == conta_corrente[i]){//verifica se os digitos são os mesmos na conta informada e nas contas cadastradas
            x = 1;//ou seja , ao menos uma conta dentro das cadastradas é igual a nova conta informada
            i = qtd_clientes;
        }

    }

    return (x);

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: VALOR_SACADO
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA O SALDO QUE JÁ FOI SACADO DO CAIXA ELETRONICO
//-------------------------------------------------------------------------------------------------------------------------------
void valor_sacado(int sacado){

    printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/SALDO DE SAQUES-----------\n");
    printf("\n\tSAQUE TOTAL EFETUADO = %d \n\n",sacado); // variavel acumulativa para o saque
    extenso(sacado);
    printf(" REAIS\n\t");
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: QTD_CEDULAS
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA A QUANTIDADE DISPONÍVEL PARA SAQUE DE CADA CÉDULA
//-------------------------------------------------------------------------------------------------------------------------------
void qtd_cedulas(){

    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/CONTAGEM DE CEDULAS-----\n");
    printf("\n\tVALOR \t\t QTD \n");
    printf("\n\t-NOTAS DE 1,00   = %d -- ",vernot1);//mostra a quantidade de cedulas existentes para saque de 1,00
    extenso(vernot1);
    printf("\n\t-NOTAS DE 2,00   = %d -- ",vernot2);//mostra a quantidade de cedulas existentes para saque de 2,00
    extenso(vernot2);
    printf("\n\t-NOTAS DE 5,00   = %d -- ",vernot5);//mostra a quantidade de cedulas existentes para saque de 5,00
    extenso(vernot5);
    printf("\n\t-NOTAS DE 10,00  = %d -- ",vernot10);//mostra a quantidade de cedulas existentes para saque de 10,00
    extenso(vernot10);
    printf("\n\t-NOTAS DE 20,00  = %d -- ",vernot20);//mostra a quantidade de cedulas existentes para saque de 20,00
    extenso(vernot20);
    printf("\n\t-NOTAS DE 40,00  = %d -- ",vernot40);//mostra a quantidade de cedulas existentes para saque de 40,00
    extenso(vernot40);
    printf("\n\t-NOTAS DE 50,00  = %d -- ",vernot50);//mostra a quantidade de cedulas existentes para saque de 50,00
    extenso(vernot50);
    printf("\n\t-NOTAS DE 100,00 = %d -- ",vernot100);//mostra a quantidade de cedulas existentes para saque de 100,00
    extenso(vernot100);
    printf("\n\t-NOTAS DE 200,00 = %d -- ",vernot200);//mostra a quantidade de cedulas existentes para saque de 200,00
    extenso(vernot200);

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: VALOR_SALDO
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: IMPRIMIR NA TELA O SALDO DISPONÍVEL DO CAIXA
//-------------------------------------------------------------------------------------------------------------------------------
void valor_saldo(int saldo){

    printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/SALDO EXISTENTE-----------\n");
    printf("\n\tSALDO = %d,00 \n\n\t",saldo);//variável acumulativa para o saldo disponível
    extenso(saldo);
    printf(" REAIS\n\t");
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ABASTECE_CAIXA
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: ABASTECER O CAIXA ELETRONICO INFORMANDO AS OPÇOES DE ESCOLHA DE NOTAS
//-------------------------------------------------------------------------------------------------------------------------------
void abastece_caixa(){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int nota1,nota2,nota5,nota10,nota20,nota50,nota40,nota100,nota200;//tipos de cedulas a serem abastecidas
    int menu;//leitura da opção da nota
    int x;//receberá o valor da diferença entre a quantidade de notas e o limite do tipo
    //------------------------------------------------------------------------------------
    void f_gerente();
    //menu de opções
    printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA---------\n");//guia usuario
    printf("\t- 200...CEDULAS DE 200,00                                 -\n");
    printf("\t- 100...CEDULAS DE 100,00                                 -\n");
    printf("\t- 50....CEDULAS DE 50,00                                  -\n");
    printf("\t- 40....CEDULAS DE 40,00                                  -\n");
    printf("\t- 20....CEDULAS DE 20,00                                  -\n");
    printf("\t- 10....CEDULAS DE 10,00                                  -\n");
    printf("\t- 5.....CEDULAS DE 5,00                                   -\n");
    printf("\t- 2.....CEDULAS DE 2,00                                   -\n");
    printf("\t- 1.....CEDULAS DE 1,00                                   -\n");
    printf("\t- 0.....VOLTAR                                            -\n");
    printf("\t-----------------------------------------------------------");

    printf("\n\tDIGITE O CODIGO DA OPCAO DESEJADA..\n\t");
    scanf("%d", &menu);//leitura da opção digitada

    switch (menu){//escolha - caso

        case 1: // caso queira abastecer com notas de 1,00
            if (vernot1 >= 2000){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 1,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls"); //comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----\n"); // guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                scanf("%d", &nota1); // lendo quantia de notas de 1

                if ((nota1 > 2000) || (nota1 < 0)){ // se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!"); // aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----\n"); // guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                    scanf("%d", &nota1); // relendo a quantia de notas
                    if (nota1 == 0){ // caso digite 0 notas
                        system("cls");// apaga tela
                    }
                }

                if ((nota1 > 0) && (nota1 <= 2000)){//se estiver dentro do intervalo
                    system("cls");// apaga tela
                    vernot1 = vernot1 + nota1;//atualiza a quantidade de notas de 1,00 que o caixa possui
                    if (vernot1 >= 2000){//caso as notas ultrapassem a quantidade limitada
                        x = 2000-(vernot1-nota1);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 1,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 1,00\n\n\t", x);//mostra a quantia de notas abastecidas
                        vernot1=(vernot1-nota1)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*1);//atualizando o caixa com o valor máximo de notas de 1
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 1,00\n\n\t", nota1);//mostra a quantia de notas abastecidas
                        saldocaixa = (saldocaixa+vernot1);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota1 > 2000) || (nota1 < 0));//enquanto as notas estejam fora do intervalo
        }

        break;//pausa

        case 2: // caso abasteca com notas de 2 reais
            if (vernot2 >= 1500){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 2,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls"); //comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----\n"); // guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                scanf("%d", &nota2); // lendo quantia de notas de 2

                if ((nota2 > 1500) || (nota2 < 0)){ // se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!"); // aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----\n"); // guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                    scanf("%d", &nota2); // relendo a quantia de notas
                    if (nota2 == 0){ // caso digite 0 notas
                        system("cls");// apaga tela
                    }
                }

                if ((nota2 > 0) && (nota2 <= 1500)){//se estiver dentro do intervalo
                    system("cls");// apaga tela
                    vernot2 = vernot2 + nota2;//atualiza a quantidade de notas de 2,00 que o caixa possui
                    if (vernot2 >= 1500){//caso as notas ultrapassem a quantidade limitada
                        x = 1500-(vernot2-nota2);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 2,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 2,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot2=(vernot2-nota2)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*2);//atualizando o caixa com o valor máximo de notas de 2
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 2,00\n\t", nota2);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot2*2);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota2 > 1500) || (nota2 < 0));//enquanto as notas estejam fora do intervalo
        }

            break; // pausa

        case 5://caso queira abastecer com notas de 5
            if (vernot5 >= 800){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 5,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota5); // lendo quantia de notas de 5

                if ((nota5 > 800) || (nota5 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota5); // relendo a quantia de notas
                    if (nota5 == 0){ // caso digite 0 notas
                        system("cls");// apaga tela
                    }
                }

                if ((nota5 > 0) && (nota5 <= 800)){//se estiver dentro do intervalo
                    system("cls");// apaga tela
                    vernot5 = vernot5 + nota5;//atualiza a quantidade de notas de 5,00 que o caixa possui
                    if (vernot5 >= 800){//caso as notas ultrapassem a quantidade limitada
                        x = 800-(vernot5-nota5);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 5,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 5,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot5=(vernot5-nota5)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*5);//atualizando o caixa com o valor máximo de notas de 5
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 5,00\n\t", nota5);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot5*5);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota5 > 800) || (nota5 < 0));//enquanto as notas estejam fora do intervalo
        }

        break; // pause



        case 10://caso queira abastecer com notas de 10,00
            if (vernot10 >= 700){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 10,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota10); //lendo quantidade de notas de 10

                if ((nota10 > 700) || (nota10 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota10);//relendo a quantia de notas
                    if (nota10 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota10 > 0) && (nota10 <= 700)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot10 = vernot10 + nota10;//atualiza a quantidade de notas de 10,00 que o caixa possui
                    if (vernot10 >= 700){//caso as notas ultrapassem a quantidade limitada
                        x = 700-(vernot10-nota10);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 10,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 10,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot10=(vernot10-nota10)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*10);//atualizando o caixa com o valor máximo de notas de 10
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 10,00\n\t", nota10);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot10*10);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota10 > 700) || (nota10 < 0));//enquanto as notas estejam fora do intervalo
        }

        break; // pause

          case 20://caso queira abastecer com notas de 20,00
            if (vernot20 >= 600){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 20,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota20); //lendo quantidade de notas de 20

                if ((nota20 > 600) || (nota20 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota20);//relendo a quantia de notas
                    if (nota20 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota20 > 0) && (nota20 <= 600)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot20 = vernot20 + nota20;//atualiza a quantidade de notas de 20,00 que o caixa possui
                    if (vernot20 >= 600){//caso as notas ultrapassem a quantidade limitada
                        x = 600-(vernot20-nota20);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 20,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 20,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot20=(vernot20-nota20)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*20);//atualizando o caixa com o valor máximo de notas de 20
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 20,00\n\t", nota20);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot20*20);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota20 > 600) || (nota20 < 0));//enquanto as notas estejam fora do intervalo
        }


        break;// pause

        case 40://caso queira abastecer com notas de 40
            if (vernot40 >= 500){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 40-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 40,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 40-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota40); //lendo quantidade de notas de 40

                if ((nota40 > 500) || (nota40 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 40-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota40);//relendo a quantia de notas
                    if (nota20 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota40 > 0) && (nota40 <= 500)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot40 = vernot40 + nota40;//atualiza a quantidade de notas de 40,00 que o caixa possui
                    if (vernot40 >= 500){//caso as notas ultrapassem a quantidade limitada
                        x = 500-(vernot40-nota40);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 40-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 20,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 40,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot40=(vernot40-nota40)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*40);//atualizando o caixa com o valor máximo de notas de 40
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 40-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 40,00\n\t", nota40);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot40*40);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota40 > 500) || (nota40 < 0));//enquanto as notas estejam fora do intervalo
        }

        break; // pause


        case 50: // caso queira abastecer com notas de 50
            if (vernot50 >= 400){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 50,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota50); //lendo quantidade de notas de 50

                if ((nota50 > 400) || (nota50 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota50);//relendo a quantia de notas
                    if (nota50 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota50 > 0) && (nota50 <= 400)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot50 = vernot50 + nota50;//atualiza a quantidade de notas de 50,00 que o caixa possui
                    if (vernot50 >= 400){//caso as notas ultrapassem a quantidade limitada
                        x = 400-(vernot50-nota50);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 50,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 50,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot50=(vernot50-nota50)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*50);//atualizando o caixa com o valor máximo de notas de 50
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 50,00\n\t", nota50);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot50*50);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota50 > 400) || (nota50 < 0));//enquanto as notas estejam fora do intervalo
        }

        break; // pause

        case 100:
             if (vernot100 >= 200){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 100-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 100,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 100-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota100); //lendo quantidade de notas de 50

                if ((nota100 > 200) || (nota100 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 100-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota100);//relendo a quantia de notas
                    if (nota100 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota100 > 0) && (nota100 <= 200)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot100 = vernot100 + nota100;//atualiza a quantidade de notas de 100,00 que o caixa possui
                    if (vernot100 >= 200){//caso as notas ultrapassem a quantidade limitada
                        x = 200-(vernot100-nota100);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 100-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 100,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 100,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot100=(vernot100-nota100)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*100);//atualizando o caixa com o valor máximo de notas de 100
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 100-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 100,00\n\t", nota100);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot100*100);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota100 > 200) || (nota100 < 0));//enquanto as notas estejam fora do intervalo
        }

        break; // pause

        case 200: // caso queira abastecer com cedulas de 200,00
              if (vernot200 >= 100){
                system("cls");//apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 200-----\n");//guia usuário
                printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 200,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                system("pause");
                system("cls"); //comando apaga tela
            }
            else{
                do{//repita
                system("cls");//comando apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 200-----\n");//guia usuario
                printf("\t- INFORME A QUANTIDADE DE CEDULAS QUE DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                scanf("%d", &nota200); //lendo quantidade de notas de 200

                if ((nota200 > 100) || (nota200 < 0)){//se realmente estiver fora
                    system("cls");//comando apaga tela
                    printf("\n\t !! QUANTIDADE NAO SUPORTADA. INFORME UMA QUANTIDADE VALIDA !!");//aviso ao usuario
                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 200-----\n");//guia usuario
                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");//guia usuario
                    scanf("%d", &nota200);//relendo a quantia de notas
                    if (nota200 == 0){//caso digite 0 notas
                        system("cls");//apaga tela
                    }
                }

                if ((nota200 > 0) && (nota200 <= 100)){//se estiver dentro do intervalo
                    system("cls");//apaga tela
                    vernot200 = vernot200 + nota200;//atualiza a quantidade de notas de 200,00 que o caixa possui
                    if (vernot200 >= 100){//caso as notas ultrapassem a quantidade limitada
                        x = 100-(vernot200-nota200);
                        system("cls");//apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 200-----\n");//guia usuário
                        printf("\n\t!! AVISO !!\n\n\t!! QUANTIDADE MAXIMA DE NOTAS DE R$ 200,00 ATINGIDA, \n\tABASTECA COM OUTROS VALORES !!\n\t"); // mensagem para o usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 200,00\n\t", x);//mostra a quantia de notas abastecidas
                        vernot200=(vernot200-nota200)+x;//faz a atualização da contagem de notas somente com a diferença
                        saldocaixa = saldocaixa+(x*200);//atualizando o caixa com o valor máximo de notas de 200
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    else{
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 200-----\n");//guia usuario
                        printf("\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 200,00\n\t", nota200);//mostra a quantia de notas abastecidas
                        saldocaixa = saldocaixa+(vernot200*200);//saldo do caixa aumentando o valor
                        system("pause");
                        system("cls"); //comando apaga tela
                    }
                    l = l+1;//controla a quantidade de vezes que o caixa foi abastecido -- variavel para liberação do saque
                }

            }while((nota200 > 100) || (nota200 < 0));//enquanto as notas estejam fora do intervalo
        }

        break;

        case 0://voltar
            f_gerente();
        break;

        default://caso a opção seja inválida

            system("cls");
            printf("\n\tOPCAO INEXISTENTE! TENTE OUTRA VEZ..\n");

        break;

    }


}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: MOSTRA_SAQUES_CLIENTES
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: MOSTRAR O CPF DE CADA SAQUE EFETUADO
//PARAMENTRO: SEM PARAMETRO DE ENTRADA
//-------------------------------------------------------------------------------------------------------------------------------
void mostra_saques_clientes (){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i,j;
    //------------------------------------

    system("cls");
    //VERIFICA SE JA FOI FEITO ALGUM SAQUE, QUE SERA CONTADO PELO OU MENOS 1 SE SIM
    if (saque_valido>0){
        printf("\n\n\t----SISTEMA BANCARIO/GERENTE/VALORES SACADOS----\n");
        printf("\n\tCPF\t\t\tSAQUE\n");
        for (i=0;i<saque_valido;i++)
        {
            printf("\t");
            for(j=0;j<11;j++){
                printf("%c",cpf_saque[i][j]);
            }
            printf("\t\t%d\n",saques_clientes[i]);
        }
    }
    else{
        printf("\n\n\t----SISTEMA BANCARIO/GERENTE/VALORES SACADOS----\n");
        printf("\n\t !! NAO FOI EFETUADO NENHUM SAQUE !!\n\n\t");
    }
    system("pause");
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: LIBERAR_NOTAS
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: ATUALIZAR AS NOTAS DO CAIXA E IMPRIMIR O SAQUE
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------------------------------------------------
void liberar_notas()//cedulas que vao ser retiradas
{

    //notas de 200
    if (a200>0) {
        printf("\n\t%d NOTA(S) - R$ 200,00",a200); // mostrando as notas que sairam
        vernot200 = vernot200 - a200; // diminuindo a quantidade de notas do caixa
        saldocaixa = saldocaixa - (a200*200);
        totsak = totsak + (a200*200);
    }
    //notas de 100
    if (a100>0) {
        printf("\n\t%d NOTA(S) - R$ 100,00",a100); // mostrando as notas que sairam de 100
        vernot100 = vernot100 - a100; // subtraindo o quantidade de notas do caixa
        saldocaixa = saldocaixa - (a100*100);
        totsak = totsak + (a100*100);
    }
    //notas de 50
    if (a50>0){
        printf("\n\t%d NOTA(S) - R$ 50,00",a50); // mostrando as notas que foram retiradas
        vernot50 = vernot50 - a50; // diminuindo as notas de 50 do caixa
        saldocaixa = saldocaixa - (a50*50);
        totsak = totsak + (a50*50);
    }
    //notas de 40
    if (a40>0){
        printf("\n\t%d NOTA(S) - R$ 40,00",a40); // mostrando as notas que foram retiradas
        vernot40 = vernot40 - a40; // diminuindo as notas de 40 do caixa
        saldocaixa = saldocaixa - (a40*40);
        totsak = totsak + (a40*40);
    }
    //notas de 20
    if (a20>0) {
        printf("\n\t%d NOTA(S) - R$ 20,00",a20); // mostra as notas retiradas
        vernot20 = vernot20 - a20; // subtrai-se as notas do caixa com as notas retiradas, para serem retiradas do caixa
        saldocaixa = saldocaixa - (a20*20);
        totsak = totsak + (a20*20);
    }
    //notas de 10
    if (a10>0) {
        printf("\n\t%d NOTA(S) - R$ 10,00",a10);
        vernot10 = vernot10 - a10;
        saldocaixa = saldocaixa - (a10*10);
        totsak = totsak + (a10*10);
    }
    //notas de 5
    if (a5>0) {
        printf("\n\t%d NOTA(S) - R$ 5,00",a5);
        vernot5 = vernot5 - a5;
        saldocaixa = saldocaixa - (a5*5);
        totsak = totsak + (a5*5);
    }
    //notas de 2
    if (a2>0) {
        printf("\n\t%d NOTA(S) - R$ 2,00",a2);
        vernot2 = vernot2 - a2;
        saldocaixa = saldocaixa - (a2*2);
        totsak = totsak + (a2*2);
    }
    //notas de 1
    if (a1>0) {
        printf("\n\t%d NOTA(S) - R$ 1,00",a1);
        vernot1 = vernot1 - a1;
        saldocaixa = saldocaixa - a1;
        totsak = totsak + a1;
    }
    printf("\n\t");

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VER_CAIXA_SAQUE_0
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE HÁ NOTAS SUFICIENTES PARA EFETUAR O SAQUE
//PARAMETRO: DE ENTRADA QUE É O SAQUE
//RETORNO: saque_ced, QUE VAI SER 0 SE HOUVER CEDULAS E <> DE 0 SE NAO HOUVER CEDULAS
//-------------------------------------------------------------------------------------------------------------------------------
int Ver_caixa_saque_0(int saq_ced)
{
    a200=0; a100=0; a50=0; a40=0; a20=0; a10=0; a5=0; a2=0; a1=0;//cedulas que vao ser retiradas

    if ((saq_ced/200>0) && (vernot200>0)) // caso houver notas suficientes para serem retiradas corretamente
    {

        a200 = saq_ced/200;
        if (vernot200>=a200)
        {
            saq_ced = (saq_ced - (a200*200));
        }
        else{
            a200 = vernot200; // como esgtaram as notas de 500, as notas que haviam sairam todas.
            saq_ced = (saq_ced - (a200*200));
        }
    }
    if ((saq_ced/100>0) && (vernot100>0)) // se houver notas de 150 a mais ou igual
    {
        a100 = saq_ced/100;
        if (vernot100>=a100){
            a100 = saq_ced/100;
            saq_ced = saq_ced - (a100*100);
        }
        else{
            a100 = vernot100; // Como as notas do caixa sao menores do que as notas que poderiam ser
                            // retiradas se houvesse mais, as notas retiradas fica com o mesmo valor das notas do caixa
            saq_ced = (saq_ced - (a100*100));
        }
    }
    if ((saq_ced/50>0) && (vernot50>0)) // caso houver notas suficientes para serem retiradas
    {

        a50 = saq_ced/50;
        if (vernot50>=a50){
            saq_ced = saq_ced - (a50*50);
        }
        else{
            a50 = vernot50; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (a50*50));
        }
    }
    if ((saq_ced/40>0) && (vernot40>0)) // caso houver notas suficientes para serem retiradas
    {

        a40 = saq_ced/40;
        if (vernot40>=a40){
            saq_ced = saq_ced - (a40*40);
        }
        else{
            a40 = vernot40; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (a40*40));
        }
    }
    if((saq_ced/20>0) && (vernot20>0)) // caso as notas de 20 forem suficientes
    {

        a20 = saq_ced/20;
        if (vernot20>=a20){
            saq_ced = (saq_ced - (a20*20));
        }
        else{
            a20 = vernot20;
            saq_ced = (saq_ced - (a20*20));
        }
    }
    if ((saq_ced/10>0) && (vernot10>0))
    {

        a10 = saq_ced/10;
        if (vernot10>=a10){
            saq_ced = saq_ced - (a10*10);
        }
        else{
            a10 = vernot10;
            saq_ced = (saq_ced - (a10*10));
        }
    }
    if ((saq_ced/5>0) && (vernot5>0))
    {

        a5 = saq_ced/5;
        if (vernot5>=a5){
            saq_ced = saq_ced - (a5*5);
        }
        else{
            a5 = vernot5;
            saq_ced = (saq_ced - (a5*5));
        }
    }
    if ((saq_ced/2>0) && (vernot2>0))
    {

        a2 = saq_ced/2;
        if (vernot2>=a2){
            saq_ced = saq_ced - (a2*2);
        }
        else{
            a2 = vernot2;
            saq_ced = saq_ced - (a2*2);
        }
    }
    if (vernot1>0)
    {
        a1 = saq_ced;
        saq_ced = saq_ced - a1;

    }
    return (saq_ced);

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VERIFICA_CONTA
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR A POSIÇÃO DA CONTA DENTRO DO VETOR CASO SEJA EXISTENTE
//PARAMETRO: A CONTA DIGITADA
//RETORNO: RETORNA -1 SE NÃO HOUVER CONTA, E RETORNA A POSICAO DA CONTA SE HOUVER CONTA CORRENTE IGUAL
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_conta(int conta){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int j,cliente; //j varia a posicão da conta, cliente vai obter a posicao da conta corrente se houver

    //--------------------------------------------------------

    cliente = -1;
    for (j=0;j<qtd_clientes;j++)
    {
        if (conta==conta_corrente[j])
        {
            cliente = j;
            j = qtd_clientes;
        }

    }

    return (cliente);
}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: TESTA_CPF
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE HA UM CPF JA CADASTRADO
//PARAMETRO: O CPF DIGITADO PELO USUARIO
//RETORNO: 0 SE NAO HOUVER CADASTRO, E RETORNA 1 CASA HAJA O CADASTRO
//-------------------------------------------------------------------------------------------------------------------------------
int testa_cpf(char cpf[]){

    //DECLARAÇÃO DE VARIAVEIS LOCAIS
    int i,j;//contadores
    int qtd;//conta os digitos iguais
    //-------------------------------
   // do{//repita
        //printf("Eai");
        //system("pause");

    for (i=0;i<qtd_clientes;i++)//laço verifica se o cpf informado já possui cadastro
    {
        qtd=0;//ao final de cada linha da matriz a quantidade é reiniciada em 0
        for (j=0;j<12;j++)//faz o controle das colunas
        {
            if (cpf[j] == clientes[i][j]){//toda vez que o digito for existente a quantidade é incrementada
                qtd = qtd+1;
            }
            if (qtd>10)
            {
                i = qtd_clientes;
            }
        }
    }
    //while((qtd<10) && (i!=qtd_clientes));
    if (qtd > 10){
        return 1;
    }
    else{
        return 0;
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VERIFICA_CLIENTE_E_SAQUE
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE O CLIENTE JA FEZ ALGUM SAQUE
//PARAMETRO: DE ENTRADA QUE É A POSICAO QUE O CLIENTE SE ENCONTRA
//RETORNO: a, QUE VAI SER 0 SE O CLIENTE EFETUOU ALGUM SAQUE CASO CONTRARIO DEVOLVE DIFERENTE DE 0
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_cliente_e_saque(int cliente){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int a=0,i;

    for (i=0;i<cont;i++)
    {
        if (verifica_sf_saque[i] == cliente)
        {
            a++;
        }
    }

    return a;
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: ALTERA_CLIENTE
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: ALTERAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void altera_cliente()
{

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i,j;
    int x;//recebe o valor retornado pela função testa_cpf após verificação se ha um cpf ja cadastrado
    int op,op2;//opções durante a execução da função
    int icpf[11];//vetor para receber o cpf em forma de inteiros
    char cpf[11];
    int conta;//vetores para conta corrente em uma array de caracteres
    //int a;

    printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
    printf("\n\tCOD.\tTITULAR\t\tCONTA/CORRENTE\n");

    for (i=0;i<qtd_clientes;i++)//imprime lista de clientes
    {
        printf("\t");//espaçamento
        printf("%d\t",i+1);//imprime o código do cliente na lista

        for (j=0;j<11;j++)//laço imprime cpf
        {
            printf("%c",clientes[i][j]);
        }
        printf("\t");//espaçamento

        //for (j=0;j<6;j++)//laço imprime conta-corrente
        //{
        printf("%d",conta_corrente[i]);
        //}
        printf("\n");//pula uma linha após cada impressão do cliente e sua respectiva conta
    }

    printf("\n\tINFORME O CODIGO DO CLIENTE QUE DESEJA ALTERAR..\n\t");
    scanf("%d",&op);//faz a leitura do codigo do cliente para alterações

    if ((op > qtd_clientes) || (op < 1)){//caso o código não exista a mensagem é exibida na tela
        system("cls");//apaga tela
        printf("\n\t!! CODIGO DE CLIENTE INVALIDO !!");
    }
    else{//caso o código seja válido um novo menu de opções
        //perguntará se deseja efetuar alterações nos dados do cpf ou conta-corrente
        if (verifica_cliente_e_saque(op-1)==0){
            while ((op2>2) || (op2<1)){
                system("cls");
                printf("\n\n\t------SISTEMA BANCARIO/CLIENTE/ALTERA CLIENTES---\n");
                printf("\n\tCOD.\tTITULAR\t\tCONTA/CORRENTE\n");

                for (i=op-1;i<op;i++)//imprime a lista de clientes
                {
                    printf("\t");
                    printf("%d\t",i+1);
                    for (j=0;j<11;j++)
                    {
                        printf("%c",clientes[i][j]);
                    }

                    printf("\t");//espaçamento

                    //for (j=0;j<6;j++)//imprime os dados da conta-corrente
                    //{
                    printf("%d",conta_corrente[i]);
                    //}
                }
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
                            printf("\n\tDIGITE O NOVO CPF:\n\t");
                            scanf("%s",&cpf);

                            for(i=0;i<11;i++)//Efetua a conversao de vetor de char para um vetor de inteiros
                            {
                                icpf[i]=cpf[i]-48;
                            }

                            if (verifica_cpf(icpf)==0){
                                x = testa_cpf(cpf);
                                if (x == 0){
                                    //for (i=op-1;i<op;i++)//efetuando a atualizacão do cpf
                                    //{
                                    for (j=0;j<11;j++)
                                    {
                                        clientes[op-1][j] = cpf[j];
                                    }

                                    //}
                                    system("cls");
                                    printf("\n\t!!CPF VALIDO!!\n\tCADASTRO ATUALIZADO!\n");
                                }
                                else{
                                    system("cls");
                                    printf("\n\t!! CPF JA CADASTRADO !!\n\n\t");
                                    system("pause");
                                }
                            }
                            else{
                                //system("cls"); // apaga tela
                                printf("\n\t!!CPF INVALIDO!!");
                            }

                        break;
                        case 2:
                            //system("cls"); // apaga tela
                            printf("\n\tDIGITE A NOVA CONTA CORRENTE:\n\t");
                            scanf("%d",&conta);
                            //for (i=op-1;i<op;i++)//efetuando atualização da conta corrente
                            //{
                            if (verifica_conta(conta) > -1)
                            {
                                printf("\n\t !! CONTA JA POSSUI CADASTRO !!\n\t");
                            }
                            else{
                                //for (j=0;j<6;j++)
                                //{
                                conta_corrente[op-1] = conta;
                                //}
                                system("cls");
                                printf("\n\t !! CADASTRO ATUALIZADO !!\n");
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
}

//-------------------------------------------------------------------------------------------------------------------------------
//FUNÇÃO: VERIFICA_CPF
//TIPO: COM PASSAGEM DE PARÂMETRO E COM RETORNO
//OBJETIVO: VERIFICAR SE O CPF É VÁLIDO
//PARAMETRO: DE ENTRADA QUE É O CPF
//RETORNO: 0 SE O CPF FOR VALIDO E 1 CASO O CPF NAO SEJA VALIDO
//-------------------------------------------------------------------------------------------------------------------------------
int verifica_cpf(int cpf[]){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int i,somador=0,digito1,result1,result2,digito2,valor;
    int v,qtd=0;
    int verifica;//será o retorno da função
    //-----------------------------


    v = cpf[0];//v recebe primeiro digito do cpf para fazer verificação

    for (i=1;i<11;i++)//o laço ira contar a quantidade de digitos iguais no cpf
    {
        if (cpf[i] == v)
            qtd = qtd+1;
    }

    if (qtd == 10){//caso todos os digitos sejam o mesmo o cpf é inválido
        verifica = 1;
    }
    else{

    // VALIDAÇÃO DO PRIMEIRO DIGITO

    for(i=0;i<9;i++)
    {
        somador =somador+cpf[i]*(10-i);
    }

    result1=somador%11;

    if(result1<2){
        digito1=0 ;
    }
    else{
        digito1 = 11-result1;
    }

    //VALIDAÇÃO SEGUNDO DIGITO

    somador=0;

    for(i=0;i<10;i++)
    {
        somador+=cpf[i]*(11-i);
    }

    valor=(somador/11)*11;
    result2=somador-valor;

    if(result2<2){
        digito2=0;
    }
    else{
        digito2=11-result2;
    }

    //RESULTADOS DAS VALIDACOES

    if((digito1==cpf[9]) && (digito2==cpf[10])){
        verifica = 0;
    }
    else{
        verifica = 1;
    }

  }

    return(verifica);
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: CADASTRO_CLIENTE
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: EFETUAR O CADASTRO DE UM CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void cadastro_cliente(){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS------------------------------
    char cpf[11];//vetor armazena CPF
    int icpf[11];//armazena os digitos do cpf em um vetor de inteiros
    int conta;//vetor armazena dados da conta corrente
    int x,y=0,z;//recebe retorno das funçaõ verifica_cpf, testa_cpf e testa_conta
    int i,j;//contadoras
    //------------------------------------------------------------

    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/CADASTRO-----\n");
    printf("\n\tINFORME O CPF:\n\t");
    scanf("%s", cpf);//recebe os dígitos do cpf

    if (qtd_clientes > 0){//quando a quantidade de clientes for maior que 0
        y = testa_cpf(cpf);//será feita a verificação se o novo cpf a ser cadastrado já existe ou não
    }

    if (y == 1){//caso o cpf ja possua cadastro uma mensagem é impressa
        system("cls");//apaga a tela
        printf("\n\t !! CPF JA POSSUI CADASTRO !!\n\t");
    }
    else{//caso nao possua o sistema continua com o cadastro
        for(i=0;i<11;i++)//Efetua a conversao de vetor de char para um vetor de inteiros
        {
            icpf[i]=cpf[i]-48;
        }

        x=verifica_cpf(icpf); //chamada da função verifica_cpf com passagem de parametro

            if (x == 0){//caso o cpf seja valido o cadastro do cliente tem continuidade
                system("cls");
                printf("\n\n\t----------SISTEMA BANCARIO/CLIENTE/CADASTRO-----------\n");
                printf("\n\t!! CPF VALIDO !!\n");
                do{
                    printf("\n\tDIGITE OS DADOS DA CONTA CORRENTE:\n\t");//leitura da conta corrente
                    scanf("%d",&conta);
                    z = verifica_conta(conta);//chamada da função que verifica a validade da conta corrente informada
                    if (z > -1){//caso a conta já exista a mensagem é exibida na tela
                        system("cls");//apaga a tela
                        printf("\n\n\t----------SISTEMA BANCARIO/CLIENTE/CADASTRO-----------\n");
                        printf("\n\t !! CONTA CORRENTE JA EXISTENTE !!\n");
                    }
                }while(z > -1);//enquanto o retorno da função testa_conta for 1, ou seja a conta já existe. Será pedida uma nova conta
                system("cls");//apaga a tela
                //apos receber uma conta-corrente valida o cadastro é finalizado
                printf("\n\n\t----------SISTEMA BANCARIO/CLIENTE/CADASTRO-----------\n");
                printf("\n\t !! CADASTRO EFETUADO COM SUCESSO !!\n");


                for (i=qtd_clientes;i<=qtd_clientes;i++)//laço coloca os dados informados nas matrizes globais
                {
                    for (j=0;j<11;j++)//armazenando o cpf do cliente na matriz
                    {
                        clientes[i][j] = cpf[j];
                    }

                    for (j=0;j<6;j++)//armazenando a conta-corrente do cliente na matriz
                    {
                        conta_corrente[i] = conta;
                    }
                }

                qtd_clientes = qtd_clientes+1;//toda vez que um clienter for cadastrado com sucesso a quantidade contadora aumenta
        }
        else{//caso o cpf seja invalido é informado na tela
            system("cls");//apaga a tela
            printf("\n\t !! CPF INVALIDO !!");
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: IMPRIME_CLIENTES
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBEJTIVO: IMPRIMIR O CADASTRO DE CADA CLIENTE
//-------------------------------------------------------------------------------------------------------------------------------
void imprime_clientes(){

    //DECLARAÇÃO DE VARIAVEIS LOCAIS
    int i,j;//contadores
    //--------------------------------

    printf("\n\n\t---SISTEMA BANCARIO/CLIENTE/LISTA DE CLIENTES---\n");//guia usuário
    printf("\n\tTITULAR\t\tCONTA/CORRENTE\n");
    for (i=0;i<qtd_clientes;i++)
    {
        printf("\t");
        for (j=0;j<11;j++)
        {
            printf("%c",clientes[i][j]);
        }
        printf("\t");//espaçamento

        printf("%d",conta_corrente[i]);

        printf("\n");
    }

}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_CLIENTE
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: OFERECER AS OPÇÕES DO MENU DA OPÇÃO 'CLIENTE'
//-------------------------------------------------------------------------------------------------------------------------------
void f_cliente(){
    //VARIAVEIS LOCAIS MENU_CLIENTE
    int menu_cli;//leitura da opção digitada no menu

    menu_cli=0;//inicialização da variável menu_cli

    while(menu_cli != 5){
        printf("\n\n\t------SISTEMA BANCARIO/CLIENTE---\n");
        printf("\t- 1...CADASTRAR CLIENTE         -\n");
        printf("\t- 2...MOSTRAR CLIENTES          -\n");
        printf("\t- 3...ALTERAR CLIENTE           -\n");
        printf("\t- 4...APAGAR CLIENTE            -\n");
        printf("\t- 5...VOLTAR                    -\n");
        printf("\t---------------------------------\n\n");
        printf("\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%d", &menu_cli);

        if (menu_cli == 1){
            system("cls");
            cadastro_cliente();//chamada da função de cadastro do cliente
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
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: OFERECER AO USUÁRIO A OPÇÃO DE SAQUE
//-------------------------------------------------------------------------------------------------------------------------------
void f_saque(){

    //DECLARAÇÃO DE VARIÁVEIS LOCAIS
    int saque;
    int posi;
    char cc;
    int i,j;
    int a=0;
    //---------------------------------------------------------

    system("cls");//apaga tela
    printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");//guia usuário
    printf("\n\tDIGITE OS DADOS DA CONTA CORRENTE:\n\t");
    scanf("%d",&cc);
    posi = verifica_conta(cc);
    if (posi > -1){
        system("cls"); // apaga tela
        printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");//guia usuário
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
            printf("\n\t-NOTAS DE 1,00   = %d",vernot1);
            printf("\n\t-NOTAS DE 2,00   = %d",vernot2);
            printf("\n\t-NOTAS DE 5,00   = %d",vernot5);
            printf("\n\t-NOTAS DE 10,00  = %d",vernot10);
            printf("\n\t-NOTAS DE 20,00  = %d",vernot20);
            printf("\n\t-NOTAS DE 40,00  = %d",vernot40);
            printf("\n\t-NOTAS DE 50,00 = %d",vernot50);
            printf("\n\t-NOTAS DE 100,00 = %d",vernot100);
            printf("\n\t-NOTAS DE 200,00 = %d\n\n\t",vernot200);
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
            if (Ver_caixa_saque_0(saque)!=0)
            {
                system("cls"); // apaga tela
                printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                printf("\n\t !! CEDULAS NECESSARIAS PARA SAQUE INSUFICIENTES !!\n\t");
            }
            else{
                if (saque != 0){
                    m++;//incrementa o m para avisar que já foi efetuado saque!
                    Sleep (1000);
                    printf ("\r \t\t\t\t \n\n\n");
                    system("cls");
                    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                    printf("\n\tSAQUE EFETUADO COM SUCESSO..");
                    liberar_notas();
                    extenso(saque);
                    printf(" REAIS");
                    //obtendo o cpf de quem sacou
                    for (i=0;i<11;i++)
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
                    saque_valido++;
                }
            }

        }
    }
    else{
        system("cls"); // apaga tela
        printf("\n\t !! CONTA CORRENTE NAO CADASTRADA NO SISTEMA !!\n\t");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------
//PROCEDIMENTO: F_GERENTE
//TIPO: SEM PASSAGEM DE PARÂMETRO E SEM RETORNO
//OBJETIVO: OFERECER AO USUÁRIO A OPÇÃO DO MENU GERENTE
//-------------------------------------------------------------------------------------------------------------------------------
void f_gerente(){

    //DECLARAÇAO DE VARIAVEIS LOCAIS
    int menu2;//menu gerente
    //------------------------------------
    menu2 = 0;//inicialização da variável
    system("cls");

    while (menu2 != 6){
                //menu de opções
        system("cls");
        printf("\n\n\t----------SISTEMA BANCARIO/GERENTE-----------\n");
        printf("\t- 1...ABASTECER O CAIXA ELETRONICO          -\n");
        printf("\t- 2...VALORES SACADOS                       -\n");
        printf("\t- 3...VALOR TOTAL SACADO                    -\n");
        printf("\t- 4...VALOR SALDO EXISTENTE                 -\n");
        printf("\t- 5...QUANTIDADE DE CEDULAS EXISTENTES      -\n");
        printf("\t- 6...MENU PRINCIPAL                        -\n");
        printf("\t---------------------------------------------");
        printf("\n\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%d", &menu2);//leitura da opção digitada pelo usuário
        if (menu2 == 1){//opção4 abastecer caixa
            system("cls");//comando apaga tela
            abastece_caixa();//chamada do procedimento
            main();
        }
        if (menu2==2){
            mostra_saques_clientes();
        }
        if (menu2 == 3){//opção1 valor total sacado
            if (m == 0){//verifica se já foi feito algum saque
                system("cls"); // comando apaga tela
                //caso não tenha sido efetuado nenhum saque ainda
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/SALDO DE SAQUES-----\n");//guia usuário
                printf("\n\t !! AINDA NAO FORAM EFETUADOS SAQUES NESTE TERMINAL !!\n\n\t");
                system("pause");
            }
            else{//caso ja tiverem sido feitos saques no caixa
                system("cls");
                valor_sacado(totsak);//chamada do procedimento valor_sacado
                system("pause");     //irá mostrar na tela o total que já foi sacado até o momento
            }
        }
        if (menu2 == 4){//opção2 valor saldo existente
            if (l == 0){//verifica se o caixa eletronico já foi abastecido
                system("cls"); // comando apaga tela
                //caso não tenha sido abastecido ainda a mensagem aparecerá na tela
                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/SALDO DO CAIXA-----\n");
                printf("\n\tSALDO = 0,00. ABASTECA O CAIXA..\n\n\t");
                system("pause");
            }
            if (l != 0){//caso o caixa ja tenha sido abastecido ao menos uma vez
                system("cls"); // comando apaga tela
                valor_saldo(saldocaixa);//chamada do procedimento valor_saldo
                system("pause");
            }
        }
        if (menu2 == 5){//opção3 quantidade de células
                system("cls");//comando apaga tela
                qtd_cedulas();//chamada do procedimento
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
    //-------------------------------

    system("color f9");//muda a cor de fundo da tela

    menu = '0'; // incializando o valor da variavel para fazer o looop;
    while (menu != '4') { // enquanto nao for digitado 4 para terminar o processo, o menu fica ate ser digitado 4(ondição de saída)

        //system("cls");
        printf("\n\n\t----------SISTEMA BANCARIO-------\n");
        printf("\t- 1...CLIENTE                   -\n");
        printf("\t- 2...SAQUE                     -\n");
        printf("\t- 3...GERENTE                   -\n");
        printf("\t- 4...FINALIZAR                 -\n");
        printf("\t---------------------------------\n\n");
        printf("\tDIGITE A OPCAO DESEJADA..\n\t");
        scanf("%s", &menu); // lendo a opcao do  menu que o usuario deseja
        system("cls");

        if (menu == '1'){
            system("cls");
            f_cliente();
        }

        if (menu == '2'){ // caso va para o saque

            system("cls"); // comando apaga tela
            if (l == 0){ // verificacao se o caixa foi abastecido - se l = 0 n foi abastecido - se l<>0 foi abastecido
                system("cls");
                printf("\n\n\t-----SISTEMA BANCARIO/SAQUE-----\n");
                printf("\n\t!! O CAIXA ELETRONICO AINDA NAO FOI ABASTECIDO PELO GERENTE..\n\tABASTECA O CAIXA NO MENU GERENTE !!\n\t");
                //getch();

            }

            if (l != 0){ // caso foi abastecido o sistema continua
                f_saque();
            }
        }

        if (menu == '3'){
            f_gerente();
        }

        if (menu == '4'){
            system("cls");
            finaliza();
        }

    }
    return 0;
}
