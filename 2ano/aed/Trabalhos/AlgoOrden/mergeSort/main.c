#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

void intercalar(int L[], int Tmp[], int ini1,int ini2,int fim2)
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

void mostra(int32_t L[], int32_t n)
{
    int32_t i;

    for(i=0;i<n;i++)
    {
        printf("%d ",L[i]);
    }
}

int main (int argc, char *argv[])
{
    FILE *fp;
    int32_t tot;
    int32_t *V;
    int tipo;
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
    /*printf("\n---------------ARQUIVO SEM ORDEM----------------\n");
    mostra(V,tot);*/
    printf("\n---------------ARQUIVO ORDENADO----------------\n");

    gettimeofday(&time_inicial,NULL);
    mergeSort(V,0,tot-1);
    gettimeofday(&time_final,NULL);

    /*mostra(V,tot);*/
    tFim = (double)time_final.tv_usec + ((double)time_final.tv_sec * (1000000)); 
    tIni = (double)time_inicial.tv_usec + ((double)time_inicial.tv_sec * (1000000)); 
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni)/1000000);
    fclose(fp);

    assert( (fp = fopen(fnameout,"w")) != NULL );
    fwrite(V,sizeof(int32_t),tot,fp);
    fclose(fp);

    free(V);

    return 0;
}
