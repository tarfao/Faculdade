/*Possíveis bibliotecas utilizadas na manipulação de dados e funcoes essenciais como printf...*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
/*Bibliotecas para o socket e para algumas variáveis já definida dentro delas*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	int scd;
	struct sockaddr_in servidor;
	int aux; /*Auxilia no retorno das funcoes para saber se teve erro ou não*/
	char buffer[100];
	char envio1[10];
	char envio2[10];
	char envio3[10];
	int tam; /*Obtem o tamanho da mensagem enviada pelo servidor*/
	char resultado[100];

	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(5194);

	/*============CRIANDO O SOCKET*/
	scd = socket(AF_INET, SOCK_STREAM, 0);
	if(scd == -1)
	{
		perror("Socket");
		exit(1);
	}
	printf("\nSocket criado com sucesso!\n");

	/*============FAZENDO CONEXAO COM O SERVIDOR*/
	aux = connect(scd,(struct sockaddr *)&servidor, sizeof(servidor));
	if(aux == -1)
	{
		perror("Connect");
		exit(1);
	}
	printf("Conexão com o servidor efetuada!\n\n");

	/*================RECEBENDO MENSAGEM DO SERIVOOR*/
	tam = recv(scd, buffer, sizeof(buffer),0);
	if(tam == -1)
	{
		perror("Send");
		exit(1);
	}
	buffer[tam] = '\0';
	printf("===============================================================\n");
	printf("Servidor diz >> %s\n",buffer);

	/*===============OBTENDO O PRIMEIRO VALOR E ENVIANDO PARA O SERVIDOR*/
	printf("Entre com o primeiro operando: ");
	fgets(envio1,10,stdin);
	envio1[strlen(envio1) - 1] = '\0';
	aux = send(scd, envio1, strlen(envio1), 0);
	if(aux == -1)
	{
		perror("Send1");
		exit(1);
	}

	/*===============OBTENDO O OPERADOR*/
	printf("Entre com o operador: ");
	fgets(envio2,10,stdin);
	envio2[1] = '\0';/*Como o operador é do tipo (*, +, - ou /) ou seja, um caracter,
					ele estará na posição 0 da string, por tanto coloco o finalizador 
					de string na próxima posicao, 1*/
	aux = send(scd, envio2, strlen(envio2), 0);
	if(aux == -1)
	{
		perror("Send2");
		exit(1);
	}

	/*=============OBTENDO O SEGUNDO OPERANDO*/
	printf("Entre com o segundo operando: ");
	fgets(envio3,10,stdin);
	envio3[strlen(envio3) - 1] = '\0';
	aux = send(scd, envio3, strlen(envio3), 0);
	if(aux == -1)
	{
		perror("Send3");
		exit(1);
	}

	/*============RECEBENDO MENSAGEM DO SERVIDOR*/
	tam = recv(scd, resultado, sizeof(resultado), 0);
	if(tam == -1)
	{
		perror("Recv");
		exit(1);
	}
	printf("Servidor diz >> %s",resultado);

	return 0;
}