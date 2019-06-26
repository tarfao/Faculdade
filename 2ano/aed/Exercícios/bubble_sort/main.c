#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------
OBJETIVO: FAZER A TROCA DE ELEMENTOS
PARAMETROS: OS DOIS ELEMENTOS QUE SERÃO TROCADOS
-------------------------------------------------------------*/
void troca(int *a, int *b)
{
    int k;

    k=*a;
    *a=*b;
    *b=k;
}


/*-----------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO DO TIPO BOLHA
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
-------------------------------------------------------------*/
void bubble_sort(int L[],int n)
{
    int i,j;

    for (i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(L[j]>L[j+1])
            {
                troca(&L[j],&L[j+1]);
            }
        }
    }
}

/*-----------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO DO TIPO BOLHA2
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
-------------------------------------------------------------*/
void bubble_sort2(int L[],int n)
{
    int mudou=1,j;
    int naux = n;
    int guarda = n;

    while(mudou)
    {
        j=0;
        mudou = 0;

        while(j<naux)
        {
            if (L[j]>L[j+1])
            {
                troca(&L[j],&L[j+1]);
                mudou = 1;
                guarda = j;
            }
            j = j+1;
        }
        naux = guarda;

    }

}
/*----------------------------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO APÓS A IMAGINARIA INSERÇÃO DO ELEMENTO
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
------------------------------------------------------------------------------*/
void insertion_sort (int L[], int n)
{
    int i,j,valor;

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

/*---------------------------------------------------------
OBJETIVO: MOSTRAR O VETOR
PARAMETROS: O VETOR E O NUMERO TOTAL DE ELEMENTOS
-----------------------------------------------------------*/
void mostra(int L[], int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("%d ",L[i]);
    }
}
int main()
{
    int vetor[]={3,2,1};
    insertion_sort(vetor,sizeof(vetor)/4);
    mostra(vetor,sizeof(vetor)/4);
    return 0;
}
