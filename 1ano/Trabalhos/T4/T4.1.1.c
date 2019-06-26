#include <stdio.h>
#include <stdlib.h>

int main()


{
    int temp[1000]; //Recebe o conjunto de dados
    int soma=0; // faz o somatorio das temperaturas e a media
    int medi [1000]; // armazena as medias e procura a maior
    int m=-99; // representa o intervalo para fazer as medias
    int n=-98; // representa o numero total de medicoes de temperatura
    int medias [1000]; // irah conter as maiores medias e as menores
    int aux; // auxiliar para saber qual a maior nota, para poder ser jogada no vetor medi_ma
    int t; // Mostra em ordem a temperatura a ser digitada: ex: temp 1, temp 2...
    int i; // auxiliar de para passo (maioria)
    int j;// auxilia o para passo ajudando momentaneamente a soma das temperaturas para calculo de media
    int teste=0; // imprime na tela o numero do teste que foi efetuado
    int v=0; // auxilia o final do processo em que imprime cada teste dois testes, sempre em ordem, menor e maior
    int cont=0; // conta quantas vezes o usuario fez as medicoes de temperatura
    int posi=0; // auxilia as posicoes do conjunto de dados
    int a; // auxilia as medias para procurar qual a maior e menor
    int k=0,p=0; //representa a casa que o primeiro n foi digitado depois de x medicoes


    while ((m!=0) || (n!=0)) // irah sair do programa quando os m's forem iguais a 0
    {

        do //repita 1 // se as condicoes abaixo forem aceitas, mas tendo o n>m irah repetir
        {
            do // repita 2 // vai repetir ate ser digitado numeros no intervalo desejado
            {
                printf("\nQUANTIDADE DE TEMPERATURAS MEDIDAS: ");
                scanf("%d", &n);
                if ((n<0) || (n>800)) // se nao estiver no intervalo vai imprimir mensagem ao usuraio e fazer iteracao
                {
                    printf("QUANTIDADE DE MEDICOES NAO SUPORTADA. INTERVALO PERMITIDO: 0 A 800\n\n");
                    scanf("%d", &n);
                }

            }while ((n<0) || (n>800)); // repita 2
            do // repita 3 // repete ate ser digitado um m no intervalo desejado
            {
                printf("QUAL O INTERVALO QUE DESEJA OBTER AS MEDIAS? ");
                scanf("%d", &m);
                if ((m<0) || (m>800)) // se nao estiver no intervalo, irah imprimir mensagem ao usuario
                {
                    printf("INTERVALO PARA AS MEDIAS NAO ACEITO.\n");
                    printf("QUANTIDADE DE TEMPERATURAS MEDIDAS: ");
                    scanf("%d", &m);
                }
            }while ((m<0) || (m>800)); // repita 3
            if (m>n) // imprimindo mensagem ao usuario caso as condicoes de intervalo sejam aceitas
                    // mas se o m>n irah imprimir mensagem ao usuario
            {
                printf("\nNAO PODEMOS CALCULAR MEDIAS COM INTERVALOS MAIORES QUE A QUANTIA DE MEDIDA!\n\n");
            }
        }while(m>n); // repita 1
        if ((n!=0) && (m!=0)) // caso os intervalos e as medicoes sejam diferentes de 0 irah continuar o programa
        {
            a=0; // incializacao da variavel de
            temp[posi] = n; //colocando no conjunto de dados o numero de medicoes
            posi++; // avançando uma casa no conjunto de dados
            temp[posi] = m;//colocando no conjunto de dados o numero de medicoes
            posi++;// avançando uma casa no conjunto de dados
            cont = cont + 1;
            for(i=0;i<n;i++) // zerando o maximo de posicoes que poderao ser utilizadas nos vetores
            {
                //soma[i] = 0;
                //temp[i] = 0;
                medi[i] = 0;
            }
            t = 0; // zerando a variavel para utilizar na impressao de temperatura para guiar o usuario

            // fazendo iteracao para o usuario digitar a quantia de temperaturas que foi feito a leitura a cima
            for (i=posi;i<(posi+n);i++)

            {
                t = t+1;
                //printf("\n%d",posi);
                //system("pause");
                do{
                    printf("\nTEMPERATURA %d: ",t);
                    scanf("%d",&temp[i]);
                    if ((temp[i]<-200) || (temp[i]>200))
                    {
                        printf("TEMPERATURA NAO SUPORTADA: SOMENTE ENTRE -200 E 200 ");
                    }
                }while (temp[i]<-200 || temp[i]>200);

            }

            posi=posi+n; // atualiza a posicao para a proxima medicao

            /*for(i=0;i<posi;i++)
            {
                printf("\n%d",temp[i]);
            }
            system("pause");*/

            // fazendo as somas das temperaturas em intervalo desejado pelo usuario
            //(k+(n-m)+1) é o padrao da quantidade de medias que serao feitas
        }
    }
    for (p=0;p<cont;p++){
        a=0;
        n = temp[k];
        m = temp[k+1];
        for (i=k;i<(k+(n-m)+1);i++)
        {
            // complemento da iteracao para ocorrer a variacao de 1 em 1 posicao do vetor temperatura
            // ex: 4 medi, int de med 2, temp = (1,2,3,4) medias(1,2)(2,3)(3,4)
            for (j=1;j<+m+1;j++){
                soma = temp[i+j+1] + soma;
            }
            soma = soma/m;
            medi[a] = soma;
            a++;
            soma = 0;
        }
        // obtendo as medias
        k=k+2;
        aux = medi[1]; // chute inicial para a menor media
        // fazendo comparacoes com as posicoes para pegar a menor media
        for (i=k;i<(k+(n-m)+1);i++)
        {
            // caso uma outra media seja a menor, ocorre a troca
            if (medi[i]<aux)
            {
                aux = medi[i];
            }
        }
        medias [teste] = aux; // guardando a menor
        teste++; // avançando uma casa "vazia"
        aux = medi[01]; // chute inicial para a maior media
        // fazendo comparacoes com as medias em cada posicao para pegar a maior
        for (i=k;i<(k+(n-m)+1);i++)
        {
            // caso a media maior for em outra posicao ocorre a troca na variavel
            if (aux<medi[i])
            {
                aux = medi[i];
            }
        }
        medias [teste] = aux; // guardando a maior media
        teste++;

        k = k + n; // avança para a casa que irah conter o primeiro n novamente
    }
    // fazendo as impressões dos testes
    for (i=1;i<cont+1;i++)
    {
        printf("\nTESTE %d\n",i);
        for (j=0;j<2;j++)
        {
            printf("%d ", medias[v]);
            v++;
        }
        printf("\n");
    }

    return 0;
}
