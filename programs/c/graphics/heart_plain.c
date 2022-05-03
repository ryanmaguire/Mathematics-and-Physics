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

static double f(double x, double y, double z)
{
    double x2 = x*x;
    double y2 = y*y;
    double z2 = z*z;
    double z3 = z2*z;
    double a = x2 + 2.25 * y2 + z2 - 1.0;
    return a * a * a - x2 * z3 - 0.1125 * y2 * z3;
}

int main(void)
{
    unsigned int width = 2048U;
    unsigned int height = 2048U;
    unsigned int m, n;

    double x, v, z;

    const double y_factor = 3.0 / (double)height;
    const double x_factor = 3.0 / (double)width;

    FILE* fp = fopen("heart_plain.ppm", "w");
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    for (m = 0U; m < height; ++m)
    {
        z = 1.5 - (double)m*y_factor;
        for (n = 0U; n < width; ++n)
        {
            x = (double)n*x_factor - 1.5;
            v = f(x, 0.0, z);

            if (v <= 0.0)
                fputc(0xFFU, fp);
            else
                fputc(0x00U, fp);

            fputc(0x00U, fp);
            fputc(0x00U, fp);
        }
    }
    fclose(fp);
    return 0;
}
