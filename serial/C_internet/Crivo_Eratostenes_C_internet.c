// Algoritmo adaptado do obtido na internet no site https://blog.tiagomadeira.com/2007/06/crivo-de-eratostenes/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#define NMAX 30000000

int main() {
    clock_t start, end;
    start = clock();

    int i, j, qtd_instrucoes = 0;
    unsigned long valorMaximo, raiz;

    valorMaximo = 30000000;

    // Aloca o vetor dinamicamente para evitar problemas de estouro de pilha
    int *vetor = malloc((NMAX + 1) * sizeof(int));

    // Verifica se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Segundo passo
    raiz = sqrt(valorMaximo);

    // Terceiro passo
    for (i = 2; i <= valorMaximo; i++) {
        vetor[i] = i;
        qtd_instrucoes++;
    }

    // Quarto passo
    for (i = 2; i <= raiz; i++) {
        qtd_instrucoes++;
        if (vetor[i] == i) {
            for (j = i + i; j <= valorMaximo; j += i) {
                qtd_instrucoes++;
                vetor[j] = 0; // removendo da lista
            }
        }
    }

    //Percorre o vetor, exibindo os números diferentes de zero que sobraram, ou seja, os primos
    for (i = 2; i <= valorMaximo; i++) {
        qtd_instrucoes++;
        if (vetor[i] == i) {
            printf("%d Eh primo!\n", i);
        }
    }

    printf("Quantidade de instrucoes realizadas: %d\n", qtd_instrucoes);

    // Obtém o valor do tempo atual
    end = clock();

    // Calcula o tempo de execução em milissegundos
    long thicks = (end - start) * 1000 / CLOCKS_PER_SEC;

    // Imprime o tempo de execução
    printf("\nO tempo de execução em milissegundos eh: %lu\n", thicks);

    // Libera a memória alocada
    free(vetor);

    printf("Pressione Enter para fechar o programa...\n");
    getchar(); // Aguarda uma tecla antes de fechar o programa

    return 0;
}