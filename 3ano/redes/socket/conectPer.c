#include <stdio.h> //printf
#include <string.h> //strcpy
#include <sys/socket.h>
#include <netdb.h> //conteúdo do host 
#include <arpa/inet.h> //conversao de endereço, de ip para
#include <unistd.h> //para função write
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int meuSocket, novoSocket, c;
	struct sockaddr_in servidor, cliente;
	char *mensagem;

	//criar um socket
	meuSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (meuSocket == -1)
	{
		printf("Erro ao criar o socket!\n");
	}

	//preparando a estrutura sockaddr_in
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons( 8888 );

	//bind - ligando uma conexão socket a uma porta local
	if ( bind(meuSocket, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
	{
		puts("Erro no bind\n");
	}
	puts("Bind executado corretamente!!\n");

	//Listen - ouvindo conexoes
	listen(meuSocket, 3); //aceita até 3 conexoes;

	//aceitando conexoes
	puts("Aguardando chegada de conexoes.......\n");
	c = sizeof(struct sockaddr_in);
	while(novoSocket = accept(meuSocket, (struct sockaddr *)&cliente, (socklen_t*)&c))
	{
		puts("Conexão aceita!\n");

		//respondendo ao cliente
		mensagem = "E ai mano. Acabei de receber a sua conexão. Fallows\n";

		send(novoSocket, mensagem, strlen(mensagem), 0);
		/*char *msg;
		fgets(msg,10,stdin);
		send(novoSocket, msg, strlen(msg),0);
		if((recv(novoSocket, msg, strlen(msg), 0)) > 0)
			printf("%d\n", atoi(msg));
		else puts("Não recebi!\n");
		recv(novoSocket, msg, 10, 0);
		printf("%s\n", msg);*/
	}//fim while
	if(novoSocket <0)
	{
		perror("Erro ao aceitar conexão!!\n");
	}//fim if

	return 0;
}