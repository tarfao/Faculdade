/*-----------------------------------------------------------------------------
OBJETIVO: 
PARAMETROS:
RETORNO:
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h> /*free*/
#include <assert.h>
#include "arv.h"

typedef struct ar{
	int32_t chave:28;
	int32_t bal:2;
	int32_t reservado:2;
	struct ar *esq;
	struct ar *dir;
}A_NO;

/*------------------------------------------------------------------------
OBJETIVO: BUSCAR UM NO NA ARVORE
PARAMETROS:
			pt - RAIZ DE UMA SUBÁRVORE
			x - QUE É O A CHAVE A SER PROCURADA
RETORNO: O PONTEIRO PARA O NÓ QUE ESTÁ BUSCANDO, OU RETORNA O PONTEIRO DO
			NÓ QUE SERIA PAI DELE
--------------------------------------------------------------------------*/
A_NO* Busca_ARB(A_NO *pt, int32_t x)
{
	if(pt->chave == x)
	{
		return pt;
	}
	else
	{
		if(x < pt->chave){
			if(pt->esq != NULL)
				return(Busca_ARB(pt->esq,x));
			else
				return pt;
		}
		else{
			if(pt->dir != NULL)
				return(Busca_ARB(pt->dir,x));
			else
				return 	pt;
		}
	}
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	INSERIR UM NÓ NA ÁRVORE(SÃO TODAS DIFERENTES)
PARAMETROS:	rz - RAIZ DA ÁRVORE
			x - NUMERO A SER INSERIDO
RETORNO: A RAIZ DA ÁRVORE
------------------------------------------------------------------------------*/
A_NO* Insrer_ARB(A_NO *rz, int32_t x)
{
	A_NO *aux;

	if(rz == NULL)
	{
		assert((rz = malloc(sizeof(A_NO))) != NULL);
		rz->chave = x;
		rz->esq = NULL;
		rz->dir = NULL;
		rz->bal = 0;
	}
	else
	{
		aux = rz;

		aux = Busca_ARB(aux,x);

		if(aux->chave == x)

		{
			system("clear");
			printf("\n!!!! NUMERO JA ESTA NA LISTA !!!");
	
		}
		else
		{
			if(x < aux->chave)
			{
				aux->esq = malloc(sizeof(A_NO));
				aux = aux->esq;
				aux->chave = x;
				aux->esq = NULL;
				aux->dir = NULL;
			}
			else
			{
				aux->dir = malloc(sizeof(A_NO));
				aux = aux->dir;
				aux->chave = x;
				aux->esq = NULL;
				aux->dir = NULL;	
			}

		}
	}

	return rz;
}

/*-----------------------------------------------------------------------------
OBJETIVO:   MOSTRAR TODOS OS NÓS DA ÁRVORE (PÓS ORDEM)
PARAMETROS:	A RAIZ DA ARVORE
RETORNO: 	NENHUM
------------------------------------------------------------------------------*/
void Imprime_NO(A_NO *pt)
{
	printf("%d ",pt->chave);

	if(pt->esq != NULL)
		Imprime_NO(pt->esq);
	if(pt->dir != NULL)
		Imprime_NO(pt->dir);
}

/*-----------------------------------------------------------------------------
OBJETIVO:   DESALOCAR OS NÓS DA ÁRVORE (PRÉ ORDEM)
PARAMETROS:	A RAIZ DA ARVORE
RETORNO: 	NENHUM
------------------------------------------------------------------------------*/
void Desaloca_Arv (A_NO *pt)
{
	if(pt->esq != NULL)
		Desaloca_Arv(pt->esq);
	if(pt->dir != NULL)
		Desaloca_Arv(pt->dir);

	free(pt);
}

int main ()
{
	int32_t op;
	int32_t n;
	A_NO *raiz = NULL;

	do
	{
		printf("\n1 = INSERIR NUMERO\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				system("clear");
				printf("\nNumero: ");
				scanf("%d",&n);
				raiz = Insrer_ARB(raiz,n);
				printf("\n-----------------------------\nArvore = ");
				Imprime_NO(raiz);
				printf("\n-----------------------------");
			break;
		}
	}while(op == 1);

	return 0;
}