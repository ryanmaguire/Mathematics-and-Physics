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
 *  I forget where I found this, but once upon a time while roaming the web   *
 *  I came across this code. I've made several modifications, but the output  *
 *  is more or less the same. This file was lying dormant in some folder on   *
 *  my computer, so I thought I'd touch this up and share.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  Microsoft's MSVC "deprecated" many of the standard library functions      *
 *  found in stdio.h. To avoid warnings, declare this macro.                  */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*  fprintf and fputc found here.                                             */
#include <stdio.h>

/*  sqrt found here.                                                          */
#include <math.h>

/*  Value needed for the intensity factor for the red in the picture.         */
static const double two_by_sqrt_3 = 2.0 / 1.7320508075688772;

/*  Function where f(x, 0, y) has a heart as the zero set for (x, z).         */
static double heart_func(double x, double y, double z)
{
    const double x2 = x*x;
    const double y2 = y*y;
    const double z2 = z*z;
    const double z3 = z2*z;
    const double a = x2 + 2.25 * y2 + z2 - 1.0;
    return a*a*a - x2*z3 - 0.1125*y2*z3;
}
/*  End of heart_func.                                                        */

/*  Function for find the y value such that f(x, y, z) = 0.                   */
static double find_y(const double x, const double z)
{
    double y0 = 2.0;
    double y1 = 2.0;
    double c = heart_func(x, y0, z);
    const double eps = 1.0E-15;
    const unsigned int max_iters = 10U;
    unsigned int n = 0U;
    while (fabs(c) > eps)
    {
        if (n > max_iters)
            break;

        if (c > 0.0)
        {
            y1 = y0;
            y0 *= 0.5;
        }
        else if (c < 0.0)
            y0 = 0.5 * (y0 + y1);
        else
            return y0;

        c = heart_func(x, y0, z);
        ++n;
    }
    if (fabs(c) < eps)
        return y0;

    return 0.0;
}
/*  End of find_y.                                                            */

/*  Function for computing the intensity of a given pixel.                    */
static unsigned char red_intensity(double x, double y, double z)
{
    const double x2 = x*x;
    const double y2 = y*y;
    const double z2 = z*z;
    const double z3 = z*z2;
    const double a = x2 + 2.25 * y2 + z2 - 1.0;
    const double a2 = a*a;

    const double dx = 6.0*x*a2 - 2.0*x*z3;
    const double dy = 13.5*y*a2 - 0.225*y*z3;
    const double dz = z*(6.0*a2 - 3.0*x2*z - 0.3375*y2*z);

    double ds = two_by_sqrt_3 / sqrt(dx*dx + dy*dy + dz*dz);
    double red = (dx + dy + dz) * ds + 0.5;
    return (unsigned char)(red * 255.0);
}

/*  Function for drawing a shiny heart.                                       */
int main(void)
{
    /*  Width and height of the image.                                        */
    unsigned int width = 1024U;
    unsigned int height = 1024U;

    /*  Variables for indexing.                                               */
    unsigned int m, n;
    unsigned char r;

    double x, y, z, v;

    const double y_factor = 3.0 / (double)height;
    const double x_factor = 3.0 / (double)width;

    FILE* fp = fopen("heart_bisection.ppm", "w");
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    for (m = 0U; m < height; ++m)
    {
        z = 1.5 - (double)m*y_factor;
        for (n = 0U; n < width; ++n)
        {
            x = (double)n*x_factor - 1.5;
            v = heart_func(x, 0.0, z);

            if (v <= 0.0)
            {
                y = find_y(x, z);
                r = red_intensity(x, y, z);
            }
            else
                r = 0x00U;

            fputc(r, fp);
            fputc(0x00U, fp);
            fputc(0x00U, fp);
        }
    }
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

