
int main(int argc, char *argv[])
{
  // declara e inicializa um array de strings
  // veja que definimos o limite de 99 caracteres
  // por string (uma posição é para o caractere
  // de fim de linha)
  char nomes[][100] = {"Osmar J. Silva", "Carlos de Souza",
    "Fernanda Reis", "Joaquim Alves"};

  // vamos exibir os nomes
  int i;
  for(i = 0; i < 4; i++){
    printf("%s\n", nomes[i]);
  }

  system("PAUSE");
  return 0;
}
