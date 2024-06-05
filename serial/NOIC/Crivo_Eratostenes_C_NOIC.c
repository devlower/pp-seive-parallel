#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxn 30000000 // Substitua 1000 pelo tamanho desejado

int eh_primo[maxn]; // -1 => indefinido, 0 => composto e 1 => primo.

void crivo(int n) {
    int n_exec = 0;
    clock_t start_time, end_time;

    start_time = clock(); // Captura o tempo inicial

    // Inicializando "eh_primo" com -1, pois não sabemos nada sobre nenhum número, inicialmente.
    for (int i = 1; i <= n; i++) {
        eh_primo[i] = -1;
        n_exec++;
    }

    // Para cada número de 2 até n
    for (int i = 2; i <= n; i++) {
        n_exec++;

        // checo se o número atual é indefinido.
        if (eh_primo[i] == -1) {

            // Se ele for, indico que ele é primo
            eh_primo[i] = 1;
            printf("%d eh primo\n", i); // Exibe o número encontrado

            // e que os múltiplos dele são compostos.
            for (int j = i + i; j <= n; j += i) {
                eh_primo[j] = 0;
                n_exec++;
            }
        }
    }

    end_time = clock(); // Captura o tempo final
    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0; // Calcula o tempo total em milissegundos
    printf("n-exec: %d\n", n_exec); // Exibe o número de instruções executadas
    printf("Tempo de execucao: %.2f ms\n", total_time); // Exibe o tempo total de execução
}

int main() {
    crivo(maxn);

    printf("Pressione Enter para fechar o programa...");
    getchar(); // Aguarda uma tecla antes de fechar o programa

    return 0;
}