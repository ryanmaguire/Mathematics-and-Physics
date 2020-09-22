/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_circle.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <math.h>
#include <kissvg/include/kissvg.h>
#include <cairo-ps.h>

#define X_INCHES 5 * 72.0
#define Y_INCHES 2 * 72.0
#define FILENAME "kissvg_circle.ps"

static const double x_shift = 0.1*X_INCHES;
static const double y_shift = 0.5*Y_INCHES;
static const double x_scale = X_INCHES/8.2;
static const double y_scale = Y_INCHES/4.2;

void draw(cairo_t *cr)
{
    kissvg_Path2D *path;
    kissvg_TwoVector P;

    long n, N;
    double x, y, dx;

    x = 0.0;

    N = 100;
    dx = M_PI/N;

    P = kissvg_NewTwoVector(x_shift, y_shift);
    path = kissvg_CreatePath2D(P);

    for (n=0; n<N; ++n)
    {
        x += dx;
        y = sin(x);
        P = kissvg_NewTwoVector(x_shift+x_scale*x, y_shift-y_scale*y);

        kissvg_AppendPath2D(path, P);
    }

    kissvg_Path2DSetColors(path, 0.1, 0.5, 10.0);
    kissvg_Path2DSetLineWidth(path, 0.8);
    kissvg_Path2DClosePath(path);
    kissvg_FillDrawPolygon2D(cr, path);

    kissvg_DestroyPath2D(path);

    path = kissvg_CreatePath2D(P);

    for (n=0; n<N; ++n)
    {
        x += dx;
        y = sin(x);
        P = kissvg_NewTwoVector(x_shift+x_scale*x, y_shift-y_scale*y);

        kissvg_AppendPath2D(path, P);
    }

    kissvg_Path2DSetColors(path, 10.0, 0.2, 0.0);
    kissvg_Path2DSetLineWidth(path, 0.8);
    kissvg_Path2DClosePath(path);
    kissvg_FillDrawPolygon2D(cr, path);
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
