#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//ALUNO: RONALDO TAFAREL PEREIRA DE SOUZA
//RGM: 35043


struct cliente {
    char nome[20];
    char cpf[12];
    char rg[11];
    char telefone[12];
    char end[20];
    int id;//número do identificador do cliente
    int q_cont;//1- conta corrente, 2 - conta poupança ou 3 - ambas
}cli;

struct contc {
    float saldo;
    int chek;//máx 20
    int id_cheq[20]; //número identificador do cheque
    float valor_cheq[20];
    int uso_cheq[20];//0 não usou, 1 para usou
    int id;//identificador do cliente
}cc;

struct contp {
    float saldo;
    int id;//identificador do cliente
}cp;


//------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE JÁ EXISTE A ID DO USUSARIO
//PARAMETRO: O CONJUNTO DE CLIENTES E A QUANTIDADE
//RETORNO: 1 CASO EXISTA A ID E 0 CASO NN EXISTA
//------------------------------------------------------------------
int ver_id (struct cliente *usu, int q)
{
    int i;

    for(i=0;i<q;i++)
    {
        if (usu[i].id == usu[q+1].id)
        {
            return 1;
        }
    }

    return 0;

}

//------------------------------------------------------------------
//OBJETIVO: CADASTRAR UM CLIENTE
//PARAMETRO: O CONJUNTO DE CLIENTES E A QUANTIDADE
//RETORNO: A QUANTIDADE DE CLIENTES MAIS UM
//------------------------------------------------------------------
int cadastra (struct cliente *usu, int q)
{
    int op;

    printf("\n\tNOME: \n");
    fflush(stdin);
    fgets(usu[q].nome,20,stdin);
    printf("\n\tCPF: \n");
    fflush(stdin);
    fgets(usu[q].cpf,12,stdin);
    printf("\n\tRG: \n");
    fflush(stdin);
    fgets(usu[q].rg,11,stdin);
    printf("\n\tTELEFONE: \n");
    fflush(stdin);
    fgets(usu[q].telefone,12,stdin);
    printf("\n\tENDERECO: \n");
    fflush(stdin);
    fgets(usu[q].end,20,stdin);
    do{
        printf("\n\t QUAIS CONTAS DESEJA OBTER? \n");
        printf("\n\t 1 - CONTA CORRENTE \n");
        printf("\n\t 2 - CONTA POUPANCA \n");
        printf("\n\t 3 - AMBAS \n");
        fflush(stdin);
        scanf("%d",&usu[q].q_cont);
    }while(usu[q].q_cont<1 || usu[q].q_cont>3);

    srand(time(NULL));
    do{
        usu[q].id = rand()%1000 + 1;
    }while(ver_id(usu,q) == 1);
    //printf("\n-->%d<--",q);
    q = q+1;
    return (q);
}

//------------------------------------------------------------------
//OBJETVIO: INICIALIZAR O USO DE CHEQUE DO CLIENTE
//PARAMETRO: O CONJUNTO DE CONTAS CORRENTES E A QUANTIDADE
//------------------------------------------------------------------
void inicializa_chek (struct contc *c, int q)
{
    int i;

    for (i=0;i<20;i++)
    {
        c[q].uso_cheq[i] = 0;
    }
}

//------------------------------------------------------------------
//OBJETIVO: INICIALIZAR OS VALORES DA CONTA CORRENTE
//PARAMETRO: O CONJUNTO DE CADASTRO DO CLIENTE, SUA CONTA E A QUANTIDADE
//------------------------------------------------------------------
void inicia_cc(struct cliente *usu, struct contc *c, int q)
{
    q = q - 1;//como o q vai estar com 1 a mais pois o vetor conta de 0 a n-1, faz a decrementação
    //printf("%d <--", q);
    //system("pause");
    c[q].chek = 20;
    c[q].id = usu[q].id;
    c[q].saldo = 0;
    inicializa_chek(c, q);
    //printf(" --> %d", c[q].chek);

}

//------------------------------------------------------------------
//OBJETIVO: CARREGAR VALORES NA CONTA POUPANÇA
//PARAMETRO:  O CONJUNTO DE CADASTRO DE CLIENTES, A CONTA E QUANTIDADE
//------------------------------------------------------------------
void inicia_cp (struct cliente *usu, struct contp *c, int q)
{
    q = q-1;
    c[q].saldo = 0;
    c[q].id = usu[q].id;
}

//-------------------------------------------------------------------------------------
//OBJETIVO: VERIFICA SE A ID EXISTE NOS CADASTROS
//PARAMETRO: O CONJUNTO DE CADASTRO, A QUANTIDADE E O NUMERO DO ID
//RETORNO: -1 CASO NÃO HAJA CASO CONTRARIO RETORNA A POSICAO QUE SE ENCONTRA
//-------------------------------------------------------------------------------------
int verificaid(struct cliente c[], int q, int id)
{
    int i;
    printf("-->%d",q);
    system("pause");
    for (i=0;i<q;i++)
    {
        if (c[i].id==id)
        {
            printf("primeiro -- %d    %d",c[i].id,i);
            return i;
        }
    }
    return -1;
}

//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O SALDO DO CLIENTE
//PARAMETRO: A CONTA E A POSICAO QUE SE ENCONTRA
//-------------------------------------------------------------------------------
void mostrasaldo (struct contc cc[], int pos)
{
    printf("\n\t SALDO: %.2f\n",cc[pos].saldo);
}

//-------------------------------------------------------------------------------
//OBJETIVO: FAZER UM DEPOSITO PARA O CLIENTE
//PARAMETRO: CONTA E POSICAO
//-------------------------------------------------------------------------------
void fazerdeposito(struct contc *cc, int pos)
{
    float dep;

    do{
        printf("\n\tVALOR DO DEPOSITO: \n\t");
        scanf("%f",&dep);
        if (dep>1000 || dep+cc[pos].saldo>1000 || dep<0)
        {
            printf("\n\tSALDO MAXIMO: 1000 REAIS\n");
        }
    }while(dep>1000 || dep+cc[pos].saldo>1000 || dep<0);
    cc[pos].saldo += dep;

}

//-------------------------------------------------------------------------------
//OBJETIVO: FAZER UM SAQUE DO CLIENTE
//PARAMETRO: CONTA E POSICAO
//-------------------------------------------------------------------------------
void fazersaque (struct contc *cc, int pos)
{
    float saque;

    if (cc[pos].saldo>0){
        do{
            printf("\n\tDIGITE UM VALOR: \n\t");
            scanf("%f",&saque);
            if(saque<0 || saque>cc[pos].saldo)
            {
                printf("\n\tSAQUE INVÁLIDO!!\n");
            }
        }while(saque<0 || saque>cc[pos].saldo);
        printf("\n\tSAQUE EFETUADO COM SUCESSO\n");
        cc[pos].saldo = cc[pos].saldo - saque;
    }
    else
    {
        printf("\n\tSEM SALDO\n");
    }
}

//-------------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE EXISTE CHEQUE COM ESSE ID
//PARAMETRO: A CONTA, O NUMERO DE ID, A QUANTIDADE DE CHEQUES E A POSICAO
//-------------------------------------------------------------------------------
int verificachek(struct contc *cc, int id, int q,int pos)
{
    int i;

    for(i=0;i<q;i++)
    {
        if(cc[pos].id_cheq[i]==id)
        {
            return 1;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------
//OBJETIVO: FAZER UM CHEQUE
//PARAMETRO: A CONTA E A SUA POSICAO
//-------------------------------------------------------------------------------
void utilizarcheque(struct contc *cc, int pos)
{
    int q_chek=20;
    float valor;
    int id;

    if(cc[pos].chek>0){
        q_chek = q_chek - cc[pos].chek;
        do{
            id = rand()%10000+1;
        }while(verificachek(cc,id,q_chek,pos));
        cc[pos].id_cheq[q_chek] = id;
        do{
            printf("\n\tVALOR DO CHEQUE: ");
            scanf("%f",&valor);
            if (valor<0 || valor>1000)
            {
                printf("\n\tVALOR ENTRE 0 E 1000");
            }
        }while(valor<0 || valor>1000);
        cc[pos].chek = cc[pos].chek - 1;
        cc[pos].valor_cheq[q_chek] = valor;
    }
    else
    {
        printf("\n\tSEM CHEQUE!!\n");
    }


}

//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR FOLHA DE CHEQUES
//PARAMETRO: A CONTA E A SUA POSICAO
//-------------------------------------------------------------------------------
void consultafolha (struct contc cc[], int pos)
{
    int q=20,i;
    printf("%d",q);
    q = q - cc[pos].chek;
    printf("\n\tCHEQUES UTILIZADOS\n");
    for (i=0;i<q;i++)
    {
        printf("\n\t%d\t\t%.2f\n",cc[pos].id_cheq[i], cc[pos].valor_cheq[i]);
    }

}

//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O MENU DA CONTA CORRENTE
//PARAMETRO: A CONTA CORRENTE E SUA POSICAO
//-------------------------------------------------------------------------------
void contacorrente(struct contc *cc, int pos)
{
    int op;
    float saque;

    do{
        printf("\n\t1 - MOSTRAR SALDO\n");
        printf("\n\t2 - FAZER SAQUE\n");
        printf("\n\t3 - EFETUAR DEPOSITO\n");
        printf("\n\t4 - UTILIZAR CHEQUE\n");
        printf("\n\t5 - CONSULTAR LIMITE\n");
        printf("\n\t6 - CONSULTAR FOLHAS DE CHEQUE UTILIZADA\n");
        printf("\n\t7 - SAIR\n\t");
        scanf("%d",&op);
        if(op == 1)
        {
            mostrasaldo(cc,pos);
        }
        if(op==2)
        {
            fazersaque(cc,pos);
        }
        if (op==3)
        {
            fazerdeposito(cc, pos);
        }
        if (op==4)
        {
            utilizarcheque(cc,pos);
        }
        if (op == 5)
        {
            printf("\n\tLIMITE DE SALDO: 1000 REAIS");
        }
        if (op == 6)
        {
            consultafolha(cc,pos);
        }
    }while(op!=7);
}

//-------------------------------------------------------------------------------
//OBJETIVO: MOSTRAR O SALDO DO CLIENTE
//PARAMETRO: A CONTA E A POSICAO QUE SE ENCONTRA
//-------------------------------------------------------------------------------
void mostrasaldopou (struct contp cp[], int pos)
{
    printf("\n\t SALDO: %.2f\n",cp[pos].saldo);
}

//-------------------------------------------------------------------------------
//OBJETIVO: FAZER UM DEPOSITO PARA O CLIENTE
//PARAMETRO: CONTA E POSICAO
//-------------------------------------------------------------------------------
void fazerdepositopou(struct contp *cp, int pos)
{
    float dep;

    do{
        printf("\n\tVALOR DO DEPOSITO: \n\t");
        scanf("%f",&dep);
        if(dep<0)
        {
            printf("\n\tSALDO INDISPONÍVEL\n");
        }
    }while(dep<0);
    cp[pos].saldo += dep;

}

//-------------------------------------------------------------------------------
//OBJETIVO: FAZER UM SAQUE DO CLIENTE
//PARAMETRO: CONTA E POSICAO
//-------------------------------------------------------------------------------
void fazersaquepou (struct contp *cp, int pos)
{
    float saque;

    if (cp[pos].saldo>0){
        do{
            printf("\n\tDIGITE UM VALOR: \n\t");
            scanf("%f",&saque);
            if(saque<0 || saque>cp[pos].saldo)
            {
                printf("\n\tSAQUE INVÁLIDO!!\n");
            }
        }while(saque<0 || saque>cp[pos].saldo);
        printf("\n\tSAQUE EFETUADO COM SUCESSO\n");
        cp[pos].saldo = cp[pos].saldo - saque;
    }
    else
    {
        printf("\n\tSEM SALDO\n");
    }
}


//-------------------------------------------------------------------------------------
//OBJETIVO: FAZER CONSULTA NA CONTA POUPANÇA
//PARAMETRO: A CONTA POUPANCA E A SUA POSICAO
//-------------------------------------------------------------------------------------
void contapoupanca (struct contp *cp, int pos)
{
    int op;

    do{
        printf("\n\t1 - MOSTRAR SALDO\n");
        printf("\n\t2 - FAZER SAQUE\n");
        printf("\n\t3 - EFETUAR DEPOSITO\n");
        printf("\n\t4 - CONSULTAR LIMITE\n");
        printf("\n\t5 - SAIR\n\t");
        scanf("%d",&op);
        if(op==1)
        {
            mostrasaldopou(cp,pos);
        }
        if(op==2)
        {
            fazersaquepou(cp,pos);
        }
        if(op==3)
        {
            fazerdepositopou(cp,pos);
        }
        if(op==4)
        {
            printf("\n\tSEM LIMITES!!!");
        }
    }while(op!=5);
}

//-------------------------------------------------------------------------------------
//OBJETIVO: ENTRAR EM UMA CONTA
//PARAMETRO: O CONJUNTO DE USUARIO, AS CONTAS POUPANÇA E CORRENTE, E A QUANTIDADE
//-------------------------------------------------------------------------------------
void entrando(struct cliente usu[], struct contc *cc, struct contp *cp, int q)
{
    int id,pos,op;

    printf("\n\tDIGITE O NUMERO DO ID: ");
    scanf("%d",&id);
    if ((pos = verificaid(usu,q,id))>=0)
    {

        if(usu[pos].q_cont==1){
            contacorrente(cc,pos);
        }
        if (usu[pos].q_cont==2)
        {
            contapoupanca(cp,pos);
        }
        if(usu[pos].q_cont==3)
        {
            do{
                printf("\n\t1 - CONTA CORRENTE\n");
                printf("\n\t2 - POUPANCA");
                printf("\n\t3 - SAIR");
                scanf("%d",&op);
                if(op==1){
                    contacorrente(cc,pos);
                }
                if (op==2)
                {
                    contapoupanca(cp,pos);
                }
            }while(op!=3);
        }

    }
    else
    {
        printf("\n\tNÃO EXISTE!!!!\n");
    }
}


//------------------------------------------------------------------
//OBJETIVO: MOSTRAR A ID DOS CLIENTES
//PARAMETRO: O CONJUNTO DE CADASTROS E O NÚMERO TOTAL
//------------------------------------------------------------------
void mostraid (struct cliente c[], int q)
{
    int i;

    printf("\n\t\tID'S");
    for(i=0;i<q;i++)
    {
        printf("\n\t %d ----- %d",i+1,c[i].id);
    }
    printf("\n\n");
}

int main()
{
    char op;
    struct cliente clientes[40];
    struct contc contac[40];
    struct contp contap[40];
    int q_cli=0;

    do{
        printf("\n\t 1 - CADASTRAR CLIENTE\n");
        printf("\n\t 2 - ENTRAR\n");
        printf("\n\t 3 - MOSTRAR ID DOS CLIENTES\n");
        printf("\n\t 4 - SAIR\n\t");
        fflush(stdin);
        scanf("%c",&op);
        //analisa a opcao escolhida pelo usuario
        if (op == '1')
        {
            q_cli = cadastra(clientes, q_cli);
            if (clientes[q_cli-1].q_cont == 1)
            {
                inicia_cc(clientes, contac, q_cli);
            }
            if (clientes[q_cli-1].q_cont == 2)
            {
                inicia_cp(clientes, contap, q_cli);
            }
            if (clientes[q_cli-1].q_cont == 3)
            {
                inicia_cc(clientes, contac, q_cli);
                inicia_cp(clientes, contap, q_cli);
            }
        }
        //printf("%s",clientes[0].nome);
        //printf("%d   %d    %d",clientes[0].id,clientes[1].id,clientes[2].id);
        //printf("\n\n\tQUANTIDADE DE CLIENTES   --> %d",q_cli);
        //printf("\n%.2f     %d\n",contap[0].saldo, contap[0].id);
        //printf("\n%.2f     %d      %d",contac[0].saldo, contac[0].id, contac[0].chek);
        if (op == '2')
        {
            entrando(clientes,contac,contap,q_cli);
        }

        if(op == '3')
        {
            mostraid(clientes, q_cli);
        }



    }while(op!='4');
    return 0;
}
