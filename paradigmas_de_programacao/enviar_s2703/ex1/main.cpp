/*
Crie uma classe chamada Invoice que possa ser utilizado por uma loja de
suprimentos de informática para representar uma fatura de um item vendido
na loja. Uma fatura deve incluir as seguintes informações como atributos:

    • o número do item faturado,
    • a descrição do item,
    • a quantidade comprada do item e
    • o preço unitário do item.

Sua classe deve ter um construtor que inicialize os quatro atributos.
Se a quantidade não for positiva, ela deve ser configurada como 0.
Se o preço por item não for positivo ele deve ser configurado como 0.0.
Forneça um método set e um método get para cada variável de instância.
Além disso, forneça um método chamado getInvoiceAmount que calcula o valor
da fatura (isso é, multiplica a quantidade pelo preço por item) e depois
retorna o valor como um double.  Escreva um aplicativo de teste que
demonstra as capacidades da classe Invoice

*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Invoice {
private:
    int num;//numero da fatura
    char desc[20];//descricao
    int q;//quantidade de itens
    float preco;//preco do item

public:
    Invoice();//inicializa os atributos
    void setnum(int x);//seta valor em num
    void setdesc(char c[]);//seta a descricao em desc
    void setq(int x);//seta a quantidade de itens em q
    void setpreco(float x);// seta o preco em preco
    void getnum();//mostra o num da fatura
    void getdesc();//mostra descricao
    void getq();//mostra a quantidade de itens
    void getpreco();//mostra o preco
    double getInvoiceAmount();//calcula o preco do item x a quantidade
                            //e retorna um double
};

Invoice::Invoice()
{
    num = 0;
    q = 0;
    preco = 0.0;
}

void Invoice::setnum(int x)
{
    num = x;
}

void Invoice::setdesc(char c[])
{
    strcpy(desc,c);
}

void Invoice::setq(int x)
{
    if (x>0)
    {
        q = x;
    }
}

void Invoice::setpreco(float x)
{
    if (x>0)
    {
        preco = x;
    }
}

void Invoice::getnum()
{
    cout << "\nNumero da fatura: " << num;
}

void Invoice::getdesc()
{
    cout << "\nDescricao: "<< desc;
}

void Invoice::getpreco()
{
    cout << "\nPreco: "<< preco;
}

void Invoice::getq()
{
    cout << "\nQuantidade: "<< q;
}

double Invoice::getInvoiceAmount()
{
    return(q*preco);
}

void setfatura(Invoice c[], int *t)
{
    int q, p;//numero, quantidade, preco
    int n;
    char s[20];//descricao

    cout << "\nNumero da fatura: ";
    cin>>n;
    cout << "Quantidade: ";
    cin >> q;
    cout << "Preco: ";
    cin >> p;
    cout << "Descricao: ";
    fflush(stdin);
    gets(s);
    //setando os valores
    c[*t].setnum(n);
    c[*t].setq(q);
    c[*t].setpreco(p);
    c[*t].setdesc(s);
    *t = *t + 1;
}

void mostrafatura(Invoice c[], int q)
{
    int i;

    for (i=0; i<q; i++)
    {
        c[i].getdesc();
        c[i].getnum();
        c[i].getpreco();
        c[i].getq();
        cout << "\nValor total: "<< c[i].getInvoiceAmount();
        cout << "\n--------------------------------------------";
    }
}

int main()
{
    Invoice fat[20];
    int op, q=0;

    do{
        cout << "\n--------------------------------------";
        cout <<"\n1 - fazer fatura";
        cout <<"\n2 - mostrar faturas";
        cout <<"\n3 - sair\n";
        cin >> op;

        switch(op)
        {
        case 1:
            setfatura(fat,&q);
        break;

        case 2:
            mostrafatura(fat,q);
        break;

        }
    }while(op!=3);

    return 0;
}
