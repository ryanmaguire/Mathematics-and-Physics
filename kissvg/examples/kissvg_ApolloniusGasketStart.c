#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -2.2
#define X_MAX  2.2
#define Y_MIN -2.2
#define Y_MAX  2.2

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 3 * 72.0

#define FILENAME "kissvg_ApolloniusGasketStart"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C0;
    kissvg_Canvas2D *canvas;


    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    center = kissvg_NewTwoVector(0.0, 0.0);
    C0 = kissvg_CreateCircle(center, 2.0, canvas);
    kissvg_DrawCircle2D(cr, C0);

    center = kissvg_NewTwoVector(0.0, -1.0);
    kissvg_ResetCircle(C0, center, 1.0);
    kissvg_DrawCircle2D(cr, C0);

    center = kissvg_NewTwoVector(0.0, 1.0);
    kissvg_ResetCircle(C0, center, 1.0);
    kissvg_DrawCircle2D(cr, C0);
    kissvg_DestroyCircle(C0);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
