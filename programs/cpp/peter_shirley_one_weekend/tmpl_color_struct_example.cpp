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
 *      This file presents a basic struct used to represent colors. This is   *
 *      entirely separate from the PPM sublibrary of libtmpl. That code is    *
 *      written in C89/C90, whereas this standalone file is written in C++.   *
 *      The rest of libtmpl is NOT a dependency to compile this file.         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  fputc is found here.                                                      */
#include <cstdio>

/*  A color is an ordered triple (r, g, b) of the amount of red, green, and   *
 *  blue present in the color.                                                */
struct tmpl_simple_color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    /*  Empty constructor.                                                    */
    tmpl_simple_color(void)
    {
        return;
    }

    /*  Constructor from three values, RGB.                                   */
    tmpl_simple_color(unsigned char r, unsigned char g, unsigned char b)
    {
        red   = r;
        green = g;
        blue  = b;
    }
    
    /*  Operator for adding colors.                                           */
    tmpl_simple_color operator + (tmpl_simple_color r)
    {
        /*  To avoid an arithmetic overflow with unsigned char's, compute     *
         *  the sum using unsigned int's. Unsigned int's are required to be   *
         *  least 16 bits in the C-standard, and I imagine the same would     *
         *  apply in C++. Since our colors are represented by 8-bit numbers   *
         *  (char can be larger than 8-bit, but is required to be at least 8  *
         *  bits, and we only want values 0 to 255, which is 8-bit), if we    *
         *  use unsigned int's to perform the addition, we are guaranteed to  *
         *  NOT get an overflow, which is useful.                             */
        unsigned int x, y, z;
        unsigned char out_red, out_green, out_blue;
        
        /*  Cast to unsigned int's and compute the sum.                       */
        x = (unsigned int)r.red   + (unsigned int)red;
        y = (unsigned int)r.green + (unsigned int)green;
        z = (unsigned int)r.blue  + (unsigned int)blue;
        
        /*  If the values exceed 255, return 255. 255 is the max intensity.   */
        if (x >= 255U)
            out_red = 255U;
        else
            out_red = (unsigned char)x;

        if (y >= 255U)
            out_green = 255U;
        else
            out_green = (unsigned char)y;

        if (z >= 255U)
            out_blue = 255U;
        else
            out_blue = (unsigned char)z;
        
        /*  Use the constructor to return the sum from the RGB values.        */
        return tmpl_simple_color(out_red, out_green, out_blue);
    }
    /*  End of color addition.                                                */

    /*  Scaling a color by a real number.                                     */
    tmpl_simple_color operator * (double a)
    {
        unsigned char r, g, b;
        r = (unsigned char)(a * (double)red);
        g = (unsigned char)(a * (double)green);
        b = (unsigned char)(a * (double)blue);
        
        return tmpl_simple_color(r, g, b);
    }

    /*  Function for writing the color to a PPM file.                         */
    void write(FILE *fp)
    {
        std::fputc(red, fp);
        std::fputc(green, fp);
        std::fputc(blue, fp);
    }
};
/*  End of tmpl_simple_color.                                                 */

/*  Function for testing the color struct defined above.                      */
int main(void)
{
    /*  We'll output the colors to a PPM file. Create and open with fopen.    */
    FILE *fp = std::fopen("simple_color_example.ppm", "w");

    /*  The file will be 1024x1024 pixels. Store this value in "size".        */
    unsigned int size = 1024U;

    /*  Two variables for indexing over the pixels of the PPM file.           */
    unsigned int x, y;

    /*  Values for the red and green components of a given color.             */
    unsigned char r, g;

    /*  This factor will be used to create a gradient in color across the PPM.*/
    double factor = 255.0 / (double)(size - 1U);

    /*  Declare a tmpl_simple_color to use for the computation.               */
    tmpl_simple_color c;

    /*  If fopen failed, it returns NULL. Check if this happened.             */
    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }
    
    /*  Write the preamble to the PPM file.                                   */
    std::fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop over the pixels of the PPM and compute the colors.               */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  The red and green values will be a gradient across the image. */
            r = (unsigned char)((double)x * factor);
            g = (unsigned char)((double)y * factor);
            
            /*  Use the constructor to create the color from these values.    */
            c = tmpl_simple_color(r, g, 64U);
            
            /*  Use the write method to write this color to the PPM file.     */
            c.write(fp);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */

