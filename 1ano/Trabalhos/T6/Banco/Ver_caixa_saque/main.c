#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE HÁ NOTAS SUFICIENTES PARA EFETUAR O SAQUE
//PARAMETRO: DE ENTRADA QUE É O SAQUE
//RETORNO: saque_ced, QUE VAI SER 0 SE HOUBER CEDULAS E DIFERENTE DE 0
//SE NAO HOUVER CEDULAS
//---------------------------------------------------------------------
int Ver_caixa_saque_0(int sa_ced)
{

    if ((saq_ced/200>0) && (vernot200>0)) // caso houver notas suficientes para serem retiradas corretamente
    {
        a200 = saque/200;
        if (vernot200>=a200)
        {
            saq_ced = saq_ced - (a200*200);
        }
        else{
            a200 = vernot200; // como esgtaram as notas de 200, as notas que haviam sairam todas.
            saq_ced = (saq_ced - (a200*200));
        }
    }
    if ((saq_ced/100>0) && (vernot>0)) // se houver notas de 100 a mais ou igual
    {
        a100 = saq_ced/100;
        if (vernot>=a100){
            saq_ced = saq_ced - (a100*100);
        }
        else{
            a100 = vernot; // Como as notas do caixa sao menores do que as notas que poderiam ser
                            // retiradas se houvesse mais, as notas retiradas fica com o mesmo valor das notas do caixa
            saq_ced = (saq_ced - (a100*100));
        }
    }
    if ((saq_ced/50>0) && (vernot50>0)) // caso houver notas suficientes para serem retiradas
    {
        a50 = saq_ced/50;
        if (vernot50>=a50){
            saq_ced = saq_ced - (a50*50);
        }
        else{
            a50 = vernot50; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (a50*50));
        }
    }
         if ((saq_ced/40>0) && (vernot40>0)) // caso houver notas suficientes para serem retiradas
    {
        a40 = saq_ced/40;
        if (vernot40>=a40){
            saq_ced = saq_ced - (a40*40);
        }
        else{
            a40 = vernot40; // notas de 50 retiradas serah igual as notas que possui no caixa
            saq_ced = (saq_ced - (a40*40));
        }
    }
    if((saq_ced/20>0) && (vernot20>0)) // caso as notas de 20 forem suficientes
    {
        a20 = saq_ced/20;
        if (vernot20>=a20){
            saq_ced = (saq_ced - (a20*20));
        }
        else{
            a20 = vernot20;
            saq_ced = (saq_ced - (a20*20));
        }
    }
    if ((saq_ced/10>0) && (vernot10>0))
    {
        a10 = saq_ced/10;
        if (vernot10>=a10){
            saq_ced = saq_ced - (a10*10);
        }
        else{
            a10 = vernot10;
            saq_ced = (saq_ced - (a10*10));
        }
    }
    if ((saq_ced/5>0) && (vernot5>0))
    {
        a5 = saq_ced/5;
        if (vernot5>=a5){
            saq_ced = saq_ced - (a5*5);
        }
        else{
            a5 = vernot5;
            saq_ced = (saq_ced - (a5*5));
        }
    }
    if ((saq_ced/2>0) && (vernot2>0))
    {
        a2 = saq_ced/2;
        if (vernot2>=a2){
            saq_ced = saq_ced - (a2*2);
        }
        else{
            a2 = vernot2;
            saq_ced = saq_ced - (a2*2);
        }
    }
    if (vernot1>0)
    {
        a1 = saq_ced;
        saq_ced = saq_ced - a1;

    }
    return (saq_ced);
}
