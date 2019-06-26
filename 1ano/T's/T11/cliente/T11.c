#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define TAM 50


struct ENDERECO {
 char rua[TAM];
 int numero;
 char bairro[TAM];
 char cidade[TAM];
 char estado[3];
 char cep[11]; //99.999-999
};

struct TELEFONE {
 char telefone[14]; //99 99999-9999
};


 struct CLIENTE {
  char nome[TAM];
  char cpf[15]; //999.999.999-99
  struct ENDERECO endereco;
  struct TELEFONE residencial;
  struct TELEFONE celular [5];
  float renda_mensal;
};


struct DATA {
    int dia, mes, ano;
};

struct VENDA_CARRO {
    char placa_car[9];
    char cpf_cli[15];
    float preco_venda;
    struct DATA data_venda;
    char fabricante[TAM];
    char modelo[TAM];
    char nome[TAM];
    int ano_fabricacao;
};


void insere_pontuacao_cpf();
void mostra_cliente();

void nome_rua(struct CLIENTE  *d)
{
    char rua[][TAM]={{"Hayel Bon Faker "},{"Avenida Brasil"},{"Joaquim Texeira Alves "},{"Marcelino Pires  "},
    {"Presidente Vargas"},{"Joao Correia Neto "},{"Joao Vicente Ferreira"},{" Joao Damasceno Pires "},
    {"Joaquim Alves Taveira "},{"Joao Rosa Goes"},{"Santo Antonio "},{"Mandaguari "},{"Quinze"},
    {"Ipanema "},{"Cuiaba "},{"Bela Vista "},{"Cafelandia "}};

    int k,j;
    srand(time(NULL));
    k=rand()%17;

    strcpy(d->endereco.rua,rua[k]);
}


int obtem_primeiro_digito_verificador(char cpf[]) {

    int digito, result,i, somador=0,cpfi[9];

    for (i=0;i<9;i++)
    {
        cpfi[i] = cpf[i]-48;
    }

    for(i=0;i<9;i++)
    {
        somador =somador+(cpfi[i]*(10-i));
    }

    result=somador%11;

    if(result<2){
        digito=0 ;
    }
    else{
        digito = 11-result;
    }
    return(digito);
}


int obtem_segundo_digito_verificador(char cpf[]) {
   int digito, somador=0, i, result,cpfi[10];

    for (i=0;i<10;i++)
    {
        cpfi[i] = cpf[i]-48;
    }

    for(i=0;i<10;i++)
    {
        somador= somador + (cpfi[i]*(11-i));
    }

    result=somador%11;

    if(result<2){
        digito=0;
    }
    else{
        digito=11-result;
    }

   return(digito);
}


void gera_cpf_valido(struct CLIENTE *d)
{

    int j;
    char ncpf[15];
    char cpf2[15];
    //srand(time(NULL));
    for (j=0;j<9;j++){
        ncpf[j]=rand()%9+48;
    }
    ncpf[9] = obtem_primeiro_digito_verificador(ncpf)+48;
    ncpf[10] = obtem_segundo_digito_verificador(ncpf)+48;
    insere_pontuacao_cpf(ncpf,cpf2);
    strcpy(d->cpf,cpf2);
}


void insere_pontuacao_cep(char cep_origem[], char cep_destino[]) //99.999-999
{
    int i;
    int cont=0;//auxilia o cep_destino para pegar
                // as posicoes certas do cep pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do cep_origem muda

    for (i=10;i>-1;i--)
    {
        if (i==10)
        {
            cep_destino[i]='\0';
        }
        else{
            if (i!=2 && i!=6){
                if (cont==0){
                    cep_destino[i]=cep_origem[i-2];
                }
                else
                {
                    if(cont==1)
                    {
                        cep_destino[i]=cep_origem[i-1];
                    }
                    else{
                        if (cont==2)
                        {
                            cep_destino[i]=cep_origem[i];
                        }

                    }
                }
            }
            else
            {

                    if(i==6)
                    {
                        cep_destino[i]='-';
                        cont++;
                    }
                    if (i==2)
                    {
                        cep_destino[i]='.';
                        cont++;
                    }
            }
        }
    }
}


void gera_cep(struct CLIENTE *d)
{
    int j;
    char ncep[11];
    char cep2[11];
 //   srand(time(NULL));
    for (j=0;j<10;j++){
        ncep[j]=rand()%9+48;
    }
    insere_pontuacao_cep(ncep,cep2);
    strcpy(d->endereco.cep,cep2);
}



void insere_pontuacao_cpf(char cpf_origem[], char cpf_destino[])
{
    int i;
    int cont=0;//auxilia o cpf_destino para pegar
                // as posicoes certas do cpf pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do cpf_origem muda

    for (i=14;i>-1;i--)
    {
        if (i==14)
        {
            cpf_destino[i]='\0';
        }
        else{
            if (i!=3 && i!=7 && i!=11){
                if (cont==0){
                    cpf_destino[i]=cpf_origem[i-3];
                }
                else
                {
                    if(cont==1)
                    {
                        cpf_destino[i]=cpf_origem[i-2];
                    }
                    else{
                        if (cont==2)
                        {
                            cpf_destino[i]=cpf_origem[i-1];
                        }
                        else
                        {
                            if (cont==3)
                            {
                                cpf_destino[i]=cpf_origem[i];
                            }
                        }
                    }
                }
            }
            else
            {
                if (i==11)
                {
                    cpf_destino[i]='-';
                    cont++;
                }
                else
                {
                    if(i==7)
                    {
                        cpf_destino[i]='.';
                        cont++;
                    }
                }
                if (i==3)
                {
                    cpf_destino[i]='.';
                    cont++;
                }
            }
        }
    }
}



void insere_pontuacao_telefone(char n_origem[], char n_destino[]) //99 99999-9999
{
    int i;
    int cont=0;//auxilia o n_destino para pegar
                // as posicoes certas do numero de telefone pois
                // cada vez que inserimos um . ou -
                // a logica para pegar certo numero
                //do n_origem muda

    for (i=13;i>-1;i--)
    {
        if (i==13)
        {
            n_destino[i]='\0';
        }
        else{
            if (i!=2 && i!=8){
                if (cont==0){
                    n_destino[i]=n_origem[i-2];
                }
                else
                {
                    if(cont==1)
                    {
                        n_destino[i]=n_origem[i-1];
                    }
                    else{
                        if (cont==2)
                        {
                            n_destino[i]=n_origem[i];
                        }
                    }
                }
            }
            else
            {
                if (i==8)
                {
                    n_destino[i]='-';
                    cont++;
                }
                else
                {
                    if(i==2)
                    {
                        n_destino[i]=' ';
                        cont++;
                    }
                }
            }
        }
    }
}


void gera_tel_residencial(struct CLIENTE *d) {

    int j;
    char n1[15];
    char n2[15];
  //  srand(time(NULL));
    for (j=0;j<9;j++){
        n1[j]=rand()%9+48;
    }
    insere_pontuacao_telefone(n1,n2);
    strcpy(d->residencial.telefone,n2);
}



void gera_tel_celular(struct CLIENTE *d) {

    int j;
    char n1[14];
    char n2[14];
    //srand(time(NULL));
    for (j=0;j<9;j++){
        n1[j]=rand()%9+48;
    }
    insere_pontuacao_telefone(n1,n2);
    strcpy(d->celular[0].telefone,n2);
}


void nome_bairro(struct CLIENTE  *d )
{
    char bairro[][TAM]={{"Agua "},{"Boa "},{"Parque "},{"Alvorada "},{"Santo "},{"Andre "},{"Izidro "},{"Pedroso "}};
    int k,j;

   // srand(time(NULL));
    k=rand()%8;

    strcpy(d->endereco.bairro,bairro[k]);

     j=rand()%8;
    while(j==k)
    {
        j=rand()%8;
    }
    strcat(d->endereco.bairro,bairro[j]);
}


void numero_endereco(struct CLIENTE *d)
{
    int k;

    //srand(time(NULL));
    k=rand()%1000 + 1;

    d->endereco.numero=k;
}


void nome_cidade(struct CLIENTE  *d)
{
    char cidade[][TAM]={{"Dourados "},{"Maringa "},{"Curitiba "},{"Sao Paulo "},{"Rio de Janeiro "},{"Florianopolis "},
    {"Salvador "},{"Rondonopolis "},{"Sao Jose dos Campos "},{"Campo Grande "},{"Cuiaba "},{"Porto Alegre "},{"Recife "}};

     int k;
    //srand(time(NULL));
    k=rand()%13;

    strcpy(d->endereco.cidade,cidade[k]);
}



void n_estado(struct CLIENTE  *d)
{
    char estado[][TAM]={{"MS"},{"MT"},{"PR"},{"SP"},{"BA"},{"RJ"},{"PE"},{"SC"},{"RS"}};
    int k;

    //srand(time(NULL));
    k=rand()%9;

    strcpy(d->endereco.estado,estado[k]);

}


void nome_cliente( struct CLIENTE  *d)
{
    char nome[][TAM]={{"Maria "},{"Julia "},{"Ana "},{"Carla "},{"Karol "},{"Joao "},
    {"Carlos "},{"Fernando "},{"Jose "},{"Pedro "},{"Fernanda  "},{"Lorenzo "},{"Debora "},{"Junior "},{"Isabela "},{"Ronaldo "},
    {"Lucas "},{"Matheus "},{"Vitor "},{"Antonio "},{"Leonardo "},{"Franscismar "},{"Karen "},{"Thiago "},{"Iury "},
    {"Amanda "},{"Alicia "},{"Laura "},{"Thais "},{"Larissa "},{"Caio "},{"Clarice "},{"Clara "},{"Luis "}};

    char sobrenome[][TAM]={{"Alves "},{"Lispector "},{"Tafarel"},{"Bastos "},{"Santos "},{"Souza "},{"Rocha "},{"Lima "},
    {"Pereira "},{"Dourado "},{"Barbosa "},{"Dias "},{"Cardoso "},{"Castro "},{"Ransolin "},{"Mendes "},{"Costa "},{"Pires "},{"Neto "},
    {"Rodrigues "},{"Martins "}};
    int k;
    int j;

    srand(time(NULL));
    k=rand()%34;

    strcpy(d->nome,nome[k]);

     j=rand()%21;

    strcat(d->nome,sobrenome[j]);
}


void renda(struct CLIENTE *d)
{
    d->renda_mensal=5000 + rand()%(10000);

}



void cadastro(struct CLIENTE *d)
{
    nome_cliente(d);
    nome_rua(d);
    numero_endereco(d);
    nome_bairro(d);
    nome_cidade(d);
    n_estado(d);
    gera_cpf_valido(d);
    renda(d);
    gera_cep(d);
    gera_tel_residencial(d);
    gera_tel_celular(d);
}


//---------------------------------------------------------------------------
//OBJETIVO: VERIFICAR SE UM CLIENTE JÁ POSSUI UMA VENDA
//PARAMETRO: O REGISTRO DO CLIENTE
//RETORNO: 0 CASO ELE NÃO FEZ UMA VENDA, OU 1
//---------------------------------------------------------------------------
int verifica_cliente_venda (struct CLIENTE c)
{
    FILE *p;
    struct VENDA_CARRO s;

    if ((p=fopen("vendacarro.dat","rb")) == NULL)
    {
        return 0;
    }
    else
    {
        do
        {
            if (fread(&s,sizeof(struct VENDA_CARRO),1,p) == 1)
            {
                if (strcmp(s.cpf_cli,c.cpf)==0)
                {
                    return 1;
                }
            }
        }while(!feof(p));
    }
    return 0;
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: PASSAR TODOS OS ARQUIVOS PARA UM VETOR
//PARAMETRO: ARQUIVO DE CARROS E UM CONJUNTO DE REGISTROS
//RETORNO: A QUANTIDADE DE CARROS
//-----------------------------------------------------------------------------------------
int arq_pvetor_cliente (FILE *p, struct CLIENTE c[])
{
    int i=0;
    struct CLIENTE s;

    fseek(p,0,SEEK_SET);
    do{
        if(fread(&s,sizeof(struct CLIENTE),1,p)==1)
        {
            c[i] = s;
            i++;
        }
    }while(!feof(p));
    return (i);
}

//-----------------------------------------------------------------------------------------
//OBJETIVO: JOGAR O CARRO PARA ULTIMA POSICAO SEM ALTERAR A SEQUENCIA QUE JÁ SE TEM
//PARAMETRO: O CONJUNTO DE REGISTROS, A QUANTIDAD, E A POSICAO DO CARRO NO VETOR
//-----------------------------------------------------------------------------------------
void ultimo_carro_cliente (struct CLIENTE c[], int q, int pos)
{
    int i;
    struct CLIENTE aux;
    if (q==pos)
    {

    }
    else
    {
        for (i=pos; i < q-1; i++)
        {
            aux = c[i];
            c[i] = c[i+1];
            c[i+1] = aux;
        }
    }

}

//-----------------------------------------------------------------------------------------
//OBJETIVO: REGRAVAR OS REGISTROS NO ARQUIVO APÓS A EXCLUSAO
//PARAMETRO: ARQUIVO DE CARROS, O CONJUNTO DE CARROS E A QUANTIDADE
//-----------------------------------------------------------------------------------------
int pos_venda_cliente(FILE *p, struct CLIENTE c[], int q)
{
    int i;
    int cont=0;
    struct CLIENTE a;

    if ((p = fopen("Cliente.dat","w+b"))==NULL)
    {
        system("cls");
        printf("\n\tCLIENTES COM VENDAS! !\n\n");
        system("pause");
        //exit(102);

    }
    else{
        for (i=0;i<q;i++){
            a=c[i];
            if (fwrite(&a,sizeof(struct CLIENTE),1,p)==1)
            {
                cont++;
            }
        }
        fclose(p);
    }
    //printf("\n--> %d %d <--\n",i, q);
    //system("pause");
}

//----------------------------------------------------------------------
//OBJEITVO: EXCLUIR UM CLIENTE
//PARAMETRO: NENHUM
//----------------------------------------------------------------------
void exclui_cliente()
{
    struct CLIENTE c;
    FILE *p;
    FILE *s;
    int sort, tot;
    //FILE *p;
    struct CLIENTE conj[100];
    int ver;

    if((p=fopen("Cliente.dat","rb"))== NULL)
    {
        system("cls");
        printf("\tNÃO HÁ CLIENTES!\n\n");
    }
    else
    {

        //sorteia um numero do total de clientes existentes
        do{
            fseek(p,0,SEEK_END);
            tot = ftell(p)/sizeof(struct CLIENTE);
            sort = rand() % tot;
            fseek(p,sizeof(struct CLIENTE)*sort,SEEK_SET);
            if (fread(&c,sizeof(struct CLIENTE),1,p) == 1)
            {
                ver = verifica_cliente_venda(c);
            }
        }while(ver != 0);
        arq_pvetor_cliente(p,conj);
        ultimo_carro_cliente(conj,tot,sort);
        tot--;
        pos_venda_cliente(p,conj,tot);
        system("cls");
        printf("\tCLIENTE EXCLUÍDO\n");
        mostra_cliente(c);
        fclose(p);
    }

}

void mostra_cliente(struct CLIENTE d)
{
    printf("\nNOME : \t");
    puts(d.nome);
    printf("\nENDERECO : ");
    printf("%s - NUMERO :%d \n ",d.endereco.rua,d.endereco.numero);
    printf("\nBAIRRO : ");
    puts(d.endereco.bairro);
    printf("\nCIDADE : ");
    puts(d.endereco.cidade);
    printf("\nESTADO : ");
    puts(d.endereco.estado);
    printf("\nCPF : ");
    puts(d.cpf);
    printf("\nRENDA : %.2f ",d.renda_mensal);
    printf("\nCEP: ");
    puts(d.endereco.cep);
    printf("\nTELEFONE RESIDENCIAL : ");
    puts(d.residencial.telefone);
    printf("\nTELEFONE CELULAR : ");
    puts(d.celular[0].telefone);


}



void ordenar_nome(struct CLIENTE d[],int k)
{
    int i,j;
    char vet[30];
    struct CLIENTE t;
    for(i = 0; i < k ; i++)
    {
      for (j = 0;j <k-1; j++)
      {
            if(strcmp(d[j].nome,d[j+1].nome)>0)
            {
                //t = d[j];
                //d[j] = d[j+1];
                //d[j+1] = t;
                strcpy(vet,d[j].nome);
                strcpy(d[j].nome,d[j+1].nome);
                strcpy(d[j+1].nome,vet);

            }
        }
    }
}


void ordena_renda_e_nome(struct CLIENTE d[],int soma)
{
    int i,j,a;
    char vet[30];
    for(i = 0; i < soma; i++)
     {
        for(j = 0; j < soma-1; j++)
         {
          if(d[j].renda_mensal > d[j+1].renda_mensal)
           // if(strcmp(d[j].nome,d[j+1].nome)>0)
            {
               // if(d[j].renda_mensal > d[j+1].renda_mensal)
              //if(strcmp(d[j].nome,d[j+1].nome)>0)
                //{
                    strcpy(vet,d[j].nome);
                    strcpy(d[j].nome,d[j+1].nome);
                    strcpy(d[j+1].nome,vet);
                    a = d[j].renda_mensal;
                    d[j].renda_mensal = d[j+1].renda_mensal;
                    d[j+1].renda_mensal=a;
                //}
            }
         }
     }
     for(i=0;i<soma;i++)
     {
        printf("\n%s\t\t%f\t",d[i].nome, d[i].renda_mensal);

     }
}


void mostra_nome(struct CLIENTE d[],int k)
{
    int i;
     for(i=0;i<k;i++)
    {
      printf("%s\n",d[i].nome);
    }
}


int main()
{
    FILE *arq;
    int opc;
    int soma=0,soma2=0,i;
    system("color f9");
    struct CLIENTE dados;
    struct CLIENTE cad[30];
    struct CLIENTE cad2[30];

   while(opc!=5)
    {

        printf("\n\t <1>INCLUIR \n");
        printf("\n\t <2>EXCLUIR \n");
        printf("\n\t <3>LISTAR PELO NOME \n");
        printf("\n\t <4>LISTAR PELO NOME E RENDA \n");
        printf("\n\t <5>SAIR \n\t");
        scanf("%d",&opc);
        system("cls");
        if(opc==1)
        {
            if((arq=fopen("Cliente.dat ","r+b"))==NULL)
                {
                    if((arq=fopen("Cliente.dat ","w+b"))==NULL)
                    {
                        printf("\nERRO NA CRIACAO");
                        exit(1);
                    }
                }
             cadastro(&dados);
             fseek(arq,0,SEEK_END);
             if((fwrite(&dados,sizeof (struct CLIENTE),1,arq))==1)
             {
                printf("\nDADOS GRAVADOS COM SUCESSO...\n");
             }
             mostra_cliente(dados);
             system("pause");
             system("cls");
             fclose(arq);
        }
        if(opc==2)
        {
            //printf("\nExclui Cliente\n ");
            exclui_cliente();
        }
        if(opc==3)
        {
            soma = 0;
            arq=fopen("Cliente.dat","r+b");
            if(arq==NULL)
            {
                printf("\nERRO AO ABRIR O ARQUIVO...");
            }
            while(!feof(arq))
            {
               if((fread(&dados,sizeof(struct CLIENTE),1,arq))==1)
                {
                      cad[soma]=dados;
                      soma++;
                }
            }
            fclose(arq);
            ordenar_nome(cad,soma);
            mostra_nome(cad,soma);
        }
        if(opc==4)
        {
            soma2 = 0;
            arq=fopen("Cliente.dat","r+b");
            if(arq==NULL)
            {
                printf("\nERRO AO ABRIR O ARQUIVO...");
            }
            while(!feof(arq))
            {
               if((fread(&dados,sizeof(struct CLIENTE),1,arq))==1)
                {
                      cad2[soma2]=dados;
                      soma2++;
                }
            }
            fclose(arq);
            ordena_renda_e_nome(cad2,soma2);
        }
    }
    return 0;
}
