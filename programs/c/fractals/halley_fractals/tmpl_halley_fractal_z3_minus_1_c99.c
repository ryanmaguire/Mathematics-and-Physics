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
 *      Draw the Halley fractal for the polynomial z^3 - 1.                   *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 *      This file uses C99 features (complex.h).                              *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 22, 2021                                                  *
 ******************************************************************************/

/*  The fprintf and FILE data type are found here.                            */
#include <stdio.h>

/*  Complex data types and complex functions found here.                      */
#include <complex.h>

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Function for scaling the intensity of a color by a real number.           */
static struct color scale_color(struct color c, double t)
{
    /*  Declare a variable for the output color.                              */
    struct color out;

    /*  Scale the components of the color by the real number and return.      */
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Function for adding a color to a PPM file.                                */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

/*  The Halley fractal we're drawing has the polynomial z^3 - 1.              */
static complex double f(complex double z)
{
    return z*z*z - 1.0;
}

/*  The derivative of z^3 - 1 is 3z^2.                                        */
static complex double f_prime(complex double z)
{
    return 3.0*z*z;
}

/*  And the second derivative of z^3 - 1 is 6z.                               */
static complex double f_double_prime(complex double z)
{
    return 6.0*z;
}

/*  Function for computing the factor used in Halley's method.                */
static complex double halley_factor(complex double z)
{
    /*  Declare necessary variables.                                          */
    complex double denom, numer, f_of_z, f_prime_of_z, f_double_prime_of_z;

    /*  Compute the factors and return the quotient.                          */
    f_of_z              = f(z);
    f_prime_of_z        = f_prime(z);
    f_double_prime_of_z = f_double_prime(z);

    numer = 2.0*f_of_z*f_prime_of_z;
    denom = 2.0*f_prime_of_z*f_prime_of_z - f_of_z*f_double_prime_of_z;
    return numer / denom;
}
/*  End of halley_factor.                                                     */

/*  Function for drawing the Halley fractal for z^3 - 1.                      */
int main(void)
{
    /*  Declare variables for z (point in the plane) and f(z).                */
    complex double z, f_of_z;

    /*  Two doubles for the real and imaginary parts of the complex number z. */
    double z_x, z_y;

    /*  The allowed error when searching for a root to z^3 - 1. This is the   *
     *  maximum value |f(z)| < EPS such that f(z) will be considered a root.  */
    const double EPS = 1.0E-6;

    /*  The allowed tolerance for a root. This is the maximum value |z-z0|,   *
     *  where z0 is a root, such that z will be consider equal to z0.         */
    const double toler = 1.0E-2;

    /*  The width of the PPM, in pixels.                                      */
    const unsigned int width = 2048U;

    /*  The height of the PPM file, in pixels.                                */
    const unsigned int height = 2048U;

    /*  The maximum number of iterations allowed in Halley's method. This     *
     *  value is declared as an unsigned char since it will not allowed to be *
     *  greater than 255. This is because the color struct uses unsigned      *
     *  char's for the colors, and the max_iter variable will be used to      *
     *  create a gradient of color.                                           */
    const unsigned char max_iters = 0x10U;

    /*  This factor is used for computing the gradient in color.              */
    const double rcpr_max_iters = 1.0 / (double)max_iters;

    /*  The values for the rectangular region we're plotting. The rectangle   *
     *  [xmin, xmax] x [ymin, ymax] will be drawn.                            */
    const double x_min = -4.0;
    const double x_max =  4.0;
    const double y_min = -4.0;
    const double y_max =  4.0;

    /*  These values are used to convert from pixel on the PPM to the         *
     *  corresponding point on the plane.                                     */
    const double x_factor = (x_max - x_min) / (double)(width - 1U);
    const double y_factor = (y_max - y_min) / (double)(height - 1U);

    /*  z^3 - 1 has three roots, so declare 3 colors to distinguish which     *
     *  root occurred as a result of Halley's method.                         */
    const struct color red   = {0xFFU, 0x00U, 0x00U};
    const struct color green = {0x00U, 0xFFU, 0x00U};
    const struct color blue  = {0x00U, 0x00U, 0xFFU};

    /*  The Julia set of z^3 - 1 is points that don't converge. Draw these    *
     *  points black.                                                         */
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Precompute the three roots of z^3 - 1 for later. These are the three  *
     *  cubic roots of unity.                                                 */
    const complex double root0 =  1.0;
    const complex double root1 = -0.5 + 0.866025403784*(complex double)I;
    const complex double root2 = -0.5 - 0.866025403784*(complex double)I;

    /*  Declare a variable for creating a gradient in color. The gradient     *
     *  indicates how many iterations it takes to converge. Darker values     *
     *  require more iterations, lighter values require less.                 */
    double color_factor;

    /*  Variables for looping over the PPM file.                              */
    unsigned int x, y;

    /*  Variable for counting the number of iterations of Halley's method.    */
    unsigned char iters;

    /*  Variable for computing the color of a given pixel.                    */
    struct color current_color;

    /*  Open a PPM file and give it write permissions.                        */
    FILE *fp = fopen("tmpl_halley_fractal_z3_minus_1_c99.ppm", "w");

    /*  If fopen fails it returns NULL. Check for this.                       */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble of the PPM to the file.                            */
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    /*  Loop over all of the y-pixels.                                        */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the current y-coordinate.                                 */
        z_y = y_max - (double)y * y_factor;

        /*  Loop over all of the x-pixels.                                    */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the current x-coordinate.                             */
            z_x = x_min + (double)x * x_factor;

            /*  Compute the complex number x + iy from the two real numbers.  */
            z = z_x + z_y*(complex double)I;

            /*  Reset the number of iterations to zero.                       */
            iters = 0x00U;

            /*  Compute f(z). If f(z) is already small, we started at a root  *
             *  and can skip Halley's method altogether.                      */
            f_of_z = f(z);

            /*  Perform Halley's method until we are close to a root, or      *
             *  perform too many iterations.                                  */
            while ((cabs(f_of_z) > EPS) && (iters < max_iters))
            {
                /*  Compute the next iteration of Halley's method.            */
                z = z - halley_factor(z);

                /*  Update f(z) and the number of iterations used.            */
                f_of_z = f(z);
                ++iters;
            }
            /*  End of Halley's method.                                       */

            /*  Compute the color factor. This is used to give a              *
             *  dark-to-light gradient based on the number of iterations.     */
            color_factor = 1.0 - (double)iters * rcpr_max_iters;

            /*  Color the pixel based on which root the result is closest to. */
            if (cabs(z - root0) < toler)
                current_color = scale_color(blue, color_factor);
            else if (cabs(z - root1) < toler)
                current_color = scale_color(green, color_factor);
            else if (cabs(z - root2) < toler)
                current_color = scale_color(red, color_factor);

            /*  And if we didn't converge to a root, color the pixel black.   */
            else
                current_color = black;

            /*  Write the current color to the PPM file.                      */
            write_color(fp, current_color);
        }
        /*  End of for-loop for the x-coordinate.                             */
    }
    /*  End of the for-loop for the y-coordinate.                             */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
