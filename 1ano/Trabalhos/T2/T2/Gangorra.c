//  Joãozinho acaba de mudar de escola e a primeira coisa que percebeu
// na nova escola é que a gangorra do parquinho não é simétrica, uma das
// extremidades é mais longa que a outra. Após brincar algumas vezes com
// um amigo de mesmo peso, ele percebeu que quando está em uma extremidade,
// a gangorra se desequilibra para o lado dele (ou seja, ele fica na parte
// de baixo, e o amigo na parte de cima), mas quando eles trocam de lado,
// a gangorra se desequilibra para o lado do amigo. Sem entender a situação,
// Joãozinho pediu ajuda a outro amigo de outra série, que explicou que o
// comprimento do lado interfere no equilíbrio da gangorra, pois a gangorra
// estará equilibrada quando P1 ∗ C1 = P2 ∗ C2 onde P1 e P2 são os pesos da
// criança no lado esquerdo e direito, respectivamente, e C1 e C2 são os
// comprimentos da gangorra do lado esquerdo e direito, respectivamente.
// Com a equação, Joãozinho já consegue dizer se a gangorra está equilibrada
// ou não mas, além disso, ele quer saber para qual lado a gangorra descerá
// caso esteja desequilibrada. Se a gangorra estiver equilibrada, imprima ‘0’.
// Se ela estiver desequilibrada de modo que a criança esquerda esteja na parte
// de baixo, imprima ‘-1’, senão, imprima ‘1’. As restrições de entrada são:
//    10 ≤ P1 ≤ 100 e 10 ≤ C1 ≤ 100 e 10 ≤ P2 ≤ 100 e 10 ≤ C2 ≤ 100.

// Integrantes: Ronaldo Tafarel Pereira de Souza
//              Iigor Ribeiro Lins
//              Zenalvo Bastos Pinto Junior
// Data: 28/04/2016

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float p1, c1, p2, c2, r1, r2;
        // p1 eh o peso da pessoa do lado esquerdo
        // p2 eh o peso da pessoa do lado direito
        // c1 eh o comprimento da gangorra do lado esquerdo
        // c2 eh o comprimento da gangorra do lado direito
        // r1 eh o balanceamento da gangorra no lado esquerdo
        // r2 eh o balanceamento da gangorra no lado direito

    printf("Consulte aqui informacoeos sobre sua gangorra.\n");
    printf("\nQual o peso da crianca do lado esquerdo? ");
    scanf("%f",&p1);
    /* Condição de valores para o peso1 */
    if ((p1<10) || (p1>100))
    {
        /* forçando o usuario digitar o valor que desejo */
        while ((p1<10) || (p1>100))
        {
            printf("Para efeito de nossos calculos digite um valor no intervalo de 10 e 100. ");
            scanf("%f",&p1);
        }
    }
    printf("Qual o peso da crianca do lado direito? ");
    scanf("%f",&p2);
    /* Condição de valores para o peso2 */
    if ((p2<10) || (p2>100));
    {
        /* forçando o usuario digitar o valor que desejo */
        while ((p2<10) || (p2>100))
        {
            printf("Para efeito de nossos calculos digite um valor no intervalo de 10 e 100. ");
            scanf("%f",&p2);
        }
    }
    printf ("Qual o o comprimento do lado esquerdo da gangorra? ");
    scanf("%f",&c1);
    /* Condição de valores para o comprimento da gangorra lado esquerdo. */
    if ((c1<10) && (c1>100));
    {
        /* forçando o usuario digitar o valor que desejo */
        while ((c1<10) || (c1>100))
        {
            printf("Para efeito de nossos calculos digite um valor no intervalo de 10 e 100. ");
            scanf("%f",&c1);
        }
    }
    printf("E do lado esquerdo? ");
    scanf("%f",&c2);
    /* Condição de valores para o comprimento da gangorra lado direito. */
    if ((c2<10) || (c2>100));
    {
        /* forçando o usuario digitar o valor que desejo */
        while ((c1<10) && (c1>100))
        {
            printf("Para efeito de nossos calculos digite um valor no intervalo de 10 e 100. ");
            scanf("%f",&c1);
        }
    }
    /* Resultado da gangorra esquerda */
    r1 = (c1*p1);
    /* resultaldo da gangorra direita */
    r2 = (c2*p2);
    /* caso r1=r2 gangorra equilibrada */
    if (r1==r2)
    {
        printf("Resultado: 0");
    }
    /* quando o peso do lado esquerdo fica desequilibrado para baixo */
    if (r1>r2)
    {
        printf("Resultado: -1");
    }
    /* quando o peso do lado esquerdo fica desequilibrado para baixo */
    if (r1<r2)
    {
        printf("Resultado: 1");
    }

    printf("\n........................."); /* melhorando a aparencia do programa */
    printf("\n"); /* melhorando a aparencia do programa */
    system("pause");

    return 0;
}


