#include <unistd.h>/*funcao read*/
#include <stdio.h>/*printf, scanf...*/
#include <string.h>
#include <stdio_ext.h>

int main(char *argv)
{
	char nome[20];
	char msg[23]={"entre com seu nome: "};
	char welcome[20]={"bem vindo, "};
	int ver;

	write(1,&msg,23);
	__fpurge(stdin);
	if(read(0,&nome,20)!=strlen(nome))
	{
		printf("\n----ERRO NA GRAVACAO----!!\n");
	}
	else
	{
		write(1,&welcome,strlen(welcome));
		write(1,&nome,strlen(nome));
	}


	return 0;
}