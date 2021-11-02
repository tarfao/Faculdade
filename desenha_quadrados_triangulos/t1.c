#include "gfx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define Rl 2


/*--------------------------------------------------------------------------
OBJETIVO: DESENHAR O TRIANGULO DE SIERPINSKI
PARAMETRO: OS PONTOS (X,Y) QUE REPRESENTAM O PONTO MÉDIO DA BASE DO TRIANGULO
			h QUE É A ALTURA DO TRIANGULO, r O NÍVEL DE RECURSIVIDADE, E c QUE AUXILIA
			NA CONTAGEM DA RECURSAO
------------------------------------------------------------------------------*/

void drawtri(int x, int y, int h, int r, int c)
{
	int l;

	l = ((2*h*Rl)/3)+1;

	gfx_line(x,y,x+l/2,y-h);
	gfx_line(x,y,x-l/2,y-h);
	gfx_line(x+l/2,y-h,x-l/2,y-h);
	//gfx_paint();
	if(c<r)
	{
		drawtri(x+l/2,y,h/2,r,c+1);
		drawtri(x-l/2,y,h/2,r,c+1);
		drawtri(x,y-h,h/2,r,c+1);
	}
}

/*------------------------------------------------------------------------------
OBJETIVO: DESENHAR QUADRADOS SOBREPOSTOS
PARAMETRO: O PONTO (X,Y) QUE REPRESENTA O CENTRO DO QUADRADO, A ALTRA h, O NÍVEL
			DE RECURSIVIDADE r, E O AUXILIAR DA RECURSIVIDADE c
----------------------------------------------------------------------------------*/
void drawsquare (int x, int y, int h, int r, int c)
{
	if (r>c)
	{
		drawsquare(x+h/2,y-h/2,h/2,r,c+1);
		drawsquare(x-h/2,y+h/2,h/2,r,c+1);
		drawsquare(x-h/2,y-h/2,h/2,r,c+1);
		drawsquare(x+h/2,y+h/2,h/2,r,c+1);
	}

	gfx_set_color(255,0,0);
	gfx_rectangle(x+h/2,y-h/2,x-h/2,y+h/2);
	gfx_set_color(255,255,255);
	gfx_filled_rectangle(x+h/2-1,y-h/2+1,x-h/2+1,y+h/2-1);
}

int main ()
{
	int h;
	int r;
	char op;
	do{
		printf("\n(1) - DESENHAR TRIANGULO DE SIERPINSKI\n");
		printf("(2) - DESENHAR QUADRADOS SOBREPOSTOS\n");
		printf("(3) - SAIR\n");
		fflush(stdin);
		scanf("%c",&op);

		switch(op)
		{
			case '1':

				do{
					printf("ALTURA DO TRIANGULO: ");
					scanf("%d",&h);
				}while(h<1);
				do{
					printf("Numero de recursividade: ");
					scanf("%d",&r);
					if(r>20)
					{
						printf("\n-----RECOMENDADO VALOR MÁX:20 MIN: 1\n");
					}
				}while(r<1 || r>20);
				gfx_init(800, 600, "-----------TRIANGULO DE SIERPINSKI-----------");
				drawtri(400,600,h,r,1);
				gfx_paint();
				sleep(4);
				gfx_quit();

			break;

			case '2':
				do{
					printf("ALTURA DO QUADRADO: ");
					scanf("%d",&h);
				}while(h<1);
				do{
					printf("Numero de recursividade: ");
					scanf("%d",&r);
				}while(r<1);
				gfx_init(800, 600, "-----------QUADRADOS SOBREPOSTOS-----------");
				drawsquare(400,300,h,r,1);
				gfx_paint();
				sleep(4);
				gfx_quit();
			break;
		}


	}while(op!='3');

	return 0;
}

