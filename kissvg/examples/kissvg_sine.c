#include <stdio.h>
#include <math.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <cairo-ps.h>

#define X_MIN -0.5
#define X_MAX  6.8
#define Y_MIN -1.35
#define Y_MAX  1.3

#define X_INCHES 3 * 72.0
#define Y_INCHES 1 * 72.0

static const double x_scale   = X_INCHES/(X_MAX - X_MIN);
static const double y_scale   = Y_INCHES/(Y_MAX - Y_MIN);
static const double scale     = (x_scale < y_scale ? x_scale : y_scale);
static const double scales[2] = {scale, scale};

static const double x_shift   = 0.5*X_INCHES - 0.5*(X_MIN + X_MAX)*x_scale;
static const double y_shift   = 0.5*Y_INCHES - 0.5*(Y_MIN + Y_MAX)*y_scale;
static const double shifts[2] = {x_shift, y_shift};

#define FILENAME "kissvg_Sine.ps"

void draw(cairo_t *cr)
{
    kissvg_Path2D *pathP, *pathQ;
    kissvg_Canvas2D *canvas;
    kissvg_Axis2D *axis;
    kissvg_Circle *circle;
    kissvg_TwoVector P, Q;
    kissvg_TwoVector A, B, C;

    long n, N;
    double x0, y0;
    double x1, y1;
    double dx;

    canvas = kissvg_CreateCanvas2D(scales, shifts);

    x0 = 0.0;
    x1 = M_PI;

    N = 200;
    dx = M_PI/N;

    P = kissvg_NewTwoVector(x0, 0.0);
    Q = kissvg_NewTwoVector(x1, 0.0);

    pathP = kissvg_CreatePath2D(P, canvas);
    pathQ = kissvg_CreatePath2D(Q, canvas);

    for (n=0; n<N; ++n)
    {
        x0 += dx;
        x1 += dx;
        y0 = sin(x0);
        y1 = sin(x1);

        P = kissvg_NewTwoVector(x0, y0);
        Q = kissvg_NewTwoVector(x1, y1);

        kissvg_AppendPath2D(pathP, P);
        kissvg_AppendPath2D(pathQ, Q);
    }

    /*  Set the first region to fill with the default blue color.             */
    kissvg_SetFillColor(pathP, kissvg_Blue);

    /*  Close the path since we want to fill it in.                           */
    kissvg_SetClosedPath(pathP, kissvg_True);

    /*  Set this region to red.                                               */
    kissvg_SetFillColor(pathQ, kissvg_Red);

    /*  Again, we close the path to fill it in.                               */
    kissvg_SetClosedPath(pathQ, kissvg_True);

    kissvg_FillDrawPolygon2D(cr, pathP);
    kissvg_FillDrawPolygon2D(cr, pathQ);

    kissvg_DestroyPath2D(pathP);
    kissvg_DestroyPath2D(pathQ);

    /*  Create and draw the y-axis.                                           */
    P = kissvg_NewTwoVector(0.0, -1.2);
    Q = kissvg_NewTwoVector(0.0,  1.2);
    axis = kissvg_CreateAxis2D(P, Q, canvas);
    kissvg_Axis2DAddArrow(axis, 0.0, kissvg_DefaultArrowSize, kissvg_Black,
                          kissvg_Black, kissvg_True, kissvg_StealthArrow,
                          kissvg_DefaultArrowLineWidth);

    P = kissvg_NewTwoVector(0.0, -1.0);
    Q = kissvg_NewTwoVector(0.0,  1.0);

    kissvg_Axis2DCreateTicks(axis, P, Q);
    kissvg_Axis2DSetTickDistance(axis, 0.25);
    kissvg_Axis2DSetTickHeight(axis, 0.3);
    kissvg_Axis2DSetTickSemiHeight(axis, 0.2);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, 0.1);

    kissvg_Axis2DUseDownTicks(axis);

    kissvg_DrawAxis2D(cr, axis);

    P = kissvg_NewTwoVector(-0.3, 0.0);
    Q = kissvg_NewTwoVector( 6.5, 0.0);

    kissvg_ResetAxis2D(axis, P, Q);

    P = kissvg_NewTwoVector(0.0, 0.0);
    Q = kissvg_NewTwoVector(6.0, 0.0);
    kissvg_Axis2DCreateTicks(axis, P, Q);
    kissvg_Axis2DSetTickDistance(axis, 0.5);
    kissvg_Axis2DSetTickHeight(axis, 0.3);
    kissvg_Axis2DSetTickSemiHeight(axis, 0.2);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, 0.1);

    kissvg_Axis2DUseUpTicks(axis);
    kissvg_DrawAxis2D(cr, axis);

    P = kissvg_NewTwoVector(0.5, 1.2);
    Q = kissvg_NewTwoVector(4.0, 1.2);

    kissvg_ResetAxis2D(axis, P, Q);
    kissvg_Axis2DUseTicks(axis, kissvg_False);
    kissvg_SetLineWidth(axis, 0.5*kissvg_DefaultPen);
    kissvg_Axis2DAddArrow(axis, 0.4, kissvg_DefaultArrowSize, kissvg_Green,
                          kissvg_Black, kissvg_True, kissvg_StealthArrow,
                          kissvg_DefaultArrowLineWidth);
    kissvg_Axis2DAddArrow(axis, 0.6, kissvg_DefaultArrowSize, kissvg_Green,
                          kissvg_Black, kissvg_False, kissvg_StealthArrow,
                          kissvg_DefaultArrowLineWidth);
    kissvg_DrawAxis2D(cr, axis);
    kissvg_DestroyAxis2D(axis);

    A = kissvg_NewTwoVector(1.0, 1.0);
    B = kissvg_NewTwoVector(2.0, 1.0);
    C = kissvg_NewTwoVector(1.5, 0.5);

    circle = kissvg_FindCenter2D(A, B, C);

    kissvg_SetCanvas(circle, canvas);

    kissvg_SetLineWidth(circle, kissvg_ThickPen);
    kissvg_DrawCircle2D(cr, circle);
    kissvg_DestroyCircle(circle);

    kissvg_CreateCircle(A, 0.02, canvas);
    kissvg_SetLineWidth(circle, 0.01);
    kissvg_SetFillColor(circle, kissvg_Blue);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_DestroyCircle(circle);

    kissvg_CreateCircle(B, 0.02, canvas);
    kissvg_SetFillColor(circle, kissvg_Green);
    kissvg_SetLineWidth(circle, 0.01);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_DestroyCircle(circle);

    kissvg_CreateCircle(C, 0.02, canvas);
    kissvg_SetLineWidth(circle, 0.01);
    kissvg_SetFillColor(circle, kissvg_Red);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_DestroyCircle(circle);

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
