#include <stdio.h>
#include <stdlib.h>

struct no
{
    int info;
    struct no *prox;
}no;


void busca_enc (struct no *pt, int n, struct no** ant, struct no **pont)
{
    struct no *ptr;    
    
    *ant = pt;
    *pont = NULL;
    ptr = pt->prox;

    while (ptr != NULL)
    {
        if(ptr->info < n)
        {
            *ant = ptr;
            ptr = ptr->prox;
        }
        else
        {
            if (ptr->info == n)
            {
                *pont = ptr;
            }
            ptr = NULL;
        }
    }

}

void ini_lista(struct no **pt)
{
    *pt = malloc(sizeof(no));
    (*pt)->prox = NULL;
}

void insere(struct no *pt, int x)
{
    struct no* ant;
    struct no* pont;

    busca_enc(pt,x,&ant,&pont);

    if(pont == NULL)
    {
        struct no *pt= malloc(sizeof(no));
        pt->info = x;
        pt->prox = ant->prox;
        ant->prox = pt;
    }
    else
        printf("\nO ELEMENTO JÁ EXISTE!!");
}

void imprime (struct no* pt)
{
    printf("\nLISTA: ");
    pt = pt->prox;

    while (pt!=NULL)
    {
        printf(" %i ",pt->info);
        pt = pt->prox;
    }
}

int main ()
{
    struct no *ptlista;

    ini_lista(&ptlista);

    free(ptlista);

    return 0;
}   
