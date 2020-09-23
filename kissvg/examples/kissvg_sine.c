/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_sine.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <math.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_Colors.h>
#include <cairo-ps.h>

#define X_MIN -0.5
#define X_MAX  6.8
#define Y_MIN -1.2
#define Y_MAX  1.2

#define X_INCHES 5 * 72.0
#define Y_INCHES 2 * 72.0

static const double x_scale = X_INCHES/(X_MAX - X_MIN);
static const double y_scale = Y_INCHES/(Y_MAX - Y_MIN);

static const double x_shift = 0.5*X_INCHES - 0.5*(X_MIN + X_MAX)*x_scale;
static const double y_shift = 0.5*Y_INCHES - 0.5*(Y_MIN + Y_MAX)*y_scale;

#define kissvg_Coordinates(x, y) x_shift+x_scale*(x), y_shift-y_scale*(y)

#define FILENAME "kissvg_sine.ps"

void draw(cairo_t *cr)
{
    kissvg_Path2D *pathP, *pathQ;
    kissvg_TwoVector P, Q;

    long n, N;
    double x0, y0;
    double x1, y1;
    double dx;

    x0 = 0.0;
    x1 = M_PI;

    N = 200;
    dx = M_PI/N;

    P = kissvg_NewTwoVector(kissvg_Coordinates(x0, 0.0));
    Q = kissvg_NewTwoVector(kissvg_Coordinates(x1, 0.0));

    pathP = kissvg_CreatePath2D(P);
    pathQ = kissvg_CreatePath2D(Q);

    for (n=0; n<N; ++n)
    {
        x0 += dx;
        x1 += dx;
        y0 = sin(x0);
        y1 = sin(x1);

        P = kissvg_NewTwoVector(kissvg_Coordinates(x0, y0));
        Q = kissvg_NewTwoVector(kissvg_Coordinates(x1, y1));

        kissvg_AppendPath2D(pathP, P);
        kissvg_AppendPath2D(pathQ, Q);
    }

    /*  Set this region to Blue, with a bit of green in it.                   */
    kissvg_Path2DSetFillColors(pathP, kissvg_Blue);

    /*  Set the line width for the bounding curve of the region.              */
    kissvg_Path2DSetLineWidth(pathP, 0.8);

    /*  Close the path since we want to fill it in.                           */
    kissvg_Path2DClosePath(pathP);

    /*  Set this region to red.                                               */
    kissvg_Path2DSetFillColors(pathQ, kissvg_Red);

    /*  Set the line width for the bounding curve of the region.              */
    kissvg_Path2DSetLineWidth(pathQ, 0.8);

    /*  Again, we close the path to fill it in.                               */
    kissvg_Path2DClosePath(pathQ);

    kissvg_FillDrawPolygon2D(cr, pathP);
    kissvg_FillDrawPolygon2D(cr, pathQ);

    kissvg_DestroyPath2D(pathP);
    kissvg_DestroyPath2D(pathQ);

    P = kissvg_NewTwoVector(kissvg_Coordinates(X_MIN+0.2, 0.0));
    Q = kissvg_NewTwoVector(kissvg_Coordinates(X_MAX-0.2, 0.0));

    pathP = kissvg_CreatePath2D(P);

    kissvg_AppendPath2D(pathP, Q);
    kissvg_Path2DSetLineWidth(pathP, 1.0);
    kissvg_Path2DCreateArrow(pathP);
    kissvg_Path2DSetArrowSize(pathP, 5.0);

    kissvg_DrawPolygon2D(cr, pathP);
    kissvg_DestroyPath2D(pathP);

    P = kissvg_NewTwoVector(kissvg_Coordinates(0.0, Y_MIN+0.2));
    Q = kissvg_NewTwoVector(kissvg_Coordinates(0.0, Y_MAX-0.2));

    pathP = kissvg_CreatePath2D(P);

    kissvg_AppendPath2D(pathP, Q);
    kissvg_Path2DSetLineWidth(pathP, 1.0);
    kissvg_Path2DCreateArrow(pathP);
    kissvg_Path2DSetArrowSize(pathP, 5.0);

    kissvg_DrawPolygon2D(cr, pathP);
    kissvg_DestroyPath2D(pathP);

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
