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
 *      Traces out the iterations in Newton's method for z^3 - 1.             *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       October 26, 2021                                              *
 ******************************************************************************/

/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc.) platforms yield no warnings.*/
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  fprintf and the FILE data type are provided here.                         */
#include <stdio.h>

/*  malloc and free are here.                                                 */
#include <stdlib.h>

/*  Struct to represent a complex number in the plane.                        */
struct complex_number {
    double x, y;
};

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  Struct for creating the SVG file.                                         */
struct canvas {
    unsigned int width, height;
    struct color background, outline;

    /*  Opacity should be a real number between 0 and 1.                      */
    double opacity;
};

/*  Function for creating the preamble to an SVG file.                        */
static void create_svg(FILE *fp, struct canvas *layout)
{
    /*  If fp is a NULL pointer, trying to write to it will result in a       *
     *  segmentation fault. Check that this isn't the case.                   */
    if (fp == NULL)
        return;

    /*  Write the preamble to the file.                                       */
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" ");
    fprintf(fp, "standalone=\"no\"?>\n");
    fprintf(fp, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" ");
    fprintf(fp, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");

    /*  This part specifies the size of the SVG file.                         */
    fprintf(fp, "<svg viewBox=\"0 0 %u %u\" ", layout->width, layout->height);
    fprintf(fp, "xmlns=\"http://www.w3.org/2000/svg\" ");
    fprintf(fp, "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");

    /*  This part specifies the background color.                             */
    fprintf(fp, "<rect fill=\"#%02x%02x%02x\" stroke=\"#%02x%02x%02x\" ",
            layout->background.red,  layout->background.green,
            layout->background.blue, layout->outline.red,
            layout->outline.green,   layout->outline.blue);

    /*  The size of the background should be the same as the size of the pic. */
    fprintf(fp, "x=\"0\" y=\"0\" width=\"%u\" height=\"%u\"/>\n",
            layout->width, layout->height);

    /*  Finally, add the opacity.                                             */
    fprintf(fp, "<g opacity=\"%f\">\n", layout->opacity);
}
/*  End of create_svg.                                                        */

/*  Function for writing the ending of an SVG file.                           */
static void close_svg(FILE *fp)
{
    /*  If fp is a NULL pointer, trying to write to it will result in a       *
     *  segmentation fault. Check that this isn't the case.                   */
    if (fp == NULL)
        return;

    fprintf(fp, "</g>\n</svg>\n");
}
/*  End of close_svg.                                                         */

/*  Function for adding a line to the SVG file.                               */
static void
draw_line(FILE *fp, struct complex_number P, struct complex_number Q,
          struct color line_color, double thickness)
{
    fprintf(fp, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
                "stroke=\"#%02x%02x%02x\" stroke-width=\"%f\" />\n",
                P.x, P.y, Q.x, Q.y, line_color.red,
                line_color.green, line_color.blue, thickness);
}
/*  End of draw_line.                                                         */

/*  Function for filling in a circle in the figure.                           */
static void
fill_circle(FILE *fp, struct complex_number P, double radius,
            struct color fill_color, double linewidth)
{
    fprintf(fp,
            "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"stroke:#000000; "
            "stroke-width: %f; fill:#%02x%02x%02x\"/>\n",
            P.x, P.y, radius, linewidth, fill_color.red,
            fill_color.green, fill_color.blue);
}
/*  End of fill_circle.                                                       */

/*  Function for embedding the image of the fractal.                          */
static void
embed_image(const char *str, unsigned int xstart, unsigned int ystart,
            unsigned int width, unsigned int height, FILE *fp)
{
    fprintf(fp,
            "<image x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" "
            "xlink:href=\"%s\" />",
            xstart, ystart, width, height, str);
    return;
}
/*  End of embed_image.                                                       */

/*  Function for subtracting two points in the plane.                         */
static struct complex_number
complex_subtract(struct complex_number p, struct complex_number q)
{
    /*  Declare necessary variables.                                          */
    struct complex_number sum;
    sum.x = p.x - q.x;
    sum.y = p.y - q.y;
    return sum;
}
/*  End of complex_subtract.                                                  */

/*  Function for multiplying two points in the plane.                         */
static struct complex_number
complex_multiply(struct complex_number p, struct complex_number q)
{
    /*  Declare necessary variables.                                          */
    struct complex_number prod;
    prod.x = p.x*q.x - p.y*q.y;
    prod.y = p.x*q.y + p.y*q.x;
    return prod;
}
/*  End of complex_multiply.                                                  */

/*  Function for dividing two points in the plane.                            */
static struct complex_number
complex_divide(struct complex_number p, struct complex_number q)
{
    /*  Declare necessary variables.                                          */
    struct complex_number quot;
    double denom = 1.0/(q.x*q.x + q.y*q.y);
    quot.x = denom*(p.x*q.x + p.y*q.y);
    quot.y = denom*(-p.x*q.y + p.y*q.x);
    return quot;
}
/*  End of complex_divide.                                                    */

/*  Function for the next iteration of Newton's method.                       */
static struct complex_number next_iterate(struct complex_number z)
{
    struct complex_number z2 = complex_multiply(z, z);
    struct complex_number z3 = complex_multiply(z2, z);
    struct complex_number numer = z3;
    struct complex_number denom = z2;
    numer.x -= 1.0;
    denom.x *= 3.0;
    denom.y *= 3.0;
    return complex_subtract(z, complex_divide(numer, denom));
}
/*  End of next_iterate.                                                      */

/*  Function for creating an SVG of a random walk.                            */
int main(void)
{
    /*  Width of the SVG (x-axis).                                            */
    const unsigned int width = 4096U;

    /*  Height of the SVG (y-axis).                                           */
    const unsigned int height = 4096U;

    /*  Number of steps being performed for Newton's method.                  */
    const unsigned int walk_size = 64;

    /*  To draw the SVG file we'll need to rescale the plane so that it lies  *
     *  in the box [0, width] x [0, height].                                  */
    const double xmin = -3.0;
    const double xmax =  3.0;
    const double ymin = -3.0;
    const double ymax =  3.0;

    /*  Compute the shift and scale factors needed for drawing the SVG.       */
    const double xshift = -xmin;
    const double yshift = -ymin;
    const double xscale = (double)width  / (xmax - xmin);
    const double yscale = (double)height / (ymax - ymin);

    /*  Set the thickness for the lines we're drawing.                        */
    const double thickness = 7.0;
    const double circle_thickness = 5.0;

    /*  The background will be black, which is (0, 0, 0).                     */
    const struct color black = {0U, 0U, 0U};

    /*  Lines will be black.                                                  */
    const struct color line_color = {0x00U, 0x00U, 0x00U};

    /*  The interior of circles is white.                                     */
    const struct color fill_color = {0xFFU, 0xFFU, 0xFFU};

    /*  Radius for dots.                                                      */
    const double radius = 12.0;

    /*  The canvas details the layout of the SVG file.                        */
    struct canvas layout;

    /*  Variable for indexing over the walk.                                  */
    unsigned int n;

    /*  Char arrays for getting the input from the user.                      */
    char strx[64], stry[64];

    /*  Array for storing the points on the walk.                             */
    struct complex_number *A = malloc(sizeof(*A) * walk_size);

    /*  And open an SVG file so that we can write to it.                      */
    FILE *fp = fopen("tmpl_walking_along_a_newton_fractal.svg", "w");

    /*  If malloc fails it returns NULL. Check that this didn't happen.       */
    if (A == NULL)
    {
        puts("Malloc failed and returned NULL. Aborting.");

        /*  Since fopen was called, we should close the file if fopen was     *
         *  successful. Check this.                                           */
        if (fp)
            fclose(fp);

        return -1;
    }

    /*  If fopen fails it also returns NULL. Check for this.                  */
    if (fp == NULL)
    {
        puts("fopen failed and returned NULL. Aborting.");

        /*  Make sure to free A since malloc was called.                       */
        free(A);
        return -1;
    }

    /*  Store the necessary values in the layout.                             */
    layout.width = width;
    layout.height = height;
    layout.background = black;
    layout.outline = black;
    layout.opacity = 1.0;

    /*  Write the preamble to the SVG file we're making.                      */
    create_svg(fp, &layout);

    /*  Add the image to the SVG.                                             */
    embed_image("newton_fractal.png", 0, 0, width, height, fp);

    /*  Set the starting point to the origin.                                 */
    printf("Enter the x coordinate: ");
    scanf("%s", strx);
    printf("Enter the y coordinate: ");
    scanf("%s", stry);
    A[0].x = atof(strx);
    A[0].y = atof(stry);

    /*  Perform Newton's method.                                              */
    for (n = 1U; n < walk_size; ++n)
    {
        A[n] = next_iterate(A[n-1]);

        /*  Shift the points so they lie in the SVG file.                     */
        A[n-1].x = xscale * (A[n-1].x + xshift);
        A[n-1].y = yscale * (A[n-1].y + yshift);
    }

    /*  Shift the final points.                                               */
    A[walk_size-1].x = xscale * (A[walk_size-1].x + xshift);
    A[walk_size-1].y = yscale * (A[walk_size-1].y + yshift);


    /*  Draw everything.                                                      */
    for (n = 0U; n < walk_size - 1U; ++n)
    {
        draw_line(fp, A[n], A[n+1], line_color, thickness);
        fill_circle(fp, A[n], radius, fill_color, circle_thickness);
    }

    /*  Write the ending of the SVG and close the file.                       */
    close_svg(fp);
    fclose(fp);

    /*  Free the memory allocated by malloc.                                  */
    free(A);
    return 0;
}
/*  End of main.                                                              */

