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
 *      Draw the plane, marking pixels (x, y) such that GCD(x, y) = 1 white,  *
 *      and pixels with GCD(x, y) != 1 black. The number of white pixels      *
 *      divided by the number of total pixels is computed, which gradually    *
 *      converges to 6/pi^2. This is related to the problem of the            *
 *      probability that two random integers are coprime.                     *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 22, 2021                                                  *
 ******************************************************************************/

/*  Needed for creating the PPM file.                                         */
#include <stdio.h>

/*  Simple routine for computing the GCD of non-negative numbers.             */
static unsigned int GCD(unsigned int n0, unsigned int n1)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (n0 == 0U)
        return n1;
    else if (n1 == 0U)
        return n0;

    while(n0 != n1)
    {
        if(n0 > n1)
            n0 -= n1;
        else
            n1 -= n0;
    }
    return n0;
}
/*  End of GCD.                                                               */

/*  Function for computing the "area" of the blocks with GCD(x, y) = 1. This  *
 *  simply sums over the square [0, N] x [0, N] for which entries have GCD 1, *
 *  and then divides by N^2.                                                  */
static double test(unsigned int N)
{
    /*  Declare necessary variables.                                          */
    unsigned int x, y;
    unsigned long counter = 0UL;

    /*  Loop over all points in the grid [0, N] x [0, N].                     */
    for (x = 0U; x < N; ++x)
        for (y = 0U; y < N; ++y)

            /*  We're counting coprime pairs, which means GCD(x, y) = 1.      */
            if (GCD(x, y) == 1U)
                ++counter;

    /*  The probability is the number of coprime pairs divided by the total,  *
     *  which is N^2. Return this.                                            */
    return (double)counter / (double)(N*N);
}
/*  End of "test" function.                                                   */

/*  Function for plotting GCD grid. White for GCD(x, y) = 1, black otherwise. */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    const unsigned int plot_size = 1024U;
    const unsigned int file_size = 1000U;

    /*  I only want to draw the block [0, 63] x [0, 63], but a 64x64 PGM file *
     *  will be really-really small and zooming in makes it blurry. Use this  *
     *  scale factor to draw the [0, 63] x [0, 63] region in a 1024x1024 PGM. */
    const double scale = 64.0 / (double)plot_size;

    /*  In a PGM file, black is zero and white is 255. Save these values.     */
    const unsigned char black = 0x00U;
    const unsigned char white = 0xFFU;

    /*  Variables for indexing and looping over the lattice.                  */
    unsigned int n, x, y, z_x, z_y;

    /*  And variables for writing to files.                                   */
    FILE *fp, *ftxt;

    /*  Open the PGM file using fopen and give write permissions.             */
    fp = fopen("tmpl_gcd_plot.pgm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        puts("fopen failed and returned NULL for PGM file. Returning.");
        return -1;
    }

    /*  Print the preamble to the PGM file.                                   */
    fprintf(fp, "P5\n%u %u\n255\n", plot_size, plot_size);

    /*  Loop through each pixel.                                              */
    for (y = 0U; y < plot_size; ++y)
    {
        /*  PGMs plot top-to-bottom, whereas mathematicians think in a        *
         *  bottom-to-top style. Plot with the z_y variable to fix this.      */
        z_y = (unsigned int)(scale*((double)plot_size - y));

        /*  Loop over every x pixel as well.                                  */
        for (x = 0U; x < plot_size; ++x)
        {
            z_x = (unsigned int)(scale*x);

            /*  If z_x and z_y are coprime, plot the pixel white.             */
            if (GCD(z_x, z_y) == 1)
                fputc(white, fp);
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */

    /*  Close the file.                                                       */
    fclose(fp);

    /*  We'll write the output to a text file so we can make neater plots     *
     *  using either GNU plotutils or matplotlib in Python.                   */
    ftxt = fopen("tmpl_gcd_test.txt", "w");

    /*  Check that fopen didn't fail.                                         */
    if (!ftxt)
    {
        puts("fopen failed and returned NULL for text file. Returning.");
        return -1;
    }

    /*  Compute the values for the table.                                     */
    for (n = 0U; n < file_size; ++n)
        fprintf(fp, "%.16f\n", test(n));

    /*  Close the file.                                                       */
    fclose(ftxt);
    return 0;
}
/*  End of main.                                                              */
