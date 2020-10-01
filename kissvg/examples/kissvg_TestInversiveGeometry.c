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

#define FILENAME "kissvg_TestInversiveGeometry"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_TwoVector A, B;
    kissvg_Circle *circle0, *circle1, *inv_circle;
    kissvg_Line2D *L0;
    kissvg_Canvas2D *canvas;
    double r0, r1;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    center = kissvg_NewTwoVector(0.0, 0.0);
    r0 = 1.0;
    circle0 = kissvg_CreateCircle(center, r0, canvas);
    kissvg_DrawCircle2D(cr, circle0);

    center = kissvg_NewTwoVector(0.2, 0.3);
    r1 = 0.3;
    circle1 = kissvg_CreateCircle(center, r1, canvas);
    inv_circle = kissvg_InversiveGeometryCircle(circle0, circle1);
    kissvg_SetLineWidth(circle1, kissvg_ThinPen);
    kissvg_SetLineColor(circle1, kissvg_Aqua);
    kissvg_SetLineColor(inv_circle, kissvg_Aqua);
    kissvg_DrawCircle2D(cr, circle1);
    kissvg_DrawCircle2D(cr, inv_circle);
    kissvg_DestroyCircle(inv_circle);

    center = kissvg_NewTwoVector(0.0, 0.7);
    r1 = 0.5;
    kissvg_ResetCircle(circle1, center, r1);
    inv_circle = kissvg_InversiveGeometryCircle(circle0, circle1);
    kissvg_SetLineWidth(inv_circle, kissvg_ThinPen);
    kissvg_SetLineColor(circle1, kissvg_Crimson);
    kissvg_SetLineColor(inv_circle, kissvg_Crimson);
    kissvg_DrawCircle2D(cr, circle1);
    kissvg_DrawCircle2D(cr, inv_circle);
    kissvg_DestroyCircle(inv_circle);
    kissvg_DestroyCircle(circle1);

    A = kissvg_NewTwoVector(-r0, 0.0);
    B = kissvg_NewTwoVector(0.0, -r0);

    L0 = kissvg_CreateLineFromTwoPoints(A, B, canvas);
    circle1 = kissvg_InversiveGeometryLine(circle0, L0);
    kissvg_SetLineWidth(circle1, kissvg_ThinPen);
    kissvg_SetLineWidth(L0, kissvg_ThinPen);
    kissvg_SetLineColor(circle1, kissvg_Blue);
    kissvg_SetLineColor(L0, kissvg_Blue);
    kissvg_DrawLine2D(cr, L0, -3.0, 3.0);
    kissvg_DrawCircle2D(cr, circle1);
    kissvg_DestroyLine2D(L0);
    kissvg_DestroyCircle(circle1);

    A = kissvg_TwoVectorScale(2.3, A);
    B = kissvg_TwoVectorScale(2.3, B);

    L0 = kissvg_CreateLineFromTwoPoints(A, B, canvas);
    circle1 = kissvg_InversiveGeometryLine(circle0, L0);
    kissvg_SetLineWidth(circle1, kissvg_ThinPen);
    kissvg_SetLineWidth(L0, kissvg_ThinPen);
    kissvg_SetLineColor(circle1, kissvg_Green);
    kissvg_SetLineColor(L0, kissvg_Green);
    kissvg_DrawLine2D(cr, L0, -3.0, 3.0);
    kissvg_DrawCircle2D(cr, circle1);
    kissvg_DestroyLine2D(L0);
    kissvg_DestroyCircle(circle1);

    kissvg_DestroyCircle(circle0);
    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
