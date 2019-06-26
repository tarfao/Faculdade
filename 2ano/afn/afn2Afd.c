//TRABALHO
//ENTRADA: Um AFN
//SAIDA : Um AFD
//Data: Depois do Recesso


//fechamento-E
void E(char *T,int tamanhoT,char *ET)
{  char pilha[20],t;
   int tamPilha,tamanho_u,i;

  for(i=0;i<tamanhoT;i++){
      ET[i]=T[i];
      pilha[i]=T[i];}

  tamanhoE =tamanhoT;
  tamPilha=tamanhoT;
  while(tamPilha){bb
      t=pilha[--tamPilha];//desempilha
      u=mov(t,'&'); //matrizDelta[linha(t)][coluna('&')]
      tamanho_u=calcTamanho(u); //calcula o numero de estados em u
      for(i=0;i<tamanho_u;i++) //para u[i] de u
         if(!pertence(u[i],ET,tamanhoT)){
            ET[tamanhoE++]=u[i]; //adiciona u em ET
            pilha[tamPilha++]=u[i];}} //empilha u na pilha

}



void ConstrSub() //o resultado é EstadosD
{
    char *estados;
    E(q0,1,EstadosD[0]); //EstadosD[0]=E(q0)
    Marca[0]=false;
    nEstadosD=1;
    posLida=0;
    while(!Marca[posLida]){
       Marca[posLida]=true;
       for(i=0;i<numAlfabeto;i++){ //não entra o '&'
          s=mov(EstadosD[posLida],Alfabeto[i]);
          tamanho_s=calcTamanho(s);
          E(s,tamanho_s,estados);
          if(!Pertence(estados,EstadoD)){
             EstadosD[nEstadosD++]=estados;
             Marca[nEstados-1]=false;}}
       posLida++;}
}
