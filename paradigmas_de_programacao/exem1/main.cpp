/*1. Declarar os m�todos do exemplo, colocando os c�digos dos
m�todos fora da classe.

2. Criar um novo m�todo para a classe Pessoa (exemplo anterior)
que calcule a idade. A idade calculada dever� ser mostrada no
m�todo ImprimirPessoa.
*/

#include <iostream>
#include <stdio.h>

using namespace std;

class Pessoa
{
     private:
        char Nome[30];
        char Cpf[15];
        int AnoNasc;

     public:
        void CadastrarPessoa();
        void ImprimirPessoa();
        int idade();

};

void Pessoa::CadastrarPessoa()
{
    cout <<"\nNome: ";
    gets(Nome);
    cout << "CPF: ";
    gets(Cpf);
    cout <<"Ano Nascimento: ";
    cin >> AnoNasc;
}

void Pessoa::ImprimirPessoa()
{
    cout << "Cpf: " <<Cpf << "\n";
    cout << "Nome: " << Nome << "\n";
    cout << "Ano nasc:" << AnoNasc << "\n";
    cout << "idade: " << idade();
}

int Pessoa::idade()
{
    return(2017-AnoNasc);
}

int main()
{
    //cout << "Hello world!" << endl;
    Pessoa p;

    p.CadastrarPessoa();
    p.ImprimirPessoa();
    //cout <<p.AnoNasc<< "<--";
    return 0;
}
