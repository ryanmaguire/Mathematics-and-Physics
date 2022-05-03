
#include <stdio.h>
#include <omp.h>
int main(void)
{
    puts("Now testing OpenMP:\n");
    #pragma omp parallel
    printf(
        "Hello from thread %d, nthreads %d\n",
        omp_get_thread_num(),
        omp_get_num_threads()
    );
    return 0;
}

