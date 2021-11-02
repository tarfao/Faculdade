#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

void mostra(int32_t *, int);

/*-----------------------------------------------------------
OBJETIVO: FAZER A TROCA DE ELEMENTOS
PARAMETROS: OS DOIS ELEMENTOS QUE SERÃO TROCADOS
-------------------------------------------------------------*/
void troca(int32_t *a, int32_t *b)
{
    int32_t aux;

    aux=*a;
    *a=*b;
    *b=aux;
}


/*-----------------------------------------------------------
OBJETIVO: FAZER A ORDENAÇÃO DO TIPO BOLHA
PARAMETROS: O VETOR COM OS ELEMENTOS E O NÚMERO TOTAL DE ELEMENTOS
-------------------------------------------------------------*/
void bubble_sort(int32_t L[],int n)
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
void bubble_sort2(int32_t L[],int n)
{
    int mudou=1,j;
    int naux = n-1;
    int guarda = n-1;

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

/*---------------------------------------------------------
OBJETIVO: MOSTRAR O VETOR
PARAMETROS: O VETOR E O NUMERO TOTAL DE ELEMENTOS
-----------------------------------------------------------*/
void mostra(int32_t L[], int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("%d ",L[i]);
    }
}


int main(int argc, char *argv[])
{

    /*int vetor[]={3,2,1,-3,8,0,2,4,10,5};
    printf("%d\n",*(vetor+3) );
    bubble_sort2(vetor,sizeof(vetor)/4);
    mostra(vetor,sizeof(vetor)/4)
    printf("-----> %ld\n",sizeof(vetor)/4);
    int32_t *V;*/
    FILE *fp;
    int32_t tot;
    int32_t *V;
    int32_t *O;
    int tipo;
    int32_t i;
    char fnamein[256];
    char fnameout[256];

    struct timeval time_inicial, time_final;
    double tIni, tFim;
    tIni = tFim = 0;


        if( argc != 3 )
    {
erro:
        printf("Uso: %s num-elementos c|d|a\n", argv[0]);
        return 0;
    }

    tipo = argv[2][0];
    argv[2][1] = '\0';

    if( tipo != 'c' && tipo != 'd' && tipo != 'a' )
        goto erro;

    strcpy(fnamein,argv[1]);
    strcat(fnamein,".");
    strcat(fnamein,argv[2]);
    strcpy(fnameout, fnamein);
    strcat(fnameout, ".out");

    assert( (fp = fopen(fnamein,"r")) != NULL );

    fseek(fp,0,SEEK_END);/*move para o final para obter a quantidade de numeros no arquivo*/
    tot = ftell(fp)/4;
    rewind(fp);/*move o ponteiro para o início do arquivo para fazermos a leitura direta*/
    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    fread(V,sizeof(int32_t),tot,fp);
    fclose(fp);
    /*printf("\n---------------ARQUIVO SEM ORDEM----------------\n");
    mostra(V,tot);*/
    printf("\n---------------ARQUIVO ORDENADO----------------\n");

    gettimeofday(&time_inicial,NULL);
    insertion_sort(V,tot);
    gettimeofday(&time_final,NULL);

    assert((O=malloc(sizeof(int32_t)*tot)) != NULL);
    assert( (fp=fopen(fnameout,"r")) != NULL);
    fwrite(O,sizeof(int32_t),tot,fp);
    fclose(fp);

    for(i=0;i<tot;i++)
    {
        if(V[i] != O[i]){
            exit(0);
        }
    }

    mostra(V,tot);
    tFim = (double)time_final.tv_usec + ((double)time_final.tv_sec * (1000000)); 
    tIni = (double)time_inicial.tv_usec + ((double)time_inicial.tv_sec * (1000000)); 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni)/1000000);

    assert( (fp = fopen(fnameout,"w")) != NULL );
    fwrite(V,sizeof(int32_t),tot,fp);
    fclose(fp);

    free(V);
    free(O);

    return 0;
}
