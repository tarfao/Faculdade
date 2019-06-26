/*
socket = controla a porta para acesso
*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> //usamos o inet addr
#include <unistd.h>
typedef struct sockaddr_in serv;

int main(int argc, char const *argv[])
{
	int meu_socket;
	serv servidor;
	char *mensagem;
	char resposta_servidor[2000];

	meu_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(meu_socket == -1){
		printf("Erro ao criar socket\n");
	}

	servidor.sin_addr.s_addr = inet_addr("172.217.29.195");
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(80);

	//conectar a um servidor remoto
	if(connect(meu_socket, (struct sockaddr *)&servidor, sizeof(servidor)))
	{
		puts("Erro ao conectar\n");
		return 1;
	}
	puts("Conectado\n");

	//enviando dados
	mensagem = "GET / HTTP/1.1\r\n\r\n"; //comando para buscar uma página principal de um site
	if(send(meu_socket, mensagem, strlen(mensagem), 0) < 0)
	{
		puts("Falha ao enviar\n");
		return 1;
	}
	puts("Dados enviados\n");

	//recebendo a resposta do servidor 
	if(recv(meu_socket, resposta_servidor, 2000, 0) < 0)
	{
		puts("Falha ao receber dados\n");
		return 1;
	}
	puts("Resposta recebida\n");
	puts(resposta_servidor);
	close(meu_socket);

	return 0;
}