#include <stdio.h>
#include <stdlib.h>
#define TAM 50

char opcionais[][TAM]={ {"4.portas"}, {"cambio.automatico"}, {"vidros.eletricos"}, {"abs"}, {"air.bag"}, {"ar.condicionado"},
{"banco.couro"}, {"sensor.estacionamento"}};


struct CARRO {
    char placa[9]; //AAA-1234
    char modelo[TAM]; //gol, celta, palio, ...
    char fabricante[TAM]; //chevrolet, fiat, ...
    int ano_fabricacao; //1980 à 2016
    int ano_modelo; //1980 à 2017
    char combustivel[TAM]; //alcool, gasolina, flex, diesel
    char cor[TAM]; //branca, prata, preta
    int opcional[8]; //ver matriz opcionais
    float preco_compra;
};


struct ENDERECO {
     char rua[TAM];
     int numero;
     char bairro[TAM];
     char cidade[TAM];
     char estado[3];
     char cep[11]; //99.999-999
};


struct TELEFONE {
    char telefone[14]; //99 99999-9999
};


struct CLIENTE {
     char nome[TAM];
     char cpf[15]; //999.999.999-99
     struct ENDERECO endereco;
     struct TELEFONE residencial;
     struct TELEFONE celular[5];
     float renda_mensal;
};


struct DATA {
    int dia, mes, ano;
};


struct VENDA_CARRO {
     char placa_car[9];
     char cpf_cli[15];
     float preco_venda;
     struct DATA data_venda;
};



int main()
{
    printf("Hello world!\n");
    return 0;
}
