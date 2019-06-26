#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

/*
DISCENTE: RONALDO TAFAREL PEREIRA DE SOUZA
RGM: 35043
DATA: 11/05/2017
*/

/*--------------------------------------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE A STRING DIGITADA PELO USUÁRIO É VÁLIDA
PARAMETRO: O ESTADO QUE ESTÁ(es), O CONJUNTO DE SÍMBOLOS(conjunto), O SEU TAMANHO(size), 
			A QUANTIDADE DE DE ESTADOS(q), A QUANTIDADE DE SÍMBOLOS (e), A MATRIZ COM A CONFIGURAÇÃO(d)
			E A POSICAO DO SÍMBOLO NO CONJUNTO QUE VAMOS VERIFICAR SE É VALIDA(pos)
RETORNO: O ESTADO FINAL DO AUTÔMATO
----------------------------------------------------------------------------------------------------------*/
char verifica_string(char es, char conjunto[], int size, int q, int e, char d[10][10], int pos)
{
	int i,j;

	if(pos != size-1){
		for(i=1;i<q+1;i++)
		{
			if ( es==d[i][0] ){	/* verifica se um símbolo está na matriz*/
				for(j=1;j<e+1;j++){
					if (conjunto[pos]==d[0][j]){
						//printf("\n%c ",d[0][j]);
						return verifica_string(d[i][j],conjunto, size, q, e, d,pos+1);
					}
				}
				if(j==e+1)
				{
					return '.';
				}
			}
		}
	}
	return es;
	
}

/*---------------------------------------------------------------------------------------------------------------
OBJETIVO: MUDAR A POSICAO DO ESTADO INCIAL, PARA QUE ELE SEJA O PRIMEIRO
PARAMETRO: O ESTADO INICIAL (q0), A QUANTIDADE DE ESTADOS POSSÍVEIS(q0), A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e), E
			A MATRIZ CONTENDO A CONFIGURAÇÃO (d)
----------------------------------------------------------------------------------------------------------------*/
void muda_pos_primeiro(char q0, int q, char d[10][10])
{
	int i;

	if(q0!=d[1][0]){
		for(i=2;i<q+1;i++){
			if(q0==d[0][i])
			{
				d[0][i]	= d[0][1];
				d[0][1] = q0;
			}
		}
	}
}

/*---------------------------------------------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE O ESTADO DIGITADA ESTÁ NA CONFIGURAÇÃO
PARAMETRO: O ESTADO(es), A QUANTIDADE DE ESTADOS POSSÍVEIS(q), A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e) E A MATRIZ
			CONTENDO A CONFIGURAÇÃO DO AFD(d)
RETORNO: SE ESTIVER RETORNA 1, CASO CONTRARIO 0
---------------------------------------------------------------------------------------------------------------*/
int Verifica_Estado(char es, int q, char d[10][10])
{
	int i;

	for(i=1;i<q+1;i++)
	{
        //printf("\n%c",d[i][0]);
       	if(es==d[i][0])
		{
			return i;
		}
	}
	return (-1);
}

/*---------------------------------------------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DA CONFIGURAÇÃO
PARAMETRO: A QUANTIDADE DE ESTADOS POSSÍVEIS(q),A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e) E A MATRIZ
			CONTENDO A CONFIGURAÇÃO DO AFD(d)
---------------------------------------------------------------------------------------------------------------*/
void Leitura_Configuracao(int q, int e, char d[10][10])
{
	int i,j,ver;//auxiliares e pos que é a posicao que o simbolo vai estar
	char estado;

	for(i=1;i<q+1;i++)
	{
		system("clear");
		//printf("\nConfiguracao do elemento %c ",d[i][0]);
		for(j=1;j<e+1;j++)
		{
			do{
				printf("\nd(%c,%c) = ",d[i][0],d[0][j]);
				__fpurge(stdin);
				scanf("%c",&estado);
				ver = Verifica_Estado(estado,q,d);
				if (ver==-1)
					printf("\nEstado nao aceito!! ");
			}while(ver == -1);
			d[i][e] = estado;
		}
	}

}

/*--------------------------------------------------------------------------------------------
OBJETIVO: OBTER OS ESTADOS, SÍMBOLOS, ESTADO DE ACEITACAO E ESTADO INICIAL
PARAMETROS: q - A QUANTIDADE DE ESTADOS POSSÍVEIS
			e - A QUANTIDADE DE SÍMBOLOS
			qf - QUANTIDADE DE ESTADOS FINAIS
PARAMETROS POR REFERENCIA:
			q0 - QUE É O ESTADO DE ACEITACAO
			d - QUE É A MATRIZ DA FUNCAO DELTA
			f - QUE É O VETOR COM OS ESTADOS INICIAIS
----------------------------------------------------------------------------------------------*/
void Recebe_Dados(int q, int e, int qf, char *q0, char d[10][10], char f[10])
{
	int i;
	char s;
	system("clear");
	printf("\nEstados(somente a inicial do estado. exemplo: estado ab, entrada: a): ");
	for(i=1;i<q+1;i++)
	{
		printf("%i: ",i);
        __fpurge(stdin);
		
	    scanf("%c",&s);
		d[i][0]=s;

	}

	printf("\nSimbolos: ");
	for(i=1;i<e+1;i++)
	{
		printf("%i: ",i);
		//flush(stdin);
        __fpurge(stdin);
		scanf("%c",&d[0][i]);
	}

	do{
		system("clear");
		printf("\nQual eh o estado inicial? ");
		//fflush(stdin);
		 __fpurge(stdin);
		scanf("%c",q0);
	}while(Verifica_Estado(*q0,q,d)==-1);
	system("clear");
	printf("\nEstados aceitacao: ");
	for(i=0;i<qf;i++)
	{
		do{
			printf("\n%d: ",i+1);
			  //fflush(stdin);
		 	 __fpurge(stdin);
			scanf("%c",&s);
		}while(Verifica_Estado(s,q,d)==-1);
		f[i]=s;
	}
}

/*------------------------------------------------------------------------------------------------
OBJETIVO: CRIAR UM AFD
PARAMETROS POR REFERENCIA: q - A QUANTIDADE DE ESTADOS POSSÍVEIS
						   e - A QUANTIDADE DE SÍMBOLOS
						   qf - QUANTIDADE DE ESTADOS FINAIS
						   q0 - QUE É O ESTADO DE ACEITACAO
						   d - QUE É A MATRIZ DA FUNCAO DELTA
						   f - QUE É O VETOR COM OS ESTADOS INICIAIS
-------------------------------------------------------------------------------------------------*/
void criacao (int* q, int* e, int* qf, char *q0, char d[10][10], char f[10])
{
	do{
		system("clear");
		printf("\nQuantos sao os estados possiveis? ");
       __fpurge(stdin);				    
		scanf("%d",q);
	}while(*q<1);

	do{
		system("clear");
		printf("\nQuantos sao os simbolos possiveis? ");
       __fpurge(stdin);  
		scanf("%d",e);
	}while(*e<1);

	do{
		system("clear");
		printf("\nQuantidade de estados de aceitacao: ");
       __fpurge(stdin);
		scanf("%d",qf);
	}while(*qf<1);

	Recebe_Dados(*q,*e,*qf,q0,d,f);
    Leitura_Configuracao(*q,*e,d);
}
/*------------------------------------------------------------------------------------------------
OBJETIVO: TESTAR O AFD COM UMA PALAVRA DE SÍMBOLOS
PARAMETROS: q - A QUANTIDADE DE ESTADOS POSSÍVEIS
			e - A QUANTIDADE DE SÍMBOLOS
			qf - QUANTIDADE DE ESTADOS FINAIS
			q0 - QUE É O ESTADO DE ACEITACAO
			d - QUE É A MATRIZ DA FUNCAO DELTA
			f - QUE É O VETOR COM OS ESTADOS INICIAIS
-------------------------------------------------------------------------------------------------*/
void testa_afd (int q, int e, int qf, char q0, char d[10][10], char f[10])
{
	int j; //auxiliar 
	char palavra[100];/*obtem a palavra do usuario*/
	int size; /*obtem o tamanho da palavra*/
	char ef; /*recebe a o último estado que a palvra proporcionou ao afd*/
	system("clear");
	printf("\nQual palavra deseja colocar no AFD? ");
    __fpurge(stdin);
	fgets(palavra,100,stdin);
	size = strlen(palavra);
	ef=verifica_string(q0,palavra,size,q,e,d,0);
	j=0;
	while(ef!=f[j] && j<qf)
	{
		j++;
	}
	printf("\n%c",ef);
	if(ef==f[j])
		printf("\n\t\tAceito\n\n");
	else
		printf("\n\t\tNao aceito\n\n");
}

int main ()
{
	int op;
	int q,e,qf;/*(q) É A QUANTIDADE DE ESTADOS POSSÍVEIS
				 (e) É A QUANTIDADE DE SÍMBOLOS POSSÍVEIS
				 (qf) É A QUANTIDADE DE ESTADOS FINAIS*/
	char q0;/*(q0) É O ESTADO INICIAL*/
    char d[10][10];
    char f[10];/*estados de aceitacao*/
    int v=0;

    do{
    	printf("\n[1] - Criar AFD");
    	printf("\n[2] - Inserir Palavra");
    	printf("\n[3] - Sair\n");
    	scanf("%d",&op);
    	system("clear");

    	switch(op)
    	{
    		case 1:
    			criacao(&q,&e,&qf,&q0,d,f);
    			v=1;
    		break;

    		case 2:
    			if(v==1)
    				testa_afd(q,e,qf,q0,d,f);
    			else
    				printf("\nAFD NAO FOI DEFINIDA!!\n");
			break;	
       	}

    }while(op!=3);

	
	return 0;
}
