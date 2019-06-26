#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int conj[50];
    int i, a=0, ev1, ev2, at, d, t;
    int dado, auxt=0,auxe;


    do{
        srand(time(NULL));// funcao para que nao se repita os numeros do dado
        // recebendo o valor de ev1
        scanf("%d",&conj[a]);
        while ((conj[a]<0) || (conj[a]>10))
        {
            printf("[EV1] ENTRADA DE DADOS INVALIDA, DIGITE UM NUMERO DE 1 A 10\n");
            scanf("%d",&conj[a]);
        }
        ev1 = conj[a];
        auxe = conj[a];
        if (ev1 != 0)
        {
            a++;
            //recebendo o valor do ev2
            scanf("%d",&conj[a]);
            while((conj[a]<1) || (conj[a]>10))
            {
                printf("[EV2] ENTRADA DE DADOS INVALIDA, DIGITE UM NUMERO DE 1 A 10\n");
                scanf("%d",&conj[a]);
            }
            ev2 = conj[a];
            // recebendo o valor do ataque
            a++;
            scanf("%d",&conj[a]);
            while((conj[a]<1) || (conj[a]>10))
            {
                printf("[ATAQUE] ENTRADA DE DADOS INVALIDA, DIGITE UM NUMERO DE 1 A 5\n");
                scanf("%d",&conj[a]);
            }
            at = conj[a];
            // recebendo o valor do dano
            a++;
            scanf("%d",&conj[a]);
            while((conj[a]<1) || (conj[a]>10))
            {
                printf("[DANO] ENTRADA DE DADOS INVALIDA, DIGITE UM NUMERO DE 1 A 10\n");
                scanf("%d",&conj[a]);
            }
            d = conj[a];
            // recebendo o tamanho do turno
            a++;
            scanf("%d",&conj[a]);
            while((conj[a]<1) || (conj[a]>10))
            {
                printf("[TURNO] ENTRADA DE DADOS INVALIDA, DIGITE UM NUMERO DE 1 A 100\n");
                scanf("%d",&conj[a]);
            }
            t = conj[a];
            // recebendo o separador de testes
            a++;
            scanf("%d",&conj[a]);
            while(conj[a]!=0)
            {
                printf("[TESTE] ENTRADA DE DADOS INVALIDA, 0 OBRIGATORIO PARA SEPARAR OS TESTES\n");
                scanf("%d",&conj[a]);
            }
            a++;
            printf("\nEV1\tEV2\tAT\tDANO\tT\tDADO\tQUEM GANHOU"); // mostrando os dados de entrada
            printf("\n%d\t%d\t%d\t%d\t%d",ev1,ev2,at,d,t);
            do{// irah repetir ate chegar a quantia do turno ou uma das energias forem 0
                auxt = auxt + 1; // vai contar os turnos
                dado = (rand() % 6) + 1; // dado sorteando de 1 ate 6
                if (dado<=at) //condiçao para o vampiro 1 ganhar a turno
                {
                    ev1 = ev1 + d;
                    ev2 = ev2 - d;
                    printf("\n%d\t%d\t%d\t%d\t%d\t%d\tVAMPIRO_1",ev1,ev2,at,d,auxt,dado); // mostra os resultados que so varia ev
                }
                else{ // caso contrario o vampiro 2 ganha se o dado for menor que o ataque
                    ev1 = ev1 - d;
                    ev2 = ev2 + d;
                    printf("\n%d\t%d\t%d\t%d\t%d\t%d\tVAMPIRO_2",ev1,ev2,at,d,auxt, dado); // mostra os resuldados
                }
                if (auxt!=t) // se o valor do turno nao for atingido verifica o resultado dos partida geral
                {
                    if (ev1 <= 0) // caso ja ocorra a morte de um vampiro que eh o vampiro 1,
                    {
                        printf("\nVAMPIRO_2 GANHOU\n"); //
                    }
                    if (ev2 <= 0) // caso o vampiro 2 morra
                    {
                        printf("\nVAMPIRO_1 GANHOU\n");
                    }
                }
                if (auxt==t) // se alcançar o numero de partidas do turno
                {
                    if (ev1==ev2) // verifica se a energia de 1 eh igual a do 2
                    {
                        printf("\nEMPATOU\n");
                    }
                    if (ev1>ev2) // caso a energia do vampiro 1 seja maior que a do 2
                    {
                        printf("\nVAMPIRO_1 GANHOU\n");
                    }
                    if (ev1<ev2) // e caso a energia do vampiro 2 seja maior que a do 1
                    {
                        printf("\nVAMPITO_2 GANHOU\n");
                    }

                }

            }while ((ev1>0) && (ev2>0) && (auxt!=t));
            auxt = 0; // zerando o numero de turnos para contar novamente em outra jogada.
        }

    }while (auxe!=0);


    return 0;
}
