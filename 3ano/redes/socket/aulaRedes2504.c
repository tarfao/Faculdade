#ifndef unix /*se nada foi especificado, vamos utilizar os protocolos do unix*/
#define WIN32
#include <windows.h>
#include <winsock.h>
#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PROTOPORT 5193 /*numero de porta do protocolo padrão*/
#define QLEN 6 /*quantidade de pedido que a conexão poderá aceitar*/

int visitas = 0; /*contador do numero de clientes conectador*/


int main(int argc,char *argv[])
{
	//struct hostent *ptrh; /*ponteiro para a entrada da tabela do host*/
	struct protoent *ptrp; /*ponteiro para a entrada da tabela do protocolo*/
	struct sockaddr_in sad; /*estrutura que armazena o endereço do servidor*/
	struct sockaddr_in cad; /*estrutura que armazena o endereço do cliente*/
	int sd, sd2; /*descritor do socket*/
	int port; /*numero da porta do protocolo*/
	int alen; /*tamanho do endereço*/
	char buffer[1000]; // buffer para armazenar as mensagens enviadas pelo servidor 
	char bufferCli[1000];
	int tamMsgCli; 
	int ativo = 1;

	#ifdef WIN32
	#define WSADATA wsaData;
	#define WSAstartup (0x0101,&wsaData);
	#endif
	
	memset ((char *)&sad, 0, sizeof(sad)); /*limpa a estrutura sockaddr*/
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = INADDR_ANY; /*configura o endereço ip local*/
	
	if(argc > 1) { //verifica se o argumento especificado é valido
		port  = atoi(argv[1]); //converte o argumento para binário
	} else {
		port = PROTOPORT; /*usa o numero de porta padrão*/
	}
	if (port > 0){ /*verifica se os valores são válidos*/
		sad.sin_port = htons((u_short)port);	
	}else {
		fprintf(stderr, "Numero de porta inválido %s\n",argv[1]); /*stderr = erro padrão, que é jogado no argv[1],
																						o próprio SO diz qual erro seu programa esta dando*/
		exit(1);
	}
	
	//Mapear o protocolo TCP para o numero de porta
	if( ((int*) (ptrp = getprotobyname("tcp")))==0){
		fprintf(stderr, "Falha ao mapear \"tcp\" para o numero de protocolo\n");
		exit(1);	
	}
	
	//cria o socket
	sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if(sd < 0 )
	{
		fprintf(stderr, "Falha ao criar socket\n");
		exit(1);	
	}
	
	//fazer a lincagem (bind) no endereço local com o socket)
	if(bind(sd, (struct sockaddr *)&sad, sizeof(sad))< 0 )
	{
		fprintf(stderr, "Falha no bind\n");
		exit(1);	
	}
	
	/*Especificar o tamanho da fila de mensagens de chegada*/
	if( listen(sd, QLEN) < 0)
	{
		fprintf(stderr, "Falha na função listen\n");
		exit(1);	
	}		
	
	/*loop do servidor - aceita e mantém os pedidos de conexão*/
	fprintf(stderr, "Servidor ativo e rodando. \n");
	while(sd > 0)
	{
		alen = sizeof(cad);
		fprintf(stderr, "SERVIDOR: Aguardando por conexões...\n");
		
		if((sd2 = accept(sd, (struct sockaddr *)&cad, &alen)) < 0)
		{
			fprintf(stderr, "Falha na funcao accept\n");
			exit(1);		
		}	
		visitas++;
		sprintf(buffer, "Este servidor foi contactado %d vezes %s\n", visitas, visitas==1?".":"s.");
		fprintf(stderr, "SERVIDOR: %s", buffer);
		send(sd2, buffer, strlen(buffer), 0);

		do{
			fflush(stdin);
			/*Para receber a mensagem do cliente
			precisa setar o valor da conexão que foi 		
			aceita, como primeiro argumento*/
			if((tamMsgCli = recv(sd2, bufferCli, 1000, 0)) == -1) 
			{
				puts("Erro na funcao recv!!\n");
				exit(1);
			}
			bufferCli[tamMsgCli] = '\0';
			printf("%s\n",bufferCli);

			if(strcmp(bufferCli,"exit") == 0)
				ativo = 0;
			/*recebendo a msg do cliente
			tamMsgCli = recv(sd, buffer, strlen(buffer), 0);
			fprintf(stderr, "Cliente diz: %s\n", buffer);*/
		}while(ativo);

		printf("Conexão encerrada\n");
		close(sd);
		close(sd2);	
	}
	return 0;
}
