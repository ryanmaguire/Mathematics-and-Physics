/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <cairo-ps.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.5
#define X_MAX  3.5
#define Y_MIN -2.0
#define Y_MAX  2.0

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

#define FILENAME "kissvg_EuclidBookOnePropOne.ps"

void draw(cairo_t *cr)
{
    kissvg_TwoVector P, Q, A;
    kissvg_Circle *C1, *C2;
    kissvg_TwoVector *intersection;
    kissvg_Canvas2D *canvas;
    kissvg_Path2D *path;
    double radius;
    double thin_width, thick_width;

    thin_width = 0.5;
    thick_width = 0.8;
    canvas = kissvg_CreateCanvas2D(scales, shifts);

    P = kissvg_NewTwoVector(-1.0, 0.0);
    Q = kissvg_NewTwoVector( 1.0, 0.0);

    radius = kissvg_EuclideanNorm2D(kissvg_TwoVectorSubtract(P, Q));

    C1 = kissvg_CreateCircle(P, radius, canvas);
    C2 = kissvg_CreateCircle(Q, radius, canvas);

    intersection = kissvg_CircleCircleIntersection(C1, C2);

    if (intersection == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_EuclidBookOnePropOne\n\n"
            "intersection variable returned NULL."
        );
        exit(0);
    }

    A = intersection[1];

    path = kissvg_CreatePath2D(P, canvas);
    kissvg_AppendPath2D(path, Q);
    kissvg_AppendPath2D(path, A);

    kissvg_Path2DSetFillColor(path, kissvg_Green);
    kissvg_Path2DSetLineColor(path, kissvg_Black);
    kissvg_Path2DSetLineWidth(path, thin_width);
    kissvg_Path2DClosePath(path);

    /*  kissvg_CircleCircleIntersection allocates memory for the pointer, so  *
     *  we need to free it.                                                   */
    free(intersection);

    kissvg_CircleCreateArrow(C2, 0.2, kissvg_DefaultArrow, kissvg_Green, kissvg_Black, kissvg_False);
    kissvg_CircleSetFillColor(C2, kissvg_White);

    kissvg_DrawCircle2D(cr, C1);
    kissvg_DrawCircle2D(cr, C2);
    kissvg_FillDrawPolygon2D(cr, path);

    kissvg_DestroyCircle(C1);
    kissvg_DestroyCircle(C2);
    kissvg_DestroyCanvas2D(canvas);
    kissvg_DestroyPath2D(path);

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
