/*
A fim de representar empregados em uma firma, crie uma classe chamada
Empregado que inclui as três informações a seguir como atributos:

    • um primeiro nome,
    • um sobrenome, e
    • um salário mensal.

Sua classe deve ter um construtor que inicializa os três atributos.
Forneça um método set e get para cada atributo.  Se o salário mensal não
for positivo, configure-o como 0.0.  Escreva um aplicativo de teste que
demonstra as capacidades da classe. Crie duas instâncias da classe e
exiba o salário anual de cada instância. Então dê a cada empregado um
aumento de 10% e exiba novamente o salário anual de cada empregado.

*/

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Empregados {
private:
    char nome[10];
    char sobnome[10];
    float sal_mens;
public:
    Empregados();
    void setnome(char c[]);
    void setsobnome(char c[]);
    void setsal_mens(float x);
    void getnome();
    void getsobnome();
    float getsal_mens();
    float getsal_anu();
    float getsal_anu10();
};


Empregados::Empregados()
{
    sal_mens=0.0;
}

void Empregados::setnome(char c[])
{
    strcpy(nome,c);
}

void Empregados::setsobnome(char c[])
{
    strcpy (sobnome,c);
}
void Empregados::setsal_mens(float x)
{
    if (x>0)
    {
        sal_mens = x;
    }
}

void Empregados::getnome()
{
    cout << "\nNome: "<< nome;
}

void Empregados::getsobnome()
{
    cout << "\nSobrenome: "<<sobnome;
}

float Empregados::getsal_mens()
{
    return (sal_mens);
}

float Empregados::getsal_anu()
{
    float x, aum;
    x= sal_mens*12;
    aum = x*1/10;
    return(x+aum);
}

float Empregados::getsal_anu10()
{
    return(sal_mens*12);
}

void setemp (Empregados *p)
{
    char n[10], s[10];
    float sal; int q;
    for (q=0;q<2;q++){
        cout << "\n------------------\nEmpregado "<< q+1<< ".\n\n";
        cout << "\nNome: ";
        fflush(stdin);
        gets(n);
        cout << "\nSobrenome: ";
        fflush(stdin);
        gets(s);
        cout << "\nSalario: ";
        cin >> sal;
        p[q].setnome(n);
        p[q].setsobnome(s);
        p[q].setsal_mens(sal);
    }

}

void mostraemp(Empregados *p)
{
    int i;

    cout << "\nEmpregados: \n--------------\n";
    for(i=0;i<2;i++){
        p[i].getnome();
        p[i].getsobnome();
        cout << "\nSal: " << p[i].getsal_anu10();
        cout <<"\n----------------------------------\n";
    }
    cout << "Salario com aumento de 10 por cento";
    for (i=0;i<2;i++)
    {
        p[i].getnome();
        p[i].getsobnome();
        cout << "\nSal: " << p[i].getsal_anu();
        cout <<"\n----------------------------------\n";
    }
}

int main()
{
    Empregados emp[2];
    int i;

    cout << "\n\tDados de Empregados\n\n";
    cout << "Digite os dados abaixo.\n";
    setemp(emp);
    mostraemp(emp);
    //cout << emp.getsal_mens();
    return 0;
}
