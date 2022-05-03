#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    unsigned int l, m, n;
    unsigned int N     = 1E4;
    unsigned int max   = 1E6;
    unsigned int iters = 100;
    unsigned int *x = malloc(sizeof(*x) * N);
    double average = 0.0;
    unsigned int counter, old;

    for (l = 0; l < iters; ++l)
    {
        printf("%u\n", l);
        counter = 0;
        old = 0;
        for (n = 0; n < N; ++n)
            x[n] = (rand() % max);

        for (m = 0; m < max; ++m)
        {
            for (n = 0; n < N; ++n)
            {
                if (x[n] == m)
                    ++counter;
            }
            if (counter - old == 1)
                counter = old;
            else
                old = counter;
        }
        average += counter;
    }
    average /= iters;
    printf("Average Value: %f\n", average);
    free(x);
    return 0;
}
