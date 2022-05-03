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
 *      Plot the average number of attributes that occur when computing the   *
 *      max of a random array of length N, plotted against N. As we average   *
 *      this out we start to get the harmonic numbers.                        *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 22, 2021                                                  *
 ******************************************************************************/

/*  Include the necessary standard library files we'll need to use.           */
#include <stdio.h>
#include <stdlib.h>

/*  We'll need this for the floor function.                                   */
#include <math.h>

/*  Function for computing the number of attributes made while finding the    *
 *  maximum value of an array of real numbers.                                */
static unsigned int max_counter(double *arr, unsigned int arr_length)
{
    /*  Declare a variable for indexing.                                      */
    unsigned int n;

    /*  And a variable for computing the max.                                 */
    double max;

    /*  Counter for the number of attributes made.                            */
    unsigned int counter = 1U;

    /*  Initialize max to the first entry of arr. This counts as an attribute.*/
    max = arr[0];

    /*  Loop over the remaining entries of arr searching for the max.         */
    for (n = 1U; n < arr_length; ++n)
    {
        /*  Reassign max to arr[n] if the latter is now bigger.               */
        if (max < arr[n])
        {
            max = arr[n];

            /*  Increment the counter.                                        */
            counter += 1;
        }
    }
    /*  End of for-loop computing max(arr).                                   */

    return counter;
}
/*  End of max_counter definition.                                            */

/*  Function for computing a linear interpolation for the value x with the    *
 *  the line containing (x0, y0), (x1, y1). Used for plotting.                */
static double interp(double x, double x0, double y0, double x1, double y1)
{
    /*  Declare necessary variables.                                          */
    double slope, y;

    /*  Compute the slope of the line (x0, y0) -- (x1, y1).                   */
    slope = (y1 - y0) / (x1 - x0);

    /*  Compute the interpolated value corresponding to the input x.          */
    y = slope * (x - x0) + y0;
    return y;
}
/*  End of interp definition.                                                 */

/*  Function for computing a pseudo-random number in the interval [0, 1].     */
static double real_rand(void)
{
    /*  Use the rand function in stdlib.h to get a non-negative pseudo-random *
     *  integer, and divide by the RAND_MAX macro to ensure the outcome       *
     *  falls within the range [0, 1].                                        */
    return (double)rand() / (double)RAND_MAX;
}
/*  End of real_rand definition.                                              */

/*  Function for testing the average efficiency of the above max routine.     */
int main(void)
{
    /*  Declare a pointer to a FILE so we can write the output. The FILE      *
     *  data type is defined in stdio.h.                                      */
    FILE *fp;

    /*  Define three colors for the plot. Black is the background, gray is    *
     *  for log(x), and white is for the data.                                */
    unsigned char black = 0x00U;
    unsigned char gray  = 0x80U;
    unsigned char white = 0xFFU;

    /*  Declare a variable for the size of the output plot.                   */
    unsigned int size = 1024U;

    /*  Declare three variables for indexing.                                 */
    unsigned int k, m, n;

    /*  And declare pointers to arrays for later.                             */
    double *arr, *x0, *y0;

    /*  Declare a variable for calculating the average number of attributions *
     *  it took for find the maximum of an array of length m.                 */
    double average_attr;

    /*  Define the maximum array size we will be testing.                     */
    unsigned int max_arr_length = 100U;

    /*  Define the number of iterations we'll run for each m < arr_max.       */
    unsigned int iter_max = 1000U;

    /*  Define the size of the box we'll be plotting to.                      */
    double x_min = 1.0;
    double x_max = (double)max_arr_length;
    double y_min = 0.0;
    double y_max = log(x_max) + 1.0;

    /*  Variable for the width of the curve being plotted.                    */
    double pixel_width = 0.01;

    /*  And variables for sampling the box [x_min, x_max] x [y_min, y_max].   */
    double z_x, z_y;
    unsigned int x, y;

    /*  Variable for scaling the figure.                                      */
    double rcpr_factor = 1.0 / (double)(size - 1U);

    /*  And a variable for interpolating the data for a line plot.            */
    double y_interp;

    /*  Allocate memory for an array of size max_arr_length to perform our    *
     *  test on. The malloc function is defined in stdlib.h.                  */
    arr = malloc(sizeof(*arr) * max_arr_length);

    /*  Check the malloc didn't fail, aborting computation if it did. Malloc  *
     *  returns NULL on failure so check for this.                            */
    if (arr == NULL)
    {
        /*  If malloc failed, print an error message and abort. The puts      *
         *  function (put-string) is found in stdio.h.                        */
        puts("Error: Malloc failed to allocate memory for arr. Aborting.");
        return -1;
    }

    /*  Do the same thing for x0 and y0.                                      */
    x0  = malloc(sizeof(*x0)  * max_arr_length);

    if (x0 == NULL)
    {
        puts("Error: Malloc failed to allocate memory for arr. Aborting.");

        /*  Since we're aborting with error, free the memory we've malloc'd.  */
        free(arr);
        return -1;
    }

    /*  Finally, allocate memory for y0 and check if malloc failed.           */
    y0  = malloc(sizeof(*y0)  * max_arr_length);

    if (y0 == NULL)
    {
        puts("Error: Malloc failed to allocate memory for arr. Aborting.");

        free(arr);
        free(x0);
        return -1;
    }

    /*  Open a file so we can write the results.                              */
    fp = fopen("tmpl_max_attr_average.pgm", "w");

    /*  If fopen fails it returns NULL. Check for this.                       */
    if (fp == NULL)
    {
        puts("Error: fopen failed and returned NULL. Aborting.");

        /*  Free all the memory we malloc'd.                                  */
        free(x0);
        free(y0);
        free(arr);
        return -1;
    }

    /*  Write the preamble of the PGM file.                                   */
    fprintf(fp, "P5\n%d %d\n255\n", size, size);

    /*  Loop over different array sizes to check the efficieny of the max     *
     *  function and see how it depends on array size, on average.            */
    for (k = 1U; k < max_arr_length; ++k)
    {
        /*  Reset average_attr to zero.                                       */
        average_attr = 0.0;

        /*  Get the average number of attributions applied in the max         *
         *  function for iter_max number of random arrays of size k.          */
        for (m = 0U; m < iter_max; ++m)
        {
            /*  Reset the first k entries of arr to random values in [0, 1].  */
            for (n = 0; n < k; ++n)
                arr[n] = real_rand();

            /*  Use the max_counter function to count how many attributes are *
             *  needed to compute the max of the array.                       */
            average_attr += (double)max_counter(arr, k);
        }

        /*  Compute the average number of attributions by dividing by the     *
         *  number of tests we ran, which is iter_max.                        */
        average_attr /= (double)iter_max;

        /*  Arrays are indexed starting at 0 in C and our for-loop starts at  *
         *  1. So set the (k-1)th element to (k, average_attr).               */
        x0[k - 1] = (double)k;
        y0[k - 1] = average_attr;
    }
    /*  End of for-loop computing average number of attributes as a function  *
     *  of the size of the array.                                             */

    /*  Loop through each pixel.                                              */
    for (y=0U; y < size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = y * (y_max - y_min) * rcpr_factor + y_min;
        z_y = y_max - z_y;

        /*  Loop over every x pixel as well.                                  */
        for (x = 0U; x < size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * rcpr_factor + x_min;

            /*  We need the index corresponding to the floor of z_x so we can *
             *  use interp on the x0 and y0 pointers. Fortunately, this index *
             *  is just floor(z_x) (converted to an integer).                 */
            n = (unsigned int)floor(z_x);

            /*  To get a line plot we need to interpolate the values between  *
             *  our discrete data set. Use the interp function defined above. */
            y_interp = interp(z_x, x0[n - 1], y0[n - 1], x0[n], y0[n]);

            /*  If y_interp and z_y are close, color the pixel white meaning  *
             *  we have a point in the plane corresponding to the data.       */
            if (fabs(y_interp - z_y) < pixel_width)
                fputc(white, fp);

            /*  If log(z_x) and z_y are close, color gray to represent the    *
             *  logarithmic function.                                         */
            else if (fabs(log(z_x) - z_y) < pixel_width)
                fputc(gray, fp);

            /*  Lastly, if neither of the above are true, color black to      *
             *  indicate the background.                                      */
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */

    /*  Free all of the pointers we've malloc'd. Free is defined in stdlib.h. */
    free(arr);
    free(x0);
    free(y0);

    /*  Close the PGM file we opened.                                         */
    fclose(fp);

    /*  And finally, exit the function.                                       */
    return 0;
}
/*  End of main.                                                              */

