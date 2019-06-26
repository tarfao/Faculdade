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



int main(int argc, char* argv[])
{
	int pid;
	int x, sock, tamanho;
	struct sockaddr_in servidor;
	char buffer[100], bufferin[100];
	char IP_SERVIDOR[15]="127.0.0.1";

	servidor.sin_port = 0;
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;

	if(argc > 1)
	{
		strcpy(IP_SERVIDOR,argv[1]);
	}
	printf("IP = %s\n",IP_SERVIDOR);

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

	servidor.sin_port = htons(10000);
	servidor.sin_addr.s_addr = inet_addr(IP_SERVIDOR);

	if((connect(sock, (const struct sockaddr *)&servidor, sizeof(servidor))) == -1)
	{
		perror("Conexão");
		exit(1);
	}

	snprintf(buffer, 128, "dados do cliente.");
	sleep(2);
	printf("Cliente enviou %li caracteres\n", send(sock, buffer, strlen(buffer), 0));
	sleep(1);
	printf("Cliente recebeu %li caracteres\n",recv(sock, buffer, 25, 0));
	sleep(1);
	//faço uma leitura dos dados de entrada do usuário para fins de testes (se enviam podem enviar msgs simultaneamente)
	do{
		printf("Entre com uma mensagem para o servidor >> ");
		fflush(stdin);
		fgets(buffer,25,stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if( (send(sock, buffer, strlen(buffer), 0)) == -1)
		{
			puts("Send");
			exit(1);
		}
		/*AQUI FAZ O RECEBIMENTO DAS MENSAGENS DOS DEMAIS CLIENTES*/
		if((tamanho = recv(sock, bufferin, sizeof(bufferin), 0)) < 0 )
		{
			printf("Erro recv");
		}
		else
		{
			bufferin[tamanho] = '\0';
			printf("Clientes >> %s \n",bufferin);
		}
	}while(strcmp(buffer,"exit") != 0);

	close(sock);


	wait(NULL);
	return 0;
}


