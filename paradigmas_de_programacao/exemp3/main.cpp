/*3. Fazer um programa que tenha um m�todo que inicialize uma
vari�vel com 0, outro que incremente esta vari�vel e outro que
mostre o valor incrementado. O programa principal dever�
chamar 5 vezes o m�todo que incrementa e o m�todo que
mostra o valor. */

#include <iostream>

using namespace std;

class x {
    private:
        int y;

    public:
        void inicializa ();
        void incrementa ();
        void mostra ();

};

void x::inicializa ()
{
    y = 0;
}

void x::incrementa ()
{
    y++;
}

void x::mostra()
{

    cout << "Valor : "<< y;
}

int main()
{
    x p;

    p.inicializa();
    p.incrementa();
    p.incrementa();
    p.incrementa();
    p.incrementa();
    p.incrementa();
    p.mostra();
    return 0;
}
