/******************************************************************************
 *                                 LICENSE                                    *
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
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/02/13                                                        *
 ******************************************************************************
 *  This code creates a Halley fractal for any polynomial up to degree 14.    *
 *  If you add more colors, you can have a higher degree. It works based on   *
 *  the ideas described in "How to find all roots of complex polynomials by   *
 *  Newton's method" by John Hubbard, Dierk Schleicher, and Scott Sutherland. *
 *  This algorithm finds the roots, and then Halley's method is used to       *
 *  create a Halley fractal. This code has been greatly generalized and made  *
 *  C89/C90 compliant in my other project, libtmpl. The code presented here   *
 *  requires C99 features, in particular complex.h.                           *
 *                                                                            *
 *  NOTE:                                                                     *
 *      As of this writing, Microsoft's C library does not support C99        *
 *      features, and does not implement complex numbers according to the     *
 *      standard. Because of this, this file will not compile on windows      *
 *      unless you use a different C library.                                 *
 ******************************************************************************/

/*  fprintf and fputc are found here.                                         */
#include <stdio.h>

/*  cos and sin found here.                                                   */
#include <math.h>

/*  Complex numbers found here.                                               */
#include <complex.h>

/******************************************************************************
 ******************************************************************************
 *                          Begin User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  The number of pixels in the x and y axes.                                 */
static const int size = 1024;

/*  The coefficients of the polynomial. The zeroth coefficient is for z^deg   *
 *  and the last coefficient is the constant term.                            */
static const complex double coeffs[] = {
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0
};

/*  Values for the min and max of the x and y axes.                           */
static const double x_min = -3.0;
static const double x_max =  3.0;
static const double y_min = -3.0;
static const double y_max =  3.0;

/******************************************************************************
 ******************************************************************************
 *                            End User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  Maximum number of iterations for Halley's method. This must be            *
 *  less than 255, otherwise we'll run out of colors.                         */
static const unsigned int max_iters = 24;

/*  Maximum number of iterations allowed before giving up on the root finding *
 *  algorithm. If no roots are found, the computation aborts.                 */
static const unsigned int root_finder_max_iter = 64;

/*  The degree of the polynomial the user selected.                           */
#define DEG (sizeof(coeffs)/sizeof(coeffs[0]) - 1U)

/*  Tolerance factor for finding a root.                                      */
static const double root_toler = 1.0E-8;

/*  Tolerance for the distance between two points to be considered distinct.  */
static const double dist_toler = 1.0E-6;

/*  A constant for pi. Some implementations include pi as M_PI, but we'll     *
 *  define it here.                                                           */
static const double PI = 3.14159265358979323846264338327950288419716;

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/*  Evaluates the user-specified polynomial at a complex number.              */
static complex double poly_eval(complex double z)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Initialize the output to a_{0}.                                       */
    complex double out = coeffs[0];

    /*  Compute the polynomial via Horner's method.                           */
    for (n = 1U; n <= DEG; ++n)
        out = z*out + coeffs[n];

    return out;
}
/*  End of poly_eval.                                                         */

/*  Evaluates the derivative of the user-specified polynomial at a complex    *
 *  number.                                                                   */
static complex double poly_prime_eval(complex double z)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Initialize the output to deg * a_{0}.                                 */
    complex double out = DEG*coeffs[0];

    /*  Compute the derivative of the polynomial via Horner's method.         */
    for (n = 1U; n < DEG; ++n)
        out = z*out + (DEG - n)*coeffs[n];

    return out;
}
/*  End of poly_prime_eval.                                                   */

/*  Computes the second derivative of the polynomial.                         */
static complex double poly_double_prime_eval(complex double z)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Initialize the output to deg * (deg-1) * a_{0}.                       */
    complex double out = DEG*(DEG-1U)*coeffs[0];

    /*  Compute the second derivative of the polynomial via Horner's method.  */
    for (n = 1U; n < DEG - 1U; ++n)
        out = z*out + (DEG - n)*(DEG - n - 1U)*coeffs[n];

    return out;
}
/*  End of poly_double_prime_eval.                                            */

/*  Computes all of the roots of the input polynomial. The integer it returns *
 *  is the number of roots. The roots are stored in the pointer roots.        */
static unsigned int get_roots(unsigned int deg, complex double *roots)
{
    complex double p, f_p, df_p;
    unsigned int m, n, ell, iter, n_roots;
    double r, theta, min, temp;

    /*  To avoid float conversion, cast _Complex_I to double precision.       */
    const complex double dbl_I = (complex double)_Complex_I;

    /*  These special values are from the HSS paper.                          */
    const double s = ceil(0.26632*log(deg));
    const double N = ceil(8.32547*deg*log(deg));
    const double factor_1 = 1.0 + sqrt(2.0);
    const double factor_2 = (deg - 1.0) / deg;
    const double angle_factor = 2.0*PI / N;

    /*  Check if the input pointer is NULL. This will be treated as a constant*
     *  polynomial and we will say it has zero roots.                         */
    if (roots == NULL)
        return 0U;

    /*  Similarly, if the degree is zero there are no roots (ignoring the     *
     *  zero polynomial which has infinitely many roots).                     */
    if (deg == 0U)
        return 0U;

    /*  Initialize the number of roots to zero.                               */
    n_roots = 0;

    /*  Loop over the circles specified in the HSS paper.                     */
    for (m = 1U; m <= s; ++m)
    {
        /*  The fundamental theorem of algebra tells us there are at most     *
         *  deg roots. If we've found this many, we can quit.                 */
        if (n_roots >= deg)
            break;

        /*  Radius of the current circle.                                     */
        r = factor_1*pow(factor_2, (2.0*m + 1.0) / (4.0*s));

        /*  Loop over the angles specified in the HSS paper.                  */
        for (n = 0U; n < N; ++n)
        {
            /*  Check if we've already found deg many roots.                  */
            if (n_roots >= deg)
                break;

            /*  Compute the angle.                                            */
            theta = angle_factor*n;

            /*  The starting point for Newton's method is specified by the    *
             *  angle and circle we're on. Compute this point.                */
            p = r * (cos(theta) + dbl_I*sin(theta));

            /*  Run Newton's method on this point, see if we converge.        */
            for (iter = 0U; iter < root_finder_max_iter; ++iter)
            {
                f_p = poly_eval(p);
                df_p = poly_prime_eval(p);

                /*  Compute the next step in sequence.                        */
                p = p - f_p / df_p;

                /*  Check for convergence.                                    */
                if (cabs(poly_eval(p)) < root_toler)
                    break;
            }
            /*  End of for (iter = 0U; iter < root_finder_max_iter; ++iter).  */

            /*  See if this new element is indeed a root.                     */
            if (cabs(poly_eval(p)) < root_toler)
            {
                /*  If this is the first root, add it.                        */
                if (n_roots == 0)
                {
                    n_roots += 1;
                    roots[0] = p;
                }

                /*  Otherwise check if this is a root we already found.       */
                else
                {
                    min = cabs(p - roots[0]);
                    for (ell = 1U; ell < n_roots; ++ell)
                    {
                        temp = cabs(p - roots[ell]);
                        if (temp < min)
                            min = temp;
                    }

                    /*  If we're far enough away, this is a new root.         */
                    if (min >= dist_toler)
                    {
                        roots[n_roots] = p;
                        n_roots += 1;
                    }
                }
                /*  End of if (n_roots == 0).                                 */
            }
            /*  End of if (cabs(poly_eval(p)) < root_toler).                  */
        }
        /*  End of for (n = 0U; n < N; ++n).                                  */
    }
    /*  End of for (m = 0U; m < s; ++m).                                      */

    return n_roots;
}
/*  End of get_roots.                                                         */

/*  Function for writing a color to a PPM file.                               */
static void write_color(struct color c, FILE *fp)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

/*  Function for drawing the Halley fractal of the input polynomial.          */
int main(void)
{
    /*  Declare all necessary variables.                                      */
    FILE *fp;
    complex double f_z, df_z, d2f_z, z, roots[DEG];
    unsigned int n_roots, x, y;
    const complex double dbl_I = (complex double)_Complex_I;
    double z_x, z_y, min, temp, scale;

    /*  The colors for the drawing.                                           */
    struct color colors[14] = {

        /*  Red. RGB = (255, 0, 30).                                          */
        {0xFFU, 0x00U, 0x1EU},  

        /*  Green. RGB = (0, 255, 30).                                        */
        {0x00U, 0xFFU, 0x1EU},

        /*  Blue. RGB = (0, 30, 255).                                         */
        {0x00U, 0x1EU, 0xFFU},

        /*  Yellow. RGB = (255, 255, 51).                                     */
        {0xFF, 0xFF, 0x33U},

        /*  Light Blue. RGB = (128, 212, 255).                                */
        {0x80U, 0xD4U, 0xFFU},

        /*  Magenta. RGB = (255, 29, 206).                                    */
        {0xFFu, 0x1DU, 0xCEU},

        /*  Teal. RGB = (0, 128, 128).                                        */
        {0x00U, 0x80U, 0x80U},

        /*  Purple. RGB = (128, 0, 128).                                      */
        {0x80U, 0x00U, 0x80U},

        /*  Orange. RGB = (255, 85, 0).                                       */
        {0xFFU, 0x55U, 0x00U},

        /*  Turquoise.  RGB = (77, 255, 196).                                 */
        {0x4DU, 0xFFU, 0xC4U},

        /*  Pine. RGB = (0, 128, 106).                                        */
        {0x00U, 0x80U, 0x6AU},

        /*  Melon. RGB = (255, 191, 179).                                     */
        {0xFFU, 0xBFU, 0xB3U},

        /*  Mauve. RGB = (255, 179, 230).                                     */
        {0xFFU, 0xB3U, 0xE6U},

        /*  Midnight Blue. RGB = (102, 51, 102).                              */
        {0x66U, 0x33U, 0x66U}
    };

    /*  Color struct used to draw the basins.                                 */
    struct color brightness;

    /*  Black for points that fail to converge.                               */
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Factor for giving the image a gradient.                               */
    unsigned char factor = 255/max_iters;

    /*  Dummy variables to loop over.                                         */
    unsigned int iters, ind, n;

    /*  Scale factors for the x and y axes.                                   */
    const double y_scale = (y_min - y_max)/(size - 1.0);
    const double x_scale = (x_max - x_min)/(size - 1.0);

    /*  Find the roots.                                                       */
    n_roots = get_roots(DEG, roots);

    /*  If none were found, abort.                                            */
    if (n_roots == 0U)
    {
        puts("No Roots Found. Aborting.");
        return -1;
    }

    /*  Open a PPM file and give it write permissions.                        */
    fp = fopen("halley_fractal_003.ppm", "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
    {
        puts("Error: fopen returned NULL. Aborting.");
        return -1;
    }

    /*  Otherwise, print the preamble to the file.                            */
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Loop over pixels in the y axis.                                       */
    for (y = 0U; y < size; ++y)
    {
        /*  Compute the current imaginary component of the complex number.    */
        z_y = y * y_scale - y_min;

        /*  Loop of the pixels in the x axis.                                 */
        for (x = 0U; x < size; ++x)
        {
            /*  Compute the real component of the current point.              */
            z_x = x * x_scale + x_min;

            /*  Compute the complex number corresponding to (x, y).           */
            z = z_x + dbl_I*z_y;

            /*  Allow max_iters number of iterations of Halley's method.      */
            for (iters = 0U; iters < max_iters; ++iters)
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                f_z = poly_eval(z);
                df_z = poly_prime_eval(z);
                d2f_z = poly_double_prime_eval(z);
                z = z - 2.0*f_z * df_z / (2.0*df_z*df_z - f_z * d2f_z);

                /*  Checks for convergence.                                   */
                if (cabs(poly_eval(z)) < root_toler)
                    break;
            }

            /*  Find which root the final iteration is closest too.           */
            min = cabs(z - roots[0]);
            ind = 0;

            for (n = 1U; n < n_roots; ++n)
            {
                temp = cabs(z - roots[n]);
                if (temp < min)
                {
                    min = temp;
                    ind = n;
                }
            }

            /*  If we didn't converge to a root, color it black.              */
            if (min > dist_toler)
                write_color(black, fp);

            /*  Else, color the pixel based on which root we converged to.    */
            else
            {
                /*  Give a gradient to the color based on the number of       *
                 *  iterations it took to converge.                           */
                scale = (255.0-factor*iters)/255.0;

                /*  Set the RGB values.                                       */
                brightness.red = (unsigned char)(scale * colors[ind].red);
                brightness.green = (unsigned char)(scale * colors[ind].green);
                brightness.blue = (unsigned char)(scale * colors[ind].blue);

                /*  Color the current pixel.                                  */
                write_color(brightness, fp);
            }
            /*  End of if (min > dist_toler).                                 */
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    return 0;
}
/*  End of main.                                                              */
