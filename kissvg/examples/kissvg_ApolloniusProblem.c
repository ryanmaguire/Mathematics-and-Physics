/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_colors.h>
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

#define FILENAME "kissvg_ApolloniusProblem.ps"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C1, *C2, *C3;
    kissvg_Circle **apo;
    kissvg_Canvas2D *canvas;
    double radius;
    long n, N;
    N = 8;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True);

    radius = 0.5;
    center = kissvg_NewTwoVector(1.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, 1.0);
    C2 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C2, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C2);

    center = kissvg_NewTwoVector(0, -1.0);
    C3 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C3, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C3);

    apo = kissvg_ApolloniusProblem(C1, C2, C3);

    for (n=0; n<N; ++n)
    {
        C1 = apo[n];
        kissvg_DrawCircle2D(cr, C1);
        kissvg_DestroyCircle(C1);
    }

    kissvg_DestroyCanvas2D(canvas);
    kissvg_DestroyCircle(C2);
    kissvg_DestroyCircle(C3);
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
