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
#include <pthread.h>


void* thread_recv(void *arg);/*Cria uma thread para controlar o recebimento de mensagens*/
void* thread_send(void *arg);/*Cria uma thread para controlar o envio de mensagem*/

int main(int argc, char* argv[])
{
	int pid;
	int x, sock, resultado;
	struct sockaddr_in servidor;
	char buffer[100], bufferin[100];
	char IP_SERVIDOR[15]="127.0.0.1";/*localhost*/
	pthread_t thread1, thread2; /*Para criação das duas threads, recv e send*/

	servidor.sin_port = 0;
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;

	if(argc > 1)
	{
		strcpy(IP_SERVIDOR,argv[1]);/*Obtendo o endereço de IP do servidor caso digitou*/
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

	/*Cria a thread para receber mensagens*/
	resultado = pthread_create(&thread1, NULL, thread_recv, (void *)&sock);
	if(resultado != 0)
	{
		printf("Nao foi possível criar a thread1");
		exit(1);
	}
	/*Cria a thread para enviar mensagens*/
	resultado = pthread_create(&thread2, NULL, thread_send, (void *)&sock);
	if(resultado != 0)
	{
		printf("Nao foi possível criar a thread2");
		exit(1);
	}


	if(pthread_join(thread2, NULL)==0)
		close(sock);


	wait(NULL);
	return 0;
}

void* thread_recv(void *arg)
{
	int sock; //recebe o descritor de socket
	int recebidos;
	char buffer[50];

	sock = *(int *)arg;

	while(1)
	{
		recebidos = recv(sock,buffer,sizeof(buffer), 0);
		if(recebidos > 0)
		{
			buffer[recebidos] = '\0';
			printf("%s\n",buffer);
		}
	}
	
}

void* thread_send(void *arg)
{
	int sock;/*Recebe o descritor do socket*/
	char buffer[50];

	sock = *(int *)arg;
	do	
	{
		printf(">> ");
		fgets(buffer,50,stdin);
		buffer[strlen(buffer)-1] = '\0';
		if((send(sock,buffer,strlen(buffer),0) == -1))
		{
			perror("Sendc");
			exit(1);
		}
	}while(strcmp(buffer,"exit")!=0);	

}


