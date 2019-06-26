
/*---------------------------------------------------------------------------------
OBJETIVO: MOVER O NÓ DO VETOR NA POSIÇÃO pos PARA A ÁRVORE
PARAMETROS: V - O VETOR COM OS NÓS QUE ESTAVAM NO ARQUIVO
			pos - É A POSICAO DO NÓ QUE VAMOS OBTER DO VETOR
			PT - PONTEIRO PARA A RAIZ DA ÁRVORE
----------------------------------------------------------------------------------*/
void move(A_NO **pt, A_NO_ARQ* V, unsigned pos)
{
	(*pt) = malloc(sizeof(A_NO));
	(*pt)->chave = V[pos].chave;
	(*pt)->bal = V[pos].bal;
	(*pt)->dir = NULL;
	(*pt)->esq = NULL;
}


/*---------------------------------------------------------------------------------
OBJETIVO: CONSTRUIR A ÁRVORE
PARAMETROS: V - O VETOR COM OS NÓS QUE ESTAVAM NO ARQUIVO
			N - O NÚMERO TOTAL DE NÓS
			ini - INICIO DO VETOR, PARA FAZER RECURSÃO
			PT - PONTEIRO PARA A RAIZ DA ÁRVORE
----------------------------------------------------------------------------------*/
void Build_Arv (A_NO_ARQ *V, unsigned N, unsigned* ini, A_NO **pt)
{
	unsigned pos; 
	if(*ini<N)
	{
		pos = *ini;
		move(pt,V,pos);
		//printf("-->%d\n",pos);
		if(V[pos].esq != 0){
			*ini = *ini + 1;
			Build_Arv(V,N,ini,&(*pt)->esq);
		}
		if(V[pos].dir != 0)
		{
			*ini = *ini + 1;
			Build_Arv(V,N,ini,&(*pt)->dir);
		}
	}	
}

/*-----------------------------------------------------------------------------------
OBJETIVO: ABRIR O ARQUIVO DE NOME QUE O USUÁRIO DIGITOU
PARAMETROS: argc - A QUANTIDADE DE ARGUMENTOS QUE FOI DIGITADO
			argv - OS ARGUMENTOS QUE FORAM DIGITADOS
			pt - A RAIZ DA ÁRVORE QUE VAMOS CONTRUIR
------------------------------------------------------------------------------------*/
void Abertura_ARQ (int argc, char *argv[], A_NO **pt)
{
	A_NO_ARQ* V;
	FILE* fp;	
	unsigned N;
	char fnamein[256];
	unsigned i=0;


	if( argc != 2 )
	{
		printf("Uso: %s NomeArq.avl\n", argv[0]);
		exit(0);
	}

	strcpy(fnamein,argv[1]);

	assert((fp = fopen(fnamein,"r")) != NULL);
	fseek(fp,0,SEEK_END);/*move para o final para obter a quantidade de numeros no arquivo*/
    N = ftell(fp)/sizeof(A_NO_ARQ);
    rewind(fp);/*move o ponteiro para o início do arquivo para fazermos a leitura direta*/
    assert ((V = malloc(sizeof(A_NO_ARQ)*N)) != NULL);
    fread(V,sizeof(A_NO_ARQ),N,fp);
    fclose(fp);

    Build_Arv(V,N,&i,pt);

	free(V);

}