/**
* @file organizacao-dados.c
* @author Anderson Soares da Silva and Mariana Goncalves Rodrigues
* @date 09 Abr 2021
* @brief  organizacao dos dados de um arquivo txt que possui rrn, nome, rua,
cidade e estado utilizando delimitadores ou indicadores de tamanho
*/

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

  //declaracao de variaveis de tipo arquivo
  FILE *entrada = NULL;
  FILE *saida = NULL;
  //declaracao de variaveis de tipo char
  char barra_n[1];
  char delimitador[1] = "|";
  //declaracao da variavel auxiliar do tipo cadastro
  cadastro aux;
  //contador para remover espacos nao utilizados na string
  int contador = 0;
  //abertura de arquivos de entrada e saida
  entrada = fopen("cadastro.txt", "r");
  saida = fopen("out.txt", "w");

  do{
    ///////////////       RRN     //////////////////////////
    //rrn nao necessita de remocao dos espacos
    fprintf(saida, "%s", delimitador);//gravacao do delimitador
    fgets(aux.rrn, sizeof(aux.rrn), entrada);
    contador = strlen(aux.rrn);
    fprintf(saida, "%d", contador);//gravacao do indicador de tamanho
    fwrite(aux.rrn, sizeof(char), 3, saida);
    //fim da gravacao do rrn

    ////////////////       NOME     //////////////////////////
    fprintf(saida, "%s", delimitador);//gravacao do delimitador
    fgets(aux.nome, sizeof(aux.nome), entrada);
    for(int i = 0; i<strlen(aux.nome); i++){//Remocao dos espaços da string
      if((aux.nome[i] == ' ' && aux.nome[i+1] == ' ')  || (i == strlen(aux.nome) - 1) || (i == strlen(aux.nome))){
        contador = i;
        break;
      }
    }//fim remocao espacos da string nome
    fprintf(saida, "%d", contador);//gravacao do indicador de tamanho
    fwrite(aux.nome, sizeof(char),contador, saida);
    //fim da gravacao dos nomes

    ////////////////       RUA     //////////////////////////
    fprintf(saida, "%s", delimitador);//gravacao do delimitador
    fgets(aux.rua, sizeof(aux.rua), entrada);
    for(int i = 0; i<strlen(aux.rua); i++){//Remocao dos espaços da string
      if((aux.rua[i] == ' ' && aux.rua[i+1] == ' ') || (i == strlen(aux.rua) - 1) || (i == strlen(aux.rua))){
        contador = i;
        break;
      }
    }//fim remocao espacos da string rua
    fprintf(saida, "%d", contador);//gravacao do indicador de tamanho
    fwrite(aux.rua, sizeof(char), contador, saida);
    //fim da gravacao das ruas

    ////////////////       CIDADE     //////////////////////////
    fprintf(saida, "%s", delimitador);//gravacao do delimitador
    fgets(aux.cidade, sizeof(aux.cidade), entrada);
    for(int i = 0; i<strlen(aux.cidade); i++){//Remocao dos espaços da string
      if((aux.cidade[i] == ' ' && aux.cidade[i+1] == ' ')  || (i == strlen(aux.cidade) - 1) || (i == strlen(aux.cidade))){
        contador = i;
        break;
      }
    }//fim remocao espacos da string cidade
    fprintf(saida, "%d", contador);//gravacao do indicador de tamanho
    fwrite(aux.cidade, sizeof(char), contador, saida);
    //fim da gravacao das cidades

    ////////////////       ESTADO     //////////////////////////
    //estado nao necessita da remocao dos espacos
    fprintf(saida, "%s", delimitador);//gravacao do delimitador
    fgets(aux.estado, sizeof(aux.estado), entrada);
    aux.estado[strcspn(aux.estado, "\n")]='\0';
    contador = strlen(aux.estado);
    fprintf(saida, "%d", contador);//gravacao do indicador de tamanho
    fwrite(aux.estado, sizeof(char), strlen(aux.estado), saida);
    //fim da gravacao dos estados
  }while(!feof(entrada));

  return 0;
}
