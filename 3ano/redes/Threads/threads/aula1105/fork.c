//Este servidor utiliza a funcao fork() para gerenciar múltiplos clientes 
//ao se fazer a chamada do sistema fork(), cria-se uma duplicata exata do programa e,
//um novo processo filho é inciado para essa cópia
//nao compartilha memoria
//bibliotecas
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

//A BIBLIOTECA <SYS/WAIT> E A BIBLIOTECA <SIGNAL> SAO NECESSARIAS PARA EVITAR A CRIACAO DE ZOMBIES
//Zombies sao processos filhos que aparecem quando processos pais deixam de existir sem ser feita
//a chamada wait() ou a chamada waitpid() ao processo filho;

void sigchld(int signo)
{
//Essa funcao é um manipulador de sinais. Ela simplesmente faz a chamada waitpid para todo filho que for desconectado;
    while(waitpid(-1, NULL, WNOHANG) > 0 );
    exit(1);
    //A ideia de se chamar um laco é que nao se tem certeza que há uma correlação um-para-um entre os filhos desconectados
    // e as chamadas ao manipulador de sinais.
    //vale lembrar que o posix(biblioteca para implementar servidores) nao permite a criação de filas nas chamadas de sinal. 
    //Ou seja, pode acontecer de chamar o manipulador após vários filhos já terem sido desconectados
}

int main (int argc, char* argv[])
{
    struct sockaddr_in servidor;
    int meu_socket, novo_socket, resultado, leitor, valor, pid;
    char buffer[25];

    if( (meu_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) == -1) 
    {
        perror("Socket");
	exit(1);
    }//fim do if

    valor = 1;
    
    if((resultado = setsockopt(meu_socket, SOL_SOCKET, SO_REUSEADDR, &valor, sizeof(valor))) < 0)
    {
	perror("Setsockopt");
	exit(1);
    }//fim do if

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(1980);
    servidor.sin_addr.s_addr = INADDR_ANY;

    if((resultado = bind(meu_socket, (struct sockaddr*)&servidor, sizeof(servidor))) == -1)
    {
	perror("Bind");
	exit(1);
    }//fim do if

    listen(meu_socket, 5);

    signal(SIGCHLD, sigchld); //Ativando o manipulador de sinais antes de entrar no laco | 
				      // é uma system call, chamada do sistema, ou SO

    while(1)
    {
	novo_socket = accept(meu_socket, NULL, NULL);
	//Antes da chamada ser feita (retornada), chama-se o fork() para a criacao dos novos processos;
   	if((pid = fork()) == 0)
	{
	    //se retornar 0 é porque estamos no processo inicial, caso contrario retornaremos o PID do novo processo.
	    printf("Processo filho %i criado. \n", getpid());
	    close(meu_socket);
	    //uma vez que eu tenho o processo filho, fecha-se o processo pai. Vale lembrar que nessa etapa ocorre a geraçãod e cópias
	    // ou seja filhos, do processo pai.
	    leitor = recv(novo_socket, buffer, 25, 0);
	    buffer[leitor] = '\0';
	    printf("%s\n",buffer);
	    send(novo_socket, buffer, leitor,0);
	    close(novo_socket);
	    //Essa linha só é alcancada no processo pai, uma vez que o processo filho tem uma cópia do socket do cliente.
	    printf("Processo filho %i terminado\n",getpid());
	    exit(0);
	}//fim do if
	close(novo_socket);
    }//fim do while

}//fim da main
