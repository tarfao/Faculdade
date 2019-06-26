#include <stdio.h>
#include <stdlib.h>

void liberar_notas()
{

    //notas de 200
    if (a200>0) {
        printf("\n\t%d NOTA(S) - R$ 200,00",a200); // mostrando as notas que sairam
        vernot200 = vernot200 - a200; // diminuindo a quantidade de notas do caixa
        saldocaixa = saldocaixa - (a200*200);
        totsak = totsak + (a200*200);
    }
    //notas de 100
    if (a100>0) {
        printf("\n\t%d NOTA(S) - R$ 100,00",a100); // mostrando as notas que sairam de 100
        vernot100 = vernot100 - a100; // subtraindo o quantidade de notas do caixa
        saldocaixa = saldocaixa - (a100*100);
        totsak = totsak + (a100*100);
    }
    //notas de 40
    if (a40>0){
        printf("\n\t%d NOTA(S) - R$ 40,00",a40); // mostrando as notas que foram retiradas
        vernot40 = vernot40 - a40; // diminuindo as notas de 40 do caixa
        saldocaixa = saldocaixa - (a40*40);
        totsak = totsak + (a40*40);
    }
    //notas de 50
    if (a50>0){
        printf("\n\t%d NOTA(S) - R$ 50,00",a50); // mostrando as notas que foram retiradas
        vernot50 = vernot50 - a50; // diminuindo as notas de 50 do caixa
        saldocaixa = saldocaixa - (a50*50);
        totsak = totsak + (a50*50);
    //notas de 20
    if (a20>0) {
        printf("\n\t%d NOTA(S) - R$ 20,00",a20); // mostra as notas retiradas
        vernot20 = vernot20 - a20; // subtrai-se as notas do caixa com as notas retiradas, para serem retiradas do caixa
        saldocaixa = saldocaixa - (a20*20);
        totsak = totsak + (a20*20);
    }
    //notas de 10
    if (a10>0) {
        printf("\n\t%d NOTA(S) - R$ 10,00",a10);
        vernot10 = vernot10 - a10;
        saldocaixa = saldocaixa - (a10*10);
        totsak = totsak + (a10*10);
    }
    //notas de 5
    if (a5>0) {
        printf("\n\t%d NOTA(S) - R$ 5,00",a5);
        vernot5 = vernot5 - a5;
        saldocaixa = saldocaixa - (a5*5);
        totsak = totsak + (a5*5);
    }
    //notas de 2
    if (a2>0) {
        printf("\n\t%d NOTA(S) - R$ 2,00",a2);
        vernot2 = vernot2 - a2;
        saldocaixa = saldocaixa - (a2*2);
        totsak = totsak + (a2*2);
    }
    //notas de 1
    if (a1>0) {
        printf("\n\t%d NOTA(S) - R$ 1,00",a1);
        vernot1 = vernot1 - a1;
        saldocaixa = saldocaixa - a1;
        totsak = totsak + a1;
    }

}
