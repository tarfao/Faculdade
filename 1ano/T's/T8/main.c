#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct rdatanascimento{
    int dia;
    int mes;
    int ano;
}nasci;

typedef struct rcliente {
    int cod;
    char nome[35];
    char sexo;
    nasci dn;
    char rg[11];
    char cpf[12];
    char end[30];
    char cid[30];
    char uf[3];
    int total_fitas_ja_locadas;
    int fitas_locadas_atual;
    int ativo; //1: ativo - 2: inativo
}vcliente[10];


//-------------------------------------------------------------
//OBJETIVO: DEIXAR COMO INATIVO, TODAS AS POSICOES DE CADASTRO
//PARAMETRO: c, REGISTRO TOTAL
//--------------------------------------------------------------
void inicia_inativo(vcliente c;)
{
    int i;

    for (i=0;i<10;i++)
    {
        c[i].ativo = 2;
        c[i].fitas_locadas_atual = 0;
        c[i].total_fitas_ja_locadas = 0;
    }
}
//--------------------------------------------------------------
//OBJETIVO:	APRESENTAR UM MENU DE OPCOES
//		    E OBTER UMA OPCAO DO USUARIO
//RETORNO: A OPCAO ESCOLHIDA
//--------------------------------------------------------------

int menu()
{
    int op;

    do {
        printf("\n\t1 - INCLUIR CLIENTE\n");
        printf("\t2 - MOSTRAR CLIENTES\n");
        printf("\t3 - REMOVE CLIENTE\n");
        printf("\t4 - LOCAR FITA\n");
        printf("\t5 - DEVOLVER FITAS\n");
        printf("\t6 - MOSTRAR CLIENTES COM FITAS\n\t");
        scanf("%1d",&op);
        fflush(stdin);
    }while(op>6 || op<1);

    return(op);

}

//--------------------------------------------------
//OBJETIVO:	GERA O PROXIMO CODIGO SEQUENCIAL
//		    PARA INCLUSAO DE UM CLIENTE
//RETORNO: PROXIMO CODIGO GERADO
//--------------------------------------------------

int obtem_codigo()
{
    int codigo;

    codigo = rand()%20 + 1;

    return(codigo);
}

//--------------------------------------------------------------
//OBJETIVO:	REALIZA O CADASTRO DE UM NOVO CLIENTE
//PARAMETROS:   c REPRESENTA O CONJUNTO DE REGISTRO DE CLIENTES
//              q REPRESENTA A QUANTIDADE TOTAL DE CLIENTES
//--------------------------------------------------------------

void inclui_cliente (vcliente c; int *q)
{
    int a=0;//verifica se foi digitado apenas numeros no rg
    int i=0;
    int pos; //pega a proxima posicao vazia

    pos = obtem_posicao_inculsao(c);
    if (pos){
        c[pos].cod = obtem_codigo;
        printf("\n\tDIGITE SEU NOME:\n\t ")
        gets(c[pos].nome);
        system("cls");
        do{
            printf("\n\tSEXO ('M' OU 'F'): \n\t");
            scanf("%s",&c[pos].sexo);
            if(c[pos].sexo!='m' || c[pos].sexo!='M' ||  c[pos].sexo!='f' || c[pos].sexo!='F')
            {
                system("cls");
                printf("\n\tERROR 98");
            }
            else{
                system("cls");
            }
        }while(c[pos].sexo!='m' || c[pos].sexo!='M' ||  c[pos].sexo!='f' || c[pos].sexo!='F');
        printf("\n\tDATA DE NASCIMENTO: ");
        printf("\n\tDIA: \n\t");
        scanf("%2d",&c[pos].dn.dia);
        printf("\n\tMES: \n\t");
        scanf("%2d",&c[pos].dn.mes);
        printf("\n\tANO: \n\t");
        scanf("%2d",&c[pos].dn.ano);
        system("cls");
        do{
            printf("\n\tRG: ");
            gets(c[pos].rg);
            while (c[pos].rg[i])
            {
                if(isalpha(c[pos].rg[i]) || ispunct(c[pos].rg[i]))
                {
                    a++;
                }
                i++;
            }
            if (a>0)
            {
                system("cls");
                printf("\n\tERROR 98");
            }
            else{
                system("cls");
            }
        }while(a>0)
        printf("\n\tCPF: \n\t");
        gets(c[pos].cpf);
        printf("\n\tENDERECO: \n\t");
        gets(c[pos].end);
        printf("\n\tCIDADE: \n\t");
        gets(c[pos].cid);
        printf("\n\tUF: \n\t");
        gets(c[pos].uf);
        *q++;
    }else
    {
        printf("\n\tMAXIMO DE INCLUSAO ATINGIDO");
    }

}


void flush_in (){
    int ch;

    while ((ch=fgetc(stdin)) != eof && ch != '\n') {

    }
}

//--------------------------------------------------------------
//OBJETIVO:	OBTEM UMA POSICAO VAZIA NO CADASTRO
	//		PARA A INCLUSAO DE UM CLIENTE
	//RETORNO: 	VALOR>0 PARA O SUCESSO DE INCLUSAO
	//		OU VALOR = 0 PARA INSUCESSO DE INCLUSAO
//--------------------------------------------------------------
int obtem_posicao_inculsao ()
{
    int i;

    for(i=0;i<10;i++)
    {
        if (c[i].ativo==2)
        {
            return(i);
        }
    }
    return 0;
}

//--------------------------------------------------------------
//OBJETIVO: 	CARREGA AS INFORMACOES DE UM CLIENTE
	//		EM CADA TEMPO DO REGISTRO
	//PARAMETRO:	c REPRESENTA O REGISTRO DO CLIENTE
//--------------------------------------------------------------
void le_cliente (vcliente *c;)
{

}

//--------------------------------------------------------------
//OBJETIVO: 	LISTAR OS CLIENTES CADASTRADOS
	//PARAMETROS: 	c REPRESENTA O CONJUNTO DE REGISTROS
	//		DE CLIENTES
//--------------------------------------------------------------
void lista_clientes_cadastrados (vcliente c;)
{

}

//--------------------------------------------------------------
//OBJETIVO: 	APRESENTAR OS CAMPOS DE UM REGISTRO CCLIENTE
	//PARAMETROS: 	c REPRESENTA O REGISTRO DO CLIENTE
//                  q REPRESENTA O TOTAL DE CADASTROS
//--------------------------------------------------------------
void mostra_cliente (vcliente c; int q;)
{
    int i;

    for (i=0;i<q;i++)
    {
        printf("CODIGO\t")
    }
}

//--------------------------------------------------------------
//OBJETIVO: 	RETIRA UM CLIENTE DO CADASTRO A PARTIR DO
	//		CODIGO DO CLIENTE FORNECIDO
	//PARAMETROS: c REPRESENTA O CONJUNTO DE REGISTRO DE CLIENTES
//--------------------------------------------------------------
void remove_cliente (vcliente c;)
{

}

//-------------------------------------------------------------------------
//OBJETIVO: 	LOCALIZA NO CADASTRO O CLIENTE QUE DESEJA REMOVER
	//PARAMETROS: 	c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES
	//		QUE SERA PESQUISADO E cod REPRESENTA O CODIGO DO
	//		CLIENTE A SER PESQUISADO
	//RETORNO: 	A POSICAO DO CLIENTE NO CADASTRO QUE SERA REMOVIDO, SE
	//		VALOR <> 0 EXISTE, OU SE VALOR = 0 NAO EXISTE NO CADASTRO
//-------------------------------------------------------------------------
int pesquisa_cliente (vcliente c; int codigo;)
{

}

//-----------------------------------------------------------------------------
//OBJETIVO:	VERIFICAR SE UM CODIGO DE CLIENTE EXISTE NO CADASTRO
	//PARAMETROS:	c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES QUE
	//		SERA PESQUISADO E cod REPRESENTA O CODIGO DO CLIENTE
	//		A SER PESQUISADO
	//RETORNO: 1 EXISTE OU 0 NAO EXISTE
//-----------------------------------------------------------------------------
int existe_codigo (vcliente c; int codigo;)
{

}

//-----------------------------------------------------------------------------
//OBJETIVO: 	LOCAR FITAS A UM CLIENTE
	//PARAMETROS: 	c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES
//-----------------------------------------------------------------------------
void loca_fitas_clientes (vcliente *c;)
{

}

//-----------------------------------------------------------------------------
//OBJETIVO: 	PESQUISA SE UM CLIENTE TEM FITAS LOCADAS
	//PARAMETROS: 	c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES
	//		A SER codigo REPRESENTA O CLIENTE
	//		QUE SERA PESQUISADO
	//RETORNO: 1 EXISTE FITA LOCADA; 0 NAO EXISTE FITA LOCADA
//-----------------------------------------------------------------------------
int existe_fita_locada_cliente (vcliente c; int codigo;)
{

}

//-----------------------------------------------------------------------------
//OBJETIVO: DEVOLVER FITAS DE UM CLIENTE
	//PARAMETROS: c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES
//-----------------------------------------------------------------------------
void devolve_fitas (vcliente c;)
{

}

//-----------------------------------------------------------------------------
//OBJETIVO: LISTAR OS CLIENTES COM FITAS LOCADAS
	//PARAMETROS: c REPRESENTA O CONJUNTO DE REGISTROS DE CLIENTES
//-----------------------------------------------------------------------------
void lista_clientes_locadas (vcliente c;)
{

}

int main()
{
    vcliente cliente;//contem os dados dos clientes
    int quantidade_clientes=0;
    int opcao;//obtem a opcao do usuario no menu


    return 0;
}
