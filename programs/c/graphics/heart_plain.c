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
 *      Modified version of "heart.c" in this folder. Draws a plain red heart.*
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
    FILE* fp = fopen("heart_plain.ppm", "w");

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

            /*  Write the red component of the pixel.                         */
            if (v <= 0.0)
                fputc(0xFFU, fp);
            else
                fputc(0x00U, fp);

            /*  The heart is red, so no green or blue parts.                  */
            fputc(0x00U, fp);
            fputc(0x00U, fp);
        }
    }

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
