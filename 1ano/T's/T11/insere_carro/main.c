#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define TAM 50

/*
    ALUNOS: RAFAELA DONASSOLO, RONALDO TAFAREL E ZENALVO JR
*/


//MOSTRANDO AS FUNÇÕES
void executa_menu_carro ();
void gera_carro ();
void mostracarro();
void ordena_carro();
void exclui_carro();
void insere_pontuacao_cpf();
void exclui_cliente();
void cadastro();
void ordena_renda_e_nome();
void ordenar_nome();
void mostra_nome();
void mostra_cliente();
void mostracarro_exc();
void trocar();

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

struct ENDERECO {
    char rua[TAM];
    int numero;
    char bairro[TAM];
    char cidade[TAM];
    char estado[3];
    char cep[11]; //99.999-999
};


struct TELEFONE {
    char telefone[14]; //99 99999-9999
};


struct CLIENTE {
    char nome[TAM];
    char cpf[15]; //999.999.999-99
    struct ENDERECO endereco;
    struct TELEFONE residencial;
    struct TELEFONE celular[5];
    float renda_mensal;
};


struct DATA {
    int dia, mes, ano;
};

struct VENDA_CARRO {
    char placa_car[9];
    char cpf_cli[15];
    float preco_venda;
    struct DATA data_venda;
    char fabricante[TAM];
    char modelo[TAM];
    char nome[TAM];
    int ano_fabricacao;
};


//-------------------------------------------------------------------------------------
//OBJETIVO: ABRIR UM ARQUIVO OU CRIAR UM ARQUIVO
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------
FILE *AbreArqca ()
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

//-------------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O MENO CARRO PARA O CLIENTE
//PARAMETRO: NENHUM
//RETORNO: A OPÇÃO DIGITADA
//-------------------------------------------------------------------------------------
char menu_carro ()
{
        char op;

        printf("\n\t1 - CARRO\n");
        printf("\t\ta. - GERA CARRO\n");
        printf("\t\tb. - EXCLUIR UM CARRO\n");
        printf("\t\tc. - MOSTRA CARRO DISPONÍVEL PARA VENDA ORDENADO F-M\n");
        printf("\t\td. - MOSTRA CARRO DISPONIVEL PARA VENDA COM UM OU MAIS ADICIONAIS\n");
        printf("\t\te. - MOSTRA CARRO DISPONIVEL PARA VENDA POR FAIXA DE ANO DE FABRICACAO\n");
        printf("\t\tf. - SAIR\n\t");
        fflush(stdin);
        scanf("%c",&op);
        return op;
}


//---------------------------------------------------------------------------------
//OBJETIVO: EXECUTAR O MENU DO CARRO
//PARAMETRO: NENHUM
//---------------------------------------------------------------------------------
void executa_menu_carro ()
{

    struct CARRO car;
    int i;
    char op;
    FILE *pfilecarro;

    do{
        //printf("\n%d  %d\n",ftell(placa),sizeof(struct CARRO));
        op = menu_carro();
        if (op == 'a'){
            pfilecarro = AbreArqca();
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
        if (op=='b')
        {
            system("cls");
            exclui_carro();
        }
        //mostra ordenado f-m
        if(op=='c')
        {
            system("cls");
            ordena_carro(1,"geracarro.dat","rb");
        }
        //mostra com um ou mais opcionais
        if (op=='d')
        {
            if ((pfilecarro = fopen("geracarro.dat","rb")) == NULL)
            {
                system("cls");
                printf("\tNÃO HÁ CARROS DISPONIVEIS! !");
            }
            else{
                fseek(pfilecarro,0,SEEK_END);
                if (ftell(pfilecarro)>0){
                    fseek(pfilecarro,0,SEEK_SET);
                    system("cls");
                    do{
                        if (fread(&car,sizeof(struct CARRO),1,pfilecarro)==1)
                        {
                            mostracarro(car);
                        }
                    }while(!feof(pfilecarro));
                    fclose(pfilecarro);
                }
                else{
                    system("cls");
                    printf("\tNÃO HÁ CARROS DISPONIVEIS! !");
                    fclose(pfilecarro);
                }
            }
        }
        //mostra por faixa de ano de fabricacao
        if (op=='e')
        {
            system("cls");
            ordena_carro(2,"geracarro.dat","rb");
        }
    }while(op!='f');
}

//------------------------------------------------------------------------------------
//OBJETIVO: GERAR O MODELO DO CARR
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_modelo (struct CARRO *c)
{
    //MODELOS E FABRICANTES DE CARROS
    //                      0             1          2          3         4           5           6
    char fabri[][TAM] = {{"CHEVROLET"}, {"FIAT"}, {"FORD"}, {"HONDA"}, {"RENAULT"}, {"TOYOTA"}, {"VOLKSWAGEN"}};
    char chev[][TAM] = {{"VERANEIO"}, {"OPALA"}, {"ONIX"}, {"PRISMA"}, {"CELTA"}, {"ASTRA "}, {"CORSA "},
    {"VECTRA"}, {"KADETT "}, {"MONZA"}};//10

    char fiat[][TAM] = {{"147"}, {"FIORINO"}, {"UNO"}, {"UNO MILLE"}, {"PALIO"}, {"SIENA"}, {"PUNTO"}, {"DOBLÒ"}};//8
    char ford[][TAM] = {{"MAVERICK"}, {"PAMPA"}, {"ROYALE"}, {"FIESTA"}, {"ECOSPORT"}};//5
    char honda[][TAM] = {{"CIVIC"}, {"CITY"}, {"FIT"}, {"HR-V "}};//4
    char renault[][TAM] = {{"CLIO SEDAN"}, {"MÉGANE SEDAN"}, {"LOGAN"}, {"SANDERO"}, {"DUSTER"}};//5
    char toyo[][TAM] = {{"COROLLA"}, {"HILUX"}, {"ETIOS"}};//3
    char volks[][TAM] = {{"BRASÍLIA"}, {"GOL"}, {"VOYAGE"}, {"PARATI"}, {"SAVEIRO"}, {"SANTANA"}, {"GOLF"},
    {"POLO"}, {"FOX"}, {"CROSSFOX"}, {"UP"}};//11

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
    int s;
    int o;

    s = rand()%8 + 1;
    for (i=0;i<s;i++)
    {
        do{
            k = rand()%8 + 1;
            o = 0;
            for (int a=0;a<i;a++)
            {
                if (c->opcional[a]==k)
                {
                    //k = rand()%8 + 1;
                    o = 1;
                }
            }
        }while(o!=0);
        c->opcional[i] = k;
    }
        /*while(k==c->opcional[0] || k==c->opcional[1] || k==c->opcional[2])
            k = rand()%8;
        c->opcional[i] = k;*/
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
    struct VENDA_CARRO t;
    FILE *s;

    //q = ftell(p);
    //printf("%d",q);
    //verifica se há um carro com essa placa nos disponiveis
    fseek(p,0,SEEK_SET);
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

    //abre o arquivo de vendas para ver se ha um carro vendido
    //com a mesma placa gerada
    if ((s = fopen("vendacarro.dat","rb")) == NULL)
    {
        return 1;
    }
    do{
        if (fread(&t,sizeof(struct VENDA_CARRO),1,s) == 1){
            //printf("aksdfhçaodh");
            //system("pause");
            if(strcmp(t.placa_car,c.placa) == 0)
            {
                //printf("PLACA ! ! ! %s",k.placa);
                return 0;
            }
        }
    }while(!(feof(s)));

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

void inicializa_adc (struct CARRO *c)
{
    struct CARRO k;

    for (int i=0;i<8;i++)
    {
        k.opcional[i] = 0;
    }
}

//-------------------------------------------------------------------------------------
//OBJETIVO: GERAR OS DADOS DO CARRO
//PARAMETRO: A STRUCT DO CARRO
//-------------------------------------------------------------------------------------
void gera_carro (struct CARRO *c, FILE *p)
{
    int ver;

    inicializa_adc(c);
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

//-----------------------------------------------------------------------------------------
//OBJETIVO: GERAR UMA PLACA
//PARAMETRO: O ARQUIVO COM CARROS E UM REGISTRO
//RETORNO: A POSICAO DO CARRO QUE FOI SORTEADA
//-----------------------------------------------------------------------------------------
int gera_placa_igual_venda(FILE *p, struct CARRO *l)
{
    int q;//recebe o numero de registros
    int q1;//sorteia um registro

    fseek(p,0,SEEK_END);
    q = ftell(p)/sizeof(struct CARRO);
    srand(time(NULL));
    q1 = rand() % q;
    fseek(p,sizeof(struct CARRO)*q1,SEEK_SET);
    if (fread(l,sizeof(struct CARRO),1,p)==1)
    {
        return(q1);
    }

}

//-----------------------------------------------------------------------------------------
//OBJETIVO: PASSAR TODOS OS ARQUIVOS PARA UM VETOR
//PARAMETRO: ARQUIVO DE CARROS E UM CONJUNTO DE REGISTROS
//RETORNO: A QUANTIDADE DE CARROS
//-----------------------------------------------------------------------------------------
int arq_pvetor (FILE *p, struct CARRO c[])
{
    int i=0;
    struct CARRO s;

    fseek(p,0,SEEK_SET);
    do{
        if(fread(&s,sizeof(struct CARRO),1,p)==1)
        {
            c[i] = s;
            i++;
        }
    }while(!feof(p));
    return (i);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: JOGAR O CARRO PARA ULTIMA POSICAO SEM ALTERAR A SEQUENCIA QUE JÁ SE TEM
//PARAMETRO: O CONJUNTO DE REGISTROS, A QUANTIDAD, E A POSICAO DO CARRO NO VETOR
//-----------------------------------------------------------------------------------------
void ultimo_carro (struct CARRO c[], int q, int pos)
{
    int i;
    struct CARRO aux;
    if (q==pos)
    {

    }
    else
    {
        for (i=pos; i < q-1; i++)
        {
            aux = c[i];
            c[i] = c[i+1];
            c[i+1] = aux;
        }
    }

}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REGRAVAR OS REGISTROS NO ARQUIVO APÓS A EXCLUSAO
//PARAMETRO: ARQUIVO DE CARROS, O CONJUNTO DE CARROS E A QUANTIDADE
//-----------------------------------------------------------------------------------------
void pos_venda (FILE *p, struct CARRO c[], int q)
{
    int i;
    struct CARRO a;

    if ((p = fopen("geracarro.dat","w+b"))==NULL)
    {
        printf("\n\tERRO AO CRIAR O ARQUIVO\n\n");
        exit(102);
    }
    for (i=0;i<q;i++){
        a=c[i];
        if (fwrite(&a,sizeof(struct CARRO),1,p)==1)
        {

        }
    }
    fclose(p);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REMOVER O CARRO DO ARQUIVO
//PARAMETRO: ARQUIVO DE CARROS, O REGISTRO DO CARRO QUE SERÁ DELETADO E A SUA POSICAO NO VETOR
//-----------------------------------------------------------------------------------------
void remove_carro (FILE *p, struct CARRO c, int pos)
{
    struct CARRO conj[100];
    int q;//quantidade de carros

    q = arq_pvetor(p,conj);
    ultimo_carro(conj,q,pos);
    q--; //diminui uma posicao do conjunto pois foi deletado
    pos_venda(p,conj,q);


}

//---------------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE UM CARRO COM TAL PLACA ESTÁ NO ARQUIVO DE VENDAS
//PARAMETRO: O REGISTRO DO CARRO
//RETORNO: 0 CASO NÃO HAJA, E 1 SE HOUVER
//---------------------------------------------------------------------------------
int verifica_venda (struct CARRO c)
{
    FILE *p;
    int op;
    struct CARRO s;

    if ((p = fopen("vendacarro.dat","rb")) == NULL)
    {
        system("cls");
        printf("\tNÃO HÁ NENHUM CARRO VENDIDO! ! \n\n");
        return 1;
    }
    else
    {
        do
        {
            if(fread(&s,sizeof(struct CARRO),1,p) == 1)
            {
                if (strcmp(s.placa,c.placa)==0)
                {
                    return 0;
                }
            }
        }while(!feof(p));
    }
    return 1;
}


//---------------------------------------------------------------------------------
//OBJETIVO: EXCLUIR UM CARRO
//PARAMETRO: NENHUM
//---------------------------------------------------------------------------------
void exclui_carro ()
{
    FILE *p;
    int sort;
    int tot;
    struct CARRO k;
    int pos;

    if ((p = fopen("geracarro.dat","r+b")) == NULL )
    {
        system("cls");
        printf("\tNÃO HÁ CARROS DISPONIVEIS! !");
    }
    else
    {
        fseek(p,0,SEEK_END);
        if(ftell(p)>0){
            fseek(p,0,SEEK_SET);
            pos = gera_placa_igual_venda(p,&k);
            remove_carro(p,k,pos);
            mostracarro(k);
            fclose(p);
        }
        else
        {
            system("cls");
            printf("\tNÃO HÁ CARROS DISPONIVEIS! !");
            fclose(p);
        }
    }
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
        printf("\tFabricante : %s\n\tMODELO : %s\n\tANO DE FABRICAÇÃO: %d\n",c[i].fabricante,c[i].modelo,c[i].ano_fabricacao);
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

//---------------------------------------------------------------------------
//OBEJTIVO: ORDENAR OS CARROS PELO MODELO
//PARAMETRO: O VETOR DE REGISTRO, E A QUANTIDADE DE REGISTRO
//----------------------------------------------------------------------------
void ordena_modelo1(struct CARRO c[], int q)
{
    int i=0;
    int cont = 0;

    do{
        if(strcmp(c[cont].fabricante,c[cont+1].fabricante) == 0)
        {
            if (strcmp(c[cont].modelo,c[cont+1].modelo)>0)
            {
                trocar(c,cont,cont+1);
            }
        }
        cont++;
    }while (cont != q);
}

//-------------------------------------------------------------------------------------
//OBJETIVO: ORDENAR OS REGISTROS
//PARAMETRO: UM CONJUNTO DE REGISTROS, E A SUA QUANTIDADE
//-------------------------------------------------------------------------------------
void ordena_fabricante(struct CARRO c[], int q, int tipo)
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
    if (tipo == 1)
    {
        ordena_modelo1(c,q);
    }
}

//-------------------------------------------------------------------------------------
//OBJETIVO: FAZER TODO O PROCESSO DE ORDENAÇÃO DOS CARROS
//PARAMETRO: UM INTEIRO QUE IRA REPRESENTAR QUAL A ORDENAÇÃO SERA FEITA
//          1 - FABRICANTE E MODELO
//          2 - ANO DE FABRICACAO
//-------------------------------------------------------------------------------------
void ordena_carro (int tipo, char *nome, char *modo)
{
    struct CARRO c;
    struct CARRO sordena[200];
    //struct CARRO ordenado[200];
    int cont=0;
    FILE *arq;
    int tot;

    if ((arq=fopen(nome,modo)) == NULL )
    {
        system("cls");
        printf("\tNÃO HÁ CARROS DISPONIVEIS! !");
    }
    else
    {
        fseek(arq,0,SEEK_END);
        if (ftell(arq)>0)
        {
            fseek(arq,0,SEEK_SET);
            do{
                if (fread(&c,sizeof(struct CARRO),1,arq)==1)
                {
                    sordena[cont] = c;
                    cont++;
                }
            }while(!feof(arq));
            fclose(arq);
            ordena_fabricante(sordena,cont,tipo);
            mostraordenado(sordena,cont);
        }
        else
        {
            system("cls");
            printf("\tNÃO HÁ CARROS DISPONIVEIS! !");

        }
    }

}

//--------------------------------------------------------------
//OBJETIVO: MOSTRAR O MENU CLIENTE PARA O USUARIO
//PARAMETRO: NENHUM
//RETORNO: A OPCAO DO USUARIO
//--------------------------------------------------------------
char menu_cliente ()
{
    char opc;

    printf("\n\t 2 - CLIENTE \n");
    printf("\t\t a. INCLUIR \n");
    printf("\t\t b. EXCLUIR \n");
    printf("\t\t c. LISTAR PELO NOME \n");
    printf("\t\t d. LISTAR PELO NOME E RENDA \n");
    printf("\t\t e. SAIR \n\t\t");
    fflush(stdin);
    scanf("%c",&opc);

    return (opc);
}

//--------------------------------------------------------------
//OBJETIVO: EXECUTAR O MENU CLIENTE PARA O USUARIO
//PARAMETRO: NENHUM
//--------------------------------------------------------------
void executa_menu_cliente ()
{
    FILE *arq;
    char opc; //variavel que recebe a opcao escolhida do menu
    int soma=0,soma2=0;//variaveis contadoras
    //system("color f9");
    struct CLIENTE dados;
    struct CLIENTE cad[30]; //vetor do registro CLIENTE para ordenar os nomes
    struct CLIENTE cad2[30];//vetor do registro CLIENTE para ordenar os nomes e as rendas

   while(opc!='e')
    {
        opc = menu_cliente();
        //system("cls");
        if(opc=='a')
        {
            system("cls");
            if((arq=fopen("Cliente.dat ","r+b"))==NULL)
                {
                    if((arq=fopen("Cliente.dat ","w+b"))==NULL)
                    {
                        printf("\nERRO NA CRIACAO");
                        exit(1);
                    }
                }
             cadastro(&dados);
             fseek(arq,0,SEEK_END);
             if((fwrite(&dados,sizeof (struct CLIENTE),1,arq))==1)
             {
                printf("\nDADOS GRAVADOS COM SUCESSO...\n");
             }
             mostra_cliente(dados);
             //system("pause");
             //system("cls");
             fclose(arq);
        }
        if(opc=='b')
        {
            //printf("\nExclui Cliente\n ");
            exclui_cliente();
        }
        if(opc=='c')
        {
            system("cls");
            soma=0;
            arq=fopen("Cliente.dat","r+b");
            if(arq==NULL)
            {
                system("cls");
                printf("\tNAO EXISTE CLIENTES...\n\n");
            }
            else
            {
                fseek(arq,0,SEEK_END);
                if (ftell(arq)>0){
                    fseek(arq,0,SEEK_SET);
                    while(!feof(arq))
                    {
                       if((fread(&dados,sizeof(struct CLIENTE),1,arq))==1)
                        {
                              cad[soma]=dados;
                              soma++;
                        }
                    }
                    fclose(arq);
                    ordenar_nome(cad,soma);
                    mostra_nome(cad,soma);
                }
                else
                {
                    system("cls");
                    printf("\tNÃO EXITE CADASTRO! !\n\n");
                    fclose(arq);
                }
            }
        }
        if(opc=='d')
        {
            system("cls");
            soma2=0;
            arq=fopen("Cliente.dat","r+b");
            if(arq==NULL)
            {
                system("cls");
                printf("\tNÃO EXITE CADASTRO! !\n\n");
            }
            else{
                fseek(arq,0,SEEK_END);
                if (ftell(arq)>0){
                    fseek(arq,0,SEEK_SET);
                    while(!feof(arq))
                    {
                       if((fread(&dados,sizeof(struct CLIENTE),1,arq))==1)
                        {
                              cad2[soma2]=dados;
                              soma2++;
                        }
                    }
                    fclose(arq);
                    ordena_renda_e_nome(cad2,soma2);
                }
                else
                {
                    system("cls");
                    printf("\tNÃO EXITE CADASTRO! !\n\n");
                    fclose(arq);
                }
            }
        }
    }
}


//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um nome de rua
//parametros: registro cliente:armazenar o nome gerado
//---------------------------------------------------------------------------------
void nome_rua(struct CLIENTE  *d)
{
    char rua[][TAM]={{"Hayel Bon Faker "},{"Avenida Brasil"},{"Joaquim Texeira Alves "},{"Marcelino Pires  "},
    {"Presidente Vargas"},{"Joao Correia Neto "},{"Joao Vicente Ferreira"},{" Joao Damasceno Pires "},
    {"Joaquim Alves Taveira "},{"Joao Rosa Goes"},{"Santo Antonio "},{"Mandaguari "},{"Quinze"},
    {"Ipanema "},{"Cuiaba "},{"Bela Vista "},{"Cafelandia "}};

    int k,j;
    srand(time(NULL));
    k=rand()%17;

    strcpy(d->endereco.rua,rua[k]);
}

//---------------------------------------------------------------------------------
//objetivo: calcula o primeiro digito verificador de um cpf no formato 999999999
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

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero de cpf valido no formato 999.999.999-99
//parametros: registro CLIENTE,o qual ira armazenar o cpf gerado
//retorno:nenhum
//---------------------------------------------------------------------------------
void gera_cpf_valido(struct CLIENTE *d)
{

    int j;
    char ncpf[15];
    char cpf2[15];
    for (j=0;j<9;j++){
        ncpf[j]=rand()%9+48;
    }
    ncpf[9] = obtem_primeiro_digito_verificador(ncpf)+48;
    ncpf[10] = obtem_segundo_digito_verificador(ncpf)+48;
    insere_pontuacao_cpf(ncpf,cpf2);
    strcpy(d->cpf,cpf2);
}

//------------------------------------------------------------
//objetivo: colocar o cep no formato 99.999-999
//parametro: cep, que é o cep do usuario
//-------------------------------------------------------------
void insere_pontuacao_cep(char cep_origem[], char cep_destino[])
{
    int i;
    int cont=0;//auxilia o cep_destino para pegar
                // as posicoes certas do cep pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do cep_origem muda

    for (i=10;i>-1;i--)
    {
        if (i==10)
        {
            cep_destino[i]='\0';
        }
        else{
            if (i!=2 && i!=6){
                if (cont==0){
                    cep_destino[i]=cep_origem[i-2];
                }
                else
                {
                    if(cont==1)
                    {
                        cep_destino[i]=cep_origem[i-1];
                    }
                    else{
                        if (cont==2)
                        {
                            cep_destino[i]=cep_origem[i];
                        }

                    }
                }
            }
            else
            {

                    if(i==6)
                    {
                        cep_destino[i]='-';
                        cont++;
                    }
                    if (i==2)
                    {
                        cep_destino[i]='.';
                        cont++;
                    }
            }
        }
    }
}

//----------------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero de cep no formato 99.999-999
//parametros: registro CLIENTE ,o qual sera armazenado o numero gerado
//retorno:nenhum
//----------------------------------------------------------------------------------------
void gera_cep(struct CLIENTE *d)
{
    int j;
    char ncep[11];
    char cep2[11];
 //   srand(time(NULL));
    for (j=0;j<10;j++){
        ncep[j]=rand()%9+48;
    }
    insere_pontuacao_cep(ncep,cep2);
    strcpy(d->endereco.cep,cep2);
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
//--------------------------------------------------------------------
//objetivo: colocar o numero do telefone no formato 99 99999-9999
//parametro: telefone , que é o telefone do usuario
//--------------------------------------------------------------------
void insere_pontuacao_telefone(char n_origem[], char n_destino[]) //99 99999-9999
{
    int i;
    int cont=0;//auxilia o n_destino para pegar
                // as posicoes certas do numero de telefone pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do n_origem muda

    for (i=13;i>-1;i--)
    {
        if (i==13)
        {
            n_destino[i]='\0';
        }
        else{
            if (i!=2 && i!=8){
                if (cont==0){
                    n_destino[i]=n_origem[i-2];
                }
                else
                {
                    if(cont==1)
                    {
                        n_destino[i]=n_origem[i-1];
                    }
                    else{
                        if (cont==2)
                        {
                            n_destino[i]=n_origem[i];
                        }
                    }
                }
            }
            else
            {
                if (i==8)
                {
                    n_destino[i]='-';
                    cont++;
                }
                else
                {
                    if(i==2)
                    {
                        n_destino[i]=' ';
                        cont++;
                    }
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero de telefone residencial no formato 99 99999-9999
//parametros: registro CLIENTE ,o qual sera armazenado o numero gerado
//retorno:nenhum
//----------------------------------------------------------------------------------------
void gera_tel_residencial(struct CLIENTE *d) {

    int j;
    char n1[15];
    char n2[15];
  //  srand(time(NULL));
    for (j=0;j<9;j++){
        n1[j]=rand()%9+48;
    }
    insere_pontuacao_telefone(n1,n2);
    strcpy(d->residencial.telefone,n2);
}

//----------------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero de telefone celular no formato 99 99999-9999
//parametros: registro CLIENTE ,o qual sera armazenado o numero gerado
//retorno:nenhum
//----------------------------------------------------------------------------------------
void gera_tel_celular(struct CLIENTE *d) {

    int j;
    char n1[14];
    char n2[14];
    //srand(time(NULL));
    for (j=0;j<9;j++){
        n1[j]=rand()%9+48;
    }
    insere_pontuacao_telefone(n1,n2);
    strcpy(d->celular[0].telefone,n2);
}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um nome de bairro
//parametros: registro cliente para armazenar o nome gerado
//---------------------------------------------------------------------------------
void nome_bairro(struct CLIENTE  *d )
{
    char bairro[][TAM]={{"Agua "},{"Boa "},{"Parque "},{"Alvorada "},{"Santo "},{"Andre "},{"Izidro "},{"Pedroso "}};
    int k,j;

   // srand(time(NULL));
    k=rand()%8;

    strcpy(d->endereco.bairro,bairro[k]);

     j=rand()%8;
    while(j==k)
    {
        j=rand()%8;
    }
    strcat(d->endereco.bairro,bairro[j]);
}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um numero para o endereco
//parametros: De referencia : registro cliente para armazenar o numero gerado
//---------------------------------------------------------------------------------
void numero_endereco(struct CLIENTE *d)
{
    int k;

    //srand(time(NULL));
    k=rand()%1000 + 1;

    d->endereco.numero=k;
}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente uma cidade
//parametros: De referncia :registro CLIENTE para armazenar o nome da cidade gerada
//---------------------------------------------------------------------------------
void nome_cidade(struct CLIENTE  *d)
{
    char cidade[][TAM]={{"Dourados "},{"Maringa "},{"Curitiba "},{"Sao Paulo "},{"Rio de Janeiro "},{"Florianopolis "},
    {"Salvador "},{"Rondonopolis "},{"Sao Jose dos Campos "},{"Campo Grande "},{"Cuiaba "},{"Porto Alegre "},{"Recife "}};

     int k;
    //srand(time(NULL));
    k=rand()%13;

    strcpy(d->endereco.cidade,cidade[k]);
}

//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente um estado
//parametros: registro CLIENTE para armazenar o estado gerado
//---------------------------------------------------------------------------------
void n_estado(struct CLIENTE  *d)
{
    char estado[][TAM]={{"MS"},{"MT"},{"PR"},{"SP"},{"BA"},{"RJ"},{"PE"},{"SC"},{"RS"}};
    int k;

    //srand(time(NULL));
    k=rand()%9;

    strcpy(d->endereco.estado,estado[k]);

}

//---------------------------------------------------------------------------------
//objetivo:gera um nome aleatoriamente
//parametros: registro CLIENTE para armazenar o nome gerado
//---------------------------------------------------------------------------------
void nome_cliente( struct CLIENTE  *d)
{
    char nome[][TAM]={{"Maria "},{"Julia "},{"Ana "},{"Carla "},{"Karol "},{"Joao "},
    {"Carlos "},{"Fernando "},{"Jose "},{"Pedro "},{"Fernanda  "},{"Lorenzo "},{"Debora "},{"Junior "},{"Isabela "},{"Ronaldo "},
    {"Lucas "},{"Matheus "},{"Vitor "},{"Antonio "},{"Leonardo "},{"Franscismar "},{"Karen "},{"Thiago "},{"Iury "},
    {"Amanda "},{"Alicia "},{"Laura "},{"Thais "},{"Larissa "},{"Caio "},{"Clarice "},{"Clara "},{"Luis "}};

    char sobrenome[][TAM]={{"Alves "},{"Lispector "},{"Tafarel"},{"Bastos "},{"Santos "},{"Souza "},{"Rocha "},{"Lima "},
    {"Pereira "},{"Dourado "},{"Barbosa "},{"Dias "},{"Cardoso "},{"Castro "},{"Ransolin "},{"Mendes "},{"Costa "},{"Pires "},{"Neto "},
    {"Rodrigues "},{"Martins "}};
    int k;
    int j;

    srand(time(NULL));
    k=rand()%34;

    strcpy(d->nome,nome[k]);

     j=rand()%21;

    strcat(d->nome,sobrenome[j]);
}
//---------------------------------------------------------------------------------
//objetivo:gera aleatoriamente uma renda
//parametros: registro CLIENTE
//---------------------------------------------------------------------------------
void renda(struct CLIENTE *d)
{
    d->renda_mensal=5000 + rand()%(10000);

}

//---------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE UM CLIENTE JÁ POSSUI UMA VENDA
//PARAMETRO: O REGISTRO DO CLIENTE
//RETORNO: 0 CASO ELE NÃO FEZ UMA VENDA, OU 1
//---------------------------------------------------------------------------
int verifica_cliente_venda (struct CLIENTE c)
{
    FILE *p;
    struct VENDA_CARRO s;

    if ((p=fopen("vendacarro.dat","rb")) == NULL)
    {
        return 0;
    }
    else
    {
        do
        {
            if (fread(&s,sizeof(struct VENDA_CARRO),1,p) == 1)
            {
                if (strcmp(s.cpf_cli,c.cpf)==0)
                {
                    return 1;
                }
            }
        }while(!feof(p));
    }
    return 0;
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: PASSAR TODOS OS ARQUIVOS PARA UM VETOR
//PARAMETRO: ARQUIVO DE CARROS E UM CONJUNTO DE REGISTROS
//RETORNO: A QUANTIDADE DE CARROS
//-----------------------------------------------------------------------------------------
int arq_pvetor_cliente (FILE *p, struct CLIENTE c[])
{
    int i=0;
    struct CLIENTE s;

    fseek(p,0,SEEK_SET);
    do{
        if(fread(&s,sizeof(struct CLIENTE),1,p)==1)
        {
            c[i] = s;
            i++;
        }
    }while(!feof(p));
    return (i);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: JOGAR O CARRO PARA ULTIMA POSICAO SEM ALTERAR A SEQUENCIA QUE JÁ SE TEM
//PARAMETRO: O CONJUNTO DE REGISTROS, A QUANTIDAD, E A POSICAO DO CARRO NO VETOR
//-----------------------------------------------------------------------------------------
void ultimo_carro_cliente (struct CLIENTE c[], int q, int pos)
{
    int i;
    struct CLIENTE aux;
    if (q==pos)
    {

    }
    else
    {
        for (i=pos; i < q-1; i++)
        {
            aux = c[i];
            c[i] = c[i+1];
            c[i+1] = aux;
        }
    }

}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REGRAVAR OS REGISTROS NO ARQUIVO APÓS A EXCLUSAO
//PARAMETRO: ARQUIVO DE CARROS, O CONJUNTO DE CARROS E A QUANTIDADE
//-----------------------------------------------------------------------------------------
int pos_venda_cliente(FILE *p, struct CLIENTE c[], int q,struct CLIENTE l)
{
    int i;
    int cont=0;
    struct CLIENTE a;

    if ((p = fopen("Cliente.dat","w+b"))==NULL)
    {
        system("cls");
        printf("\n\tCLIENTES COM VENDAS! !\n\n");
        system("pause");
        //exit(102);

    }
    else{
        for (i=0;i<q;i++){
            a=c[i];
            if (fwrite(&a,sizeof(struct CLIENTE),1,p)==1)
            {
                cont++;
            }
        }
        printf("\tCLIENTE EXCLUÍDO\n");
        mostra_cliente(l);
        fclose(p);
    }
    //printf("\n--> %d %d <--\n",i, q);
    //system("pause");
}

//----------------------------------------------------------------------
//OBJEITVO: EXCLUIR UM CLIENTE
//PARAMETRO: NENHUM
//----------------------------------------------------------------------
void exclui_cliente()
{
    struct CLIENTE c;
    FILE *p;
    FILE *s;
    int sort, tot;
    //FILE *p;
    struct CLIENTE conj[100];
    int ver;

    if((p=fopen("Cliente.dat","rb"))== NULL)
    {
        system("cls");
        printf("\tNÃO HÁ CLIENTES!\n\n");
    }
    else
    {

        //sorteia um numero do total de clientes existentes
        fseek(p,0,SEEK_END);
        if (ftell(p)>0){
            do{
                fseek(p,0,SEEK_END);
                tot = ftell(p)/sizeof(struct CLIENTE);
                sort = rand() % tot;
                fseek(p,sizeof(struct CLIENTE)*sort,SEEK_SET);
                if (fread(&c,sizeof(struct CLIENTE),1,p) == 1)
                {
                    ver = verifica_cliente_venda(c);
                }
            }while(ver != 0);
            arq_pvetor_cliente(p,conj);
            ultimo_carro_cliente(conj,tot,sort);
            tot--;
            pos_venda_cliente(p,conj,tot,c);
            //system("cls");
            fclose(p);
        }
        else
        {
            system("cls");
            printf("\tNÃO HÁ CLIENTES!\n\n");
        }
    }

}

//---------------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE HÁ UM CADASTRO COM ESSE CPF
//PARAMETRO: O REGISTRO
//RETORNO 0 CASO NÃO HAJA, SE HOUVER RETORNA 1
//---------------------------------------------------------------------------------
int verifica_cpf (struct CLIENTE c)
{
    FILE *p;
    struct CLIENTE s;

    if ((p=fopen("Cliente.dat","rb"))==NULL)
    {
        return 0;
    }
    else
    {
        fseek(p,0,SEEK_END);
        if (ftell(p)>0)
        {
            fseek(p,0,SEEK_SET);
            do{
                if (fread(&s,sizeof(struct CLIENTE),1,p)==1)
                {
                    if(strcmp(c.cpf,s.cpf)==0)
                    {
                        return 1;
                    }
                }
            }while(!feof(p));
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------------
//objetivo:Cadastrar um cliente
//parametros: registro CLIENTE
//---------------------------------------------------------------------------------
void cadastro(struct CLIENTE *d)
{
    int ver;

    nome_cliente(d);
    nome_rua(d);
    numero_endereco(d);
    nome_bairro(d);
    nome_cidade(d);
    n_estado(d);
    do{
        gera_cpf_valido(d);
        ver = verifica_cpf(*d);
    }while(ver!=0);
    renda(d);
    gera_cep(d);
    gera_tel_residencial(d);
    gera_tel_celular(d);
}

//---------------------------------------------------------------------------------
//objetivo:Mostrar o cliente que foi incluido
//parametros: registro CLIENTE
//---------------------------------------------------------------------------------
void mostra_cliente(struct CLIENTE d)
{
    printf("\nNOME : \t");
    puts(d.nome);
    printf("\nENDERECO : ");
    printf("%s - NUMERO :%d \n ",d.endereco.rua,d.endereco.numero);
    printf("\nBAIRRO : ");
    puts(d.endereco.bairro);
    printf("\nCIDADE : ");
    puts(d.endereco.cidade);
    printf("\nESTADO : ");
    puts(d.endereco.estado);
    printf("\nCPF : ");
    puts(d.cpf);
    printf("\nRENDA : %.2f ",d.renda_mensal);
    printf("\nCEP: ");
    puts(d.endereco.cep);
    printf("\nTELEFONE RESIDENCIAL : ");
    puts(d.residencial.telefone);
    printf("\nTELEFONE CELULAR : ");
    puts(d.celular[0].telefone);


}

//---------------------------------------------------------------------------------
//Objetivo:Ordenar os nomes dos clientes em ordem alfabetica
//Parametros: registro CLIENTE e a quantidade de clientes no arquivo
//---------------------------------------------------------------------------------
void ordenar_nome(struct CLIENTE d[],int k)
{
    int i,j;
    char vet[30]; // string auxiliar para realiar a toca dos nomes
    for(i = 0; i < k ; i++)
    {
      for (j = 0;j <k-1; j++)
      {
            if(strcmp(d[j].nome,d[j+1].nome)>0)
            {
                strcpy(vet,d[j].nome);
                strcpy(d[j].nome,d[j+1].nome);
                strcpy(d[j+1].nome,vet);
            }
        }
    }
}

//---------------------------------------------------------------------------------
//Objetivo:Ordenar os nomes dos clientes em ordem alfabetica e por renda
//Parametros: registro CLIENTE  e quantidade de clientes no arquivo
//---------------------------------------------------------------------------------
void ordena_renda_e_nome(struct CLIENTE d[],int soma)
{
    int i,j,a;
    char vet[30]; // string auxiliar para realizar a troca
    for(i = 0; i < soma; i++)
     {
        for(j = 0; j < soma-1; j++)
         {
            if(d[j].renda_mensal > d[j+1].renda_mensal)
            {
                strcpy(vet,d[j].nome);
                strcpy(d[j].nome,d[j+1].nome);
                strcpy(d[j+1].nome,vet);
                a = d[j].renda_mensal;
                d[j].renda_mensal = d[j+1].renda_mensal;
                d[j+1].renda_mensal=a;
            }
         }
     }
     for(i=0;i<soma;i++)
     {
        printf("\n%s\t\t%f\t",d[i].nome, d[i].renda_mensal);

     }
}
//---------------------------------------------------------------------------------
//Objetivo:Mostrar os nomes apos ser ordenado
//Parametros: registro CLIENTE  e quantidade de clientes no arquivo
//---------------------------------------------------------------------------------
void mostra_nome(struct CLIENTE d[],int k)
{
    int i;
     for(i=0;i<k;i++)
    {
      printf("NOME: %s\tCPF: %s\n",d[i].nome,d[i].cpf);
    }
}

//-------------------------------------------------------------------------------------
//OBJETIVO: ABRIR UM ARQUIVO OU CRIAR UM ARQUIVO
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------
FILE *AbreArqv ()
{
    FILE *p;

    if ((p = fopen("vendacarro.dat","r+b")) == NULL)
    {
        if ((p = fopen("vendacarro.dat","w+b"))== NULL)
        {
            printf("ERRO");
            exit(100);
        }
    }

}


//----------------------------------------------------------------------------------
//OBJETIVO: SORTEAR UM CLIENTE PARA COMPRAR O CARRO
//PARAMETRO: UM REGISTRO DE VENDA
//RETORNO: 1 PARA INSUCESSO, CASO CONTRARIO 0
//----------------------------------------------------------------------------------
int sorteia_cliente (struct VENDA_CARRO *c)
{
    int sort, tot;//um faz o sorteio e o outro verifica quantos registro tem
    FILE *p;
    struct CLIENTE k;

    if ((p = fopen("Cliente.dat","rb"))== NULL)
    {
        system("cls");
        printf("\tSEM CLIENTES PARA VENDA! ! \n\n");
        return 1;
    }
    else
    {
        fseek(p,0,SEEK_END);
        if(ftell(p)>0){
            tot = ftell(p)/sizeof(struct CLIENTE);
            sort = rand() % tot;
            fseek(p,sizeof(struct CLIENTE)*sort,SEEK_SET);
            if (fread(&k,sizeof(struct CLIENTE),1,p)==1)
            {
                strcpy(c->cpf_cli,k.cpf);
                strcpy(c->nome,k.nome);
                fclose(p);
                return 0;
            }
        }
        else
        {
            system("cls");
            printf("\tSEM CLIENTES PARA VENDA! ! \n\n");
            fclose(p);
            return 1;
        }
    }
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: INSERIR UMA VENDA NO ARQUIVO
//PARAMETRO: ARQUIVO DE CARROS E O ARQUIVO DE VENDAS
//-----------------------------------------------------------------------------------------
void insere_venda ()
{
    struct CARRO c;
    struct VENDA_CARRO v;
    FILE *p;
    int pos;//pega a posicao do carro que sera excluido no arquivo
    FILE *s;//arquivo de venda


    if ((p = fopen("geracarro.dat","rb")) == NULL)
    {
        system("cls");
        printf("\tNENHUM CARRO PARA VENDER! !\n\n");
    }
    else{
        s = AbreArqv();
        fseek(s,0,SEEK_END);
        fseek(p,0,SEEK_END);
        //printf("-->>");
        if (ftell(p)>0){
            if (ftell(s)<0)
            {
                //printf("-->>");
                if(sorteia_cliente(&v)==0) {
                    gera_placa_igual_venda(p,&c);
                    strcpy(v.placa_car,c.placa);
                    strcpy(v.fabricante,c.fabricante);
                    strcpy(v.modelo,c.modelo);
                    v.preco_venda = c.preco_compra;
                    v.ano_fabricacao = c.ano_fabricacao;
                    if (fwrite(&v,sizeof(struct VENDA_CARRO),1,s)==1)
                    {
                        remove_carro(p,c,pos);
                        system("cls");
                        printf("\tVENDA INSERIDA \n\n");
                        mostracarro_exc(v);
                    }
                }
                fclose(s);
                fclose(p);
            }
            else
            {
                if (sorteia_cliente(&v) == 0){
                    pos = gera_placa_igual_venda(p,&c);
                    //printf("-->> aq");
                    strcpy(v.placa_car,c.placa);
                    strcpy(v.fabricante,c.fabricante);
                    strcpy(v.modelo,c.modelo);
                    v.preco_venda = c.preco_compra;
                    v.ano_fabricacao = c.ano_fabricacao;
                    if (fwrite(&v,sizeof(struct VENDA_CARRO),1,s)==1)
                    {
                        remove_carro(p,c,pos);
                        printf("\tVENDA INSERIDA: \n\n");
                        mostracarro_exc(v);
                    }
                }
                fclose(s);
                fclose(p);
            }
        }
        else
        {
            system("cls");
            printf("\tSEM CARROS PARA VENDER! !\n\n");
            fclose(s);
            fclose(p);
        }
    }
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: GERAR UMA PLACA
//PARAMETRO: O ARQUIVO COM CARROS E UM REGISTRO
//RETORNO: A POSICAO DO CARRO QUE FOI SORTEADA
//-----------------------------------------------------------------------------------------
int gera_placa_igual(FILE *p, struct VENDA_CARRO *l)
{
    int q;
    int q1;
    //struct CARRO l;
    //int tot;

    fseek(p,0,SEEK_END);
    q = ftell(p)/sizeof(struct VENDA_CARRO);
    //printf("--> %d",ftell(p));
    q1 = rand() % q;
    fseek(p,sizeof(struct VENDA_CARRO)*q1,SEEK_SET);
    //tot = ftell(p);
    if (fread(l,sizeof(struct VENDA_CARRO),1,p)==1)
    {
        printf("SUCESSO\n");
        return(q1);
        //mostracarro(l);
    }

    //printf("-->%d",q);
    //system("pause");


}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REGRAVAR OS REGISTROS NO ARQUIVO APÓS A EXCLUSAO
//PARAMETRO: ARQUIVO DE CARROS, O CONJUNTO DE CARROS E A QUANTIDADE
//-----------------------------------------------------------------------------------------
void pos_exclusao (FILE *p, struct VENDA_CARRO c[], int q)
{
    int i;
    int cont=0;
    struct VENDA_CARRO a;

    if ((p = fopen("vendacarro.dat","w+b"))==NULL)
    {
        printf("\n\tERRO AO CRIAR O ARQUIVO\n\n");
        exit(102);
    }
    for (i=0;i<q;i++){
        a=c[i];
        if (fwrite(&a,sizeof(struct VENDA_CARRO),1,p)==1)
        {
            cont++;
        }
    }
    fclose(p);
    //printf("\n--> %d %d <--\n",i, q);
    //system("pause");
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: JOGAR O CARRO PARA ULTIMA POSICAO SEM ALTERAR A SEQUENCIA QUE JÁ SE TEM
//PARAMETRO: O CONJUNTO DE REGISTROS, A QUANTIDAD, E A POSICAO DO CARRO NO VETOR
//-----------------------------------------------------------------------------------------
void ultimo_carro_exc (struct VENDA_CARRO c[], int q, int pos)
{
    int i;
    struct VENDA_CARRO aux;
    if (q==pos)
    {

    }
    else
    {
        for (i=pos; i < q-1; i++)
        {
            aux = c[i];
            c[i] = c[i+1];
            c[i+1] = aux;
        }
    }

}

//-----------------------------------------------------------------------------------------
//OBJETIVO: PASSAR TODOS OS ARQUIVOS PARA UM VETOR
//PARAMETRO: ARQUIVO DE CARROS E UM CONJUNTO DE REGISTROS
//RETORNO: A QUANTIDADE DE CARROS
//-----------------------------------------------------------------------------------------
int arq_pvetor_exc (FILE *p, struct VENDA_CARRO c[])
{
    int i=0;
    struct VENDA_CARRO s;

    fseek(p,0,SEEK_SET);
    do{
        if(fread(&s,sizeof(struct VENDA_CARRO),1,p)==1)
        {
            c[i] = s;
            i++;
        }
    }while(!feof(p));
    return (i);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REMOVER O CARRO DO ARQUIVO
//PARAMETRO: ARQUIVO DE CARROS, O REGISTRO DO CARRO QUE SERÁ DELETADO E A SUA POSICAO NO VETOR
//-----------------------------------------------------------------------------------------
void remove_carro_exc (FILE *p, struct VENDA_CARRO c, int pos)
{
    struct VENDA_CARRO conj[100];
    int q;//quantidade de carros

    q = arq_pvetor_exc(p,conj);
    //printf("\n\n");
    //mostracarro(conj[2]);
    //printf("\n\n");
    ultimo_carro_exc(conj,q,pos);
    q--; //diminui uma posicao do conjunto pois foi deletado
    pos_exclusao(p,conj,q);


}

//-------------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR OS CARROS
//PARAMETRO: O REGISTRO DO CARRO QUE SERÁ MOSTRADO
//-------------------------------------------------------------------------------------
void mostracarro_exc (struct VENDA_CARRO car)
{
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("\tModelo : %s\n\tFabricante : %s\n\tAno de Fabricação : %d\n",car.modelo,car.fabricante,car.ano_fabricacao);
    //printf("\n\tADICIONAIS : %s\n\t\t%s\n\t\t%s\n",opcionais[car.opcional[0]],opcionais[car.opcional[1]],opcionais[car.opcional[2]]);
    printf("\tPlaca : %s\n\tPreco de compra : %.2f\n",car.placa_car,car.preco_venda);
    printf("\tCOMPRADOR: %s\tCPF: %s\n",car.nome,car.cpf_cli);
    printf("-------------------------------------------------------------------------------------\n");


}

//-------------------------------------------------------------------------------------
//OBJETIVO: EXCLUIR UMA VENDA
//PARAMETRO: NENHUM
//-------------------------------------------------------------------------------------
void exclui_venda ()
{
    FILE *p;
    struct VENDA_CARRO c;
    int pos;

    if ((p=(fopen("vendacarro.dat","rb"))) == NULL)
    {
        system("cls");
        printf("\nNÃO POSSUI CARROS VENDIDOS! !\n\n");
    }
    else
    {
        fseek(p,0,SEEK_END);
        if (ftell(p)>0){
            fseek(p,0,SEEK_SET);
            pos = gera_placa_igual(p,&c);
            remove_carro_exc(p,c,pos);
            system("cls");
            printf("\tVENDA EXCLUÍDA COM SUCESSO.\n CARRO:\n");
            mostracarro_exc(c);
            fclose(p);
        }
        else
        {
            system("cls");
            printf("\nNÃO POSSUI CARROS VENDIDOS! !\n\n");
            fclose(p);
        }
    }
}


//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O MODELO, PLACA, ANO DE FABRICACAO E O NOME DO COMPRADOR
//PARAMETRO: O REGISTRO DA VENDA
//-------------------------------------------------------------------------------
void mostra_apn (struct VENDA_CARRO c)
{
    printf("----------------------------------------------------------------\n");
    printf("\tPLACA: %s\n\tANO DE FABRICAÇÃO: %d\n\tNOME DO CLIENTE: %s\n",c.placa_car,c.ano_fabricacao,c.nome);
    printf("----------------------------------------------------------------\n");
}

//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O MODELO, PLACA, ANO DE FABRICACAO E O NOME DO COMPRADOR
//PARAMETRO: O REGISTRO DA VENDA
//-------------------------------------------------------------------------------
void mostra_mpan (struct VENDA_CARRO c)
{
    printf("----------------------------------------------------------------\n");
    printf("\tMODELO: %s\n\tPLACA: %s\n\tANO DE FABRICAÇÃO: %d\n\tNOME DO CLIENTE: %s\n",c.modelo,c.placa_car,c.ano_fabricacao,c.nome);
    printf("----------------------------------------------------------------\n");
}

//------------------------------------------------------------------------------
//OBJETIVO: COLOCAR NO VETOR OS CARROS DE UM TIPO
//PARAMETRO: UM VETOR DE REGISTROS, E UM REGISTRO COM UM FABRICANTE QUALQUER
//           E O TIPO:  1 - FABRICANTE
//                      2 - MODELO
//RETORNO: A QUANTIDADE DE CARROS COM O MESMO FABRICANTE
//------------------------------------------------------------------------------
int vetor_pfab (struct VENDA_CARRO c[], struct VENDA_CARRO k, int tipo)
{
    FILE *p;
    int i=0;
    struct VENDA_CARRO s;
    if ((p = fopen("vendacarro.dat","rb")) == NULL)
    {
        system("cls");
        printf("\tNÃO EXISTE CARROS VENDIDOS! ");
        return (i);
    }
    else
    {
        fseek(p,0,SEEK_END);
        if (ftell(p)>0){
            fseek(p,0,SEEK_SET);
            do
            {
                if (fread(&s,sizeof(struct VENDA_CARRO),1,p) == 1){
                    if (tipo == 1){//tipo fabricante
                        if (strcmp(s.fabricante,k.fabricante) == 0){
                            c[i] = s;
                            i++;
                        }
                    }
                    else
                    {
                        if (strcmp(s.modelo,k.modelo) == 0){
                            c[i] = s;
                            i++;
                        }
                    }
                }
            }while(!feof(p));
            fclose(p);
        }
        else
        {
            system("cls");
            printf("\tNÃO EXISTE CARROS VENDIDOS! ");
            fclose(p);
            return (i);
        }
    }
    fclose(p);
    return (i);
}

//-------------------------------------------------------------------------------------
//OBJETIVO: MUDAR A POSICAO DO CARRO NO VETOR DE REGISTRO
//PARAMETRO: O CONJUNTO DE REGISTROS POR REFERENCIA,  x = POSICAO DO
//           REGISTRO QUE É MAIOR DO QUE AQUELE QUE ESTÁ NA POSICAO y
//-------------------------------------------------------------------------------------
void trocar1(struct VENDA_CARRO *c, int x, int y) {

		struct VENDA_CARRO aux;

		aux = c[x];
		c[x] = c[y];
		c[y] = aux;

}

//---------------------------------------------------------------------------
//OBEJTIVO: ORDENAR OS CARROS PELO MODELO
//PARAMETRO: O VETOR DE REGISTRO, E A QUANTIDADE DE REGISTRO
//----------------------------------------------------------------------------
void ordena_modelo2(struct VENDA_CARRO c[], int q)
{
    int i=0;
    int cont = 0;

    do{
        if (strcmp(c[cont].modelo,c[cont+1].modelo)>0)
        {
            trocar1(c,cont,cont+1);
        }
        cont++;
    }while (cont != q);
}

//---------------------------------------------------------------------------------
//OBJETIVO: ORDENAR UM CONJUNTO DE REGISTRO DE UM UNICO FABRICANTE
//PARAMETRO: NENHUM
//--------------------------------------------------------------------------------
void ordena_fabri_modelo()
{
    int f;//representa um sorteio aleatorio dos fabricantes
    int i;
    char fabri[][TAM] = {{"Chevrolet"}, {"Fiat"}, {"Ford"}, {"Honda"}, {"Renault"}, {"Toyota"}, {"Volkswagen"}};
    struct VENDA_CARRO conj[100];
    struct VENDA_CARRO k;
    int q=0; //representa a quantidade de carros com o mesmo fabricante
    FILE *p;
    int tot=0;//representa o total de registros no arquivo


    if ((p = fopen("vendacarro.dat","rb")) == NULL )
    {
        system("cls");
        printf("\tSEM CARROS \n\n");
    }
    else{
            fseek(p,0,SEEK_END);
            if(ftell(p)>0){
                tot = ftell(p)/sizeof(struct VENDA_CARRO);
                f = rand () % tot;
                fseek(p,sizeof(struct VENDA_CARRO)*f,SEEK_SET);
                if (fread(&k,sizeof(struct VENDA_CARRO),1,p) == 1){
                    q = vetor_pfab(conj,k,1);
                    ordena_modelo2(conj,q);
                    for (i=0;i<q;i++)
                    {
                        mostra_mpan(conj[i]);
                    }
                }
            }
            else
            {
                system("cls");
                printf("\tSEM CARROS \n\n");
                fclose(p);
            }
    }

}

//-------------------------------------------------------------------------------
//OBJETIVO: ORDENAR OS REGISTROS PELO ANO DE FABRICAÇÃO
//PARAMETRO: O VETOR COM OS REGISTROS, E A QUANTIDADE
//-------------------------------------------------------------------------------
void ordena_ano_fabricante(struct VENDA_CARRO c[], int q)
{
    int i=0;
    int cont = 0;

    do{
        if (c[cont].ano_fabricacao>c[cont+1].ano_fabricacao)
        {
            trocar1(c,cont,cont+1);
        }
        cont++;
    }while (cont != q);
}

//---------------------------------------------------------------------------------
//OBJETIVO: ORDENAR UM CONJUNTO DE REGISTRO DE UM UNICO FABRICANTE
//PARAMETRO: NENHUM
//--------------------------------------------------------------------------------
void ordena_modelo_af()
{
    int f;//representa um sorteio aleatorio dos fabricantes
    int i;
    char fabri[][TAM] = {{"Chevrolet"}, {"Fiat"}, {"Ford"}, {"Honda"}, {"Renault"}, {"Toyota"}, {"Volkswagen"}};
    struct VENDA_CARRO conj[100];
    struct VENDA_CARRO k;
    int q=0; //representa a quantidade de carros com o mesmo fabricante
    FILE *p;
    int tot=0;//representa o total de registros no arquivo


    if ((p = fopen("vendacarro.dat","rb")) == NULL )
    {
        system("cls");
        printf("\tSEM CARROS \n\n");
    }
    else{
            fseek(p,0,SEEK_END);
            if(ftell(p)>0){
                tot = ftell(p)/sizeof(struct VENDA_CARRO);
                f = rand () % tot;
                fseek(p,sizeof(struct VENDA_CARRO)*f,SEEK_SET);
                if (fread(&k,sizeof(struct VENDA_CARRO),1,p) == 1){
                    q = vetor_pfab(conj,k,2);
                    ordena_ano_fabricante(conj,q);
                }
            }
            else
            {
                system("cls");
                printf("\tSEM CARROS \n\n");
                fclose(p);
            }
    }
    system("cls");
    if(tot>0)
    {
        for (i=0;i<q;i++)
        {
            mostra_apn(conj[i]);
        }
    }
    else
    {
        system("cls");
        printf("\tSEM CARROS \n\n");
    }
}



//--------------------------------------------------------------------
//OBJETIVO: MOSTRAR A QUANTIDADE DE CARROS VENDIDOS E O VALOR TOTAL
//PARAMETRO: NENHUM
//--------------------------------------------------------------------
void qcarros_totvendido ()
{
    FILE *p;
    int q=0;
    float valor = 0;
    struct VENDA_CARRO l;

    if ((p = fopen("vendacarro.dat","rb")) == NULL )
    {
        system("cls");
        printf("\tNÃO HÁ CARROS VENDIDOS!");
    }
    else
    {
        fseek(p,0,SEEK_END);
        if (ftell(p)>0)
        {
            fseek(p,0,SEEK_SET);
            do{
                if (fread(&l,sizeof(struct VENDA_CARRO),1,p) == 1)
                {
                    q++;
                    valor += l.preco_venda;
                }
            }while(!feof(p));
            fclose(p);
        }
        else
        {
            fclose(p);
        }
    }

    printf("\tTOTAL DE CARROS VENDIDOS: %d\n\tTOTAL DE PREÇOS VENDIDOS: %f\n\n",q,valor);
}

//----------------------------------------------------------
//OBJETIVO: MOSTRAR O LUCRO DAS VENDAS
//PARAMETRO: NENHUM
//----------------------------------------------------------
void informa_lucro ()
{
    FILE *p;
    struct VENDA_CARRO l;
    float total=0;

    if ((p = fopen("vendacarro.dat","rb")) == NULL )
    {
        system("cls");
        printf("\tNÃO HÁ CARROS VENDIDOS!");
    }
    else
    {
        do{
            if (fread(&l,sizeof(struct VENDA_CARRO),1,p) == 1)
            {
                total += l.preco_venda;
            }
        }while(!feof(p));
    }
    printf("\tLUCRO TOTAL: %f\n\n",total);
}

//------------------------------------------------------------------------------------
//OBEJTIVO: MOSTRAR O MENU DAS VENDAS
//PARAMETRO NENHUM
//RETORNO: A OPCAO QUE O USUARIO DESEJA
//------------------------------------------------------------------------------------
char menu_vendas()
{
    char op;

    printf("\t3 - VENDA\n");
    printf("\t\ta. - INSERIR UMA VENDA\n");
    printf("\t\tb. - EXCLUIR UMA VENDA\n");
    printf("\t\tc. - LISTAR OS CARROS VENDIDOS DE UM DETERMINADO FABRICANTE, ORDENADOS CRESCENTEMENTE PELO MODELO (AS SEGUINTES INFORMAÇÕES DEVEM APARECER: MODELO, PLACA, ANO DE FABRICAÇÃO E NOME CLIENTE)\n");
    printf("\t\td. - LISTAR OS CARROS VENDIDOS DE UM DETERMINADO MODELO, ORDENADOS CRESCENTEMENTE PELO ANO DE FABRICAÇÃO (AS SEGUINTES INFORMAÇÕES DEVEM APARECER: ANO DE FABRICAÇÃO, PLACA E NOME CLIENTE)\n");
    printf("\t\te. - INFORMAR A QUANTIDADE DE CARROS VENDIDOS COM O VALOR TOTALIZADO DOS PREÇOES VENDIDOS\n");
    printf("\t\tf. - INFORMAR O LUCRO TOTAL DAS VENDAS\n");
    printf("\t\tg. - SAIR\n\t\t");
    fflush(stdin);
    scanf("%c",&op);
    return(op);
}


//------------------------------------------------------------------------------------
//OBEJTIVO: EXECUTAR O MENU DE VENDA
//PARAMETRO NENHUM
//------------------------------------------------------------------------------------
void executa_menu_vendas ()
{

    //int op;
    char op;

    do{
        op = menu_vendas();
        //inserir venda
        if(op == 'a')
        {
            system("cls");
            insere_venda();
            //mostracarro(conj);
        }
        //exclui venda
        if(op == 'b')
        {
            system("cls");
            exclui_venda();
        }
        //mostra vendidos por um fabricante ordem crescente
        if(op == 'c')
        {
            system("cls");
            ordena_fabri_modelo();
        }
        //mostra vendidos de um modelo ordem crescente
        if(op == 'd')
        {
            system("cls");
            ordena_modelo_af();
        }
        //informa a quantidade de carros vendidos e o valor total
        if(op == 'e')
        {
            system("cls");
            qcarros_totvendido();
        }
        //informa o lucro
        if(op == 'f')
        {
            system("cls");
            informa_lucro();
        }
    }while(op!='g');
}

int main()
{
    setlocale(LC_ALL,"");
    printf("\n");
    system("color a");
    char op;

    do
    {
        system("cls");
        printf("\n\t1 - CARRO\n");
        printf("\t2 - CLIENTE\n");
        printf("\t3 - VENDA\n");
        printf("\t4 - SAIR\n\t");
        scanf("%c",&op);
        //carro
        if (op == '1')
        {
            system("cls");
            executa_menu_carro();
        }
        //cliente
        if (op == '2')
        {
            system("cls");
            executa_menu_cliente();
        }
        //venda
        if (op == '3')
        {
            system("cls");
            executa_menu_vendas();
        }
        if (op != '4')
        {

        }
    }while(op != '4');

    return 0;
}
