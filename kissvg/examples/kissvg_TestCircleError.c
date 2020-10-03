/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.0
#define X_MAX  3.0
#define Y_MIN -3.0
#define Y_MAX  3.0

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 2 * 72.0

#define FILENAME "kissvg_ApolloniusProblem"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center, *centers;
    kissvg_Circle *C0, *C1;
    kissvg_Canvas2D *canvas;
    double radius;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    radius = 1.0;
    center = kissvg_NewTwoVector(0.0, 0.0);

    C0 = kissvg_CreateCircle(center, radius, canvas);
    C1 = kissvg_EuclideanFindCenter2D(center, center, center);

    centers = kissvg_CircleCircleIntersection(C1, C1);
    kissvg_DrawCircle2D(cr, C0);

    kissvg_DestroyCanvas2D(canvas);
    kissvg_DestroyCircle(C0);
    kissvg_DestroyCircle(C1);
    free(centers);
    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}