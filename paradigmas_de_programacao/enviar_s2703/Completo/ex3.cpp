/*
Crie uma classe para representar datas.

    1. Represente uma data usando três atributos: o dia, o mês, e o ano.
    2. Sua classe deve ter um construtor que inicializa os três atributos e verifica a validade dos valores fornecidos.
    3. Forneça um construtor sem parâmetros que inicializa a data com a data atual fornecida pelo sistema operacional.
    4. Forneça um método set um get para cada atributo.
    5. Forneça o método toString para retornar uma representação da data como string.  Considere que a data deve ser
    formatada mostrando o dia, o mês e o ano separados por barra (/).
    6. Forneça uma operação para avançar uma data para o dia seguinte.
    7. Escreva um aplicativo de teste que demonstra as capacidades da classe.

Garanta que uma instância desta classe sempre esteja em um estado consistente.

*/

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class data {
private:
    int dia;
    int mes;
    int ano;

public:
    //void construtor(int x, int y, int z);
    data();
    data(int x, int y, int z);
    void setdia(int x);
    void setmes(int x);
    void setano(int x);
    int getdia();
    int getmes();
    int getano();
    void toString ();
    void avancaData();
};

//construtor que verifica se os numeros fornecidos podem ser uma data.
data::data(int x, int y, int z){
    char d[9], s[3];
    int a;

    if (z>0){
        setano(z);
        if(!z/4)
        {
            if(y == 2)
            {
                if (!(x>0 && x<30))
                {
                    _strdate(d);
                    s[0] = d[0];
                    s[1] = d[1];
                    s[2] = '\0';
                    a = atoi(s);
                    setmes(a);
                    s[0] = d[3];
                    s[1] = d[4];
                    s[2] = '\0';
                    a=atoi(s);
                    setdia(a);
                    s[0] = d[6];
                    s[1] = d[7];
                    s[2] = '\0';
                    a=atoi(s);
                    setano(2000+a);
                }
                else
                {
                    setmes(y);
                    setdia(x);
                }

            }
            else
            {
                if(y>0 && y<13)
                {
                    setmes(y);
                    if (y == 1 || y == 3 || y==5 || y==7 || y==8 || y==10 || y ==12)
                    {
                        if (!(x>0 && x<32))
                        {
                            _strdate(d);
                            s[0] = d[0];
                            s[1] = d[1];
                            s[2] = '\0';
                            a = atoi(s);
                            setmes(a);
                            s[0] = d[3];
                            s[1] = d[4];
                            s[2] = '\0';
                            a=atoi(s);
                            setdia(a);
                            s[0] = d[6];
                            s[1] = d[7];
                            s[2] = '\0';
                            a=atoi(s);
                            setano(2000+a);
                        }
                        else
                        {
                            setdia(x);
                        }
                    }
                    else
                    {
                        if(!(x>0 && x<31))
                        {
                            _strdate(d);
                            s[0] = d[0];
                            s[1] = d[1];
                            s[2] = '\0';
                            a = atoi(s);
                            setmes(a);
                            s[0] = d[3];
                            s[1] = d[4];
                            s[2] = '\0';
                            a=atoi(s);
                            setdia(a);
                            s[0] = d[6];
                            s[1] = d[7];
                            s[2] = '\0';
                            a=atoi(s);
                            setano(2000+a);
                        }
                        else
                        {
                            setmes(y);
                        }
                    }
                }

            }
        }
        else
        {
            if(y == 2)
            {
                if (!(x>0 && x<29))
                {
                    _strdate(d);
                    s[0] = d[0];
                    s[1] = d[1];
                    s[2] = '\0';
                    a = atoi(s);
                    setmes(a);
                    s[0] = d[3];
                    s[1] = d[4];
                    s[2] = '\0';
                    a=atoi(s);
                    setdia(a);
                    s[0] = d[6];
                    s[1] = d[7];
                    s[2] = '\0';
                    a=atoi(s);
                    setano(2000+a);
                }
                else
                {
                    setmes(y);
                    setdia(x);
                }

            }
            else
            {
                if(y>0 && y<13)
                {
                    setmes(y);
                    if (y == 1 || y == 3 || y==5 || y==7 || y==8 || y==10 || y ==12)
                    {
                        if (!(x>0 && x<32))
                        {
                            _strdate(d);
                            s[0] = d[0];
                            s[1] = d[1];
                            s[2] = '\0';
                            a = atoi(s);
                            setmes(a);
                            s[0] = d[3];
                            s[1] = d[4];
                            s[2] = '\0';
                            a=atoi(s);
                            setdia(a);
                            s[0] = d[6];
                            s[1] = d[7];
                            s[2] = '\0';
                            a=atoi(s);
                            setano(2000+a);
                        }
                        else
                        {
                            setdia(x);
                        }
                    }
                    else
                    {
                        if(!(x>0 && x<31))
                        {
                            _strdate(d);
                            s[0] = d[0];
                            s[1] = d[1];
                            s[2] = '\0';
                            a = atoi(s);
                            setmes(a);
                            s[0] = d[3];
                            s[1] = d[4];
                            s[2] = '\0';
                            a=atoi(s);
                            setdia(a);
                            s[0] = d[6];
                            s[1] = d[7];
                            s[2] = '\0';
                            a=atoi(s);
                            setano(2000+a);
                        }
                        else
                        {
                            setmes(y);
                        }
                    }
                }

            }
        }

    }
}

//Construtor p inicializar com data do sistema
data::data()
{
    char d[9];//recebe a data do sistema
    char s[3];//vai receber o dia, mes e ano para serem convertidos em inteiros
    int a;//auxilia as conversoes para inicializar os atributos da classe

    _strdate(d);
    s[0] = d[0];
    s[1] = d[1];
    s[2] = '\0';
    a = atoi(s);
    setmes(a);
    s[0] = d[3];
    s[1] = d[4];
    s[2] = '\0';
    a=atoi(s);
    setdia(a);
    s[0] = d[6];
    s[1] = d[7];
    s[2] = '\0';
    a=atoi(s);
    setano(2000+a);
}


void data::setdia(int x)
{
    dia = x;
}

void data::setmes(int x)
{
    mes = x;
}

void data::setano(int x)
{
    ano = x;
}

int data::getano()
{
    return(ano);
}

int data::getmes()
{
    return(mes);
}

int data::getdia()
{
    return (dia);
}

void data::toString()
{
    char c[9];
    c[2]='/'; c[5] = '/';

    c[0] = dia/10 + 48;
    c[1] = (dia - ((dia/10)*10)) + 48;

    c[3] = mes/10 + 48;
    c[4] = (mes - ((mes/10)*10)) + 48;

    c[6] = ((ano - ((ano/1000 * 1000) + (((ano%1000)/100)*100)))/10) + 48;
    c[7] = ((ano - ((ano/1000 * 1000) + (((ano%1000)/100)*100)))%10) + 48;
    c[8] = '\0';

    cout << "\nData: " << c << "\n\n";
}

void data::avancaData()
{
    dia += 1;
}

using namespace std;

int main()
{
    data hoje;
    int d, m, a;
    hoje.toString();

    //cout << hoje.getdia() << "/" << hoje.getmes() << "/" << hoje.getano() << endl;
    cout << "\nDia: ";
    cin >> d;
    cout << "\nMes: ";
    cin >> m;
    cout << "\nAno: ";
    cin >> a;
    cout << "\n";
    data hoje2(d,m,a);
    //cout << hoje.getdia() << "/" << hoje.getmes() << "/" << hoje.getano() << endl;
    hoje2.toString();
    hoje2.avancaData();
    cout << "Avanca um dia -- > ";
    cout << hoje2.getdia() << "/" << hoje2.getmes() << "/" << hoje2.getano() << endl;


    return 0;
}
