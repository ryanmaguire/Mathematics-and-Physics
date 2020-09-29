/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_colors.h>
#include <cairo-ps.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -2.2
#define X_MAX  2.2
#define Y_MIN -2.2
#define Y_MAX  2.2

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 3 * 72.0

#define FILENAME "kissvg_ApolloniusGasket.ps"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C0, *C00;
    kissvg_Circle *C1;
    kissvg_Circle *Current_Circle;
    kissvg_Canvas2D *canvas;
    double radius;
    double small_radius;
    long n, N;

    N = 25;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True);

    radius = 2.0;
    center = kissvg_NewTwoVector(0.0, -2.0);
    C0 = kissvg_CreateCircle(center, radius, canvas);

    center = kissvg_NewTwoVector(0.0, 2.0);
    C00 = kissvg_CreateCircle(center, radius, canvas);

    center = kissvg_NewTwoVector(0.0, 0.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_DrawCircle2D(cr, C1);

    radius = 0.5;
    small_radius = 0.125;
    kissvg_SetLineWidth(C1, kissvg_ThinPen);

    for (n=-N; n<N; ++n)
    {
        center = kissvg_NewTwoVector(-n, -0.5);
        kissvg_ResetCircle(C1, center, radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, -0.125);
        kissvg_ResetCircle(C1, center, small_radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, -0.875);
        kissvg_ResetCircle(C1, center, small_radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, -0.70834);
        kissvg_ResetCircle(C1, center, 0.0416533311993);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, -0.29166);
        kissvg_ResetCircle(C1, center, 0.0416533311993);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.3333333-n, -0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.6666666667-n, -0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.3333333-n, -0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.6666666667-n, -0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C0, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);



        center = kissvg_NewTwoVector(-n, 0.5);
        kissvg_ResetCircle(C1, center, radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);
        kissvg_DestroyCircle(Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, 0.125);
        kissvg_ResetCircle(C1, center, small_radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, 0.875);
        kissvg_ResetCircle(C1, center, small_radius);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, 0.70834);
        kissvg_ResetCircle(C1, center, 0.0416533311993);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.5-n, 0.29166);
        kissvg_ResetCircle(C1, center, 0.0416533311993);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.3333333-n, 0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.6666666667-n, 0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.3333333-n, 0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);

        center = kissvg_NewTwoVector(0.6666666667-n, 0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);

        Current_Circle = kissvg_InversiveGeometryCircle(C00, C1);
        kissvg_SetLineWidth(Current_Circle, kissvg_ThinPen);
        kissvg_DrawCircle2D(cr, Current_Circle);
    }

    kissvg_DestroyCircle(C0);
    kissvg_DestroyCircle(C00);

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
