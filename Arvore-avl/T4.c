#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#define tam1 1300
#define tam2 700
typedef struct s_no
{
	int32_t chave:28;
	int32_t bal:2;
	int32_t reservado:2; /* sem uso */
	struct s_no* esq;
	struct s_no* dir;
}NO;

void inicio_no(NO **pt,int32_t x)
{
	//NO *pt;
	(*pt)=malloc(sizeof(NO));
	if((*pt)!=NULL)
	{
		(*pt)->esq=NULL;
		(*pt)->dir=NULL;
		(*pt)->chave=x;
		(*pt)->bal=0;

	}
}
void caso1(NO **arv,char *h)
{
	NO *ptu,*ptv;
	ptu=(*arv)->esq;
	if(ptu->bal==-1)
	{
		(*arv)->esq=ptu->dir;
		ptu->dir=(*arv);
		(*arv)->bal=0;
		(*arv)=ptu;
		
	}
	else
	{
		ptv=ptu->dir;
		ptu->dir=ptv->esq;
		ptv->esq=ptu;
		(*arv)->esq=ptv->dir;
		ptv->dir=(*arv);
		//printf("\nd1");
		if(ptv->bal==-1)
		{
			(*arv)->bal=1;
			//printf("\nd2");
		}
		else
		{
			(*arv)->bal=0;
			//printf("\nd3");
		}
		if(ptv->bal==1)
		{
			ptu->bal=-1;
			//printf("\nd4");
		}
		else
		{
			ptu->bal=0;
			//printf("\nd5");
		}
		(*arv)=ptv;
	}
	(*arv)->bal=0;
	*h='f';
}

void caso2(NO **arv,char *h)
{
	NO *ptu,*ptv;
	ptu=(*arv)->dir;
	if(ptu->bal==1)
	{
		(*arv)->dir=ptu->esq;
		ptu->esq=(*arv);
		(*arv)->bal=0;
		(*arv)=ptu;
		//printf("\nc");
	}
	else
	{
		ptv=ptu->esq;
		ptu->esq=ptv->dir;
		ptv->dir=ptu;
		(*arv)->dir=ptv->esq;
		ptv->esq=(*arv);
		//printf("\nc1");
		if(ptv->bal==1)
		{
			(*arv)->bal=-1;
			//printf("\nc2");
		}
		else
		{
			(*arv)->bal=0;
			//printf("\nc3");
		}
		if(ptv->bal==-1)
		{
			ptu->bal=1;
			//printf("\nc4");
		}
		else
		{
			ptu->bal=0;
			//printf("\nc5");
		}
		(*arv)=ptv;
	}
	(*arv)->bal=0;
	*h='f';
}
void avl(NO **pt,int32_t x,char *h)
{
	
	if((*pt)==NULL)
	{	
		inicio_no(&(*pt),x);
		//(*pt)=arv;
		*h='v';
		
	}
	else
	{
		if(x==(*pt)->chave)
		{
			printf("\nElemento ja inserido");
			*h = 'f';
		}
		else
		{
			if(x<(*pt)->chave)
			{
				avl(&(*pt)->esq,x,h);
				//printf("\no3");
			
				if(*h=='v')
				{	
					//printf("\noi3");
					if((*pt)->bal==1)
					{
						(*pt)->bal=0;
						*h='f';
					//	printf("\noi4");
					}
					else
					{
						if((*pt)->bal==0)
						{
							(*pt)->bal=-1;
							//printf("\noi5");
						}
						else
						{
							if((*pt)->bal==-1)
							{
								caso1(&(*pt),h);
								//printf("\noi6");
							}
						}
					}
				}
			}
			else
			{	
				//printf("\noi7");
				if(x>(*pt)->chave)
				{	
					//printf("\noi8");
					avl(&(*pt)->dir,x,h);
					if(*h=='v')
					{	
						//printf("\noi9");
						if((*pt)->bal==-1)
						{	
							//printf("\noi10");
							(*pt)->bal=0;
							*h='f';
						}
						else
						{
							if((*pt)->bal==0)
							{	
								//printf("\noi11");
								(*pt)->bal=1;
								
							}
							else
							{
								if((*pt)->bal==1)
								{	
									//printf("\no99");
									caso2(&(*pt),h);
								}
							}	
						}
					}
				}
			}
		}
	}
}
void visita_no(NO * arv,int x,int y)
{	
	int32_t w,z;
	w=arv->chave;
	z=arv->bal;

	char str[10],str1[10];
	sprintf(str,"%d",w);
	sprintf(str1,"%d",z);
	gfx_filled_ellipse(x,y,20,20);
	gfx_set_color(0,0,0);
	gfx_text(x,y-9,str);
	gfx_text(x,y+5,str1);
}
void desenha(NO *arv,int x, int y,int z)
{
	NO *pt;
	int32_t k;
	if(arv!=NULL)
	{	
		pt=arv;
		k=(z-x)/2;
		if(k<0)
		{
			k=k*(-1);
		}
		visita_no(pt,x,y);
		gfx_set_color(255,255,255);
		if(pt->esq!=NULL)
		{	
			gfx_line(x,y,x-k,y+20);
			desenha(pt->esq,x-k,y+20,x);
		}
		if(pt->dir!=NULL)
		{	
			gfx_line(x,y,x+k,y+20);
			desenha(pt->dir,x+k,y+20,x);
		}
	}
} 
void verifica(NO *pt,int x)
{	
	if(pt->chave==x)
	{
		printf("\n Elemento buscado =====>%d<=====\t",pt->chave);
	}
	
}
void busca_no(NO *pt,int x)
{
	NO *no=pt;
	
	if(pt->chave == x)
	{
		printf("\n Elemento buscado =====>%d<=====\t",pt->chave);
	}
	else
	{
		if(no->esq!=NULL)
		{	
			busca_no(no->esq,x);
		}
		if(no->dir!=NULL)
		{	
			busca_no(no->dir,x);
		}
	}
}
/*void  busca_no(NO *pt,int x,int *f)
{
	NO *arv=pt;
	if(arv==NULL)
	{
		*f=0;
		
	}
	else
	{
		if(arv->chave==x)
		{
			*f=1;
		}
		else
		{
			if(x<arv->chave)
			{
				if(arv->esq==NULL)
				{
					*f=2;
				}
				else
				{
					arv=arv->esq;
					busca_no(arv,x,&f);
				}
			}
			else
			{
				if(arv->dir==NULL)
				{
					*f=3;
				}
				else
				{
					arv=arv->dir;
					busca_no(arv,x,&f);
				}
			}
		}
	}
} */
NO * sucessor(NO **pt1,NO **pt2)
{
	NO *no1=(*pt1);
	NO *no2=(*pt1)->esq;

	while(no2!=NULL)
	{	
		if((no2->esq)->esq==NULL)
		{	
			
			(*pt2)=no2;
		}
		no1=no2;
		no2=no2->esq;
			
	}
  return no1;
}
void re_avl(NO **pt,int x)
{	
	NO *no,*pai,*no2;
	no=NULL;
	if((*pt)==NULL)
	{
		printf("\nValor inexistente");
	}
	else
	{	
		if((*pt)->chave==x)
		{	
			printf("\nan");	
			if((*pt)->esq==NULL || (*pt)->dir==NULL)
			{
				no2=(*pt);
				if((*pt)->esq!=NULL)
				{	
					printf("\nesq");
					(*pt)=(*pt)->esq;
				}
				else
				{	
					printf("\ndir");
					(*pt)=(*pt)->dir;
				}
				free(no2);
			}
			else
			{
				no=sucessor(&(*pt)->dir,&pai);
				printf("\n sucessor %d",no->chave);
				printf("\n pai %d",pai->chave);
			}	
		}
	}
}
int main()
{	
	NO *arv;
	arv=NULL;
	int opc=0;
	int32_t x,z,y;
	char h;
	gfx_init(tam1,tam2,"teste");
	while(opc!=4)
	{
		printf("\n<1> INSERIR");
		printf("\n<2> BUSCAR");
		printf("\n<3> REMOVER");
		printf("\n<4> SAIR\n");
		scanf("%d",&opc);
		if(opc ==1)
		{	
			printf("Digite o elemento que deseja inserir : \n");
			scanf("%d",&x);
			avl(&arv,x,&h);
			//printf("\nrafa");	
		}
		if(opc==2)
		{	
			printf("\nDigite o elemento que deseja buscar\n");
			scanf("%d",&z);
			busca_no(arv,z);
		}
		if(opc==3)
		{
			printf("\nDigite o elemento que deseja remover\n");
			scanf("%d",&y);
			re_avl(&arv,y);
		}
		desenha(arv,tam1/2,20,tam1);
		gfx_paint();

	}
	gfx_quit();
	return 0;
}