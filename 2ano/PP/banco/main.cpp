/*
6. Uma agência bancária possui cadastrada em seu sistema vários clientes.
As informações dos clientes cadastradas no sistema são: nome, cpf, rg, telefone e endereço.
Nessa agência é possível que o cliente tenha apenas uma conta corrente, na qual possui um número identificador,
um saldo, e funcionalidades como: mostrar saldo, fazer saque de um valor x e efetuar deposito de um valor y.
Elabore este pequeno sistema bancário utilizando Programação Orientada a Objetos
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class cliente {
    private:
        char nome[20];
        char cpf[15];
        char rg[14];
        char tel[12];
        char adress[30];
        int id;
        float saldo;

    public:
        void cadastra(int t);
        void inicializaId();
        //int getID ();
        void inicializaSaq();
        void saque();
        void deposito();
        void mostrasaldo();
        int verificacli(int tot, cliente p[], char cpf[]);

};

void cliente::inicializaSaq()
{
    saldo = 0;
}

void cliente::inicializaId()
{
    srand(time(NULL));
    id = rand()%2000+1;

}

void cliente::saque(){
    float saq;

    cout << "\nVALOR DO SAQUE: ";
    cin >> saq;
    if (saq>0 && saq<=saldo)
    {
        cout << "\nSAQUE EFETUADO!!";
        saldo -= saq;
    }
    else
    {
        cout << "\n!!!!!VALOR NAO SUPORTADO!!!!!";
    }

}

void cliente::deposito()
{
    float dep;

    cout << "\nVALOR DO DEPOSITO: ";
    cin >> dep;
    saldo += dep;
    cout << "\nDEPOSITO EFETUADO COM SUCESSO!!";
}

void cliente::mostrasaldo()
{
    cout << "Saldo -- > %f.2" << saldo;
}

int cliente::verificacli (int tot, cliente p[], char cpf[])
{
    int i;

    for (i=0;i<tot;i++)
    {
        if(!strcmp(p[i].cpf,cpf))
        {
            return (i);
        }
    }
    return -1;
}

void cliente::cadastra(int t)
{
    cout << "\nNOME: ";
    gets(nome);
    cout << "CPF: ";
    gets(cpf);
    cout << "RG: ";
    gets(rg);
    cout << "Tel: ";
    gets(tel);
    cout << "Endereco: ";
    gets(adress);
    id = 100 + t;
    inicializaSaq();

}

int main()
{
    int q=0;
    cliente usu[20];
    int op;

    do{
        cout << "1 - Cadastra";
        cout << "2 - Entra";
        cout << "3 - Sai";
        cin >> op;

        switch(op){
        case 1:
            usu[q].cadastra(q);
            cout << "Cadastro Efetuado com sucesso\n";
        break;

        }
    }while(op!=3);
    return 0;
}

