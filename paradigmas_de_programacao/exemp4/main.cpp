/*4. Fazer um programa que implemente a classe Automóvel
mostrada no slide 14. */

#include <iostream>
#include <stdio.h>

using namespace std;

class automovel {
    private:
        char placa[9];
        char fabricante[20];
        char modelo[20];
        char proprietario[20];

    public:
        void RegistraDados();
        void ImprimeDados ();

};

void automovel::RegistraDados(){
    cout << "Nome: ";
    gets(proprietario);
    cout << "Modelo: ";
    gets(modelo);
    cout << "Fabricante: ";
    gets(fabricante);
    cout << "Placa: ";
    gets(placa);
}

void automovel::ImprimeDados()
{
    cout << "\n\n" <<placa << "\n";
    cout << modelo << "\n";
    cout << fabricante << "\n";
    cout << proprietario;
}

int main()
{
    automovel x;

    x.RegistraDados();
    x.ImprimeDados();

    return 0;
}
