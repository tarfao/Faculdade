#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	int meu_socket;

	meu_socket = socket(AF_INET,SOCK_DGRAM,0);//AF_INET, é o endereço da família que seu socket 
												//poderá se comunicar, tem família do bluetooth
												 //Unix, entre outras, essa é de internet
												//aqui também utilizamos o udp, e o endereço IP

	if(meu_socket == -1)
		printf("Erro ao criar o socket\n");
	else
		printf("Socket cirado com sucesso!\n");

	return 0;
}