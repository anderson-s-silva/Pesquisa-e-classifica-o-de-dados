/**
* @file cadastro.c
* @author Mariana Goncalves Rodrigues, Anderson Soares da Silva
* @r.a: 2151014 e 2150875
* @date 21 Abr 2021
* @brief  Cadastro Indexado Sr. Apolonio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int id;
  char nome[26];
  char rua[26];
  char cidade[21];
  char estado[3];
}arqdados;

typedef struct{
  int id;
  int rrn;
}indp;

typedef struct{
  char nome[26];
  int rrn;
}ind_sforte;

typedef struct{
  int id;
  char cidade[21];
}ind_sfraco;

int ordenaid(const void * a, const void * b){
  int r;
  if(a == b)
    r = 0;
  if(a > b)
    r = 1;
  if(a < b)
    r = -1;

  if(r == 0){
    return 0;
  }else{
    if(r<0){
      return -1;
    }else{
      return 1;
    }
  }
}

void conteudo(FILE* entrada, arqdados aux, indp* prim, ind_sforte *forte, ind_sfraco *fraco){

  int i=0;

  while(fscanf(entrada, "%3d %25[^\n] %25[^\n] %20[^\n] %2[^\n]", &aux.id, aux.nome, aux.rua, aux.cidade, aux.estado) != EOF){
    prim[i].id = aux.id;
    fraco[i].id = aux.id;
    strncpy(forte[i].nome, aux.nome, 26);
    strncpy(fraco[i].cidade, aux.cidade, 21);
    i++;
  }//end while
  qsort(prim->id, 500, sizeof(indp), ordenaid);//ordenacao do id no indice primario por quicksort
  qsort(fraco->id, 500, sizeof(ind_sfraco), ordenaid);//ordenacao do id no indice secundario por quicksort
  // for(int c = 0; c < 500; c++){
  //   printf("%d\n", prim[c].id);
  // }
}

void arqprimario(FILE* primario, indp* prim){
  for(int i = 0; i < 500; i++){
    fprintf(primario, "%03d\t%05d\n", prim[i].id, i*75);
  }
}

void arqforte(FILE* secundarioforte, ind_sforte *forte){
  for(int i = 0; i < 500; i++){
    fprintf(secundarioforte, "%s\t%05d\n", forte[i].nome, i*75);
  }
}

void arqfraco(FILE* secundariofraco, ind_sfraco *fraco){
  for(int i = 0; i < 500; i++){
    fprintf(secundariofraco, "%s\t%05d\n", fraco[i].cidade, fraco[i].id);
  }
}


int main(int argc, char const *argv[]) {

  FILE* entrada; //ponteiro para arquivo que vou usar como entrada
  FILE* primario; //ponteiro para arquivo do indice primario
  FILE* secundarioforte; //ponteiro para arquivo do indice secundario forte
  FILE* secundariofraco; //ponteiro para arquivo do indice secundario fraco

  arqdados aux;
  indp prim[500];
  ind_sfraco fraco[500];
  ind_sforte forte[500];

  entrada = fopen("cadastro.txt", "r");
  primario = fopen("primario.txt", "w");
  secundarioforte = fopen("secforte.txt", "w");
  secundariofraco = fopen("secfraco.txt", "w");

  if(entrada == NULL){
    printf("erro ao ler arquivo");
  }else{
    conteudo(entrada, aux, &prim, &forte, &fraco);
    arqprimario(primario, &prim);
    // cidadenome(entrada, primario, secundarioforte, secundariofraco, aux);
  }//else
  return 0;
}//main
