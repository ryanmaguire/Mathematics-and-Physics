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
 *      Creates the Newton fractal for f(z) = -1 + z^3.                       *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/21                                                        *
 ******************************************************************************/

/*  Routines for creating Newton fractals provided here.                      */
#include "nf.h"

/*  puts function for printing messages given here.                           */
#include <stdio.h>

/*  The function we're plotting the Newton fractal for. f(z) = -1 + z^3.      */
NF_INLINE struct nf_complex
f(const struct nf_complex *z)
{
    /*  First compute z^2, then z*z^2, then z*z^2 - 1.                        */
    struct nf_complex out = nf_complex_square(z);
    nf_complex_multiplyby(&out, z);
    out.real -= 1.0;
    return out;
}

/*  The derivative of the polynomial. f'(z) = 3z^2.                           */
NF_INLINE struct nf_complex
fp(const struct nf_complex *z)
{
    /*  Compute the square of z and scale the real and imaginary parts.       */
    struct nf_complex out = nf_complex_square(z);
    nf_complex_multiplyby_real(3.0, &out);
    return out;
}

/*  Function for creating the Newton fractal for f(z) = -1 + z^3.             */
int main(void)
{
    /*  Variables for looping over the x and y coordinates of the file.       */
    unsigned int x, y;

    /*  Variable for counting how many iterations of Newton's method needed.  */
    unsigned int iters;

    /*  Scale factor for darkening colors based on the number of iterations.  */
    double scale;

    /*  Complex number corresponding to a given pixel in the PPM file.        */
    struct nf_complex z;

    /*  Color struct to color the point z in the plane.                       */
    struct nf_color c;

    /*  Create the PPM file.                                                  */
    struct nf_ppm ppm = nf_ppm_create("newton_fractal_z_cubed_minus_one.ppm");

    /*  The previous function calls fopen, which return NULL on failure.      */
    if (!ppm.fp)
    {
        /*  Print an error message and abort the computation.                 */
        puts("Error: nf_ppm_create returned NULL for the FILE pointer.");
        return -1;
    }

    /*  Otherwise initialize the ppm file with the default preamble.          */
    nf_ppm_init(&ppm);

    /*  Loop through the y coordinates of the PPM file.                       */
    for (y = 0U; y < nf_setup_ysize; ++y)
    {
        /*  Convert the given y component of the pixel to the imaginary part. */
        const double imag = nf_setup_ymax - nf_setup_py_factor*(double)y;

        /*  Loop through the x coordinates of the PPM file.                   */
        for (x = 0U; x < nf_setup_xsize; ++x)
        {
            /*  Convert the x component of the pixel to the real part.        */
            const double real = nf_setup_xmin + nf_setup_px_factor*(double)x;

            /*  Treat the point (real, imag) as a complex number.             */
            z.real = real;
            z.imag = imag;

            /*  Perform Newton's method with guess z0 = z.                    */
            iters = nf_newton(f, fp, &z);

            /*  The only root with positive real part is z = 1. Color blue.   */
            if (z.real > 0.0)
                c = nf_blue;

            /*  The only root with positive imaginary part is (-1+sqrt(3)i)/2.*/
            else if (z.imag > 0.0)
                c = nf_red;

            /*  The only root with negative imaginary part is (-1-sqrt(3)i)/2.*/
            else
                c = nf_green;

            /*  Darken the color based on the number of iterations needed.    */
            scale = (double)(nf_setup_max_iters - iters)*nf_setup_color_scale;

            /*  Scale the color by the scale factor to darken it.             */
            nf_color_scaleby(&c, scale);

            /*  And lastly, write the color to the PPM file.                  */
            nf_color_write_to_ppm(&c, &ppm);
        }
        /*  End of for loop for the x-coordinate.                             */
    }
    /*  End of for loop for the y-coordinate.                                 */

    /*  Close the PPM file and return.                                        */
    nf_ppm_close(&ppm);
    return 0;
}
/*  End of main.                                                              */
