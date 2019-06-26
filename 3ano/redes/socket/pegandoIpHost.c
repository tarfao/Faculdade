//Programa para pegar o host e o ip 
#include <stdio.h> //printf
#include <string.h> //strcpy
#include <sys/socket.h>
#include <netdb.h> //conteúdo do host 
#include <arpa/inet.h> //conversao de endereço, de ip para
					//o formato longo, que o pc consiga entender

int main(int argc, char const *argv[])
{
	char *nomeHost = "www.google.com.br";
	char ip[100];
	struct hostent *maquina;//conteúdo do host
	struct in_addr **addr_list;//
	int i;

	/*
	Para se conectar a um host remoto é necessário obter o 
	endereço ip. A função gethostbyname é usada para este
	propósito. Ela pega o nome do domínio como parâmetro e retorna 
	a estrutura do tipo hostent.
	Esta estrutura tem a informação do ip. A biblioteca é a netdb.h*/

	if((maquina = gethostbyname( nomeHost )) == NULL)
	{
		//o gathostbyname falhou
		herror("gethostbyname");
		return 1;
	}//fim do if

	//aqui vamos dar um cast em h_addr_list para in_addr
	//uma vez que h_addr_list também tem o endereço ip, mas
	//somente no formato longo

	addr_list = (struct in_addr **) maquina->h_addr_list;

	for(i=0; addr_list[i] != NULL; i++)
	{
		//retorna o primeiro encontrado
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}

	printf("\n%s possui o endereço ip: %s\n", nomeHost, ip);

	return 0;
}//fim do int
