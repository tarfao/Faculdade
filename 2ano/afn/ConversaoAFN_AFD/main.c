#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <locale.h>

#define false 0
#define true 1
#define vazio -1

typedef struct estado
{
	char Nest[20][5];/*contem os estados*/
	int cont; /*conta os estados*/
}Estados;

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
		if ( !(aux[i] == ',') && !(aux[i] == '\n')) {
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

	/*N[pos].Nest[j-1] = '\0';como o fgets lê tbm o '\n' precisamos
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
		if ( !(aux[i] == ',') && aux[i]!='\n'){
			string[j++] = aux[i];
		}
		i++;
	}

	string[j] = '&'; /*ADICIONA A PALAVRA VAZIA NO ALFABETO*/
	string[j+1] = '\0';/*como o fgets lê tbm o '\n' precisamos
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
			if(!(est[k]=='\n' && est[k-1]==','))	
			{
				matriz->Nest[aux][j] = '\0'; /*ADICIONA O FINALIZADOR DE STRING TODA VEZ QUE ENCONTRAR VIRGULA*/
				matriz->cont = matriz->cont + 1;
				i++;				/*INCREMENTA PARA MUDAR A LINHA PARA OUTRA STRING DO ESTADO*/
				j=0;				/*COMEÇA DA POSICAO 0 POIS PULOU PARA A PROXIMA LINHA*/
				aux = matriz->cont;
			}
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
	char estFinal[20];
	int tamState=0;

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
			printf("Entre com um único estado válido\n");
	}while(!cont);

	do{
		cont = false;
		ver = -1;
		estFinal[0]='\0';
		printf("\nEstado final = ");
		__fpurge(stdin);
		fgets(estFinal,20,stdin);

		j=0;
		l=0;
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
		/*obtenho 1 a 1 estado até encontrar o '\0' para verificar se esses estados
		pertencem aos estados do AFN*/
		tamState = strlen(matriz->Nest[0]);
		if(aux[0] != '\0' )
			ver = 0;
		j=0;
		while(aux[j] != '\0')
		{
			l=0;
			for(k=j; k < j+tamState; k++)
			{
				oneEstate[l++] = aux[k];
			}
			oneEstate[l] = '\0';
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
			i=0;
			while(strcmp(matriz.Nest[i],aux) && i<matriz.cont ) /*VERIFICA 1 A 1 ESTADO SE CORRESPONDE COM OS DA MATRIZ*/
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
			verifica_destinos(matriz,move);
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
void imprime (char *alfa, Estados state, char *q0, Estados qf, Estados dest[])
{
	int i,j,l,cont=0;

	printf("Informações do AFN: \n");
	printf("--------------------------------------------\n");
	printf("\nAlfabeto = 			%s\n",alfa);
	printf("--------------------------------------------\n");
	printf("Estados = 		");
	for(i=0;i<state.cont;i++)
		printf("%s ",state.Nest[i]);
	printf("\n--------------------------------------------\n");
	printf("\nEstado inicial = 	%s\n", q0);
	printf("--------------------------------------------\n");
	printf("Estado final = 		");
	for(i=0; i < qf.cont; i++){
		printf(" %s ", qf.Nest[i]);
	}
	printf("\n--------------------------------------------\n");
	for(i=0;i<state.cont;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("\nDelta(%s,%c) = 		",state.Nest[i] , alfa[j]);
			for(l=0; l < dest[cont].cont; l++)
				printf("%s ",dest[cont].Nest[l]);
			cont++;
			printf("\n");

		}
		printf("--------------------------------------------\n");
	}

}

/*verifica se o estado já foi pro movimento*/
int verEstMove(Estados move, char *q)
{
	int i;

	for(i=0;i<move.cont;i++)
	{
		if(strcmp(move.Nest[i], q) == 0)
			return i;
	}

	return -1;
}

/*---------------------------------------------------------------------------
OBJETIVO: OBTER A POSICAO DE UM ESTADO
PARAMETRO: est: ESTADO QUE DESEJA OBTER A POSICAO
			state: MATRIZ COM TODOS OS ESTADOS
			tot: TOTAL DE ESTADOS DE state
RETORNO: A POSICAO DO ESTADO
---------------------------------------------------------------------------*/
int obtemPosEstado (char *est, Estados state)
{
	int i=0;

	while(i < state.cont)
	{
		if( strcmp(est,state.Nest[i])==0 )
			return i;
		i++;
	}

	return -1;
}

void move1alfa(char *estado, Estados state, Estados dest[], Estados *moveAlfa1)
{
	int pos = obtemPosEstado(estado,state);
	int indice1, indice2, i;

	if(pos != -1)
	{
		indice1 = moveAlfa1->cont;
		indice2 = pos*3;

		for(i=0; i < dest[indice2].cont; i++)
		{
			if(strcmp(dest[indice2].Nest[i],"-") != 0){
				if(verEstMove(*moveAlfa1, dest[indice2].Nest[i]) == -1){
					strcpy( moveAlfa1->Nest[indice1], dest[indice2].Nest[i]);
					moveAlfa1->cont = moveAlfa1->cont + 1;
					indice1++;
				}
			}
		}
	}

}

void move2alfa(char *estado, Estados state, Estados dest[], Estados *moveAlfa2)
{
	int pos = obtemPosEstado(estado,state);
	int indice1, indice2,i;

	if(pos != -1)
	{
		indice1 = moveAlfa2->cont;
		indice2 = (pos*3)+1;

		for(i=0; i < dest[indice2].cont; i++)
		{
			if( strcmp(dest[indice2].Nest[i], "-") != 0 ){
				if(verEstMove(*moveAlfa2, dest[indice2].Nest[i]) == -1){
					strcpy( moveAlfa2->Nest[indice1], dest[indice2].Nest[i]);
					moveAlfa2->cont = moveAlfa2->cont + 1;
					indice1++;
				}
			}
		}
	}
}



void adcAFD(int ini, Estados Fila[], Estados AFD[], int *totAFD)
{
	int i;

	for(i=0; i < Fila[ini].cont; i++)
	{
		strcpy(AFD[*totAFD].Nest[i], Fila[ini].Nest[i]);
	}

	*totAFD = *totAFD + 1;
}

void adcFila(Estados final, Estados Fila[], int *fimFila)
{
	int i;

	for(i=0;i < final.cont; i++)
	{
		strcpy(Fila[*fimFila].Nest[i], final.Nest[i]);
	}
	Fila[*fimFila].cont = final.cont;
	*fimFila = *fimFila + 1;
}

int verificaIgual(Estados final, Estados Fila[], int fimFila)
{
	int j,ver,i,k,auxJ;
	int pos[10];
	j=ver=auxJ=0;

	/*verifico se tem conjunto com a mesma quantidade,
	pois se não houver já vai ser diferente e eu simplesmente adc*/
	for(i=0; i < fimFila; i++)
	{
		if (final.cont == Fila[i].cont)
			pos[j++] = i;
	}

	if(j == 0)
	{
		return 1;	
	}
	else
	{
		while(auxJ < j)
		{
			ver = 0;
			for (i=0; i < final.cont; i++)
			{
				for(k=0; k < final.cont; k++)
				{
					if ( strcmp( final.Nest[i], Fila[pos[auxJ]].Nest[k] ) == 0 )
						ver++;
				}
			}
			auxJ++;
			if(ver == final.cont){
				auxJ = j;
				return 0;
			}
		}

		if(ver != final.cont)
		{
			return 1;
		}
		return 0;

	}

}

int verificaEstado (char *estado, Estados E)
{
	int i=0;

	while(i<E.cont && (strcmp(estado,E.Nest[i])!= 0))
	{
		i++;
	}

	if(i<E.cont)
		return 0;
	return 1;
}

void empilha (Estados *Pilha, char *estado)
{
	strcpy(Pilha->Nest[Pilha->cont++],estado);
}

void fecho (Estados estado, Estados Fila[], Estados state, Estados dest[], int *fimFila, Estados *N)
{
	Estados final; /*obtem o estado apos o fecho*/
	char q[10];
	int pos;
	int i;
	int indice;
	Estados Pilha;
	Pilha.cont = 0;

	/*empilha todo mundo*/
	for(i=0;i<estado.cont;i++)
	{
		empilha(&Pilha,estado.Nest[i]);
	}
	N->cont = 0;
	for(i=0;i<estado.cont;i++)
	{
		strcpy(N->Nest[N->cont++],estado.Nest[i]);
	}
	
	while(Pilha.cont != vazio)
	{
		strcpy(q,Pilha.Nest[--Pilha.cont]);
		pos = obtemPosEstado(q,state);
		final.cont = 0;
		if(pos != -1)
		{
			indice = ( (pos+1) * 3 ) - 1;
			for(i=0; i < dest[indice].cont; i++)
			{
					strcpy (final.Nest[final.cont], dest[indice].Nest[i]);
					final.cont = final.cont + 1;
			}

			for(i=0;i<final.cont;i++)
			{
				if(strcmp(final.Nest[i],"-")!=0){
					if(verificaEstado(final.Nest[i],*N)){
						strcpy(N->Nest[N->cont++],final.Nest[i]);
						empilha(&Pilha,final.Nest[i]);
					}
				}
			}	
		}
	}
	if(N->cont ==  0)
	{
		strcpy(N->Nest[N->cont++],"-");
	}
	/*for(i=0;i<final.cont;i++)
		printf("%s ",final.Nest[i]);*/
	if(verificaIgual(*N,Fila,*fimFila))
		adcFila(*N, Fila, fimFila);

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
int delta (Estados state, Estados dest[], Estados AFD[], Estados NewState[])
{
	int iniFila=0				/*trabalho com fila para ver as marcacoes*/;
	int fimFila=0;				/*final da fila para poder retirar um estado*/
	Estados Fila[20];			/*o registro trabalho com fila para enfileirar os estados novos*/
	char estado[4];			/*obtem um estado da fila para fazer o fecho do delta do estado*/
	Estados moveAlfa1;	/*obtem o movimento de um estado com a primeira letra do alfabeto*/
	Estados moveAlfa2;	/*obtem o movimento de um estado com a segunda letra do alfabeto*/
	Estados conjE;		/*obtem o conjunto final de estados após o fecho, para poder adc no AFD*/
	int i,j;
	int totAFD;

	totAFD = 0;
	strcpy ( moveAlfa1.Nest[0], state.Nest[0] );
	moveAlfa1.cont = 1;
	fecho(moveAlfa1, Fila, state, dest, &fimFila, &conjE);
	while(iniFila != fimFila)
	{
		j=0;
		moveAlfa1.cont = 0;
		/*printf("Fila - ");
		for(i=0;i<Fila[iniFila].cont;i++)
			printf("%s ",Fila[iniFila].Nest[i]);
		printf("\n");*/
		while(Fila[iniFila].cont>j)
		{
			strcpy(estado,Fila[iniFila].Nest[j]); /*faco a copia de um estado da fila e ando com ela*/

			move1alfa(estado, state, dest, &moveAlfa1);

			j++;
		}

		/*printf("move1 - ");
		for(i=0;i<moveAlfa1.cont;i++)
			printf("%s ",moveAlfa1.Nest[i]);
		printf("\n");*/
		if(moveAlfa1.cont == 0)
		{
			strcpy(conjE.Nest[0],"-");
			conjE.cont = 1;
		}
		/*else
		{*/
		fecho(moveAlfa1, Fila, state, dest, &fimFila, &conjE);
		/*}*/

		for(i=0; i < conjE.cont; i++)
			strcpy(AFD[totAFD].Nest[i], conjE.Nest[i]);
		AFD[totAFD].cont = conjE.cont;
		totAFD++;

		j=0;
		moveAlfa2.cont = 0;
		while(Fila[iniFila].cont > j){

			strcpy(estado,Fila[iniFila].Nest[j]);
			move2alfa(estado,state,dest,&moveAlfa2);

			j++;
		}
		/*printf("move2 - ");
		for(i=0;i<moveAlfa2.cont;i++)
			printf("%s ",moveAlfa2.Nest[i]);
		printf("\n");*/
		if(moveAlfa2.cont == 0)
		{
			strcpy(conjE.Nest[0],"-");
			conjE.cont = 1;
		}
		/*else{*/
		fecho(moveAlfa2, Fila, state, dest, &fimFila, &conjE);
		/*}*/

		for(i=0; i < conjE.cont; i++)
			strcpy(AFD[totAFD].Nest[i], conjE.Nest[i]);
		AFD[totAFD].cont = conjE.cont;
		totAFD++;

		iniFila = iniFila + 1;/*retira da fila*/
	}

	for(i=0;i<fimFila;i++)
	{
		for(j=0; j<Fila[i].cont; j++){
			strcpy(NewState[i].Nest[j],Fila[i].Nest[j]);
		}
		NewState[i].cont = Fila[i].cont;
	}

	return fimFila;
}

int ObtemQf(Estados *NQF, Estados qf, Estados state[], int tot)
{
	int i,j,k,l;
	int aux=0;

	i=0;
	while(i<qf.cont)/*varia os estados finais do afn*/
	{
		j=0;
		while(j<tot)/*varia todos os novos estados do afd d*/
		{
			k=0;
			while(k<state[j].cont)/*varia o conjunto de estados do afd*/
			{
				/*verifica se há o estado final em um conjunto para imprimir o conjunto*/
				if(strcmp(qf.Nest[i],state[j].Nest[k++]) == 0)
				{
					if(verificaIgual(state[j],NQF,aux)){
						for(l=0;l<state[j].cont;l++)
						{
							strcpy(NQF[aux].Nest[l], state[j].Nest[l]);
						}
						NQF[aux].cont = state[j].cont;
						aux++;
						k = state[j].cont;
						/*printf("\n");*/
					}
				}
			}
			j++;
		}
		i++;
	}
	return aux;
}

void imprime2 (Estados state[], Estados dest[], char *alfabeto, int tot, Estados qf[], int totqf)
{
	int i,j,l,k,cont;
	cont = 0;
	alfabeto[strlen(alfabeto)-1] = '\0';

	printf("\n-------Alfabeto---------\n\t");
	printf("%s",alfabeto );
	printf("\n-------------Estados------------\n");
	for(i=0;i<tot;i++)
	{
		printf("\n%d = [",i+1);
		for(j=0;j<state[i].cont;j++)
		{
			printf("%s ", state[i].Nest[j]);
		}
		printf("]");
	}
	printf("\n--------------Estados finais------------------\n");
	for(i=0;i<totqf;i++)
	{
		printf("\n[");
		for(j=0;j<qf[i].cont;j++)
		{
			printf("%s ",qf[i].Nest[j]);
		}
		printf("]");
	}
	printf("\n----------move---------------\n");
	for(i=0;i<tot;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("\nd([");
			for(k=0;k<state[i].cont;k++)
			{
				printf("%s ",state[i].Nest[k]);
			}
			printf("],%c) =     [",alfabeto[j]);
			for(l=0; l < dest[cont].cont; l++)
				printf("%s ",dest[cont].Nest[l]);
			cont++;
			printf("]\n");

		}
		printf("--------------------------------------------\n");
	}

}

int main ()
{
	setlocale(LC_ALL, "Portuguese");
	char alfa[10];				/*é o alfabeto*/
	Estados state;			/*vai conter os estados do AFN*/
	Estados qf;					/*estado final*/
	Estados est[50]; 		/*obtem todas as movimentacoes dos estados*/
	Estados AFD[20];
	Estados NewState[20];
	char totstate[100];			/*faz a primeira leitura dos estados para depois jogar em state*/
	int totDestino=0;
	Estados NewQf[10];
	int totQF;
	char q0[4];					/*estado inicial*/
	int nState;

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

	nState = delta(state, est, AFD, NewState);

	totQF = ObtemQf(NewQf,qf,NewState,nState);

	imprime2(NewState, AFD, alfa, nState,NewQf,totQF);

	return 0;
}
