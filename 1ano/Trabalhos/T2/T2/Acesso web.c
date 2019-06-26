//  Em um site de busca encontra-se a resposta no terceiro link. Nesse mesmo site
// observa-se que t pessoas já haviam clicado no terceiro link. Já no segundo link o
// número de pessoas que o acessam é o dobro do número de pessoas que clicam no terceiro
// link. Mais curioso ainda é que o número de pessoas que clicam no segundo link é a metade
// do número de pessoas que clicam no primeiro link. Determine quantas pessoas clicaram no
// primeiro link para t pessoas, que representa o número de pessoas que clicaram no terceiro
// link, onde 1 ≤ t ≤ 1000.

// Integrantes: Ronaldo Tafarel Pereira de Souza
//              Igor Ribeiro Lins
//              Zenalvo Bastos Pinto Junior
// Data: 24/04/2016

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t, l1, l2;
        // t - recebe o numero de pessoas que clicaram no link 3
        // l1 eh a quantidade de pessoas que clicaram no link 2
        // l2 eh a quantidade de pessoas que clicaram no link 3


    printf("Numero de pessoas que acessaram os links da web. (3 links)\n");
    /* Recebendo o numero de cliques do link principal */
    printf("\nDetermine os cliques no terceiro link: ");
    scanf("%d",&t);
    /* condicao para o limite de cliques a ser recebido. */
    if ((t<1) || (t>100))
    {
        while ((t<1) || (t>100))
        {
            printf("O numero de cliques devem estar no intervalo de 1 e 1000.");
            printf("Por favor digite outro valor: ");
            scanf("%d",&t);
        }
    }
    /* executando o processamento de numeros de cliques do primeiro e do segundo link */
    l2 = 2*t;
    l1 = l2 *2;
    /* mostrando os valores dos cliques dos link's */
    printf("\nAcessos no primeiro link: %d",l1);
    printf("\nAcessos no segundo link: %d",l2);
    printf("\nAcessos no terceiro link: %d",t);
    /* melhorando a aparencia do programa */
    printf("\n..................................");
    /* melhorando a aparencia do programa */
    printf("\n");
    /* Pausando o sistema para que nao feche imediatamente! */
    system("pause");


    return 0;
}
