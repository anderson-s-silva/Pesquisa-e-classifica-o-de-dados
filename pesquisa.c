#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
  char rrn[4];
  char nome[26];
  char rua[26];
  char cidade[21];
  char estado[4];
}cadastro;



int main(int argc, char const *argv[]) {
  setlocale(LC_ALL,"");
  FILE *entrada = NULL;
  FILE *saida = NULL;
  char barra_n[1];
  char delimitador[1] = "|";

  cadastro aux;

  int contador = 0;

  entrada = fopen("cadastro.txt", "r");
  saida = fopen("saida.txt", "w");
  do{
    fprintf(saida, "%s", delimitador);
    fgets(aux.rrn, sizeof(aux.rrn), entrada);
    fwrite(aux.rrn, sizeof(char), 3, saida);

    fprintf(saida, "%s", delimitador);
    fgets(aux.nome, sizeof(aux.nome), entrada);
    for(int i = 0; i<strlen(aux.nome); i++){
      if((aux.nome[i] == ' ' && aux.nome[i+1] == ' ')  || (i == strlen(aux.nome) - 1) || (i == strlen(aux.nome))){
        contador = i;
        break;
      }
    }
    fwrite(aux.nome, sizeof(char),contador, saida);

    fprintf(saida, "%s", delimitador);
    fgets(aux.rua, sizeof(aux.rua), entrada);
    for(int i = 0; i<strlen(aux.rua); i++){
      if((aux.rua[i] == ' ' && aux.rua[i+1] == ' ') || (i == strlen(aux.rua) - 1) || (i == strlen(aux.rua))){
        contador = i;
        break;
      }
    }
    
    fwrite(aux.rua, sizeof(char), contador, saida);
    fprintf(saida, "%s", delimitador);
    fgets(aux.cidade, sizeof(aux.cidade), entrada);
    for(int i = 0; i<strlen(aux.cidade); i++){
      if((aux.cidade[i] == ' ' && aux.cidade[i+1] == ' ')  || (i == strlen(aux.cidade) - 1) || (i == strlen(aux.cidade))){
        contador = i;
        break;
      }
    }
    fwrite(aux.cidade, sizeof(char), contador, saida);

    fprintf(saida, "%s", delimitador);
    fgets(aux.estado, sizeof(aux.estado), entrada);
    fwrite(aux.estado, sizeof(char), strlen(aux.estado), saida);

    fgets(barra_n, sizeof(barra_n), entrada);
    barra_n[strcspn(barra_n,"\n")]='\0';
    fwrite(barra_n, 0, strlen(barra_n), saida);

  }while(!feof(entrada));

  return 0;
}
