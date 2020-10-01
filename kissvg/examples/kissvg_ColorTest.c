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

#define FILENAME "kissvg_ColorsTest"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C1;
    kissvg_Canvas2D *canvas;
    double radius;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);
    radius = 0.5;

    center = kissvg_NewTwoVector(-2.0, 2.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Blue);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, 2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Green);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, 2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Red);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, 2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Black);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, 2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Black);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(2.0, 2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_DarkGray);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-2.0, 1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Gray);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, 1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_LightGray);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, 1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_White);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, 1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(2.0, 1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Purple);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-2.0, 0.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Violet);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, 0.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Pink);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, 0.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Yellow);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, 0.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Crimson);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(2.0, 0.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_DarkGreen);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-2.0, -1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Orange);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, -1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_LightBlue);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, -1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Teal);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, -1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_DarkBlue);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(2.0, -1.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Lavender);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-2.0, -2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Magenta);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-1.0, -2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_DeepPink);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, -2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Azure);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(1.0, -2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Silver);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(2.0, -2.0);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Sand);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-3.0, -0.5);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Marine);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(-3.0, 0.5);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Lime);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(3.0, -0.5);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Carrot);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(3.0, 0.5);
    kissvg_ResetCircle(C1, center, radius);
    kissvg_SetFillColor(C1, kissvg_Brown);
    kissvg_FillDrawCircle2D(cr, C1);

    kissvg_DestroyCircle(C1);
    kissvg_DestroyCanvas2D(canvas);
    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}