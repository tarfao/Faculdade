/*  Uma determinada empresa possui três tipos de empregados de acordo com o tipo de contratação:

    • Regime Integral: o empregado possui um salário mensal fixo.
    • Horista: o empregado é remunerado de acordo com a quantidade de horas trabalhadas.
    • Serviço: o empregado é remunerado por um determinado serviço que lhe foi designado.

    A partir dessa descrição, crie uma hierarquia de classes em C++ onde a classe Empregado,
    que possui os atributos e métodos comuns de um empregado (nome, RG e CPF) e os métodos
    para manipulação desses atributos é superclasse de EmpregadoIntegral, EmpregadoHorista e EmpregadoServico.
    Em cada uma das subclasses modele seu tipo específico de remuneração, criando os atributos e métodos necessários para isso.
    Além disso, implemente o método calcSalario() para cada uma das subclasses.
    Com base na descrição anterior, crie uma classe Empresa que possui objetos das classes que herdam a classe Empregado.
    Implemente métodos para inserir e remover empregados e para calcular o gasto mensal da empresa com relação aos salários.
    Além das classes especificadas, a função principal (main) deve instanciar um objeto da classe Empresa e fornecer um menu para
    inserir e remover empregados e visualizar as informações de um empregado já inserido. O gasto total da empresa com empregados
    também deve ser calculado.


    ALUNO: RONALDO TAFAREL
    RGM: 35043
    DATA: 03/04/2017
*/




#include <iostream>
#include <string.h> //strcpy()
#include <windows.h>
#include <stdio.h> //fgets()

using namespace std;

class Empregado{
    private:
        char nome[20];
        char rg[14];
        string cpf;
    public:
        void setnome(char c[]); //seta o nome do usuario para o atributo nome da classe
        void setrg(char c[]);//seta o rg do usuario para o atributo rg da classe
        void setcpf(string c);//seta o cpf do usuario para o atributo cpf da classe
        void getnome ();//mostra para o usuario o nome
        void getrg ();//mostra para o usuario o rg
        string getcpf ();//mostra para o usuario o cpf

};

void Empregado::setnome(char c[])
{
    strcpy(nome,c);
}

void Empregado::setrg(char c[])
{
    strcpy(rg,c);
}

void Empregado::setcpf(string c)
{
    cpf = c;
}

void Empregado::getnome()
{
    cout << "\nNome: "<< nome << endl;
}

void Empregado::getrg()
{
    cout << "RG: "<< rg << endl;
}

string Empregado::getcpf()
{
    /*cout << "CPF: "<< cpf << endl;*/
    return(cpf);
}

//Classe para EmpregadoIntegral
class EmpregadoIntegral:public Empregado{
    private:
        float sal;//salario mensal fixo
        int ativo;//1 ativo, 2 inativo
    public:
        EmpregadoIntegral();
        void setSal(float x);//seta o valor do salario no atributo sal
        float getSal();//retorna o valor de sal
        void setativo(int x);
        int getAtivo();
};

EmpregadoIntegral::EmpregadoIntegral()
{
    sal = 0.0;
    ativo = 2;
}

void EmpregadoIntegral::setSal(float x)
{
    if (x>0){
        sal = x;
    }
}

float EmpregadoIntegral::getSal()
{
    return (sal);
}

void EmpregadoIntegral::setativo(int x)
{
    ativo = x;
}

int EmpregadoIntegral::getAtivo()
{
    return(ativo);
}

//Classe para EmpregadoHorista
class EmpregadoHorista:public Empregado
{
    private:
        int h;//horas trabalhadas
        float valor;//valor por hora
        int ativo;//1 ativo, 2 inativo
    public:
        EmpregadoHorista();
        void setH(int x); //seta a hora de trabalho no atributo h da classe
        void setValor(float x); //seta o valor do ganho por hora trabalhada no atributo
                                //valor da classe
        int getH();//retorna o valor das horas trabalhadas
        float getValor(); //retorna o valor da hora trabalhada
        float calcSal();
        void setativo (int x);
        int getAtivo();

};

EmpregadoHorista::EmpregadoHorista()
{
    h=0;
    valor = 0.0;
    ativo = 2;
}

void EmpregadoHorista::setH(int x)
{
    if (x>0){
        h = x;
    }
}

void EmpregadoHorista::setValor(float x)
{
    if (x>0){
        valor = x;
    }
}

int EmpregadoHorista::getH()
{
    return (h);
}

float EmpregadoHorista::getValor()
{
    return (valor);
}

float EmpregadoHorista::calcSal()
{
    return (h*valor);
}

void EmpregadoHorista::setativo(int x)
{
    ativo = x;
}

int EmpregadoHorista::getAtivo()
{
    return (ativo);
}
//classe para EmpregadoServico
class EmpregadoServico:public Empregado
{
    private:
        char servico[20];//descricao do servico
        float sal;//salario do servico
        int ativo; //1 ativo, 2 inativo
    public:
        EmpregadoServico();
        void setServico(char c[]);//seta o servico do empregado no atributo servico da classe
        void setSal(float x);//seta o valor do salario no atributo servico da classe
        void getServico();//mostra o servico do empregado
        float getSal ();//retorna o salario do empregado
        void setativo(int x);
        int getAtivo();

};

EmpregadoServico::EmpregadoServico()
{
    sal = 0.0;
    ativo = 2;
}

void EmpregadoServico::setServico(char c[])
{
    strcpy(servico,c);
}

void EmpregadoServico::setSal(float x)
{
    if (x>0){
        sal = x;
    }
}

void EmpregadoServico::getServico()
{
    cout << "\nServico: " << servico << endl;
}

float EmpregadoServico::getSal()
{
    return (sal);
}

void EmpregadoServico::setativo(int x)
{
    ativo = x;
}

int EmpregadoServico::getAtivo()
{
    return(ativo);
}

class Empresa {
    private:
        int cei;
        int ceh;
        int ces;
    public:
        Empresa();
        EmpregadoIntegral ei[30];
        EmpregadoHorista eh[30];
        EmpregadoServico es[30];
        void cadastraemp(char l);
        int searchCli(string c, int s);
        void excluiCli(string c, int s);
        void aum_ei();//incrementa a contadora dos empregados integrais
        void aum_eh();//incrementa a contadora dos empregados horistas
        void aum_es();//incrementa a contadora dos empregados servico
        void dim_ei();//decrementa a contadora dos empregados integrais
        void dim_eh();//decrementa a contadora dos empregados horistas
        void dim_es();//decrementa a contadora dos empregados servico
        int getcei();//retorna a contadora dos empregados integrais
        int getceh();//retorna a contadora dos empregados horistas
        int getces();//retorna a contadora dos empregados servico
        void mostraEmp();

};

Empresa::Empresa()
{
    cei =0;
    ceh =0;
    ces =0;
}

void Empresa::cadastraemp(char l)
{
    char no[20], r[14], ser[20];
    string cp;
    float salario;

    cout << "\n CADASTRA EMPREGADO\n"<< endl;
    cout << "Nome: ";
    fflush(stdin);
    fgets(no,20,stdin);
    cout << "RG: ";
    fflush(stdin);
    fgets(r,14,stdin);
    cout << "CPF: ";
    fflush(stdin);
    getline(cin,cp);

    if (l=='i')
    {
        float sa;

        cout << "Salario: ";
        cin >> sa;
        ei[cei].setnome(no);
        ei[cei].setrg(r);
        ei[cei].setcpf(cp);
        ei[cei].setSal(sa);
        ei[cei].setativo(1);
        aum_ei();

    }
    else
    {
        if (l == 's')
        {
            cout << "Descricao do servico: ";
            fflush(stdin);
            fgets(ser,20,stdin);
            cout << "Salario: ";
            cin >> salario;
            es[ces].setnome(no);
            es[ces].setrg(r);
            es[ces].setcpf(cp);
            es[ces].setServico(ser);
            es[ces].setSal(salario);
            es[ces].setativo(1);
            aum_es();
        }
        else
        {
            int hr;
            float va;

            cout << "Horas trabalhadas por mes: ";
            cin >> hr;
            cout << "Valor de 1h trabalhada: ";
            cin >> va;
            eh[ceh].setnome(no);
            eh[ceh].setrg(r);
            eh[ceh].setcpf(cp);
            eh[ceh].setH(hr);
            eh[ceh].setValor(va);
            eh[ceh].setativo(1);
            aum_eh();
        }
    }
}

int Empresa::searchCli(string c, int s)
{
    int i,x;

    if (s == 1)
    {
        x = getcei();
        for (i=0;i<x;i++)
        {
            if (c == ei[i].getcpf())
            {
                return i;
            }
        }
        return -1;
    }

    if (s==2)
    {
        x = getces();
        for (i=0;i<x;i++)
        {
            if (c == es[i].getcpf())
            {
                return i;
            }
        }
        return -1;
    }
    if (s==3)
    {
        x = getceh();
        for (i=0;i<x;i++)
        {
            if (c == eh[i].getcpf())
            {
                return i;
            }
        }
        return -1;
    }
    return 0;
}

void Empresa::excluiCli(string c, int s)
{
    int i;

    i = searchCli(c,s);
    if (i<0)
    {
        cout << "-----ATENCAO!!! CLIENTE NAO FOI ENCONTRADO-----" << endl;
    }
    else
    {
        cout << "---CLIENTE EXCLUIDO COM SUCESSO---"<< endl;
        if (s==1)
        {
            ei[i].getnome();
            ei[i].getrg();
            cout << "CPF: " <<ei[i].getcpf()<< endl;
            ei[i].setativo(2);
        }
        if (s==2)
        {
            es[i].getnome();
            es[i].getrg();
            cout << "CPF: " <<es[i].getcpf()<< endl;
            es[i].setativo(2);
        }
        if (s==3)
        {
            eh[i].getnome();
            eh[i].getrg();
            cout << "CPF: " <<eh[i].getcpf()<< endl;
            eh[i].setativo(2);
        }
    }

}

void Empresa::aum_ei()
{
    cei = cei + 1;
}

void Empresa::aum_eh()
{
    ceh = ceh + 1;
}

void Empresa::aum_es()
{
    ces = ces + 1;
}

void Empresa::dim_ei()
{
    cei = cei - 1;
}

void Empresa::dim_eh()
{
    ceh = ceh - 1;
}

void Empresa::dim_es()
{
    ces = ces - 1;
}

int Empresa::getceh()
{
    return(ceh);
}

int Empresa::getcei()
{
    return(cei);
}

int Empresa::getces()
{
    return(ces);
}

void Empresa::mostraEmp()
{
    int x,i;
    float gasto=0;

    x = getces();

    cout << "\n\n---------------Empregado Servico-----------------\n";
    for (i=0;i<x;i++)
    {
        if(es[i].getAtivo() == 1){
            es[i].getnome();
            es[i].getrg();
            cout << "\nCPF: " <<es[i].getcpf()<<"\n";
            es[i].getServico();
            cout << "\nSalario: "<< es[i].getSal();
            gasto += es[i].getSal();
        }
    }
    cout << "\n\n---------------Empregado Horista-----------------\n";
    x=getceh();

    for (i=0;i<x;i++)
    {
        if(eh[i].getAtivo() == 1){
            eh[i].getnome();
            eh[i].getrg();
            cout << "\nCPF: " <<eh[i].getcpf() <<"\n";
            cout << "\nHoras trabalhadas por mes: " << eh[i].getH();
            cout << "\n\nValor de cada Hora tabalhada: "<< eh[i].getValor();
            cout << "\n\nSalario: "<< eh[i].calcSal() << "\n";
            gasto += eh[i].calcSal();
        }
    }

    cout << "\n\n---------------Empregado Integral-----------------\n";
    x=getcei();

    for (i=0;i<x;i++)
    {
        if(ei[i].getAtivo() == 1){
            ei[i].getnome();
            ei[i].getrg();
            cout << "CPF: " <<ei[i].getcpf() << "\n";
            cout << "\nSalario: "<< ei[i].getSal() << "\n";
            gasto += ei[i].getSal();
        }
    }
    cout << "----------------------------------------------"<<"\n";
    cout <<"GASTO TOTAL DA EMPRESA --> "<< gasto;
}

int main()
{

    Empresa c;
    char op;

    do{
        cout <<"\n-------------------EMPRESA TARFAO------------------\n" ;
        cout << "\n1 - INSERIR"<< endl;
        cout << "2 - VISUALIZAR"<< endl;
        cout << "3 - REMOVER"<<endl;
        cout << "4 - SAIR"<<endl;
        cin>>op;

        switch(op)
        {
        case '1':
            //verifica qual tipo de empregado quer inserir e faz uma funcao para cada inserção
            //insereEmpI, insereEmpH, insereEmps
            char k;
            do{
                cout << "Qual o tipo de empregado deseja incluir? Integra(i) Servico(s) Horista(h): ";
                fflush(stdin);
                cin >> k;
                k = tolower(k);
            }while(k != 's' && k != 'i' && k != 'h');
            c.cadastraemp(k);
            break;
        case '2':
            //visualiza tudo normal e divide, quem é de servico, integral e horista
            c.mostraEmp();
            break;
        case '3':
            int n;
            string cp;

            cout << "\n-------EXCLUI CLIENTE-------\n"<< endl;
            do{
                cout << "DIGITE UM NUMERO REFERENTE AO EMPREGADO QUE QUER EXLCUIR: INTEGRAL(1) SERVICO(2) HORISTA(3)"<<endl;
                cin >> n;
            }while(n!=1 && n!=2 && n!=3);
            cout << "DIGITE O NUMERO DO CPF DO EMPREGADO: " << endl;
            fflush(stdin);
            getline(cin,cp);
            c.excluiCli(cp,n);
            break;
        }
    }while(op!='4');
    return 0;
}
