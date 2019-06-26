#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#define true 1
#define false 0
#define vazio -1

typedef struct NState {/*tem o objetivo de obter os movimentos de um estado (seja ele do afd ou afn)
						com as letras do alfabeto*/
	char locale[20];
}Nstate;

typedef struct TMarcas {/*tem o objetivo de simular uma fila quando encontramos um
						novo estado após fazer o fecho de um E[d(x,&)]*/
	char resultado[20];
	int marca;
}TMarcas;
/*----------------------------------------------------------------------
OBJETIVO: RETIRAR AS VIRGULAS DO ALFABETO POIS ENTRA COM OS DADOS
			SEPARADOS POR VÍRGULAS
PARAMETRO: A STRING
----------------------------------------------------------------------*/
void retiraVirgulaAlfa (char string[])
{
	int i,j;
	char aux[10];

	i=j=0;
	strcpy(aux,string);/*COPIA A STRING PARA PODER RETIRAR AS VIRGULAS*/

	while( !(aux[i] == '\0') ) /*PROCURA ATÉ ENCONTRAR O FINAL DA STRING*/
	{
		if ( !(aux[i] == ',') ){
			string[j++] = aux[i];
		}
		i++;
	}

	string[j-1] = '&'; /*ADICIONA A PALAVRA VAZIA NO ALFABETO*/
	string[j] = '\0';/*como o fgets lê tbm o '\n' precisamos
						colocar o '\0' no seu lugar para finalizar a string*/
}

/*----------------------------------------------------------------------
OBJETIVO: RETIRAR AS VIRGULAS DOS ESTADO POIS ENTRA COM OS DADOS
			SEPARADOS POR VÍRGULAS
PARAMETRO: A MATRIZ QUE VAI GUARDAR OS ESTADOS,
			est: POSSUI TODOS OS ESTADOS DIGITADOS PELO USUARIO
			*tam: VAI OBTER O TAMANHO DE CADA ESTADO (NUMEROS DE LETRAS)
RETORNO: O TOTAL DE ESTADOS DO AFN
----------------------------------------------------------------------*/
int retiraVirgulaState (char matriz[][4], char est[], int *tam)
{
	int i,j,k;

	j=i=k=0;

	while( !(est[k] == '\0') ) /*PROCURA ATÉ ENCONTRAR O FINAL DA STRING*/
	{
		if ( !(est[k] == ',')){
			matriz[i][j] = est[k];
			j++;
		}
		else
		{
			matriz[i][j] = '\0'; /*ADICIONA O FINALIZADOR DE STRING TODA VEZ QUE ENCONTRAR VIRGULA*/
			i++;				/*INCREMENTA PARA MUDAR A LINHA PARA OUTRA STRING DO ESTADO*/
			j=0;				/*COMEÇA DA POSICAO 0 POIS PULOU PARA A PROXIMA LINHA*/
		}
		k++;
	}

	*tam = j-1; /*COMO NO ÚLTIMO ESTADO FAZ A CONTAGEM DO '\n' O J É INCREMENTADO
				E PRECISAMOS DECREMENTAR ELE PARA OBTERMOS O TAMANHO DE UM ESTADO*/

	matriz[i][j-1] = '\0'; /*como o fgets lê tbm o '\n' precisamos
						colocar o '\0' no seu lugar para finalizar a string*/
	return i+1;
}

/*---------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DO ESTADO INICIAL E FINAL
PARAMETROS: A MATRIZ COM OS ESTADOS
			tot: QUE É O TOTAL DE ESTADOS
			*q0: QUE É O ESTADO INICIAL
			*qf: QUE É O ESTADO FINAL
---------------------------------------------------------------------------*/
void estadoInicial (char matriz [][4], int tot, char *q0, char *qf, const int tamState)
{
	int i;
	char aux[20];
	char oneEstate[4];
	int cont = false;
	int j,k,l;
	int ver;  /*VERIFICA QUANTAS VEZES ENTROU NO FOR, QUE REPRESENTA QUANTOS ESTADOS FINAIS POSSUI*/
	int tam; /*obtem obtem o tamanho de qf*/

	do{
		printf("\nEstado inical = ");
		__fpurge(stdin);
		fgets(q0,4,stdin);

		q0[strlen(q0)-1] = '\0';/*COLOCA O FINALIZADOR POIS FGETS LÊ O '\n'*/

		for(i=0;i<tot;i++)/*VERIFICA SE O ESTADO DIGITADO ESTA NA MATRIZ*/
		{
			if( !(strcmp(matriz[i],q0)) )
			{
				/*FAZ A TROCA PARA QUE O ESTADO INICIAL SEJA O PRIMEIRO DA MATRIZ*/
				strcpy(aux,matriz[0]);
				strcpy(matriz[0],matriz[i]);
				strcpy(matriz[i],aux);

				cont = true;
			}
		}

		if(!cont)
			printf("Entre com estado válido\n");
	}while(!cont);

	cont = false;
	ver = 0;
	do{
		printf("\nEstado final = ");
		__fpurge(stdin);
		fgets(qf,20,stdin);

		tam = strlen(qf);
		qf[tam-1] = '\0';

		j=0;
		l=0;
		printf("%s\n", qf);
		while(qf[j] != '\0')
		{
			if(qf[j]!=',')
			{
					aux[l++] = qf[j];
			}
			j++;
		}
		aux[l] = '\0';
		printf("%s\n",aux );
		j=0;
		while(aux[j] != '\0')
		{
			l=0;
			for(k=j;k<j+tamState;k++)
			{
				oneEstate[l++] = aux[k];
			}
			oneEstate[l] = '\0';
			printf("o = %s\n",oneEstate);
			j = j+tamState;
			ver++;
			for(i=0;i<tot;i++)
			{
				if( !(strcmp(matriz[i],oneEstate)) )
				{
					cont++;
				}
			}

		}
		printf("ver = %d  cont = %d\n",ver,cont);

		if(cont != ver)
			printf("Entre com estado válido\n");
	}while(cont != ver);

}

/*---------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE OS DESTINOS DE UM CERTO ESTADO COM x LETRA DO ALFABETO
			ESTÃO NA MATRIZ DE ESTADOS
PARÂMETROS: A MATRIZ DE ESTADOS
			tot: TOTAL DE ESTADOS
			dest: DESTINO DE UM ESTADO
			pos: POSICAO DO DESTINO DE UM ESTADO NO VETOR dest
---------------------------------------------------------------------------*/
void verifica_destinos (char matriz [][4], int tot, Nstate dest[], int pos)
{
	int i=0;
	char aux[4];
	int j=0,k=0;

	if(dest[pos].locale[j] != '-')/*VERIFICA SE NAO EH ESTADO VAZIO*/
	{
		while(dest[pos].locale[j] != '\0')
		{
			while(dest[pos].locale[j] != ',' && dest[pos].locale[j] != '\0' && dest[pos].locale[j] != '\n')
			{
				aux[k++] = dest[pos].locale[j++];/*OBTEM UM ESTADO PURO, SOMENTE SUA STRING*/
			}
			j++;
			aux[k] = '\0';
			k = 0;
			printf("%s\n",aux );
			i=0;
			while( (strcmp(matriz[i],aux)) ) /*VERIFICA 1 A 1 ESTADO SE CORRESPONDE COM OS DA MATRIZ*/
			{
				i++;
				if(i==tot) /*CASO ELE PASSE DA POSICAO ACESSÍVEL O PROGRAMA PARA*/
					exit(100);
			}
		}
	}
}

/*---------------------------------------------------------------------------
OBJETIVO: RETIRAR AS VÍRGULAS DE UM MOVIMENTO DO DEST
PARAMETRO: dest: QUE É A MOVIMENTACAO DOS ESTADOS COM AS LETRAS DO ALFABETO
			post: QUE É A POSICAO DO ESTADO QUE SE DESEJA RETIRAR VIRGULA
---------------------------------------------------------------------------*/
void retiraVirgulaMove (Nstate *dest, int pos)
{
	int i,j;
	i=j=0;

	char aux[20];
	strcpy(aux,dest[pos].locale);

	while( !(aux[i] == '\0') )
	{
		if ( !(aux[i] == ',') ){
			dest[pos].locale[j++] = aux[i];
		}
		i++;
	}

	dest[pos].locale[j-1] = '\0';/*como o fgets lê tbm o '\n' precisamos
						colocar o '\0' no seu lugar para finalizar a string*/
}
/*---------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DOS MOVIMENTOS DOS ESTADOS COM AS LETRAS DO ALFABETO
PARAMETROS: matriz: MATRIZ CONTENDO TODOS OS ESTADOS
			alfa: CONTENDO O ALFABETO DA MAQUINA
			dest: QUE É O QUE VAI ADQUIRIR TODOS OS MOVIMENTOS DE UM ESTADO
			totState: TOTAL DE ESTADOS DA MATRIZ
---------------------------------------------------------------------------*/
void read_move (char matriz[][4], char alfa[], Nstate dest[], int totState )
{
	int i,j,cont=0;


	printf("\n[obs: entre com os estados separados por vírgula]\n");

	for(i=0;i<totState;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("Delta(%s,%c) = ",matriz[i] , alfa[j]);
			__fpurge(stdin);
			fgets(dest[cont].locale,20,stdin);
			verifica_destinos(matriz,totState,dest,cont);
			retiraVirgulaMove(dest,cont);
			cont++;
		}
	}
}


/*---------------------------------------------------------------------------
OBJETIVO: IMPRIMIR AS INFORMAÇÕES DO AFN
---------------------------------------------------------------------------*/
void imprime (char *alfa, char state[][4], char *q0, char *qf, Nstate dest[], int totState)
{
	int i,j,cont=0;

	printf("Informações do AFN: \n");
	printf("--------------------------------------------\n");
	printf("\nAlfabeto = 			%s\n",alfa);
	printf("--------------------------------------------\n");
	printf("Estados = 			");
	for(i=0;i<totState;i++)
		printf("%s ",state[i]);
	printf("\n--------------------------------------------\n");
	printf("\nEstado inicial = 	%s\n", q0);
	printf("--------------------------------------------\n");
	printf("Estado final = 		%s\n", qf);
	printf("--------------------------------------------\n");
	for(i=0;i<totState;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("\nDelta(%s,%c) = 		%s\n",state[i] , alfa[j],dest[cont++].locale);

		}
		printf("--------------------------------------------\n");
	}

}


/*---------------------------------------------------------------------------
OBJETIVO: OBTER A POSICAO DE UM ESTADO
PARAMETRO: est: ESTADO QUE DESEJA OBTER A POSICAO
			state: MATRIZ COM TODOS OS ESTADOS
			tot: TOTAL DE ESTADOS DE state
RETORNO: A POSICAO DO ESTADO
---------------------------------------------------------------------------*/
int obtemPosEstado (char *est, char state[][4], int tot)
{
	int i=0;

	printf("--> est =   %s\n",est);
	while(i<tot)
	{
		if( strcmp(est,state[i])==0 )
			return i;
		i++;
	}

	return i;
}
/*---------------------------------------------------------------------------
OBJETIVO: OBTER A MOVIMENTACAO DE UM ESTADO COM A PRIMEIRA LETRA DO ALFABETO
PARAMETRO: 	*estado: ESTADO QUE VAMOS OBTER A MOVIMENTACAO

			dest: EH O DESTINO DE CADA ESTADO COM UMA LETRA DO ALFABETO

			tam1Estado: EH O TAMANHO DE UM ESTADO (QUANTAS LETRAS TEM)

			*estFinal: EH O ESTADO FINAL COM O MOVIMENTO, POIS O A STRING *estado
			PODE ESTAR COM UM CONJUNTO DE ESTADO E VAMOS RECEBER TAMBḾE OUTRO CONJUNTO
			DE ESTADOS EM *estFinal

			state: EH A MATRIZ COM TODOS OS ESTADOS

			totState: EH O TOTAL DE ESTADOS DE state
---------------------------------------------------------------------------*/
void move1alfa (char *estado, Nstate dest[], int tam1Estado, char *estFinal, char state[][4], int totState)
{
	int i=0,j,k;
	char est[4];
	int pos;

	if(estado[i] != '-')/*representação de vazio*/
	{
		while(estado[i] != '\0')
		{
			k=0;
			for(j=i;j<i+tam1Estado;j++){/*COMO JA SABEMOS O TAMANHO DE 1 ÚNICO ESTADO
										FAZEMOS A ATRIBUIÇÃO EM est DIRETO*/
				est[k++] = estado[i];
			}
			est[k] = '\0'; /*COMO SEMPRE K E INCREMENTADO, COLOCAMOS EM SUA ÚLTIMA POSICAO O FINALIZADOR*/
			i = i+tam1Estado; /*COMO JÁ SEI O TAMANHO DA UM ESTADO E VAI ESTAR SEM VIRGULAS NA STRING *estado
								PODEMOS AVANÇAR SEMPRE COM INCREMENTANDO i COM tam1Estado ATÉ ENCONTRA '\0'*/

			pos = obtemPosEstado(est,state,totState);
				/*como o dest ele tem as movimentacoes de um estado com todas letras do alfabeto
			e de padrao temos sempre 3 letras, exemplo 0,1 e &, por tanto para cada
			posicao de um estado temos 3 movientacoes em dest, uma para 0, outra para 1
			e por ultimo o de &, por isso faço essa equacao pos*3*/
			printf("move = %s\n",estFinal);
			if(strcmp(dest[(pos*3)].locale,"-")){
				strcat(estFinal,dest[(pos*3)].locale);
				printf("move = %s\n",estFinal);
			}
		}
	}
}

/*---------------------------------------------------------------------------
OBJETIVO: OBTER A MOVIMENTACAO DE UM ESTADO COM A SEGUNDA LETRA DO ALFABETO
PARAMETRO: 	*estado: ESTADO QUE VAMOS OBTER A MOVIMENTACAO

			dest: EH O DESTINO DE CADA ESTADO COM UMA LETRA DO ALFABETO

			tam1Estado: EH O TAMANHO DE UM ESTADO (QUANTAS LETRAS TEM)

			*estFinal: EH O ESTADO FINAL COM O MOVIMENTO, POIS O A STRING *estado
			PODE ESTAR COM UM CONJUNTO DE ESTADO E VAMOS RECEBER TAMBḾE OUTRO CONJUNTO
			DE ESTADOS EM *estFinal

			state: EH A MATRIZ COM TODOS OS ESTADOS

			totState: EH O TOTAL DE ESTADOS DE state
---------------------------------------------------------------------------*/
void move2alfa (char *estado, Nstate dest[], int tam1Estado, char *estFinal, char state[][4], int totState)
{
	int i=0,j,k;
	char est[4];
	int pos;
	int l,m,n;
	int q,r,s;
	int cont=0;
	char est1Dest[4],est1EstFin[4];
	char final[20]={'\0'};

	if(estado[i] != '-')/*representação de vazio*/
	{
		while(estado[i] != '\0')
		{
			k=0;
			for(j=i;j<i+tam1Estado;j++)
			{
				est[k++] = estado[i];
			}
			est[k++] = '\0';
			i = i+tam1Estado;

			pos = obtemPosEstado(est,state,totState);
				/*como o dest ele tem as movimentacoes de um estado com todos alfabeto
			e de padrao temos sempre 3 letras, exemplo 0,1 e &, por tanto para cada
			posicao de um estado temos 3 movientacoes em dest, uma para 0, outra para 1
			e por ultimo o de &, por isso faço essa conta*/
			printf("move2 = %s\n",estFinal);
			if(strcmp(dest[(pos*3)+1].locale,"-"))
			{
				l=0;
				if(strlen(estFinal)!=0)
				{
					while(dest[(pos*3)+1].locale[l] != '\0')
					{
						/*separa um estado da string para poder verificar se já esta em estFinal*/
						n=0;
						for(m=l;m<l+tam1Estado;m++)
						{
							est1Dest[n++] = dest[(pos+1)*3-1].locale[m] ;
						}
						est1Dest[n] = '\0';
						l = l + tam1Estado;
						q=0;
						while(estFinal[q] != '\0')
						{
							r=0;
							for(s=q;s<q+tam1Estado;s++)
							{
								est1EstFin[r++] = estFinal[m] ;
							}
							est1EstFin[r] = '\0';
							q = q + tam1Estado;

							if(strcmp(est1EstFin,est1Dest) == 0)/*caso o estado já esteja dentro de estFinal nao vou adicionar*/
								cont = 1;

						}
						if(cont == 0)
							strcat(final,est1Dest);
						cont = 0;
					}
				}
				else
					strcat(estFinal,dest[(pos*3) + 1].locale);
			}
		}
		strcat(estFinal,final);
		printf("->move2 = %s\n",estFinal);
	}
}

/*-----------------------------------------------------------------------------------
OBJETIVO: OBTER O FECHO DE UM ESTADO E JOGAR NA PILHA
PARAMETROS: estado: 	eh o estado que vamos verificar o fecho
			state: 		eh a a matriz com todos os estados
			pilha:		eh onde guardo todos os estados finais apos o fecho
			dest:		eh a movimentacao de um estado com o alfabeto
			fimpilha:	eh o final da pilha
			tam1estado: eh o tamanho de 1 unico estado, (q0 é de tamanho 2)
			totState:	eh o total de estados em state
---------------------------------------------------------------------------------------*/
void fecho (char *estado, char state[][4], TMarcas *Fila, Nstate dest[],
		int *fimFila, int tam1Estado, int totState, Nstate *AFD, int *totAFD)
{
	char est[5]; /*obtem um unico estado para ver o fecho dele só*/
	char estFinal[20]={'\0'}; /*obtem o estado final após o fecho */
	int i=0,j=0,k,z;
	int ver = false;
	int pos; /*obtem a posicao que um do(s) estado(s) do char *estado esta
				para poder acessar em dest por essa posicao, pois as movimentações
				estao em posicoes iguais para cada variavel*/
	int l,m,n;
	int q,r,s;
	int cont=0;
	char est1Dest[4],est1EstFin[4];
	char final[20]={'\0'};

	if(estado[i] != '-'){/*representação de vazio*/
		while(estado[i] != '\0')
		{
			k=0;
			for(j=i;j<i+tam1Estado;j++)/*como os estados ja estao sem virgulas eu faco a copia direto
										pois ja sei o tamanho(quantas letras tem) de cada estado, até
										encontrar um '\0'*/
			{
				est[k++] = estado[i];
			}
			est[k] = '\0';
			printf("EST = %s %i %i\n",estado,tam1Estado,i);
			i = i+tam1Estado;
			pos = obtemPosEstado(est,state,totState);
			/*como o dest ele tem as movimentacoes de um estado com todos alfabeto
			e de padrao temos sempre 3 letras, exemplo 0,1 e &, por tanto para cada
			posicao de um estado temos 3 movientacoes em dest, uma para 0, outra para 1
			e por ultimo o de &, por isso faço essa conta*/
			printf("pos = %d  ",pos);
			/*if(pos == 0){
				strcat(estFinal,dest[pos+2].locale);
				printf(" %s\n",dest[pos+2].locale);
			}
			else{
				strcat(estFinal,dest[(pos*3) - 1].locale);
				printf(" %s\n",dest[(pos*3)-1].locale);
			}*/
			l=0;
			if(strlen(estFinal)!=0)
			{
				while(dest[(pos+1)*3-1].locale[l] != '\0')
				{
					/*separa um estado da string para poder verificar se já esta em estFinal*/
					n=0;
					for(m=l;m<l+tam1Estado;m++)
					{
						est1Dest[n++] = dest[(pos+1)*3-1].locale[m] ;
					}
					est1Dest[n] = '\0';
					l = l + tam1Estado;
					q=0;
					while(estFinal[q] != '\0')
					{
						r=0;
						for(s=q;s<q+tam1Estado;s++)
						{
							est1EstFin[r++] = estFinal[m] ;
						}
						est1EstFin[r] = '\0';
						q = q + tam1Estado;

						if(strcmp(est1EstFin,est1Dest) == 0)/*caso o estado já esteja dentro de estFinal nao vou adicionar*/
							cont = 1;

					}
					if(cont == 0)
						strcat(final,est1Dest);
					cont = 0;
				}
			}
			else
				strcat(estFinal,dest[((pos+1)*3) - 1].locale);

		}
		strcat(estFinal,final);

		if(strcmp(estFinal,"-")){/*se for igual ele da falso e vai para o else*/
				for (z = 0; z < *fimFila; z++)/*verifico se o fecho do estado já esta na pilha*/
				{
					printf(" %s -",Fila[z].resultado);
					if ( strcmp(Fila[z].resultado,estFinal)==0 )
					{
						ver = true;
					}
				}
		}
		else
		{
			ver = true;
		}
		printf("verficacao = %i    estFinal = %s\n", ver,estFinal);

		if(!ver){
			printf("Acrescentou!!!!!!!!!!!!!!!!!! %s\n",estFinal);
			strcpy(Fila[*fimFila].resultado,estFinal); /*jogo para a fila um estado que nao tem ainda*/
			Fila[*fimFila].marca = false;
			*fimFila = *fimFila + 1;					/*aumento a fila */
		}

		strcpy(AFD[*totAFD++].locale,estFinal);/*faco a copia do fecho para o AFD, pois
												trabalho com respectivas posicoes, as mesmas para os estados
												e também para a movimentacao com a primeira e segunda letra
												de alfa*/
	}

}

/*-----------------------------------------------------------------------------------
OBJETIVO: FAZER A TRANSICAO DE ESTADO DE CADA ESTADO COM UMA LETRA DO ALFABETO
		  E FAZ TAMBÉM A TRANSFORMAÇÃO DO AFN EM AFD DIRETO

PARAMETRO:	state: 		eh a a matriz com todos os estados
			dest:		eh a movimentacao de um estado com o alfabeto
			tam1estado: eh o tamanho de 1 unico estado, (q0 é de tamanho 2)
			totState:	eh o total de estados em state
			AFD:		vai ser as novas transicoes com a transformacao
			NewState:	sao os novos estados do AFD
			totAFD: 	quantidade de transicoes do AFD (acho dispensavel)
--------------------------------------------------------------------------------------*/
int delta (char state[][4], Nstate dest[], int tam1Estado,
			int totState, Nstate AFD[], char NewState[][10], int *totAFD)
{
	int iniFila=0				/*trabalho com fila para ver as marcacoes*/;
	int fimFila=0;				/*final da fila para poder retirar um estado*/
	TMarcas Fila[20];			/*o registro trabalho com fila para enfileirar os estados novos*/
	char estado[20]={'\0'};			/*obtem um estado da fila para fazer o fecho do delta do estado*/
	char moveAlfa1[20]={'\0'};	/*obtem o movimento de um estado com a primeira letra do alfabeto*/
	char moveAlfa2[20]={'\0'};	/*obtem o movimento de um estado com a segunda letra do alfabeto*/
	int aux;					/*um simples auxiliar para fazer a primeira chamada do fecho*/
	Nstate aux1[2];				/*o mesmo acima*/
	int i;


	fecho(state[0], state, Fila, dest, &fimFila, tam1Estado, totState,aux1,&aux);
	printf("%i\n",fimFila );
	while(iniFila != fimFila)
	{
		printf("fimfila = %d\n", fimFila);
		printf("Entrou\n");
		strcpy(estado,Fila[iniFila].resultado);/*faco a copia de um estado da fila e ando com ela*/
		Fila[iniFila].marca = true;/*faz a marcacao*/
		iniFila = iniFila + 1;/*retira da fila*/
		printf("inifila = %d\n",iniFila);

		move1alfa(estado,dest,tam1Estado,moveAlfa1, state,totState);

		fecho(moveAlfa1,state, Fila, dest, &fimFila, tam1Estado, totState, AFD, totAFD);
		moveAlfa1[0]='\0';
		move2alfa(estado,dest,tam1Estado,moveAlfa2,state,totState);

		fecho(moveAlfa2,state, Fila, dest, &fimFila, tam1Estado, totState, AFD, totAFD);
		moveAlfa2[0]='\0';
	}

	for(i=0;i<fimFila;i++)
	{
		strcpy(NewState[i],Fila[i].resultado);
	}

	return fimFila;
}

void AfnAfd ()
{
	char alfa[10];				/*é o alfabeto*/
	char state[10][4];			/*vai conter os estados do AFN*/
	char totstate[100];			/*faz a primeira leitura dos estados para depois jogar em state*/
	int contState; 		  		/*obtem a quantidade de estados */

	Nstate destino[100]; 		/*é um registro que vai conter a informação de quantas
									estados uma letra do alfabeto pode influenciar em um único estado
									por exemplo no delta(q0,&) = {q1,q2,q3}*/
	char q0[4];					/*estado inicial*/
	char qf[20];					/*estado final*/
	int tam; 					/*recebe o tamanho da string do estado*/
	Nstate AFD[20];				/*eh o AFD pronto, com os movimentos divididos 2 a 2,
								conforme a posicao de cada NewState*/
	char NewState[20][10];		/*sao os novos estados apos a transformacao em AFD*/
	int tamAFD=0;				/*obtem o tamanho de estados do AFD(penso dispensavel)*/
	int tamNewState;			/*Obtem o novo total de estados*/
	int i;

	printf("Digite o alfabeto separado por vírgula\n");
	__fpurge(stdin);
	fgets(alfa,10,stdin);
	retiraVirgulaAlfa(alfa);

	printf("Digite os estados separados por vírgula\n");
	__fpurge(stdin);
	fgets(totstate,100,stdin);
	contState = retiraVirgulaState(state,totstate,&tam);

	estadoInicial(state,contState,q0,qf,tam);

	read_move(state,alfa,destino,contState);

	imprime(alfa,state,q0,qf,destino,contState);

	tamNewState = delta(state, destino, tam, contState, AFD, NewState, &tamAFD);
	printf("------------------------------------------------------------\n");
	printf("%d\n",tamNewState );
	printf("\n\tNOVOS ESTADOS DO AFD\n");
	for ( i = 0; i < tamNewState; i++)
	{
		printf("%s\n",NewState[i]);
	}

}

int main()
{
	int opc;

	do {
		printf("1 - Converta AFN-AFD\n");
		scanf("%d",&opc);
		if (opc==1) {
				AfnAfd();
		}
	} while(opc == 1);

	/*__fpurge(stdin);
	fgets(a,10,stdin);
	printf("%s\n",a);
	a[strlen(a) - 1] = '\0';
	if(strcmp(a,state[0])==0)
		printf("ok\n");*/



	return 0;
}
