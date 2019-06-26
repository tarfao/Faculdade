/*DISCENTE: RONALDO TAFAREL PEREIRA DE SOUZA
RGM: 35043
DATA: 10/08/2017*/

#include <stdlib.h> /*to add srand*/
#include <stdio.h>
#include <time.h>
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


/*
OBJETIVO: FAZER A COPIA PARA SEREM O NOME DOS ARQUIVOS DE ENTRADA E SAIDA*/
void copias(char *fnamein, char *fnameout, char *argv[])
{
	strcpy(fnamein,argv[1]);
    strcat(fnamein,".");
    strcat(fnamein,argv[2]);
    strcpy(fnameout, fnamein);
    strcat(fnameout, ".out");
}

/*
OBJETIVO: ABRIR O ARQUIVO E COLOLA-LO NO VETOR*/
void abreArq (char *fnamein, int32_t V[], int32_t tot)
{
	FILE *fp;

	assert( (fp = fopen(fnamein,"r")) != NULL );

	fread(V,sizeof(int32_t),tot,fp);

    fclose(fp);


}

/*
OBJETIVO: SALVAR O NOVO ARQUIVO ORDENADO*/
void salvaArq (char *fnameout, int32_t *V, int32_t tot)
{
	FILE *fp;

	assert( (fp = fopen(fnameout,"w")) != NULL );
    fwrite(V,sizeof(int32_t),tot,fp);
    fclose(fp);
}

/*-----------------------------------------------------------
OBJETIVO: FAZER A TROCA DE ELEMENTOS
PARAMETROS: OS DOIS ELEMENTOS QUE SERÃO TROCADOS
-------------------------------------------------------------*/
void trocar(int32_t *a, int32_t *b)
{
    int32_t aux;

    aux=*a;
    *a=*b;
    *b=aux;
}

void swap (ListDup *pt1, ListDup *pt2)
{
	int32_t aux;

	aux = pt1->info;
	pt1->info = pt2->info;
	pt2->info = aux;
}

/*-----------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO DO TIPO BOLHA2
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
-------------------------------------------------------------*/
void bubble_sort2(int32_t L[],int32_t n)
{
    int32_t mudou=1,j;
    int32_t naux = n-1;
    int32_t guarda = n-1;

    while(mudou)
    {
        j=0;
        mudou = 0;

        while(j<naux)
        {
            if (L[j]>L[j+1])
            {
                trocar(&L[j],&L[j+1]);
                mudou = 1;
                guarda = j;
            }
            j = j+1;
        }
        naux = guarda;

    }

}

/*-----------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO DO TIPO BOLHA
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
-------------------------------------------------------------*/
void bubble_sort(int32_t L[],int32_t n)
{
    int32_t i,j;

    for (i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(L[j]>L[j+1])
            {
                trocar(&L[j],&L[j+1]);
            }
        }
    }
}

/*----------------------------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO APÓS A IMAGINARIA INSERÇÃO DO ELEMENTO
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
------------------------------------------------------------------------------*/
void insertion_sort (int32_t L[], int n)
{
    int32_t i,j,valor;

    for(i=1;i<n;i++)
    {
        valor=L[i];
        j=i-1;

        while(j>=0 && valor<L[j])
        {
            L[j+1] = L[j];
            j--;
        }
        L[j+1]=valor;
    }
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA O BUBBLE SORT ORIGINAL NA ORDENAÇÃO
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void bubble(char *fnamein, char *fnameout, int32_t tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    gettimeofday(&time_inicial,NULL);
    bubble_sort(V,tot);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni));

    salvaArq(fnameout, V, tot);

    free(V);
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA O BUBBLE SORT MELHORADO NA ORDENAÇÃO
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void bubble2(char *fnamein, char *fnameout, int32_t tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    gettimeofday(&time_inicial,NULL);
    bubble_sort2(V,tot);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni));

    salvaArq(fnameout, V, tot);

    free(V);
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA 0 INSERTION SORT NA ORDENAÇÃO
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void insertion(char *fnamein, char *fnameout, int32_t tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    gettimeofday(&time_inicial,NULL);
    insertion_sort(V,tot);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni));

    salvaArq(fnameout, V, tot);

    free(V);
}


void intercalar(int32_t L[], int32_t Tmp[], int32_t ini1,int32_t ini2,int32_t fim2)
{
    int32_t i;
    int32_t fim1 = ini2-1;
    int32_t nro = 0;
    int32_t ind = ini1;
    int32_t aux=ini1;



	while (ini1<=fim1 && ini2<=fim2)
	{
       if(L[ini1]<L[ini2])
	   {
           	Tmp[ind] = L[ini1];
            ini1++;
	    }
	    else
	    {
	       Tmp[ind] = L[ini2];
	       ini2++;
	    }

	    ind++;
	    nro++;
	}

	

    while(ini1<=fim1)
    {
        Tmp[ind]=L[ini1];
        ini1++;
        ind++;
        nro++;
    }

    while(ini2<=fim2)
    {
		Tmp[ind]=L[ini2];
	    ini2++;
	    ind++;
	    nro++;
   	}
    for(i=0;i<nro;i++)
    {
        L[i+aux]=Tmp[i+aux];
    }
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA O QUICKSORT NA ORDENAÇÃO
PARAMETRO: L = VETOR COM OS NUMEROS
			esq = ÍNDICE DA PARTE ESQUERDA
			dir = ÍNDICE DA PARTE DIREITA
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void mergeSort (int32_t L[],int32_t esq,int32_t dir)
{
    int32_t centro;
    int32_t *Tmp = malloc(sizeof(int32_t)*dir+1);

    if(esq<dir)
    {
        centro = (esq+dir)/2;

        mergeSort(L,esq,centro);
        mergeSort(L,centro+1,dir);
        /*printf("esq = %d, dir = %d, centro = %d\n",esq,dir,centro);*/
        intercalar(L,Tmp,esq,centro+1,dir);
        /*intercalar(esq,Tmp,centro+1,dir,L);*/

    }
    free(Tmp);
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA O MERGESORT NA ORDENAÇÃO
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void merge(char *fnamein, char *fnameout, int tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    gettimeofday(&time_inicial,NULL);
    mergeSort(V,0,tot-1);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec ; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",tFim - tIni);

    salvaArq(fnameout, V, tot);

    free(V);
}
/*-------------------------------------------------------------------------------------------
OBJETIVO: FAZER A MEDIANA DE 3
---------------------------------------------------------------------------------------------*/
void pivoM3(int32_t L[],const int32_t ini,const int32_t fim)
{
	int32_t meio = (fim+ini)/2;
	int32_t v[3] = {L[ini],L[meio],L[fim]};
	int32_t mediana;

	bubble_sort(v,3);

	if(v[1] == L[ini])
	{
		mediana = ini;
	}
	else
	{
		if(v[1] == L[meio])
		{
			mediana = meio;
		}
		else
		{
			mediana = fim;
		}
	}
	trocar(&L[mediana],&L[fim]);


}
/*-------------------------------------------------------------------------------------------
OBJETIVO: OBER O PIVO ALEATORIO
---------------------------------------------------------------------------------------------*/
void pivoA (int32_t *L, const int32_t ini,const int32_t fim)
{
	unsigned intervalo;
	int32_t mediana;

	intervalo = fim-ini;

	srand(time(NULL));
	mediana = ini + (rand() % intervalo); /*choice the number from the total*/
	trocar(&L[mediana],&L[fim]);

}

/*-------------------------------------------------------------------------------------------
OBJETIVO: ORDENAR OS ELEMENTOS
---------------------------------------------------------------------------------------------*/
void quickSort(int32_t *L,int32_t ini, int32_t fim, int32_t tipo)
{
	int32_t key;/*recebe o pivô*/
	int32_t i,j;

	if (fim - ini < 2)
	{
		if(fim - ini == 1)
		{
			if(L[ini]>L[fim])
			{
				trocar(&L[ini],&L[fim]);
			}
		}
	}
	else
	{
		if(tipo == 6)
		{
			pivoA(L,ini,fim);
		}
		else{
			if(tipo == 7){
				pivoM3(L,ini,fim);
			}
		}

		i = ini;
		j = fim-1;
		key = L[fim];

		while(j>i)
		{
			/*anda com o vetor da esquerda para a direita, pegando os numeros
			menores que o pivô até encontrar um maior*/
			while(L[i]<key)
			{
				i++;
			}
			/*anda com o vetor do final para o inicio, contando a quantidade de
			numeros maiores que o pivô, e controla o j, pois ele alcançava o i 
			quando está decrescente, e acaba indo para uma posicao que nao existe no vetor
			fazendo comparações com undefind*/
			while(L[j]>key && i<j)
			{
				j--;
			}

			if(j>i)
			{
				trocar(&L[i],&L[j]);
				i++;
				j--;
			}
		}
		if(L[i] < L[fim])/*auxilia quando os elementos estão dispostos aleatoriamente*/
			i++;
		trocar(&L[i],&L[fim]);
		quickSort(L,ini,i-1,tipo);
		quickSort(L,i+1,fim,tipo);
	}
}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIA O QUICKSORT NA ORDENAÇÃO
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
			opc = O TIPO PARA MEDIANA
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void quick(char *fnamein, char *fnameout, int tot, int32_t opc)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    gettimeofday(&time_inicial,NULL);
    quickSort(V,0,tot-1,opc);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec ; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",tFim - tIni);

    salvaArq(fnameout, V, tot);

    free(V);
}

/*----------------------------------------------------------------------------
OBJETIVO: ARRUMAR O HEAP APÓS UMA MODIFICAÇÃO EM UM INDICE i QUE PODE DAR PROBLEMA PARA BAIXO
PARAMETRO: O HEAP, O LOCAL ONDE OCORREU A MODIFICAÇÃO E O TOTAL
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void descer (int32_t *V, int i, int n)
{
	int j;

	if (i==0)
		j = 1;
	else
		j = 2 * i;

	if (j <= n)
	{
		if(j < n)
		{
			if (V[j+1] > V[j])
				j++;
		}
		if (V[i] < V[j])
		{
			trocar(&V[i], &V[j]);
			descer (V,j,n);
		}
	}

}

/*----------------------------------------------------------------------------
OBJETIVO: TRANSFORMAR EM HEAP
PARAMETRO: O VETOR COM OS NUMEROS E O TOTAL
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void arranjar (int32_t *V, int n)
{
	int i;

	for(i = n/2; i >= 0; i--)
	{
		descer(V,i,n);
	}

}

/*----------------------------------------------------------------------------
OBJETIVO: AUXILIAR A OPCAO HEAP
PARAMETRO: fnamein = NOMEDO ARQUIVO DE ENTRADA
			fnameout = NOME DO ARQUIVO DE SAÍDA
			tot = TOTAL DE ELEMENTOS
RETORNO: NENHUM
------------------------------------------------------------------------------*/
void heap(char *fnamein, char *fnameout, int tot)
{
	int32_t *V;
	int32_t m;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    arranjar(V,tot-1);
	tot--;
	m = tot;
    gettimeofday(&time_inicial,NULL);
    while (m > 0)
	{
		trocar(&V[0],&V[m--]);
		descer(V,0,m);
	}
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec ; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",tFim - tIni);

    salvaArq(fnameout, V, tot+1);

    free(V);
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
			j = ptlista;
			j->info = valor;
		}
		else{
			j = j->prox;
			j->info = valor;
			pt = pt->prox;
		}
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

void retornaNumeros (ListDup *pt, int *V)
{
	int i;

	i=0;
	while(pt != NULL){
		V[i++] = pt->info;
		pt = pt->prox;
	}
}


void LDbubble(char *fnamein, char *fnameout, int tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    ListDup *ptlista=NULL;

    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);
    ptlista = elemento(ptlista,V,tot);
    gettimeofday(&time_inicial,NULL);
    ptlista = LDbubble_Sort(ptlista);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec ; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",tFim - tIni);
    
    retornaNumeros(ptlista,V);

    salvaArq(fnameout, V, tot);

    free(V);
}

void LDIsenrtion(char *fnamein, char *fnameout, int tot)
{
	int32_t *V;
	struct timeval time_inicial, time_final;
    double tIni, tFim;
    ListDup *ptlista=NULL;

    tIni = tFim = 0;

    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    abreArq(fnamein,V,tot);

    ptlista = elemento(ptlista,V,tot);

    gettimeofday(&time_inicial,NULL);
    LDinsertionSort(ptlista);
    gettimeofday(&time_final,NULL);

    tFim = (double)time_final.tv_usec/1000000 + (double)time_final.tv_sec ; 
    tIni = (double)time_inicial.tv_usec/1000000 + (double)time_inicial.tv_sec; 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",tFim - tIni);

    retornaNumeros(ptlista,V);

    salvaArq(fnameout, V, tot);

    free(V);
}

int main(int argc, char *argv[])
{

    FILE *fp;
    int32_t tipo,N;
    char fnamein[256];
    char fnameout[256];
    int32_t opc;


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

    copias(fnamein, fnameout, argv);

    assert((fp = fopen(fnamein,"r")) != NULL);
    fclose(fp);
    
    do
    {
    	printf("\n------------------ORDENAÇÃO------------\n");
    	printf("1 - Bubble Sort Original\n");
    	printf("2 - Bubble Sort Melhorado\n");
    	printf("3 - Insertion Sort\n");
    	printf("4 - Merge Sort\n");
    	printf("5 - Quick Sort com pivô sendo o último elemento\n");
    	printf("6 - Quick Sort com pivô sendo um elemento aleatório\n");
    	printf("7 - Quick Sort com pivô sendo a media de tres\n");
    	printf("8 - Heap Sort\n");
    	printf("\n------------------LISTA ENCADEADA-------------\n");
    	printf("9 - Bubble Sort Original\n");
    	printf("10 - Insertion Sort\n");
    	printf("11 - Sair\n");
    	scanf("%d",&opc);

    	switch(opc)
    	{
    		case 1: 
    			bubble(fnamein, fnameout, N );
    		break;

    		case 2:
    			bubble2(fnamein, fnameout, N);
    		break;

    		case 3:
    			insertion(fnamein, fnameout, N);
    		break;

    		case 4:
    			merge(fnamein, fnameout,N);
    		break;

    		case 5:
    			quick(fnamein, fnameout,N,opc);
    		break;

    		case 6:
    			quick(fnamein, fnameout,N,opc);
    		break;

    		case 7:
    			quick(fnamein, fnameout,N,opc);
    		break;

    		case 8:
    			heap(fnamein, fnameout,N);
    		break;

    		case 9:
    			LDbubble(fnamein, fnameout, N);
    		break;

    		case 10:
    			LDIsenrtion(fnamein, fnameout, N);
    		break;
    	}
    } while (opc != 11);

	return 0;
}