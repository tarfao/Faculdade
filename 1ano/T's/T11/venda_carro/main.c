#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void mostracarro_exc();



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

//-------------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR OS CARROS
//PARAMETRO: O REGISTRO DO CARRO QUE SERÁ MOSTRADO
//-------------------------------------------------------------------------------------
void mostracarro (struct CARRO car)
{
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("\tModelo : %s\n\tFabricante : %s\n\tAno de Fabricação : %d\n\tAno do modelo: %d \tTipo : %s\n\tCor : %s\n",car.modelo,car.fabricante,car.ano_fabricacao,car.ano_modelo,car.combustivel,car.cor);
    printf("\tADICIONAIS : %s\n\t\t%s\n\t\t%s\n",opcionais[car.opcional[0]],opcionais[car.opcional[1]],opcionais[car.opcional[2]]);
    printf("\tPlaca : %s\n\tPreco de compra : %.2f\n",car.placa,car.preco_compra);
    printf("-------------------------------------------------------------------------------------\n");


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
                    if (tipo == 1){
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
            return (i);
            fclose(p);
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
void trocar (struct VENDA_CARRO *c, int x, int y) {

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
            trocar(c,cont,cont+1);
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
            mostra_mpan(conj[i]);
        }
    }
    else
    {
        system("cls");
        printf("\tSEM CARROS \n\n");
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
            trocar(c,cont,cont+1);
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
        /*if(op == 'g')
        {
            system("cls");
            if ((pfilecarro = fopen("vendacarro.dat","rb")) == NULL)
            {
                system("cls");
                printf("\tNAO POSSUI NENHUM CARRO PARA VENDER! !\n\n");
            }
            else
            {
                fseek(pfilecarro,0,SEEK_SET);
                do{
                    if (fread(&conj,sizeof(struct VENDA_CARRO),1,pfilecarro) == 1)
                    {
                        mostracarro_exc(conj);
                    }
                }while(!feof(pfilecarro));
            }
            fclose(pfilecarro);

        }*/
    }while(op!='h');
}

int main()
{
    setlocale(LC_ALL,"");
    system("color a");
    executa_menu_vendas();

    return 0;
}
