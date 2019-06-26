#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	int meu_socket;

	meu_socket = socket(AF_INET,SOCK_STREAM,0);/*STREAM DE DADOS = TCP*/

	if(meu_socket == -1)
		printf("Erro ao criar o socket\n");
	else
		printf("Socket cirado com sucesso!\n");

	return 0;
}