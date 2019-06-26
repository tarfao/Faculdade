#include <stdio.h>
#include <stdlib.h>

void extenso(int saque)
{
    int CM;//CENTENA DE MILHAR
    int DM;//DEZENA DE MILHAR
    int UNM;//UNIDADE DE MILHAR
    int CEN;//CENTENA
    int DEZ;//DEZENA
    int UN;//UNIDADE

    CM = saque/100000 ; // centena de milhar recebe valor do saque dividido por 100000
    DM = (saque - CM*100000)/10000; // dezena de milhar recebe valor do saque menos centena de milhar vezes 100000 dividido por 10000
    UNM = (saque - CM*100000 - DM*10000)/1000; // unidade de milhar recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 dividido por 1000
    CEN = (saque - CM*100000 - DM*10000 - UNM*1000)/100; // centena recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 dividido por 100
    DEZ = (saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100)/10; // dezena recebe daque menos centena de milha vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 dividido por 10
    UN = saque - CM*100000 - DM*10000 - UNM*1000 - CEN*100 - DEZ*10; // unidade recebe saque menos centena de milhar vezes 100000 menos dezena de milhar vezes 10000 menos unidade de milhar vezes 1000 menos centena vezes 100 menos dezena vezes 10
    printf("\n\t");
    if ((CM == 1) && (DM == 0) && (UNM == 0) && (CEN == 0) && (DEZ == 0) && (UN == 0)) // condicao para somente 100.000
    {
        printf("CEM MIL");
    }
                                                // condicao para imprimir cem mil caso a centena, dezena ou unidade possuir valores diferentes de 0
                                                if ((CM == 1) && (DM == 0) && (UNM == 0) && ((CEN != 0) || (DEZ != 0) || (UN != 0)))
                                                {
                                                    printf ("CEM MIL");
                                                }
                                                // imprime "cento e" caso a unidade de milhar ou dezena de milhar seja diferente de 0
                                                if ((CM == 1) && ((DM != 0) || (UNM != 0)))
                                                    printf(" CENTO E");
                                                // imprimir valores da dezena de milhar
                                                if (DM == 9)
                                                    printf(" NOVENTA");
                                                else{
                                                    if (DM == 8)
                                                        printf (" OITENTA");
                                                    else{
                                                        if (DM == 7)
                                                            printf (" SETENTA");
                                                        else{
                                                            if (DM == 6)
                                                                printf (" SESSENTA");
                                                            else{
                                                                if (DM == 5)
                                                                    printf (" CINQUENTA");
                                                                else{
                                                                    if (DM == 4)
                                                                        printf (" QUARENTA");
                                                                    else{
                                                                        if (DM == 3)
                                                                            printf (" TRINTA");
                                                                        else{
                                                                            if (DM == 2)
                                                                                printf (" VINTE");
                                                                            else{
                                                                                if ((DM == 1) && (UNM ==0))
                                                                                    printf (" DEZ");
                                                                                else{
                                                                                    if (DM ==1)
                                                                                        if (UNM == 9)
                                                                                            printf (" DEZENOVE");
                                                                                        else{
                                                                                            if (UNM == 8)
                                                                                                printf (" DEZOITO");
                                                                                            else{
                                                                                                if (UNM == 7)
                                                                                                    printf(" DEZESSETE");
                                                                                                else{
                                                                                                    if (UNM == 6)
                                                                                                        printf (" DEZESSEIS");
                                                                                                    else{
                                                                                                        if (UNM == 5)
                                                                                                            printf (" QUINZE");
                                                                                                        else{
                                                                                                            if (UNM == 4)
                                                                                                                printf (" QUATORZE");
                                                                                                            else{
                                                                                                                if (UNM == 3)
                                                                                                                    printf (" TREZE");
                                                                                                                else{
                                                                                                                    if (UNM == 2)
                                                                                                                        printf (" DOZE");
                                                                                                                    else{
                                                                                                                        if (UNM ==1)
                                                                                                                            printf (" ONZE");

                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                            // condicao para valores de com a dezena de milhar igual a 1, com valores particulares de treze, onze...
                                                                                            if ((CM == 0) && (DM==1))
                                                                                                printf(" MIL");
                                                                                        }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                // imprime "mil" antes do valor da centena, dezena e unidade
                                                if ((CM != 0) && (DM != 0) && (UNM == 0))
                                                    printf(" MIL");
                                                else{
                                                    if ((CM==0) && (DM != 0) && (UNM == 0))
                                                        printf(" MIL");
                                                    else{
                                                        if ((DM != 1) && (DM!=0) && (UNM != 0)) // imprime o "e" para separação de dezena e unidade, para ex: noventa E três
                                                            printf(" E");
                                                    }
                                                }
                                                // para aparecer vinte e três a dezena de milhar tem que ser diferente de 1,
                                                // se for 1 deveria sair valores como, treze, onze. casos particulares
                                                if (DM!=1)
                                                {
                                                    if (UNM == 9)
                                                        printf (" NOVE");
                                                    if (UNM == 8)
                                                        printf (" OITO");
                                                    if (UNM == 7)
                                                        printf(" SETE");
                                                    if (UNM == 6)
                                                        printf (" SEIS");
                                                    if (UNM == 5)
                                                        printf (" CINCO");
                                                    if (UNM == 4)
                                                        printf (" QUATRO");
                                                    if (UNM == 3)
                                                        printf (" TRES");
                                                    if (UNM == 2)
                                                        printf (" DOIS");
                                                    if (UNM ==1)
                                                        printf (" UM");
                                                }
                                                // imprime "mil" antes dos valores das centenas, dezenas e unidades
                                                if ((CM == 0 ) && (DM!=1) && (UNM != 0))
                                                    printf(" MIL");
                                                 if ((CM != 0) && (DM == 0) && (UNM != 0))
                                                {
                                                    printf(" MIL");
                                                }
                                                // aparece o "e" para valores particulares como 1009, 2020, 2300.
                                                if ((CM==0) && (DM==0) && (UNM!=0) && ((CEN!=0) || (DEZ!=0) || (UN!=0)))
                                                {
                                                    printf(" E");
                                                }
                                                // imprime "mil" antes dos valores das centenas, dezenas e unidades
                                                if ((CM != 0) && (DM != 0) && (UNM != 0))
                                                {
                                                    printf(" MIL");
                                                }
                                                // imprime "e" para valores com final de dezena e unidade iguais a 0
                                                if ((CM != 0) && (DM != 0) && (UNM != 0) && (CEN != 0) && (DEZ == 0) && (UN==0))
                                                {
                                                    printf(" E");
                                                }
                                                // imprime valores da centena
                                                if (CEN == 9)
                                                    printf ("  NOVECENTOS");
                                                if (CEN == 8)
                                                        printf (" OITOCENTOS");
                                                if (CEN == 7)
                                                        printf (" SETECENTOS");
                                                if (CEN == 6)
                                                        printf (" SEISCENTOS");
                                                if (CEN == 5)
                                                        printf (" QUINHENTOS");
                                                if (CEN == 4)
                                                        printf (" QUATROCENTOS");
                                                if (CEN == 3)
                                                        printf (" TREZENTOS");
                                                if (CEN == 2)
                                                        printf (" DUZENTOS");
                                                // caso particular para o valor 100
                                                if ((CEN == 1) && (DEZ==0) && (UN==0))
                                                        printf (" CEM");
                                                // caso para centena igual a 1 e os demais valores diferentes de 0, pelo ou menos a dezena ou unidade
                                                if ((CEN == 1) && ((DEZ!=0) || (UN!=0)))
                                                {
                                                    printf(" CENTO");
                                                }
                                                // condicao para imprimir o "e" em casos da centena de milhar e unidade de milhar forem 0,
                                                // aparece ex: nove mil trezentos "e" oito
                                                if ((UNM !=0) && (CEN != 0) && (DEZ!=0))
                                                    printf(" E");
                                                else // caso para centenas
                                                    if ((UNM == 0) && (CEN != 0) && (DEZ!=0))
                                                        printf(" E");
                                                // imprime valores da dezena
                                                if (DEZ == 9)
                                                    printf (" NOVENTA");
                                                if (DEZ == 8)
                                                    printf(" OITENTA");
                                                if (DEZ == 7)
                                                    printf (" SETENTA");
                                                if (DEZ == 6)
                                                    printf (" SESSENTA");
                                                if (DEZ == 5)
                                                    printf (" CINQUENTA");
                                                if (DEZ ==4)
                                                    printf (" QUARENTA");
                                                if (DEZ == 3)
                                                    printf (" TRINTA");
                                                if (DEZ == 2)
                                                    printf (" VINTE");
                                                // caso particular para o numero 10
                                                if ((DEZ == 1) && (UN==0))
                                                    printf (" DEZ");
                                                // casos para dezena igual a 1, aparecendo doze, treze...
                                                if ((DEZ == 1) && (UN!=0))
                                                {
                                                    if (UN == 9)
                                                        printf (" DEZENOVE");
                                                    if (UN == 8)
                                                        printf (" DEZOITO");
                                                    if (UN == 7)
                                                        printf (" DEZESSETE");
                                                    if (UN == 6)
                                                        printf (" DEZESSEIS");
                                                    if (UN == 5)
                                                        printf (" QUINZE");
                                                    if (UN == 4)
                                                        printf (" QUATORZE");
                                                    if (UN == 3)
                                                        printf (" TREZE");
                                                    if (UN == 2)
                                                        printf (" DOZE");
                                                    if (UN == 1)
                                                        printf (" ONZE");
                                                }
                                                // imprime "e" em valores do tipo cento "e" nove, cento "e" vinte
                                                if ((CEN!=0) && (DEZ!=1) && (UN != 0))
                                                    printf(" E");
                                                else{
                                                    if ((DEZ!=1) && (DEZ != 0) && (UN != 0))
                                                        printf(" E");

                                                }
                                                // imprime os valores da unidade
                                                if (DEZ != 1)
                                                {
                                                    if (UN == 9)
                                                        printf (" NOVE");
                                                    if (UN == 8)
                                                        printf (" OITO");
                                                    if (UN == 7)
                                                        printf (" SETE");
                                                    if (UN == 6)
                                                        printf (" SEIS");
                                                    if (UN == 5)
                                                        printf (" CINCO");
                                                    if (UN == 4)
                                                        printf (" QUATRO");
                                                    if (UN == 3)
                                                        printf (" TRES");
                                                    if (UN == 2)
                                                        printf (" DOIS");
                                                    if (UN == 1)
                                                        printf (" UM");
                                                }
                                                printf(" REAIS");

}


