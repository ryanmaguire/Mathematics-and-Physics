#include <stdio.h>
#include <math.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>

#define X_MIN -0.2
#define X_MAX  6.3
#define Y_MIN -1.35
#define Y_MAX  1.35

#define X_INCHES 6 * 72.0
#define Y_INCHES 2 * 72.0

#define FILENAME "kissvg_Sine"

static void draw(cairo_t *cr)
{
    kissvg_Path2D *pathP, *pathQ;
    kissvg_Canvas2D *canvas;
    kissvg_Axis2D *axis;
    kissvg_Circle *circle;
    kissvg_Arrow *arrow;
    kissvg_TwoVector P, Q;
    kissvg_TwoVector A, B, C;

    long n, N, current_arrow;
    double x0, y0;
    double x1, y1;
    double dx;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True,
                                   kissvg_PDF);

    x0 = 0.0;
    x1 = M_PI;

    N = 200;
    dx = M_PI/N;

    P = kissvg_NewTwoVector(x0, 0.0);
    Q = kissvg_NewTwoVector(x1, 0.0);

    pathP = kissvg_CreatePath2D(P, canvas);
    pathQ = kissvg_CreatePath2D(Q, canvas);
    current_arrow = 0;

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

        if (((n % 50) == 0) && (n != 0))
        {
            kissvg_Path2DAddArrow(pathP, ((double)n) / ((double)N),
                                  0.8*kissvg_DefaultArrowSize,
                                  kissvg_StealthArrow);

            arrow = kissvg_nthArrow(pathP, current_arrow);
            kissvg_SetFillColor(arrow, kissvg_Aqua);

            kissvg_Path2DAddArrow(pathQ, ((double)n) / ((double)N),
                                  0.8*kissvg_DefaultArrowSize,
                                  kissvg_StealthArrow);
            arrow = kissvg_nthArrow(pathQ, current_arrow);
            kissvg_SetFillColor(arrow, kissvg_Aqua);

            current_arrow += 1;
        }
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

    kissvg_DestroyPath2D(&pathP);
    kissvg_DestroyPath2D(&pathQ);

    /*  Create and draw the y-axis.                                           */
    P = kissvg_NewTwoVector(0.0, -1.2);
    Q = kissvg_NewTwoVector(0.0,  1.2);

    axis = kissvg_CreateAxis2D(P, Q, canvas);

    kissvg_Axis2DChangeEndArrow(axis, 1.0, kissvg_DefaultArrowSize,
                                kissvg_Black, kissvg_Black,
                                kissvg_StealthArrow, 0.5*kissvg_ThinPen);
    kissvg_Axis2DAddArrow(axis, 0.0, kissvg_DefaultArrowSize, kissvg_Black,
                          kissvg_Black, kissvg_ReverseStealthArrow,
                          0.1*kissvg_ThinPen);

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
    kissvg_Axis2DResetTicks(axis, P, Q);
    kissvg_DrawAxis2D(cr, axis);

    P = kissvg_NewTwoVector(0.5, 1.2);
    Q = kissvg_NewTwoVector(4.0, 1.2);
    kissvg_ResetAxis2D(axis, P, Q);

    kissvg_Axis2DUseTicks(axis, kissvg_False);
    kissvg_SetLineWidth(axis, 0.5*kissvg_DefaultPen);
    kissvg_Axis2DAddArrow(axis, 0.4, kissvg_DefaultArrowSize, kissvg_Green,
                          kissvg_Black, kissvg_ReverseStealthArrow,
                          kissvg_ThinPen);
    kissvg_Axis2DAddArrow(axis, 0.6, kissvg_DefaultArrowSize, kissvg_Green,
                          kissvg_Black, kissvg_StealthArrow, kissvg_ThinPen);
    kissvg_DrawAxis2D(cr, axis);
    kissvg_DestroyAxis2D(axis);

    A = kissvg_NewTwoVector(1.0, 1.0);
    B = kissvg_NewTwoVector(2.0, 1.0);
    C = kissvg_NewTwoVector(1.5, 0.5);

    circle = kissvg_EuclideanFindCenter2D(A, B, C);
    kissvg_SetCanvas(circle, canvas);
    kissvg_DrawCircle2D(cr, circle);

    kissvg_ResetCircle(circle, A, 0.02);
    kissvg_SetLineWidth(circle, kissvg_ThinPen);
    kissvg_SetFillColor(circle, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, circle);

    kissvg_ResetCircle(circle, B, 0.02);
    kissvg_SetFillColor(circle, kissvg_Teal);
    kissvg_FillDrawCircle2D(cr, circle);

    kissvg_ResetCircle(circle, C, 0.02);
    kissvg_SetFillColor(circle, kissvg_Magenta);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_DestroyCircle(circle);

    kissvg_DestroyCanvas2D(&canvas);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
