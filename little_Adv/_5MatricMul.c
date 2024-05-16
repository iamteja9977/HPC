/*
omp_set_num_threads(Noofthreads): Sets the number of threads to be used for parallel execution.
#pragma omp parallel for private(j,k) shared(Matrix_A, Matrix_B, Result): This is the OpenMP parallel for directive. It parallelizes the loop that follows it.
 It automatically distributes iterations of the loop across available threads. `private



The struct timeval structure is used to represent time in the form of seconds and microseconds.
 In this code, TimeValue_Start and TimeValue_Final are instances of this structure, used to store the start and end times of the computation
*/

// The code aims to perform dense matrix multiplication using the OpenMP parallel for directive and private clause.
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int NoofRows_A, NoofCols_A, NoofRows_B, NoofCols_B, i, j, k, Noofthreads;
    float **Matrix_A, **Matrix_B, **Result;
    double time_overhead;
    struct timeval TimeValue_Start, TimeValue_Final;

    printf("\n\t\t---------------------------------------------------------------------------");
    printf("\n\t\t Centre for Development of Advanced Computing (C-DAC)");
    printf("\n\t\t---------------------------------------------------------------------------");
    printf("\n\t\t Objective : Dense Matrix Computations (Floating Point Operations)\n ");
    printf("\n\t\t Matrix into Matrix Multiplication using ");
    printf("\n\t\t OpenMP one PARALLEL for directive and Private Clause;");
    printf("\n\t\t..........................................................................\n");

    // Checking for command line arguments
    if (argc != 6)
    {
        printf("\n\t\t Very Few Arguments\n ");
        printf("\n\t\t Syntax : exec <Threads> <NoOfRows A> <NoOfCols A>  <NoOfRows B> <NoOfCols B>\n");
        exit(-1);
    }

    Noofthreads = atoi(argv[1]);
    NoofRows_A = atoi(argv[2]);
    NoofCols_A = atoi(argv[3]);
    NoofRows_B = atoi(argv[4]);
    NoofCols_B = atoi(argv[5]);

    printf("\n\t\t Threads        : %d ", Noofthreads);
    printf("\n\t\t Matrix A Size  : %d X %d ", NoofRows_A, NoofCols_A);
    printf("\n\t\t Matrix B Size  : %d X %d ", NoofRows_B, NoofCols_B);

    // Checking matrix dimensions for validity
    if (NoofRows_A <= 0 || NoofCols_A <= 0 || NoofRows_B <= 0 || NoofCols_B <= 0)
    {
        printf("\n\t\t The number of rows and columns should be positive integers\n");
        exit(1);
    }

    // Checking if matrix multiplication is possible
    if (NoofCols_A != NoofRows_B)
    {
        printf("\n\t\t Matrix Matrix Computation Is Not Possible \n");
        exit(1);
    }

    // Dynamic memory allocation and initialization of Matrix_A elements
    Matrix_A = (float **)malloc(sizeof(float *) * NoofRows_A);
    for (i = 0; i < NoofRows_A; i++)
    {
        Matrix_A[i] = (float *)malloc(sizeof(float) * NoofCols_A);
        for (j = 0; j < NoofCols_A; j++)
            Matrix_A[i][j] = i + j;
    }

    // Dynamic memory allocation and initialization of Matrix_B elements
    Matrix_B = (float **)malloc(sizeof(float *) * NoofRows_B);
    for (i = 0; i < NoofRows_B; i++)
    {
        Matrix_B[i] = (float *)malloc(sizeof(float) * NoofCols_B);
        for (j = 0; j < NoofCols_B; j++)
            Matrix_B[i][j] = i + j;
    }

    // Dynamic memory allocation for Result matrix
    Result = (float **)malloc(sizeof(float *) * NoofRows_A);
    for (i = 0; i < NoofRows_A; i++)
    {
        Result[i] = (float *)malloc(sizeof(float) * NoofCols_B);
        for (j = 0; j < NoofCols_B; j++)
            Result[i][j] = 0.0;
    }

    // Starting timer
    gettimeofday(&TimeValue_Start, NULL);

    // Set the number of threads
    omp_set_num_threads(Noofthreads);

    // OpenMP Parallel For Directive : Fork a team of threads giving them their own copies of variables
#pragma omp parallel for private(j, k) shared(Matrix_A, Matrix_B, Result)
    for (i = 0; i < NoofRows_A; i++)
    {
        for (j = 0; j < NoofCols_B; j++)
        {
            for (k = 0; k < NoofCols_A; k++)
            {
                Result[i][j] += Matrix_A[i][k] * Matrix_B[k][j];
            }
        }
    }

    // Ending timer
    gettimeofday(&TimeValue_Final, NULL);

    // Calculate the time taken for the computation
    time_overhead = (TimeValue_Final.tv_sec - TimeValue_Start.tv_sec) + ((TimeValue_Final.tv_usec - TimeValue_Start.tv_usec) / 1000000.0);

    printf("\n\t\t Time in Seconds (T)        : %lf Seconds \n", time_overhead);
    printf("\n\t\t..........................................................................\n");

    // Freeing allocated memory
    for (i = 0; i < NoofRows_A; i++)
    {
        free(Matrix_A[i]);
        free(Matrix_B[i]);
        free(Result[i]);
    }
    free(Matrix_A);
    free(Matrix_B);
    free(Result);

    return 0;
}

/*
 gcc -fopenmp _5MatricMul.c
[srtejaa@srtejaa-pc] ➜ little_Adv (! main) ./a.out 4 3 3 3 4

output;
-------

---------------------------------------------------------------------------
                 Centre for Development of Advanced Computing (C-DAC)
                ---------------------------------------------------------------------------
                 Objective : Dense Matrix Computations (Floating Point Operations)

                 Matrix into Matrix Multiplication using
                 OpenMP one PARALLEL for directive and Private Clause;
                ..........................................................................

                 Threads        : 4
                 Matrix A Size  : 3 X 3
                 Matrix B Size  : 3 X 4
                 Time in Seconds (T)        : 0.000162 Seconds

                ..........................................................................

*/