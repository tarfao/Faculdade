#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 1. COMO COPIAR DOIS ARQUIVOS DE VEZ LEIA(ARQUIVO1,ARQUIVO2)

// 2. BAGUNÇA QUANDO VOCÊ EXCLUI UM CADASTRO, POIS A SEQUENCIA MUDA,
//SE VOCE DELETAR O PRIMEIRO, O SEGUNDO VAI FICAR COMO PRIMEIRO
//E SE FOR IMPRIMIR PARA O USUARIO A PARTIR DO QUE ELE VER NA TELA,
//NAO VAI APARECER CONFORME O ESPERADO POR ELE - EASY
typedef struct cad
{
	char nome[20];
	int idade;
	int ativo;
} pessoa;

//abrindo um arquivo de qualquer modo
FILE *abreArq (char *nome_arq, char *abr_mod)
{
	FILE *arq;

	if ((arq = fopen(nome_arq,abr_mod)) == NULL)
	{
		printf("Erro abrindo, 100\n");
		exit(100);
	}

	return(arq);

}

void mostra (int *k)
{
    int q=0;
    if (q==0)
    {
        q = 2;
        printf("\n\t tarfa - > %d  q = %d\n",*k,q);
    }
}
void cadastrando(pessoa c[], int *q)
{
	pessoa rpessoa;
	char s;

	//pfiletemp = abreArq("arquivo.dat","a+b");

	do{
		/*if(cont==2)
		{
			printf("\nTam: %ld\n",ftell(pfiletemp));
		}*/
		mostra(&*q);
		fflush(stdin);
		printf("Nome: ");
        printf("-> %d",*q);
		getchar();
        printf("-> %d",*q);
		fgets(rpessoa.nome,20,stdin);
		printf("ID: ");
        printf("-> %d\n",*q);
		scanf("%d",&rpessoa.idade);
        printf("-> %d\n",*q);

		rpessoa.ativo = 1;
		c[*q] = rpessoa;
		*q = *q + 1;
		printf("Continua? S/n   -> %d",*q);
		getchar();
		scanf("%c",&s);
	}while(s == 'S' || s == 's');
	//fclose(pfiletemp);
}

//--------------------------------------------------------------------------
//OBJETIVO: MOSTRA OS CADASTROS
//--------------------------------------------------------------------------
void mostraCad (pessoa c[],int q)
{
	int pos;
	pessoa lpessoa;
	int pos_usu=0;
	int i;
	//FILE *pfile;

	system("cls");

	//pfile = abreArq("arquivo.dat","rb");
	//fseek(pfile,0,SEEK_SET);
	for(i=0;i<q;i++)
    {
        printf("%d numero ativo -> %d  -- ",i+1, c[i].ativo);
        printf("%s",c[i].nome);
    }
	/*do{
		pos_usu++;
		if (fread(&lpessoa,sizeof(lpessoa),1,pfile)>0){
			if (lpessoa.ativo == 1){
			}
		}
	}while(!feof(pfile));*/

	printf("\nMostra separado:\nNumero -> ");
	scanf("%d",&pos);
	if (c[pos].ativo==1)
    {
        printf("NOME -> %s",c[pos].nome);
        printf("ID -> %d\n",c[pos].idade);
    }
    else
    {
        system("cls");
        printf("Cadastro nn encontrado\n\n");
    }
	/*fseek(pfile,0,SEEK_SET);
	fseek(pfile,sizeof(lpessoa)*(pos-1),SEEK_SET);
	if (fread(&lpessoa,sizeof(lpessoa),1,pfile)>0){
		system("clear");
		if (lpessoa.ativo == 1){
			printf("NOME -> %s",lpessoa.nome);
			printf("ID -> %d\n",lpessoa.idade);
		}
	}
	else
	{
		system("clear");
		printf("Cadastro nn encontrado\n\n");
	}	*/
	//fclose(pfile);
}

void main (void)
{
	FILE *pfiletemp;
	pessoa rpessoa;
	//pessoa lpessoa;
	int i;
	pessoa vpessoa[1000];
	int p=0;
	int n;//obtem uma opcao do usuario
	int ver;//Verifica se ja foi criado o arquivo

	if ((pfiletemp = fopen("arquivo.dat","r+b")) == NULL)
	{
		pfiletemp = abreArq("arquivo.dat","w+b");
	}

	do{
        if (fread(&rpessoa,sizeof(pessoa),1,pfiletemp)==1)
        {
           vpessoa[p] = rpessoa;
           p++;
        }
	}while(!feof(pfiletemp));
	fclose(pfiletemp);

	do{
		printf("1 - Insere\n");
		printf("2 - Mostrar\n");
		printf("3 - Excluir\n");
		printf("4 - Altera\n");
		printf("5 - Sair    -> %d\n",p);
		scanf("%d",&n);


		if (n==1)
		{
			cadastrando(vpessoa,&p);
		}


		if (n==2)
		{
			//if (ver>1)
			//{
			mostraCad(vpessoa,p);
			//}
			//else
			//{
				//system("clear");
				//printf("Nenhum cadastro efetuado!!\n");
			//}
		}


		if(n==3)
		{
			int pos;
			int achou=1;//1 nao achou, 2 achou
			FILE *pfile;
			int s=0;
			//int j;
			system("cls");
			printf("Qual a idade da pessoa que deseja deletar? \n");
			scanf("%d",&pos);
			//pfiletemp = abreArq("arquivo.dat","a+b");
			while (s!=p+1 && achou==1)
			{
			    if (vpessoa[s].idade == pos)
                {
                    achou = 2;
                }
                s++;
			}
			/*fseek(pfiletemp,0,SEEK_SET);
			do{
				fread(&lpessoa,sizeof(lpessoa),1,pfiletemp);
				if (lpessoa.idade == pos && lpessoa.ativo == 1)
				{
					achou = 2;
				}
			}while(!feof(pfiletemp) && (achou == 1));*/
			if (achou == 2)
			{
				//fseek(pfiletemp, sizeof(lpessoa) * -1, SEEK_CUR);
				vpessoa[s-1].ativo = 2;
				{
					system("cls");
					printf("Gravacao concluida com sucesso\n" );
				}
			}
			else
			{
				system("cls");
				printf("Pessoa não encontrada\n\n");
			}
			/*if (fread(&lpessoa,sizeof(lpessoa),1,pfiletemp) > 0)
			{
				//printf("->  é aq tarfao  <-\n");
				lpessoa.ativo = 2; //esse campo do registro não ta sendo gravado
				printf("\nnumero ativo dps de deletar-> %d\n\n", lpessoa.ativo);
				if (fwrite(&lpessoa,sizeof(lpessoa),1,pfiletemp)==1)
				{
					system("clear");
					printf("Gravado com sucesso\n");
				}
				else
				{
					system("clear");
					printf("Erro em gravacao\n" );
				}
			}
			else
			{
				system("clear");
				printf("Erro copia...");
			}*/
			//fclose(pfiletemp);

		}

		if(n==4)
		{
			int pos;
			int atual;
			int achou=1;
			int s=0;
			system("cls");
			printf("Qual a idade do cliente? ");
			scanf("%d",&pos);
			//pfiletemp = abreArq("arquivo.dat","w+b");
			//printf("\nNumero de bytes: %ld \n",ftell(pfiletemp));

			while (s!=p+1 && achou==1)
			{
			    if (vpessoa[s].idade == pos)
                {
                    achou = 2;
                }
                s++;
			}
			/*fseek(pfiletemp,0,SEEK_SET);
			do{
				fread(&lpessoa,sizeof(lpessoa),1,pfiletemp);
				if (lpessoa.idade == pos)
				{
					achou = 2;
				}
			}while(!feof(pfiletemp) && (achou == 1));*/

			//fseek(pfiletemp,sizeof(lpessoa)* -1, SEEK_CUR);
			if (achou == 2)
			{
				printf("Nome antigo -> %s\n Nome atual: ",vpessoa[s-1].nome);
				fflush(stdin);
				getchar();
				fgets(vpessoa[s-1].nome,20,stdin);
                system("cls");
                printf("Gravacao efetuada com sucesso\n");


			}
			else
			{
				system("cls");
				printf("Cliente nao encontrado\n");
			}
			//rewind(pfiletemp);
			/*if (fread(&lpessoa,sizeof(lpessoa),1,pfiletemp) > 0)
			{
				printf("\nPOSICAO ATUAL: %d\n\nNOME -> ",atual);
				getchar();
				fgets(lpessoa.nome,20,stdin);
				fwrite(&lpessoa,sizeof(lpessoa),1,pfiletemp);
			}
			else
			{
				system("clear");
				printf("Erro copia...");
			}*/
			//fclose(pfiletemp);

		}
	}while(n!=5);

	if ((pfiletemp = fopen("arquivo.dat","w+b")) == NULL)
    {
        printf("\n\tERRO FINAL! !");
        exit(10);

    }

    for (i=0;i<p;i++)
    {
        rpessoa = vpessoa[i];
        if (fwrite(&rpessoa,sizeof(pessoa),1,pfiletemp)!=1)
        {
            printf("Gravação concluida com sucesso! ! %d",i+1);
        }
    }
	fclose(pfiletemp);
}
