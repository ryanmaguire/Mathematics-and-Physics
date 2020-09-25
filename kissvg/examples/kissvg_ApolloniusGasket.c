/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <cairo-ps.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.0
#define X_MAX  3.0
#define Y_MIN -3.0
#define Y_MAX  3.0

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 2 * 72.0

/*  Compute the scales needed to convert from the mathematical coordinate     *
 *  system to the coordinates of the output image.                            */
static const double __x_scale = X_INCHES/(X_MAX - X_MIN);
static const double __y_scale = Y_INCHES/(Y_MAX - Y_MIN);

/*  We'll use the smaller of the two scales and set both the x and y scales   *
 *  to this value to ensure we have a 1-to-1 aspect ratio.                    */
static const double __scale = (__x_scale < __y_scale ? __x_scale : __y_scale);

/*  Compute the shifts needed to ensure the image is centered.                */
static const double __x_shift = 0.5*X_INCHES - 0.5*(X_MIN + X_MAX)*__x_scale;
static const double __y_shift = 0.5*Y_INCHES - 0.5*(Y_MIN + Y_MAX)*__y_scale;

/*  Set the scale to a 1-to-1 aspect ratio.                                   */
static const double scales[2] = {__scale, __scale};

/*  Set the shifts accordingly to center the image.                           */
static const double shifts[2] = {__x_shift, __y_shift};

#define FILENAME "kissvg_ApolloniusProblem.ps"

void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C1, *C2, *C3;
    kissvg_Circle **apo;
    kissvg_Canvas2D *canvas;
    double radius;
    double thick_width;
    long n, m, N;
    N = 8;

    thick_width = 1.0;

    canvas = kissvg_CreateCanvas2D(scales, shifts);

    center = kissvg_NewTwoVector(0.0, 0.0);
    radius = 1.0;
    C1 = kissvg_CreateCircle(center, radius);
    kissvg_DrawCircle2D(cr, center, radius, thick_width, kissvg_Black, canvas);

    center = kissvg_NewTwoVector(0.0, 0.5);
    radius = 0.5;
    C2 = kissvg_CreateCircle(center, radius);
    kissvg_DrawCircle2D(cr, center, radius, thick_width, kissvg_Black, canvas);

    center = kissvg_NewTwoVector(0, -0.5);
    radius = 0.5;
    C3 = kissvg_CreateCircle(center, radius);

    kissvg_DrawCircle2D(cr, center, radius, thick_width, kissvg_Black, canvas);

    center = kissvg_NewTwoVector(2.0, 0.0);
    radius = 1.0;
    C1 = kissvg_CreateCircle(center, radius);

    apo = kissvg_ApolloniusProblem(C1, C2, C3);

    n = 0;
    C3 = apo[n];
    center = kissvg_CircleCenter(C3);
    radius = kissvg_CircleRadius(C3);
    kissvg_DrawCircle2D(cr, center, radius, thick_width, kissvg_Black, canvas);

    for (m=0; m<8; ++m)
        kissvg_DestroyCircle(apo[m]);

    free(apo);
    return;
}

int main (void)
{
    cairo_surface_t *surface;
    cairo_t *cr;
    FILE *file;

    file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file %s for writing.\n", FILENAME);
        return 1;
    }

    surface = cairo_ps_surface_create(FILENAME, X_INCHES, Y_INCHES);

    cr = cairo_create(surface);
    cairo_surface_destroy(surface);

    draw(cr);

    cairo_show_page(cr);
    cairo_destroy(cr);
    fclose(file);

    return 0;
}
