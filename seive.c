int *list1; /* The list of numbers <= sqrtN -- if
list1[x] equals 1, then x is
marked. If list1[x] equals 0, then x is
unmarked. */
int *list2; /* The list of numbers > sqrtN – if
list2[x-L] equals 1, then x is marked.
If list2[x-L] equals 0, then x is
unmarked. */
int S = 0; /* A near-as-possible even split of the
count of numbers above sqrtN */
int R = 0; /* The remainder of the near-as-possible
even split */
int L = 0; /* The lowest number in the current
process’s split */
int H = 0; /* The highest number in the current
process’s split */
int r = 0; /* The rank of the current process */
int p = 0; /* The total number of processes */

/* Initialize the MPI Environment */
MPI_Init(&argc, &argv);

/* Determine the rank of the current process and
the number of processes */
MPI_Comm_rank(MPI_COMM_WORLD, &r);
MPI_Comm_size(MPI_COMM_WORLD, &p);

/* Calculate S, R, L, and H */
S = (N-(sqrtN+1)) / p;
R = (N-(sqrtN+1)) % p;
L = sqrtN + r*S + 1;
H = L+S-1;
if(r == p-1) {
H += R;
}

/* Allocate memory for lists */
list1 = (int*)malloc((sqrtN+1) * sizeof(int));
list2 = (int*)malloc((H-L+1) * sizeof(int));

/* Run through each number in list1 */
for(c = 2; c <= sqrtN; c++) {
/* Set each number as unmarked */
list1[c] = 0;
}
/* Run through each number in list2 */
for(c = L; c <= H; c++) {
/* Set each number as unmarked */
list2[c-L] = 0;
}

/* Run through each number in list1 */
for(c = 2; c <= sqrtN; c++) {
/* If the number is unmarked */
if(list1[c] == 0) {
/* Run through each number bigger than c in
list1 */
for(m = c+1; m <= sqrtN; m++) {
/* If m is a multiple of c */
if(m%c == 0) {
/* Mark m */
list1[m] = 1;
}
}
/* Run through each number bigger than c in
list2 */
for(m = L; m <= H; m++)
{
/* If m is a multiple of C */
if(m%c == 0)
{
/* Mark m */
list2[m-L] = 1;
}
}
}
}

/* If Rank 0 is the current process */
if(r == 0) {
/* Run through each of the numbers in list1 */
for(c = 2; c <= sqrtN; c++) {
/* If the number is unmarked */
if(list1[c] == 0) {
/* The number is prime, print it */
printf("%lu ", c);
}
}

/* Run through each of the numbers in list2 */
for(c = L; c <= H; c++) {
/* If the number is unmarked */
if(list2[c-L] == 0) {
/* The number is prime, print it */
printf("%lu ", c);
}
}

/* Run through each of the other processes */
for(r = 1; r <= p-1; r++) {
/* Calculate L and H for r */
L = sqrtN + r*S + 1;
H = L+S-1;
if(r == p-1) {
H += R;
}
/* Receive list2 from the process */
MPI_Recv(list2, H-L+1, MPI_INT, r, 0,
MPI_COMM_WORLD, MPI_STATUS_IGNORE);

/* Run through the list2 that was just
received */
for(c = L; c <= H; c++) {
/* If the number is unmarked */
if(list2[c-L] == 0) {
/* The number is prime, print it */
printf("%lu ", c);
}
}

/* If the process is not Rank 0 */
} else {
/* Send list2 to Rank 0 */
MPI_Send(list2, H-L+1, MPI_INT, 0, 0,
MPI_COMM_WORLD);
}

/* Deallocate memory for list */
free(list2);
free(list1);

/* Finalize the MPI environment */
MPI_Finalize();

/* how to tun
mpicc -o sieve.mpi sieve.mpi.c -lm
mpirun –np 2 ./sieve.mpi -n 10
*/