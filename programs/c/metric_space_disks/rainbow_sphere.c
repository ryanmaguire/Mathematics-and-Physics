/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Draw a circle with a rainbow gradient.                                *
 ******************************************************************************/

/*  Struct for creating PPM files and writing to them.                        */
#include "msd_ppm.h"

/*  Struct for working with colors in 24-bit RGB format.                      */
#include "msd_color.h"

/*  Default parameters for the images are given here.                         */
#include "msd_setup.h"

/*  free and malloc, standard library functions.                              */
#include <stdlib.h>

/*  fabs given here.                                                          */
#include <math.h>

/*  puts function provided here.                                              */
#include <stdio.h>

/*  Function for drawing a sphere with a rainbow gradient.                    */
int main(void)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  The total number of pixels in the PPM file.                           */
    const unsigned int size = msd_setup_xsize * msd_setup_ysize;

    /*  Allocate memory for the colors of each pixel in the file.             */
    struct msd_color *c = malloc(sizeof(*c) * size);

    /*  Create and name the PPM file.                                         */
    struct msd_ppm PPM = msd_ppm_create("rainbow_sphere.ppm");

    /*  Check if the constructor for the PPM failed.                          */
    if (!PPM.fp)
    {
        puts("msd_ppm_create returned NULL for FILE pointer. Aborting.");

        /*  Check if malloc also failed. It returns NULL if it does.          */
        if (c)
            free(c);

        return -1;
    }

    /*  Check if malloc failed.                                               */
    if (!c)
    {
        puts("malloc failed and returned NULL. Aborting.");
        msd_ppm_close(&PPM);
        return -1;
    }

    /*  Initialize the preamble of the PPM file with the default values.      */
    msd_ppm_init(&PPM);

    /*  OpenMP can be used to parallelize the computation.                    */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < size; ++n)
    {
        /*  Compute the x and y coordinates of the current pixel.             */
        const unsigned int xp = n % msd_setup_xsize;
        const unsigned int yp = n / msd_setup_xsize;

        /*  Get the coordinates corresponding to the given pixel.             */
        const double x = msd_setup_xmin + xp*msd_setup_px_factor;
        const double y = msd_setup_ymax - yp*msd_setup_py_factor;

        /*  Compute the distance using the Euclidean metric.                  */
        const double dist = sqrt(x*x + y*y);

        /*  Points outside of the circle are black.                           */
        if (dist > 1.0)
            c[n] = msd_black;

        /*  Points inside the circle are given a rainbow gradient.            */
        else
            c[n] = msd_linear_rainbow_gradient(1.0 - dist, 0.0, 1.0);
    }
    /*  End of for-loop for n.                                                */

    /*  Create the PPM from the data.                                         */
    for (n = 0U; n < size; ++n)
        msd_color_write_to_ppm(&c[n], &PPM);

    /*  Free the data, close the PPM file, and return.                        */
    msd_ppm_close(&PPM);
    free(c);
    return 0;
}
/*  End of main.                                                              */
