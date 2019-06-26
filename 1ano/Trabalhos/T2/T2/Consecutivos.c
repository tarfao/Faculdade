// Num sorteio que distribui prêmios, um participante sorteia um inteiro N
// que representa a quantidade de bolas de um globo da sorte e cada bola possui
// um valor. O número de pontos do participante é o tamanho da maior sequência
// de valores consecutivos iguais. Por exemplo, suponhamos que um participante
// sorteia N = 11 e, nesta ordem, os valores 30, 30, 30, 30, 40, 40, 40, 40, 40, 30, 30.
// Então, o participante ganha 5 pontos, correspondentes aos 5 valores 40 consecutivos.
// Note que o participante sorteou 6 valores iguais a 30, mas nem todos são consecutivos.
// Determine o número de pontos de um participante onde a quantidade de bolas deve ser 1 ≤ N ≤ 104

// Integrantes: Ronaldo Tafarel Pereira de Souza
//              Igor Ribeiro Lins
//              Zenalvo Bastos Pinto Junior
// Data: 29/04/2016


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    int n, i, sorte, seq, maior, igual;
        // n, eh o numero de vezes que vai ser sorteado
        // i, eh auxiliar do for
        // sorte, vai ler os sorteios
        // seq, conta a sequencia de numeros iguais
        // maior, recebe a maior sequencia
        // igual, compara o valor sorteado anteriormente

        srand((unsigned) time(NULL)); // esse comando nao permite a funcao rand nao gere valores semrpe iguais
        printf ("Qual numero voce sorteou? "); // usuario ira informar a quantidade de bolas a serem retiradas
        scanf ("%d",&n); // lendo o valor
        if ((n<1) || (n>10000)) // condicao para que o numero que o usuario digite seja valido
        {
            while ((n<1) || (n>10000))
            {
                printf ("\nPara efeito de nossos calculos, o valor digitado eh invalido. Digite um valor entre 1 e 10000."); //mensagem caso seja um numero fora do intervalo
                scanf ("%d",&n); // lendo o valor novamente
            }
        }
        sorte = rand()%((100)+1); // gerando o primeiro valor fora do laço para nao ser comparado
        igual = sorte; // variavel recebe o sorteio da bola para verificar se eh igual ao proximo
        printf("\n1 - %d",sorte); // mostrando a primeira bola
        seq = 1; // inicializacao do valor da sequencia por 1.
        for (i=2;i<n+1;i++) // repetindo o sorteio
        {
            sorte = rand()% ((100)+1); // sorteio 2 ate n
            printf("\n%d - %d",i,sorte); // mostrando a bola sorteada
            if (sorte == igual) // (parte: x) condicao caso as bolas forem iguais
            {
                seq = seq + 1; // sequenciador comeca a contar
                maior = seq; // a maior sequencia eh responsabilidade da variavel maior
            }else
            {
                if (sorte!=igual) // caso as bolas sejam diferentes
                {
                    seq = 1; // sequenciador recebe 1 porque vai ser o primeiro numero de uma possivel sequencia
                }
                if (maior<=seq) // condicao caso uma outra sequencia seja inciada e ultrapasse o valor da antiga maior sequencia.
                {
                    maior = seq; // efetuando a mudança
                }
                igual = sorte; // trocando o valor da variavel igual pelo valor sorteado novamente para que seja feita a verificacao na parte x
            }
        }
        printf("\n...............................................................................");// melhorando a aparencia do programa
        printf("\nA maior sequencia tem %d numero(s), logo voceh recebe %d ponto(s)",maior,maior); // mostrando a maior sequencia
        printf("\n..............................................................................."); // melhorando a aparencia do programa
        printf("\n"); // melhorando a aparencia do programa
        system("pause");

        return 0;

}
