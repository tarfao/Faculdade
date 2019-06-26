#include <stdio.h>
#include <stdlib.h>

void Obtem_Dados(float *vecx, float *vecy, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("\nX%d = ",i+1);
        scanf("%f",&vecx[i]);
        printf("\nY%d = ",i+1);
        scanf("%f",&vecy[i]);
    }
}

float SomatorioXY (float *vecx, float *vecy, int n)
{
    float total = 0;
    int i;

    for(i=0; i < n; i++)
    {
        total+=(vecx[i]*vecy[i]);
    }

    return (total*n);
}

float Somatorio (float *vec, int n)
{
    float total = 0;
    int i;

    for(i=0; i < n; i++)
    {
        total+=vec[i];
    }

    return (total);
}

float SomatorioX2(float *vecx, int n)
{
    float total = 0;
    int i;

    for(i=0; i < n; i++)
    {
        total+=(vecx[i]*vecx[i]);
    }

    return (total*n);
}

float Somatorio2X(float *vecx, int n)
{
    float total = 0;
    int i;

    for(i=0; i < n; i++)
    {
        total+=vecx[i];
    }

    return (total*total);
}

float CalculaB (float *vecx, float *vecy, int n)
{
    float t1, t2, t3, t4; /*termos de cada calculo para obtencao de b*/
    float a;
    float b;

    t1 = SomatorioXY(vecx, vecy, n);
    a = Somatorio(vecx,n);
    b = Somatorio(vecy,n);
    t2 = a*b;
    t3 = SomatorioX2(vecx, n);
    t4 = Somatorio2X(vecx,n);

    return ((t1-t2)/(t3-t4));
}

float media(float *vec, int n)
{
    int i;
    float total = 0;

    for(i=0;i<n;i++)
    {
        total+=vec[i];
    }

    return(total/n);
}

float CalculaA(float *vecx, float *vecy, float b, int n)
{
    float my,mx;

    mx = media(vecx,n);
    my = media(vecy,n);

    return(my - (b*mx));
}

int main()
{
    int n;
    float vecx[20];
    float vecy[20];
    float a;
    float b;

    do{
        printf("\nEntre com a quantidade de pontos: ");
        scanf("%d",&n);
        if(n>0)
        {
            Obtem_Dados(vecx, vecy,n);
            b = CalculaB(vecx, vecy, n);
            a = CalculaA(vecx, vecy, b,n);
            printf("\n Y = %f + %f*x",a,b);
        }
    }while(n != 0);
    return 0;
}
