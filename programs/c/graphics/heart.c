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
 *      I forget where I found this, but once upon a time while roaming the   *
 *      web I came across this code. I've made several modifications, but the *
 *      output is more or less the same. This file was lying dormant in some  *
 *      folder on my computer, so I thought I'd touch this up and share.      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/07/28                                                        *
 ******************************************************************************/

/*  Microsoft's MSVC "deprecated" many of the standard library functions      *
 *  found in stdio.h. To avoid warnings, declare this macro.                  */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

/*  fprintf and fputc found here.                                             */
#include <stdio.h>

/*  sqrt found here.                                                          */
#include <math.h>

/*  Value needed for the intensity factor for the red in the picture.         */
static const double rcpr_half_sqrt_3 = 1.1547005383792517;

/*  Step size when trying to find the zero of f(x, y, z).                     */
static const double dy = 0.001;

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

/*  Function to find the y value such that f(x, y, z) = 0.                    */
static double find_y(double x, double z)
{
    double y = 1.0;

    while (y >= 0.0)
    {
        if (heart_func(x, y, z) <= 0.0)
            return y;

        /*  Increment y.                                                      */
        y -= dy;
    }

    /*  If we didn't find a zero, return 0.                                   */
    return 0.0;
}
/*  End of find_y.                                                            */

/*  Function for computing the intensity of a given pixel.                    */
static unsigned char red_intensity(double x, double y, double z)
{
    const double dx = find_y(x + dy, z) - y;
    const double dz = find_y(x, z + dy) - y;
    const double ds = rcpr_half_sqrt_3 / sqrt(dx*dx + dy*dy + dz*dz);
    const double red = (dx + dy - dz) * ds + 0.5;
    return (unsigned char)(red * 255.0);
}
/*  End of red_intensity.                                                     */

/*  Function for drawing a shiny heart.                                       */
int main(void)
{
    /*  Width and height of the image.                                        */
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;

    /*  Variables for indexing.                                               */
    unsigned int m, n;
    unsigned char r;
    double x, y, z, v;

    const double y_factor = 3.0 / (double)height;
    const double x_factor = 3.0 / (double)width;

    /*  Open the file and give it write permissions.                          */
    FILE* fp = fopen("heart.ppm", "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  The preamble to the PPM file.                                         */
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    /*  Loop over the PPM file, pixel by pixel.                               */
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

            /*  Write the color to the PPM file.                              */
            fputc(r, fp);
            fputc(0x00U, fp);
            fputc(0x00U, fp);
        }
    }

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

