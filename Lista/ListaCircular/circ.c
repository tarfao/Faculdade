#include "gfx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

typedef struct lista {
    int info;
    struct lista *prox;
}lista;


void DesenhaSeta (int pos)
{
    int increase;
    increase = 64*pos;

    gfx_line(70+increase, 43, 70+increase,33);
    gfx_line(70+increase, 43, 70+increase+3, 43-3); 
    gfx_line(70+increase, 43, 70+increase-3, 43-3);
    gfx_paint();
    sleep(2);
}

void desenhaNo (lista *c)
{
    lista *pt=c;
    int increase=0;
    char convert[10];
    

    while(pt->prox!=c){
       gfx_set_color(255,0,0);
       gfx_rectangle(50+increase,50,95+increase,70);
       gfx_line(88+increase,50,88+increase,70);
       /*DESENHA A SETA*/
       gfx_line(95+increase,60,(95+increase)+15,60);
       gfx_line((95+increase)+10,55,(95+increase)+15,60);
       gfx_line((95+increase)+10,65,(95+increase)+15,60);
       /*IMPRIME O NÚMERO*/
       sprintf(convert,"%d",pt->info);
       gfx_text(53+increase,53,convert);
       increase += 64;  
       pt = pt->prox;
       /*sleep(1);*/
    }
    /*DESENHA O ÚLTIMO NÓ DA LISTA*/
    pt = pt->prox;
    gfx_set_color(255,0,0);
    gfx_rectangle(50+increase,50,95+increase,70);
    gfx_line(88+increase,50,88+increase,70);
    sprintf(convert,"%d",pt->info);
    gfx_text(53+increase,53,convert);

}

void imprime(lista *p)
{
    lista *pt;
    
    pt=p;

    if(pt!=NULL){
       while (pt->prox != p)
       {
          printf(" %d ",pt->info);
          pt = pt->prox;
       }
       printf(" %d ",pt->info);
    }
        
    
}

/*----------------------------------------------------------------------------
OBJETIVO: PROCURAR O NÓ ANTERIOR DO NOVO NÓ QUE SERÁ ALOCADO
PARAMETRO: O PONTEIRO INICIAL DA LISTA, E O NÚMERO PARA PROCURAR
RETORNO: O NÓ ANTERIOR AO NOVO QUE SERÁ INSERIDO
-----------------------------------------------------------------------------*/
lista *BuscaNo_Circ(lista *ptlista, int n, int *pos)
{
    lista *pt=ptlista;
    lista *no=ptlista;
    *pos = 0 ;

    while (pt->prox != ptlista)
    {
        if(pt->info < n)
        {
            *pos = *pos+1;
            no=pt;
            pt=pt->prox;
        }
        else
            return no; 
    }
    
    return no;

}

/*----------------------------------------------------------------------------
OBJETIVO: INSERIR UM NOVO NÓ NA LISTA ORDENADA
PARAMETRO: O PONTEIRO INICIAL DA LISTA, E O NOVO NUMERO QUE DESEJA COLOCAR
RETORNO: A LISTA ATUALIZADA
-----------------------------------------------------------------------------*/
lista *InsereCirc (lista *ptlista, int n)
{
    lista *novo;
    lista *no=NULL;  //Recebe o nó anterior do novo nó
    lista *aux=NULL; //
    int a;//auxilia na troca de valores
    int pos;

    if((novo=malloc(sizeof(lista))) != NULL)
    {
        novo->info = n;
        novo->prox = NULL;
        if(ptlista == NULL)
        {
            ptlista = novo;
            novo->prox = novo;
            printf("\nInseriu o primeiro\n");
        }
        else
        {
            no = BuscaNo_Circ(ptlista,n,&pos);
            if(no==ptlista)
            {
                if(no->info > n)
                {
                    //troca os valores
                    a = novo->info;
                    novo->info = ptlista->info;
                    ptlista->info = a;                    
                    /*MUDA OS PONTEIROS*/
                    novo->prox = ptlista->prox;
                    ptlista->prox = novo;
                }
                else
                {
                	aux = no->prox;
                	if(aux->info > n){
                    	novo->prox = no->prox;
                    	no->prox = novo;
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
                /*IMPLEMENTAÇÃO DO CASO O NÓ RECEBIDO NÃO FOR O PRIMEIRO (MAIS COMPLICADO)*/           
                 aux = no;
                 no = no->prox;
                 if (n < no->info)
                 {
                     novo->prox = aux->prox;
                     aux->prox = novo;     
                 }
                 else
                 {
                        novo->prox = no->prox;
                        no->prox = novo;                       
                 }             
                
            }           
        }
    }
    return ptlista;
}

lista *remov_Circ(lista *c, int n)
{
    /*lista *r; IRÁ OBTER O ENDEREÇO DE ONDE SERÁ DESALOCADO O NÓ*/
    lista *aux;/*IRÁ OBTER O ENDEREÇO QUE O ELEMENTO A SER REMOVIDO ESTÁ*/
    lista *proxAux; /*IRÁ OBTER O PROXIMO NÓ DO AUX*/
    int a;
    int pos; //obtem a posicao do nó (obs: nao sera utilizado nessa funcao)
    
    if(c!=NULL)
    {
        aux = BuscaNo_Circ(c,n,&pos);
        
        if(aux->info == n)/*VERIFICA SE É O ÚNICO ELEMENTO DA LISTA*/
        {
        	if(aux->prox != c)
        	{
        		/*faço a troca de valores para nao alterar o endereçamento do último nó e passo o 
        		nó que vai ser deletado para o próximo*/
        		a = aux->prox->info;
        		aux->prox->info = c->info;
        		c->info = a;
        		/*agora mudo o aux porque os valores foram trocados*/
        		aux = c->prox;
        		c->prox = aux->prox;
        		free(aux);
        	}
        	else
        	{
	            free(c);
	            return NULL;
	        }
        }
        else/*CASO O NÚMERO NAO SEJA O ÚNICO DA LISTA*/
        {
            proxAux = aux->prox;
            if(proxAux->info == n){/*COMO O BuscaN_Circ  RETORNA UM ANTES, ELE PODE RETORNAR O PRIMEIRO CASO FOR O PROCURADO FAZ VERIFICAÇÃO SE É O PRIMEIRO*/
                aux->prox = proxAux->prox;
                free(proxAux);
            }
            else/*SE NÃO FOR O PRIMEIRO, O NÓ RETORNADO PODE TAMBÉM NÃO SER O PRIMEIRO PODERÁ SER O SEGUNDO OU UM OUTRO DA LISTA, ENTÃO AVANÇAMOS UMA CASA QUE SERÁ O ÚLTIMO NÓ PARA VERIFICARMOS*/  
            {
                    printf("\nELEMENTO NAO ESTA CONTIDO\n"); 
            }
        }
    }
    else
        printf("\nNAO POSSUI ELEMENTOS NA LISTA\n"); 

    return c;
}

/*-------------------------------------------------------------------------------------
OBJETIVO: BUSCAR UM NUMERO NA LISTA CIRCULAR PARA O USUARIO
PARAMETRO: A LISTA E O NUMERO
--------------------------------------------------------------------------------------*/
void buscaCirc(lista *pt, int x)
{
	lista *ant;/*RECEBE O NÓ DA BUSCA*/
	int pos;/*VAI OBTER A POSICAO PARA PRINTAR UMA SETA COM A GFX*/

	if(pt!=NULL)
	{
		ant = BuscaNo_Circ(pt,x,&pos);

		if(ant==pt)
		{
			if(ant->info == x)/*caso a lista tiver só um nó, ou caso ele for o primeiro mesmo*/
			{
				DesenhaSeta(pos);
			}
			else
			{
				ant=ant->prox;/*verifica se retornou o anterior, entao avanço */
				pos++;/*incrementa o pos também pois avancou um nó*/
				if(ant->info == x)
				{
					DesenhaSeta(pos);
				}
				else
					printf("\nO ELEMENTO NAO ESTA NA LISTA");
			}
		}
		else
		{
			ant=ant->prox;
			pos++;
			if(ant->info==x)
				DesenhaSeta(pos);
			else
				printf("\nO ELEMENTO NAO ESTA NA LISTA");
		}
	}else{
		printf("\nNAO HA ELEMENTOS NA LISTA");
	}
}

/*-------------------------------------------------------------------------------------
OBJETIVO: DESALOCAR A LISTA CIRCULAR
PARAMETRO: A LISTA E O NUMERO
--------------------------------------------------------------------------------------*/
void Desaloca_Circ (lista *ptl)
{

}

int main()
{
    lista *ptlista=NULL;
    int op;
    int x;

   /* do{
    	gfx_init(800,200,"------>LISTA<-------");
        printf("\n[1] - INSERIR\n");
        printf("\n[2] - REMOVER\n");
        printf("\n[3] - BUSCAR\n");
        printf("\n[4] - SAIR\n");
        scanf("%d",&op);
        
        switch(op){
            case 1:
                printf("\nVALOR: ");    
                scanf("%d",&x);
                ptlista = InsereCirc(ptlista,x);
                gfx_clear(); 
                desenhaNo(ptlista);
            break;

            case 2:
                printf("\nVALOR: ");    
                scanf("%d",&x);
                ptlista = remov_Circ(ptlista,x);
                gfx_clear(); 
                desenhaNo(ptlista);
            break;

            case 3:
            	if(ptlista!=NULL)
            	{
            		printf("\nVALOR: ");    
                	scanf("%d",&x);
            		buscaCirc(ptlista,x);
            		gfx_clear();
            		desenhaNo(ptlista);
            	}
            break;
        }
        gfx_paint();
    }while(op!=4);*/
    do
    {
        gfx_init(800,200,"------>LISTA<-------");
        printf("\n------------------LISTA DUPLAMENTE ENCADEADA------------------\n");
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
                    printf("\nVALOR: ");    
                    scanf("%d",&x);
                    buscaCirc(ptlista,x);
                    gfx_clear();
                    desenhaNo(ptlista);
                }
                else
                    printf("\n--------------SEM ELEMENTOS NA LISTA-------------\n");
            break;

            case 'b':
                printf("\nVALOR: ");    
                scanf("%d",&x);
                ptlista = InsereCirc(ptlista,x);
                gfx_clear(); 
                desenhaNo(ptlista);
             break;

            case 'c':
                if(ptlista!=NULL){
                    printf("\nVALOR: ");    
                    scanf("%d",&x);
                    ptlista = remov_Circ(ptlista,x);
                    gfx_clear(); 
                    desenhaNo(ptlista);
                }
                else
                    printf("\n--------------SEM ELEMENTOS NA LISTA-------------\n");
             break;
        }
            gfx_paint();
    }while(op!='d');

    return 0;
}
