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
 *      This file uses C99 extensions (complex.h) and DOES NOT compile using  *
 *      Microsoft's C library (MSVC is NOT C99 compliant). There is a C89     *
 *      version of this file that has successfully been tested on Windows 10  *
 *      using both MSVC and Clang. GNU's C library, and Apple's, handle this  *
 *      file just fine.                                                       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 26, 2021                                                  *
 ******************************************************************************/

/*  The fopen, fprintf, and FILE data type are here.                          */
#include <stdio.h>

/*  Square root and other basic math functions.                               */
#include <math.h>

/*  Complex variables and basic complex functions.                            */
#include <complex.h>

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Function for evaluating a polynomial at a complex number z given the      *
 *  coefficients of the polynomial. This uses Horner's method.                */
static complex double
poly_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    unsigned int n;

    /*  Initialize out to the coefficient of z^deg.                           */
    out = arr[0];

    /*  Loop over the coefficients and apply Horner's method.                 */
    for (n = 1U; n <= deg; ++n)
        out = z*out + arr[n];

    return out;
}
/*  End of poly_eval.                                                         */

/*  Function for computing the derivative of a polynomial using               *
 *  Horner's method.                                                          */
static complex double
poly_deriv_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    const double factor = (double)deg;
    unsigned int n;

    /*  Intialize the output to the coefficient of z^deg times deg. This is   *
     *  because the derivative of z^deg is deg*z^(deg-1).                     */
    out = factor*arr[0];

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1U; n < deg; ++n)
        out = z*out + factor*arr[n];

    return out;
}
/*  End of poly_deriv_eval.                                                   */

/*  Compute the second derivative of a polynomial using Horner's method.      */
static complex double
poly_deriv2_eval(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    complex double out;
    const double factor = (double)deg * ((double)deg - 1.0);
    unsigned int n;

    /*  Initialize the output.                                                */
    out = factor*arr[0];

    /*  Loop over the coefficients and perform Horner's method.               */
    for (n = 1U; n < deg - 1U; ++n)
        out = z*out + factor*arr[n];

    return out;
}
/*  End of poly_deriv2_eval.                                                  */

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red,   fp);
    fputc(c.green, fp);
    fputc(c.blue,  fp);
}
/*  End of write_color.                                                       */

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
static complex double
halley_factor(complex double z, complex double *arr, unsigned int deg)
{
    /*  Declare necessary variables.                                          */
    const complex double f_of_z              = poly_eval(z, arr, deg);
    const complex double f_prime_of_z        = poly_deriv_eval(z, arr, deg);
    const complex double f_double_prime_of_z = poly_deriv2_eval(z, arr, deg);
    complex double numer, denom;

    /*  The numerator is f(z)f'(z) and the denominator is                     *
     *  f'(z)^2 - 0.5 f(z)f''(z). Compute this.                               */
    numer = f_of_z * f_prime_of_z;
    denom = f_prime_of_z*f_prime_of_z - 0.5*f_of_z*f_double_prime_of_z;
    return numer / denom;
}
/*  End of halley_factor.                                                     */

/*  Function for drawing the Halley fractal for z^10 - 1.                     */
int main(void)
{
    /*  Variable for the width of the PPM file.                               */
    const unsigned int width = 2048U;

    /*  And a variable for the height of the PPM.                             */
    const unsigned int height = 2048U;

    /*  Maximum number of iterations allowed in Halley's method and the       *
     *  maximum number of iterations allowed in the                           *
     *  Hubbard-Schleicher-Sutherland algorithm for finding the roots.        */
    const unsigned char MaxIters = 0x20U;

    /*  The coefficients of the polynomial we're using. This is z^10 - 1.     */
    complex double arr[11] = {
        1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0
    };

    /*  Variable for the roots of this polynomial. The fundamental theorem of *
     *  algebra tells us there are at most 10 since the polynomial is degree  *
     *  10. For z^10 - 1, there are exactly 10.                               */
    complex double roots[sizeof(arr)/sizeof(arr[0]) - 1U];

    /*  Variable for the degree of the polynomial.                            */
    const unsigned int deg = sizeof(roots) / sizeof(roots[0]);

    /*  Variable for storing f(z) as we loop over points in the plane.        */
    complex double f_z;

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
    double color_scale = 1.0 / (double)MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned char iters;
    unsigned int ind, x, y, ell;

    /*  Variables for the tolerance of finding a root.                        */
    const double toler = 1.0E-4;
    const double EPS   = 1.0E-8;

    /*  Variables for the real and imaginary parts of a complex number.       */
    double z_x, z_y;
    complex double z;

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
    FILE *fp = fopen("tmpl_halley_fractal_general_z10_minus_1_c99.ppm", "w");

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
            z = r * (cos(theta) + (complex double)_Complex_I*sin(theta));

            /*  Compute f(z) and set the number of iterations back to zero.   */
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Halley's Method.       */
            while ((cabs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perform Halley's Method on the polynomial.                */
                z = z - halley_factor(z, arr, deg);

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }
            /*  End of Halley's method.                                       */

            /*  If |f(z)| < EPS, we found a root. Check if we already found   *
             *  this one.                                                     */
            if (cabs(f_z) < EPS)
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
                    min = cabs(z - roots[0]);
                    for (ell = 1U; ell < n_roots; ++ell)
                    {
                        temp = cabs(z - roots[ell]);
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
            /*  End of if (cabs(f_z) < EPS).                                  */
        }
        /*  End of y for-loop.                                                */
    }
    /*  End of x for-loop.                                                    */

    /*  If we didn't allow for enough iterations of Halley's method, or if    *
     *  there is a bug, it is possible that we didn't find any roots. Abort   *
     *  the computation if this is the case.                                  */
    if (n_roots == 0U)
    {
        puts("Failed to find the roots. Aborting.");
        fclose(fp);
        return -1;
    }

    /*  Write the preamble to the PPM file.                                   */
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

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
            z = z_x + (complex double)_Complex_I*z_y;

            /*  Evaluate the polynomial at z and reset iters to zero.         */
            f_z = poly_eval(z, arr, deg);
            iters = 0x00U;

            /*  Allow MaxIters number of iterations of Halley's method.       */
            while ((cabs(f_z) > EPS) && (iters < MaxIters))
            {
                /*  Perform Halley's Method on the polynomial f.              */
                z = z - halley_factor(z, arr, deg);

                /*  Update f_z and increment iters.                           */
                f_z = poly_eval(z, arr, deg);
                ++iters;
            }
            /*  End of Halley's method.                                       */

            /*  Find which roots the final iteration is closest too.          */
            min = cabs(z - roots[0]);
            ind = 0U;

            /*  Find if we converge to a root or not.                         */
            for (ell = 1U; ell < n_roots; ++ell)
            {
                temp = cabs(z - roots[ell]);
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
                scale = 1.0 - color_scale*(double)iters;
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

