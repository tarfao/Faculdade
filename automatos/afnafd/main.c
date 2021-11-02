#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

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
			printf("Entre com estado válido\n");
	}while(!cont);

	cont = false;
	ver = -1;
	do{
		printf("\nEstado final = ");
		__fpurge(stdin);
		fgets(estFinal,20,stdin);

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
		j=0;
		/*obtenho 1 a 1 estado até encontrar o '\0' para verificar se esses estados
		pertencem aos estados do AFN*/
		tamState = strlen(matriz->Nest[i]);
		if(aux[j] != '\0' )
			ver = 0;
		while(aux[j] != '\0')
		{
			l=0;
			for(k=j;k<j+tamState;k++)
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
	int j,ver,i,k,auxJ;
	int pos[10];
	j=ver=auxJ=0;

	/*verifico se tem conjunto com a mesma quantidade,
	pois se não houver já vai ser diferente e eu simplesmente adc*/
	for(i=0; i < *fimFila; i++)
	{
		if (final.cont == Fila[i].cont)
			pos[j++] = i;
	}

	if(j == 0)
	{
		Fila[*fimFila].cont = 0;
		for(i=0;i < final.cont; i++)
		{
			strcpy(Fila[*fimFila].Nest[i], final.Nest[i]);
		}
		Fila[*fimFila].cont = final.cont;
		*fimFila = *fimFila + 1;
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
			if(ver == final.cont)
				auxJ = j;
		}

		if(ver != final.cont)
		{
			for(i=0; i < final.cont; i++)
			{
				strcpy( Fila[*fimFila].Nest[i], final.Nest[i]);
			}
			Fila[*fimFila].cont = final.cont;
			*fimFila = *fimFila + 1;
		}

	}

}

void fecho (Estados *estado, Estados state, 
	Estados dest[], int *fimFila, Estados *N, int ini)
{
	/*Estados final; obtem o estado apos o fecho*/
	int pos,ver;
	int i,j;
	int indice;

	/*N->cont = 0;
	final.cont = 0;*/
	for(i=0;i<estado->cont;i++)
	{
		printf("%s-",estado->Nest[i]);
	}
	printf("\n");
	if(ini < estado->cont)
	{
		pos = obtemPosEstado(estado->Nest[ini],state);
		indice = ( (pos+1) * 3 ) - 1;

		for(i=0; i < dest[indice].cont; i++)
		{
			if(strcmp(dest[indice].Nest[i],"-") != 0)
			{
				ver = 0;
				for(j=0; j<estado->cont; j++)
				{
					if(strcmp(estado->Nest[j],dest[indice].Nest[i]) == 0)
						ver = 1;
				}

				if(ver != 1)
				{
					strcpy(estado->Nest[estado->cont],dest[indice].Nest[i]);
					estado->cont = estado->cont + 1;
				}

				ver = 0;
				for(j=0; j<N->cont; j++)
				{
					if(strcmp(estado->Nest[j],dest[indice].Nest[i])==0)
						ver = 1;
				}

				if(ver != 1)
				{
					strcpy (N->Nest[N->cont], dest[indice].Nest[i]);
					N->cont = N->cont + 1;
				}

				fecho(estado, state, dest, fimFila, N, ini + 1);
			}
		}
	}

	/*for(j=0; j < estado.cont; j++)
	{
		pos = obtemPosEstado(estado.Nest[j],state);
		if(pos != -1)
		{
			indice = ( (pos+1) * 3 ) - 1;
			for(i=0; i < dest[indice].cont; i++)
			{
				if(strcmp(dest[indice].Nest[i], "-") != 0){
					strcpy (final.Nest[final.cont], dest[indice].Nest[i]);
					strcpy (N->Nest[N->cont], dest[indice].Nest[i]);
					N->cont = N->cont + 1;
					final.cont = final.cont + 1;
				}
			}
		}
	}
	for(i=0;i<final.cont;i++)
		printf("%s ",final.Nest[i]);
	if(N->cont == 0)
	{
		strcpy(N->Nest[0],"-");
		N->cont = 1;
	}
	else{
		printf("ADC - ");
		for(i=0;i<final.cont;i++)
		{
			printf("%s ",final.Nest[i]);
		}
		adcFila(final, Fila, fimFila);
	}*/
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
	conjE.cont = 0;
	fecho(&moveAlfa1, state, dest, &fimFila, &conjE, 0);
	adcFila(moveAlfa1, Fila, &fimFila);
	printf("move1 - ");
	for(i=0;i<conjE.cont;i++)
		printf("%s ",conjE.Nest[i]);
	printf("\n");
	getchar();
	while(iniFila != fimFila)
	{
		j=0;
		moveAlfa1.cont = 0;
		while(Fila[iniFila].cont>j)
		{
			strcpy(estado,Fila[iniFila].Nest[j]); /*faco a copia de um estado da fila e ando com ela*/

			move1alfa(estado, state, dest, &moveAlfa1);

			j++;
		}
		conjE.cont = 0;
		if(moveAlfa1.cont == 0)
		{
			strcpy(moveAlfa1.Nest[0],"-");
			moveAlfa1.cont = 1;
		}
		else
		{
			fecho(&moveAlfa1, state, dest, &fimFila, &conjE, 0);
			/*fecho(moveAlfa1, Fila, state, dest, &fimFila, &conjE);*/
		}

		adcFila(moveAlfa1, Fila, &fimFila);
		for(i=0; i < moveAlfa1.cont; i++)
			strcpy(AFD[totAFD].Nest[i], moveAlfa1.Nest[i]);
		AFD[totAFD].cont = conjE.cont;
		totAFD++;

		printf("move1 - ");
		for(i=0;i<moveAlfa1.cont;i++)
			printf("%s ",moveAlfa1.Nest[i]);
		printf("\n");
		getchar();

		j=0;
		moveAlfa2.cont = 0;
		conjE.cont = 0;
		while(Fila[iniFila].cont > j){

			strcpy(estado,Fila[iniFila].Nest[j]);
			move2alfa(estado,state,dest,&moveAlfa2);

			j++;
		}

		if(moveAlfa2.cont == 0)
		{
			strcpy(moveAlfa2.Nest[0],"-");
			moveAlfa2.cont = 1;
		}
		else{
			fecho(&moveAlfa2, state, dest, &fimFila, &conjE, 0);
			/*fecho(moveAlfa2, Fila, state, dest, &fimFila, &conjE);*/
		}

		adcFila(moveAlfa2, Fila, &fimFila);

				printf("move2 - ");
		for(i=0;i<moveAlfa2.cont;i++)
			printf("%s ",moveAlfa2.Nest[i]);
		printf("\n");
		getchar();


		for(i=0; i < moveAlfa2.cont; i++)
			strcpy(AFD[totAFD].Nest[i], moveAlfa2.Nest[i]);
		AFD[totAFD].cont = moveAlfa2.cont;
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

void imprime2 (Estados state[], Estados dest[], char *alfabeto, int tot)
{
	int i,j,l,k,cont;
	cont = 0;
	alfabeto[strlen(alfabeto)-1] = '\0';

	printf("\n-------Alfabeto---------\n\t");
	printf("%s",alfabeto );
	printf("\n-------------Estados------------\n");
	for(i=0;i<tot;i++)
	{
		printf("\n%d ",i+1);
		for(j=0;j<state[i].cont;j++)
		{
			printf("%s ", state[i].Nest[j]);
		}
	}
	printf("\n----------move---------------\n");
	for(i=0;i<tot;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("\nDelta([");
			for(k=0;k<state[i].cont;k++)
			{
				printf("%s ",state[i].Nest[k]);
			}
			printf("],%c) =     ",alfabeto[j]);
			for(l=0; l < dest[cont].cont; l++)
				printf("%s ",dest[cont].Nest[l]);
			cont++;
			printf("\n");

		}
		printf("--------------------------------------------\n");
	}

}

int main ()
{
	char alfa[10];				/*é o alfabeto*/
	Estados state;			/*vai conter os estados do AFN*/
	Estados qf;					/*estado final*/
	Estados est[20]; 		/*obtem todas as movimentacoes dos estados*/
	Estados AFD[20];
	Estados NewState[10];
	char totstate[100];			/*faz a primeira leitura dos estados para depois jogar em state*/
	int totDestino=0;

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

	imprime2(NewState, AFD, alfa, nState);

	return 0;
}
