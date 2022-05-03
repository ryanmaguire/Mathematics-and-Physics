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
 *  Creates a Barnley fern. I got most of the ideas from a reddit post in     *
 *  r/madeinpython and converted it to C.                                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2022/01/16                                                        *
 ******************************************************************************/

/*  Avoid silly warnings from the MSVC compiler for Windows users.            */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  FILE, fopen, and fprintf found here.                                      */
#include <stdio.h>

/*  Random function found here.                                               */
#include <stdlib.h>

/*  Function for drawing the Barnsley Fern.                                   */
int main(void)
{
    /*  Width and height of the PGM file.                                     */
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;

    /*  Number of iterations used per pixel while making the fern.            */
    const unsigned int iters = 50U;

    /*  Total number of steps in the for-loop.                                */
    const unsigned int total = width * height * iters;

    /*  Growth factor for the fern. Set this between 0 and 1.                 */
    const double grow = 0.8;

    /*  Scale factor for generating a pseudo-random number between 0 and 100. */
    const double scale_factor = 100.0 / (double)RAND_MAX;

    /*  Integers for looping over pixels in the fern.                         */
    unsigned int n, x, y;

    /*  Starting x and y values.                                              */
    double x_val = 0.0;
    double y_val = 1.0;

    /*  Other variables needed throughout the computation.                    */
    double x_new, y_new, random_value, random_int, val;

    /*  Variable for the intensity of the output color. We're using greyscale.*/
    unsigned char grey;

    /*  Pointer to the data. The (x, y) pixel corresdonds to the entry        *
     *  n = x + y*width.                                                      */
    double *data;

    /*  Open the file and give it write permissions.                          */
    FILE *fp = fopen("barnsley_fern.pgm", "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Allocate memory for the data and initialize it to zero.               */
    data = calloc(width*height, sizeof(*data));

    /*  calloc returns NULL on failure. Check for this.                       */
    if (!data)
    {
        puts("malloc failed and returned NULL. Aborting.");

        /*  Close the file since fopen was successful.                        */
        fclose(fp);
        return -1;
    }

    /*  Write the preamble to the PGM file. Windows users will use            *
     *  text-based, and everyone else will use binary format.                 */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P2\n%u %u\n255\n", width, height);
#else
    fprintf(fp, "P5\n%u %u\n255\n", width, height);
#endif

    /*  Loop over and create the fern.                                        */
    for (n = 0U; n < total; ++n)
    {
        x_new = x_val;
        y_new = y_val;

        /*  Get a random integer using the standard library function rand().  */
        random_int = rand();

        /*  Scale this to a random number between 0 and 100.                  */
        random_value = (double)random_int * scale_factor;

        if (random_value < 1.0)
        {
            x_val = 0.0;
            y_val = 0.16*y_new;
        }
        else if (random_value < 86.0)
        {
            x_val = grow*x_new + 0.04*y_new;
            y_val = -0.04*x_new + 0.85*y_val + 1.6;
        }
        else if (random_value < 93.0)
        {
            x_val = 0.20*x_new - 0.26*y_new;
            y_val = 0.23*x_new + 0.22*y_new + 1.6;
        }
        else
        {
            x_val = -0.15*x_new + 0.28*y_new;
            y_val = 0.26*x_new + 0.24*y_new + 0.44;
        }

        /*  Get the pixel x_val and y_val correspond to.                      */
        x = (unsigned int)(width * (0.45 + 0.195*x_val));
        y = (unsigned int)(height * (1.0 - 0.09*y_val));

        /*  The (x, y) pixel is n = x + y*width.                              */
        data[x + y*width] += 1.0;
    }
    /*  End of for-loop over n.                                               */

    /*  Loop over the y pixels and create the PGM file.                       */
    for (y = 0U; y < height; ++y)
    {
        /*  Loop over x pixels.                                               */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the color the pixel is going to be.                   */
            val = (256.0 - data[x + y*width]) / 256.0;

            /*  Negative values will be black.                                */
            if (val <= 0.0)
                grey = 0x00U;

            /*  Otherwise, use a grayscale gradient from black-to-white.      */
            else
            {
                val = val*val;
                grey = (unsigned char)(255.0 * val*val*val);
            }

            /*  For Windows users, use text-based. Everyone else, use binary. */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
            fprintf(fp, "%u\n", grey);
#else
            fputc(grey, fp);
#endif
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Free the memory allocated for the data.                               */
    free(data);

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
