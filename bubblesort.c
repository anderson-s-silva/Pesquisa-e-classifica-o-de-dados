#include <stdio.h>
#include <stdlib.h>

int bubblesort(int *vetor, int tamanho){
  int i, continua, aux, fim = tamanho;
  do{
    continua = 0;
    for(int i = 0; i < fim - 1; i++){
      if(vetor[i] > vetor[i + 1]){ //Verifica o elemento adjacente para ordenar;
        aux = vetor[i]; //Auxiliar recebe o elemento que precisa ser ordenado;
        vetor[i] = vetor[i + 1]; // O elemento de menor indice recebe o menor valor;
        vetor[i + 1] = aux; // O elemento de maior indice recebe o maior valor;
        continua = i; // muda o valor de continue porque houve uma mudança;
      }
    }
    fim--;//reduz o fim conforme o laço ocorre;
  }while (continua != 0);
}

int *printarvetor(int *vetor, int tamanho){
  for(int i = 0; i < tamanho; i++){
    printf("[%d] ", vetor[i]);
  }
}

int main(int argc, char const *argv[]) {
  int *vetor = NULL;
  int tamanho;
  printf("Insira o tamnho do vetor\n");
  scanf("%d", &tamanho);
  vetor = (int*)malloc(tamanho * sizeof(int));
  for(int i = 0; i < tamanho; i++){
    printf("Insira o valor [%i] no vetor\n", i);
    scanf("%d", &vetor[i]);
  }
  bubblesort(vetor, tamanho);
  printarvetor(vetor, tamanho);

  return 0;
}
