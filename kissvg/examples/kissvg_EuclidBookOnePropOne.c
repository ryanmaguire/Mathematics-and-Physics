/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <cairo/src/cairo-pdf.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.5
#define X_MAX  3.5
#define Y_MIN -2.0
#define Y_MAX  2.0

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 2 * 72.0

#define FILENAME "kissvg_EuclidBookOnePropOne"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector P, Q, A;
    kissvg_Circle *C1, *C2;
    kissvg_TwoVector *intersection;
    kissvg_Canvas2D *canvas;
    kissvg_Path2D *path;
    double radius;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

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
    kissvg_SetFillColor(path, kissvg_Green);
    kissvg_SetLineColor(path, kissvg_Black);
    kissvg_SetLineWidth(path, kissvg_DefaultPen);
    kissvg_SetClosedPath(path, kissvg_True);

    /*  kissvg_CircleCircleIntersection allocates memory for the pointer, so  *
     *  we need to free it.                                                   */
    free(intersection);

    kissvg_CircleCreateArrow(C1, 0.1, kissvg_DefaultArrowSize, kissvg_Green,
                             kissvg_Black, kissvg_False, kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    kissvg_CircleAddArrow(C1, 0.2, kissvg_DefaultArrowSize, kissvg_Green,
                             kissvg_Black, kissvg_False, kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    kissvg_CircleAddArrow(C1, 0.3, kissvg_DefaultArrowSize, kissvg_Green,
                             kissvg_Black, kissvg_False, kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    kissvg_CircleAddArrow(C1, 0.4, kissvg_DefaultArrowSize, kissvg_Green,
                             kissvg_Black, kissvg_False, kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    kissvg_CircleAddArrow(C1, 0.5, kissvg_DefaultArrowSize, kissvg_Green,
                             kissvg_Black, kissvg_False, kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    kissvg_DrawCircle2D(cr, C1);
    kissvg_DrawCircle2D(cr, C2);
    kissvg_FillDrawPolygon2D(cr, path);

    kissvg_DestroyCircle(C1);
    kissvg_DestroyCircle(C2);
    kissvg_DestroyCanvas2D(&canvas);
    kissvg_DestroyPath2D(path);

    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
