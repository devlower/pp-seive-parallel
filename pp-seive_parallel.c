#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int *list1; /* The list of numbers <= sqrtN */
    int *list2; /* The list of numbers > sqrtN */
    int S = 0;  /* A near-as-possible even split of the count of numbers above sqrtN */
    int R = 0;  /* The remainder of the near-as-possible even split */
    int L = 0;  /* The lowest number in the current process’s split */
    int H = 0;  /* The highest number in the current process’s split */
    int r = 0;  /* The rank of the current process */
    int p = 0;  /* The total number of processes */
    int N, sqrtN; /* Total number and its square root */
    int c, m;   /* Loop counters */

    int n_exec = 0;
    clock_t start_time, end_time;

    start_time = clock(); // Captura o tempo inicial

    /* Initialize the MPI Environment */
    MPI_Init(&argc, &argv);

    /* Determine the rank of the current process and the number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    /* Assume N is provided as an argument */
    if (argc != 2) {
        if (r == 0) {
            printf("Usage: %s <N>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    N = atoi(argv[1]);
    sqrtN = (int)sqrt((double)N);

    /* Calculate S, R, L, and H */
    S = (N - (sqrtN + 1)) / p;
    R = (N - (sqrtN + 1)) % p;
    L = sqrtN + r * S + 1;
    H = L + S - 1;
    if (r == p - 1) {
        H += R;
    }

    /* Allocate memory for lists */
    list1 = (int*)malloc((sqrtN + 1) * sizeof(int));
    list2 = (int*)malloc((H - L + 1) * sizeof(int));

    /* Set each number as unmarked */
    for (c = 2; c <= sqrtN; c++) {
        list1[c] = 0;
        n_exec++;
    }
    for (c = L; c <= H; c++) {
        list2[c - L] = 0;
        n_exec++;
    }

    /* Mark non-primes in list1 */
    for (c = 2; c <= sqrtN; c++) {
        if (list1[c] == 0) {
            for (m = c + 1; m <= sqrtN; m++) {
                if (m % c == 0) {
                    list1[m] = 1;
                }
            }
            for (m = L; m <= H; m++) {
                if (m % c == 0) {
                    list2[m - L] = 1;
                }
            }
        }
    }

    if (r == 0) {
        for (c = 2; c <= sqrtN; c++) {
            if (list1[c] == 0) {
                printf("%d ", c);
            }
            n_exec++;
        }
        for (c = L; c <= H; c++) {
            if (list2[c - L] == 0) {
                printf("%d ", c);
            }
            n_exec++;
        }
        for (int src = 1; src < p; src++) {
            L = sqrtN + src * S + 1;
            H = L + S - 1;
            if (src == p - 1) {
                H += R;
            }
            MPI_Recv(list2, H - L + 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            n_exec++;
            for (c = L; c <= H; c++) {
                if (list2[c - L] == 0) {
                    printf("%d ", c);
                }
                n_exec++;
            }
        }
    } else {
        MPI_Send(list2, H - L + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(list2);
    free(list1);
    
    end_time = clock(); // Captura o tempo final
    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0; // Calcula o tempo total em milissegundos
    printf("n-exec: %d\n", n_exec); // Exibe o número de instruções executadas
    printf("Tempo de execucao: %.2f ms\n", total_time); // Exibe o tempo total de execução

    MPI_Finalize();
    return 0;
}

// Compilar com: mpicc -o pp-seive_parallel.mpi pp-seive_parallel.c -lm
// Executar com: mpirun -np <num_procs> ./pp-seive_parallel.mpi <N>
