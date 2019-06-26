#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>



void imprime(int ordem, float A[10][10], float I[10])
{
    int i,j;       
    printf("\n-------------MATRIZ ALTERADA------------\n");
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            printf("\t%.2f",A[i][j]);
        }
        if(A[i][j-1]>=0)/*efeito de impressão*/
        	printf(" | %.2f\n",I[i]);		
        else
        	printf("| %.2f\n",I[i]);
    }
}

/*------------------------------------------------------------------------------
OBJETIVO: TROCAR LINHA DA MATRIZ
PARAMETRO: A LINHA QUE POSSUI O ANTIGO PIVO, E A LINHA QUE POSSUI O ATUAL
-------------------------------------------------------------------------------*/
void troca_linha(int ordem, int linha, int nova_linha,float m[10][10], float m2[10])
{
    int i;
    float aux;
    
    for(i=0;i<ordem;i++)
    {   
    	/*MOVE NA MATRIZ DOS COEFICIENTES*/
        aux = m[linha][i];
        /*printf("\nAUX -> %.2f",m[nova_linha][i]);*/
        m[linha][i] = m[nova_linha][i];
        m[nova_linha][i] = aux;
        /*if (linha==1){
            printf("\n");           
            imprime(ordem,m);
            printf("\n");
        }*/
    }
    /*MOVE NA MATRIZ DOS TERMOS INDEPENDETES*/
    aux = m2[linha];
    m2[linha] = m2[nova_linha];
    m2[nova_linha] = aux;
}
        
/*------------------------------------------------------------------------------
OBJETIVO: VERIFICAR SE O PIVO É O MAIOR DE TODOS DA COLUNA ABAIXO
PARAMETRO: A LINHA QUE O PIVO VAI ESTAR, A ORDEM DA MATRIZ E A MATRIZ
-------------------------------------------------------------------------------*/
void verifica_pivo(int linha, int ordem, float m[10][10], float m2[10])
{
    int i; 
    int auxLin = 0;
    float pivo=m[linha][linha];

    for(i=0;i<ordem;i++)
    {
        if(i>linha){
            if(m[i][linha] > pivo){
                pivo = m[i][linha];
                auxLin=i;
            }      
        }
    }
    if (auxLin!=0){
        troca_linha(ordem,linha,auxLin,m,m2);
    }
            
        
}

/*-------------------------------------------------------------------------------------------------------
OBJETIVO: FAZER OPERAÇÕES PARA OBTER O RESULTADO DE UM SISTEMA PELO MÉTODO DE GAUS PP
PARAMETRO: A ORDEM DA MATRIZ, A MATRIZ, A MATRIZ COLUNA DOS TERMOS INDEPENDETES E A MATRIZ RESPOSTA
------------------------------------------------------------------------------------------------------*/
void Gauss_PP (int ordem,float m[10][10],float r[10], float res[10])
{
    int i,j,k,q=ordem-1;/*variaveis auxiliares, e q, para obter a quantidade de operações na matriz*/    
    float mult;/*vai obter o multiplicador de cada linha*/

    for(i=0;i<q;i++)
    {
        verifica_pivo(i,ordem,m,r);/*faz a verificação do pivo*/
            
        for(j=i+1;j<ordem;j++)
        {               
            mult = ((-1)*m[j][i])/m[i][i];/*multiplicador de cada linha é obtido*/
            /*printf("\nP%d%d -  MULTIPLICADOR -> %.2f",i+1,i+1,mult);*/
            for(k=0;k<ordem;k++)
            {               
                m[j][k]= (mult * m[i][k])+ m[j][k];/*faz a operação elementar em cada linha*/
                    
            }
            r[j] = (mult*r[i])+r[j];/*faz a operação elementar também na matriz coluna dos termos independentes*/
        }       
            
    }
    /*inicialização da matriz coluna resposta*/    
    for (i=0;i<ordem;i++)
        res[i]=0;
}

/*---------------------------------------------------------------------------------------
OBJETIVO: TRANSFORMA A MATRIZ EM UMA MATRIZ DIAGONAL
PARAMETRO: A MATRIZ DOS COEFICIENTES - m
		   A MATRIZ DOS TERMOS INDEPENDENTES - m2
		   A ORDEM DA MATRIZ - ordem
----------------------------------------------------------------------------------------*/
void Jordan (int ordem, float m[10][10],float m2[10])
{
    int i,j,k;    
    float mult;

    if(ordem>1){
        for(i=0;i<ordem;i++)
        {
            if(m[i][i] == 0){
                /*printf("Entrou %f\n",m[i][i]);            */
                verifica_pivo(i,ordem,m,m2);
            }
            
            for(j=0;j<ordem;j++)
            {               
                mult = ((-1)*m[j][i])/m[i][i];
                
                for(k=0;k<ordem;k++)
                {
                    if(j!=i){               
                        m[j][k]= (mult * m[i][k])+ m[j][k];
                    }
                    
                }
                if(j!=i){
                	m2[j] = mult*m2[i]+m2[j];
                }
            }

            
        }
             
    }
}   

/*---------------------------------------------------------------------------------------
OBJETIVO: OBTEM O RESULTADO FINAL DO SISTEMA LINEAR QUANDO É FEITO PELO MÉTODO DE GAUSS
PARAMETRO: A MATRIZ DOS COEFICIENTES - m
		   A MATRIZ DOS TERMOS INDEPENDENTES - mi
		   A MATRIZ COLUNA DAS RESPOSTAS - r
		   A ORDEM DA MATRIZ - ordem
----------------------------------------------------------------------------------------*/
void obtem_resultado(float m[10][10], float mi[10], float r[10], int ordem)
{
	int i,j;
	float acum;/*acumula as multiplicacoes dos termos dependentes com as respostas obtidas*/
	float sub;/*subtrai a o temo idependente pelo o resultado da acumulação*/

	for(i=ordem-1;i>-1;i--)
	{
		acum = 0;
		for(j=ordem-1;j>i;j--)
		{
			acum = m[i][j]*r[j]+acum;
		}
		sub = mi[i]-acum;
		r[i]=sub/m[i][j];
	}
}

/*----------------------------------------------------------------------------------
OBJETIVO: PREENCHER A MATRIZ QUANDO SISTEMA
PARAMETRO: NENHUM
---------------------------------------------------------------------------------*/
void preenche(float A[10][10],float I[10], int *ordem)
{
	int i,j;

	printf ("\nORDEM DA MATRIZ DOS COEFICIENTES(MAIOR QUE 1): "); 
    do{
        scanf("%d",ordem);
    }while(*ordem<2 || *ordem>10);
    
    printf("\n----------PREENCHIMENTO DA MATRIZ DOS COEFICIENTES-------------\n");
    for(i=0;i<*ordem;i++)
    {
        for(j=0;j<*ordem;j++)
        {
            printf("a%d%d -> ",i+1,j+1);
            scanf("%f",&A[i][j]);
        }
    }
    printf("\n----------PREENCHIMENTO DA MATRIZ TERMOS INDEPENDENTES-------------\n");
    for(i=0;i<*ordem;i++)
    {
        printf("a1%d -> ",i+1);
        scanf("%f",&I[i]);
    }
}

/*----------------------------------------------------------------------------------
OBJETIVO: PREENCHER A MATRIZ
PARAMETRO: NENHUM
---------------------------------------------------------------------------------*/
void preenche2(float A[10][10], int *ordem)
{
	int i,j;

	printf ("\nORDEM DA MATRIZ: "); 
    do{
        scanf("%d",ordem);
    }while(*ordem<2 || *ordem>10);
    
    printf("\n----------PREENCHIMENTO DA MATRIZ--------------------\n");
    for(i=0;i<*ordem;i++)
    {
        for(j=0;j<*ordem;j++)
        {
            printf("a%d%d -> ",i+1,j+1);
            scanf("%f",&A[i][j]);
        }
    }
}

/*----------------------------------------------------------------------------------
OBJETIVO: OBTER O RESULTADO DO SISTEMA LINEAR
PARAMETRO: NENHUM
---------------------------------------------------------------------------------*/
void sis_liear()
{
	int i,j;//auxiliares para matriz
	int ordem;//ordem da matriz
	float A[10][10];/*matriz dos coeficientes*/
	float I[10];/*matriz coluna dos termos independentes*/
	float res[10];/*matriz coluna resposta*/
	char op;/*obtem o método que sera resolvido a matriz*/

	preenche(A,I,&ordem);
    printf("\n--------QUAL O MEDTODO QUE DESEJA UTILIZAR------------\n");
    do{
    	printf("1 - GAUSS\n");
    	printf("2 - JORDAN\n");
    	__fpurge(stdin);
    	scanf("%c",&op);
    }while(op!='1' && op!='2');

    if(op=='1')
    {
    	Gauss_PP(ordem,A,I,res);
    	imprime(ordem,A,I);
    	obtem_resultado(A,I,res,ordem);
    	printf("--------------RESULTADO----------------\n\t");
    	for(i=0;i<ordem;i++)
	    {	
    		printf("%.2f ",res[i]);
    	}

    }
    else
    {
    	Jordan(ordem,A,I);
    	imprime(ordem,A,I);
    	printf("---------------RESULTADO-----------------\n\t");
    	for(i=0;i<ordem;i++)
	    {	
    		printf("%.2f ",I[i]/A[i][i]);
    	}
    }
}

/*----------------------------------------------------------------------------------
OBJETIVO: OBTER O DETERMINANTE DE UMA MATRIZ
PARAMETRO: NENHUM
---------------------------------------------------------------------------------*/
void determ()
{
	int ordem;//ordem da matriz
	float A[10][10];/*matriz dos coeficientes*/
	float I[10];/*matriz coluna dos termos independentes*/
	float det=1;/*vai obter o determinante da matriz*/
	int i;/*Auxiliar*/

	preenche(A,I,&ordem);
	Jordan(ordem,A,I);

	for(i=0;i<ordem;i++)
	{
		det = det*A[i][i];
	}

	printf("\nO DETERMINANTE É IGUAL A %.2f\n",det);

}
/*---------------------------------------------------------------------------------------
OBJETIVO: TRANSFORMA A MATRIZ EM UMA MATRIZ DIAGONAL, E A IDENTIDADE VIRA A INVERSA
PARAMETRO: A MATRIZ DOS COEFICIENTES - m
		   A MATRIZ DOS TERMOS INDEPENDENTES - m2
		   A ORDEM DA MATRIZ - ordem
----------------------------------------------------------------------------------------*/
void Jordan_invers (int ordem, float m[10][10])
{
    int i,j,k;    
    float mult;
    float aux[10]={0,0,0,0,0,0,0,0,0,0};

    if(ordem>1){
        for(i=0;i<ordem;i++)
        {
            if(m[i][i] == 0){
                /*printf("Entrou %f\n",m[i][i]);            */
                verifica_pivo(i,ordem,m,aux);
            }
            
            for(j=0;j<ordem;j++)
            {               
                mult = ((-1)*m[j][i])/m[i][i];
                
                for(k=0;k<ordem+ordem;k++)
                {
                    if(j!=i){               
                        m[j][k]= (mult * m[i][k])+ m[j][k];
                    }
                    
                }
            }

            
        }
        /*como se transformou em uma matriz diagonal
        vamos dividir cada linha pelo unico termo != 0
        da linha da matriz*/
        for(i=0;i<ordem;i++)
        {

        	for(j=0;j<ordem+ordem;j++)     
        	{
        		m[i][j] = m[i][j]/m[i][i];
        	}
    	}
   	}
}   


/*---------------------------------------------------------------------------------------
OBJETIVO: AUMENTAR A MATRIZ COM A MATRIZ IDENTIDADE DE MESMA ORDEM
PARAMETRO: A MATRIZ - m
		   A ORDEM DA MATRIZ - ordem
----------------------------------------------------------------------------------------*/
void increase_A(float A[10][10], int ordem)
{
	int i,j;

	for(i=0;i<ordem;i++)
	{
		for(j=ordem;j<(2*ordem);j++)
		{
			if(j-i != ordem)/*verifica se a posicao coloca 0 ou 1 na matriz*/
				A[i][j] = 0;
			else
				A[i][j]=1;
		}
	}
}

/*---------------------------------------------------------------------------------------
OBJETIVO: OBTER UMA MATRIZ INVERSA
PARAMETRO: NENHUM
----------------------------------------------------------------------------------------*/
void matr_invers()
{
	int ordem;//ordem da matriz
	float A[10][10];/*matriz dos coeficientes*/
	float I[10];/*matriz coluna dos termos independentes*/
	int i,j;

	preenche2(A,&ordem);
	increase_A(A,ordem);
	Jordan_invers(ordem,A);
	for(i=0;i<ordem;i++)
	{
		printf("\n");
		for(j=0;j<ordem+ordem;j++)
		{
			printf("%.2f ",A[i][j] );
		}
	}

}

int main(){

    int i,j;
    char op;


    do{
    	printf("\n----------------MENU - RESOLUCAO COM MATRIZES----------------\n");
    	printf("1 - SISTEMA LINEAR\n");
    	printf("2 - DETERMINANTE\n");
    	printf("3 - MATRIZ INVERSA\n");
    	printf("4 - SAIR\n");
    	__fpurge(stdin);
    	scanf("%c",&op);
    	switch(op)
    	{
    		case '1':
    			sis_liear();
    		break;

    		case '2':
    			determ();
    		break;

    		case '3':
    			matr_invers();
    		break;
    	}
    }while(op!='4');
    return 0;
}
