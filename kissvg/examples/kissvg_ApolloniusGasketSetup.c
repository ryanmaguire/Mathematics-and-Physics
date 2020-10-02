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

#define FILENAME "kissvg_ApolloniusGasketSetup"

#define USE_COLORS 1
#ifdef USE_COLORS
#define N_COLORS 26
typedef struct my_colors my_colors;

static kissvg_Color **get_my_colors(void)
{
    kissvg_Color **my_colors = malloc(sizeof(*my_colors) * N_COLORS);
    my_colors[0] = kissvg_Brown;
    my_colors[1] = kissvg_Crimson;
    my_colors[2] = kissvg_Azure;
    my_colors[3] = kissvg_Carrot;
    my_colors[4] = kissvg_Lavender;
    my_colors[5] = kissvg_Magenta;
    my_colors[6] = kissvg_Aqua;
    my_colors[7] = kissvg_DarkGreen;
    my_colors[8] = kissvg_DeepPink;
    return my_colors;
}
#endif

static void DO_DRAW(cairo_t *cr, kissvg_Circle *C1,
                    kissvg_Color **cols, int num)
{

    kissvg_SetLineWidth(C1, kissvg_ThinPen);
#ifdef USE_COLORS
    kissvg_SetFillColor(C1, cols[num]);
    kissvg_FillDrawCircle2D(cr, C1);
#else
    if (!(cols == NULL))
        cols = NULL;
    if (!num == 0)
        num = 0;
    kissvg_DrawCircle2D(cr, C1);
#endif
}

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center, A, B;
    kissvg_Circle *C0;
    kissvg_Circle *C1;
    kissvg_Line2D *L0;
    kissvg_Canvas2D *canvas;
    long n, N;
    kissvg_Color **cols;

#ifdef USE_COLORS
    cols = get_my_colors();
#else
    cols = NULL;
#endif

    N = 25;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    center = kissvg_NewTwoVector(0.0, -2.0);
    C0 = kissvg_CreateCircle(center, 2.0, canvas);
    C1 = kissvg_CreateCircle(center, 1.0, canvas);

    for (n=-N; n<N; ++n)
    {
        center = kissvg_NewTwoVector(-n, -0.5);
        kissvg_ResetCircle(C1, center, 0.5);
        DO_DRAW(cr, C1, cols, 0);

        center = kissvg_NewTwoVector(0.5-n, -0.125);
        kissvg_ResetCircle(C1, center, 0.125);
        DO_DRAW(cr, C1, cols, 1);

        center = kissvg_NewTwoVector(0.5-n, -0.875);
        kissvg_ResetCircle(C1, center, 0.125);
        DO_DRAW(cr, C1, cols, 2);

        center = kissvg_NewTwoVector(0.5-n, -0.70834);
        kissvg_ResetCircle(C1, center, 0.0416533311993);
        DO_DRAW(cr, C1, cols, 3);

        center = kissvg_NewTwoVector(0.5-n, -0.29166);
        kissvg_ResetCircle(C1, center, 0.0416533311993);
        DO_DRAW(cr, C1, cols, 4);

        center = kissvg_NewTwoVector(0.3333333-n, -0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);
        DO_DRAW(cr, C1, cols, 5);

        center = kissvg_NewTwoVector(0.6666666667-n, -0.0556);
        kissvg_ResetCircle(C1, center, 0.0556776436283);
        DO_DRAW(cr, C1, cols, 6);

        center = kissvg_NewTwoVector(0.3333333-n, -0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);
        DO_DRAW(cr, C1, cols, 7);

        center = kissvg_NewTwoVector(0.6666666667-n, -0.9444);
        kissvg_ResetCircle(C1, center, 0.0556776436283);
        DO_DRAW(cr, C1, cols, 8);
    }

    center = kissvg_NewTwoVector(0.0, -1.0);
    kissvg_ResetCircle(C1, center, 1.0);
    kissvg_DrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, 0.0);
    kissvg_ResetCircle(C1, center, 2.0);
    kissvg_DrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0.0, -2.0);
    kissvg_ResetCircle(C1, center, 2.0);
    kissvg_DrawCircle2D(cr, C1);

    kissvg_DestroyCircle(C0);
    kissvg_DestroyCircle(C1);

    A = kissvg_NewTwoVector(-1.0, -1.0);
    B = kissvg_NewTwoVector(1.0, -1.0);

    L0 = kissvg_CreateLineFromTwoPoints(A, B, canvas);
    kissvg_DrawLine2D(cr, L0, -3.0, 3.0);
    kissvg_DestroyLine2D(L0);

    A = kissvg_NewTwoVector(-1.0, 0.0);
    B = kissvg_NewTwoVector(1.0, 0.0);
    L0 = kissvg_CreateLineFromTwoPoints(A, B, canvas);
    kissvg_DrawLine2D(cr, L0, -3.0, 3.0);
    kissvg_DestroyLine2D(L0);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
