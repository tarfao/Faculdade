/*
5. Utilizando a Programação Orientada a Objetos implemente uma
pilha utilizando um vetor de inteiros. O seu programa deve
conter os métodos de inserir, remover e mostrar da pilha.
Observações:

O vetor simulando a pilha deverá ser alocado estaticamente com 1000 posições.
A classe deverá possuir, além do vetor, um atributo como apontador para o topo da
pilha.
As operações de inserção, remoção e impressão deverão ser chamadas a partir da
main()

*/

#include <iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace std;

class pilha {
    private:
        int x[100];
        int y;

    public:
        void inicializa ();
        void insere ();
        void remov ();
        void mostra();
};

void pilha::inicializa()
{
    y = 0;
}

void pilha::insere()
{
    if (y<1000)
    {
        cout << "Numero: ";
        cin >> x[y];
        y = y+ 1;
    }
    else
    {
        cout <<"\nCHEIOOO!!";
    }
}

void pilha::remov ()
{
    if (y > 0){
        y = y -1;
    }
}

void pilha::mostra()
{
    int i;

    for (i=0;i<y;i++)
    {
        cout << x[i] << "\n";
    }
}
int main()
{
    int op;
    pilha p;

    p.inicializa();
    do{
        cout << "1 - Insere\n";
        cout << "2 - Remove\n";
        cout << "3 - Mostra\n";
        cout << "4 - Sair\n";
        cin >> op;

        switch(op){
            case 1:
                p.insere();
            break;
            case 2:
                p.remov();
            break;
            case 3:
                p.mostra();
            break;
        }

    }while(op!=4);
    return 0;
}
