// diretiva de compilação gcc arquivo_fonte.c -o arquivo_objeto -lpthread

// thread -> compartilhamento de memória
// uso pesado de memória
// usar semáfotos ou mutexes para gerenciar
// funcionamento: um processo cliente, um processo pai que gera varias threads_servidores. Cada thread
// servidora atende um cliente
// como rodar: ./servidor 3(nº de clientes)
//rodar o cliente como: ./cliente 3
#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sched.h>
#include<pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/ioctl.h> /*Organiza a fila de conexões*/

/*Uso de macros
VOID FD_SET(int fd, fd_set *set): um flag para o descritor que deve ser observado
VOID FD_CLR(int fd, fd_set *set): reseta a flag relacionado ao descritor
INT FD_ISSET(int fd, fd_set *set): após o retorno da funlção select, FD_ISSET determina
qual descritor será marcado (flag) ou nao
VOID FD_ERO(fd_set *set): limpa o conjunto associado aos descritores*/

void* thread_proc(void *arg);

int main(int argc, char *argv[])
{
    struct sockaddr_in servidor;
    fd_set readset, testset;
    int meu_socket, novo_socket;
    char buffer[25];
    int ouvir_socket;
    int n_lidos;
    int resultado;
    int nfilhos;
    pthread_t  thread_id;
    int x, valor;

    if(argc > 1){
        nfilhos = atoi(argv[1]);
    }

    meu_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    /* SO_REUSEADDR -> durante a compilação é comum estartar e parar várias vezes o computador
    O linux tende a manter o endereço e a porta reservada para aplicação. Essa opção libera esses argumetnos.
    A função setsocketopt define as opções de argumento no nível de protocolo. O nível de argumento especifica
    o nível de protocolo onde as opções residem. Para especificar as opções no nivel socket usa-se o argumento
    SOL_SOCKET
    */
    valor = 1;
    resultado = setsockopt(meu_socket, SOL_SOCKET, SO_REUSEADDR, &valor, sizeof(valor));
    if(resultado < 0)
    {
        perror("Servidor");
        return 0;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(1980);
    servidor.sin_addr.s_addr = INADDR_ANY;

    resultado = bind(meu_socket, (struct sockaddr *)&servidor, sizeof(servidor));

    if(resultado < 0)
    {
        perror("Bind");
        return 0;
    }

    resultado = listen(meu_socket, 5);

    if(resultado < 0)
    {
        perror("Listen");
        return 0;
    }

    for(x=0; x < nfilhos; x++)
    {
        resultado = pthread_create(&thread_id, NULL, thread_proc, (void *) meu_socket);
        if(resultado != 0 )
        {
            printf("Não foi possível criar a thread!\n");
            return 0;
        }

        sched_yield(); // a função sched_yield() força a thread que está rodando a abandonar o processador
        // até que ela se torne novamente cabeça da lista de threads. Não leva argumentos
    }

    pthread_join(thread_id, NULL);

  return 0;
} // fim do main

void* thread_proc(void *arg)
{
    int ouve, sock;
    char buffer[25];
    int ler_dados;
     ouve = (int)arg;

     while(1)
     {
        sock = accept(ouve, NULL, NULL);
        printf("Cliente conectado a thread filha %i com pid %i.\n", pthread_self(), getpid() );
        ler_dados = recv(sock, buffer, 25, 0);
        buffer[ler_dados] = '\0';
        printf("%s\n", buffer);
        send(sock, buffer, ler_dados, 0);
     }
     close(sock);
     printf("Cliente desconectado da thread filha %i com pid %i.\n", pthread_self(), getpid() );

}
