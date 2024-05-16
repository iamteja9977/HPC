#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel num_threads(4)
    printf("Welcome to CDAC Bangalore\n");
}

// manually i'm making it 4 now

/*OUTPUT
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore
Welcome to CDAC Bangalore

*/
