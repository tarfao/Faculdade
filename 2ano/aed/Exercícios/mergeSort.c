#include <stdio.h>
#include <stdlib.h>

void intercalar(int L[], int Tmp[], int ini1,int ini2,int fim2)
{
    int i;
    int fim1 = ini2;
    int nro = 0;
    int ind = ini1;

    while (ini1<fim1 && ini2<fim2)
    {
        if(L[ini1]<L[ini2])
        {
            Tmp[ind] = L[ini1];
            ini1++;
        }
        else
        {
            Tmp[ind] = L[ini2];
            ini2++;
        }
        ind++;
        nro++;
    }
    while(ini1<fim1)
    {
        Tmp[ind]=L[ini1];
        ini1++;
        ind++;
        nro++;
    }

    while(ini2<fim2)
    {
        Tmp[ind]=L[ini2];
        ini2++;
        ind++;
        nro++;
    }

    for(i=0;i<nro;i++)
    {
        L[i]=Tmp[i];
    }
}

void mergeSort (int L[],int esq,int dir)
{
    int centro;
    int Tmp[3];

    if(esq<dir)
    {
        centro = (esq+dir)/2;
        mergeSort(L,esq,centro);
        mergeSort(L,centro,dir);
        intercalar(L,Tmp,esq,centro,dir);
    }
}

void mostra(int L[], int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("%d ",L[i]);
    }
}

int main ()
{
    int vetor[]={3,2,1,5};
    mergeSort(vetor,0,4);
    mostra(vetor,4);

    return 0;
}
