/*-----------------------------------------------------------------------------
OBJETIVO: 
PARAMETROS:
RETORNO:
------------------------------------------------------------------------------*/

#include <assert.h>
#include "biblosH/draw.h"
#include "biblosH/remov.h"
#include "biblosH/arquivo.h"

int main (int argc, char *argv[])
{
	int32_t op;
	int32_t n;
	int32_t h;
	A_NO *raiz = NULL;

	Abertura_ARQ(argc,argv,&raiz);

	gfx_init(1300,700,"Arvore AVL");
	do
	{
		gfx_clear();
		printf("Menu\n");
		Draw_Arv(raiz,650,50,20,1300);
		gfx_paint();
		printf("\n-----------------------------\nArvore = ");
		Imprime_NO(raiz);
		printf("\n-----------------------------");
		
		printf("\n1 = INSERIR NUMERO\n");
		printf("\n2 = REMOVER NUMERO\n");
		printf("\n3 = BUSCAR NUMERO\n");
		printf("\n4 = SAIR\n");
		scanf("%d",&op);
		switch(op)
		{
			h = 0;
			case 1:
				system("clear");
				printf("\nNumero: ");
				scanf("%d",&n);
				Insrer_ARB(&raiz,n,&h);
				
			break;

			case 2:
				system("clear");
				printf("\nNumero: ");
				printf("raiz = %d, deletado = %d, balancemento = %d .\n",raiz->chave, n, raiz->bal);
				scanf("%d",&n);
				Remov_ARV(&raiz, n, &h);
			break;

			case 3:
				system("clear");
				printf("\nNumero: ");
				scanf("%d",&n);
				Busca_ARB(raiz, n, 650, 50, 1300);
			break;
		}
	}while(op != 4);
	//gfx_quit();
	if(raiz != NULL)
		Desaloca_Arv(raiz);
	return 0;
}