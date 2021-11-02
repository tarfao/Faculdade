#include <stdio.h>
#define MAX 10 /*para o numero máximo de pontos*/

void Leitura_Pontos(float *ord, float *abs, int m);
void Obtem_Dados(float *ord, float *abs, int *m);
void Interpolando(float *ord, float *abs, int m);

int main()
{
    float ord[MAX];
    float abs[MAX];
    int m=0;

    int op;

    do{
        printf("\n[1] Dados para o polinomio");
        printf("\n[2] Numero a ser interpolado");
        printf("\n[3] Sair\n");
        scanf("%i",&op);
        
       switch(op)
       {
             case 1:
 		  Obtem_Dados(ord,abs,&m);
	     break;
	     case 2:
		  if(m>0)
		  	Interpolando(ord,abs,m);
		  else
			printf("\nEntre com os dados para o polinomio!!\n");
            break;
       }
    }while(op != 3);
    return 0;
}

/*----------------------------------------------------------------------------------
OBJETIVO: INTERPOLAR UM NUMERO QUALQUER A PARTIR DO POLINOMIO DADO
-----------------------------------------------------------------------------------*/
void Interpolando(float *ord, float *abs, int m)
{
     float x0; /*numero a ser interpolado*/
     float equ; /*obtem as multiplicações do produtório*/
     float mul; /*faz uma das multiplicações para nao poluir o código*/
     float acum; /*obtem o acumulo do somatório da formula de lagrange*/
     int i,j;

     printf("\nEntre com o numero que deseja interpolar: ");
     scanf("%f",&x0);
     if(x0<abs[0] || x0>abs[m-1])
     {
         printf("Esse numero não é recomendado para interpolacao. extrapola!!!");
     }
     else
     {
         acum = 0;
	 for(i=0;i<m;i++)
   	 {
	     equ = ord[i];
  	     for(j=0;j<m;j++)
 	     {
   		if( j != i)
		{
		     mul = (x0 - abs[j])/(abs[i] - abs[j]);
		     equ = equ*mul;
		}
	     }
	     acum = acum + equ;
	 }
     }
     printf("\nO P(%f) = %f\n",x0,acum);
}
/*----------------------------------------------------------------------------------
OBJETIVO: OBTER OS DADOS PARA INTERPOLAÇÃO DE UM VALOR
-----------------------------------------------------------------------------------*/
void Obtem_Dados(float *ord, float *abs, int *m)
{
    
   printf("\nEntre com o numero de pontos: ");
   do{
      scanf("%i",m);
      if(m <= 0){
          printf("\nEntre com o numero de pontos m>0: ");
      }
   }while(m <= 0);
   Leitura_Pontos(ord,abs,*m);	
}

void Leitura_Pontos (float *ord, float *abs, int m)
{
    int i,j;

    for(i=0;i<m;i++)
    {
        printf("X[%d]= ",i+1);
        scanf("%f",&abs[i]);
	printf("Y[%d]= ",i+1);
        scanf("%f",&ord[i]);
    }
}
