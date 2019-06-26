#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TAM 50

char opcionais[][TAM]={ {"4.portas"}, {"cambio.automatico"}, {"vidros.eletricos"}, {"abs"}, {"air.bag"}, {"ar.condicionado"},
    {"banco.couro"}, {"sensor.estacionamento"}};

struct CARRO {

    char placa[9]; //AAA-1234
    char modelo[TAM]; //gol, celta, palio, ...
    char fabricante[TAM]; //chevrolet, fiat, ...
    int ano_fabricacao; //1980 à 2016
    int ano_modelo; //1980 à 2017
    char combustivel[TAM]; //alcool, gasolina, flex, diesel
    char cor[TAM]; //branca, prata, preta
    int opcional[8]; //ver matriz opcionais
    float preco_compra;

};

//objetivo:escolhe dentre as letras do alfabeto ('a'..'z') uma letra aleatoriamente
//parametros: nenhum
//retorno:a letra do alfabeto
char geraAlfabeto() {
    int i;
    char letras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    i=rand()%26;
    return(letras[i]-32);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: GERAR AS LETRAS DA PLACA
//PARAMETRO: A STRUCT DE CARRO POR REFERENCIA
//-----------------------------------------------------------------------------------------
void gera_letra_placa (struct CARRO *c)
{
    int i;
    srand(time(NULL));

    for(i=0;i<3;i++)
    {
        c->placa[i] = geraAlfabeto();
    }
    c->placa[3] = '-';
}

//objetivo:escolhe dentre os numeros ('0'..'9') uma numero aleatoriamente
//parametros: nenhum
//retorno:o numero
char geraNumero() {
    int i;
    char numeros[] = { '0','1','2','3','4','5','6','7','8','9'};

    i=rand()%9;
    return(numeros[i]);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: GERAR UMA PLACA
//PARAMETRO: A STRUCT DE CARRO POR REFERENCIA
//-----------------------------------------------------------------------------------------
void gera_numero_placa (struct CARRO *c)
{
    int i;

    srand(time(NULL));
    for (i=0;i<4;i++)
    {
        c->placa[i+4] = geraNumero();
    }
    c->placa[8] = '\0';
    //AAA-1234
}
//-----------------------------------------------------------------------------------------
//OBJETIVO: VERIFICA SE HÁ UMA PLACA COM OS MESMOS CARACTERES GERADOS
//RETORNO: 0 CASO HAJA UMA PLACA NO ARQUIVO, E 1 CASO NÃO HAJA
//PARAMETRO: A STRUCT DE CARRO E O ARQUIVO COM AS PLACAS CADASTRADAS
//-----------------------------------------------------------------------------------------
int verifica_placa (struct CARRO c, FILE *p)
{
    struct CARRO k;
    //int q;

    //q = ftell(p);
    //printf("%d",q);

    do{
        if (fread(&k,sizeof(struct CARRO),1,p) == 1){
            //printf("aksdfhçaodh");
            //system("pause");
            if(strcmp(k.placa,c.placa) == 0)
            {
                //printf("PLACA ! ! ! %s",k.placa);
                return 0;
            }
        }
    }while(!(feof(p)));

    return 1;
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: GERAR UMA PLACA
//PARAMETRO: A STRUCT DE CARRO POR REFERENCIA E O ARQUIVO
//-----------------------------------------------------------------------------------------
void gera_placa_igual (struct CARRO *c, FILE *p)
{
    int i=0;
    do{
        gera_letra_placa(c);
        gera_numero_placa(c);
        i++;
    }while(verifica_placa(*c,p)!=0);
    system("cls");
    printf("\nTARFAO? A PLACA GEROU! ! TENTOU %d VEZES\n\n",i);

}

//------------------------------------------------------------------------------------
//OBEJTIVO: MOSTRAR O MENU DAS VENDAS
//PARAMETRO NENHUM
//RETORNO: A OPCAO QUE O USUARIO DESEJA
//------------------------------------------------------------------------------------
int mostra_menu_vendas()
{
    int op;

    printf("\t1 - Inserir uma venda\n");
    printf("\t2 - Excluir uma venda\n");
    printf("\t3 - Listar os carros vendidos de um determinado fabricante, ordenados crescentemente pelo modelo (as seguintes informacoes devem aparecer: modelo, placa, ano fabricacao e nome cliente ) \n");
    printf("\t4 - Listar os carros vendidos de um determinado modelo, ordenados crescentemente pelo ano de fabricacao (asseguintes informacoes devem aparecer: ano de fabricacao, placa e nome cliente )  \n");
    printf("\t5 - Informar a quantidade de carros vendidos com o valor totalizado dos precos vendidos\n");
    printf("\t6 - Informar o lucro total das vendas\n\t");
    scanf("%d",&op);
    return(op);
}

int main()
{
    FILE *pfilevenda;
    int op;
    struct CARRO conj;

    do{
        op = mostra_menu_vendas();
        //inserir venda
        if(op == 1)
        {
            if ((pfilevenda = fopen("geracarro.dat","r+b")) == NULL)
            {
                system("cls");
                printf("\tNAO POSSUI NENHUM CARRO PARA VENDER CARROS! !\n\n");
            }
            else
            {
                gera_placa_igual(&conj,pfilevenda);
            }
        }
        //exclui venda
        if(op == 2)
        {

        }
        //mostra vendidos por um fabricante ordem crescente
        if(op == 3)
        {

        }
        //mostra vendidos de um modelo ordem crescente
        if(op == 4)
        {

        }
        //informa a quantidade de carros vendidos e o valor total
        if(op == 5)
        {

        }
        //informa o lucro
        if(op == 6)
        {

        }
    }while(op!=7);
}
