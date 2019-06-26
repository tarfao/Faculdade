#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> //essa biblioteca é necessária para usar inet addr
					  //que permite converter um endereço ip em um formato longo

int main(int argc, char const *argv[])
{
	int meu_socket;
	struct sockaddr_in servidor;

	meu_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(meu_socket == -1)
		printf("Erro ao criar o socket\n");
	
	servidor.sin_addr.s_addr  = inet_addr("162.144.34.172");//sin_addr = endereço de entrada, 
	                                                        //s_addr = endereço do servidor
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(80);

	//conectar a um servidor remoto
	if(connect(meu_socket, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
	{
		puts("Erro ao conectar!");
	}
	puts("conectado");
	return 0;
}