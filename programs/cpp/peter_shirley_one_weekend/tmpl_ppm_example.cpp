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
 *  Purpose:                                                                  *
 *      This is part of a set of files I made while studying from Peter       *
 *      Shirley's "Ray Tracing in One Weekend", Copyright 2018-2020, Peter    *
 *      Shirley, All rights reserved. The code is my own, but follows the     *
 *      ideas laid out in the text.                                           *
 *                                                                            *
 *      This file shows basic usage of the PPM file format. PPM's are used a  *
 *      lot in the main tmpl library (which is written in C, not C++ like     *
 *      this file) since they are simple and easy to use.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  fopen and puts are found here. This is the C++ equivalent of stdio.h.     */
#include <cstdio>

/*  Function for creating a PPM file with a color gradient.                   */
int main(void)
{
    /*  We'll write the output to a .ppm file. Open this with fopen.          */
    FILE *fp = std::fopen("basic_ppm.ppm", "w");

    /*  We'll create a 1024x1024 picture. Save this in the variable "size".   */
    unsigned int size = 1024U;
    
    /*  The value 255 / (size-1) is used to compute the color gradient. 255   *
     *  is the maximum value allowed in the RGB format, so 255 / (size - 1)   *
     *  can be used to "normalize" the value.                                 */
    double factor = 255.0 / (double)(size - 1U);
    
    /*  The RGB value is three unsigned integers between 0 and 255            *
     *  representing the intensity of Red, Green, and Blue respectively.      */
    unsigned char red, green, blue;
 
    /*  And declare two variables for indexing. C++ allows one to declare     *
     *  indexing variables inside of the for loop (C99 and higher allows this *
     *  as well), but I find this ugly as sin.                                */
    unsigned int x, y;

    /*  fopen returns NULL on failure. Check that this didn't happen.         */
    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  The preamble of a PPM file is the following:                          *
     *      Pn                                                                *
     *      x_size y_size                                                     *
     *      max_color                                                         *
     *  Pn determines the type of file we're making. There are 6 types:       *
     *      P1: Black and White, text-based.                                  *
     *      P2: Gray-scale, text-based.                                       *
     *      P3: RGB, text-based.                                              *
     *      P4: Black and white, binary.                                      *
     *      P5: Grayscale, binary.                                            *
     *      P6: RGB, binary.                                                  *
     *  The text based options are more human-readable, but larger in file    *
     *  size. For this example we'll use RGB binary, which is P6.             */
    std::fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop over all of the pixels.                                          */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  Compute the RGB value as a gradient based on the where the    *
             *  current pixel lies.                                           */
            red   = (unsigned char)((double)x * factor);
            green = (unsigned char)((double)y * factor);
            blue  = 64U;
            
            /*  Write the RGB value to the file.                              */
            std::fputc(red, fp);
            std::fputc(green, fp);
            std::fputc(blue, fp);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */

