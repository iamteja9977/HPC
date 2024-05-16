#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
    printf("Welcome to CDAC Bangalore\n");
}

// This will print that statement "n" number of times, where n = number of CPU cores
// currently my laptop has 8

/*OUTPUT
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore

*/




// You can increase or decrease number of threads based on your requirement,
// by changing the pre-processor directive:

// #pragma omp parallel num_threads (8)

// NEXT