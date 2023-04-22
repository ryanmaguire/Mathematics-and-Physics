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
 *      Provides routines for plotting complex functions.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/21                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_H
#define CVP_H

/*  malloc and free are given here.                                           */
#include <stdlib.h>

/*  Complex struct provided here.                                             */
#include "cvp_complex.h"

/*  Struct for working with colors in RGB format.                             */
#include "cvp_color.h"

/*  Struct for creating and writing to PPM files.                             */
#include "cvp_ppm.h"

/*  Basic setup parameters for plotting functions provided here.              */
#include "cvp_setup.h"

/*  Functions for converting complex numbers into colors given here.          */
#include "cvp_colorers.h"

/*  Coloring functions for coloring points in the complex plane.              */
typedef struct cvp_color (*colorer)(const struct cvp_complex *);

/*  Complex-valued functions with complex inputs.                             */
typedef struct cvp_complex (*complex_func)(const struct cvp_complex *);

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_plot                                                      *
 *  Purpose:                                                                  *
 *      Creates a plot from a complex function based on argument and modulus. *
 *  Arguments:                                                                *
 *      cfunc (complex_func):                                                 *
 *          A complex-valued function of a complex variable.                  *
 *      color (colorer):                                                      *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_plot(complex_func cfunc, colorer color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    unsigned int x, y;

    /*  Variables for the real and imaginary parts of a given complex number. */
    double z_re, z_im;

    /*  Variable for the complex number z_re + i*z_im.                        */
    struct cvp_complex z;

    /*  Color for the pixel corresponding to z.                               */
    struct cvp_color c;

    /*  Variable for the ppm file.                                            */
    struct cvp_ppm PPM = cvp_ppm_create(name);

    /*  Check if the constructor failed.                                      */
    if (!PPM.fp)
        return;

    /*  Initialize the ppm file to the default values.                        */
    cvp_ppm_init(&PPM);

    /*  Loop over the y coordinates of the ppm file.                          */
    for (y = 0U; y < cvp_setup_ysize; y++)
    {
        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = cvp_setup_ymax - cvp_setup_pyfactor*y;

        /*  Loop over the x coordinates of the ppm file.                      */
        for (x = 0U; x < cvp_setup_xsize; x++)
        {
            /*  Compute the corresponding x coordinate.                       */
            z_re = cvp_setup_xmin + cvp_setup_pxfactor*x;

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z.real = z_re;
            z.imag = z_im;

            /*  Get the color corresponding to this pixel.                    */
            z = cfunc(&z);
            c = color(&z);

            /*  Write the color to the ppm file.                              */
            cvp_color_write_to_ppm(&c, &PPM);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the ppm file.                                                   */
    cvp_ppm_close(&PPM);
}
/*  End of cvp_complex_plot.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_iters_plot                                                        *
 *  Purpose:                                                                  *
 *      Creates a plot from repeated evaluation of a complex function.        *
 *  Arguments:                                                                *
 *      cfunc (complex_func):                                                 *
 *          A complex-valued function of a complex variable.                  *
 *      iters (unsigned int):                                                 *
 *          The number of times to call the function.                         *
 *      color (colorer):                                                      *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (const char *):                                                  *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
CVP_INLINE void
cvp_iters_plot(complex_func cfunc, unsigned int iters,
               colorer color, const char *name)
{
    /*  Variables for the x and y coordinates of a given pixel.               */
    unsigned int x, y;

    /*  Variable for keeping tracks of the number of iterations performed.    */
    unsigned int ind;

    /*  Variables for the real and imaginary parts of a given complex number. */
    double z_re, z_im;

    /*  Variable for the complex number z_re + i*z_im.                        */
    struct cvp_complex z;

    /*  Color for the pixel corresponding to z.                               */
    struct cvp_color c;

    /*  Variable for the ppm file.                                            */
    struct cvp_ppm PPM = cvp_ppm_create(name);

    /*  Check if the constructor failed.                                      */
    if (!PPM.fp)
        return;

    /*  Initialize the ppm file to the default values.                        */
    cvp_ppm_init(&PPM);

    /*  Loop over the y coordinates of the ppm file.                          */
    for (y = 0U; y < cvp_setup_ysize; y++)
    {
        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = cvp_setup_ymax - cvp_setup_pyfactor*y;

        /*  Loop over the x coordinates of the ppm file.                      */
        for (x = 0U; x < cvp_setup_xsize; x++)
        {
            /*  Compute the corresponding x coordinate.                       */
            z_re = cvp_setup_xmin + cvp_setup_pxfactor*x;

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z.real = z_re;
            z.imag = z_im;

            /*  Repeatedly call the function.                                 */
            for (ind = 0U; ind < iters; ++ind)
                z = cfunc(&z);

            /*  Get the color corresponding to this pixel.                    */
            c = color(&z);

            /*  Write the color to the ppm file.                              */
            cvp_color_write_to_ppm(&c, &PPM);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the ppm file.                                                   */
    cvp_ppm_close(&PPM);
}
/*  End of cvp_iters_plot.                                                    */

#endif
/*  End of include guard.                                                     */
