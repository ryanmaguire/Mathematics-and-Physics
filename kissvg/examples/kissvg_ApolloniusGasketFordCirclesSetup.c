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

static long GCD(long n0, long n1)
{
    while(n0 != n1)
    {
        if(n0 > n1)
            n0 -= n1;
        else
            n1 -= n0;
    }
    return n0;
}

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
    kissvg_TwoVector center;
    kissvg_Circle *C0;
    kissvg_Circle *C1;
    kissvg_Canvas2D *canvas;
    long ell, m, n, M, N;
    double radius, x, y;
    kissvg_Color **cols;

#ifdef USE_COLORS
    cols = get_my_colors();
#else
    cols = NULL;
#endif

    N = 25;
    M = 9;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    center = kissvg_NewTwoVector(0.0, -2.0);
    C0 = kissvg_CreateCircle(center, 2.0, canvas);

    center = kissvg_NewTwoVector(0.0, 0.0);
    C1 = kissvg_CreateCircle(center, 2.0, canvas);
    kissvg_DrawCircle2D(cr, C1);

    kissvg_SetLineWidth(C1, kissvg_ThinPen);

    for (n=-N; n<=N; ++n)
    {
        for (m=1; m<=M; ++m)
        {
            radius = 1.0/(2.0*m*m);
            y = radius;
            for (ell=1; ell<=m; ++ell)
            {
                if (GCD(ell, m) == 1)
                {
                    x = ((double)ell)/((double)m);
                    center = kissvg_NewTwoVector(x - n, y-1);
                    kissvg_ResetCircle(C1, center, radius);
                    DO_DRAW(cr, C1, cols, m-1);
                    center = kissvg_NewTwoVector(x - n, -y);
                    kissvg_ResetCircle(C1, center, radius);
                    DO_DRAW(cr, C1, cols, m-1);
                }
            }
        }
    }

    center = kissvg_NewTwoVector(0.0, -1.0);
    kissvg_ResetCircle(C1, center, 1.0);
    kissvg_DrawCircle2D(cr, C1);

    kissvg_DestroyCircle(C0);
    kissvg_DestroyCircle(C1);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
