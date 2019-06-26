#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#define true 1
#define false 0
#define vazio -1

typedef struct estado
{
	char Nest[20][5];/*contem os estados*/
	int cont; /*conta os estados*/
}Estados;

typedef struct NState {/*tem o objetivo de obter os movimentos de um estado (seja ele do afd ou afn)
						com as letras do alfabeto*/
	char locale[20];
}Nstate;

typedef struct TMarcas {/*tem o objetivo de simular uma fila quando encontramos um
						novo estado após fazer o fecho de um E[d(x,&)]*/
	char resultado[20];
	int marca;
}TMarcas;

void inicializa (Estados *N, int pos)
{
	N[pos].cont=0;
}

/*---------------------------------------------------------------------------
OBJETIVO: RETIRAR AS VÍRGULAS DE UM MOVIMENTO DO N
PARAMETRO: N: QUE É A MOVIMENTACAO DOS ESTADOS COM AS LETRAS DO ALFABETO
			pos: QUE É A POSICAO DO ESTADO QUE SE DESEJA RETIRAR VIRGULA
			*aux que são os movimentos
---------------------------------------------------------------------------*/
void retiraVirgulaMove (char *aux, int pos, Estados *N)
{
	int i,j;
	i=j=0;
	

	while( !(aux[i] == '\0') )
	{
		if ( !(aux[i] == ',') && !(aux[i] == '\n')){
			N[pos].Nest[N[pos].cont][j++] = aux[i];
		}
		else
		{
			N[pos].Nest[N[pos].cont][j] = '\0';	
			N[pos].cont = N[pos].cont + 1;
			j=0;
		}
		i++;
	}
	/*N[pos].Nest[j-1] = '\0';/*como o fgets lê tbm o '\n' precisamos
						colocar o '\0' no seu lugar para finalizar a string*/
}

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
void retiraVirgulaState (Estados *matriz, char est[])
{
	int i,j,k;
	int aux=0;
	j=i=k=0;

	inicializa(matriz,0);
	while( !(est[k] == '\0') ) /*PROCURA ATÉ ENCONTRAR O FINAL DA STRING*/
	{
		if ( !(est[k] == ',') && !(est[k] == '\n')){
			matriz->Nest[aux][j] = est[k];
			j++;
		}
		else
		{
			matriz->Nest[aux][j] = '\0'; /*ADICIONA O FINALIZADOR DE STRING TODA VEZ QUE ENCONTRAR VIRGULA*/
			matriz->cont = matriz->cont + 1;
			i++;				/*INCREMENTA PARA MUDAR A LINHA PARA OUTRA STRING DO ESTADO*/
			j=0;				/*COMEÇA DA POSICAO 0 POIS PULOU PARA A PROXIMA LINHA*/
			aux = matriz->cont;
		}
		k++;
	}
}

/*---------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DO ESTADO INICIAL E FINAL
PARAMETROS: A MATRIZ COM OS ESTADOS
			tot: QUE É O TOTAL DE ESTADOS
			*q0: QUE É O ESTADO INICIAL
			*qf: QUE É O ESTADO FINAL
---------------------------------------------------------------------------*/
void estadoInicial (Estados *matriz, char *q0, Estados *qf)
{
	int i;
	char aux[20];	/*auxilia quando obtemos o estado inicial para copiar ele para o primeiro estado*/
	char oneEstate[4];/*obtem um estado para verificar se está em matriz*/
	int cont = false;
	int j,k,l;
	int ver;  /*VERIFICA QUANTAS VEZES ENTROU NO FOR, QUE REPRESENTA QUANTOS ESTADOS FINAIS POSSUI*/
	int tam; /*obtem obtem o tamanho de qf*/
	char estFinal[20];
	int tamState;

	do{
		printf("\nEstado inical = ");
		__fpurge(stdin);
		fgets(q0,4,stdin);

		q0[strlen(q0)-1] = '\0';/*COLOCA O FINALIZADOR POIS FGETS LÊ O '\n'*/
		i=0;

		while(!(strcmp(matriz->Nest[i],q0)==0) && i < matriz->cont)
		{
			i++;
		}

		if(i < matriz->cont){/*se estado incial e valido eu o coloco na primeira posicao*/
			cont = true;

			strcpy(aux,matriz->Nest[0]);
			strcpy(matriz->Nest[0],matriz->Nest[i]);
			strcpy(matriz->Nest[i],aux);
		}

		if(!cont)
			printf("Entre com estado válido\n");
	}while(!cont);

	cont = false;
	ver = 0;
	do{
		printf("\nEstado final = ");
		__fpurge(stdin);
		fgets(estFinal,20,stdin);

		tam = strlen(estFinal);
		estFinal[tam-1] = '\0';

		j=0;
		l=0;
		printf("%s\n", estFinal);
		/*retiro todas as vírgulas e também o '\n' da string para outra string*/
		while(estFinal[j] != '\0')
		{
			if(estFinal[j]!=',' && estFinal[j]!='\n')
			{
					aux[l++] = estFinal[j];
			}
			j++;
		}
		aux[l] = '\0';
		printf("%s\n",aux );
		j=0;
		tamState = strlen(matriz->Nest[i]);
		/*obtenho 1 a 1 estado até encontrar o '\0' para verificar se esses estados
		pertencem aos estados do AFN*/
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
			for(i=0;i<matriz->cont;i++)
			{
				if( !(strcmp(matriz->Nest[i],oneEstate)) )
				{
					cont++;
				}
			}

		}
		printf("ver = %d  cont = %d\n",ver,cont);

		if(cont != ver)
			printf("Entre com estado válido\n");
	}while(cont != ver);
	inicializa(qf,0);
	retiraVirgulaMove(estFinal,0,qf);

}

/*---------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE OS DESTINOS DE UM CERTO ESTADO COM x LETRA DO ALFABETO
			ESTÃO NA MATRIZ DE ESTADOS
PARÂMETROS: A MATRIZ DE ESTADOS
			dest: DESTINO DE UM ESTADO
---------------------------------------------------------------------------*/
void verifica_destinos (Estados matriz, char *dest)
{
	int i=0;
	char aux[4];
	int j=0,k=0;

	if(dest[j] != '-')/*VERIFICA SE NAO EH ESTADO VAZIO*/
	{
		while(dest[j] != '\0')
		{
			while(dest[j] != ',' && dest[j] != '\0' && dest[j] != '\n')
				aux[k++] = dest[j++];/*OBTEM UM ESTADO PURO, SOMENTE SUA STRING*/
			
			j++;
			aux[k] = '\0';
			k = 0;
			printf("%s\n",aux );
			i=0;
			while(strcmp(matriz.Nest[i],aux) && matriz.cont ) /*VERIFICA 1 A 1 ESTADO SE CORRESPONDE COM OS DA MATRIZ*/
				i++;

			if(!(i < matriz.cont)) /*CASO ELE PASSE DA POSICAO ACESSÍVEL O PROGRAMA PARA*/
				exit(100);
		}
	}
}


/*---------------------------------------------------------------------------
OBJETIVO: FAZER A LEITURA DOS MOVIMENTOS DOS ESTADOS COM AS LETRAS DO ALFABETO
PARAMETROS: matriz: CONTENDO TODOS OS ESTADOS
			alfa: CONTENDO O ALFABETO DA MAQUINA
			N: QUE É O QUE VAI ADQUIRIR TODOS OS MOVIMENTOS DE UM ESTADO
			totState: TOTAL DE ESTADOS DA MATRIZ
---------------------------------------------------------------------------*/
void read_move (Estados matriz, char alfa[], Estados N[], int *totN)
{
	int i,j,cont=0;
	char move[20];

	printf("\n[obs: entre com os estados separados por vírgula]\n");

	for(i=0;i<matriz.cont;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("Delta(%s,%c) = ",matriz.Nest[i] , alfa[j]);
			__fpurge(stdin);
			fgets(move,20,stdin);
			verifica_destinos(matriz,totState,move);
			inicializa(N,cont);
			retiraVirgulaMove(move,cont,N);
			cont++;
		}
	}
	*totN = cont;
}


/*---------------------------------------------------------------------------
OBJETIVO: IMPRIMIR AS INFORMAÇÕES DO AFN
---------------------------------------------------------------------------*/
void imprime (char *alfa, Estados state, char *q0, Estados qf, Estados *dest, int totDest)
{
	int i,j,l,cont=0;

	printf("Informações do AFN: \n");
	printf("--------------------------------------------\n");
	printf("\nAlfabeto = 			%s\n",alfa);
	printf("--------------------------------------------\n");
	printf("Estados = 			");
	for(i=0;i<state.cont;i++)
		printf("%s ",state.Nest[i]);
	printf("\n--------------------------------------------\n");
	printf("\nEstado inicial = 	%s\n", q0);
	printf("--------------------------------------------\n");
	printf("Estado final = 		");
	for(i=0; i < qf.cont; i++){
		printf(" %s ", qf.Nest[i]);
	}
	printf("--------------------------------------------\n");
	for(i=0;i<state.cont;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("\nDelta(%s,%c) = 		",state.Nest[i] , alfa[j]);
			for(l=0; l < dest[cont].cont; l++)
				printf(" %s ",dest[cont].Nest[l]);
			cont++;

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
void fecho (char *estado, char state[][4], TMarcas *Fila, Estados *N,
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

	if(estado[i] != '-')
	{/*representação de vazio*/
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
				while(N[(pos+1)*3-1].cont < l)
				{
					/*separa um estado da string para poder verificar se já esta em estFinal*/
					strcpy(est1Dest,N[(pos+1)*3-1].Nest[l])

					l++;
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
				strcpy(estFinal,N[(pos+1)*3-1].Nest[l]);

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
			int totState, Nstate AFD[], char NewState[][10], int *totAFD, Estados *N)
{
	int iniFila=0				/*trabalho com fila para ver as marcacoes*/;
	int fimFila=0;				/*final da fila para poder retirar um estado*/
	Estados Fila[20];			/*o registro trabalho com fila para enfileirar os estados novos*/
	Estados estado;			/*obtem um estado da fila para fazer o fecho do delta do estado*/
	Estados moveAlfa1;	/*obtem o movimento de um estado com a primeira letra do alfabeto*/
	Estados moveAlfa2;	/*obtem o movimento de um estado com a segunda letra do alfabeto*/
	int aux;					/*um simples auxiliar para fazer a primeira chamada do fecho*/
	Nstate aux1[2];				/*o mesmo acima*/
	int i,j;

	estado.cont = 0;
	moveAlfa1.cont = 0;
	moveAlfa2.cont = 0;
	fecho(state[0], state, Fila, N, &fimFila, tam1Estado, totState,aux1,&aux);
	printf("%i\n",fimFila );
	while(iniFila != fimFila)
	{
		j=0;
		while(Fila[iniFila].cont>j)
		{
			printf("fimfila = %d\n", fimFila);
			printf("Entrou\n");
			strcpy(estado,Fila[iniFila].Nest[j]);/*faco a copia de um estado da fila e ando com ela*/
			Fila[iniFila].marca = true;/*faz a marcacao*/
			printf("inifila = %d\n",iniFila);
			move1alfa(estado,dest,tam1Estado,moveAlfa1,state,totState,j);

			j++;
		}


		fecho(moveAlfa1,state, Fila, dest, &fimFila, tam1Estado, totState, AFD, totAFD);
		moveAlfa1[0]='\0';
		move2alfa(estado,dest,tam1Estado,moveAlfa2,state,totState);

		fecho(moveAlfa2,state, Fila, dest, &fimFila, tam1Estado, totState, AFD, totAFD);
		moveAlfa2[0]='\0';

		iniFila = iniFila + 1;/*retira da fila*/
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
	Estados state;			/*vai conter os estados do AFN*/
	state.cont=0;
	char totstate[100];			/*faz a primeira leitura dos estados para depois jogar em state*/

	Estados destino[20]; 		/*é um registro que vai conter a informação de quantas
									estados uma letra do alfabeto pode influenciar em um único estado
									por exemplo no delta(q0,&) = {q1,q2,q3}*/
	int totDestino=0;

	char q0[4];					/*estado inicial*/
	Estados qf;					/*estado final*/
	Nstate AFD[20];				/*eh o AFD pronto, com os movimentos divididos 2 a 2,
								conforme a posicao de cada NewState*/
	Estados NewState[20];		/*sao os novos estados apos a transformacao em AFD*/
	int tamAFD=0;				/*obtem o tamanho de estados do AFD(penso dispensavel)*/
	int tamNewState;			/*Obtem o novo total de estados*/
	int i;
	Estados est[20]; 		/*obtem todas as movimentacoes dos estados*/

	printf("Digite o alfabeto separado por vírgula\n");
	__fpurge(stdin);
	fgets(alfa,10,stdin);
	retiraVirgulaAlfa(alfa);

	printf("Digite os estados separados por vírgula\n");
	__fpurge(stdin);
	fgets(totstate,100,stdin);
 	retiraVirgulaState(&state,totstate);

	estadoInicial(&state,q0,&qf);

	read_move(state,alfa,est,&totDestino);

	imprime(alfa,state,q0,qf,destino,totDestino);

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
