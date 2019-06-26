#include <stdio.h>

//extern int add (int a, int b);//função add feita em nasm

int main ()
{
    return 0;
}

//compilar e linkar:
//gcc -o mainC.o -c mainC.c, gera o mainC.o
//nasm -g -f elf64 -o addAsm.o addAsm.asm, gera o addAsm.o
//gcc -o cMainAsm mainC.o addAsm.o, gera o cMainAsm

