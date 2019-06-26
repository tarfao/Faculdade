// A invenção do carro tornou muito mais rápido e mais barato realizar viagens
// de longa distância. Realizar uma viagem rodoviária tem dois tipos de custos:
// cada quilômetro percorrido na rodovia tem um custo associado (não só devido
// ao consumo de combustível mas também devido ao desgaste das peças do carro,
// pneus, etc.), mas também é necessário passar por vários pedágios localizados
// ao longo da rodovia. Os pedágios são igualmente espaçados ao logo da rodovia;
// o começo da estrada não possui um pedágio, mas o seu final pode estar logo após
// um pedágio (por exemplo, se a distância entre dois pedágios consecutivos for de
// 37 km e a estrada tiver 111 km, o motorista deve pagar um pedágio aos 37 km, aos
// 74 km e aos 111 km, logo antes de terminar a sua viagem). Dadas as características
// da rodovia e os custos com gasolina e com pedágios, informe o custo total da viagem.
// Considere que o comprimento (C) da estrada é 1 ≤ C ≤ 104 e a distância (D) entre pedágios é 1 ≤ C ≤ 104.

// Integrantes: Ronaldo Tafarel Pereira de Souza
//              Higor Ribeiro Lins
//              Zenalvo Bastos Pinto Junior
// Data: 28/04/2016


#include <stdio.h>
#include <stdlib.h>

int main()
{
    float c, d, comb, ped, custo;
    int qped;
        /* c, faz a leituta do total de km de viagem. */
        /* d, faz a leitura da distancia entre um pedagio e outro */
        /* comb, faz a leitura do valor gasto no combustivel */
        /* ped, recebe a o custo do pedagio */
        /* custo, faz o calculo do total gasto na viagem */
        /* qped, calcula quantos pedagios tem */


    printf("Total de gastos com uma viagem.\n");
    printf("Quanto foi gasto de comobustivel? ");
    scanf("%f",&comb); /* obtendo o gasto com combustivel */
    if (comb<0) /* condicao caso valores negativos sejam colocados */
    {
        while (comb<0) /* caso o numero for negativo repetira até que informe valores positivos. */
        {
            printf("Impossivel gastar essa quantia de combustivel, digite um dado valido. ");
            scanf("%f",&comb); /* refaz a leitura do gasto com combustivel */
        }

    }
    printf("Quanto custa um pedagio? "); /* o custo com pedagio */
    scanf("%f",&ped); /* lendo o custo do pedagio */
    if (ped<0) /* caso o valor do pedagio seja um valor negativo */
    {
        while (ped<0) /* se ocorrer irá repetir até que seja digitado um valor válido para nossos calculos */
        {
            printf("Eh impossivel um pedagio custar %f. Digite um valor valido: ",ped);
            scanf("%f",&ped); /* refaz a leitura de custo do pedagio */
        }
    }
    printf("Quantos km a viagem? "); /* total de km de viagem */
    scanf("%f",&c); /* fazendo a leitura do total de km */
    /*Condicao para a distancia esta no intervalo desejado */
    if ((c<1) || (c>10000)); /* os km devem estar no intervalo de 1 a 10000 */
    {
        while ((c<1) || (c>10000)) /* caso seja fora do intervalo, sera feita a repeticao */
        {
            printf("Informe um valor no intervalo de 1 e 10000: ");
            scanf("%f",&c); /* repetindo a leitura da quantidade de km */
        }
    }
    printf("Qual a distancia entre um pedagio e outro? ");
    scanf("%f",&d); /* lendo a distancia entre um pedagio e outro */
    /*Condicao para a distancia dos pedagioso serem validas */
    if ((d<1) || (d>10000))
    {
        while ((d<1) || (d>10000)) /* caso a condicao nao seja satisfeita, fará repeticao */
        {
            printf("Informe um valor no intervalo de 1 e 10000: ");
            scanf("%f",&d); /* repetindo a leitura da distancia entre um pedagio e outro */
        }
    }
    /* verificacao da quantidade de pedagios */
    qped = c/d;
    custo = comb + (ped*qped);
    /* melhoramento na aparencia do programa */
    printf("\n.............................................");
    /* Imprimindo o custo da viagem */
    printf("\nA sua viagem sairah no custo de: %.2f",custo);
    /* melhoramento na aparencia do programa */
    printf("\n.............................................");
    /* melhoramento na aparencia do programa */
    printf("\n");
    /* pausando o sistema para que nao feche imediatamente */
    system("pause");


    return 0;
}
