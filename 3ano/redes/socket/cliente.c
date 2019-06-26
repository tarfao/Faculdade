/*Cliente*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PROTOPORT 5193 /*O número do protocolo padrão
						obs: Poderia ser qualquer outra*/

extern int errno;
char localhost[] = "localhost"; /*O cliente roda na própria maq*/

int main(int argc, char const *argv[])
{
	struct hostent *ptrh; 	/*Ponteiro para a tabela de entrada do host*/
	struct protoent *ptrp; 	/*Ponteiro para a tablea de entrada do protocolo*/
	struct sockaddr_in sad;	/*estrutura para manter o endereço do serv*/
	int sd; 				/*Descritor do socket*/
	int port; 				/*número da porta do protocolo*/
	char *host; 			/*Ponteiro para o nome do host*/
	int n; 					/*Usado para o número de caracteres*/
	char buf[1000]; 		/*Buffer para os dados recebidos do servidor*/
	char msg[100];
	int tamMsg;
	int ativo;

	memset((char *)&sad, 0, sizeof(sad)); /*Limpa a estrutura sockaddr*/
	sad.sin_family = AF_INET;

	if(argc > 2)
		port = atoi(argv[2]);
	else
		port = PROTOPORT;

	if(port > 0)
	{
		sad.sin_port = htons((u_short)port);
	}
	else
	{
		fprintf(stderr," Numero da porta inválido %s\n", argv[2]);
		exit(1);
	}

	if(argc > 1)
		strcpy(host,argv[1]);
	else
		host = localhost;

	ptrh = gethostbyname(host);

	if( ((char *)ptrh) == NULL )
	{
		fprintf(stderr, "Host invalido: %s\n", host);
		exit(1);
	}

	memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);

	if( (int)(ptrp = getprotobyname("tcp")) == 0)
	{
		fprintf(stderr, "Erro ao mapear \"tcp\" para o numero do procolo.\n");
		exit(1);
	}

	if((sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto)) < 0)
	{
		fprintf(stderr, "Erro ao criar socket.\n");
		exit(1);
	}

	if((connect(sd, (struct sockaddr *)&sad, sizeof(sad))) < 0)
	{
		fprintf(stderr, "Falha na conexao\n");
		exit(1);
	}

	n = recv(sd, buf, sizeof(buf), 0);
	buf[n] = '\0';
	fprintf(stderr,"Cliente: %s\n", buf);

	/*if(send(sd, "Iniciar conversa", 17, 0) == -1)
	{
		printf("Erro na funcao send!!\n");
		exit(1);
	}*/

	while(sd > 0)
	{
		fflush(stdin);
		fgets(msg,100,stdin);
		msg[strlen(msg)-1] = '\0';
		if(send(sd, msg, strlen(msg), 0) == -1)
		{
			printf("Erro na funcao send!!\n");
			exit(1);
		}
	}//fim do while

	close(sd);
	return 0;
}//fim do main