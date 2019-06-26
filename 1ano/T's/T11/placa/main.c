#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 50

struct CARRO
{
    char placa[TAM];
}pl;

FILE *AbreArq ()
{
    FILE *p;
    int i=0;

    if ((p = fopen("geraplaca.dat","r+b")) == NULL)
    {
        i=i+1;
        if ((p = fopen("geraplaca.dat","w+b"))== NULL)
        {
            printf("ERRO");
            exit(100);
        }
    }
    if(i>0)
    {
        printf("Arquivo criado!\n");
    }
    else
    {
        printf("Arquivo Aberto!\n");
    }
    return(p);

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
            //printf("aksdfhçaodh");
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
//PARAMETRO: A STRUCT DE CARRO POR REFERENCIA
//-----------------------------------------------------------------------------------------
void gera_placa (struct CARRO *c)
{
    gera_letra_placa(&*c);
    gera_numero_placa(&*c);

}


void mostraplaca(FILE *p)
{
    struct CARRO k;

    system("cls");
    fseek(p,0,SEEK_SET);
    do
    {
        if (fread(&k,sizeof(struct CARRO),1,p) == 1){
            printf("%s\n",k.placa);
        }
    }while(!feof(p));
}


int main()
{
    struct CARRO car;
    FILE *placa;
    int op;

    do{
        //printf("\n%d  %d\n",ftell(placa),sizeof(struct CARRO));
        printf("1 - GERA PLACA\n");
        printf("2 - MOSTRAR PLACAS\n");
        printf("3 - SAIR\n");
        scanf("%d",&op);
        if (op == 1){
            placa = AbreArq();
            gera_placa(&car);
            system("cls");

            if (verifica_placa(car,placa)==1)
            {
                fseek(placa,0,SEEK_END);
                if (fwrite(&car,sizeof(struct CARRO),1,placa) == 1)
                {
                    printf("GRAVAÇÃO FEITA COM SUCESSO\n");
                }
                puts(car.placa);
            }
            fclose(placa);
        }
        if (op==2)
        {
            if ((placa = fopen("geraplaca.dat","rb")) == NULL)
            {
                printf("nn há cadastro.");
            }
            else{
                mostraplaca(placa);
            }
            fclose(placa);
        }
    }while(op!=3);
    return 0;
}
