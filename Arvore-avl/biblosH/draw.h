#include "gfx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*free*/
#include <unistd.h>
#include "arv.h"

/*----------------------------------------------------------------------------
OBJETIVO: DESENHAR O CÍRCULO DA ÁRVORE
PARÂMETROS: c - CHAVE DO NÓ
			b - BALANÇO DO NÓ
			x, y, E r SÃO OS PARÂMETROS PARA DESENHAR A CIRCUNFERENCIA
-----------------------------------------------------------------------------*/
void Draw_Circ(int32_t c, int32_t b, int x, int y, int r)
{
	char p[8];
	char l[12];

	gfx_set_color(0, 255, 0);
	gfx_filled_ellipse(x, y, r, r);

	gfx_set_color(0, 0, 255);
	sprintf(p, "%d", c);
	gfx_text(x - 10, y - 15, p);
	sprintf(l, "%d", b);
	gfx_set_color(0, 0, 0);
	gfx_text(x - 5, y, l);
}

/*----------------------------------------------------------------------------
OBJETIVO: MOSTRAR O DESENHO COM AS INFORMAÇÕES DE UM NÓ DA ÁRVORE
PARÂMETROS: O NÓ QUE VAI DESENHAR,
			x, y, rx e ry são os parâmetros para desenhar a circunferencia
-----------------------------------------------------------------------------*/
void visita(A_NO *pt, int x, int y, int r)
{
	int32_t bal, chave;

	bal = pt->bal;
	chave = pt->chave;
	Draw_Circ(chave, bal, x, y, r);
}

/*---------------------------------------------------------------------- 
OBJETIVO: CONSTRUIR UMA ÁRVORE AVL
PARÂMETROS: O NÓ RAIZ,
			x - É O CENTRO NO EIXO OX
			y - É A ALTURA QUE SERÁ DESENHADO O NÓ -> INICIO = 50
			r de 20px 
			C.E -> Draw_Arv(raiz,650,50,20,1300);
-----------------------------------------------------------------------*/
void Draw_Arv(A_NO *pt, int x, int y, int r, int w)
{
	int y1, x1;

	if (pt != NULL)
	{
		x1 = (w - x) / 2;

		if (x1 < 0) /*como há a chamada recursiva para esquerda e para a direita
						na chamada recursiva para a direita, como o w vai ser menor do que o x
						a diferença entre os dois vai ser em módulo igual a que precisamos*/
			x1 = x1 * (-1);

		y1 = y + 50;

		visita(pt, x, y, r);
		if (pt->esq != NULL)
		{
			gfx_set_color(0, 255, 0);
			gfx_line(x, y, x - x1, y1);
			Draw_Arv(pt->esq, x - x1, y1, r, x);
		}
		if (pt->dir != NULL)
		{
			gfx_set_color(0, 255, 0);
			gfx_line(x, y, x + x1, y1);
			Draw_Arv(pt->dir, x + x1, y1, r, x);
		}
	}
}
