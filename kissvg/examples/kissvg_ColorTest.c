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

#define FILENAME "kissvg_Colors.ps"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C1;
    kissvg_Canvas2D *canvas;
    double radius;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True);
    radius = 0.5;

    center = kissvg_NewTwoVector(-2.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Blue);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-1.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Green);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(0.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Red);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Black);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Black);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(2.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_DarkGray);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-2.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Gray);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-1.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_LightGray);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(0.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_White);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(2.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Purple);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-2.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Violet);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-1.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Pink);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(0.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Yellow);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Crimson);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(2.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_DarkGreen);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-2.0, -1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Orange);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-1.0, -1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_LightBlue);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(0.0, -1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Teal);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, -1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_DarkBlue);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(2.0, -1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Lavender);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-2.0, -2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Magenta);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-1.0, -2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_DeepPink);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(0.0, -2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Azure);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(1.0, -2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Silver);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(2.0, -2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Sand);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-3.0, -0.5);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Marine);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(-3.0, 0.5);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Lime);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(3.0, -0.5);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Carrot);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    center = kissvg_NewTwoVector(3.0, 0.5);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Brown);
    kissvg_FillDrawCircle2D(cr, C1);
    kissvg_DestroyCircle(C1);

    kissvg_DestroyCanvas2D(canvas);
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