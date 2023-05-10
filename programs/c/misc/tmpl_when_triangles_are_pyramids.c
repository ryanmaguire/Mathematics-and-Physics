/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *  Purpose:                                                                  *
 *      Search for non-negative integers M and N with the property that:      *
 *             M                N                                             *
 *           -----            -----                                           *
 *           \                \       2                                       *
 *           /      m    =    /      n                                        *
 *           -----            -----                                           *
 *           m = 0            n = 0                                           *
 *                                                                            *
 *      That is, numbers that are both triangular numbers and pyramidal.      *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 22, 2021                                                  *
 ******************************************************************************/

/*  Needed for printf.                                                        */
#include <stdio.h>

/*  Needed for the square root function.                                      */
#include <math.h>

/*  The sum 1 + 4 + 9 + ... + n^2 can be precomputed as n(n+1)(2n+1)/6. The   *
 *  proof of this follows from induction. Use this to quickly compute the sum.*/
static unsigned long int fcube(unsigned long int n)
{
    return n*(n + 1UL)*(2UL*n + 1UL) / 6UL;
}

/*  The sum 1 + 2 + 3 + ... + n can be precomputed as n(n+1)/2. The proof     *
 *  also follows from induction. Use this to quickly compute the sum.         */
static unsigned long int fsquare(unsigned long int n)
{
    return n * (n + 1UL) / 2UL;
}

/*  Function for finding numbers that are both triangular and pyramidal. We   *
 *  can reduce an O(n^2) search to an O(n) one by solving the inverse of      *
 *  n(n+1)/2 = 0.5*n^2 + 0.5*n via the quadratic formula. We can then plug    *
 *  this into the cube formula and see if we get the original value.          */
int main(void)
{
    /*  Index for checking various integers.                                  */
    unsigned long int m;

    /*  Maximum bound we'll search up to.                                     */
    const unsigned long int max = 1000000UL;

    /*  Values for storing the sum of integers and the sum of squares.        */
    unsigned long int valx, valy;

    /*  Variable used for computing the inverse of 0.5*n^2 + 0.5*n.           */
    unsigned long int x;

    /*  (0, 0) is a matching pair. Print this, and then skip it in the sum.   */
    puts("(0, 0)");

    /*  Same for (1, 1).                                                      */
    puts("(1, 1)");

    /*  If OpenMP is available, use it. This greatly improves performance.    */
#ifdef _OMP
#pragma omp parallel for
#endif

    /*  Since we've printed the n = 0 and n = 1 case, start at n = 2.         */
    for (m = 2UL; m < max; ++m)
    {
        /*  Compute the sum 1 + 4 + ... + m^2.                                */
        valy = fcube(m);

        /*  Compute the inverse of 0.5*valy^2 + 0.5*valy. If fcube(m)         *
         *  is a value that is both triangular and pyramidal, x should        *
         *  be an integer. However, due to floating-point round-off errors    *
         *  this may not be true. We'll correct for this later.               */
        x = (unsigned long int)(-0.5 + 0.5*sqrt(8.0*(double)valy + 1.0));

        /*  Compute the sum 1 + 2 + ... + x.                                  */
        valx = fsquare(x);

        /*  Floating-point error may mean we are less than or greater than    *
         *  the actual value. Check for this.                                 */
        if (valx < valy)
        {
            /*  Increment x until either we get equality, meaning we have     *
             *  found a number that is both triangular and pyramidal, or      *
             *  until we overshoot, meaning fcube(m) is not such a value.     */
            while (valx < valy)
            {
                ++x;
                valx = fsquare(x);
            }

            /*  If we have equality, print the pair (x, m). This is a pair    *
             *  such that 1 + 2 + ... + x = 1 + 4 + ... + m^2.                */
            if (valx == valy)
                printf("(%lu, %lu)\n", x, m);
        }

        /*  Do the same thing in the event that we went over the value.       */
        else if (valx > valy)
        {
            while (valx > valy)
            {
                --x;
                valx = fsquare(x);
            }

            /*  Again, print the values if we have equality.                  */
            if (valx == valy)
                printf("(%lu, %lu)\n", x, m);
        }

        /*  In this instance there was no floating-point error, and we have   *
         *  a matching pair. Print this out.                                  */
        else
            printf("(%lu, %lu)\n", x, m);
    }
    return 0;
}
/*  End of main.                                                              */

