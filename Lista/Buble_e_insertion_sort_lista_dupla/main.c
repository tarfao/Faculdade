#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#define true 1
#define false 0

typedef struct lista_Dupla{
	int32_t info;
	struct lista_Dupla *prox;
	struct lista_Dupla *ant;
}ListDup;

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

void mostra(ListDup *ptl)
{
	printf("Lista -> ");
	while(ptl!=NULL)
	{
		printf("  %d  ",ptl->info);
		ptl=ptl->prox;
	}
	printf("\n");
}

/*----------------------------------------------------------------------------
OBJETIVO: ADICIONAR ELEMENTOS NA LISTA
PARAMETRO: A LISTA DUPLAMENTE ENCADEADA - ptl
RETORNO: NENHUM
------------------------------------------------------------------------------*/
ListDup *Insere_elemento(ListDup *pt)
{
	int32_t x = 2;
	ListDup *no;
	ListDup *ini;

	while(x != 0)
	{
		printf("\nEntre com o num: ");
		scanf("%d",&x);
		if(x != 0)
		{
			if(pt == NULL){
				pt = malloc(sizeof(ListDup));
				pt->info = x;
				pt->prox = NULL;
				pt->ant = NULL;
				ini = pt;
			}
			else
			{
				pt->prox = malloc(sizeof(ListDup));
				no = pt;
				pt = pt->prox;

				pt->info = x;
				pt->prox = NULL;
				pt->ant = no;

				no->prox = pt;
			}
			mostra(ini);
		}

	}
	return ini;
}

void swap (ListDup *pt1, ListDup *pt2)
{
	int32_t aux;

	aux = pt1->info;
	pt1->info = pt2->info;
	pt2->info = aux;
}

ListDup *LDbubble_Sort(ListDup *ptlista)
{
	int mudou=true;
	ListDup *n_linha;
	ListDup *guarda;
	ListDup *pt = ptlista;
	ListDup *ptini = ptlista;
	ListDup *j;

	while(pt->prox != NULL)
		pt = pt->prox;

	n_linha = guarda = pt;

	while(mudou)
	{
		j = ptini;
		mudou = false;

		while(j != n_linha)
		{
			if(j->info > j->prox->info)
			{
				swap(j,j->prox);
				mudou = true;
				guarda = j;
			}
			j = j->prox;
		}
		n_linha = guarda;
	}
	return ptini;
}


void LDinsertionSort (ListDup *ptlista)
{
	int32_t valor;
	ListDup *j;
	ListDup *pt=ptlista->prox;

	while(pt != NULL)
	{
		valor = pt->info;
		j = pt->ant;

		while(j != NULL && valor < j->info)
		{
			j->prox->info = j->info;
			j = j->ant;
		}
		if (j == NULL){
			printf(">\n");
			j = ptlista;
			j->info = valor;
		}
		else{
			j = j->prox;
			printf("-->\n");
			j->info = valor;
			pt = pt->prox;
		}
	}
}

void quickSortLD (ListDup *ptini, ListDup *ptfim)
{
	int32_t key;
	ListDup *i=ptini;
	ListDup *j=ptfim;

	if(ptini->prox == ptfim)
	{
		if(ptini->info > ptfim->info)
			swap(ptini, ptfim);
	}
	else
	{
		key = ptfim->info;
		j = ptfim->ant;

		while(i->prox != j)
		{
			while(i->info < key && i->prox != NULL)
			{
				i = i->prox;
			}

			while(j->info > key && j->ant != NULL)
			{
				j = j->ant;
			}

			if(j->ant != i && j->prox != i)
			{
				swap(i,j);
				if(i->prox != NULL)
					i = i->prox;
				if(j->ant != NULL)
					j = j->ant;
			}
		}
		if(i->info < j->info){
			if(i->prox != NULL)
				i = i->prox;
		}
		swap(i,ptfim);
		quickSortLD(ptini,i->ant);
		quickSortLD(i->prox,ptfim);

	}
}

void retornaNumeros (ListDup *pt, int *V)
{
	int i;

	i=0;
	while(pt != NULL){
		V[i++] = pt->info;
		pt = pt->prox;
	}
}

ListDup *elemento(ListDup *pt, int32_t *V, int tot)
{
	ListDup *novo;
	ListDup *aux;
	int i=0;

	pt = malloc(sizeof(ListDup));
	pt->prox = NULL;
	pt->ant = NULL;
	aux = pt;

	while(i<tot)
	{
		pt->info = V[i];
		if(i+1 < tot){
			novo = malloc(sizeof(ListDup));
			novo->prox = NULL;
			pt->prox = novo;
			novo->ant = pt;
			pt = pt->prox;
		}
		i++;
	}
	return aux;
}

int main (int argc, char *argv[])
{
	ListDup *ptlista=NULL;
	ListDup *ptfim=NULL;
	FILE *fp;

	

    int32_t tot,N;
    int32_t *V;
    int tipo;
    char fnamein[256];
    char fnameout[256];
   

        if( argc != 3 )
    {
erro:
        printf("Uso: %s num-elementos c|d|a\n", argv[0]);
        return 0;
    }

    N = atoi(argv[1]);
    tipo = argv[2][0];
    argv[2][1] = '\0';

    if( tipo != 'c' && tipo != 'd' && tipo != 'a' )
        goto erro;

    strcpy(fnamein,argv[1]);
    strcat(fnamein,".");
    strcat(fnamein,argv[2]);
    strcpy(fnameout, fnamein);
    strcat(fnameout, ".out");

    assert ( (fp = fopen(fnamein,"r")) != NULL );

    fseek(fp,0,SEEK_END);/*move para o final para obter a quantidade de numeros no arquivo*/
    tot = ftell(fp)/4;
    rewind(fp);/*move o ponteiro para o início do arquivo para fazermos a leitura direta*/
    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    fread(V,sizeof(int32_t),tot,fp);
    fclose(fp);

	ptfim = ptlista = elemento(ptlista,V,tot);

	mostra(ptlista);

	while(ptfim->prox != NULL)
		ptfim = ptfim->prox;
	printf("\n-----ordenado------\n");
	quickSortLD(ptlista,ptfim);
	mostra(ptlista);

	retornaNumeros(ptlista,V);

	assert(fp = fopen(fnameout,"w"));
	fwrite(V,sizeof(int32_t),N,fp);
	fclose(fp);

	Desaloca_Dup(ptlista);
	free(V);

	return 0;
}