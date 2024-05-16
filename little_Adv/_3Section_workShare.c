// code demonstrates how to divide work among multiple threads using OpenMP sections,
//  enhancing performance by exploiting parallelism.

/*
omp_get_thread_num(): This function returns the thread ID of the calling thread.

omp_get_num_threads(): This function returns the total number of threads in the current parallel region.

#pragma omp sections nowait: This directive divides the enclosed code block into sections, each to be executed by a separate thread.
 The nowait clause indicates that threads can proceed immediately to the next statement after completing their section without waiting for others.

#pragma omp section: This directive defines a section of code to be executed by a single thread.
 In this code, two sections are defined, each containing a loop that operates on arrays a, b, c, and d.


*/

// This code utilizes OpenMP to parallelize two different computations: addition (c[i] = a[i] + b[i]) and multiplication (d[i] = a[i] * b[i]) of elements from arrays a and b.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int main(int argc, char *argv)
{
    int i, nthreads, tid;
    float a[N], b[N], c[N], d[N];
    // some initializations:
    for (i = 0; i < N; i++)
    {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
        c[i] = d[i] = 0.0;
    }
#pragma omp parallel shared(a, b, c, d, nthreads) private(i, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

#pragma omp sections nowait
        // The nowait clause allows threads to proceed independently to the end of the parallel region without waiting for other threads.
        {
#pragma omp section
            {
                printf("Thread %d doing section 1\n", tid);
                for (i = 0; i < N; i++)
                {
                    c[i] = a[i] + b[i];
                    printf("Thread %d: c[%d] = %f\n", tid, i, c[i]);
                }
            }
#pragma omp section
            {
                printf("Thread %d doing section 2\n", tid);
                for (i = 0; i < N; i++)
                {
                    d[i] = a[i] * b[i];
                    printf("Thread %d: d[%d] = %f\n", tid, i, d[i]);
                }
            }
        } // end of sections

    } // end of single
}