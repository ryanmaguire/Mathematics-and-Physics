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
 *      This file only uses features available in C89. Something interesting  *
 *      to note, GCC ran this file more than twice as fast as the C99         *
 *      equivalent that is also in this directory. That file uses complex.h   *
 *      features from the C99 standard. Clang ran this file about 1.5 times   *
 *      as fast as the C99 version.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 23, 2021                                                  *
 ******************************************************************************/

/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc) platforms yield no warnings. */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  The fprintf and FILE data type are found here.                            */
#include <stdio.h>

/*  Needed for the square root function.                                      */
#include <math.h>

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

/*  For reasons completely beyond me, fputc doesn't seem to work correctly on *
 *  Windows 10. The problem seems to arise when too many colors are present   *
 *  in the PPM file. The rendered PPM file is completely corrupted and looks  *
 *  horrible. If the user is running Windows, use fprintf instead of fputc,   *
 *  and use the text-based PPM format instead of the binary based one. The    *
 *  text-based format ends up being around 4x larger than the binary format,  *
 *  but renders properly.                                                     */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fprintf(fp, "%u %u %u\n", c.red, c.green, c.blue);
}
/*  End of write_color.                                                       */

#else
/*  Everyone else (GNU, Linux, macOS, FreeBSD, etc.).                         */

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red,   fp);
    fputc(c.green, fp);
    fputc(c.blue,  fp);
}
/*  End of write_color.                                                       */

#endif
/*  End of #if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER).       */

/*  Struct for working with complex numbers.                                  */
struct complex_number {
    double real, imag;
};

/*  Function for subtracting two complex numbers.                             */
static struct complex_number
complex_subtract(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the sum.                                       */
    struct complex_number out;

    /*  Complex subtraction is done component-wise.                           */
    out.real = z.real - w.real;
    out.imag = z.imag - w.imag;
    return out;
}
/*  End of complex_subtract.                                                  */

/*  Function for multiplying two complex numbers.                             */
static struct complex_number
complex_multiply(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the product.                                   */
    struct complex_number prod;

    /*  Compute the product using the rule i^2 = -1.                          */
    prod.real = z.real*w.real - z.imag*w.imag;
    prod.imag = z.real*w.imag + z.imag*w.real;
    return prod;
}
/*  End of complex_multiply.                                                  */

/*  Function for dividing complex numbers.                                    */
static struct complex_number
complex_divide(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the quotient.                                  */
    struct complex_number quot;

    /*  The quotient z/w can be written as z * (1/w). Use this.               */
    double denom = 1.0 / (w.real*w.real + w.imag*w.imag);

    quot.real = (z.real*w.real + z.imag*w.imag)*denom;
    quot.imag = (z.imag*w.real - z.real*w.imag)*denom;
    return quot;
}
/*  End of complex_division.                                                  */

/*  Function for squaring a complex number.                                   */
static struct complex_number complex_square(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number z_sq;

    /*  Compute z*w with z = w.                                               */
    z_sq.real = z.real*z.real - z.imag*z.imag;
    z_sq.imag = 2.0*z.real*z.imag;
    return z_sq;
}
/*  End of complex_square.                                                    */

/*  Function for computing the distance between two complex numbers.          */
static double complex_dist(struct complex_number z, struct complex_number w)
{
    /*  Declare necessary variables.                                          */
    double dx, dy;

    /*  Use the Pythagorean formula to compute the distance.                  */
    dx = z.real - w.real;
    dy = z.imag - w.imag;
    return sqrt(dx*dx + dy*dy);
}
/*  End of complex_dist.                                                      */

/*  Function for computing the absolute value of a complex number.            */
static double complex_abs(struct complex_number z)
{
    /*  Use the Pythagorean formula and return.                               */
    return sqrt(z.real*z.real + z.imag*z.imag);
}
/*  End of complex_abs.                                                       */

/*  The Halley fractal we're drawing has the polynomial z^3 - 1.              */
static struct complex_number f(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute z^3, and then subtract 1 from the real part.                  */
    out.real = z.real*z.real*z.real - 3.0*z.real*z.imag*z.imag - 1.0;
    out.imag = 3.0*z.real*z.real*z.imag - z.imag*z.imag*z.imag;
    return out;
}

/*  The derivative of z^3 - 1 is 3z^2.                                        */
static struct complex_number f_prime(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute the square of z, and multiply real and imaginary part by 3.   */
    out.real = 3.0*(z.real*z.real - z.imag*z.imag);
    out.imag = 6.0*z.real*z.imag;
    return out;
}

/*  And the second derivative of z^3 - 1 is 6z.                               */
static struct complex_number f_double_prime(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Multiply the real and imaginary parts by 6 and return.                */
    out.real = 6.0*z.real;
    out.imag = 6.0*z.imag;
    return out;
}

/*  Function for computing the factor used in Halley's method.                */
static struct complex_number halley_factor(struct complex_number z)
{
    /*  Declare necessary variables.                                          */
    struct complex_number denom, numer, f_of_z, f_prime_of_z;
    struct complex_number f_double_prime_of_z, denom_a, denom_b;

    /*  Compute the factors and return the quotient.                          */
    f_of_z              = f(z);
    f_prime_of_z        = f_prime(z);
    f_double_prime_of_z = f_double_prime(z);

    /*  The numerator is f(z)f'(z).                                           */
    numer = complex_multiply(f_of_z, f_prime_of_z);

    /*  The denominator is f'(z)^2 - 0.5*f(z)f''(z).                          */
    denom_a = complex_square(f_prime_of_z);
    denom_b = complex_multiply(f_of_z, f_double_prime_of_z);
    denom_b.real *= 0.5;
    denom_b.imag *= 0.5;

    denom = complex_subtract(denom_a, denom_b);
    return complex_divide(numer, denom);
}
/*  End of halley_factor.                                                     */

/*  Function for drawing the Halley fractal for z^3 - 1.                      */
int main(void)
{
    /*  Declare variables for z (point in the plane) and f(z).                */
    struct complex_number z, f_of_z;

    /*  Variables for the real and imaginary parts of z.                      */
    double z_x, z_y;

    /*  The allowed error when searching for a root to z^3 - 1. This is the   *
     *  maximum value |f(z)| < EPS such that f(z) will be considered zero.    */
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

    /*  The Julia set of z^3 - 1 are points that don't converge. Draw these   *
     *  points black.                                                         */
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Precompute the three roots of z^3 - 1 for later. These are the three  *
     *  cubic roots of unity.                                                 */
    const struct complex_number root0 = {1.0, 0.0};
    const struct complex_number root1 = {-0.5,  0.866025403784};
    const struct complex_number root2 = {-0.5, -0.866025403784};

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
    FILE *fp = fopen("tmpl_halley_fractal_z3_minus_1_c89.ppm", "w");

    /*  If fopen fails it returns NULL. Check for this.                       */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file. For Windows users we'll use text  *
     *  based PPM, and for everyone else we'll use binary format.             */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

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

            /*  Compute z from the real and imaginary parts.                  */
            z.real = z_x;
            z.imag = z_y;

            /*  Reset the number of iterations to zero.                       */
            iters = 0x00U;

            /*  Compute f(z). If f(z) is already small, we started at a root  *
             *  and can skip Halley's method altogether.                      */
            f_of_z = f(z);

            /*  Perform Halley's method until we are close to a root, or      *
             *  perform too many iterations.                                  */
            while ((complex_abs(f_of_z) > EPS) && (iters < max_iters))
            {
                /*  Compute the next iteration of Halley's method.            */
                z = complex_subtract(z, halley_factor(z));

                /*  Update f(z) and the number of iterations used.            */
                f_of_z = f(z);
                ++iters;
            }
            /*  End of Halley's method.                                       */

            /*  Compute the color factor. This is used to give a              *
             *  dark-to-light gradient based on the number of iterations.     */
            color_factor = 1.0 - (double)iters * rcpr_max_iters;

            /*  Color the pixel based on which root the result is closest to. */
            if (complex_dist(z, root0) < toler)
                current_color = scale_color(blue, color_factor);
            else if (complex_dist(z, root1) < toler)
                current_color = scale_color(green, color_factor);
            else if (complex_dist(z, root2) < toler)
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

