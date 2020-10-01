#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <kissvg/include/kissvg.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.0
#define X_MAX  3.0
#define Y_MIN -3.0
#define Y_MAX  3.0

/*  The size of the actual output image.                                      */
#define X_INCHES 2 * 72.0
#define Y_INCHES 2 * 72.0

#define FILENAME "kissvg_ColorsTest"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector A, B, C, center;
    kissvg_Line2D *L0, *L1;
    kissvg_Circle *circle;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    A = kissvg_NewTwoVector(cos(M_PI/3.0), sin(M_PI/3.0));
    B = kissvg_NewTwoVector(cos(3*M_PI/4.0), sin(3*M_PI/4.0));
    C = kissvg_NewTwoVector(-1.0, 0.0);

    circle = kissvg_CreateCircle(A, 0.03, canvas);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_ResetCircle(circle, B, 0.03);
    kissvg_FillDrawCircle2D(cr, circle);
    kissvg_ResetCircle(circle, C, 0.03);
    kissvg_FillDrawCircle2D(cr, circle);

    kissvg_DestroyCircle(circle);

    L0 = kissvg_CreateLineFromTwoPoints(A, B, canvas);
    L1 = kissvg_CreateLineFromTwoPoints(B, C, canvas);
    kissvg_SetLineWidth(L0, 0.3);
    kissvg_SetLineWidth(L1, 0.3);

    kissvg_DrawLine2D(cr, L0, 0.0, 1.0);
    kissvg_DrawLine2D(cr, L1, 0.0, 1.0);
    kissvg_DestroyLine2D(L0);
    kissvg_DestroyLine2D(L1);

    circle = kissvg_EuclideanFindCenter2D(A, B, C);
    kissvg_SetCanvas(circle, canvas);
    kissvg_SetLineWidth(circle, 0.3);
    kissvg_DrawCircle2D(cr, circle);

    L0 = kissvg_CreateLineFromTwoPoints(A, center, canvas);
    L1 = kissvg_CreateLineFromTwoPoints(B, center, canvas);
    kissvg_SetLineWidth(L0, 0.3);
    kissvg_SetLineWidth(L1, 0.3);
    kissvg_DrawLine2D(cr, L0, 0.0, 1.0);
    kissvg_DrawLine2D(cr, L1, 0.0, 1.0);
    kissvg_DestroyLine2D(L0);
    kissvg_DestroyLine2D(L1);
    L0 = kissvg_CreateLineFromTwoPoints(C, center, canvas);
    kissvg_SetLineWidth(L0, 0.3);
    kissvg_DrawLine2D(cr, L0, 0.0, 1.0);
    kissvg_DestroyLine2D(L0);

    center = kissvg_CircleCenter(circle);
    A = kissvg_EuclideanMidPoint2D(A, B);
    B = kissvg_EuclideanMidPoint2D(B, C);

    L0 = kissvg_CreateLineFromTwoPoints(A, center, canvas);
    L1 = kissvg_CreateLineFromTwoPoints(B, center, canvas);
    kissvg_SetLineWidth(L0, 0.3);
    kissvg_SetLineWidth(L1, 0.3);
    kissvg_DrawLine2D(cr, L0, -2.0, 3.0);
    kissvg_DrawLine2D(cr, L1, -2.0, 3.0);
    kissvg_DestroyLine2D(L0);
    kissvg_DestroyLine2D(L1);

    kissvg_ResetCircle(circle, center, 0.03);
    kissvg_FillDrawCircle2D(cr, circle);

    kissvg_DestroyCircle(circle);
    kissvg_DestroyCanvas2D(canvas);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
