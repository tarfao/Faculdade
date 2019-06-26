#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include <unistd.h>
#include <stdio_ext.h>
/*ESTRUTURA PARA LISTA SIMPLESMENTE ENCADEADA
E A LISTA CIRCULAR*/
typedef struct lista {
    int info;  
    struct lista *prox;
}lista;

/*ESTRUTURA PARA A LISTA DUPLAMENTE ENCADEADA COM NO CABEÇA*/
typedef struct lista_Dupla{
	int info;
	struct lista_Dupla *prox;
	struct lista_Dupla *ant;
}ListDup;


/*-------------------------------------------------------------------------
DESENHAR A SETA PARA IDENTIFICAR UM NUMERO BUSCADO PELO USUARIO
PARAMETRO: A POSICAO QUE O ELEMENTO ESTA
----------------------------------------------------------------------------*/
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
        
void Lista_simp() {
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
}

/*--------------------------------------------------------------------------
OBJETIVO: DESENHAR OS NOS DA LISTA CIRCULAR
PARAMETRO: A LISTA
---------------------------------------------------------------------------*/
void desenhaNo_Circ(lista *c)
{
    lista *pt=c;
    int increase=0;
    char convert[10];
    

    while(pt->prox!=c){
       /*DESENHA O NO*/
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
    gfx_set_color(255,0,0);
    gfx_rectangle(50+increase,50,95+increase,70);
    gfx_line(88+increase,50,88+increase,70);
    sprintf(convert,"%d",pt->info);
    gfx_text(53+increase,53,convert);

    /*DESENHA A LINHA SAINDO DO ÚLTIMO NO E INDO PARA O PRIMEIRO*/
    gfx_line((95+increase)-1, 70,(95+increase)-1,80);/*DIMINUO 1 DO ULTIMO QUE DESENHOUPRA AJUSTAR NO RETANGULO PONTEIRO, E DESCO A LINHA 3 PIXELS*/
    gfx_line((95+increase)-1, 80,52,80);/*O PRIMEIRO NO FOI FEITO NO X=50, E AUMENTEI 2 PIXELS PARA QUE A SETA NAO FIQUE NO FINAL DO NO*/
    gfx_line(52,80,52,72);/*O PRIMEIRO NO FOI FEITO NO X=50, E AUMENTEI 2 PIXELS PARA QUE A SETA NAO FIQUE NO FINAL DO NO*/
    /*DESENHANDO A SETA*/
    gfx_line(52,72,55,75);
    gfx_line(52,72,48,75);

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
OBJETIVO: BUSCAR UM NUMERO NA LISTA PARA O USUARIO
PARAMETRO: A LISTA E O NUMERO
--------------------------------------------------------------------------------------*/
void buscaCirc(lista *pt, int x)
{
	lista *ant;/*RECEBE O NÓ DA BUSCA*/
	int pos;/*VAI OBTER A POSICAO PARA PRINTAR UMA SETA COM A GFX*/

    gfx_clear();
    desenhaNo_Circ(pt);
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
    lista *aux=ptl->prox;/*VAI RECEBER O PRIMEIRO NO DA LISTA PARA CAMINHAR NA LISTA*/
    lista *aux2; /*VAI AUXILIAR QUANDO FOR DESALOCAR OS NÓS*/
	if(ptl->prox == ptl)
	{
		free(ptl);
	}
	else
	{
	    while(aux->prox != ptl)
	    {
	        aux2=aux;
	        aux=aux->prox;
	        free(aux2);
	    }
	    free(aux);
	    free(ptl);
	}
    

}


void Lista_Circ()
{
    lista *ptlista=NULL;
    char op;
    int x;

    do
    {
        gfx_init(800,200,"------------------LISTA CIRUCLAR ENCADEADA------------------");
        printf("\n-----------------OPERACOES------------------\n");
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
                    __fpurge(stdin);
                    buscaCirc(ptlista,x);
                    gfx_clear();
                    desenhaNo_Circ(ptlista);
                }
                else
                    printf("\n--------------SEM ELEMENTOS NA LISTA-------------\n");
            break;

            case 'b':
                printf("\nVALOR: ");    
                scanf("%d",&x);
                __fpurge(stdin);
                ptlista = InsereCirc(ptlista,x);
                gfx_clear(); 
                desenhaNo_Circ(ptlista);
             break;

            case 'c':
                if(ptlista!=NULL){
                    printf("\nVALOR: ");    
                    scanf("%d",&x);
                    __fpurge(stdin);
                    ptlista = remov_Circ(ptlista,x);
                    if(ptlista!=NULL)
                    {
                    	gfx_clear(); 
                    	desenhaNo_Circ(ptlista);
                    }
                }
                else
                    printf("\n--------------SEM ELEMENTOS NA LISTA-------------\n");
             break;
        }
        gfx_paint();
    }while(op!='d');
    if(ptlista!=NULL){
        Desaloca_Circ(ptlista);
    }
    gfx_quit();
}

/*--------------------------------------------------------------------------
OBJETIVO: DESENHAR OS NOS DA LISTA DUPLAMENTE ENCADEADA
PARAMETRO: A LISTA
---------------------------------------------------------------------------*/
void desenhaNo_Dup(ListDup *c)
{
    int increase=0;
    char convert[10];
	  
	gfx_set_color(255,0,0);
    gfx_rectangle(50+increase,50,95+increase,70);
    gfx_line(88+increase,50,88+increase,70);
    if(c->prox!=NULL){
    	/*DESENHA SETA INDO*/
        gfx_line(95+increase,54,(95+increase)+15,54);
        gfx_line((95+increase)+10,50,(95+increase)+15,54);
        gfx_line((95+increase)+10,58,(95+increase)+15,54);
    } 
    c=c->prox;
    if(c!=NULL)
    {
    	gfx_line((95+increase)+4,62,(95+increase)+19,62);/*O TAMANHO DA SETA SÃO 15 PIXELS COM O ESPACO QUE SOBRA DE 4 PIXELS, SÃO 19 NO TOTAL
            													ENTAO FACO O DESENHO DO PROXIMO NÓ PARA O ANTERIOR*/
       gfx_line((95+increase)+3,62,(95+increase)+8,59);
       gfx_line((95+increase)+3,62,(95+increase)+8,65);
       increase += 64;
    }
    while(c!=NULL){
       /*DESENHA O RETANGULO*/
       gfx_set_color(255,0,0);
       gfx_rectangle(50+increase,50,95+increase,70);
       gfx_line(88+increase,50,88+increase,70);
       if(c->prox!=NULL){
       		/*DESENHA SETA INDO*/
	        gfx_line(95+increase,54,(95+increase)+15,54);
	        gfx_line((95+increase)+10,50,(95+increase)+15,54);
	        gfx_line((95+increase)+10,58,(95+increase)+15,54);
	        /*DESENHA SETA VOLTANDO*/
	       gfx_line((95+increase)+4,62,(95+increase)+19,62);/*O TAMANHO DA SETA SÃO 15 PIXELS COM O ESPACO QUE SOBRA DE 4 PIXELS, SÃO 19 NO TOTAL
	            													ENTAO FACO O DESENHO DO PROXIMO NÓ PARA O ANTERIOR*/
	       gfx_line((95+increase)+3,62,(95+increase)+8,59);
	       gfx_line((95+increase)+3,62,(95+increase)+8,65);
       }
       sprintf(convert,"%d",c->info);
       gfx_text(53+increase,53,convert);
       increase += 64;  
       c = c->prox;
       /*sleep(1);*/
    }

}

/*--------------------------------------------------------------------------
OBJETIVO: CRIAR O NO CABEÇA
PARAMETRO: O PONTEIRO DA LISTA
RETORNO: O NO CABEÇA
-----------------------------------------------------------------------------*/
ListDup *cabeca()
{

	ListDup *ptl;

	if((ptl=malloc(sizeof(ListDup)))!=NULL)
	{
		ptl->prox = NULL;
		/*ptl->ant = NULL;*/
		return ptl;
	}
	else
	{
		printf("\n---------------SEM MEMORIA--------------");
		exit(404);
	}
	return NULL;
}

/*----------------------------------------------------------------------------
OBJETIVO: BUCAR UM ELEMENTO NA LISTA DUPLA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
		   O NUMERO QUE ESTA PROCURANDO - x
		   UM CONTADOR PARA PEGAR A SUA POSICAO - pos
RETORNO: O NÓ CORRESPONDENTE AO NUMERO
------------------------------------------------------------------------------*/
ListDup *Busca_Dup(ListDup *ptl, int x, int *pos)
{
	ListDup *pt=ptl->prox;
	*pos = 1;

	while(pt!=NULL)
	{
		if(pt->info == x)
			return pt;
		else
			pt = pt->prox;
			*pos=*pos+1;
	}

	return pt;
}

/*----------------------------------------------------------------------------
OBJETIVO: INSERIR UM ELEMENTO NA LISTA ENCADEADA, SEMPRE NO INÍCIO
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: A LISTA MODIFICADA
------------------------------------------------------------------------------*/
ListDup *Insere_Dup(ListDup *ptl)
{
	int x;/*o numero que vai inserir*/
	ListDup *novo;/*VAI SER O NOVO NÓ*/
	ListDup *proximo;/*OBTÉM O PROXIMO NÓ DA LISTA*/

	printf("\n-----------------INSERCAO---------------------\n");
	printf("\nQUAL NUMERO DESEJA INSERIR?");
	scanf("%d",&x);
	__fpurge(stdin);

	if((novo=malloc(sizeof(ListDup)))!=NULL)
	{
		novo->info = x;

		proximo = ptl->prox;

		if(proximo!=NULL)
		{
			novo->prox = ptl->prox;
			ptl->prox = novo;
			novo->ant = ptl;
			proximo->ant = novo;
		}
		else
		{
			novo->prox = ptl->prox;
			ptl->prox = novo;
			novo->ant = ptl;
		}
	}
	return ptl;

}

/*----------------------------------------------------------------------------
OBJETIVO: REMOVER UM ELEMENTO DA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: A LISTA MODIFICADA
------------------------------------------------------------------------------*/
ListDup *Remove_Dup(ListDup *ptl)
{
	int x;/*o numero que vai inserir*/
	int pos;/*OBTEM A POSICAO DO NO QUE VAI REMOVER, NAO UTILIZAMOS ELE NESSA FUNCAO
			POREM SERVE COMO PARÂMENTERO PARA A FUNCAO Busca_Dup*/
	ListDup *no;/*VAI RECEBER O NÓ DA BUSCA*/
	ListDup *anterior;/*RECEBE O NÓ ANTERIOR DO NÓ ENCONTRADO*/
	ListDup *proximo;/*RECEBE O PROXIMO NÓ DO NÓ ENCONTRADO*/

	if(ptl->prox != NULL){
		printf("\n-----------------REMOCAO---------------------\n");
		printf("\nQUAL NUMERO DESEJA REMOVER?");
		scanf("%d",&x);
		__fpurge(stdin);

		no = Busca_Dup(ptl,x,&pos);

		if(no!=NULL)
		{
			anterior = no->ant;
			proximo = no->prox;

			if(proximo != NULL){
				anterior->prox = proximo;
				proximo->ant = anterior;
			}
			else
			{
				anterior->prox = NULL;
			}
			free(no);
		}
		else
			printf("\n-------------ELEMENTO NAO ESTA NA LISTA------------\n");
	}
	else
		printf("\n---------------SEM ELEMENTOS NA LISTA----------------");
	return ptl;

}

/*----------------------------------------------------------------------------
OBJETIVO: BUSCAR UM ELEMENTO NA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void Buscando (ListDup *ptl)
{
	int x;/*O NUMERO A SER PROCURADO*/
	int pos;/*OBTEM A POSICAO DO NÓ PARA IMPRIMIR NA GFX*/
	ListDup *no;/*RECEBE O NÓ SE FOI ENCONTRADO*/

	if(ptl->prox!=NULL)
	{
		printf("\n-----------------BUSCAR---------------------\n");
		printf("\nQUAL NUMERO DESEJA BUSCAR?");
		scanf("%d",&x);
		__fpurge(stdin);

		no = Busca_Dup(ptl,x,&pos);

		if(no!=NULL)
		{
			DesenhaSeta(pos);
		}
		else
			printf("\n--------------NUMERO NAO ESTA PRESENTE NA LISTA---------------");
	}
	else
		printf("\n----------------SEM ELEMENTOS NA LISTA--------------\n");
}

/*----------------------------------------------------------------------------
OBJETIVO: DESALOCA OS ELEMENTOS DA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void Desaloca_Dup(ListDup *ptl)
{
	ListDup *desaloc; /*PONTEIRO PARA AUXILIAR QUANDO FOR DESALOCAR*/

	while(ptl!=NULL)
	{
		desaloc = ptl;
		ptl=ptl->prox;
		free(desaloc);
	}
}

void Lista_Dup()
{
	ListDup *ptlista;/*O PONTEIRO PARA LISTA*/
	char op;/*OBTEM AS OPCOES DO MENU*/

	ptlista=cabeca();
	do
	{
        gfx_init(800,200,"------------------LISTA DUPLAMENTE ENCADEADA------------------");
        gfx_clear();
		desenhaNo_Dup(ptlista);
		gfx_paint();
        printf("\n-----------------OPERACOES------------------\n");
		printf("\ta) BUSCA DE ELEMENTO;\n");
		printf("\tb) INSERCAO DE ELEMENTO;\n");
		printf("\tc) REMOCAO DE ELEMENTO;\n");
		printf("\td) SAIR;\n\t");
		scanf("%c",&op);
		__fpurge(stdin);
		switch(op)
		{
			case 'a':
				Buscando(ptlista);
			break;

			case 'b':
				ptlista = Insere_Dup(ptlista);
			break;

			case 'c':
				ptlista = Remove_Dup(ptlista);
			break;
		}
		
	}while(op!='d');

	Desaloca_Dup(ptlista);
	gfx_quit();
}

int main ()
{
	char op;

	do
	{
		printf("\n\nEscolher o tipo da lista a ser manipulada dentre as seguintes opções:\n");
		printf("\n\ta) Simplesmente encadeada sem nó cabeça e ordenada;\n");	
		printf("\tb) Circular simplesmente encadeada sem nó cabeça e ordenada;\n");	
		printf("\tc) Duplamente encadeada com nó cabeça e sem ordenação.\n");	
		printf("\td) Sair;\n\t");	
		scanf("%c",&op);
		__fpurge(stdin);

		switch(op)
		{
			case 'a':
				Lista_simp();
			break;

			case 'b':
				Lista_Circ();
			break;

			case 'c':
				Lista_Dup();
			break;
		}
	}while(op!='d');
	return 0;
}