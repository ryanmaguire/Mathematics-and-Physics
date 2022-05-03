/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************/

/*  Needed for creating the output file.                                      */
#include <stdio.h>

/*  Malloc is defined here.                                                   */
#include <stdlib.h>

/*  Math functions like pow are defined here.                                 */
#include <math.h>

/*  And lastly, we'll need complex variables which are defined here.          */
#include <complex.h>

/*  The number of pixels in the x and y axes.                                 */
const int size = 1024;

/*  Constant used in the computation of g_3.                                  */
const double PI = 3.14159265358979323846264338327950288419716;
const double g_fac = 284.856057355645759120065020341457747812508897;

/*  Maximum number of terms in the Taylor series.                             */
const unsigned int max_taylor = 500;

/*  To avoid computing sigma_5 over and over again, which is computationally  *
 *  expensive, we'll create a table of the first "max_taylor" values of       *
 *  sigma_5 make calls to this table in the computation of g_3.               */
long *divisor_quintic_table;

/*  Function for computing the divisor function sigma_5(n).                   */
static long divisor_quintic(int N)
{
    int n;
    long out;

    /*  Initialize the output to zero.                                        */
    out = 0;

    /*  We need to check if n divides N, and if it does we add n^5 to out.    */
    for (n=1; n<=N; ++n)
        if ((N % n) == 0)
            out += n*n*n*n*n;

    return out;
}

/******************************************************************************
 *  The function g_3, the coefficient of the quadratic term of the            *
 *  Weierstrass elliptic function. We are plotting g_3 with respect to the    *
 *  nome q. This has the formula:                                             *
 *                                                                            *
 *                        __        inf                   __                  *
 *                8 pi^6 |          ____                    |                 *
 *      g_3(q)  = -------|  1 - 504 \     sigma_5(n)q^(2n)  |                 *
 *                  27   |          /___                    |                 *
 *                       |__         n=1                  __|                 *
 ******************************************************************************/
static complex double gee_three(complex double q)
{
    complex double sum, q_squared, q_power;
    unsigned int n;

    if (cabs(q) >= 1.0)
        return 0.0;

    q_squared = q*q;
    q_power = 1.0;
    sum = 0.0;

    for (n=0; n<max_taylor; ++n)
    {
        q_power *= q_squared;
        sum += divisor_quintic_table[n]*q_power;
    }
    return g_fac*(1.0 - 504.0*sum);
}

/*  Now we plot g_3 as a function of q^2 instead of q.                        */
static complex double gee_three_square(complex double q_squared)
{
    complex double sum, q_power;
    unsigned int n;

    if (cabs(q_squared) >= 1.0)
        return 0.0;

    q_power = 1.0;
    sum = 0.0;

    for (n=0; n<max_taylor; ++n)
    {
        q_power *= q_squared;
        sum += divisor_quintic_table[n]*q_power;
    }
    return g_fac*(1.0 - 504.0*sum);
}

static long *get_divisors(unsigned int N)
{
    unsigned int n;
    long *out;
    out = malloc(sizeof(*out) * N);

    for (n=1; n<=N; ++n)
        out[n-1] = divisor_quintic(n);

    return out;
}

/*  Function for computing the color corresponding to a given value of the    *
 *  real and complex parts. We'll use an RGB gradient with Blue as the        *
 *  smallest value and Red as the max.                                        */
static void set_color(unsigned char *color, double x)
{
    double val, sgn;

    sgn = (x < 0 ? -1 : 1);

    /*  The values of this function are HUGE! Compress the values down by     *
     *  taking the fifth roots to really see the dynamics. Otherwise, the     *
     *  output images will just be red almost everywhere.                     */
    val = ceil(pow(fabs(x), 0.2));

    /*  The function is very dark and blue in the interior if we let blue     *
     *  vary linearly. Letting it very with the square roots makes it too     *
     *  bright, letting it verry with the x^(3/4) gives a nice aesthetic.     */
    if (val < 64)
    {
        color[0] = (unsigned char)0;
        color[1] = (unsigned char)11.269*pow(val, 0.75);
        color[2] = (unsigned char)255;
    }

    /*  For green, yellow, and orange, and red portions, just let it vary     *
     *  linearly with x.                                                      */
    else if (val < 128)
    {
        color[0] = (unsigned char)0;
        color[1] = (unsigned char)255;
        color[2] = (unsigned char)(255 - 4*(val - 64));
    }
    else if (val < 192)
    {
        color[0] = (unsigned char)4*(x-128);
        color[1] = (unsigned char)255;
        color[2] = (unsigned char)0;
    }
    else if (val < 255)
    {
        color[0] = (unsigned char)255;
        color[1] = (unsigned char)(255 - 4*(val-192));
        color[2] = (unsigned char)0;
    }

    /*  For large values, simply return red. This has the effect of making    *
     *  the entire boundary red. To see the dynamics of the boundary, which   *
     *  is where a lot of the fractal stuff occurs, adjust this part and      *
     *  adjust how we're compressing x.                                       */
    else
    {
        color[0] = (unsigned char)255;
        color[1] = (unsigned char)0;
        color[2] = (unsigned char)0;
    }

}

static void set_square_color(unsigned char *color, double x)
{
    if (x < 0.0)
    {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
    }
    else
        set_color(color, x);
}

/*  Function for coloring the current pixel of the .ppm file.                 */
void color(char red, char green, char blue, FILE *fp)
{
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *g3_re, *g3_im, *g3_sq_re, *g3_sq_im;

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  More dummy variables to loop over.                                    */
    int x, y;
    double z_x, z_y, re, im;
    complex double z, g;

    /*  Compute the sigma_5(n) table for the first max_taylor values of n.    */
    divisor_quintic_table = get_divisors(max_taylor);

    /*  Open the two images and give them write permissions.                  */
    g3_re = fopen("gee_three_real.ppm", "w");
    g3_im = fopen("gee_three_imag.ppm", "w");
    g3_sq_re = fopen("gee_three_square_real.ppm", "w");
    g3_sq_im = fopen("gee_three_square_imag.ppm", "w");

    /*  Write the preamble for the ppm files.                                 */
    fprintf(g3_re, "P6\n%d %d\n255\n", size, size);
    fprintf(g3_im, "P6\n%d %d\n255\n", size, size);
    fprintf(g3_sq_re, "P6\n%d %d\n255\n", size, size);
    fprintf(g3_sq_im, "P6\n%d %d\n255\n", size, size);

    /*  Colors for the roots (Red, Green, Blue).                              */
    unsigned char *brightness = malloc(sizeof(*brightness) * 3);

    /*  Loop over all of the pixels and set the colors.                       */
    for (y=0; y<size; ++y)
    {
        /*  Scale the y value so it lies in the range [y_min, y_max].         */
        z_y = y * (y_max - y_min)/(size - 1) + y_min;

        /*  .ppm files go top to bottom, so flip the y component to color it  *
         *  bottom to top, which is what our indices are doing.               */
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            /*  Scale the x value so it lies in the range [x_min, x_max].     */
            z_x = x * (x_max - x_min)/(size - 1) + x_min;

            /*  Compute the point (x,y) as a complex number z.                */
            z = z_x + _Complex_I*z_y;

            /*  For points outside of the unit disk, color them white.        */
            if (cabs(z) >= 1.0)
            {
                color((char)255, (char)255, (char)255, g3_re);
                color((char)255, (char)255, (char)255, g3_im);
                color((char)255, (char)255, (char)255, g3_sq_re);
                color((char)255, (char)255, (char)255, g3_sq_im);
            }
            else
            {
                /*  Compute g_3 and extract it's real and imaginary parts.    */
                g = gee_three(z);
                re = creal(g);
                im = cimag(g);

                /*  Color the current pixel.                                  */
                set_color(brightness, re);
                color(brightness[0], brightness[1], brightness[2], g3_re);

                set_color(brightness, im);
                color(brightness[0], brightness[1], brightness[2], g3_im);

                /*  Now make the "square" pictures.                           */
                g = gee_three_square(z);
                re = creal(g);
                im = cimag(g);

                /*  Now make the "square" pictures.                           */
                set_square_color(brightness, re);
                color(brightness[0], brightness[1], brightness[2], g3_sq_re);

                set_square_color(brightness, im);
                color(brightness[0], brightness[1], brightness[2], g3_sq_im);
            }
        }
    }

    /*  Free the memory allocated before returning.                           */
    free(divisor_quintic_table);
    free(brightness);
    return 0;
}
