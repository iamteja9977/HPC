//  code demonstrates the use of OpenMP (Open Multi-Processing) to parallelize a simple vector addition operation.

/*
 Two constants are defined: CHUNKSIZE for controlling the chunk size in the parallel loop, and N for the size of the arrays a, b, and c.

  an OpenMP parallel region using the #pragma omp parallel directive. Within this region, each thread will execute the same code block in parallel.
|
--- Inside the parallel region, each thread identifies its thread number (tid) using omp_get_thread_num().
 If the thread number is 0, it also obtains and prints the total number of threads (nthreads) using omp_get_num_threads().

 The code parallelizes the loop using the #pragma omp for directive.
  Each thread iterates over a portion of the loop's iterations, with the loop scheduling set to dynamic and the chunk size specified as CHUNKSIZE.

It distributes the work among multiple threads, each responsible for computing a portion of the final result.
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 6
#define N 26

int main(int argc, char *argv[])
{
    int nthreads, tid, i, chunk;
    float a[N], b[N], c[N];

    // Some initializations
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 2.0;
    chunk = CHUNKSIZE;

#pragma omp parallel shared(a, b, c, nthreads, chunk) private(i, tid) num_threads(4)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        // printf("Thread %d starting...\n", tid);

#pragma omp for schedule(dynamic, chunk)
        for (i = 0; i < N; i++)
        {
            c[i] = a[i] + b[i];
            printf("Thread %d: c[%d] = %f\n", tid, i, c[i]);
        }
    } // end of parallel section
}

// every time the output changes 