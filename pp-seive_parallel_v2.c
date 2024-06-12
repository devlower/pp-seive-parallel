#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int *list; /* The list of numbers to be processed by this process */
    int S = 0;  /* A near-as-possible even split of the count of numbers */
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
    S = N / p;
    R = N % p;
    L = r * S + 1;
    H = L + S - 1;
    if (r == p - 1) {
        H += R;
    }

    /* Allocate memory for lists */
    list = (int*)malloc((H - L + 1) * sizeof(int));

    /* Set each number as unmarked */
    for (c = L; c <= H; c++) {
        list[c - L] = 0;
        n_exec++;
    }

    /* Mark non-primes in list */
    for (c = 2; c <= sqrtN; c++) {
        if (c > sqrtN) continue;
        int start = (L % c == 0) ? L : L + (c - (L % c));
        if (start == c) start += c;
        for (m = start; m <= H; m += c) {
            list[m - L] = 1;
        }
    }

    if (r == 0) {
        /* Print primes found by process 0 */
        for (c = L; c <= H; c++) {
            if (list[c - L] == 0) {
                printf("%d ", c);
            }
            n_exec++;
        }
        /* Receive results from other processes and print */
        for (int src = 1; src < p; src++) {
            MPI_Recv(&L, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&H, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(list, H - L + 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (c = L; c <= H; c++) {
                if (list[c - L] == 0) {
                    printf("%d ", c);
                }
                n_exec++;
            }
        }
        printf("\n");
    } else {
        MPI_Send(&L, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&H, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(list, H - L + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(list);

    end_time = clock(); // Captura o tempo final
    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0; // Calcula o tempo total em milissegundos

    if (r == 0) {
        printf("n-exec: %d\n", n_exec); // Exibe o número de instruções executadas
        printf("Tempo de execucao: %.2f ms\n", total_time); // Exibe o tempo total de execução
    }

    MPI_Finalize();
    return 0;
}

// Compilar com: mpicc -o pp-seive_parallel.mpi pp-seive_parallel.c -lm
// Executar com: mpirun -np <num_procs> ./pp-seive_parallel.mpi <N>
