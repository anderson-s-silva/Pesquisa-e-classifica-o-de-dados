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

typedef struct{
  char estado[3];
  char rua[26];
}complemento;

int ordenaid_indp(const void *a, const void *b){
  const indp *x = (const indp*)a;
  const indp *y = (const indp*)b;
  if ( x->id < y->id){
    return -1;
  }else if ( y->id < x->id){
    return 1;
  }else{
    if ( x->id < y->id ){
      return 1;
    }else if ( y->id < x->id){
      return -1;
    }else{
      return 0;
    }
  }
}

int ordenaid_indsfraco(const void * a, const void * b){
  const ind_sfraco *x = (const ind_sfraco*)a;
  const ind_sfraco *y = (const ind_sfraco*)b;
  if ( x->id < y->id ){
    return -1;
  }else if ( y->id < x->id ){
    return 1;
  }else{
    if ( x->id < y-> id ){
      return 1;
    }else if ( y->id < x->id ){
      return -1;
    }else{
      return 0;
    }
  }
}

void conteudo(FILE* entrada, arqdados aux, indp* prim, ind_sforte *forte, ind_sfraco *fraco, complemento *comp){
  int i=0;
  while(fscanf(entrada, "%3d %25[^\n] %25[^\n] %20[^\n] %2[^\n]", &aux.id, aux.nome, aux.rua, aux.cidade, aux.estado) != EOF){
    prim[i].id = aux.id;
    fraco[i].id = aux.id;
    strncpy(forte[i].nome, aux.nome, 26);
    strncpy(comp[i].rua, aux.rua, 26);
    strncpy(fraco[i].cidade, aux.cidade, 21);
    strncpy(comp[i].estado, aux.estado, 3);
    i++;
  }//end while

  /* Ordenacao com problemas
  qsort(prim, 500, sizeof(int), ordenaid_indp);//ordenacao do id no indice primario por quicksort
  qsort(fraco, 500, sizeof(int), ordenaid_indsfraco);//ordenacao do id no indice secundario por quicksort
  for(int c = 0; c < 500; c++){
    printf("%d\n", prim[c].id);
  }
  printf("\n\n\n");
  for(int c = 0; c < 500; c++){
    printf("%d\n", fraco[c].id);
  }
  */
}

void listarTodosAmigos(indp* prim, ind_sforte* forte, ind_sfraco* fraco, complemento* comp){
  for(int i = 0; i<500; i++){
    printf("%03d %s %s %s %s \n", prim[i].id, forte[i].nome, comp[i].rua, fraco[i].cidade, comp[i].estado);
  }
}

void arqprimario(FILE* primario, indp* prim){
  for(int i = 0; i < 500; i++){
    prim[i].rrn = i;
    fprintf(primario, "%03d\t%05d\n", prim[i].id, prim[i].rrn);
  }
}

void arqforte(FILE* secundarioforte, ind_sforte *forte){
  for(int i = 0; i < 500; i++){
    forte[i].rrn = i;
    fprintf(secundarioforte, "%s\t%05d\n", forte[i].nome, forte[i].rrn);
  }
}

void arqfraco(FILE* secundariofraco, ind_sfraco *fraco){
  for(int i = 0; i < 500; i++){
    fprintf(secundariofraco, "%s\t%03d\n", fraco[i].cidade, fraco[i].id);
  }
}

void pesquisaNome(FILE* entrada, FILE* secundarioforte, ind_sforte *forte){
  int byteoffset;
  int aux = 0;
  char nome[26];
  arqdados temp;
  int contador=0;
  char name[contador];

  printf("Insira um nome para realizar a busca\n");
  fgets(nome, 26, stdin);
  setbuf(stdin, NULL);
  nome[strcspn(nome,"\n")]='\0';

  for(int i = 0; i<500;i++){
    for(int j = 0; j<strlen(forte[i].nome); j++){//remover espacos desnecessarios
      if((forte[i].nome[j] == ' ' && forte[i].nome[j+1] == ' ')  || (j == strlen(forte[i].nome) - 1) || (j == strlen(forte[i].nome))){
        contador = j;
        break;
      }
    }
    if(memcmp(forte[i].nome, nome, contador) == 0){
      aux = 1;
      byteoffset = forte[i].rrn * 77;
    }
  }
  if(aux == 0){
    printf("Nome nao encontrado");
  }else{
    printf("\n%d\n", byteoffset);
    fseek(entrada, byteoffset, SEEK_SET);
    fscanf(entrada, "%03d %25[^\n] %25[^\n] %20[^\n] %2[^\n]", &temp.id, temp.nome, temp.rua, temp.cidade, temp.estado);
    printf("%03d %s %s %s %s\n", temp.id, temp.nome, temp.rua, temp.cidade, temp.estado);
  }
}

void pesquisaCidade(FILE* entrada, FILE* secundariofraco, ind_sfraco *fraco){

  char cidade[26];
  int aux = 0;
  int contador = 0;
  int byteoffset;
  int cont=0;
  arqdados temp[cont];

  printf("Insira um cidade para realizar a busca\n");
  fgets(cidade, 26, stdin);
  setbuf(stdin, NULL);
  cidade[strcspn(cidade,"\n")]='\0';

  for(int i = 0; i < 500; i++){
    for(int j = 0; j<strlen(fraco[i].cidade); j++){//remover espacos desnecessarios
      if((fraco[i].cidade[j] == ' ' && fraco[i].cidade[j+1] == ' ')  || (j == strlen(fraco[i].cidade) - 1) || (j == strlen(fraco[i].cidade))){
        contador = j;
        break;
      }
    }
    if(memcmp(fraco[i].cidade, cidade, contador) == 0){
      aux = 1;
      byteoffset = i * 77;
      fseek(entrada, byteoffset, SEEK_SET);
      fscanf(entrada, "%3d %25[^\n] %25[^\n] %20[^\n] %2[^\n]", &temp[i].id, temp[i].nome, temp[i].rua, temp[i].cidade, temp[i].estado);
      printf("\n%03d %s %s %s %s\n", temp[i].id, temp[i].nome, temp[i].rua, temp[i].cidade, temp[i].estado);
    }
  }
  if(aux == 0){
    printf("A cidade nao foi encontrada!\n");
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
  complemento comp[500];
  int menu;

  entrada = fopen("cadastro.txt", "r");
  primario = fopen("primario.txt", "w");
  secundarioforte = fopen("secforte.txt", "w");
  secundariofraco = fopen("secfraco.txt", "w");

  if(entrada == NULL){
    printf("erro ao ler arquivo");
  }else{
    conteudo(entrada, aux, prim, forte, fraco, comp);
    arqprimario(primario, prim);
    arqforte(secundarioforte, forte);
    arqfraco(secundariofraco, fraco);
  }//else

  printf("=======Amigos do Sr Polonio=======\n1-Listar todos os dados dos amigos\n2-Pesquisar por nome\n3-Pesquisar por cidade\n4-Sair do programa\nDigite uma opcao:\n");

  do{
    do{
      scanf("%d", &menu);
      setbuf(stdin, NULL);
    }while((menu > 4) || (menu < 1));

    switch (menu) {
      case 1:
      printf("A opcao escolhida foi: 'Listar todos os dados dos amigos'\n");
      listarTodosAmigos(prim, forte, fraco, comp);
      break;
      case 2:
      printf("A opcao escolhida foi: 'Pesquisar por nome'\n");
      pesquisaNome(entrada, secundarioforte, forte);
      //Acessar o arq secundario forte e identificar o byteoffset relacionado a aquele nome,
      //então fazer um seek no arq de dados com o byteoffset encontrado e printar os dados
      //daquela linha
      break;
      case 3:
      printf("A opcao escolhida foi: 'Pesquisar por cidade'\n");
      pesquisaCidade(entrada, secundariofraco, fraco);
      //Acessar o arq secundario fraco e buscar o id relacionado a cidade, acessar o arq
      //primario e buscar o byteoffset daquele id, fazer seek no arq de dados com o byteoffset
      //encontrado e printar os dados daquela linha
      break;
    }
  }while(menu != 4);
  return 0;
}
