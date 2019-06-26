/*Deamon*/
#include <stdio.h>
#include <stdlib.h> /*uso do exit*/
#include <sys/types.h>
#include <sys/stat.h> /*uso do umask*/
#include <syslog.h> /*para usar openlog e syslog*/

int deamonize()
{
    pid_t pid;
    long n_desc;
    int i;

    /*Essa funcao fork() desatacha o processo do terminal*/
    if((pid = fork()) != 0)
    {
        exit(0);
    }

    setsid(); /*Cria um novo grupo de processos e um novo grupo de sessao
	       A funcao torna o processo o unico membro e lider de ambos
 	       os grupos*/
    if((pid = fork()) != 0)
    {
        exit(0);
    }

    /*Novamente a funcao fork() retira o processo pai. Os grupos de sessao
     e processos sao retirados e como o processo pai nao eh mais lider ele
     nao pode mais ser controlado pelo terminal*/
    
    chdir("/");/*Muda o diretorio de trabalho para o diretorio root*/
    umask(0); /*A funcao umask() limpa o file-mode creation*/

   /*Fecha todo arquivo aberto pelo fork()*/ 
    n_desc = sysconf(_SC_OPEN_MAX);
    for(i = 0; i < n_desc; i++)
    {
        close(i); 
    }/*fim do for*/

    return 1;
}//fim da funcao deamonize


int main(int argc, char* argv[])
{
    deamonize();
    openlog("teste deamon", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "%s", "Oi mundo!");
    closelog();

    return 0;
}
