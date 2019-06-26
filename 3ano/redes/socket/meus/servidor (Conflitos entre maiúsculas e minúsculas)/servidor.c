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
	int ssd, scd; /*Descritor do socket servidor e cliente*/
	struct sockaddr_in servidor, cliente;
	char buffer[100];
	int aux; /*Auxilia o retorno de algumas funcoes para identificar erros*/
	char resposta1[10];/*Resposta 1 do cliente, um operando*/
	char resposta2[10];/*Resposta 2 do cliente, um operador*/
	char resposta3[10];/*Resposta 3 do cliente , um operando*/
	char operador; /*Essa caracter é criado com a finalidade de fazer a cópia do conteúdo
					de resposta2, que é um operador, para podermos fazer um switch com
					essa variável operador*/
	int tam1; /*Tamanho da resposta 1 do cliente*/
	int tam2; /*Tamanho da resposta 2 do cliente*/
	int tam3; /*Tamanho da resposta 3 do cliente*/
	int num1, num2;/*Obtem a conversao dos dois numeros enviado pelo cliente*/
	int resultado; /*Obtem o resultado da operacao enviada na resposta 2 do cliente*/

	/*=========================Preparando o servidor=========================================*/
	servidor.sin_family = AF_INET; /*Trabalhamos com protocolos da internet*/
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(5194);

	ssd = socket(AF_INET, SOCK_STREAM, 0);

	if(ssd == -1)
	{
		perror("Socket");
		exit(1);
	}
	printf("\nSeu socket foi criado com sucesso!\n");

	aux = bind(ssd,(struct sockaddr *)&servidor,sizeof(servidor));
	if(aux == -1)
	{
		perror("Bind");
		exit(1);
	}
	printf("\nAgora você possui uma porta associada com um socket!!\n");

	listen(ssd, 5);/*Ouvindo a porta*/
	printf("Aguardando conexoes...\n");
	/*==========================FINAL DA PREPARAÇÃO E INÍCIO DE CONEXÃO========================*/

	aux = sizeof(cliente);
	scd = accept(ssd, (struct sockaddr *)&cliente, &aux);
	if(scd == -1)
	{
		perror("Accept");
		exit(1);
	}
	printf("Conexão aceita com o cliente %d.\n",scd);

	/*=================Envia uma mensagem de identificação para o cliente*/
	strcpy(buffer,"Olá eu sou uma calculadora, faça seu cálculo (+, -, *, /)\n");
	aux = send(scd, buffer, strlen(buffer), 0);
	if(aux == -1)
	{
		perror("Send");
		exit(1);
	}
 
	/*=============Recebendo resposta 1*/
	tam1 = recv(scd,resposta1,sizeof(resposta1),0);
	if(tam1 == -1)
	{
		perror("Tam1");
		exit(1);
	}
	num1 = atoi(resposta1);
	printf("Mensagem 1 recebida = %s | Conversao = %d.\n",resposta1,num1);

	/*=============Recebendo resposta 2*/
	tam2 = recv(scd,resposta2,sizeof(resposta2),0);
	if(tam2 == -1)
	{
		perror("Tam2");
		exit(1);
	}
	operador = resposta2[0]; /**/
	printf("Mensagem 2 recebida = %s\n",resposta2);

	/*============Recebendo resposta 3*/
	tam3 = recv(scd,resposta3,sizeof(resposta3),0);
	if(tam3 == -1)
	{
		perror("Tam3");
		exit(1);
	}
	num2 = atoi(resposta3);
	printf("Mensagem 3 recebida = %s Conversao = %d.\n",resposta3,num2);

	/*===============Verifica qual operador o cliente enviou*/
	switch(operador)
	{
		case '+':
			resultado = num1 + num2;
		break;

		case '-':
			resultado = num1 - num2;
		break;

		case '/':
			resultado = num1 / num2;
		break;

		case '*':
			resultado = num1 * num2;
		break;

		default:
			printf("Não entendemos sua operação\n");
			resultado = 0;
		break;
	}

	sprintf(buffer,"Resultado = %d. Valeus!!!\n",resultado);
	aux = send(scd, buffer, strlen(buffer), 0);
	if(aux == -1)
	{
		perror("Send");
		exit(1);
	}

	close(scd);
	close(ssd);
	return 0;
}