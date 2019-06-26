#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
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

//-------------------------------------------------------------------------------------
//OBJETIVO: ABRIR UM ARQUIVO OU CRIAR UM ARQUIVO
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------
FILE *AbreArq ()
{
    FILE *p;

    if ((p = fopen("geracarro.dat","r+b")) == NULL)
    {
        if ((p = fopen("geracarro.dat","w+b"))== NULL)
        {
            printf("ERRO");
            exit(100);
        }
    }

}


//------------------------------------------------------------------------------------
//OBJETIVO: GERAR O MODELO DO CARR
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_modelo (struct CARRO *c)
{
    //MODELOS E FABRICANTES DE CARROS
    //                      0             1          2          3         4           5           6
    char fabri[][TAM] = {{"Chevrolet"}, {"Fiat"}, {"Ford"}, {"Honda"}, {"Renault"}, {"Toyota"}, {"Volkswagen"}};
    char chev[][TAM] = {{"Veraneio"}, {"Opala"}, {"Onix"}, {"Prisma"}, {"Celta"}, {"Astra "}, {"Corsa "},
    {"Vectra"}, {"Kadett "}, {"Monza"}};//10

    char fiat[][TAM] = {{"147"}, {"Fiorino"}, {"Uno"}, {"Uno Mille"}, {"Palio"}, {"Siena"}, {"Punto"}, {"Doblò"}};//8
    char ford[][TAM] = {{"Maverick"}, {"Pampa"}, {"Royale"}, {"Fiesta"}, {"Ecosport"}};//5
    char honda[][TAM] = {{"Civic"}, {"City"}, {"Fit"}, {"HR-V "}};//4
    char renault[][TAM] = {{"Clio Sedan"}, {"Mégane Sedan"}, {"Logan"}, {"Sandero"}, {"Duster"}};//5
    char toyo[][TAM] = {{"Corolla"}, {"Hilux"}, {"Etios"}};//3
    char volks[][TAM] = {{"Brasília"}, {"Gol"}, {"Voyage"}, {"Parati"}, {"Saveiro"}, {"Santana"}, {"Golf"},
    {"Polo"}, {"Fox"}, {"Crossfox"}, {"Up"}};//11

    int cfab; //recebe o sorteio do fabricante que vai ser o carro
    int cmod; //recebe o sorteio do modelo que vai ser o carro

    srand(time(NULL));srand(time(NULL));
    cfab = rand()%7;
    strcpy(c->fabricante,fabri[cfab]);

    if (cfab == 0)//tipo chevrolet
    {
        cmod = rand ()%10;
        strcpy(c->modelo,chev[cmod]);
    }
    else
    {
        if (cfab == 1)//tipo Fiat
        {
            cmod = rand ()%8;
            strcpy(c->modelo,fiat[cmod]);
        }
        else
        {
            if (cfab == 2)//tipo ford
            {
                cmod = rand ()%5;
                strcpy(c->modelo,ford[cmod]);
            }
            else
            {
                if (cfab == 3)//tipo honda
                {
                    cmod = rand ()%4;
                    strcpy(c->modelo,honda[cmod]);
                }
                else
                {
                    if (cfab == 4)//tipo renault
                    {
                        cmod = rand ()%5;
                        strcpy(c->modelo,renault[cmod]);
                    }
                    else
                    {
                        if (cfab == 5)//tipo toyota
                        {
                            cmod = rand ()%3;
                            strcpy(c->modelo,toyo[cmod]);
                        }
                        else
                        {
                            if (cfab == 6)//tipo volkswagem
                            {
                                cmod = rand ()%11;
                                strcpy(c->modelo,volks[cmod]);
                            }
                        }
                    }
                }
            }
        }
    }


}

//-------------------------------------------------------------------------------------
//OBJETIVO: GERAR O TIPO DE COMBUSTIVEL DO CARRO
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_combustivel (struct CARRO *c)
{
    char combus[][TAM] = {{"Alcool"}, {"Gasolina"}, {"Diesel"}, {"Flex"}};
    int cbus;

    cbus = rand() % 3; //pega uma das cores do combus
    strcpy (c->combustivel,combus[cbus]);
}

//-------------------------------------------------------------------------------------
//OBJETIVO: GERAR A COR DO CARRO
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_cor (struct CARRO *c)
{
    char cor[][TAM] = {{"Preto"}, {"Amarelo"}, {"Azul"}, {"Branco"}, {"Prata"}};
    int cc; //recebe uma posicao sorteada da cor na string cor

    cc = rand ()% 5;
    strcpy (c->cor,cor[cc]);

}

//-------------------------------------------------------------------------------------
//OBJETIVO: GERAR OS ADCIONAIS DO CARRO
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_adicionais (struct CARRO *c)
{
    int k;
    int i;

    for (i=0;i<3;i++)
    {
        k = rand()%8;
        while(k==c->opcional[0] || k==c->opcional[1] || k==c->opcional[2])
            k = rand()%8;
        c->opcional[i] = k;
    }


}

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
    int q;

    //q = ftell(p);
    //printf("%d",q);

    do{
        if (fread(&k,sizeof(struct CARRO),1,p) == 1){
            printf("aksdfhçaodh");
            system("pause");
            if(strcmp(k.placa,c.placa) == 0)
            {
                printf("PLACA ! ! ! %s",k.placa);
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
void gera_placa (struct CARRO *c, FILE *p)
{
    do{
        gera_letra_placa(c);
        gera_numero_placa(c);
    }while(verifica_placa(*c,p)!=1);

}

//-------------------------------------------------------------------------------------
//OBJETIVO: GERAR OS DADOS DO CARRO
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_carro (struct CARRO *c, FILE *p)
{
    gera_modelo(c);
    c->ano_fabricacao = 1980 + rand ()% (2016-1980);
    c->ano_modelo = c->ano_fabricacao + rand()% (2017 - c->ano_fabricacao);
    gera_combustivel(c);
    gera_cor(c);
    gera_adicionais(c);
    gera_placa(c,p);
    c->preco_compra = 10000 + rand ()% (30000-10000);
    //printf("\n%d\n",c->ano_fabricacao);


}

//-------------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR OS CARROS
//PARAMETRO: O REGISTRO DO CARRO QUE SERÁ MOSTRADO
//-------------------------------------------------------------------------------------
void mostracarro (struct CARRO car)
{
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("\tModelo : %s\n\tFabricante : %s\n\tAno de Fabricação : %d\n\tAno do modelo: %d \tTipo : %s\n\tCor : %s",car.modelo,car.fabricante,car.ano_fabricacao,car.ano_modelo,car.combustivel,car.cor);
    printf("\n\tADICIONAIS : %s\n\t\t%s\n\t\t%s\n",opcionais[car.opcional[0]],opcionais[car.opcional[1]],opcionais[car.opcional[2]]);
    printf("\n\tPlaca : %s\n\t Preco de compra : %.2f\n",car.placa,car.preco_compra);
    printf("-------------------------------------------------------------------------------------\n");


}

//-------------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR OS CARROS EM ORDEM DE FABRICANTE E MODELO
//PARAMETRO: O VETOR COM OS REGISTROS DOS CARROS ORDENADOS, E q QUE É A QUANTIDADE
//-------------------------------------------------------------------------------------
void mostraordenado (struct CARRO c[], int q)
{
    int i;

    for (i=0;i<q;i++)
    {
        printf("\n-------------------------------------------------------------------------------------\n");
        printf("\tFabricante : %s\n\tMODELO : %s\n\t%d\n",c[i].fabricante,c[i].modelo,c[i].ano_fabricacao);
        printf("-------------------------------------------------------------------------------------\n");
    }
}

//-------------------------------------------------------------------------------------
//OBJETIVO: MUDAR A POSICAO DO CARRO NO VETOR DE REGISTRO
//PARAMETRO: O CONJUNTO DE REGISTROS POR REFERENCIA,  x = POSICAO DO
//           REGISTRO QUE É MAIOR DO QUE AQUELE QUE ESTÁ NA POSICAO y
//-------------------------------------------------------------------------------------
void trocar (struct CARRO *c, int x, int y) {

		struct CARRO aux;

		aux = c[x];
		c[x] = c[y];
		c[y] = aux;

}

//-------------------------------------------------------------------------------------
//OBJETIVO: ORDENAR OS REGISTROS
//PARAMETRO: UM CONJUNTO DE REGISTROS, E A SUA QUANTIDADE
//-------------------------------------------------------------------------------------
void ordena(struct CARRO c[], int q, int tipo)
{
    int i,j;

    for (i=q-1;i>0;i--)
    {
        for(j=0;j<i;j++)
        {
            if (tipo==1){
                if(strcmp(c[j].fabricante,c[j+1].fabricante)>0)
                {
                    trocar(c,j,j+1);
                }
            }
            else
            {
                if (tipo==2)
                {
                    if(c[j].ano_fabricacao>c[j+1].ano_fabricacao)
                    {
                        trocar(c,j,j+1);
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------
//OBJETIVO: FAZER TODO O PROCESSO DE ORDENAÇÃO DOS CARROS
//PARAMETRO: UM INTEIRO QUE IRA REPRESENTAR QUAL A ORDENAÇÃO SERA FEITA
//          1 - FABRICANTE E MODELO
//          2 - ANO DE FABRICACAO
//-------------------------------------------------------------------------------------
void ordena_carro (int tipo)
{
    struct CARRO c;
    struct CARRO sordena[200];
    //struct CARRO ordenado[200];
    int cont=0;
    FILE *arq;

    if ((arq=fopen("geracarro.dat","rb")) == NULL )
    {
        printf("\nSem carros adicionados!\n");
    }
    else
    {
        do{
            if (fread(&c,sizeof(struct CARRO),1,arq)==1)
            {
                sordena[cont] = c;
                cont++;
            }
        }while(!feof(arq));
    }
    ordena(sordena,cont,tipo);
    mostraordenado(sordena,cont);

}

int main()
{
    struct CARRO car;
    int i;
    int op;
    FILE *pfilecarro;
    setlocale(LC_ALL,"");

    printf("\n");
    system("color a");

    do{
        //printf("\n%d  %d\n",ftell(placa),sizeof(struct CARRO));
        printf("\n\t1 - GERA CARRO\n");
        printf("\t2 - EXCLUIR UM CARRO\n");
        printf("\t3 - MOSTRA CARRO DISPONÍVEL PARA VENDA ORDENADO F-M\n");
        printf("\t4 - MOSTRA CARRO DISPONIVEL PARA VENDA COM UM OU MAIS ADICIONAIS\n");
        printf("\t5 - MOSTRA CARRO DISPONIVEL PARA VENDA POR FAIXA DE ANO DE FABRICACAO\n");
        printf("\t6 - SAIR\n\t");
        scanf("%d",&op);
        if (op == 1){
            pfilecarro = AbreArq();
            gera_carro(&car,pfilecarro);
            system("cls");
            fseek(pfilecarro,0,SEEK_END);
            if (fwrite(&car,sizeof(struct CARRO),1,pfilecarro) == 1)
            {
                printf("GRAVAÇÃO FEITA COM SUCESSO\n");
            }
            mostracarro(car);
            fclose(pfilecarro);
        }
        //esclui um carro
        if (op==2)
        {

        }
        //mostra ordenado f-m
        if(op==3)
        {
            system("cls");
            //printf("Arquivo removido!\n");
            //remove(pfilecarro);
            ordena_carro(1);
        }
        //mostra com um ou mais opcionais
        if (op==4)
        {
            if ((pfilecarro = fopen("geracarro.dat","rb")) == NULL)
            {
                printf("nn há cadastro.");
            }
            else{
                 printf("%d %d\n",ftell(pfilecarro),sizeof(struct CARRO));
                do{
                    if (fread(&car,sizeof(struct CARRO),1,pfilecarro)==1)
                    {
                        mostracarro(car);
                    }
                }while(!feof(pfilecarro));
                printf("%d %d\n",ftell(pfilecarro),sizeof(struct CARRO));
            }
            fclose(pfilecarro);
        }
        //mostra por faixa de ano de fabricacao
        if (op==5)
        {
            ordena_carro(2);
        }
    }while(op!=6);
    return 0;
}
