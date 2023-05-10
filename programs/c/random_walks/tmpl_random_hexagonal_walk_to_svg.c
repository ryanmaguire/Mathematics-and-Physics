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
 *      Perform a random walk with steps on a hexagon.                        *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as part of libtmpl.       *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 16, 2021                                                  *
 ******************************************************************************/

/*  fprintf and the FILE data type are provided here.                         */
#include <stdio.h>

/*  malloc and free are here.                                                 */
#include <stdlib.h>

/*  Struct to represent an ordered pair for points in the plane.              */
struct pair {
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

/*  Function for creating a rainbow gradient for coloring the random walk.    *
 *  The input double should be a value between 0 and 1023.                    */
static struct color rainbow_gradient(double val)
{
    /*  Declare an output struct for the color we're computing.               */
    struct color out;

    /*  Split [0, 1023] into four parts, [0, 255], [256, 511], [512, 767],    *
     *  and [768, 1023]. Create a blue-to-red rainbow gradient from this.     *
     *  The first interval corresponds to blue to blue-green.                 */
    if (val < 256.0)
    {
        out.red   = (unsigned char)0;
        out.green = (unsigned char)(val);
        out.blue  = (unsigned char)255;
    }

    /*  Next we do blue-green to green.                                       */
    else if (val < 512.0)
    {
        /*  Subtract 256 from val so that val lies in [0, 255], which are the *
         *  allowed values for an 8-bit unsigned char.                        */
        val -= 256.0;
        out.red   = (unsigned char)0;
        out.green = (unsigned char)255;
        out.blue  = (unsigned char)(256.0 - val);
    }

    /*  Next is green to yellow.                                              */
    else if (val < 768.0)
    {
        /*  Subtract by 512 to get val in [0, 255].                           */
        val -= 512.0;
        out.red   = (unsigned char)(val);
        out.green = (unsigned char)255;
        out.blue  = (unsigned char)0;
    }

    /*  Finally, yellow to red.                                               */
    else
    {
        /*  Subtract by 768 to get val in the range [0, 255].                 */
        val -= 768.0;
        out.red   = (unsigned char)255;
        out.green = (unsigned char)(256.0 - val);
        out.blue  = (unsigned char)0;
    }

    return out;
}
/*  End of rainbow_gradient.                                                  */

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
static void draw_line(FILE *fp, struct pair P, struct pair Q,
                      struct color line_color, double thickness)
{
    fprintf(fp, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
                "stroke=\"#%02x%02x%02x\" stroke-width=\"%f\" />\n",
                P.x, P.y, Q.x, Q.y, line_color.red,
                line_color.green, line_color.blue, thickness);
}
/*  End of draw_line.                                                         */

/*  Function for adding two points in the plane.                              */
static struct pair add_pairs(struct pair p, struct pair q)
{
    /*  Declare necessary variables.                                          */
    struct pair sum;

    /*  Addition is done component-wise.                                      */
    sum.x = p.x + q.x;
    sum.y = p.y + q.y;
    return sum;
}
/*  End of add_pairs.                                                         */

/*  Function for computing a random vertex of a hexagon.                      */
static struct pair random_pair(void)
{
    /*  Get a random number between 0 and 5 using tools from stdlib.h         */
    double rreal = (double)rand() / (double)RAND_MAX;
    int rint = (int)(6.0 * rreal);
    struct pair out;

    /*  Precompute the values of the vertices of the hexagon, and return one  *
     *  of these based on the random integer that was chosen.                 */
    if (rint == 0)
    {
        out.x = 1.0;
        out.y = 0.0;
    }
    else if (rint == 1)
    {
        out.y = 0.86602540378443864;
        out.x = 0.5;
    }
    else if (rint == 2)
    {
        out.y =  0.86602540378443864;
        out.x = -0.5;
    }
    else if (rint == 3)
    {
        out.x = -1.0;
        out.y =  0.0;
    }
    else if (rint == 4)
    {
        out.y = -0.86602540378443864;
        out.x = -0.5;
    }
    else
    {
        out.y = -0.86602540378443864;
        out.x =  0.5;
    }
    return out;
}
/*  End of random_pair.                                                       */

/*  Function for creating an SVG of a random walk.                            */
int main(void)
{
    /*  Width of the SVG (x-axis).                                            */
    const unsigned int width = 1000U;

    /*  Height of the SVG (y-axis).                                           */
    const unsigned int height = 1000U;

    /*  Number of steps being performed in the random walk.                   */
    const unsigned int walk_size = 50000U;

    /*  Various variables necessary for the computation.                      */
    double xmin, xmax, ymin, ymax, xscale, yscale, scale, val, thickness;
    double xshift, yshift;

    /*  We'll use this variable for coloring the path with a rainbow          *
     *  gradient. Blue will represent the start and red is the end.           */
    struct color line_color;

    /*  The background will be black, which is (0, 0, 0).                     */
    struct color black = {0U, 0U, 0U};

    /*  The canvas details the layout of the SVG file.                        */
    struct canvas layout;

    /*  Variable for indexing over the walk.                                  */
    unsigned int n;

    /*  Array for storing the points on the walk.                             */
    struct pair *A = malloc(sizeof(*A) * walk_size);

    /*  And open an SVG file so that we can write to it.                      */
    FILE *fp = fopen("tmpl_random_walk_hexagonal.svg", "w");

    /*  If malloc fails it returns NULL. Check that this didn't happen.       */
    if (A == NULL)
    {
        puts("Malloc failed and returned NULL. Returning.");

        /*  Since fopen was called, we should close the file if fopen was     *
         *  successful. Check this.                                           */
        if (fp)
            fclose(fp);

        return -1;
    }

    /*  If fopen fails it also returns NULL. Check for this.                  */
    if (fp == NULL)
    {
        puts("fopen failed and returned NULL. Returning.");

        /*  Make sure to free A since malloc was called.                      */
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

    /*  Set the starting point to the origin.                                 */
    A[0].x = 0.0;
    A[0].y = 0.0;

    /*  To draw the SVG file we'll need to rescale the plane so that it lies  *
     *  in the box [0, width] x [0, height]. To do this we need the maximum   *
     *  and minimum values in the x and y axes for our random walk.           */
    xmin = 0.0;
    xmax = 0.0;
    ymin = 0.0;
    ymax = 0.0;

    /*  Set the thickness for the lines we're drawing.                        */
    thickness = 1.0;

    /*  Perform the random walk.                                              */
    for (n = 1U; n < walk_size; ++n)
    {
        A[n] = add_pairs(A[n-1], random_pair());

        /*  Update the minimum and maximum values for the walk.               */
        if (A[n].x > xmax)
            xmax = A[n].x;
        if (A[n].x < xmin)
            xmin = A[n].x;
        if (A[n].y > ymax)
            ymax = A[n].y;
        if (A[n].y < ymin)
            ymin = A[n].y;
    }
    /*  End of random walk.                                                   */

    /*  Compute the shift and scale factors needed for drawing the SVG.       */
    xshift = -xmin;
    yshift = -ymin;
    xscale = (double)width  / (xmax - xmin);
    yscale = (double)height / (ymax - ymin);

    /*  To have a 1:1 aspect ratio, we need the same scale for the x and y    *
     *  axes. To ensure the drawing fits inside the picture, use the smaller  *
     *  of the two scales.                                                    */
    if (xscale < yscale)
        scale = xscale;
    else
        scale = yscale;

    /*  Loop through the random walk and scale the points so they fit into    *
     *  the SVG's frame.                                                      */
    for (n = 0U; n < walk_size; ++n)
    {
        A[n].x = scale * (A[n].x + xshift);
        A[n].y = scale * (A[n].y + yshift);
    }

    /*  Lastly, loop through and draw the random walk.                        */
    for (n = 0U; n < walk_size - 1U; ++n)
    {
        /*  Compute the color of the current line on the walk. The gradient   *
         *  is drawn blue-to-red, blue representing the start, and red        *
         *  representing the end, with a continuous rainbow gradient.         */
        val = 1024.0*(double)n / (double)(walk_size - 1U);
        line_color = rainbow_gradient(val);

        /*  Draw the line onto the SVG.                                       */
        draw_line(fp, A[n], A[n+1], line_color, thickness);
    }

    /*  Write the ending of the SVG and close the file.                       */
    close_svg(fp);
    fclose(fp);

    /*  Free the memory allocated by malloc.                                  */
    free(A);
    return 0;
}
/*  End of main.                                                              */

