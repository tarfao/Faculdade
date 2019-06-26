/*-----------------------------------------------------------------------------
OBJETIVO: 
PARAMETROS:
RETORNO:
------------------------------------------------------------------------------*/

typedef struct ar{
	int32_t chave:28;
	int32_t bal:2;
	int32_t reservado:2;
	struct ar *esq;
	struct ar *dir;
}A_NO;

typedef struct s_arq_no
{
    int32_t chave:28;
    int32_t bal:2;
    uint32_t esq:1;
    uint32_t dir:1;
}A_NO_ARQ;

/*----------------------------------------------------------------------------
OBJETIVO: DESENHAR O CÍRCULO DA ÁRVORE
PARÂMETROS: c - CHAVE DO NÓ
			b - BALANÇO DO NÓ
			x, y, E r SÃO OS PARÂMETROS PARA DESENHAR A CIRCUNFERENCIA
-----------------------------------------------------------------------------*/
void Draw_Seta(int x, int y)
{
	gfx_set_color(255,0,0);
	gfx_line(x-10,y+15,x+10,y-15);
	gfx_line(x-10,y-15,x+10,y+15);
	gfx_paint();
	sleep(1.5);
}


/*------------------------------------------------------------------------
OBJETIVO: BUSCAR UM NO NA ARVORE
PARAMETROS:
			pt - RAIZ DE UMA SUBÁRVORE
			x - QUE É O A CHAVE A SER PROCURADA
RETORNO: O PONTEIRO PARA O NÓ QUE ESTÁ BUSCANDO, OU RETORNA O PONTEIRO DO
			NÓ QUE SERIA PAI DELE
--------------------------------------------------------------------------*/
void Busca_ARB(A_NO *pt, int32_t x, int dx, int dy, int l)
{
	int x1;

	x1 = (l - dx)/2;

	if(x1<0)
		x1 = x1*(-1);

	if (pt == NULL)
	{
		printf("!!!!CHAVE NAO ENCONTRADA!!!!!\n");
	}
	else
	{
		if(x == pt->chave)
		{
			Draw_Seta(dx,dy);
		}
		else
		{
			if( x < pt->chave )
			{
				if ( pt->esq != NULL)
				{
					pt = pt->esq;
					Busca_ARB(pt,x,dx-x1,dy+50,dx);
				}
			}
			else
			{
				if(pt->dir != NULL)
				{
					pt = pt->dir;
					Busca_ARB(pt,x,dx+x1,dy+50,dx);
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	FAZER UMA ROTAÇÃO DIREITA OU DUPLA DIREITA
PARAMETROS:	rz - RAIZ DA ÁRVORE
			h - VALIDADOR
------------------------------------------------------------------------------*/
void caso1(A_NO **rz, int32_t *h)
{
	A_NO *ptu;
	A_NO *ptv;

	ptu = (*rz)->esq;

	if(ptu->bal == -1)
	{
		(*rz)->esq = ptu->dir;
		ptu->dir = *rz;
		(*rz)->bal = 0;
		*rz = ptu;
	}
	else
	{
		ptv = ptu->dir;

		ptu->dir = ptv->esq;
		ptv->esq = ptu;
		(*rz)->esq = ptv->dir;
		ptv->dir = *rz;

		if(ptv->bal == -1)
			(*rz)->bal = 1;
		else
			(*rz)->bal = 0;

		if(ptv->bal == 1)
			ptu->bal = -1;
		else
			ptu->bal = 0;

		*rz = ptv;
	}

	(*rz)->bal = 0;
	*h = 0;
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	FAZER UMA ROTAÇÃO ESQUERDA OU DUPLA ESQUERDA
PARAMETROS:	rz - RAIZ DA ÁRVORE
			h - VALIDADOR
------------------------------------------------------------------------------*/
void caso2 (A_NO **rz, int32_t *h)
{
	A_NO *ptu = (*rz)->dir;
	A_NO *ptv = ptu->esq;

	if(ptu->bal == 1)
	{
		(*rz)->dir = ptu->esq;
		ptu->esq = *rz;
		(*rz)->bal = 0;
		*rz = ptu;
	}
	else
	{
		ptu->esq = ptv->dir;
		ptv->dir = ptu;
		(*rz)->dir = ptv->esq;
		ptv->esq = *rz;

		if(ptv->bal == 1)
			(*rz)->bal = -1;
		else
			(*rz)->bal = 0;

		if(ptv->bal == -1)
			ptu->bal = 1;
		else
			ptu->bal = 0;

		*rz = ptv;
	}
	(*rz)->bal = 0;
	*h = 0;
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	INSERIR UM NÓ NA ÁRVORE(SÃO TODAS DIFERENTES)
PARAMETROS:	rz - RAIZ DA ÁRVORE
			x - NUMERO A SER INSERIDO
------------------------------------------------------------------------------*/
void Insrer_ARB(A_NO **rz, int32_t x, int32_t *h)
{

	if(*rz == NULL)
	{
		
		assert(((*rz) = malloc(sizeof(A_NO))) != NULL);
		(*rz)->chave = x;
		(*rz)->esq = NULL;
		(*rz)->dir = NULL;
		(*rz)->bal = 0;
		*h = 1;
	}
	else
	{
		if(x == (*rz)->chave)
		{
			printf("CHAVE JA ESTA CONTIDA!!\n");
			*h = 0;
		}
		else
		{
			if (x < (*rz)->chave)
			{
				Insrer_ARB(&(*rz)->esq, x, h);
				if(*h == 1)
				{
					switch((*rz)->bal)
					{
						case 1:
							(*rz)->bal = 0;
							*h = 0;
						break;

						case 0:
							(*rz)->bal = -1;
						break;

						case -1:
							caso1(rz,h);
						break;
					}
				}
			}
			else
			{
				Insrer_ARB(&((*rz)->dir), x, h);
				if(*h == 1)
				{
					switch((*rz)->bal)
					{
						case 1:
							caso2(rz,h);
						break;

						case 0:
							(*rz)->bal = 1;
						break;

						case -1:
							(*rz)->bal = 0;
							*h = 0;
						break;
					}
				}
			}
		}
		
	}
}

/*-----------------------------------------------------------------------------
OBJETIVO:   MOSTRAR TODOS OS NÓS DA ÁRVORE (PÓS ORDEM)
PARAMETROS:	A RAIZ DA ARVORE
RETORNO: 	NENHUM
------------------------------------------------------------------------------*/
void Imprime_NO(A_NO *pt)
{
	printf("%d ",pt->chave);

	if(pt->esq != NULL)
		Imprime_NO(pt->esq);
	if(pt->dir != NULL)
		Imprime_NO(pt->dir);
}

/*-----------------------------------------------------------------------------
OBJETIVO:   DESALOCAR OS NÓS DA ÁRVORE (PRÉ ORDEM)
PARAMETROS:	A RAIZ DA ARVORE
RETORNO: 	NENHUM
------------------------------------------------------------------------------*/
void Desaloca_Arv (A_NO *pt)
{
	if(pt->esq != NULL)
		Desaloca_Arv(pt->esq);
	if(pt->dir != NULL)
		Desaloca_Arv(pt->dir);

	free(pt);
}

