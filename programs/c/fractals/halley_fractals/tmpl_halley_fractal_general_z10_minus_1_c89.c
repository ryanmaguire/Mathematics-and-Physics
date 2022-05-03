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
 *      Use the algorithm by Hubbard, Schleicher, and Sutherland to find all  *
 *      roots of a complex polynomial, rather than precomputing them. The     *
 *      Halley fractal for z^10 - 1 is then drawn. This can be changed to any *
 *      polynomial of degree less than or equal to 14.                        *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 29, 2021                                                  *
 ******************************************************************************/

/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc.) platforms yield no warnings.*/
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  The fopen, fprintf, and FILE data type are here.                          */
#include <stdio.h>

/*  Square root and other basic math functions.                               */
#include <math.h>

/*  Struct for working with complex numbers.                                  */
struct complex_number {
    double real, imag;
};

/*  Function for computing the absolute value of a complex number.            */
static double complex_abs(struct complex_number z)
{
    /*  Use the Pythagorean formula and return.                               */
    return sqrt(z.real*z.real + z.imag*z.imag);
}
/*  End of complex_abs.                                                       */

/*  Function for computing the distance between two complex numbers.          */
static double complex_dist(struct complex_number z, struct complex_number w)
{
    /*  Declare necessary variables.                                          */
    const double dx = z.real - w.real;
    const double dy = z.imag - w.imag;

    /*  Use the Pythagorean formula and return.                               */
    return sqrt(dx*dx + dy*dy);
}
/*  End of complex_dist.                                                      */

/*  Function for adding complex numbers.                                      */
static struct complex_number
complex_add(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Complex addition is done component-wise.                              */
    out.real = z.real + w.real;
    out.imag = z.imag + w.imag;
    return out;
}
/*  End of complex_add.                                                       */

/*  Function for subtracting complex numbers.                                 */
static struct complex_number
complex_subtract(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Complex subtraction is done component-wise.                           */
    out.real = z.real - w.real;
    out.imag = z.imag - w.imag;
    return out;
}
/*  End of complex_subtract.                                                  */

/*  Function for multiplying complex numbers.                                 */
static struct complex_number
complex_multiply(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute the product using the rule i^2 = -1.                          */
    out.real = z.real*w.real - z.imag*w.imag;
    out.imag = z.real*w.imag + z.imag*w.real;
    return out;
}
/*  End of complex_multiply.                                                  */

/*  Function for squaring a complex number.                                   */
static struct complex_number complex_square(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute z*w with z = w.                                               */
    out.real = z.real*z.real - z.imag*z.imag;
    out.imag = 2.0*z.real*z.imag;
    return out;
}
/*  End of complex_square.                                                    */

/*  Function for dividing complex numbers.                                    */
static struct complex_number
complex_divide(struct complex_number z, struct complex_number w)
{
    /*  Declare a variable for the quotient.                                  */
    struct complex_number out;

    /*  Compute using z / w = z * (1/w), and use the formula for the          *
     *  reciprocal of a complex number.                                       */
    const double denom = 1.0 / (w.real*w.real + w.imag*w.imag);
    out.real = (z.real*w.real + z.imag*w.imag)*denom;
    out.imag = (z.imag*w.real - z.real*w.imag)*denom;
    return out;
}
/*  End of complex_divide.                                                    */

/*  Function for scaling a complex number a real one.                         */
static struct complex_number
complex_scale(struct complex_number z, double a)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Multiply the real and imaginary parts by a and return.                */
    out.real = a*z.real;
    out.imag = a*z.imag;
    return out;
}
/*  End of complex_scale.                                                     */

/*  Function for evaluating a polynomial at a complex number z given the      *
 *  coefficients of the polynomial. This uses Horner's method.                */
static struct complex_number
poly_eval(struct complex_number z, struct complex_number *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    struct complex_number out;
    unsigned int n;

    /*  Initialize out to the coefficient of z^deg.                           */
    out = arr[0];

    /*  Loop over the coefficients and apply Horner's method.                 */
    for (n = 1U; n <= deg; ++n)
        out = complex_add(complex_multiply(z, out), arr[n]);

    return out;
}
/*  End of poly_eval.                                                         */

/*  Function for computing the derivative of a polynomial using               *
 *  Horner's method.                                                          */
static struct complex_number
poly_deriv_eval(struct complex_number z,
                struct complex_number *arr,
                unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    struct complex_number out;
    const double factor = (double)deg;
    unsigned int n;

    /*  Intialize the output to the coefficient of z^deg times deg. This is   *
     *  because the derivative of z^deg is deg*z^(deg-1).                     */
    out = complex_scale(arr[0], factor);

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1U; n < deg; ++n)
    {
        out = complex_multiply(z, out);
        out = complex_add(out, complex_scale(arr[n], factor));
    }

    return out;
}
/*  End of poly_deriv_eval.                                                   */

/*  Compute the second derivative of a polynomial using Horner's method.      */
static struct complex_number
poly_deriv2_eval(struct complex_number z,
                 struct complex_number *arr,
                 unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    struct complex_number out;
    const double factor = (double)deg * (double)(deg - 1U);
    unsigned int n;

    /*  Initialize the output.                                                */
    out = complex_scale(arr[0], factor);

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1U; n < deg - 1U; ++n)
    {
        out = complex_multiply(z, out);
        out = complex_add(out, complex_scale(arr[n], factor));
    }

    return out;
}
/*  End of poly_deriv2_eval.                                                  */

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

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

/*  Function for scaling the intensitity of a color by a real number.         */
static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Function for computing the factor that occurs in Halley's method.         */
static struct complex_number
halley_factor(struct complex_number z,
              struct complex_number *arr,
              unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    const struct complex_number f_z        = poly_eval(z, arr, deg);
    const struct complex_number f_deriv_z  = poly_deriv_eval(z, arr, deg);
    const struct complex_number f_deriv2_z = poly_deriv2_eval(z, arr, deg);
    struct complex_number numer, denom, denoma, denomb;

    /*  The numerator is f(z)f'(z) and the denominator is                     *
     *  f'(z)^2 - 0.5 f(z)f''(z). Compute this.                               */
    numer  = complex_multiply(f_z, f_deriv_z);
    denoma = complex_square(f_deriv_z);
    denomb = complex_scale(complex_multiply(f_z, f_deriv2_z), 0.5);
    denom  = complex_subtract(denoma, denomb);
    return complex_divide(numer, denom);
}
/*  End of halley_factor.                                                     */

/*  Function for drawing the Halley fractal for z^10 - 1.                     */
int main(void)
{
    /*  Variable for the width of the PPM file.                               */
    const unsigned int width = 1024U;

    /*  And a variable for the height of the PPM.                             */
    const unsigned int height = 1024U;

    /*  Maximum number of iterations allowed in Halley's method and the       *
     *  maximum number of iterations allowed in the                           *
     *  Hubbard-Schleicher-Sutherland algorithm for finding the roots.        */
    const unsigned char MaxIters = 0x20U;

    /*  The coefficients of the polynomial we're using. This is z^10 - 1.     */
    struct complex_number arr[11] = {
        { 1.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        { 0.0, 0.0},
        {-1.0, 0.0}
    };

    /*  Variable for the roots of this polynomial. The fundamental theorem of *
     *  algebra tells us there are at most 10 since the polynomial is degree  *
     *  10. For z^10 - 1, there are exactly 10.                               */
    struct complex_number roots[sizeof(arr)/sizeof(arr[0]) - 1U];

    /*  Variable for the degree of the polynomial.                            */
    const unsigned int deg = sizeof(roots) / sizeof(roots[0]);

    /*  Variable for storing f(z) as we loop over points in the plane.        */
    struct complex_number f_z;

    /*  Values for the min and max of the x and y axes. The rectangular       *
     *  region [x_min, x_max] x [y_min, y_max] will be plotted.               */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  Factor used in the root-finding algorithm. See the paper by           *
     *  Hubbard, Schleicher, and Sutherland for a description of these values.*/
    const double s_double = ceil(0.26632*log((double)deg));
    const double N_double = ceil(8.32547*(double)deg*log((double)deg));

    const unsigned int s = (unsigned int)s_double;
    const unsigned int N = (unsigned int)N_double;

    /*  These factors also occur in the root-finding algorithm.               */
    const double factor_1     = 2.4142135623730951;
    const double factor_2     = ((double)deg - 1.0) / (double)deg;
    const double theta_factor = 6.283185307179586 / N_double;
    const double r_factor     = 0.25 / s_double;

    /*  Factors for converting from a pixel to a point in the plane.          */
    const double factor_x = (x_max - x_min)/(double)(width - 1U);
    const double factor_y = (y_max - y_min)/(double)(height - 1U);

    /*  Factor for giving the image a gradient in color. The darker colors    *
     *  will represent points that required more iterations to converge.      */
    double color_factor = 1.0 / (double)MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned char iters;
    unsigned int ind, x, y, ell;

    /*  Variables for the tolerance of finding a root.                        */
    const double toler = 1.0E-2;
    const double EPS   = 1.0E-8;

    /*  Variables for the real and imaginary parts of a complex number.       */
    double z_x, z_y;
    struct complex_number z;

    /*  Scale factor for giving a gradient to the image.                      */
    double scale;

    /*  Variable for storing the number of roots found via the algorithm.     */
    unsigned int n_roots = 0U;

    /*  More variables needed for the algorithm.                              */
    double r, theta, min, temp;

    /*  Variable for computing the color of a given pixel.                    */
    struct color current_color;

    /*  Points that don't converge are colored black.                         */
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Various colors for up to 14 roots.                                    */
    const struct color colors[14] = {
        {0xFFU, 0x00U, 0x1FU},  /*  Red.           */
        {0x00U, 0xFFU, 0x1FU},  /*  Green.         */
        {0x00U, 0x1FU, 0xFFU},  /*  Blue.          */
        {0xFFU, 0xFFU, 0x33U},  /*  Yellow.        */
        {0x80U, 0xD4U, 0xFFU},  /*  Light Blue.    */
        {0xFFU, 0x1DU, 0xCCU},  /*  Magenta.       */
        {0x00U, 0x80U, 0x80U},  /*  Teal.          */
        {0xFFU, 0x00U, 0xFFU},  /*  Purple.        */
        {0xFFU, 0x55U, 0x00U},  /*  Orange.        */
        {0x4DU, 0xFFU, 0xC3U},  /*  Turquoise.     */
        {0x00U, 0x80U, 0x6AU},  /*  Pine.          */
        {0xFFU, 0xBFU, 0xB3U},  /*  Melon.         */
        {0xFFU, 0xB3U, 0xE6U},  /*  Mauve.         */
        {0x66U, 0x43U, 0x66U}   /*  Midnight blue. */
    };

    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp = fopen("tmpl_halley_fractal_general_z10_minus_1_c89.ppm", "w");

    /*  Check if fopen failed.                                                */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Perform the Hubbard-Schleicher-Sutherland algorithm. First, loop      *
     *  over all circles in the algorithm.                                    */
    for (x = 0U; x < s; ++x)
    {
        /*  There are at most deg roots. If we found this many, we can quit   *
         *  the algorithm.                                                    */
        if (n_roots >= deg)
            break;

        /*  The radius of the circle we're inspecting.                        */
        r = factor_1 + pow(factor_2, (2.0*(double)x + 1.0) * r_factor);

        /*  Loop over the angles on this circle.                              */
        for (y = 0U; y < N; ++y)
        {
            /*  Again, quit if we found deg many roots.                       */
            if (n_roots >= deg)
                break;

            /*  Compute the angle.                                            */
            theta = theta_factor * (double)y;

            /*  Get the complex number r exp(i theta).                        */
            z.real = r*cos(theta);
            z.imag = r*sin(theta);

            /*  Compute f(z) and set the number of iterations back to zero.   */
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Halley's Method.       */
            while ((complex_abs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perform Halley's Method on the polynomial.                */
                z = complex_subtract(z, halley_factor(z, arr, deg));

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }
            /*  End of Halley's method.                                       */

            /*  If |f(z)| < EPS, we found a root. Check if we already found   *
             *  this one.                                                     */
            if (complex_abs(f_z) < EPS)
            {
                /*  If we haven't found a root yet, add this to our list.     */
                if (n_roots == 0U)
                {
                    n_roots += 1;
                    roots[0] = z;
                }

                /*  If we've already found a root, check that this isn't a    *
                 *  duplicate before adding to our list.                      */
                else
                {
                    /*  Compute the distances from this newly found point to  *
                     *  the roots we've already found.                        */
                    min = complex_dist(z, roots[0]);
                    for (ell = 1U; ell < n_roots; ++ell)
                    {
                        temp = complex_dist(z, roots[ell]);
                        if (temp < min)
                            min = temp;
                    }

                    /*  If this new point is more than toler away from all    *
                     *  the others, it's a new root. Add it to the list.      */
                    if (min >= toler)
                    {
                        roots[n_roots] = z;
                        n_roots += 1;
                    }
                }
                /*  End of if (n_roots == 0U).                                */
            }
            /*  End of if (complex_abs(f_z) < EPS).                           */
        }
        /*  End of y for-loop.                                                */
    }
    /*  End of x for-loop.                                                    */

    /*  If we didn't allow for enough iterations of Halley's method, or if    *
     *  there is a bug, it is possible that we didn't find any roots. Abort   *
     *  the computation if this is the case.                                  */
    if (n_roots == 0)
    {
        puts("Failed to find the roots. Aborting.");
        fclose(fp);
        return -1;
    }

    /*  Write the preamble to the PPM file. For Windows users we'll use text  *
     *  based PPM, and for everyone else we'll use binary format.             */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

    /*  Loop over the y pixels.                                               */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the y-coordinate in the plane corresponding to this pixel.*/
        z_y = y_max - (double)y * factor_y;

        /*  Loop over the x pixels.                                           */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the x coordinate.                                     */
            z_x = x_min + (double)x * factor_x;

            /*  Set z to x + iy.                                              */
            z.real = z_x;
            z.imag = z_y;

            /*  Evaluate the polynomial at z and reset iters to zero.         */
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Halley's method.       */
            while ((complex_abs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perform Halley's Method on the polynomial f.              */
                z = complex_subtract(z, halley_factor(z, arr, deg));

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }
            /*  End of Halley's Method.                                       */

            /*  Find which roots the final iteration is closest too.          */
            min = complex_dist(z, roots[0]);
            ind = 0U;

            /*  Find if we converge to a root or not.                         */
            for (ell = 1U; ell < n_roots; ++ell)
            {
                temp = complex_dist(z, roots[ell]);
                if (temp < min)
                {
                    min = temp;
                    ind = ell;
                }
            }

            /*  If we didn't converge to a root, color the pixel black.       */
            if (min > toler)
                current_color = black;

            /*  Otherwise, color the pixel corresponding to the root.         */
            else
            {
                scale = 1.0 - color_factor*(double)iters;
                current_color = scale_color(colors[ind], scale);
            }

            /*  Write the color to the PPM file.                              */
            write_color(fp, current_color);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

