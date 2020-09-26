/*
 *  Compile with:
 *      gcc-10 -std=c89 -pedantic -pedantic-errors -Wall -Wextra -I../../ \
 *      -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes \
 *      $(pkg-config --cflags --libs cairo) -c kissvg.c
 *
 *      gcc kissvg.o -shared -o libkissvg.so -lcairo
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>
#include <cairo.h>

kissvg_TwoVector kissvg_NewTwoVector(double x, double y)
{
    kissvg_TwoVector NewVector;

    NewVector.dat[0] = x;
    NewVector.dat[1] = y;

    return NewVector;
}

kissvg_TwoVector kissvg_TwoVectorAdd(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    kissvg_TwoVector sum;

    sum.dat[0] = kissvg_TwoVectorXComponent(P) + kissvg_TwoVectorXComponent(Q);
    sum.dat[1] = kissvg_TwoVectorYComponent(P) + kissvg_TwoVectorYComponent(Q);

    return sum;
}

kissvg_TwoVector kissvg_TwoVectorSubtract(kissvg_TwoVector P,
                                          kissvg_TwoVector Q)
{
    kissvg_TwoVector sum;

    sum.dat[0] = kissvg_TwoVectorXComponent(P)-kissvg_TwoVectorXComponent(Q);
    sum.dat[1] = kissvg_TwoVectorYComponent(P)-kissvg_TwoVectorYComponent(Q);

    return sum;
}

kissvg_TwoVector kissvg_TwoVectorScale(double r, kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double x_new, y_new;
    double x0, y0;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    x_new = r*x0;
    y_new = r*y0;

    out = kissvg_NewTwoVector(x_new, y_new);
    return out;
}

double kissvg_EuclideanNorm2D(kissvg_TwoVector P)
{
    double x_comp, y_comp;
    double norm;

    x_comp = kissvg_TwoVectorXComponent(P);
    y_comp = kissvg_TwoVectorYComponent(P);

    norm = sqrt(x_comp*x_comp + y_comp*y_comp);
    return norm;
}

double kissvg_DotProduct2D(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    double x0, y0;
    double x1, y1;
    double dot_product;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    x1 = kissvg_TwoVectorXComponent(Q);
    y1 = kissvg_TwoVectorYComponent(Q);

    dot_product = x0*x1 + y0*y1;

    return dot_product;
}

kissvg_TwoVector kissvg_MidPoint2D(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    double x0, y0;
    double x1, y1;
    double xmid, ymid;
    kissvg_TwoVector midpoint;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    x1 = kissvg_TwoVectorXComponent(Q);
    y1 = kissvg_TwoVectorYComponent(Q);

    xmid = 0.5*(x0 + x1);
    ymid = 0.5*(y0 + y1);

    midpoint = kissvg_NewTwoVector(xmid, ymid);

    return midpoint;
}

double kissvg_RelAngle2D(kissvg_TwoVector O,
                         kissvg_TwoVector P,
                         kissvg_TwoVector Q)
{
    double dot_prod;
    double abs_prod;
    double rel_angle;
    kissvg_TwoVector OP;
    kissvg_TwoVector OQ;

    OP = kissvg_TwoVectorSubtract(P, O);
    OQ = kissvg_TwoVectorSubtract(Q, O);

    dot_prod = kissvg_DotProduct2D(OP, OQ);
    abs_prod = kissvg_EuclideanNorm2D(OP)*kissvg_EuclideanNorm2D(OQ);

    if (abs_prod == 0.0)
        rel_angle = kissvg_NaN;
    else
        rel_angle = acos(dot_prod/abs_prod);

    return rel_angle;
}

kissvg_Bool kissvg_IsCollinear(kissvg_TwoVector A,
                               kissvg_TwoVector B,
                               kissvg_TwoVector C)
{
    kissvg_TwoVector AB;
    kissvg_TwoVector AC;
    double ABx, ABy;
    double ACx, ACy;
    double det;

    AB = kissvg_TwoVectorSubtract(B, A);
    AC = kissvg_TwoVectorSubtract(C, A);

    ABx = kissvg_TwoVectorXComponent(AB);
    ABy = kissvg_TwoVectorYComponent(AB);

    ACx = kissvg_TwoVectorXComponent(AC);
    ACy = kissvg_TwoVectorYComponent(AC);

    det = ABx*ACy - ABy*ACx;

    if (det == 0.0)
        return kissvg_True;
    else
        return kissvg_False;
}

kissvg_TwoVector kissvg_LineLineIntersection(kissvg_TwoVector P0,
                                             kissvg_TwoVector V0,
                                             kissvg_TwoVector P1,
                                             kissvg_TwoVector V1)
{
    kissvg_TwoVector inter;
    kissvg_TwoVector P1P0;
    kissvg_TwoByTwoMatrix A, inverseA;
    double v0x, v0y;
    double v1x, v1y;

    double interx, intery;

    double det;

    v0x = kissvg_TwoVectorXComponent(V0);
    v0y = kissvg_TwoVectorYComponent(V0);

    v1x = kissvg_TwoVectorXComponent(V1);
    v1y = kissvg_TwoVectorYComponent(V1);

    det = v1x*v0y -v0x*v1y;

    if (det == 0.0)
    {
        interx = kissvg_Infinity;
        intery = kissvg_Infinity;
        inter = kissvg_NewTwoVector(interx, intery);

        return inter;
    }
    else
    {
        P1P0 = kissvg_TwoVectorSubtract(P1, P0);
        A = kissvg_NewTwoByTwoMatrix(v0x, -v1x, v0y, -v1y);
        inverseA = kissvg_InverseTwoByTwoMatrix(A);
        inter = kissvg_TwoVectorMatrixTransform(inverseA, P1P0);
        return inter;
    }
}

kissvg_TwoVector kissvg_FindCenter2D(kissvg_TwoVector A,
                                     kissvg_TwoVector B,
                                     kissvg_TwoVector C)
{
    kissvg_TwoVector U;
    kissvg_TwoVector V;
    kissvg_TwoVector center;

    if (kissvg_IsCollinear(A, B, C))
    {
        center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
    }
    else
    {
        U = kissvg_TwoVectorSubtract(A, B);
        V = kissvg_TwoVectorSubtract(A, C);

        center = kissvg_LineLineIntersection(B, U, C, V);
    }
    return center;
}

kissvg_TwoVector kissvg_PlaneToDiskHomeo(kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double px, py;
    double outx, outy;
    double norm;
    double scale_factor;

    px = kissvg_TwoVectorXComponent(P);
    py = kissvg_TwoVectorYComponent(P);

    if ((px == 0.0) && (py == 0.0))
    {
        outx = 0.0;
        outy = 0.0;
    }
    else
    {
        norm = kissvg_EuclideanNorm2D(P);
        outx = px/norm;
        outy = py/norm;

        scale_factor = (-1.0 + sqrt(4.0*norm*norm + 1.0))/(2.0*norm);

        outx *= scale_factor;
        outy *= scale_factor;
    }
    out = kissvg_NewTwoVector(outx, outy);

    return out;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                 Begin kissvg_TwoByTwoMatrix Functions                      *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_TwoByTwoMatrix kissvg_NewTwoByTwoMatrix(double a, double b,
                                               double c, double d)
{
    kissvg_TwoByTwoMatrix A;

    A.dat[0][0] = a;
    A.dat[0][1] = b;
    A.dat[1][0] = c;
    A.dat[1][1] = d;

    return A;
}

kissvg_TwoVector kissvg_TwoVectorMatrixTransform(kissvg_TwoByTwoMatrix A,
                                                 kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double x_new, y_new;
    double x0, y0;
    double a, b, c, d;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    a = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    b = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    c = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    d = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    x_new = a*x0 + b*y0;
    y_new = c*x0 + d*y0;

    out = kissvg_NewTwoVector(x_new, y_new);
    return out;
}

kissvg_TwoByTwoMatrix kissvg_RotationMatrix2D(double theta)
{
    double cos_theta, sin_theta;
    kissvg_TwoByTwoMatrix R;

    cos_theta = cos(theta);
    sin_theta = sin(theta);

    R = kissvg_NewTwoByTwoMatrix(cos_theta, -sin_theta, sin_theta, cos_theta);
    return R;
}

kissvg_TwoByTwoMatrix kissvg_TwoByTwoMatrixScale(double r,
                                                 kissvg_TwoByTwoMatrix A)
{
    kissvg_TwoByTwoMatrix out;
    double a00, a01, a10, a11;

    a00 = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    a01 = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    a10 = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    a11 = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    out = kissvg_NewTwoByTwoMatrix(r*a00, r*a01, r*a10, r*a11);
    return out;
}

kissvg_TwoByTwoMatrix kissvg_InverseTwoByTwoMatrix(kissvg_TwoByTwoMatrix A)
{
    double a, b, c, d, det, det_rcp;
    double ainv, binv, cinv, dinv;

    a = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    b = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    c = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    d = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    det = a*d - b*c;

    if (det == 0)
    {
        ainv = kissvg_NaN;
        binv = kissvg_NaN;
        cinv = kissvg_NaN;
        dinv = kissvg_NaN;
    }
    else
    {
        det_rcp = 1.0/det;
        ainv = d*det_rcp;
        binv = -b*det_rcp;
        cinv = -c*det_rcp;
        dinv = a*det_rcp;
    }
    return kissvg_NewTwoByTwoMatrix(ainv, binv, cinv, dinv);
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                   Begin kissvg_Canvas2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_Canvas2D *kissvg_CreateCanvas2D(const double scales[2],
                                       const double shifts[2])
{
    kissvg_Canvas2D *canvas;

    canvas = malloc(sizeof(*canvas));

    canvas->x_scale = scales[0];
    canvas->y_scale = scales[1];
    canvas->x_shift = shifts[0];
    canvas->y_shift = shifts[1];

    return canvas;
}

void kissvg_DestroyCanvas2D(kissvg_Canvas2D *canvas)
{
    free(canvas);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Color Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_Color *kissvg_CreateColor(double red, double green, double blue)
{
    kissvg_Color *color;

    color = malloc(sizeof(*color));
    color->dat[0] = red;
    color->dat[1] = green;
    color->dat[2] = blue;
    return color;
}

void kissvg_DestroyColor(kissvg_Color *color)
{
    free(color);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Arrow Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

void kissvg_ArrowSetReverse(kissvg_Arrow *arrow, kissvg_Bool reverse)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetReverse\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->reverse_arrow = reverse;
    return;
}

void kissvg_ArrowSetType(kissvg_Arrow *arrow, kissvg_ArrowType type)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetType\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_type = type;
    return;
}
void kissvg_ArrowSetPos(kissvg_Arrow *arrow, double pos)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetPos\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_pos = pos;
    return;
}

void kissvg_ArrowSetFillColor(kissvg_Arrow *arrow, kissvg_Color *fill_color)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetFillColor\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_fill_color = fill_color;
    return;
}

void kissvg_ArrowSetLineColor(kissvg_Arrow *arrow, kissvg_Color *line_color)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetLineColor\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_color = line_color;
    return;
}

void kissvg_ArrowSetSize(kissvg_Arrow *arrow, double size)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetSize\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_size = size;
    return;
}

void kissvg_ArrowSetLineWidth(kissvg_Arrow *arrow, double width)
{
    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ArrowSetLineWidth\n\n"
             "Input arrow is NULL. Aborting.\n\n");
        exit(0);
    }

    arrow->arrow_line_width = width;
    return;
}

kissvg_Arrow *kissvg_CreateArrow(double pos,
                                 double arrow_size,
                                 kissvg_Color *arrow_fill_color,
                                 kissvg_Color *arrow_color,
                                 kissvg_Bool reverse_arrow,
                                 kissvg_ArrowType type,
                                 double arrow_line_width)
{
    kissvg_Arrow *arrow;

    arrow = malloc(sizeof(*arrow));

    if (arrow == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateArrow\n\n"
             "Malloc failed to create arrow and returned NULL. Aborting.\n\n");
        exit(0);
    }

    kissvg_ArrowSetPos(arrow, pos);
    kissvg_ArrowSetSize(arrow, arrow_size);
    kissvg_ArrowSetFillColor(arrow, arrow_fill_color);
    kissvg_ArrowSetLineColor(arrow, arrow_color);
    kissvg_ArrowSetReverse(arrow, reverse_arrow);
    kissvg_ArrowSetLineWidth(arrow, arrow_line_width);
    kissvg_ArrowSetType(arrow, type);

    return arrow;
}

void kissvg_DestroyArrow(kissvg_Arrow *arrow)
{
    free(arrow);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Path2D Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/


void kissvg_Path2DSetClosePath(kissvg_Path2D *path, kissvg_Bool closed)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetClosePath\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->is_closed = closed;
    return;
}

void kissvg_Path2DSetFillDraw(kissvg_Path2D *path, kissvg_Bool fill)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetFillDraw\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->fill_draw = fill;
    return;
}

void kissvg_Path2DSetError(kissvg_Path2D *path)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetError\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->error_occured = kissvg_True;
    return;
}

void kissvg_Path2DSetErrorMessage(kissvg_Path2D *path, char *message)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetErrorMessage\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    strcpy(path->error_message, message);
    return;
}

void kissvg_Path2DSetLineColor(kissvg_Path2D *path, kissvg_Color *color)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetLineColor\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->line_color = color;
    return;
}

void kissvg_Path2DSetFillColor(kissvg_Path2D *path, kissvg_Color *color)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetFillColor\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->fill_color = color;
    return;
}

void kissvg_Path2DSetLineWidth(kissvg_Path2D *path, double line_width)
{
    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Path2DSetLineWidth\n\n"
             "Input path is NULL. Aborting.\n\n");
        exit(0);
    }

    path->line_width = line_width;
    return;
}

void kissvg_Path2DCreateArrow(kissvg_Path2D *path, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    path->has_arrow = kissvg_True;
    path->N_Arrows = 1;
    path->arrows = malloc(sizeof(*path->arrows));

    path->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                         arrow_color, reverse_arrow, type,
                                         arrow_line_width);
    return;
}

void kissvg_Path2DAddArrow(kissvg_Path2D *path, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    path->N_Arrows += 1;
    path->arrows = realloc(path->arrows, sizeof(*path->arrows)*path->N_Arrows);

    path->arrows[path->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                        arrow_fill_color,
                                                        arrow_color,
                                                        reverse_arrow, type,
                                                        arrow_line_width);

    return;
}

kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Path2D *path;

    path = malloc(sizeof(*path));
    path->data = malloc(sizeof(*path->data));

    kissvg_Path2DSetLineColor(path, kissvg_Black);
    kissvg_Path2DSetFillColor(path, kissvg_Black);
    kissvg_Path2DSetLineWidth(path, kissvg_DefaultPen);

    path->data[0] = start;
    path->N_Pts = 1;

    path->is_closed = kissvg_False;
    path->has_arrow = kissvg_False;
    path->fill_draw = kissvg_False;
    path->error_occured = kissvg_False;

    path->canvas = canvas;

    return path;
}

void kissvg_AppendPath2D(kissvg_Path2D *path, kissvg_TwoVector P)
{
    long new_path_size;

    if (path == NULL)
    {
        kissvg_Path2DSetError(path);
        kissvg_Path2DSetErrorMessage(path,
                                     "Error Encountered: KissVG\n"
                                     "\tFunction: kissvg_AppendPath2D\n\n"
                                     "Input path is NULL.");
        return;
    }

    new_path_size = kissvg_Path2DSize(path) + 1;
    path->data = realloc(path->data, sizeof(*path->data) * new_path_size);

    if (path->data == NULL)
    {
        kissvg_Path2DSetError(path);
        kissvg_Path2DSetErrorMessage(path, "Error Encountered: KissVG\n"
                                           "\tFunction: kissvg_AppendPath2D\n\n"
                                           "Realloc failed and returned NULL.");
    }
    else
    {
        path->data[new_path_size-1] = P;
        path->N_Pts = new_path_size;
    }

    return;
}

void kissvg_DestroyPath2D(kissvg_Path2D *path)
{
    long n, N_Arrows;
    free(path->data);

    N_Arrows = kissvg_Path2DNumberOfArrows(path);

    if (kissvg_Path2DHasArrow(path))
    {
        for (n=0; n<N_Arrows; ++n)
            kissvg_DestroyArrow(path->arrows[n]);
    }

    free(path);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                     Begin kissvg_Axis2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

void kissvg_Axis2DCreateTicks(kissvg_Axis2D *axis,
                              kissvg_TwoVector P,
                              kissvg_TwoVector Q)
{
    kissvg_Axis2DSetTicks(axis, kissvg_True);
    axis->tick_start = P;
    axis->tick_finish = Q;
    return;
}

void kissvg_Axis2DSetLineColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->line_color = color;
    return;
}

void kissvg_Axis2DSetLineWidth(kissvg_Axis2D *axis, double line_width)
{
    axis->line_width = line_width;
    return;
}

void kissvg_Axis2DSetTickSize(kissvg_Axis2D *axis, double tick_size)
{
    axis->tick_size = tick_size;
    return;
}

void kissvg_Axis2DSetTickDist(kissvg_Axis2D *axis, double tick_dist)
{
    axis->ticks_dx = tick_dist;
    return;
}

void kissvg_Axis2DSetTickColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->tick_color = color;
    return;
}

void kissvg_Axis2DSetTickHeight(kissvg_Axis2D *axis, double tick_height)
{
    axis->ticks_height = tick_height;
}

void kissvg_Axis2DSetTickSemiHeight(kissvg_Axis2D *axis,
                                    double tick_semi_height)
{
    axis->ticks_semi_height = tick_semi_height;
    return;
}

void kissvg_Axis2DSetTickSemiSemiHeight(kissvg_Axis2D *axis,
                                        double tick_semi_semi_height)
{
    axis->ticks_semi_semi_height = tick_semi_semi_height;
    return;
}

void kissvg_Axis2DSetAxisStart(kissvg_Axis2D *axis, kissvg_TwoVector P)
{
    axis->start = P;
    return;
}

void kissvg_Axis2DSetAxisFinish(kissvg_Axis2D *axis, kissvg_TwoVector P)
{
    axis->finish = P;
    return;
}

void kissvg_Axis2DSetCanvas(kissvg_Axis2D *axis, kissvg_Canvas2D *canvas)
{
    axis->canvas = canvas;
    return;
}

void kissvg_Axis2DSetTicks(kissvg_Axis2D *axis, kissvg_Bool ticks)
{
    axis->has_ticks = ticks;
    return;
}

void kissvg_Axis2DUseUpTicks(kissvg_Axis2D *axis)
{
    axis->up_ticks = kissvg_True;
    axis->down_ticks = kissvg_False;
    return;
}

void kissvg_Axis2DUseDownTicks(kissvg_Axis2D *axis)
{
    axis->down_ticks = kissvg_True;
    axis->up_ticks = kissvg_False;
    return;
}

void kissvg_Axis2DCreateArrow(kissvg_Axis2D *axis, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    axis->has_arrow = kissvg_True;
    axis->N_Arrows = 1;
    axis->arrows = malloc(sizeof(*axis->arrows));

    axis->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                         arrow_color, reverse_arrow, type,
                                         arrow_line_width);
    return;
}

void kissvg_Axis2DAddArrow(kissvg_Axis2D *axis, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    axis->N_Arrows += 1;
    axis->arrows = realloc(axis->arrows, sizeof(*axis->arrows)*axis->N_Arrows);

    axis->arrows[axis->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                        arrow_fill_color,
                                                        arrow_color,
                                                        reverse_arrow, type,
                                                        arrow_line_width);
    return;
}

kissvg_Axis2D *kissvg_CreateAxis2D(kissvg_TwoVector start,
                                   kissvg_TwoVector finish,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Axis2D *axis;

    axis = malloc(sizeof(*axis));

    if (axis == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateAxis2D\n\n"
            "Malloc failed to create axis and return NULL. Aborting."
        );
        exit(0);
    }

    kissvg_Axis2DSetLineColor(axis, kissvg_Black);
    kissvg_Axis2DSetTickColor(axis, kissvg_Black);
    kissvg_Axis2DSetLineWidth(axis, kissvg_DefaultAxes);
    kissvg_Axis2DSetTickSize(axis, kissvg_DefaultTickSize);
    kissvg_Axis2DSetTickDist(axis, kissvg_DefaultTickDist);
    kissvg_Axis2DSetTickHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetAxisStart(axis, start);
    kissvg_Axis2DSetAxisFinish(axis, finish);
    kissvg_Axis2DSetCanvas(axis, canvas);
    kissvg_Axis2DSetTicks(axis, kissvg_False);

    kissvg_Axis2DCreateArrow(axis, 1.0, kissvg_DefaultArrowSize,
                             kissvg_Black, kissvg_Black, kissvg_False,
                             kissvg_StealthArrow,
                             kissvg_DefaultArrowLineWidth);

    axis->up_ticks = kissvg_False;
    axis->down_ticks = kissvg_False;

    return axis;
}

void kissvg_Axis2DChangeEndArrow(kissvg_Axis2D *axis, double pos,
                                 double arrow_size,
                                 kissvg_Color *arrow_fill_color,
                                 kissvg_Color *arrow_color,
                                 kissvg_Bool reverse_arrow,
                                 kissvg_ArrowType type,
                                 double arrow_line_width)
{
    kissvg_Arrow *arrow;

    if (axis == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_Axis2DChangeEndArrow\n\n"
            "Input axis is NULL. Aborting."
        );
        exit(0);
    }

    kissvg_DestroyArrow(axis->arrows[0]);

    arrow = kissvg_CreateArrow(pos, arrow_size,
                               arrow_fill_color, arrow_color, reverse_arrow,
                               type, arrow_line_width);

    axis->arrows[0] = arrow;
    return;
}

void kissvg_ResetAxis2D(kissvg_Axis2D* axis,
                        kissvg_TwoVector start,
                        kissvg_TwoVector finish)
{
    axis->start = start;
    axis->finish = finish;
    return;
}

void kissvg_DestroyAxis2D(kissvg_Axis2D *axis)
{
    long n, N_Arrows;

    N_Arrows = kissvg_Axis2DNumberOfArrows(axis);

    if (kissvg_Axis2DHasArrow(axis))
    {
        for (n=0; n<N_Arrows; ++n)
            kissvg_DestroyArrow(axis->arrows[n]);
    }

    free(axis);
    return;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                    Begin kissvg_Circle Functions                           *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

void kissvg_CircleSetCanvas(kissvg_Circle *circle, kissvg_Canvas2D *canvas)
{
    circle->canvas = canvas;
    return;
}

void kissvg_CircleSetLineWidth(kissvg_Circle *circle, double linewidth)
{
    circle->line_width = linewidth;
    return;
}

void kissvg_CircleSetLineColor(kissvg_Circle *circle, kissvg_Color *color)
{
    circle->line_color = color;
    return;
}

void kissvg_CircleSetFillColor(kissvg_Circle *circle, kissvg_Color *color)
{
    circle->fill_color = color;
    return;
}

void kissvg_CircleCreateArrow(kissvg_Circle *circle, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    circle->has_arrow = kissvg_True;
    circle->N_Arrows = 1;
    circle->arrows = malloc(sizeof(*circle->arrows));

    circle->arrows[0] = kissvg_CreateArrow(pos, arrow_size, arrow_fill_color,
                                           arrow_color, reverse_arrow, type,
                                           arrow_line_width);
    return;
}

void kissvg_CircleAddArrow(kissvg_Circle *circle, double pos, double arrow_size,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color,
                           kissvg_Bool reverse_arrow,
                           kissvg_ArrowType type,
                           double arrow_line_width)
{
    circle->N_Arrows += 1;
    circle->arrows = realloc(
        circle->arrows, sizeof(*circle->arrows)*circle->N_Arrows
    );

    circle->arrows[circle->N_Arrows-1] = kissvg_CreateArrow(pos, arrow_size,
                                                            arrow_fill_color,
                                                            arrow_color,
                                                            reverse_arrow,
                                                            type,
                                                            arrow_line_width);
    return;
}

kissvg_Circle *kissvg_CreateCircle(kissvg_TwoVector P, double r,
                                   kissvg_Canvas2D *canvas)
{
    kissvg_Circle *circle;

    circle = malloc(sizeof(*circle));

    if (circle == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateCircle\n\n"
            "Malloc failed to create circle and return NULL. Aborting."
        );
        exit(0);
    }

    kissvg_CircleSetLineColor(circle, kissvg_Black);
    kissvg_CircleSetFillColor(circle, kissvg_Black);
    kissvg_CircleSetLineWidth(circle, kissvg_DefaultPen);
    kissvg_CircleSetCanvas(circle, canvas);

    circle->center = P;
    circle->radius = r;
    circle->has_arrow = kissvg_False;
    circle->fill_draw = kissvg_False;

    return circle;
}

void kissvg_DestroyCircle(kissvg_Circle *circle)
{
    free(circle);
    return;
}

kissvg_TwoVector *kissvg_CircleCircleIntersection(kissvg_Circle *C0,
                                                  kissvg_Circle *C1)
{
    kissvg_TwoVector P0, P1;
    double r0, r1;
    double dist;
    double a, h;
    double x0, y0;
    double x1, y1;
    double x2, y2;

    double inter0_x, inter0_y;
    double inter1_x, inter1_y;

    kissvg_TwoVector *intersections;

    P0 = kissvg_CircleCenter(C0);
    P1 = kissvg_CircleCenter(C1);

    r0 = kissvg_CircleRadius(C0);
    r1 = kissvg_CircleRadius(C1);

    if (r0 <= 0.0)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CircleCircleIntersection\n\n"
            "r0 is not positive."
        );
        exit(0);
    }
    else if (r1 <= 0.0)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CircleCircleIntersection\n\n"
            "r1 is not positive."
        );
        exit(0);
    }

    dist = kissvg_EuclideanNorm2D(kissvg_TwoVectorSubtract(P0, P1));

    if ((dist > (r0+r1)) || (dist < kissvg_AbsDouble(r1-r0)) ||
        ((dist == 0.0) && (r0 != r1)))
    {
        intersections = NULL;
        return intersections;
    }
    else if ((dist == 0.0) && (r0 == r1))
    {
        intersections = malloc(sizeof(*intersections));
        intersections[0] = kissvg_NewTwoVector(kissvg_Infinity,
                                               kissvg_Infinity);
        return intersections;
    }

    x0 = kissvg_TwoVectorXComponent(P0);
    y0 = kissvg_TwoVectorYComponent(P0);

    x1 = kissvg_TwoVectorXComponent(P1);
    y1 = kissvg_TwoVectorYComponent(P1);

    a = (r0*r0 - r1*r1 + dist*dist) / (2.0*dist);
    h = sqrt(r0*r0 - a*a);

    x2 = x0 + (a/dist) * (x1-x0);
    y2 = y0 + (a/dist) * (y1-y0);

    inter0_x = x2 + h*(y1 - y0)/dist;
    inter0_y = y2 - h*(x1 - x0)/dist;

    inter1_x = x2 - h*(y1 - y0)/dist;
    inter1_y = y2 + h*(x1 - x0)/dist;

    intersections = malloc(sizeof(*intersections)*2);

    intersections[0] = kissvg_NewTwoVector(inter0_x, inter0_y);
    intersections[1] = kissvg_NewTwoVector(inter1_x, inter1_y);

    return intersections;
}


kissvg_Circle **kissvg_ApolloniusProblem(kissvg_Circle *circle1,
                                         kissvg_Circle *circle2,
                                         kissvg_Circle *circle3)
{
    kissvg_Circle **solutions;
    kissvg_Canvas2D *canvas;
    kissvg_TwoVector center1, center2, center3;
    kissvg_TwoVector center;
    double r1, r2, r3;
    double x1, x2, x3;
    double y1, y2, y3;
    double rcp;
    long n;

    /*  There are eight solutions, so set N to 8.                             */
    long N = 8;

    double a12, b12, c12, d12;
    double a13, b13, c13, d13;

    double A, B, C, D;
    double x, y, radius;

    double alpha, beta, gamma;

    double s1[8] = {-1.0, -1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0};
    double s2[8] = {-1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0,  1.0};
    double s3[8] = {-1.0,  1.0, -1.0,  1.0, -1.0,  1.0, -1.0,  1.0};

    canvas = circle1->canvas;

    /*  There are, in general, eight solutions so allocate eight slots.       */
    solutions = malloc(sizeof(*solutions) * N);

    center1 = kissvg_CircleCenter(circle1);
    center2 = kissvg_CircleCenter(circle2);
    center3 = kissvg_CircleCenter(circle3);

    r1 = kissvg_CircleRadius(circle1);
    r2 = kissvg_CircleRadius(circle2);
    r3 = kissvg_CircleRadius(circle3);

    x1 = kissvg_TwoVectorXComponent(center1);
    y1 = kissvg_TwoVectorYComponent(center1);

    x2 = kissvg_TwoVectorXComponent(center2);
    y2 = kissvg_TwoVectorYComponent(center2);

    x3 = kissvg_TwoVectorXComponent(center3);
    y3 = kissvg_TwoVectorYComponent(center3);

    for (n=0; n<N; ++n)
    {
        a12 = 2.0*(x1 - x2);
        b12 = 2.0*(y1 - y2);
        c12 = 2.0*(s2[n]*r2 - s1[n]*r1);
        d12 = (x2*x2 + y2*y2 - r2*r2) - (x1*x1 + y1*y1 - r1*r1);

        a13 = 2.0*(x1 - x3);
        b13 = 2.0*(y1 - y3);
        c13 = 2.0*(s3[n]*r3 - s1[n]*r1);
        d13 = (x3*x3 + y3*y3 - r3*r3) - (x1*x1 + y1*y1 - r1*r1);

        rcp = a12*b13 - b12*a13;

        if (rcp == 0.0)
        {
            if (((a12 == 0.0) && (b12 == 0.0)) ||
                ((a13 == 0.0) && (b13 == 0.0)))
            {
                puts("Warning: KissVG\n"
                     "\tFunction: kissvg_ApolloniusProblem\n\n"
                     "\tTwo of the Circles are Identical.");
                center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
                radius = kissvg_Infinity;
            }
            else
            {

            }
            center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
            radius = kissvg_Infinity;

            solutions[n] = kissvg_CreateCircle(center, radius, canvas);
        }
        else
        {
            rcp = 1.0/rcp;
            A = (-b13*d12 + b12*d13)*rcp;
            B = (-b13*c12 + b12*c13)*rcp;
            C = ( a13*d12 - a12*d13)*rcp;
            D = ( a13*c12 - a12*c13)*rcp;

            alpha = -1.0 + B*B + D*D;
            beta = 2.0*(A*B + C*D + r1*s1[n] - B*x1 - D*y1);
            gamma = A*A + C*C - r1*r1 + x1*x1 + y1*y1 - 2.0*(A*x1 + C*y1);

            radius = (-beta - sqrt(beta*beta - 4.0*alpha*gamma))/(2.0*alpha);

            if (radius < 0.0)
                radius = (-beta+sqrt(beta*beta - 4.0*alpha*gamma))/(2.0*alpha);

            x = A + B*radius;
            y = C + D*radius;

            center = kissvg_NewTwoVector(x, y);

            solutions[n] = kissvg_CreateCircle(center, radius, canvas);
        }
    }
    return solutions;
}

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                       Begin Drawing Functions                              *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

typedef void (*__arrow_func)(cairo_t *cr, kissvg_TwoVector P1,
                             kissvg_TwoVector Q, double arrow_size,
                             kissvg_Color *fill_color, kissvg_Color *line_color,
                             double line_width, kissvg_Canvas2D *canvas);

static void kissvg_DrawStealthArrow(cairo_t *cr,
                                    kissvg_TwoVector P1,
                                    kissvg_TwoVector Q,
                                    double arrow_size,
                                    kissvg_Color *fill_color,
                                    kissvg_Color *line_color,
                                    double line_width,
                                    kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2;
    kissvg_TwoByTwoMatrix R;
    double x, y;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A0);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A0);
    cairo_move_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A1);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A1);

    cairo_line_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(P1);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(P1);

    cairo_line_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A2);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A2);

    cairo_line_to(cr, x, y);

    cairo_close_path(cr);

    cairo_save(cr);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(fill_color),
                         kissvg_GreenColor(fill_color),
                         kissvg_BlueColor(fill_color));

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(line_color),
                         kissvg_GreenColor(line_color),
                         kissvg_BlueColor(line_color));
    cairo_stroke(cr);
    return;
}

static void kissvg_DrawTriangularArrow(cairo_t *cr,
                                      kissvg_TwoVector P1,
                                      kissvg_TwoVector Q,
                                      double arrow_size,
                                      kissvg_Color *fill_color,
                                      kissvg_Color *line_color,
                                      double line_width,
                                      kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2;
    kissvg_TwoByTwoMatrix R;
    double x, y;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A0);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A0);
    cairo_move_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A1);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A1);

    cairo_line_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A2);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A2);

    cairo_line_to(cr, x, y);

    cairo_close_path(cr);

    cairo_save(cr);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(fill_color),
                         kissvg_GreenColor(fill_color),
                         kissvg_BlueColor(fill_color));

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(line_color),
                         kissvg_GreenColor(line_color),
                         kissvg_BlueColor(line_color));
    cairo_stroke(cr);
    return;
}

static void kissvg_DrawPolygonalArrows(cairo_t *cr, kissvg_Path2D *path)
{
    kissvg_TwoVector Q;
    kissvg_TwoVector P0, P1;
    kissvg_Canvas2D *canvas;
    kissvg_Color *line_color, *fill_color;
    kissvg_Arrow *arrow;
    kissvg_Bool reverse_arrow;
    __arrow_func DrawArrows;
    double norm;
    double arrow_size, arrow_line_width;
    double path_length;
    double *path_norms;
    double pos, current_arrow_length, arr_pos_length;
    long m, n, N, N_Arrows, current_arrow_pos;
    int arrow_type;

    canvas = kissvg_Path2DCanvas(path);
    N = kissvg_Path2DSize(path);
    N_Arrows = kissvg_Path2DNumberOfArrows(path);

    path_norms = malloc(sizeof(*path_norms) * (N-1));

    P0 = kissvg_Path2DData(path)[0];
    P1 = kissvg_Path2DData(path)[1];
    Q = kissvg_TwoVectorSubtract(P1, P0);

    norm = kissvg_EuclideanNorm2D(Q);
    path_length = norm;
    path_norms[0] = norm;

    for (n=1; n<N-1; ++n)
    {
        P0 = kissvg_Path2DData(path)[n];
        P1 = kissvg_Path2DData(path)[n+1];
        Q = kissvg_TwoVectorSubtract(P1, P0);

        norm = kissvg_EuclideanNorm2D(Q);

        path_length += norm;
        path_norms[n] = path_length;
    }

    for (n=0; n<N_Arrows; ++n)
    {
        arrow = kissvg_Path2DnthArrow(path, n);
        arrow_type = kissvg_ArrowType(arrow);

        if (arrow_type == kissvg_StealthArrow)
            DrawArrows = &kissvg_DrawStealthArrow;
        else if (arrow_type == kissvg_TriangularArrow)
            DrawArrows = &kissvg_DrawTriangularArrow;
        else
        {
            puts("Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawPolygonalArrows\n\n"
                "Illegal arrow type selected.\n\n");
            exit(0);
        }

        pos = kissvg_ArrowPosition(arrow);
        line_color = kissvg_ArrowLineColor(arrow);
        fill_color = kissvg_ArrowFillColor(arrow);
        arrow_size = kissvg_ArrowSize(arrow);
        reverse_arrow = kissvg_ArrowIsReversed(arrow);
        arrow_line_width = kissvg_ArrowLineWidth(arrow);

        if (pos < 0.0)
            pos = 0.0;
        else if (pos > 1.0)
            pos = 1.0;

        if (pos == 0.0)
        {
            norm = path_norms[0];

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "The first two points in the input path are the same.\n"
                    "Cannot compute the tangent vector at start of path.\n"
                );
                exit(0);
            }

            P0 = kissvg_Path2DData(path)[0];
            P1 = kissvg_Path2DData(path)[1];

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            Q = kissvg_TwoVectorScale(1.0/norm, Q);

            DrawArrows(cr, P0, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
        else if (pos == 1.0)
        {
            norm = path_norms[N-2];

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "The last two points in the input path are the same.\n"
                    "Cannot compute the tangent vector at end of path.\n"
                );
                exit(0);
            }

            P0 = kissvg_Path2DData(path)[N-2];
            P1 = kissvg_Path2DData(path)[N-1];

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            Q = kissvg_TwoVectorScale(1.0/norm, Q);

            DrawArrows(cr, P1, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
        else
        {
            current_arrow_pos = 0;
            current_arrow_length = path_norms[0];
            arr_pos_length = pos * path_length;

            for (m=0; m<N-1; ++m)
            {
                if (arr_pos_length < current_arrow_length)
                    break;
                current_arrow_pos += 1;
                current_arrow_length = path_norms[current_arrow_pos];
            }

            P0 = kissvg_Path2DData(path)[current_arrow_pos];
            P1 = kissvg_Path2DData(path)[current_arrow_pos+1];
            Q = kissvg_TwoVectorSubtract(P1, P0);

            norm = kissvg_EuclideanNorm2D(Q);

            if (norm == 0.0)
            {
                puts(
                    "Error Encountered: KissVG\n"
                    "\tkissvg_DrawPolygonalArrows\n\n"
                    "Two of the points used for arrows are the same.\n"
                    "Cannot compute the tangent vector.\n"
                );
                exit(0);
            }

            Q = kissvg_TwoVectorScale(1.0/norm, Q);
            norm = arr_pos_length-path_norms[current_arrow_pos-1];
            Q = kissvg_TwoVectorScale(norm, Q);
            P1 = kissvg_TwoVectorAdd(P0, Q);

            if (reverse_arrow)
                Q = kissvg_TwoVectorSubtract(P0, P1);
            else
                Q = kissvg_TwoVectorSubtract(P1, P0);

            norm = kissvg_EuclideanNorm2D(Q);
            Q = kissvg_TwoVectorScale(1.0/norm, Q);
            DrawArrows(cr, P1, Q, arrow_size, fill_color,
                       line_color, arrow_line_width, canvas);
        }
    }

    return;
}

void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;
    kissvg_Color *color;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_Path2DCanvas(path);
    path_size = kissvg_Path2DSize(path);

    if (path_size<2)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_DrawPolygon2D\n\n"
            "Input path has less than two points.\n"
        );
        exit(0);
    }

    Pn = kissvg_Path2DData(path)[0];

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(Pn);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(Pn);

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];

        x = kissvg_Canvas2DXShift(canvas) +
            kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(Pn);

        y = kissvg_Canvas2DYShift(canvas) -
            kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(Pn);

        cairo_line_to(cr, x, y);
    }

    if (kissvg_Path2DIsClosed(path))
        cairo_close_path(cr);

    cairo_set_line_width(cr, kissvg_Path2DLineWidth(path));

    color = kissvg_Path2DLineColor(path);
    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));
    cairo_stroke(cr);

    if (kissvg_Path2DHasArrow(path))
        kissvg_DrawPolygonalArrows(cr, path);
}

void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;
    kissvg_Color *color;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_Path2DCanvas(path);
    path_size = kissvg_Path2DSize(path);

    if (path_size<2)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_DrawPolygon2D\n\n"
            "Input path has less than two points.\n"
        );
        exit(0);
    }

    Pn = kissvg_Path2DData(path)[0];
    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(Pn);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(Pn);

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];
        x = kissvg_Canvas2DXShift(canvas) +
            kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(Pn);

        y = kissvg_Canvas2DYShift(canvas) -
            kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(Pn);

        cairo_line_to(cr, x, y);
    }

    cairo_close_path(cr);
    cairo_save(cr);
    color = kissvg_Path2DFillColor(path);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));
    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_set_line_width(cr, kissvg_Path2DLineWidth(path));
    color = kissvg_Path2DLineColor(path);
    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));
    cairo_stroke(cr);
}

void kissvg_DrawCircle2D(cairo_t *cr, kissvg_Circle *circle)
{
    kissvg_TwoVector P;
    kissvg_TwoVector center;
    kissvg_Path2D *path;
    double radius;
    double theta;
    double x, y;
    double theta_factor;
    long n, N;

    N = 300;

    theta_factor = 2.0*M_PI/N;

    center = kissvg_CircleCenter(circle);
    radius = kissvg_CircleRadius(circle);

    P = kissvg_NewTwoVector(radius, 0.0);
    P = kissvg_TwoVectorAdd(center, P);

    path = kissvg_CreatePath2D(P, circle->canvas);

    kissvg_Path2DSetLineColor(path, circle->line_color);
    kissvg_Path2DSetLineWidth(path, circle->line_width);
    kissvg_Path2DSetClosePath(path, kissvg_True);

    if (circle->has_arrow)
    {
        path->has_arrow = kissvg_True;
        path->arrows = circle->arrows;
        path->N_Arrows = circle->N_Arrows;
    }

    for (n=1; n<N; ++n)
    {
        theta = n*theta_factor;
        x = radius*cos(theta);
        y = radius*sin(theta);

        P = kissvg_NewTwoVector(x, y);
        P = kissvg_TwoVectorAdd(P, center);
        kissvg_AppendPath2D(path, P);
    }

    kissvg_DrawPolygon2D(cr, path);
    kissvg_DestroyPath2D(path);

    return;
}

void kissvg_FillDrawCircle2D(cairo_t *cr, kissvg_Circle *circle)
{
    kissvg_TwoVector P;
    kissvg_TwoVector center;
    kissvg_Path2D *path;
    double radius;
    double theta;
    double x, y;
    double theta_factor;
    long n, N;

    N = 200;

    theta_factor = 2.0*M_PI/N;

    center = kissvg_CircleCenter(circle);
    radius = kissvg_CircleRadius(circle);

    P = kissvg_NewTwoVector(radius, 0.0);
    P = kissvg_TwoVectorAdd(center, P);

    path = kissvg_CreatePath2D(P, circle->canvas);

    kissvg_Path2DSetLineColor(path, circle->line_color);
    kissvg_Path2DSetLineWidth(path, circle->line_width);
    kissvg_Path2DSetFillColor(path, circle->fill_color);

    if (circle->has_arrow)
    {
        path->has_arrow = kissvg_True;
        path->arrows = circle->arrows;
        path->N_Arrows = circle->N_Arrows;
    }

    for (n=1; n<N; ++n)
    {
        theta = n*theta_factor;
        x = radius*cos(theta);
        y = radius*sin(theta);

        P = kissvg_NewTwoVector(x, y);
        P = kissvg_TwoVectorAdd(P, center);
        kissvg_AppendPath2D(path, P);
    }

    kissvg_FillDrawPolygon2D(cr, path);
    kissvg_DestroyPath2D(path);

    return;
}

void kissvg_DrawAxis2D(cairo_t *cr, kissvg_Axis2D *axis)
{
    kissvg_Path2D *path;
    kissvg_Path2D *tick_path;
    kissvg_TwoVector dxtick, dytick, tick;
    kissvg_TwoVector tick_top, tick_bottom;
    kissvg_TwoVector tick_perp, tick_perp_semi, tick_perp_semi_semi;
    long n, N_Ticks;
    double norm;
    double tick_factor;

    path = kissvg_CreatePath2D(axis->start, axis->canvas);

    kissvg_AppendPath2D(path, axis->finish);
    kissvg_Path2DSetLineColor(path, axis->line_color);
    kissvg_Path2DSetLineWidth(path, axis->line_width);

    if (axis->has_arrow)
    {
        path->has_arrow = kissvg_True;
        path->arrows = axis->arrows;
        path->N_Arrows = axis->N_Arrows;
    }

    if (axis->has_ticks)
    {
        if (axis->ticks_dx <= 0.0)
        {
            puts(
                "Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawAxis2D\n\n"
                "Axis ticks_dx variables is not positive.\n"
            );
            exit(0);
        }

        dxtick = kissvg_TwoVectorSubtract(axis->tick_finish, axis->tick_start);
        norm = kissvg_EuclideanNorm2D(dxtick);

        if (norm == 0)
        {
            puts(
                "Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawAxis2D\n\n"
                "Distance between tick_start and tick_finish is zero.\n"
            );
            exit(0);
        }

        tick_factor = 0.5 / norm;

        tick = kissvg_NewTwoVector(-kissvg_TwoVectorYComponent(dxtick),
                                   kissvg_TwoVectorXComponent(dxtick));

        dxtick = kissvg_TwoVectorScale(axis->ticks_dx/norm, dxtick);
        tick_perp = kissvg_TwoVectorScale(tick_factor*axis->ticks_height, tick);
        tick_perp_semi = kissvg_TwoVectorScale(
            tick_factor*axis->ticks_semi_height, tick
        );

        tick_perp_semi_semi = kissvg_TwoVectorScale(
            tick_factor*axis->ticks_semi_semi_height, tick
        );

        N_Ticks = (long)(norm/axis->ticks_dx);

        tick = axis->tick_start;

        for (n=0; n<N_Ticks; ++n)
        {
            if ((n % 4) == 0)
                dytick = tick_perp;
            else if ((n % 2) == 0)
                dytick = tick_perp_semi;
            else
                dytick = tick_perp_semi_semi;

            if (axis->down_ticks)
                tick_top = tick;
            else
                tick_top = kissvg_TwoVectorAdd(tick, dytick);

            if (axis->up_ticks)
                tick_bottom = tick;
            else
                tick_bottom = kissvg_TwoVectorSubtract(tick, dytick);

            tick_path = kissvg_CreatePath2D(tick_bottom, axis->canvas);
            kissvg_AppendPath2D(tick_path, tick_top);

            kissvg_Path2DSetLineWidth(tick_path, axis->tick_size);
            kissvg_Path2DSetLineColor(tick_path, axis->tick_color);
            kissvg_DrawPolygon2D(cr, tick_path);
            kissvg_DestroyPath2D(tick_path);
            tick = kissvg_TwoVectorAdd(tick, dxtick);
        }
    }

    kissvg_DrawPolygon2D(cr, path);

    path->has_arrow = kissvg_False;
    kissvg_DestroyPath2D(path);
    return;
}
