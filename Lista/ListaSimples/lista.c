#include "gfx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct lista {
    int info;  
    struct lista *prox;
}lista;

void desenhaNo (lista *c)
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
       increase += 70;  
       c = c->prox;
       gfx_paint();
       /*sleep(1);*/
    }

}
/*---------------------------------------------------------------------------
OBJETIVO: IMPRIMIR UMA LISTA NA ORDEM 
PARAMETRO: **p, QUE É O PONTEIRO PARA O PONTEIRO DA LISTA
-----------------------------------------------------------------------------*/
void imprimen(lista *p)
{
    printf ("[");
    while(p != NULL)
    {
	    printf(" %d",p->info);
	    p = p->prox;
    }
    printf (" ]\n");
}


/*------------------------------------------------------------------------------
OBJETIVO: BUSCAR O NÓ COM O NUMERO MAIOR OU IGUAL AO PROCURADO
PARAMETRO: O PRIMEIRO NÓ DA LISTA E O NUMERO A SER PROCURADO
RETORNO: O NÓ ANTERIOR (SERÁ RETORNADO SOMENTE O NÓ CORRENPONDENTE EM CASO DE O 
PRIMEIRO NÓ FOR O MAIOR EM RELACAO AO n, OU A LISTA SÓ TER UM NUMERO)
-------------------------------------------------------------------------------*/ 
lista *BuscaNo (lista *c, int n, int *k)
{
    *k=0;
    lista *l, *aux=c;
    l = c;
    
    while (l != NULL)
    {
        if(l->info < n){ 
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
OBJETIVO: INSERIR UM NUMERO NA LISTA ORDENADA
PARAMETRO: O PRIMEIRO NÓ DA LISTA, E O NÚMERO QUE IRÁ INSERIR
RETORNO: A LISTA ALTERADA
----------------------------------------------------------------------------*/
lista *InsereOrdenado (lista *c, int n)
{
   lista *novo; /*PARA FAZER A ALOCAÇÃO DE UM NOVO NÓ*/
   lista *l;    /*PARA PERCORRER A LISTA COM SEM PERDER O INÍCIO*/
   lista *aux;  /*PARA RECEBER O NÓ ANTERIOR AO QUE VAI SER INSERIDO*/
   //lista *aux1; /*PARA FAZER VERIFICAÇÃO DO PROXIMO DO NÓ RECEBIDO SEM PERDER-LO*/
   int p;

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
               
            aux = BuscaNo(l,n,&p);
                    
            //aux1 = aux->prox
            if (aux==c)
            {
                if(c->info < n)
                {
                    novo->prox = c->prox;
                    c->prox = novo;
                }
                else
                {
                    novo->prox = c;
                    c = novo;
                }
            }
            else
            {
                aux->prox = novo->prox;
                novo->prox = novo;
            } 
                    
            
            /*if(aux == c)//CASO DE O NÓ RECEBIDO FOR O PRIMEIRO
            {
                if(n < aux->info)//VERIFICA SE O PRIMEIRO NÓ RECEBIDO É O MAIOR
                {
                    printf ("\nIgual ant");
                    novo->prox = c;
                    c = novo;
                }
                else
                {
                    if(aux1 != NULL)//CASO DE TER MAIS DE UM NÓ NA LISTA
                    {
                        if(aux1->info < n){//SE NÃO FOR NULO, VERIFICA SE ELE É O MAOR OU MENOR                           
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
                         //CASO DE TER SÓ UM NÓ NA LISTA
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
             else//CASO O NÓ NÃO FOR O PRIMEIRO
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
             }*/
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
    int p;

    if(c!=NULL){    
        aux = BuscaNo(c,n,&p);
        
        if(aux->prox == NULL)/*VERIFICA SE É O ÚNICO ELEMENTO DA LISTA*/
        {
            if(aux->info == n){/*CASO AFIRMATIVO VERIFICA SE É O NUMERO DESEJADO E DESALOCA*/
                free(aux);
                c = NULL;
            }
            else
                printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
        }
        else/*CASO O NÚMERO NAO SEJA O ÚNICO DA LISTA*/
        {
            aux = aux->prox;
            if(aux->info == n){/*COMO O BuscaNo RETORNA UM ANTES, ELE PODE RETORNAR O PRIMEIRO CASO FOR O PROCURADO FAZ VERIFICAÇÃO SE É O PRIMEIRO*/
                c = c->prox;
                free(aux);
            }
            else/*SE NÃO FOR O PRIMEIRO, O NÓ RETORNADO PODE TAMBÉM NÃO SER O PRIMEIRO PODERÁ SER O SEGUNDO OU UM OUTRO DA LISTA, ENTÃO AVANÇAMOS UMA CASA QUE SERÁ O ÚLTIMO NÓ PARA VERIFICARMOS*/  
            {
                /*r = aux->prox;//OBTEMOS O ENDEREÇO MESMO SEM VERIFICAR SE É O NUMERO PROCURADO
                if(r->info == n)//SE FOR O NUMERO PROCURADO FAZEMOS O PROXIMO DO ANTERIOR APONTAR PRO PROXIMO DO EXCLUIDO E DESALOCAMOS
                {
                    aux->prox = r->prox;
                    free(r);
                }
                else
                    printf("\nELEMENTO NAO ESTA CONTIDO\n"); */
                printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
            }
        }
    }
    else
        printf("\nELEMENTO NAO ESTA CONTIDO\n");    
    return c;
}

        
int main () {
    lista *p=NULL, *s;
    int op,n;
    
    do{
        gfx_init(800,200,"------>LISTA<-------");
        printf("\n[1] - ADICIONA");
        printf("\n[2] - REMOVE: ");
        printf("\n[3] - SAIR: ");
        scanf("%d",&op);    
        
        switch(op){
            case 1:
                printf ("\nNUMERO: ");
                scanf("%d",&n);
                p = InsereOrdenado(p,n);
                gfx_clear();
                desenhaNo(p);
            break;

            case 2:
                printf ("\nNUMERO: ");
                scanf("%d",&n);
                p = remov(p,n);
                gfx_clear();
                desenhaNo(p);
            break;

            case 3:
                
            break;
        }
    }while(op!=3);

    while(p!=NULL){
        s=p;
        p = p->prox;
        free(s);
    }

    gfx_quit();

    
    
    return 0;
}
