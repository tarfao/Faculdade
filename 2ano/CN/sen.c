#include <stdio.h>
#include <stdio_ext.h>//para usar o __fpurge();
#include <stdlib.h>
#include <string.h>
#include <math.h>


double factorial(double b){

	int a;//auxilia o for
	//b pega o numero que deseja obter o fatorial
	double fact=1;//vai obter o resultado

	for (a=b;a>1;a--)
	{
		fact = fact*a;
	}
	return (fact);
}

double calcula_seno(double x)
{
    int i;
    double sen,aux,aux1,tot=0;    

    sen = (x*3.14)/180;
    
    for (i=0;i<10;i++)
    {                    
        if(i%2 == 0){                    
               
            aux1 = (2*i) + 1;
            aux = (pow(sen,aux1));
            tot = tot + (aux/(factorial(aux1)));
        }
        else
        {
            aux1 = (2*i) + 1;
            aux = (pow(sen,aux1));
            tot = tot - (aux/(factorial(aux1)));
        }
    }
    return tot;

}

double calcula_e(double x)
{
    int i;
    double tot=0;
     
    for(i=0;i<15;i++)
    {
       tot = tot + pow(x,i)/factorial(i);
    }
    
    return tot;
}

int main()
{
    char op;
    double x;

    do{
        printf("\n[1] - CALCULAR SENO(X).\n");
        printf("\n[2] - CALCULAR e^x.\n");
        printf("\n[3] - SAIR.\n");
        __fpurge(stdin);
        scanf("%c",&op);
        
        switch(op)
        {
            case '1':
                printf("\nINFORME O ANGULO: ");
                scanf("%lf",&x);
                printf("\n\nsen(%.f) = %1.4f\n",x,calcula_seno(x));

            break;

            case '2':
                printf("\nX: ");
                scanf("%lf",&x);
                printf("\n\ne^%.f = %.4f\n",x,calcula_e(x));
            break;
       }
                
    }while(op!='3');

	return 0;

}

