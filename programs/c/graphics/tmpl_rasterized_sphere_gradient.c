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
 *      Example use of working with PPM files. This creates a circular        *
 *      gradient to imitate a three dimensional sphere.                       *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 22, 2021                                                  *
 ******************************************************************************/

/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc) platforms yield no warnings. */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  fprintf and the FILE data type are here.                                  */
#include <stdio.h>

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Struct for working with points in the Euclidean plane.                    */
struct pair {
    double x, y;
};

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

/*  Function for scaling the intensity of a color by a real number.           */
static struct color scale_color(struct color c, double t)
{
    /*  Declare a variable for the output color.                              */
    struct color out;

    /*  Scale all of the components of the input color by t.                  */
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Function for computing the square of the distance between two points.     */
static double dist_squared(struct pair p, struct pair q)
{
    /*  Declare necessary variables.                                          */
    double dx, dy;

    /*  Use the Pythagorean theorem to compute the square of the distance.    */
    dx = p.x - q.x;
    dy = p.y - q.y;
    return dx*dx + dy*dy;
}
/*  End of dist_squared.                                                      */

/*  Function for creating a circle with circular gradient coloring.           */
int main(void)
{
    /*  Pixel size of the image to be created.                                */
    const unsigned int size = 2048U;

    /*  Divide by two before hand to save on division computations.           */
    const double size_by_two = (double)size * 0.5;

    /*  Radius of the final image.                                            */
    const double image_radius = 2.0;

    /*  Radius of the circle to be drawn.                                     */
    const double circle_radius = 1.5;

    /*  And precompute the square and the reciprocal of the square of this    *
     *  radius for later.                                                     */
    const double circle_radius_squared = circle_radius * circle_radius;
    const double rcpr_circle_radius_squared = 1.0 / circle_radius_squared;

    /*  Scale factor for incrementing through each pixel.                     */
    const double scale_factor = 2.0 * image_radius / (double)size;

    /*  Variable for the the center of the sphere being drawn.                */
    struct pair center = {0.0, 0.0};

    /*  Variable for the current point being drawn.                           */
    struct pair point;

    /*  The color of the sphere. (0, 0, 255) is blue.                         */
    const struct color sphere_color = {0x00U, 0x00U, 0xFFU};

    /*  The background of the image is white, (255, 255, 255).                */
    const struct color white = {0xFFU, 0xFFU, 0xFFU};

    /*  And declare a color corresponding to the pair "point".                */
    struct color current_color;

    /*  Variable used for determining how bright a given pixel is.            */
    double brightness;

    /*  Variables used for indexing over the x and y coordinates.             */
    unsigned int x, y;

    /*  Variable used for the square of the distance from point to center.    */
    double distsq;

    /*  Open the PPM file.                                                    */
    FILE *fp = fopen("tmpl_rasterized_sphere_gradient.ppm", "w");

    /*  If fopen fails it returns NULL. Check for this.                       */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file.                                   */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop through each y-pixel.                                            */
    for(y = 0U; y < size; y++)
    {
        /*  Get the current y-coordinate.                                     */
        point.y = (size_by_two - (double)y) * scale_factor;

        /*  Loop over the x-coordinates.                                      */
        for(x = 0U; x < size; x++)
        {
            /*  Calculate the x-coordinate.                                   */
            point.x = ((double)x - size_by_two) * scale_factor;

            /*  Compute the square of the distance from point to center.      */
            distsq = dist_squared(point, center);

            /*  If the point is outside of the circle, color it white.        */
            if(distsq > circle_radius_squared)
                current_color = white;

            /*  Otherwise, give it a gradient based of the distance to the    *
             *  center of the circle.                                         */
            else
            {
                brightness = 1.0 - distsq*rcpr_circle_radius_squared;
                current_color = scale_color(sphere_color, brightness);
            }

            /*  Write the color to the PPM file.                              */
            write_color(fp, current_color);
        }
        /*  End of for-loop for the x-coordinate.                             */
    }
    /*  End of for-loop for the y-coordinate.                                 */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
