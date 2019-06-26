/*Cliente genérico para acesso aos servidores multiplexing, fork e threads
--> Executar como: ./cliente 5 (5 é o numero de clientes)
=====================================================================================*/

//Demais biblio

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Cliente(int num_clientes);

int main(int argc, char* argv[])
{
	int pid, x, numero_clientes;

	if(argc > 1)
	{
		numero_clientes = atoi(argv[1]);
	}

	for(x = 0; x < numero_clientes; x++)
	{
		/*Uso da funcao fork() = system call para gerar um numero de processos
		filhos para simular multiplos clientes conectando ao mesmo servidor.*/
		if(pid = fork() == 0)
		{
			Cliente(x+1); /*Se fork retorna 0, então ele está retornando o processo pai
						entao chamamos a funcao*/
			exit(0);
		}
	}

	wait(NULL);
	return 0;
}

void Cliente(int num_clientes)
{
	int x, sock;
	struct sockaddr_in servidor;
	char buffer[25];

	servidor.sin_port = 0;
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket");
		exit(1);
	}

	if((bind(sock, (const struct sockaddr *)&servidor, sizeof(servidor))) == -1)
	{
		perror("Bind");
		exit(1);
	}

	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	servidor.sin_port = htons(1980);

	if((connect(sock, (const struct sockaddr *)&servidor, sizeof(servidor))) == -1)
	{
		perror("Conexão");
		exit(1);
	}

	snprintf(buffer, 128, "dados do cliente: #%i.", num_clientes);
	sleep(2);
	printf("Cliente #%i enviou %li caracteres\n",num_clientes, send(sock, buffer, strlen(buffer), 0));
	sleep(1);
	printf("Cliente #%i recebeu %li caracteres\n",num_clientes, recv(sock, buffer, 25, 0));
	sleep(1);

	close(sock);

}

