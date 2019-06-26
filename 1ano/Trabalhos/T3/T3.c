/*Desenvolver um sistema para saques de um caixa eletrônico que deverá liberar o menor
número de cédulas para um valor solicitado pelo cliente. As cédulas armazenadas no
caixa são de 500, 150, 50, 20, 10, 5, 2 e 1 real.
O caixa eletrônico pode ser abastecido pelo gerente com as seguintes quantidades de
cédulas no máximo: 100 (cédulas) de 500; 200 de 150; 400 de 50; 800 de 20; 1.600
de 10; 3.200 de 5; 6.400 de 2 e 12.800 de 1 real.
Para sacar dinheiro o cliente deve fornecer seu CPF e o sistema irá liberar a quantidade
de cada cédula e o valor do saque por extenso será apresentando ao cliente caso o
CPF seja um CPF válido. Consulte como se determina se um CPF é válido.
Para o gerente o sistema deve informar o valor total sacado, o valor do saldo existente e
a quantidade de cada cédula armazenada no caixa eletrônico, após várias transações
efetuadas. O valor total sacado, o valor do saldo existente e a quantidade de cédulas
existentes devem ser informadas, além de seu valor numérico, o valor por extenso

*/

/*  RGM     INTEGRANTES
    35029   IURY RODRIGUES PRATES
    35237   RAFAELA DONASSOLO ALVES
    35043   RONALDO TAFAREL PEREIRA DE SOUZA
    35046   THIAGO VERON YAFUSSO
    35048   ZENALVO BASTOS PINTO JÚNIOR
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

int n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11; // recebe os numeros do cpf
int teste,teste2,primeiroverificador,segundoverificador,soma1,soma2,verifica; // faz operaçoes para validação do cpf
int saque;// obtem o valor do saque
int i, j; // faz iteração para encerramento do programa como carregamento
int saldocaixa=0; // variavel para verificar o saldo do caixa
char menu;//menu principal
char menu2;//menu gerente
int menu3;//menu abastecer caixa
int nota1,nota2,nota5,nota10,nota20,nota50,nota150,nota500;//tipos de cedulas
int m;//verifica se ja foi feito algum saque
int l;//verifica se caixa já foi abastecido
int a500, a150, a50, a20, a10, a5, a2, a1; //cedulas que vao ser retiradas
int totsak=0;// totsak eh o total jah sacado depois de varias transações
int vernot1=0, vernot2=0, vernot5=0, vernot10=0, vernot20=0, vernot50=0, vernot150=0, vernot500=0; // essas variaveis verificam as quantidade de notas caso ultrapassem o limite do banco.
// int res500, res150, res50, res20, res10, res5, res2, res1;
int saq_ced;
int CM ; //valor em centena milhar
int DM ; //valor em dezena de milhar
int UNM ; //valor em unidade de milhar
int CEN ; //valor em centena
int DEZ ; //valor em dezena
int UN ; //valor em unidade
int dif;

void main(){


    system("color f9");

    l = 0;
    m = 0;


    menu = '9'; // incializando o valor da variavel para fazer o looop;

    while (menu != '3') { // enquanto nao for digitado 3 para terminar o processo, o menu fica ate ser digitado 3
        if (menu != '1') // condicao para verificar se o caixa ja foi abastecido, se sim, continua, caso contrario
                      // ococrre iteração do menu com mensagem sobre o caixa
            //system("cls");
            printf("\n\tUSE SOMENTE TECLADO NUMERICO!!\n");
            printf("\n\n\t----------MENU BANCARIO----------\n");
            printf("\t- 1...SAQUE                     -\n");
            printf("\t- 2...GERENTE                   -\n");
            printf("\t- 3...FINALIZAR                 -\n");
            printf("\t---------------------------------\n\n");
            printf("\tDIGITE A OPCAO DESEJADA..\n\t");
            scanf("%s", &menu); // lendo a opcao do  menu que o usuario deseja
        if (menu == '1'){ // caso va para o saque
            system("cls"); // comando apaga tela
            if (l == 0) // verificacao se o caixa foi abastecido - se l = 0 n foi abastecido - se l<>0 foi abastecido
                printf("\n\tO CAIXA ELETRONICO AINDA NAO FOI ABASTECIDO PELO GERENTE..\n\tABASTECA O CAIXA NO MENU GERENTE..\n");
                if (l != 0){ // caso foi abastecido o sistema continua
                    printf("\n\tPARA EFETUAR O SAQUE DIGITE O SEU CPF..\n");// obtendo o cpf. Numero por numero
                    printf("\n");
                    printf("\tDigite o digito 1..\n\t");
                    scanf("%d", &n1);
                    while ((n1<0)|| (n1>9)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 1..\n\t");
                            scanf("%d", &n1);

                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 2..\n\t");
                    scanf("%d", &n2);
                    while ((n2 > 9) || (n2 < 0)){ // serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 2..\n\t");
                            scanf("%d", &n2);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 3..\n\t");
                    scanf("%d", &n3);
                    while ((n3 > 9) || (n3 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 3..\n\t");
                            scanf("%d", &n3);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 4..\n\t");
                    scanf("%d", &n4);
                    while ((n4 > 9) || (n4 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 4..\n\t");
                            scanf("%d", &n4);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 5..\n\t");
                    scanf("%d", &n5);
                    while ((n5 > 9) || (n5 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("Digite o digito 5..\n\t");
                            scanf("%d", &n5);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 6..\n\t");
                    scanf("%d", &n6);
                    while ((n6 > 9) || (n6 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 6..\n\t");
                            scanf("%d", &n6);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 7..\n\t");
                    scanf("%d", &n7);
                    while ((n7 > 9) || (n7 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 7..\n\t");
                            scanf("%d", &n7);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 8..\n\t");
                    scanf("%d", &n8);
                    while ((n8 > 9) || (n8 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 8..\n\t");
                            scanf("%d", &n8);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 9..\n\t");
                    scanf("%d", &n9);
                    while ((n9 > 9) || (n9 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 9..\n\t");
                            scanf("%d", &n9);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 10..\n\t");
                    scanf("%d", &n10);
                    while ((n10 > 9) || (n10 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 10..\n\t");
                            scanf("%d", &n10);
                    }
                    system("cls"); // comando apaga tela
                    printf("\n\tDigite o digito 11..\n\t");
                    scanf("%d", &n11);
                    while ((n11 > 9) || (n11 < 0)){// serao digitados apenas numero de 0 ate 9
                            system("cls"); // comando apaga tela
                            printf("\tDigite o digito 11..\n\t");
                            scanf("%d", &n11);
                    }
                    // condicao caso o digite os numeros iguais, pois a verificacao alega ser valido esse cpf, e nas normas nao existe cpf dessa forma
                    if ((n1==n2)&&(n2==n3)&&(n3==n4)&&(n4==n5)&&(n5==n6)&&(n6==n7)&&(n7==n8)&&(n8==n9)&&(n9==n10)&&(n10==n11)){
                            printf("\n\tO CPF E INVALIDO!!");
                        }
                    else{ // fazendo a verificacao se o cpf eh valido ou nao
                        soma1 = ((n1*10)+(n2*9)+(n3*8)+(n4*7)+(n5*6)+(n6*5)+(n7*4)+(n8*3)+(n9*2));
                        teste = soma1%11;

                        if (teste<2){ // se teste for igual a 1 (11-1=10) e 10 nao eh unidade e a verificacao soh eh feita com unidade
                            primeiroverificador = 0; // recebe 0 por conta da unidade que nao foi encontrada e sim uma dezena
                            }
                            else
                                if (teste >= 2){ // caso contrario a subtração ocorrerá normalmente
                                    primeiroverificador = (11-teste);
                                }
                                // verificando o ultimo numero
                                soma2 = ((n1*11)+(n2*10)+(n3*9)+(n4*8)+(n5*7)+(n6*6)+(n7*5)+(n8*4)+(n9*3)+(primeiroverificador*2));
                                teste2 = (soma2%11);

                                if (teste2 < 2)// se teste for igual a 1 (11-1=10) e 10 nao eh unidade e a verificacao soh eh feita com unidade
                                    segundoverificador = 0;// recebe 0 por conta da unidade que nao foi encontrada e sim uma dezena
                                else
                                    if (teste2 >= 2){
                                        segundoverificador = (11-teste2);// caso contrario a subtração ocorrerá normalmente
                                    }
                                // verificando se correspondem os ultimos 2 numeros do cpf
                                if ((primeiroverificador == n10)&&(segundoverificador == n11)){
                                    printf("\n\tCPF VALIDO!!\n");
                                    verifica = 0; // verificador continua o sistema
                                    }
                                else{
                                    printf("\n\tCPF INVALIDO!!");
                                    verifica = 1; // verificador volta para o menu
                                }

                                if (verifica == 0){
                                    system("cls"); // apaga tela
                                    printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                                    printf("\t- INFORME O VALOR DO SAQUE..\n\t- (0) VOLTAR \n\t");
                                    scanf("%d", &saque);// recenbendo o saque
                                    if (saque == 0){
                                        system("cls");
                                    }

                                    while (saque<0)
                                    {
                                        system("cls");
                                        printf("\n\n\tPOR FAVOR, INFORME UM VALOR VALIDO PARA EFETUARMOS O SAQUE.\n");
                                        printf("\n\n\t-----SISTEMA BANCARIO/CLIENTE/SAQUE-----\n");
                                        printf("\t- INFORME O VALOR DO SAQUE..\n\t- (0) VOLTAR \n\t");
                                        scanf("%d",&saque); // fazendo a leitura do saque do usuario
                                    }

                                    if (saque > saldocaixa)
                                        system("cls");
                                        printf("\n\tSALDO INDISPONIVEL!");
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
                                        system("cls");
                                        saq_ced = saque;
                                        if ((saq_ced/500>0) && (vernot500>0)) // caso houver notas suficientes para serem retiradas corretamente
                                        {
                                            a500 = saque/500;
                                            if (vernot500>=a500)
                                            {
                                                saq_ced = saq_ced - (a500*500);
                                            }
                                            else{
                                                a500 = vernot500; // como esgtaram as notas de 500, as notas que haviam sairam todas.
                                                saq_ced = (saq_ced - (a500*500));

                                            }
                                        }
                                        if ((saq_ced/150>0) && (vernot150>0)) // se houver notas de 150 a mais ou igual
                                        {
                                            a150 = saq_ced/150;
                                            if (vernot150>=a150){
                                                saq_ced = saq_ced - (a150*150);
                                            }
                                            else{
                                                    a150 = vernot150; // Como as notas do caixa sao menores do que as notas que poderiam ser
                                                                // retiradas se houvesse mais, as notas retiradas fica com o mesmo valor das notas do caixa
                                                    saq_ced = (saq_ced - (a150*150));
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
                                        if (saq_ced!=0) // caso as notas do caixa nao seje zerada com as retiradas do caixa imprime mensagem
                                            printf("\n\tCEDULAS NECESSARIAS PARA SAQUE INSUFICIENTES.");
                                        else{// caso haja o numero de notas necessarias imprime as notas e atualiza o caixa
                                            if (saque>0){
                                                Sleep (1000);
                                                printf ("\r \t\t\t\t \n\n\n");
                                                system("cls");
                                                printf("\n\tSAQUE EFETUADO COM SUCESSO..");
                                                //notas de 500
                                                if (a500>0) {
                                                    printf("\n\t%d NOTA(S) - R$ 500,00",a500); // mostrando as notas que sairam
                                                    vernot500 = vernot500 - a500; // diminuindo a quantidade de notas do caixa
                                                    saldocaixa = saldocaixa - (a500*500);
                                                    totsak = totsak + (a500*500);
                                                }
                                                //notas de 150
                                                if (a150>0) {
                                                    printf("\n\t%d NOTA(S) - R$ 150,00",a150); // mostrando as notas que sairam de 150
                                                    vernot150 = vernot150 - a150; // subtraindo o quantidade de notas do caixa
                                                    saldocaixa = saldocaixa - (a150*150);
                                                    totsak = totsak + (a150*150);
                                                }
                                                //notas de 50
                                                if (a50>0){
                                                    printf("\n\t%d NOTA(S) - R$ 50,00",a50); // mostrando as notas que foram retiradas
                                                    vernot50 = vernot50 - a50; // diminuindo as notas de 50 do caixa
                                                    saldocaixa = saldocaixa - (a50*50);
                                                    totsak = totsak + (a50*50);
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
                                                // imprimindo as notas por extenso
                                                CM = saque/100000 ; // centena de milhar recebe valor do saque dividido por 100000
                                                DM = (saque - CM*100000)/10000; // dezena de milhar recebe valor do saque menos centena de milhar vezes 100000 dividido por 10000
                                                UNM = (saque - CM*100000 - DM*10000)/1000; // unidade de milhar recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 dividido por 1000
                                                CEN = (saque - CM*100000 - DM*10000 - UNM*1000)/100; // centena recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 dividido por 100
                                                DEZ = (saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100)/10; // dezena recebe daque menos centena de milha vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 dividido por 10
                                                UN = saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100 - DEZ*10; // unidade recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 menos dezena vezes 10
                                                printf("\n\t");
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
                                                    printf(" CENTO E");
                                                // imprimir valores da dezena de milhar
                                                if (DM == 9)
                                                    printf(" NOVENTA");
                                                else{
                                                    if (DM == 8)
                                                        printf (" OITENTA");
                                                    else{
                                                        if (DM == 7)
                                                            printf (" SETENTA");
                                                        else{
                                                            if (DM == 6)
                                                                printf (" SESSENTA");
                                                            else{
                                                                if (DM == 5)
                                                                    printf (" CINQUENTA");
                                                                else{
                                                                    if (DM == 4)
                                                                        printf (" QUARENTA");
                                                                    else{
                                                                        if (DM == 3)
                                                                            printf (" TRINTA");
                                                                        else{
                                                                            if (DM == 2)
                                                                                printf (" VINTE");
                                                                            else{
                                                                                if ((DM == 1) && (UNM ==0))
                                                                                    printf (" DEZ");
                                                                                else{
                                                                                    if (DM ==1)
                                                                                        if (UNM == 9)
                                                                                            printf (" DEZENOVE");
                                                                                        else{
                                                                                            if (UNM == 8)
                                                                                                printf (" DEZOITO");
                                                                                            else{
                                                                                                if (UNM == 7)
                                                                                                    printf(" DEZESSETE");
                                                                                                else{
                                                                                                    if (UNM == 6)
                                                                                                        printf (" DEZESSEIS");
                                                                                                    else{
                                                                                                        if (UNM == 5)
                                                                                                            printf (" QUINZE");
                                                                                                        else{
                                                                                                            if (UNM == 4)
                                                                                                                printf (" QUATORZE");
                                                                                                            else{
                                                                                                                if (UNM == 3)
                                                                                                                    printf (" TREZE");
                                                                                                                else{
                                                                                                                    if (UNM == 2)
                                                                                                                        printf (" DOZE");
                                                                                                                    else{
                                                                                                                        if (UNM ==1)
                                                                                                                            printf (" ONZE");

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
                                                printf(" REAIS");
                                            }
                                        }
                                    }

                                }
                        }
                }

        }
        if (menu == '2'){ // entrando no menu gerente

            menu2 = '0'; // incializacao da variavel do menu gerente
            system("cls");

            while (menu2 != '5'){ // enquanto nao digitar 5, nao saira do menu gerente
                if ((menu2 != '5') && (menu2 != '1') && (menu2 != '2') && (menu2 != '3') && (menu2 != '4')) // caso digite um numero fora
                                                                                                // da opcao possivel faz iteracao
                    system("cls");
                    printf("\t----------SISTEMA BANCARIO/GERENTE-----------\n");
                    printf("\t- 1...VALOR TOTAL SACADO                    -\n");
                    printf("\t- 2...VALOR SALDO EXISTENTE                 -\n");
                    printf("\t- 3...QUANTIDADE DE CEDULAS EXISTENTES      -\n");
                    printf("\t- 4...ABASTECER O CAIXA ELETRONICO          -\n");
                    printf("\t- 5...MENU PRINCIPAL                        -\n");
                    printf("\t---------------------------------------------");

                    printf("\n\tDIGITE A OPCAO DESEJADA..\n\t");
                    scanf("%s", &menu2);
                if (menu2 == '1'){
                    if (l == 0){
                        system("cls"); // comando apaga tela
                        printf("\n\tAINDA NAO FORAM EFETUADOS SAQUES NESTE TERMINAL..\n\n");
                    }
                    else{
                        system("cls");
                        printf("\n\tSAQUE TOTAL EFETUADO = %d \n\n",totsak); // variavel acumulativa para o saque
                    }
                }
                if (menu2 == '2'){
                    if (l == 0){
                        system("cls"); // comando apaga tela
                        printf("\n\tSALDO = 0,00. ABASTECA O CAIXA..\n\n");
                    }
                    if (l != 0){
                        system("cls"); // comando apaga tela
                        printf("\n\tSALDO = %d \n\n",saldocaixa);
                    }
                }
                if (menu2 == '3'){
                        system("cls");
                        printf("\t----------SISTEMA BANCARIO/GERENTE/CONTAGEM CEDULAS-----------\n");
                        printf("\n\tQUANTIDADE DE CEDULAS EXISTENTES\n");
                        printf("\n\t-NOTAS DE 1,00   = %d",vernot1);
                        printf("\n\t-NOTAS DE 2,00   = %d",vernot2);
                        printf("\n\t-NOTAS DE 5,00   = %d",vernot5);
                        printf("\n\t-NOTAS DE 10,00  = %d",vernot10);
                        printf("\n\t-NOTAS DE 20,00  = %d",vernot20);
                        printf("\n\t-NOTAS DE 50,00  = %d",vernot50);
                        printf("\n\t-NOTAS DE 150,00 = %d",vernot150);
                        printf("\n\t-NOTAS DE 500,00 = %d\n\n",vernot500);


                }
                if (menu2 == '4'){
                        system("cls");
                        printf("\n\n\t----------SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA---------\n");
                        printf("\t- 500...CEDULAS DE 500,00                                 -\n");
                        printf("\t- 150...CEDULAS DE 150,00                                 -\n");
                        printf("\t- 50....CEDULAS DE 50,00                                  -\n");
                        printf("\t- 20....CEDULAS DE 20,00                                  -\n");
                        printf("\t- 10....CEDULAS DE 10,00                                  -\n");
                        printf("\t- 5.....CEDULAS DE 5,00                                   -\n");
                        printf("\t- 2.....CEDULAS DE 2,00                                   -\n");
                        printf("\t- 1.....CEDULAS DE 1,00                                   -\n");
                        printf("\t- 0.....VOLTAR                                            -\n");
                        printf("\t-----------------------------------------------------------");

                        printf("\n\tDIGITE O CODIGO DA OPCAO DESEJADA..\n\t");
                        scanf("%d", &menu3);

                    switch (menu3){

                    case 1: // caso abasteça com notas de 1 real
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----MAX:12800\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota1); // lendo quantia de notas de 1


                        while ((nota1 > 12800) || (nota1 < 0)) // fazendo loop caso as notas estejam fora do intervalo
                        {
                                if ((nota1 > 12800) || (nota1 < 0)) // se realmente estiver fora
                                    system("cls"); // apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 1-----MAX:12800\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota1); // relendo a quantia de notas

                        }
                        if (nota1 == 0){ // caso digite 0 notas

                            system("cls"); // apaga tela
                        }

                        if ((nota1 > 0) && (vernot1+nota1<=12800)){ // se estiver dentro do intervalo e a soma for menor continua
                            system("cls"); // apaga tela
                            if ((vernot1<12800) && (vernot1+nota1<=12800)){// se houver notas menor que o desejado no caixa e a soma for menor continua
                                system("cls");
                                printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 1,00\n\n\t", nota1); // mostra a quantia de notas abastecidas
                                system("pause");
                                l = l+1; // variavel para liberação do saque
                                vernot1 = (nota1 + vernot1);// variavel acumulativa para as notas de 1 real
                            }
                            if (vernot1 <= 12800){
                                saldocaixa = (saldocaixa+(nota1*1)); // saldo do caixa aumentando o valor
                            }
                            menu2 = '5';
                        }
                        else{ //caso as notas ultrapassem a quantidade limitada
                            if ((nota1 > 0) && (vernot1+nota1>=12800)){
                                system("cls");
                                printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 1,00 FOI ATINGIDA, ABASTECA COM OUTROS VALORES\n."); // mensagem para o usuario
                                vernot1 = 12800;
                            }
                            menu2 = '5';
                        }
                    break;
                    case 2: // caso abasteca com notas de 2 reais
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----MAX:6400\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");// guia usuario
                        scanf("%d", &nota2); // lendo quantia de notas


                        while ((nota2 > 6400) || (nota2 < 0)) // dando loop caso nao esteja no intervalo desejado
                        {
                                if ((nota2 > 6400) || (nota2 < 0)) // se realmente nao estiver
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 2-----MAX:6400\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota2); // relendo a quantia de notas

                        }


                            if (nota2 == 0){ // caso digite nenhuma nota
                                system("cls"); // apaga tela
                            }

                            if ((nota2 > 0) && (vernot2+nota2<=6400)){ // se a quantia estiver no intervalo desejado e a soma for menor continua
                                system("cls"); // apaga tela
                                if ((nota2+vernot2<=6400) && (vernot2<6400))// se houver notas menor que o desejado no caixa e a soma for menor continua
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 2,00\n", nota2); // mostra a quantia de notas abastecidas
                                    l = l+1; // liberando o saque
                                    vernot2 = vernot2 + nota2; // variavel acumulativa para as notas de 2 reais
                                if (vernot2 <= 6400)
                                    saldocaixa = (saldocaixa+(nota2*2)); // acumulando o saldo do caixa
                            }
                            else{
                                if ((nota2 > 0) && (vernot2+nota2>=6400)){
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 2,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // mostra ao usuario
                                    vernot2 = 6400; // a quantidade serah logo estabelecida
                                }
                            }


                        break; // pausa


                    case 5: // caso queira abastecer com notas de 5 reais
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----MAX:3200\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota5); // lendo a quantia de notas


                        while ((nota5 > 3200) || (nota5 < 0))  // dando loop caso a quantia de notas de 5 nao esteja no intervalo desejado
                        {
                                if ((nota5 > 3200) || (nota5 < 0)) // se nao estiver no intervalo
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 5-----MAX:3200\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota5); // relendo a quantia de notas

                        }


                            if (nota5 == 0){ // caso digite nenhuma cedula
                                system("cls"); // apaga tela
                            }

                            if ((nota5 > 0) && (vernot5+nota5<=3200)){ // se a quantia estiver no intervalo desejado e a soma for menor continua
                                system("cls"); // apaga tela
                                if ((vernot5<3200) && (vernot5+nota5<=3200))// se houver notas menor que o desejado no caixa e a soma for menor continua
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 5,00\n", nota5); // mostra a quantia abastecida
                                    l = l+1; // liberando o saque
                                    vernot5 = vernot5 + nota5; // acumulando as notas de 5
                                if (vernot5 <= 3200)
                                    saldocaixa = (saldocaixa+(nota5*5)); // acumulando o saldo do caixa
                            }
                            else{
                                if ((nota5 > 0) && (vernot5+nota5>=3200)){
                                    system("cls");
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 5,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // aviso ao usuario
                                    vernot5 = 3200; // implementando o maximo valor de notas de 5
                                }
                            }


                        break; // pause


                    case 10: // caso queira abastecer com notas de 10
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----MAX:1600\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota10); // lendo a quantia de notas


                        while ((nota10 > 1600) || (nota10 < 0)) // dando loop caso a quantia nao esteja no intervalo desejado
                        {
                                if ((nota10 > 1600) || (nota10 < 0)) // se as notas nao estiverem no intervalo
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 10-----MAX:1600\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota10);// relendo a quantia de notas

                        }


                            if (nota10 == 0){ // caso o usuario digite nenhuma nota
                                system("cls"); // apaga tela
                            }

                            if ((nota10 > 0) && (nota10+vernot10<=1600)){ // se a quantia estiver no intervalo desejado
                                                                                            // e a soma nao ultrapasse o valor
                                system("cls"); // apaga tela
                                if ((vernot10<1600) && (nota10+vernot10<=1600)) // se houver notas menor que o desejado no caixa e a soma for menor continua
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 10,00\n", nota10); // mostra as notas abastecidas
                                    l = l+1; // liberando o saque
                                    vernot10 = vernot10 + nota10; // acumulando as notas de 10 reais
                                if (vernot10 <= 1600)
                                    saldocaixa = (saldocaixa+(nota10*10)); // acumulando o saldo do caixa
                            }
                            else{
                                if ((nota10 > 0) && (nota10+vernot10>=1600)){
                                    system("cls");
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 10,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // aviso ao usuario
                                    vernot10 = 1600; // ocorre a implementacao do limite na variavel
                                }
                            }

                        break; // pause

                    case 20: // caso abasteca com notas de 20
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----MAX:800\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t");// guia usuario
                        scanf("%d", &nota20); // lendo quantia de notas


                        while ((nota20 > 800) || (nota20 < 0)) // dando loop caso a quantia de notas nao esteja no intervalo desejado
                        {
                                if ((nota20 > 800) || (nota20 < 0)) // se realmente nao estiver
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 20-----MAX:800\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota20); // relendo a quantia de notas

                        }


                            if (nota20 == 0){ // caso a quantia seja 0
                                system("cls");// apaga tela
                            }

                            if ((nota20 > 0) && (vernot20+nota20<=800)){ // se a quantia estiver no intervalo desejado
                                system("cls"); // apaga tela
                                if ((vernot20<800) && (vernot20+nota20<=800))
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 20,00\n", nota20); // mostra ao usuario a quantia abastecida
                                    l = l+1; // liberando o saque
                                    vernot20 = vernot20 + nota20; // acumulando as notas de 20
                                if (vernot20 <= 800)
                                    saldocaixa = (saldocaixa+(nota20*20)); // acumulando o saldo do caixa
                            }
                            else{
                                if ((nota20 > 0) && (vernot20+nota20>=800)){
                                    system("cls");
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 20,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // aviso ao usuario
                                    vernot20 = 800; // implementação do limite ocorre
                                }
                            }


                        break; // pause

                    case 50: // caso queira abastecer com notas de 50
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----MAX:400\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota50); // lendo as notas de 50


                        while ((nota50 > 400) || (nota50 < 0)) // caso a quantia de notas nao esteja no intervalo desejado
                        {
                                if ((nota50 > 400) || (nota50 < 0)) // se nao estiver no intervalo
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // guia usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 50-----MAX:400\n"); // guia usuario
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota50); // relendo a quantia de notas de 50

                        }


                            if (nota50 == 0){ // caso o usuario digite nenhuma nota
                                system("cls"); // apaga tela
                            }

                            if ((nota50 > 0) && (vernot50+nota50<=400)){ // se a quantia de notas estiver no intervalo desejado
                                system("cls"); // apaga tela
                                if ((vernot50<400) && (vernot50+nota50<=400))
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 50,00\n", nota50);// mostra a quantidade de notas abastecidas
                                    l = l+1; // liberando o saque
                                    vernot50 = vernot50 + nota50; // acumulando as notas de 50
                                if (vernot50 <= 400)
                                    saldocaixa = (saldocaixa+(nota50*50)); // acumulando o saldo do caixa
                            }
                            else{
                                if ((nota50 > 0) && (vernot50+nota50>=400)){
                                    system("cls");
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 50,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // aviso ao usuario
                                    vernot50 = 400; // implementação do limite de notas
                                }
                            }


                        break; // pause

                    case 150:
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 150-----MAX:200\n");// guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota150); // lendo a quantia


                        while ((nota150 > 200) || (nota150 < 0)) // fazendo loop caso as notas nao estejam no padrao
                        {
                                if ((nota150 > 200) || (nota150 < 0)) // caso as notas nao esteja conforme o padrao
                                    system("cls");// apaga tela
                                    printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                    printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 150-----MAX:200\n"); // guia usuairio
                                    printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                    scanf("%d", &nota150); // relendo a quantia de notas

                        }


                            if (nota150 == 0){ // se digitar 0 notas
                                system("cls"); // apaga tela
                            }

                            if ((nota150 > 0) && (vernot150+nota150<=200)){ // caso a quantia esteja no intervalo desejado
                                system("cls"); // apaga tela
                                if ((vernot150<200) && (vernot150+nota150<=200))
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 150,00\n", nota150); // msg ao usuario de abastecimento
                                    l = l+1; // liberando saque
                                    vernot150 = vernot150 + nota150; // acumulando notas de 150
                                if (vernot150 <= 200)
                                    saldocaixa = (saldocaixa+(nota150*150)); // acumulando quantia de dinheiro no caixa
                            }
                            else{
                                if ((nota150 > 0) && (vernot150+nota150>=200)){
                                    system("cls");
                                    printf("\n\tQUANTIDADE MAXIMA DE NOTAS DE R$ 150,00 FOI ATINGIDA. ABASTECA COM OUTROS VALORES\n"); // aviso ao usuario
                                    vernot150 = 200; // implementando a quantia de notas direta
                                }
                            }
                        break; // pause

                    case 500: // caso escolha 500
                        system("cls"); // apaga tela
                        printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 500-----MAX:100\n"); // guia usuario
                        printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                        scanf("%d", &nota500); // lendo a quantia de notas


                        while ((nota500 > 100) || (nota500 < 0)) // caso a quantia de notas nao esteja no padrao da loop
                        {
                                if ((nota500 > 100) || (nota500 < 0)) // caso a quantia de notas nao esteja correspondendo ao padrao
                                system("cls");// apaga tela
                                printf("\n\tQUANTIDADE NAO SUPORTADA... OBSERVE O NUMERO MAXIMO DE CEDULAS.\n"); // aviso ao usuario
                                printf("\n\n\t-----SISTEMA BANCARIO/GERENTE/ABASTECER CAIXA/CEDULAS DE 500-----MAX:100\n"); // guia usuario
                                printf("\t- INFORME A QUANTIDADE DE CEDULAS DESEJA DEPOSITAR..\n\t- (0) VOLTAR \n\t"); // guia usuario
                                scanf("%d", &nota500); // relendo a quantia de notas

                        }


                            if (nota500 == 0){ // caso digite nenhuma nota
                                system("cls"); // apaga tela
                            }

                            if ((nota500 > 0) && (vernot500+nota500<=100)){ // caso as notas esteja no intervalo desejado, nem valor negativo e nem extrapolando o limite
                                system("cls"); // apaga tela
                                if ((vernot500<100) && (vernot500+nota500<=100))
                                    printf("\n\n\tO CAIXA FOI ABASTECIDO COM %d NOTAS DE 500,00\n", nota500); // mostra ao usuario as notas abastecidas
                                    l = l+1; // liberando o saque com a variavel
                                    vernot500 = vernot500 + nota500; // acumulando notas de 500
                                if (vernot500 <= 100)
                                    saldocaixa = (saldocaixa+(nota500*500)); // acumulando o caixa
                            }
                            else{
                                if ((nota500 > 0) && (vernot500+nota500>100)){
                                    system("cls");
                                    if (vernot500<100){
                                        dif = (100 - vernot500);
                                        printf("\n\t%d",dif);
                                        vernot500 = vernot500 + dif;
                                        printf("\n\t%d",vernot500);
                                        saldocaixa = saldocaixa + (dif*500);
                                        //printf("\n\t%d",totsak);
                                        system("pause");
                                    }
                                    printf("\tA QUANTIDADE MAXIMA DE NOTAS DE R$ 500,00 FOI ATINGIDA.\n"); // mostra ao usuario
                                    //vernot500 = 100; // o limite serah logo implementado
                                }
                            }


                        break;

                        default:

                        printf("\n\tOPCAO INEXISTENTE! TENTE OUTRA VEZ..\n");
                        system("cls");

                        break;

                    }
                }

            }
            system("cls"); // comando apaga tela
        }

    }
    if (menu == '3'){
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
}
