#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void primo(int *vetor,int indice_proximo_elemento_a_remover,int tamanho,int p, int k, int j,int prox){
 
  // Itera sobre o vetor
  for (int i = prox; i <= tamanho * sizeof(vetor)/sizeof(vetor[0]); i = i+sizeof(vetor)/sizeof(vetor[0])) {
    printf("\nvalor_vetor=%d",vetor[i]);
    // Verifica se o elemento atender à condição
    if (vetor[i] != p && vetor[i] % p != 0) {

      // Remove o elemento
      vetor[indice_proximo_elemento_a_remover] = vetor[i];
      indice_proximo_elemento_a_remover++;
    }
  }


  // Atualiza o tamanho do vetor
  int novo_tamanho_vetor = indice_proximo_elemento_a_remover;
 

  // Imprime o novo vetor
  for (int i = 0; i < novo_tamanho_vetor; i++) {
    printf("%d ", vetor[i]);
  }

    j=1;
    printf("\nj=%d",j);
    p = vetor[j];
    printf("  p=%d",p);
    prox++;
    printf("  prox=%d\n",prox);

    if(p<5)
  primo(vetor,indice_proximo_elemento_a_remover=0,novo_tamanho_vetor,p,k,j,prox);
 

    
}


int main()
{
    int n=100;
    int *vetor[n], k;
    // Declara uma variável para armazenar o índice do próximo elemento a ser removido
    int indice_proximo_elemento_a_remover = 0;
    int tamanho;
    int p=2;
    int j=0;
    int prox=0;

    for (int i = 0; i <= n; i++) {
        vetor[i] = i;
        printf("%d ",vetor[i]);
    }
    
    tamanho = sizeof(vetor) / sizeof(vetor[0]);
    printf("O tamanho do vetor eh: %d", tamanho);
   
  // Obtém a parte inteira da raiz quadrada do número de posiçôes do vetor
  k = floor(sqrt(n));
  printf("\nCondicao de parada (k)= %d ",k);

  //Chama a função
  primo(vetor,indice_proximo_elemento_a_remover,tamanho,p,k,j,prox);




}