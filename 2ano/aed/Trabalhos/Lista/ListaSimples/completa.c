#include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>

typedef struct lista {
    int info;  
    struct lista *prox;
}lista;

void DesenhaSeta(int pos)
{
    int increase;
    increase = 64*pos;

    gfx_line(70+increase, 43, 70+increase,33);
    gfx_line(70+increase, 43, 70+increase+3, 43-3); 
    gfx_line(70+increase, 43, 70+increase-3, 43-3);
    gfx_paint();
    sleep(2);
}

/*--------------------------------------------------------------------------
OBJETIVO: DESENHAR OS NOS DA LISTA SIMPLESMENTE ENCADEADA
PARAMETRO: A LISTA
---------------------------------------------------------------------------*/
void desenhaNo_Simp(lista *c)
{
    int increase=0;
    char convert[10];
    

    while(c!=NULL){
       gfx_set_color(255,0,0);
       gfx_rectangle(50+increase,50,95+increase,70);
       gfx_line(88+increase,50,88+increase,70);
       if(c->prox!=NULL){
            gfx_line(95+increase,60,(95+increase)+15,60);
            gfx_line((95+increase)+10,55,(95+increase)+15,60);
            gfx_line((95+increase)+10,65,(95+increase)+15,60);
       }
       sprintf(convert,"%d",c->info);
       gfx_text(53+increase,53,convert);
       increase += 64;  
       c = c->prox;
       /*sleep(1);*/
    }

}



/*------------------------------------------------------------------------------
OBJETIVO: BUSCAR O NÓ ANTERIOR A UM NÚMERO DADO EM UMA LISTA ORDENADA
PARAMETRO: O PRIMEIRO NÓ DA LISTA E O NUMERO A SER PROCURADO
RETORNO: O NÓ ANTERIOR (SERÁ RETORNADO SOMENTE O NÓ CORRENPONDENTE EM CASO DE O 
PRIMEIRO NÓ FOR O MAIOR EM RELACAO AO n, OU A LISTA SÓ TER UM NUMERO)
-------------------------------------------------------------------------------*/ 
lista *BuscaNo_Simp(lista *c, int n, int *pos)
{
    lista *l, *aux=c;
    *pos = 0;
    l = c;
    
    while (l->prox != NULL)
    {
        if(l->info < n){ 
            *pos=*pos+1;
            aux = l;           
            l = l->prox;
        }
        else{
            return aux;
        }
    }
    return aux;
}


/*---------------------------------------------------------------------------
OBJETIVO: INSERIR UM NUMERO NA LISTA ORDENADA SIMPLESMENTE ENCADEADA
PARAMETRO: O PRIMEIRO NÓ DA LISTA, E O NÚMERO QUE IRÁ INSERIR
RETORNO: A LISTA ALTERADA
----------------------------------------------------------------------------*/
lista *InsereOrdenado_Simp (lista *c, int n)
{
   lista *novo; /*PARA FAZER A ALOCAÇÃO DE UM NOVO NÓ*/
   lista *l;    /*PARA PERCORRER A LISTA COM SEM PERDER O INÍCIO*/
   lista *aux;  /*PARA RECEBER O NÓ ANTERIOR AO QUE VAI SER INSERIDO*/
   lista *aux1; /*PARA FAZER VERIFICAÇÃO DO PROXIMO DO NÓ RECEBIDO SEM PERDER-LO*/
   int pos;/*obtem a posicao do no(obs: nao utilizado nessa funcao)*/

   l=c;
           
   if(c==NULL){/*CASO NAO HAJA NUMERO NA LISTA, NAO VERIFICA NADA E FAZ INSERÇÃO*/
       c = malloc(sizeof(lista));
       c->info = n;
       c->prox = NULL;
   }
   else/*CASO HAJA PELO MENOS UM NUMERO NA LISTA FAZEMOS BUSCA*/
   {
        if ( (novo = malloc(sizeof(lista))) != NULL)/*FAZ A ALOCAÇÃO E VERIFICA SE FOI REALIZADA COM SUCESSO PARA DAR CONTINUIDADE AO PROGRAMA*/
        {                   
            novo->info = n;        
               
            aux = BuscaNo_Simp(l,n,&pos);
                    
            aux1 = aux->prox; 
                    
            
            if(aux == c)/*CASO DE O NÓ RECEBIDO FOR O PRIMEIRO*/
            {
                if(n < aux->info)/*VERIFICA SE O PRIMEIRO NÓ RECEBIDO É O MAIOR*/
                {
                    printf ("\nIgual ant");
                    novo->prox = c;
                    c = novo;
                }
                else
                {
                    if(aux1 != NULL)/*CASO DE TER MAIS DE UM NÓ NA LISTA*/
                    {
                        if(aux1->info < n){/*SE NÃO FOR NULO, VERIFICA SE ELE É O MAOR OU MENOR*/                            
                            printf ("\nIgual dps");
                            novo->prox = aux1->prox;
                            aux1->prox = novo;
                        }
                        else{
                            novo->prox = aux->prox;
                            aux->prox = novo;
                        }  
                    }
                    else
                    {
                        /*CASO DE TER SÓ UM NÓ NA LISTA*/
                         if(aux->info < n){                            
                             printf ("\nIgual dps");
                             novo->prox = aux->prox;
                             aux->prox = novo;
                         }
                         else{
                             novo->prox = aux->prox;
                             aux->prox = novo;
                         }
                    }
                                
                 }   
             }
             else/*CASO O NÓ NÃO FOR O PRIMEIRO*/
             {
                                            
                
                if(n > aux1->info)
                {                         
                    printf ("\núltimo prox");
                    aux=aux->prox;
                    novo->prox = aux->prox;
                    aux->prox = novo;                            
                }
                else
                {
                    novo->prox = aux->prox;
                    aux->prox = novo;
                }
             }
         }
         else
         {
             printf("\n\tNAO ALOCADO!!");
         }
   }
   return c;
}


/*---------------------------------------------------------------------------
OBJETIVO: REMOVER O NÚMERO DA LISTA ORDENADA REALIZANDO BUSCA
PARAMETRO: O PRIMEIRO NÓ DA LISTA, E O NÚMERO QUE DESEJA REMOVER
RETORNO: A LISTA ALTERADA
----------------------------------------------------------------------------*/
lista *remov(lista *c, int n)
{
    lista *r; /*IRÁ OBTER O ENDEREÇO DE ONDE SERÁ DESALOCADO O NÓ*/
    lista *aux; /*IRÁ OBTER O ENDEREÇO QUE O ELEMENTO A SER REMOVIDO ESTÁ*/
    int pos; /*obtem a posicao do nó (obs: nao sera utilizado nessa funcao)*/
    
    /*if(c!=NULL)
    {*/
        aux = BuscaNo_Simp(c,n,&pos);
        
        if(aux->prox == NULL)/*VERIFICA SE É O ÚNICO ELEMENTO DA LISTA*/
        {
            if(aux->info == n){/*CASO AFIRMATIVO VERIFICA SE É O NUMERO DESEJADO E DESALOCA*/
                free(c);
                c = NULL;
            }
            else
                printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
        }
        else/*CASO O NÚMERO NAO SEJA O ÚNICO DA LISTA*/
        {
            if(aux->info == n){/*COMO O BuscaNo RETORNA UM ANTES, ELE PODE RETORNAR O PRIMEIRO CASO FOR O PROCURADO FAZ VERIFICAÇÃO SE É O PRIMEIRO*/
                c = c->prox;
                free(aux);
            }
            else/*SE NÃO FOR O PRIMEIRO, O NÓ RETORNADO PODE TAMBÉM NÃO SER O PRIMEIRO PODERÁ SER O SEGUNDO OU UM OUTRO DA LISTA, ENTÃO AVANÇAMOS UMA CASA QUE SERÁ O ÚLTIMO NÓ PARA VERIFICARMOS*/  
            {
                r = aux->prox;/*OBTEMOS O ENDEREÇO MESMO SEM VERIFICAR SE É O NUMERO PROCURADO*/
                if(r->info == n)/*SE FOR O NUMERO PROCURADO FAZEMOS O PROXIMO DO ANTERIOR APONTAR PRO PROXIMO DO EXCLUIDO E DESALOCAMOS*/
                {
                    aux->prox = r->prox;
                    free(r);
                }
                else
                    printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
            }
        }
    /*}
    else
        printf("\nNAO POSSUI ELEMENTOS NA LISTA\n"); */

    return c;
}

/*---------------------------------------------------------------
OBJETIVO: BUSCAR UM NÓ ESPECÍFICO NA LISTA COM O NÚMERO n
PARAMETRO: O PONTEIRO INICIAL DA LISTA E O NUMERO
---------------------------------------------------------------*/
void Busca(lista *pt, int n)
{
    lista *aux;
    int pos;/*obtem a posicao do no;*/


    gfx_clear();    
    desenhaNo_Simp(pt);
    /*if(pt!=NULL)
    {*/
        aux = BuscaNo_Simp(pt,n,&pos);
        
        if(aux->prox == NULL)/*VERIFICA SE É O ÚNICO ELEMENTO DA LISTA*/
        {
            if(aux->info == n){/*CASO AFIRMATIVO VERIFICA SE É O NUMERO DESEJADO E DESALOCA*/
                DesenhaSeta(pos);
            }
            else
                printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
        }
        else/*CASO O NÚMERO NAO SEJA O ÚNICO DA LISTA*/
        {
            if(aux->info == n){/*COMO O BuscaNo RETORNA UM ANTES, ELE PODE RETORNAR O PRIMEIRO CASO FOR O PROCURADO FAZ VERIFICAÇÃO SE É O PRIMEIRO*/
                DesenhaSeta(pos);
            }
            else/*SE NÃO FOR O PRIMEIRO, O NÓ RETORNADO PODE TAMBÉM NÃO SER O PRIMEIRO PODERÁ SER O SEGUNDO OU UM OUTRO DA LISTA, ENTÃO AVANÇAMOS UMA CASA QUE SERÁ O ÚLTIMO NÓ PARA VERIFICARMOS*/  
            {
                aux = aux->prox;/*OBTEMOS O ENDEREÇO MESMO SEM VERIFICAR SE É O NUMERO PROCURADO*/
                if(aux->info == n)/*SE FOR O NUMERO PROCURADO FAZEMOS O PROXIMO DO ANTERIOR APONTAR PRO PROXIMO DO EXCLUIDO E DESALOCAMOS*/
                {
                    DesenhaSeta(pos);
                }
                else
                    printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
            }
        }
   /* }
    else
        printf("\nNAO POSSUI ELEMENTOS NA LISTA\n");*/
    printf("\n%d\n",pos); 
    gfx_paint();
    
    

}

/*----------------------------------------------------------------
OBJETIVO: DESALOCAR A LISTA ENCADEADA SIMPLES
PARAMETROS: O PONTEIRO DA LISTA
-----------------------------------------------------------------*/
void Desaloca_Simp(lista *ptl)
{
    lista *aux;/*AUXILIA QUANDO FOR DESALOCAR*/

    while(ptl!=NULL){
        aux=ptl;
        ptl = ptl->prox;
        free(aux);
    }
}
        
int main () {
    lista *ptlista=NULL;/*PONTEIRO PARA A LISTA*/
    char op;/*OBTEM A OPCAO DO MENU*/
    int n;/*OBTEM O NUMERO PARA INSERIR, BUSCAR OU REMOVER*/

    do
    {
        gfx_init(800,200,"------>LISTA SIMPLESMENTE ENCADEADA<-------");
        printf("\n------------------OPERACOES------------------\n");
        printf("\ta) BUSCA DE ELEMENTO;\n");
        printf("\tb) INSERCAO DE ELEMENTO;\n");
        printf("\tc) REMOCAO DE ELEMENTO;\n");
        printf("\td) SAIR;\n\t");
        scanf("%c",&op);
        __fpurge(stdin);
        switch(op)
        {
            case 'a':
                if(ptlista!=NULL)
                {
                    printf ("\nNUMERO: ");
                    scanf("%d",&n);
                    __fpurge(stdin);
                    Busca(ptlista,n);
                    gfx_clear();    
                    desenhaNo_Simp(ptlista);
                    gfx_paint();
                }
                else
                    printf("\n----------------SEM ELEMENTOS NA LISTA--------------------\n");
            break;

            case 'b':
                printf ("\nNUMERO: ");
                scanf("%d",&n);
                __fpurge(stdin);
                ptlista = InsereOrdenado_Simp(ptlista,n);
                gfx_clear();
                desenhaNo_Simp(ptlista);
                gfx_paint();
            break;

            case 'c':
                if(ptlista!=NULL)
                {
                    printf ("\nNUMERO: ");
                    scanf("%d",&n);
                    __fpurge(stdin);
                    ptlista = remov(ptlista,n);
                    gfx_clear();
                    desenhaNo_Simp(ptlista);
                    gfx_paint();
                }
                else
                    printf("\n------------------SEM ELEMENTOS NA LISTA-----------------\n");
            break;
        }
    }while(op!='d');
    Desaloca_Simp(ptlista);
    gfx_quit();

    
    
    return 0;
}
