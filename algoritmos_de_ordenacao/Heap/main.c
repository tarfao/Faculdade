#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

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
			troca(&V[i], &V[j]);
			descer (V,j,n);
		}
	}

}


void arranjar (int32_t *V, int n)
{
	int i;

	for(i = n/2; i >= 0; i--)
	{
		descer(V,i,n);
	}

}

double HeapSort (int32_t *V, int n)
{
	int m;
	struct timeval time_inicial, time_final;
	double tIni, tFim;

	tIni = tFim = 0;

	arranjar(V,n-1);
	n--;
	m = n;
	gettimeofday(&time_inicial,NULL);
	while (m > 0)
	{
		troca(&V[0],&V[m--]);
		descer(V,0,m);
	}
	gettimeofday(&time_final,NULL);

	tFim = (double)time_final.tv_usec + ((double)time_final.tv_sec * (1000000)); 
    tIni = (double)time_inicial.tv_usec + ((double)time_inicial.tv_sec * (1000000)); 

    return (tFim - tIni);


}

int main (int argc, char *argv[])
{
	/*int32_t V[]={95,60,78,39,28,66,70,33};95,60,78,39,28,66,70,33
	arranjar(V,sizeof(V)/4);
	mostra(V,sizeof(V)/4);*/
	FILE *fp;
    int32_t tot;
    int32_t *V;
    int tipo;
    char fnamein[256];
    char fnameout[256];
    double time;

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
    printf("\n---------------ARQUIVO SEM ORDEM----------------\n");
    /*mostra(V,tot);*/
    printf("\n---------------ARQUIVO ORDENADO----------------\n");

    time = HeapSort(V,tot);

    /*mostra(V,tot);*/

    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",time);

    fclose(fp);

    assert( (fp = fopen(fnameout,"w")) != NULL );
    fwrite(V,sizeof(int32_t),tot,fp);
    fclose(fp);

    free(V);

	return 0;
}