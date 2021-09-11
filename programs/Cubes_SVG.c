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
 *  NOTE:                                                                     *
 *      This is a modification of code I found on stack exchange when trying  *
 *      to learn about SVG. This file is for example only and is not included *
 *      in the Mathematics-and-Physics book.                                  *
 ******************************************************************************/

/*  Needed for file input/output and writing SVG lines.                       */
#include <stdio.h>

/*  Globals used for drawing the picture.                                     */
static const int border = 16;
static int xt = 0;
static int yt = 0;

/*  Globals for the size of the picture and for drawing.                      */
static long rrmin = 64UL;
static long rrmax = 128UL;
static int center = 0;
static const int size = 32U;

/*  Hex code for blue-green. White is the triple (255, 255, 255), which       *
 *  corresponds to the hex value 0xFFFFFF. Similarly, black is (0, 0, 0)      *
 *  which is 0x000000. This is in RGB (red, green, blue) format, so red is    *
 *  0xFF0000, green is 0x00FF00, and blue is 0x0000FF.                        */
static const unsigned int blue_green = 0x00AAFF;

/*  Function for getting the x coordinate from the triple (x, y, z). The z    *
 *  coordinate is not needed for this.                                        */
static int get_x(int x, int y)
{
    return 16*x + 12*y;
}
/*  End of get_x.                                                             */

/*  Similar function for y.                                                   */
static int get_y(int x, int y, int z)
{
    return 6*x - 8*y - 17*z;
}
/*  End of get_y.                                                             */

/*  Function for drawing a cube in SVG.                                       */
static void fcube(int x, int y, int z, const unsigned int fill, FILE *out)
{
    int xc = xt + get_x(x, y);
    int yc = yt + get_y(x, y, z);

    /*  This will create the SVG code for the image.                          */
    fprintf(out, "<path d=\"M %d %d l 16 6 l 12 -8 0 -17 -16 -6 -12 8 z\" "
                 "fill=\"#%06x\" stroke=\"black\" />\n", xc, yc, fill);
    fprintf(out, "<path d=\"M%d, %dl16, 6, 12, -8m-12, 8l0, 17\" "
                 "fill=\"none\" stroke=\"black\" />\n", xc, yc-17);
}
/*  End of fcube.                                                             */

/*  Function for determining if we're drawing the cube with center (x, y, z). */
static int surface(int x, int y, int z)
{
    /*  Doubled coordinates:                                                  */
    long dx = 2*x - center;
    long dy = 2*y - center;
    long dz = 2*z - center;
    long rr = dx*dx + dy*dy + dz*dz;

    return (rrmin <= rr) && (rr <= rrmax);
}
/*  End of surface.                                                           */

/*  Main function for drawing the SVG graphic.                                */
int main(void)
{
    int width, height;
    int x, y, z;

    /*  Calculate coordinate range.                                           */
    int xmin = get_x(0U, 0U);
    int xmax = get_x(0U, 0U);

    int ymin = get_y(0U, 0U, 0U);
    int ymax = get_y(0U, 0U, 0U);
    int xc, yc;

    /*  Open an SVG file and give it write permissions.                       */
    FILE *fp = fopen("Cubes_Vector.svg", "w");

    /*  Check that fopen didn't fail.                                         */
    if (fp == NULL)
    {
        puts("fopen failed to open and returned NULL. Aborting.");
        return -1;
    }

    for (z = 0; z <= size; z++)
    {
        for (y = 0; y <= size; y++)
        {
            for (x = 0; x <= size; x++)
            {
                xc = get_x(x, y);
                yc = get_y(x, y, z);
                if (xc < xmin)
                    xmin = xc;

                if (xc > xmax)
                    xmax = xc;

                if (yc < ymin)
                    ymin = yc;

                if (yc > ymax)
                    ymax = yc;
            }
            /*  End of x for-loop.                                            */
        }
        /*  End of y for-loop.                                                */
    }
    /*  End of z for-loop.                                                    */

    xt = border - xmin;
    width = xmax - xmin + 2*border;

    yt = border - ymin;
    height = ymax - ymin + 2*border;

    center = size - 1;

    /* SVG preamble.                                                          */
    fprintf(fp, "<?xml version=\"1.0\"?>\n");
    fprintf(fp,
            "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            "viewBox=\"0 0 %d %d\">\n",
            width, height);

    fprintf(
        fp,
        "<path d=\"M%d,%dL%d,%d,%d,%d,%d,%d,%d,%d,%d,%dz\" "
        "fill=\"red\" stroke=\"#000000\"/>\n",
        xt + (int)get_x(  0U,   0U), yt + get_y(   0U,  0U,   0U),
        xt + (int)get_x(size,   0U), yt + get_y(size,   0U,   0U),
        xt + (int)get_x(size, size), yt + get_y(size, size,   0U),
        xt + (int)get_x(size, size), yt + get_y(size, size, size),
        xt + (int)get_x(0U,   size), yt + get_y(  0U, size, size),
        xt + (int)get_x(0U,     0U), yt + get_y(  0U,   0U, size)
    );

    fprintf(
        fp,
        "<path d=\"M%d,%dL%d,%d,%d,%dM%d,%dL%d,%d\" "
        "fill=\"none\" stroke=\"#666666\"/>\n",
        xt + get_x(  0U,   0U), yt + get_y(  0U,   0U,   0U),
        xt + get_x(  0U, size), yt + get_y(  0U, size,   0U),
        xt + get_x(size, size), yt + get_y(size, size,   0U),
        xt + get_x(  0U, size), yt + get_y(  0U, size,   0U),
        xt + get_x(  0U, size), yt + get_y(  0U, size, size)
    );

    for (z = 0; z < size; ++z)
    {
        for (y = 0; y < size; ++y)
        {
            for (x = 0; x < size; ++x)
            {
                if (surface(x, size - y - 1, z))
                    fcube(x, size - y - 1, z, blue_green, fp);
            }
            /*  End of x for-loop.                                            */
        }
        /*  End of y for-loop.                                                */
    }
    /*  End of z for-loop.                                                    */

    /*  End of SVG file.                                                      */
    fprintf(fp, "</svg>\n");

    /*  Close the file and exit the program.                                  */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

