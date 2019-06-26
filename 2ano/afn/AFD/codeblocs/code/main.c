#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*--------------------------------------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE A STRING DIGITADA PELO USUÁRIO É VÁLIDA
PARAMETRO: O ESTADO QUE ESTÁ(es), O CONJUNTO DE SÍMBOLOS(conjunto), O SEU TAMANHO(size),
			A QUANTIDADE DE DE ESTADOS(q), A QUANTIDADE DE SÍMBOLOS (e), A MATRIZ COM A CONFIGURAÇÃO(d)
			E A POSICAO DO SÍMBOLO NO CONJUNTO QUE VAMOS VERIFICAR SE É VALIDA(pos)
RETORNO: O ESTADO FINAL DO AUTÔMATO
----------------------------------------------------------------------------------------------------------*/
char verifica_string(char es, char conjunto[], int size, int q, int e, char d[q+1][e+1], int pos)
{
	int i,j;

	if(pos != size){
		for(i=1;i<q+1;i++)
		{
			if ( es==d[i][0] ){	/* verifica se um símbolo está na matriz*/
				for(j=1;j<e+1;j++){
					if (conjunto[pos]==d[0][j]){
						return verifica_string(d[i][j],conjunto, size, q, e, d,pos+1);
					}
				}
				if(j==e+1)
				{
					printf("\nCONJUNTO N FORA DO PADRÃO DO AUTOMATO");
					exit(404);
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
void muda_pos_primeiro(char q0, int q, int e, char d[q+1][e+1])
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
OBJETIVO: BUSCAR ONDE ESTA O SÍMBOLO QUE FOI DIGITADO
PARAMETRO: O SÍMBOLO(s), A QUANTIDADE DE ESTADOS POSSÍVEIS(q),A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e) E A MATRIZ
			CONTENDO A CONFIGURAÇÃO DO AFD(d)
RETORNO: A POSICAO QUE O SÍMBOLO ESTÁ NA MATRIZ OU -1 PARA REPRESENTAR A AUSENCIA
---------------------------------------------------------------------------------------------------------------*/
int Busca_Pos_Simbolo(char s, int q, int e, char d[q+1][e+1])
{
	int i;

	for(i=1;i<q+1;i++)
	{
		if(s==d[0][i])
		{
			return i;
		}
	}
	return -1;
}

/*---------------------------------------------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE O ESTADO DIGITADA ESTÁ NA CONFIGURAÇÃO
PARAMETRO: O ESTADO(es), A QUANTIDADE DE ESTADOS POSSÍVEIS(q), A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e) E A MATRIZ
			CONTENDO A CONFIGURAÇÃO DO AFD(d)
RETORNO: SE ESTIVER RETORNA 1, CASO CONTRARIO 0
---------------------------------------------------------------------------------------------------------------*/
int Verifica_Estado(char es, int q, int e, char d[q+1][e+1])
{
	int i;

	for(i=1;i<q+1;i++)
	{
		if(es==d[i][0])
		{
			return 1;
		}
	}
	return 0;
}

/*---------------------------------------------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DA CONFIGURAÇÃO
PARAMETRO: A QUANTIDADE DE ESTADOS POSSÍVEIS(q),A QUANTIDADE DE SÍMBOLOS POSSÍVEIS(e) E A MATRIZ
			CONTENDO A CONFIGURAÇÃO DO AFD(d)
---------------------------------------------------------------------------------------------------------------*/
void Leitura_Configuracao(int q, int e, char d[q+1][e+1])
{
	int i,j,pos;//auxiliares e pos que é a posicao que o simbolo vai estar
	char s,estado;

	for(i=1;i<q+1;i++)
	{
		printf("\nConfiguracao do elemento %c",d[0][i]);
		for(j=1;j<e+1;j++)
		{
			do{
				printf("\nSimbolo: ");
				scanf("%c",&s);
				pos=Busca_Pos_Simbolo(s,q,e,d);
				if(pos==-1)
					printf("\n\tSímbolo nao aceito!!");
			}while(pos==-1);

			do{
				printf("\nEstado: ");
				scanf("%c",&estado);
				pos = Verifica_Estado(estado,q,e,d);
				if(pos==-1)
					printf("\nEstado nao aceito!!");
			}while(pos==-1);
			d[i][pos]=estado;//colocando na matriz o estado correspondente ao símbolo da posicao pos
		}
	}

}

int main ()
{
	int q,e,size,qf;/*(q) É A QUANTIDADE DE ESTADOS POSSÍVEIS
				//(e) É A QUANTIDADE DE SÍMBOLOS POSSÍVEIS
				//(size) É O TAMANHO DA STRING DIGITADA PELO USUARIO
				//(qf) É A QUANTIDADE DE ESTADOS FINAIS*/
	char q0;/*(q0) É O ESTADO INICIAL*/
	char s;/*AUXILIA NA LEITURA DE UM ESTADO DE ACEITAÇÃO*/
	char ef;/*obtem o estado final*/
	char palavra[100];/*obtem a palvara para jogar no afd*/
	int i,j;/*auxiliares do for*/
    char d[10][10];

	do{
		printf("\nQuantos sao os estados possiveis? ");
        fflush(stdin);
		scanf("%d",&q);
	}while(q<1);

	do{
		printf("\nQuantos sao os simbolos possiveis? ");
        fflush(stdin);
		scanf("%d",&e);
	}while(e<1);

	printf("\nEstados: ");
	for(i=1;i<q+1;i++)
	{
		printf("%i: ",i);
		fflush(stdin);
        getc(d[i][0]);
        //scanf("%c",&d[i][0]);

	}

	printf("\nSimbolos: ");
	for(i=1;i<e+1;i++)
	{
		printf("%i: ",i);
    	fflush(stdin);
		scanf("%c",&d[0][i]);
	}

	do{
		printf("\nQual eh o estado inicial? ");
		fflush(stdin);
		scanf("%c",&q0);
	}while(Verifica_Estado(q0,q,e,d)==-1);

	do{
		printf("\nQuantidade de estados de aceitacao: ");
        fflush(stdin);
		scanf("%d",&qf);
	}while(qf<1);
	char f[qf];/*estados de aceitacao*/
	printf("\nEstados aceitacao: ");
	for(i=0;i<qf;i++)
	{
		do{
			printf("\n%d",i+1);
            fflush(stdin);
			scanf("%c",&s);
		}while(Verifica_Estado(s,q,e,d)==-1);
		f[i]=s;
	}
	Leitura_Configuracao(q,e,d);
	printf("\nQual palavra deseja colocar no AFD? ");
	fflush(stdin);
	fgets(palavra,100,stdin);
	size = strlen(palavra);
	ef=verifica_string(q0,palavra,size,q,e,d,0);
	j=0;
	while(ef!=f[j] && j<qf)
	{
		j++;
	}
	if(ef==f[j])
		printf("\nAceito");
	else
		printf("\nNao aceito");
	return 0;
}
