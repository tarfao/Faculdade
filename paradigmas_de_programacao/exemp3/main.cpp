/*3. Fazer um programa que tenha um método que inicialize uma
variável com 0, outro que incremente esta variável e outro que
mostre o valor incrementado. O programa principal deverá
chamar 5 vezes o método que incrementa e o método que
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
