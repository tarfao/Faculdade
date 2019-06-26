/*FUNCAO: X*LOG(X)-1 = 0 */
#include <stdio.h>
#include <stdio_ext.h>
#include <math.h>

/*------------------------------------------------------------
OBJETIVO: VERIFICAR SE O INTERVALO DA RAÍZ É VÁLIDO PARA A FUNCAO:
          f(x) = xlog(x)-1
PARAMETROS: a & b - INTERVALO DA RAIZ
RETORNO: 0 - SE NÃO É INTERVALO DE RAIZ
        1 - SE É INTERVALO DE RAIZ
------------------------------------------------------------*/
int verify_interval (double a, double b)
{
  int ver=0;
  double ra = a*log10(a) - 1;/*resultado de a*/
  double rb = b*log10(b) - 1;/*resultado de b*/

  if(ra>0)
  {
    if (rb < 0)
      ver = 1;
  }
  else
  {
    if (rb > 0 )
      ver = 1;
  }

  return ver;
}


/*------------------------------------------------------------
OBJETIVO: OBTER O NÚMERO APROXIMADO PARA A RAIZ DA FUNCAO:
          f(x) = xlog(x)-1
PARAMETROS: a & b - INTERVALO DA RAIZ
            e - ERRO APROXIMADO
RETORNO: A RAIZ APROXIMADA
------------------------------------------------------------*/
double run (double a, double b, double e)
{
  double x;/*recebe o número que o xn corresponde na funcao*/
  double xn1=0; /*eh o resultado anterior para subtrair*/
  double xn=0;/*eh o novo resultado*/
  double mod;

    printf("a = %f  b = %f\n",a,b);
    do {

        /*printf("a = %f  b = %f\n",a,b);*/
        xn = xn1;
        xn1 = (a+b)/2;
        x = xn1 * log10(xn1) - 1;
        if(x>0)
        {
          if(a * log10(a) - 1 > 0 )
            a = xn1;
          else
            b = xn1;
        }
        else
        {
          if(a * log10(a) - 1 < 0)
            a = xn1;
          else
            b = xn1;
        }
        mod = xn1-xn;
        if (mod < 0){mod = mod*(-1);}
        printf("xn = %f \n",xn1);
        printf("a = %f\n",a);
        printf("b = %f\n",b);
        printf("f(xn) = %f\n|Xn1-Xn| = %f\n----------------------\n",x,mod);
    } while( mod > e);


  return xn1;
}

/*------------------------------------------------------------
OBJETIVO: OBTER A RAIZ N-ÁRIA DE QUALQUER NÚMERO
PARAMETROS: n - ÍNDICE DA raiz
            p - O NÚMERO QUE DESEJA OBTER A raiz
RETORNO: A RAIZ
------------------------------------------------------------*/
double execute (int n, double p)
{
  double x0;
  double xn=1;


  do
  {
    x0 = xn;
    xn = x0 - ( (pow(x0,n) - p) / ( pow(n*p,n-1) ) );
  }while(x0 != xn);

  return xn;

}

/*---------------------------------------------------
OBJETIVO: MENU PARA O METODO DA BISSECCAO
----------------------------------------------------*/
void bisseccao ()
{
  double a,b; /*INTERVALO DA RAIZ*/
  double erro; /*erro aproximado*/

  printf("digite o intervalo (a,b): \n");
  scanf("%lf",&a);
  scanf("%lf",&b);
  do {
    printf("Informe o erro aproximado: \n");
    scanf("%lf",&erro);
  } while(erro<0);

  if(verify_interval(a,b))
    printf("Raiz: %f\n",run(a,b,erro));
  else
    printf("Intervalo invalido\n");
}

/*---------------------------------------------------
OBJETIVO: MENU PARA O OBTENCAO DA RAIZ PELO METODO DE NEWTON-RAPHSON
----------------------------------------------------*/
void raiz()
{
  double p;/*NÚMERO*/
  int n;/*ÍNDICE DA RAIZ*/

  do{
    printf("QUAL O ÍNDICE DA RAIZ?\n");
    scanf("%d",&n);
  }while(n<0);

  printf("NUMERO: \n");
  if(n % 2 != 0 )
    scanf("%lf",&p);
  else
  {
    do {
      scanf("%lf",&p);
      if(p<0)
        printf("NAO EXISTE RAIZ REAL COM ÍNDICE PAR, TENTE OUTRO NUMERO\n");
    } while(p<0);
  }
  printf("Raiz: %f\n",execute(n,p));
}

int main ()
{
  char op;

  do {
    printf("\n1 - METODO BISSECCAO [f(x) = xlog(x)-1]\n");
    printf("2 - OBTENCAO DE RAIZ PELO METODO DE NEWTON-RAPHSON\n");
    printf("3 - SAIR\n");
    __fpurge(stdin);
    scanf("%c",&op);
    switch (op) {
      case '1':
        bisseccao();
      break;

      case '2':
        raiz();
      break;
    }
  } while(op!='3');

  return 0;
}
