

/*-----------------------------------------------------------------------------
OBJETIVO: 	FAZER UMA ROTAÇÃO DIREITA OU DUPLA DIREITA
PARAMETROS:	rz - RAIZ DA ÁRVORE
			h - VALIDADOR
------------------------------------------------------------------------------*/
void caso1R(A_NO **rz, int* h)
{
	A_NO *ptu;
	A_NO *ptv;

	ptu = (*rz)->esq;
	printf("antes caso1R");
	if(ptu->bal == 0 || ptu->bal == -1)
	{
		(*rz)->esq = ptu->dir;
		ptu->dir = *rz;
		if(ptu->bal == 0){
			(*rz)->bal = -1;
            *h = 0;
        }
		else{
			(*rz)->bal = 0;
            *h = 1;
        }

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
        *h = 0;
	}
	printf("Depois caso1R");
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	FAZER UMA ROTAÇÃO ESQUERDA OU DUPLA ESQUERDA
PARAMETROS:	rz - RAIZ DA ÁRVORE
			h - VALIDADOR
------------------------------------------------------------------------------*/
void caso2R (A_NO **rz, int* h)
{
	A_NO *ptu = (*rz)->dir;
	A_NO *ptv = ptu->esq;

	if(ptu->bal != -1)
	{
		(*rz)->dir = ptu->esq;
		ptu->esq = *rz;
		if(ptu->bal == 0){
			(*rz)->bal = 1;
            *h = 0;
        }
		else{
			(*rz)->bal = 0;
            *h = 1;
        }
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
        *h = 1;
	}
}

/*----------------------------------------------------------------------------
OBJETIVO: PROCURAR O SUCESSOR DE UM NÓ
PARÂMETRO: O PT->ESQUERDA(**rz) SENDO PT O NÓ QUE VAMOS PROCURAR O ANTECESSOR
RETORNO: O PAI DO NÓ QUE É O ANTECESSOR
------------------------------------------------------------------------------*/
void Antecessor(A_NO **rz, A_NO **ant, int *h)
{

    if ((*rz)->dir == NULL)
    {
        (*ant) = *rz;
        //*rz = NULL;
        *h = 1;
    }
    else
    {
        Antecessor(&(*rz)->dir,ant,h);
        if (*h == 1)
        {
            switch((*rz)->bal)
            {
                case 1:
                    (*rz)->bal = 0;
                break;

                case 0:
                    (*rz)->bal = -1;
                    *h = 0;
                break;

                case -1:
                    caso1R(rz,h);
                break;
            }
        }
    }
}

/*-----------------------------------------------------------------------------
OBJETIVO: 	INSERIR UM NÓ NA ÁRVORE(SÃO TODAS DIFERENTES)
PARAMETROS:	rz - RAIZ DA ÁRVORE
			x - NUMERO A SER INSERIDO
------------------------------------------------------------------------------*/
void Remov_ARV(A_NO **rz, int32_t x, int32_t *h)
{
	A_NO *del, *antecessor=NULL; /**pred, *pai; nó que sera deletado e o predecessor*/

	if(*rz == NULL)
	{
		system("clear");
		printf("Chave nao existe!!!!!\n");
	}
	else
	{
		if(x == (*rz)->chave)
		{
			del = *rz;
			if((*rz)->esq == NULL && (*rz)->dir == NULL)
			{
				*rz = NULL;
                *h = 1;
			}
			else
			{
				if((*rz)->esq != NULL)
				{
					Antecessor(&(*rz)->esq,&antecessor,h); /*obtem o antecessor do número a ser deletado*/
					if(antecessor == (*rz)->esq)
					{
						antecessor->dir = (*rz)->dir;
					}
					else
					{
                    	antecessor->esq = (*rz)->esq;
						antecessor->dir = (*rz)->dir;
					}

					switch((*rz)->bal)
					{
						case 1:
							caso1R(rz,h);
						break;

						case 0:
							antecessor->bal = 1;
						break;

						case -1:
							antecessor->bal = 0;
						break;
					}
					(*rz) = antecessor;

				}
				else
				{
					*rz = (*rz)->dir;
					*h = 1;
				}
      		}
			free(del);
		}
		else
		{
			if (x < (*rz)->chave)
			{
				Remov_ARV(&((*rz)->esq), x, h);
				if(*h == 1)
				{
					switch((*rz)->bal)
					{
						case 1:
							caso2R(rz,h);
						break;

						case 0:
							(*rz)->bal = 1;
							*h = 0;
						break;

						case -1:
							(*rz)->bal = 0;
						break;
					}
				}
			}
			else
			{
				Remov_ARV(&((*rz)->dir), x, h);
				if(*h == 1)
				{
					switch((*rz)->bal)
					{
						case 1:
							(*rz)->bal = 0;
						break;

						case 0:
							(*rz)->bal = -1;
							*h = 0;
						break;

						case -1:
							caso1R(rz,h);
						break;
					}
				}
			}
		}
		
	}
}
