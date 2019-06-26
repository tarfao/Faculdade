#include "gfx.h"
#include <stdio.h>
#include <string.h>

int main ()
{
	char p = '4';

	gfx_init(1300,700,"Tarfão");



	gfx_set_color(0,255,0);
	gfx_filled_ellipse(650,50,20,20);

	gfx_set_color(0,0,0);
	gfx_text(645,30,&p);
	gfx_text(645,50,"7");

	gfx_set_color(0,255,0);
	/*xl = x-10;
	  yl = y+15;
	  x1l = x - (((xfin - xini)/2)*(1/2));
	  y2l = xl + 30;
	gfx_line(xl, yl, x1l, y2l);*/
	/*primeira esquerda da raiz*/
	gfx_line(650,50,480+10,95-5);
	
	gfx_filled_ellipse(480,95,20,20);
	
	/*segunda esquerda*/
	gfx_line(480,95,345+30,180-5);
	
	gfx_filled_ellipse(345+25,180,20,20);

	/*segunda direita*/
	gfx_line(480,95,480+((650-480)/2)+20,180-5);
	gfx_filled_ellipse(480+((650-480)/2)+10,180,20,20);	

	/*esquerda da raiz*/
	gfx_line(650,50,810+10,95-5);
	gfx_filled_ellipse(810,95,20,20);

	gfx_line(810,95,810-((820-650)/2)+20,180-5);
	gfx_filled_ellipse(810-((820-650)/2)+10,180,20,20);

	gfx_line(810,95,950+10,180-5);
	gfx_filled_ellipse(950,180,20,20);
	/*gfx_filled_ellipse()*/
	gfx_paint();
	getchar();
	gfx_quit();
	return 0;
}