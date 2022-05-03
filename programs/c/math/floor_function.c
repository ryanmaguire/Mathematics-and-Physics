/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  This silly bit of code uses a binary search to compute floor(x) to 16     *
 *  decimals. This does NOT assume the IEEE 754 format is implemented, and is *
 *  portable. It is, however, 5-10 times SLOWER than glibc's floor function   *
 *  which does take advantage of the IEEE 754 format.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  Printf, puts, etc., found here.                                           */
#include <stdio.h>

/*  Malloc and free are here.                                                 */
#include <stdlib.h>

/*  floor function is found here. This is for comparison.                     */
#include <math.h>

/*  Timing tools for comparing against glibc.                                 */
#include <time.h>

/*  The values 2^n are needed for n = 0 to n = 52. 2^52 is the largest power  *
 *  of 2 such that beyond this and value x > 2^n can be treated as an integer *
 *  within double precision (16 decimals).                                    */
static const double arr[53] = {
    4503599627370496.0,
    2251799813685248.0,
    1125899906842624.0,
    562949953421312.0,
    281474976710656.0,
    140737488355328.0,
    70368744177664.0,
    35184372088832.0,
    17592186044416.0,
    8796093022208.0,
    4398046511104.0,
    2199023255552.0,
    1099511627776.0,
    549755813888.0,
    274877906944.0,
    137438953472.0,
    68719476736.0,
    34359738368.0,
    17179869184.0,
    8589934592.0,
    4294967296.0,
    2147483648.0,
    1073741824.0,
    536870912.0,
    268435456.0,
    34217728.0,
    67108864.0,
    33554432.0,
    16777216.0,
    8388608.0,
    4194304.0,
    2097152.0,
    1048576.0,
    524288.0,
    262144.0,
    131072.0,
    65536.0,
    32768.0,
    16384.0,
    8192.0,
    4096.0,
    2048.0,
    1024.0,
    512.0,
    256.0,
    128.0,
    64.0,
    32.0,
    16.0,
    8.0,
    4.0,
    2.0,
    1.0
};

/*  Function for computing the floor of x.                                    */
static double my_floor(double x)
{
    /*  Variable for indexing.                                                */
	unsigned int n;

    /*  Variable for the output, and for the step size.                       */
	double out, dx;

    /*  We can use a reflection rule to reduce to x > 0.                      */
    const double abs_x = fabs(x);

    /*  For real numbers greater than 10^16 we can treat as integers to       *
     *  a reasonable precision.                                               */
	if (x > 1.0E16)
		return x;

    /*  Find the least power of 2 greater than |x|.                           */
    n = 0U;

    while (abs_x < arr[n])
    {
        ++n;
    }

    /*  We can start out binary search at this power of two.                  */
	out = arr[n];
    dx = abs_x - out;
	n = n + 1U;

    /*  Increment out by different powers of two. We are effectively          *
     *  computing the binary represention of floor(x).                        */
	while (dx > 1.0)
	{
		if (abs_x > out)
			out += arr[n];
		else if (x < out)
			out -= arr[n];
        else
            return out;

        dx = fabs(abs_x - out);
		++n;
	}

    /*  If x was positive to begin with, no reflection needed.                */
    if (x > 0.0)
    {
	    if (out <= abs_x)
		    return out;
	    else
		    return out - 1.0;
    }

    /*  Otherwise, use the reflection rule.                                   */
    else
    {
        if (out == abs_x)
            return -abs_x;
	    else if (out < abs_x)
		    return -1.0 - out;
	    else
		    return -out;
    }
}
/*  End of my_floor.                                                          */

/*  Function for testing my_floor vs. floor.                                  */
int main(void)
{
	double *x, *y0, *y1, max, temp;

    /*  Step size in the test values.                                         */
    const double dx = 0.1;

    /*  Number of test values to run.                                         */
	unsigned int N = 1E6;

    /*  Variable for indexing.                                                */
	unsigned int n;

    /*  Variables for computing the run time.                                 */
	clock_t t1, t2;

    /*  Allocate memory for the arrays.                                       */
	x = malloc(sizeof(*x) * N);

    /*  Check if malloc failed.                                               */
    if (x == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

	y0 = malloc(sizeof(*x) * N);

    /*  Check if malloc failed.                                               */
    if (y0 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(x);
        return -1;
    }

	y1 = malloc(sizeof(*x) * N);

    /*  Check if malloc failed.                                               */
    if (y1 == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(x);
        free(y1);
        return -1;
    }

    /*  Compute the test values.                                              */
	x[0] = -0.5*dx*(double)N;
	for (n = 1UL; n < N; ++n)
		x[n] = x[n-1] + dx;

    /*  Compute my_floor of the test values and time this.                    */
	t1 = clock();
	for (n = 0UL; n < N; ++n)
		y0[n] = my_floor(x[n]);
	t2 = clock();
	printf("my_floor: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Compute floor of the test values and time this.                       */
    t1 = clock();
    for (n = 0UL; n < N; ++n)
        y1[n] = floor(x[n]);
    t2 = clock();
    printf("floor:    %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Initialize max.                                                       */
    max = 0.0;

    /*  Find the maximum error.                                               */
	for (n = 0UL; n < N; ++n)
	{
		temp = fabs(y0[n] - y1[n]);
		if (max < temp)
		    max = temp;
	}

    /*  And print out this error.                                             */
	printf("Error: %.16f\n", max);

    /*  Free everything.                                                      */
	free(x);
	free(y0);
	free(y1);
	return 0;
}
/*  End of main.                                                              */

