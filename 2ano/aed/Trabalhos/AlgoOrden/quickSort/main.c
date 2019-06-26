/*-------------------------------------------------------------------------------------------
OBJECTIVE:
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
#include <stdlib.h> /*to add srand*/
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>


void trocar (int32_t *, int32_t *);
void mostra (int32_t *, int);

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
                trocar(&L[j],&L[j+1]);
            }
        }
    }
}

/*-------------------------------------------------------------------------------------------
OBJECTIVE: CHANGE TWO NUMBERS
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
void trocar(int32_t *a, int32_t *b)
{
	int32_t aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
/*-------------------------------------------------------------------------------------------
OBJECTIVE:
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
void pivoM3(int32_t L[],const int32_t ini,const int32_t fim, int32_t *mediana)
{
	int meio = (fim+ini)/2;
	int32_t v[3] = {L[ini],L[meio],L[fim]};
	bubble_sort(v,3);
	/*printf("Mediana -> ");
	mostra(v,3);
	printf("\n");*/
	if(v[1] == L[ini])
	{
		*mediana = ini;
	}
	else
	{
		if(v[1] == L[meio])
		{
			*mediana = meio;
		}
		else
		{
			*mediana = fim;
		}
	}


}
/*-------------------------------------------------------------------------------------------
OBJECTIVE:
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
void pivoA (const int32_t ini,const int32_t n, int32_t *mediana)
{
	unsigned intervalo;

	intervalo = n-ini;

	srand(time(NULL));
	*mediana = ini + (rand() % intervalo); /*choice the number from the total*/

}

/*-------------------------------------------------------------------------------------------
OBJECTIVE:
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
void quickSort(int32_t *L,int32_t ini, int32_t fim, int32_t tipo)
{
	int32_t key;/*recebe o pivô*/
	int32_t i,j;
	int32_t mediana;

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
			pivoA(ini,fim,&mediana);
			trocar(&L[mediana],&L[fim]);
		}
		else{
			if(tipo == 7){
				pivoM3(L,ini,fim,&mediana);
				trocar(&L[mediana],&L[fim]);
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
		/*printf("-->1\n");*/
		if(L[i] < L[fim])/*auxilia quando os elementos estão dispostos aleatoriamente*/
			i++;
		trocar(&L[i],&L[fim]);
		/*mostra(L,13);
		printf("\n");*/
		quickSort(L,ini,i-1,tipo);
		/*printf("-->3\n");*/
		quickSort(L,i+1,fim,tipo);
		/*printf("-->4\n");*/
	}
}

/*-------------------------------------------------------------------------------------------
OBJECTIVE:
PARAMETER:
RETURN:
---------------------------------------------------------------------------------------------*/
void mostra(int32_t L[], int32_t n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("%d ",L[i]);
    }
}

int main(int argc, char *argv[])
{
	/*int L[]={5,1,6,2,9,3,10,4};
	quickSort(L,0,7,5);
	mostra(L,8);*/

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

    assert ( (fp = fopen(fnamein,"r")) != NULL );

    fseek(fp,0,SEEK_END);/*move para o final para obter a quantidade de numeros no arquivo*/
    tot = ftell(fp)/4;
    rewind(fp);/*move o ponteiro para o início do arquivo para fazermos a leitura direta*/
    assert ((V = malloc(sizeof(int32_t)*tot)) != NULL);
    fread(V,sizeof(int32_t),tot,fp);
    /*printf("\n---------------ARQUIVO SEM ORDEM----------------\n");
    mostra(V,tot);
    printf("\n---------------ARQUIVO ORDENADO----------------\n");*/

    gettimeofday(&time_inicial,NULL);
    quickSort(V,0,tot-1,7);
    gettimeofday(&time_final,NULL);

    /*mostra(V,tot);*/
   
    tFim = (double)time_final.tv_usec + ((double)time_final.tv_sec * (1000000));
    tIni = (double)time_inicial.tv_usec + ((double)time_inicial.tv_sec * (1000000));
    printf("\nTempo gasto para ordenacao: -> %.6lf ms\n",(tFim - tIni));

    fclose(fp);

    assert( (fp = fopen(fnameout,"w")) != NULL );
    fwrite(V,sizeof(int32_t),tot,fp);
    fclose(fp);

    free(V);

	return 0;
}
