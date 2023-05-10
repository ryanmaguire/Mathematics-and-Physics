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
 *  I have no idea why I made this, but this code shows the convergence of    *
 *  the sequence a_{n+2} = sqrt(a_{n} * a_{n+1}) with starting values         *
 *  a_{0} = 1, a_{1} = 2, to the value 2^(2/3).                               *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       July 28, 2021                                                 *
 ******************************************************************************/

/*  Needed for printf.                                                        */
#include <stdlib.h>

/*  Needed for malloc.                                                        */
#include <stdio.h>

/*  Needed for sqrt.                                                          */
#include <math.h>

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
    double xshift, yshift, xscale, yscale;
    double xmin, ymin, xmax, ymax;

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
static void draw_line(FILE *fp, struct pair P, struct pair Q,
                      struct color line_color, double thickness)
{
    fprintf(fp, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
                "stroke=\"#%02x%02x%02x\" stroke-width=\"%f\" "
                "stroke-linecap=\"round\" />\n",
                P.x, P.y, Q.x, Q.y, line_color.red,
                line_color.green, line_color.blue, thickness);
}
/*  End of draw_line.                                                         */

/*  Function for computing a_{n+2} = sqrt(a_{n} * a_{n+1}).                   */
void func(unsigned int n, double *arr)
{
    /*  The initial conditions are 1 and 2.                                   */
	if (n == 0)
		arr[0] = 1.0;
	else if (n == 1)
		arr[1] = 2.0;

    /*  For all other values, use the recursive definition.                   */
	else
		arr[n] = sqrt(arr[n-2]*arr[n-1]);
}
/*  End of func.                                                              */

/*  Function for converting between Cartesian and SVG coordinates.            */
struct pair Cart2SVG(struct pair P, struct canvas layout)
{
    /*  Declare variable for the output.                                      */
    struct pair out;

    /*  Convert the Cartesian values to the SVG values.                       */
    out.x = layout.xscale*(P.x + layout.xshift);
    out.y = layout.yscale*(layout.ymax - layout.ymin - P.y - layout.yshift);
    return out;
}
/*  End of Cart2SVG.                                                          */

/*  Function for showing the convergence of a_{n} to 2^(2/3).                 */
int main(void)
{
    /*  Variable for indexing.                                                */
	unsigned int n;

    /*  Number of iterations to perform.                                      */
	const unsigned int N = 31U;

    /*  Size of the output SVG file.                                          */
    const unsigned int width = 1024U;
    const unsigned int height = 576U;

    /*  Coordinates of the output.                                            */
    const double xmax = (double)(N - 1U);
    const double ymax = 3.0;
    const double xmin = -1.0;
    const double ymin = -0.5;

    /*  The value 2^(2/3).                                                    */
    const double val = 1.5874010519681994;

    /*  The background will be white, which is (255, 255, 255).               */
    const struct color white = {255U, 255U, 255U};

    /*  And the line color is black.                                          */
    const struct color black = {0U, 0U, 0U};

    /*  Thickness for lines.                                                  */
    const double thickness = 1.0;

    /*  The canvas details the layout of the SVG file.                        */
    struct canvas layout;

    /*  Pairs for plotting the sequence.                                      */
    struct pair *A;

    /*  Pairs for the axes.                                                   */
    const struct pair X[2] = {{xmin, 0.0}, {xmax, 0.0}};
    const struct pair Y[2] = {{0.0, ymin}, {0.0, ymax}};
    struct pair XAxes[2], YAxes[2];

    /*  Thickness for axes.                                                   */
    const double axes_thickness = 2.0;

    /*  And a pointer to an array to store the sequence.                      */
	double *arr;

    /*  FILE pointer for creating the SVG.                                    */
    FILE *fp;

    /*  Allocate memory for the array.                                        */
    arr = malloc(sizeof(*arr) * N);

    /*  Check if malloc failed.                                               */
    if (arr == NULL)
    {
        puts("Malloc failed and returned NULL. Returning.");
        return -1;
    }

    /*  Same for the array of pairs.                                          */
    A = malloc(sizeof(*A) * N);

    /*  Check if malloc failed.                                               */
    if (A == NULL)
    {
        puts("Malloc failed and returned NULL. Returning.");
        free(arr);
        return -1;
    }

    /*  Open a file to write the SVG too.                                     */
    fp = fopen("convergence_for_two_to_the_two_thirds.svg", "w");

    /*  Check if fopen failed.                                                */
    if (fp == NULL)
    {
        puts("fopen failed and returned NULL. Returning.");
        free(arr);
        free(A);
        return -1;
    }

    /*  Store the necessary values in the layout.                             */
    layout.width = width;
    layout.height = height;
    layout.background = white;
    layout.outline = black;
    layout.opacity = 1.0;
    layout.xmin = xmin;
    layout.xmax = xmax;
    layout.ymin = ymin;
    layout.ymax = ymax;
    layout.xshift = -xmin;
    layout.yshift = -ymin;
    layout.xscale = (double)width  / (xmax - xmin);
    layout.yscale = (double)height / (ymax - ymin);

    /*  Compute the coordinates of the axes.                                  */
    XAxes[0] = Cart2SVG(X[0], layout);
    XAxes[1] = Cart2SVG(X[1], layout);
    YAxes[0] = Cart2SVG(Y[0], layout);
    YAxes[1] = Cart2SVG(Y[1], layout);

    /*  Write the preamble to the SVG file we're making.                      */
    create_svg(fp, &layout);

    /*  Perform the iteration a_{n+2} = sqrt(a_n * a_{n+1}).                  */
	for (n = 0U; n < N; ++n)
	{
        func(n, arr);
        A[n].x = (double)n;
        A[n].y = arr[n];
        A[n] = Cart2SVG(A[n], layout);

        printf("a_%u = %.16f | 2^(2/3) = %.16f | diff = %.16f\n",
               n, arr[n], val, val - arr[n]);
	}

    /*  Draw the curve in the SVG file.                                       */
    for (n = 0U; n < N-1U; ++n)
        draw_line(fp, A[n], A[n+1U], black, thickness);

    /*  Draw the axes.                                                        */
    draw_line(fp, XAxes[0], XAxes[1], black, axes_thickness);
    draw_line(fp, YAxes[0], YAxes[1], black, axes_thickness);

    /*  Write the ending of the SVG and close the file.                       */
    close_svg(fp);
    fclose(fp);

    /*  Free memory allocated for arr and A.                                  */
    free(arr);
    free(A);
	return 0;
}
/*  End of main.                                                              */

