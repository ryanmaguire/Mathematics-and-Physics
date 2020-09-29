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
#include <kissvg/include/kissvg_colors.h>
#include <cairo.h>

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

kissvg_Color *kissvg_CreateColor(double red, double green, double blue,
                                 kissvg_Bool transparent, double alpha)
{
    kissvg_Color *color;

    color = malloc(sizeof(*color));
    color->dat[0] = red;
    color->dat[1] = green;
    color->dat[2] = blue;
    color->has_transparency = transparent;
    color->alpha = alpha;
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
    kissvg_ArrowSetReverse(arrow, reverse_arrow);
    kissvg_ArrowSetType(arrow, type);

    kissvg_SetFillColor(arrow, arrow_fill_color);
    kissvg_SetLineColor(arrow, arrow_color);
    kissvg_SetLineWidth(arrow, arrow_line_width);

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

void kissvg_Path2DCreateArrow(kissvg_Path2D *path, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    kissvg_SetHasArrows(path, kissvg_True);
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

    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreatePath2D\n\n"
             "Malloc failed and returned NULL for path.");
        exit(0);
    }

    path->data = malloc(sizeof(*path->data));

    if (path->data == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreatePath2D\n\n"
             "Malloc failed and returned NULL for path->data.");
        exit(0);
    }

    path->data[0] = start;
    path->N_Pts = 1;

    kissvg_SetLineColor(path, kissvg_Black);
    kissvg_SetFillColor(path, kissvg_Black);
    kissvg_SetLineWidth(path, kissvg_DefaultPen);
    kissvg_SetClosedPath(path, kissvg_False);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_SetFillDraw(path, kissvg_False);
    kissvg_SetError(path, kissvg_False);
    kissvg_SetCanvas(path, canvas);

    return path;
}

void kissvg_AppendPath2D(kissvg_Path2D *path, kissvg_TwoVector P)
{
    long new_path_size;

    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_AppendPath2D\n\n"
             "Input path is NULL.");
        exit(0);
    }

    new_path_size = kissvg_Path2DNumberOfPoints(path) + 1;
    path->data = realloc(path->data, sizeof(*path->data) * new_path_size);

    if (path->data == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_AppendPath2D\n\n"
             "Realloc failed and returned NULL.");
        exit(0);
    }

    path->data[new_path_size-1] = P;
    path->N_Pts = new_path_size;

    return;
}

void kissvg_DestroyPath2D(kissvg_Path2D *path)
{
    long n, N_Arrows;
    kissvg_Arrow *current_arrow;
    free(path->data);

    N_Arrows = kissvg_NumberOfArrows(path);

    if (kissvg_HasArrows(path))
    {
        for (n=0; n<N_Arrows; ++n)
        {
            current_arrow = kissvg_nthArrow(path, n);
            kissvg_DestroyArrow(current_arrow);
        }
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
    kissvg_Axis2DUseTicks(axis, kissvg_True);
    axis->tick_start = P;
    axis->tick_finish = Q;
    return;
}

void kissvg_Axis2DSetTickWidth(kissvg_Axis2D *axis, double tick_width)
{
    axis->tick_width = tick_width;
    return;
}

void kissvg_Axis2DSetTickDistance(kissvg_Axis2D *axis, double tick_dist)
{
    axis->tick_dx = tick_dist;
    return;
}

void kissvg_Axis2DSetTickColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->tick_color = color;
    return;
}

void kissvg_Axis2DSetTickHeight(kissvg_Axis2D *axis, double tick_height)
{
    axis->tick_height = tick_height;
}

void kissvg_Axis2DSetTickSemiHeight(kissvg_Axis2D *axis,
                                    double tick_semi_height)
{
    axis->tick_semi_height = tick_semi_height;
    return;
}

void kissvg_Axis2DSetTickSemiSemiHeight(kissvg_Axis2D *axis,
                                        double tick_semi_semi_height)
{
    axis->tick_semi_semi_height = tick_semi_semi_height;
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

void kissvg_Axis2DUseTicks(kissvg_Axis2D *axis, kissvg_Bool ticks)
{
    axis->has_ticks = ticks;
    return;
}

void kissvg_Axis2DUseUpTicks(kissvg_Axis2D *axis)
{
    axis->has_ticks = kissvg_True;
    axis->up_ticks = kissvg_True;
    axis->down_ticks = kissvg_False;
    return;
}

void kissvg_Axis2DUseDownTicks(kissvg_Axis2D *axis)
{
    axis->has_ticks = kissvg_True;
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
    kissvg_SetHasArrows(axis, kissvg_True);
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

    kissvg_SetLineColor(axis, kissvg_Black);
    kissvg_SetLineWidth(axis, kissvg_DefaultAxes);
    kissvg_SetCanvas(axis, canvas);

    kissvg_Axis2DSetTickColor(axis, kissvg_Black);
    kissvg_Axis2DSetTickWidth(axis, kissvg_DefaultTickWidth);
    kissvg_Axis2DSetTickDistance(axis, kissvg_DefaultTickDist);
    kissvg_Axis2DSetTickHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetAxisStart(axis, start);
    kissvg_Axis2DSetAxisFinish(axis, finish);
    kissvg_Axis2DUseTicks(axis, kissvg_False);

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

    arrow = kissvg_nthArrow(axis, 0);
    kissvg_DestroyArrow(arrow);

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
    kissvg_Arrow *current_arrow;

    N_Arrows = kissvg_NumberOfArrows(axis);

    if (kissvg_HasArrows(axis))
    {
        for (n=0; n<N_Arrows; ++n)
        {
            current_arrow = kissvg_nthArrow(axis, n);
            kissvg_DestroyArrow(current_arrow);
        }
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

void kissvg_CircleCreateArrow(kissvg_Circle *circle, double pos,
                              double arrow_size,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color,
                              kissvg_Bool reverse_arrow,
                              kissvg_ArrowType type,
                              double arrow_line_width)
{
    kissvg_SetHasArrows(circle, kissvg_True);
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

    kissvg_SetLineColor(circle, kissvg_Black);
    kissvg_SetFillColor(circle, kissvg_Black);
    kissvg_SetLineWidth(circle, kissvg_DefaultPen);
    kissvg_SetCanvas(circle, canvas);
    kissvg_CircleSetIsLine(circle, kissvg_False);

    circle->center = P;
    circle->radius = r;

    kissvg_SetHasArrows(circle, kissvg_False);
    kissvg_SetFillDraw(circle, kissvg_False);

    return circle;
}

void kissvg_ResetCircle(kissvg_Circle *C, kissvg_TwoVector P, double r)
{
    if (C == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateCircle\n\n"
            "Malloc failed to create circle and return NULL. Aborting."
        );
        exit(0);
    }

    C->center = P;
    C->radius = r;
    return;
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
 *                     Begin kissvg_Line2D Functions                          *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_Line2D *kissvg_CreateLineFromTwoPoints(kissvg_TwoVector P,
                                              kissvg_TwoVector Q,
                                              kissvg_Canvas2D *canvas)
{
    kissvg_Line2D *line;
    kissvg_TwoVector V;
    line = malloc(sizeof(*line));

    V = kissvg_TwoVectorSubtract(P, Q);

    line->P = P;
    line->V = V;

    kissvg_SetLineWidth(line, kissvg_DefaultPen);
    kissvg_SetLineColor(line, kissvg_Black);
    kissvg_SetCanvas(line, canvas);

    return line;
}

kissvg_Line2D *kissvg_CreateLineFromPointAndTangent(kissvg_TwoVector P,
                                                    kissvg_TwoVector V,
                                                    kissvg_Canvas2D *canvas)
{
    kissvg_Line2D *line;
    line = malloc(sizeof(*line));

    line->P = P;
    line->V = V;

    kissvg_SetLineWidth(line, kissvg_DefaultPen);
    kissvg_SetLineColor(line, kissvg_Black);
    kissvg_SetCanvas(line, canvas);

    return line;
}

void kissvg_DestroyLine2D(kissvg_Line2D *L)
{
    free(L);
    return;
}

kissvg_TwoVector kissvg_LineLineIntersection(kissvg_Line2D *L0,
                                             kissvg_Line2D *L1)
{
    kissvg_TwoVector P0, P1;
    kissvg_TwoVector V0, V1;
    kissvg_TwoVector inter;
    kissvg_TwoVector P1P0;
    kissvg_TwoVector times;
    kissvg_TwoByTwoMatrix A, inverseA;
    double v0x, v0y;
    double v1x, v1y;
    double t0;
    double det;

    P0 = kissvg_Line2DPoint(L0);
    V0 = kissvg_Line2DTangent(L0);

    P1 = kissvg_Line2DPoint(L1);
    V1 = kissvg_Line2DTangent(L1);

    v0x = kissvg_TwoVectorXComponent(V0);
    v0y = kissvg_TwoVectorYComponent(V0);

    v1x = kissvg_TwoVectorXComponent(V1);
    v1y = kissvg_TwoVectorYComponent(V1);

    det = v1x*v0y -v0x*v1y;

    if (det == 0.0)
    {
        inter = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);

        return inter;
    }
    else
    {
        P1P0 = kissvg_TwoVectorSubtract(P1, P0);
        A = kissvg_NewTwoByTwoMatrix(v0x, -v1x, v0y, -v1y);
        inverseA = kissvg_InverseTwoByTwoMatrix(A);
        times = kissvg_TwoVectorMatrixTransform(inverseA, P1P0);
        t0 = kissvg_TwoVectorXComponent(times);

        inter = kissvg_TwoVectorAdd(P0, kissvg_TwoVectorScale(t0, V0));
        return inter;
    }
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

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }
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

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }

    cairo_stroke(cr);
    return;
}

static void kissvg_DrawLatexArrow(cairo_t *cr,
                                  kissvg_TwoVector P1,
                                  kissvg_TwoVector Q,
                                  double arrow_size,
                                  kissvg_Color *fill_color,
                                  kissvg_Color *line_color,
                                  double line_width,
                                  kissvg_Canvas2D *canvas)
{
    kissvg_TwoVector A0, A1, A2, O, extra, B0, B1;
    kissvg_TwoByTwoMatrix R;
    double x, y, ox, oy, bx0, by0, bx1, by1;

    A0 = kissvg_TwoVectorScale(arrow_size, Q);

    extra = kissvg_TwoVectorScale(0.05, Q);

    R  = kissvg_RotationMatrix2D(5.0*M_PI/6.0);
    A1 = kissvg_TwoVectorMatrixTransform(R, A0);

    R  = kissvg_RotationMatrix2D(7.0*M_PI/6.0);
    A2 = kissvg_TwoVectorMatrixTransform(R, A0);

    B0 = kissvg_EuclideanMidPoint2D(A0, A1);
    B1 = kissvg_EuclideanMidPoint2D(A0, A2);

    B0 = kissvg_TwoVectorScale(0.5, B0);
    B1 = kissvg_TwoVectorScale(0.5, B1);

    A0 = kissvg_TwoVectorScale(0.8, A0);

    A0 = kissvg_TwoVectorAdd(A0, P1);
    A1 = kissvg_TwoVectorAdd(A1, P1);
    A2 = kissvg_TwoVectorAdd(A2, P1);
    B0 = kissvg_TwoVectorAdd(B0, P1);
    B1 = kissvg_TwoVectorAdd(B1, P1);

    A0 = kissvg_TwoVectorAdd(A0, extra);
    A1 = kissvg_TwoVectorAdd(A1, extra);
    A2 = kissvg_TwoVectorAdd(A2, extra);
    B0 = kissvg_TwoVectorAdd(B0, extra);
    B1 = kissvg_TwoVectorAdd(B1, extra);

    O = kissvg_EuclideanMidPoint2D(P1, A0);

    ox = kissvg_Canvas2DXShift(canvas) +
         kissvg_TwoVectorXComponent(O) * kissvg_Canvas2DXScale(canvas);
    oy = kissvg_Canvas2DYShift(canvas) -
         kissvg_TwoVectorYComponent(O) * kissvg_Canvas2DYScale(canvas);

    bx0 = kissvg_Canvas2DXShift(canvas) +
          kissvg_TwoVectorXComponent(B0) * kissvg_Canvas2DXScale(canvas);
    by0 = kissvg_Canvas2DYShift(canvas) -
          kissvg_TwoVectorYComponent(B0) * kissvg_Canvas2DYScale(canvas);

    bx1 = kissvg_Canvas2DXShift(canvas) +
          kissvg_TwoVectorXComponent(B1) * kissvg_Canvas2DXScale(canvas);
    by1 = kissvg_Canvas2DYShift(canvas) -
          kissvg_TwoVectorYComponent(B1) * kissvg_Canvas2DYScale(canvas);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A0);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A0);
    cairo_move_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A1);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A1);
    cairo_curve_to(cr, ox, oy, bx0, by0, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A2);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A2);
    cairo_line_to(cr, x, y);

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(A0);

    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(A0);
    cairo_curve_to(cr, bx1, by1, ox, oy, x, y);

    cairo_close_path(cr);
    cairo_save(cr);

    if (kissvg_ColorIsTransparent(fill_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(fill_color),
                              kissvg_ColorGreen(fill_color),
                              kissvg_ColorBlue(fill_color),
                              kissvg_ColorAlpha(fill_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(fill_color),
                             kissvg_ColorGreen(fill_color),
                             kissvg_ColorBlue(fill_color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, line_width);

    if (kissvg_ColorIsTransparent(line_color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(line_color),
                              kissvg_ColorGreen(line_color),
                              kissvg_ColorBlue(line_color),
                              kissvg_ColorAlpha(line_color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(line_color),
                             kissvg_ColorGreen(line_color),
                             kissvg_ColorBlue(line_color));
    }

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

    canvas = kissvg_GetCanvas(path);
    N = kissvg_Path2DNumberOfPoints(path);
    N_Arrows = kissvg_NumberOfArrows(path);

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
        arrow = kissvg_nthArrow(path, n);
        arrow_type = kissvg_ArrowType(arrow);

        if (arrow_type == kissvg_StealthArrow)
            DrawArrows = &kissvg_DrawStealthArrow;
        else if (arrow_type == kissvg_TriangularArrow)
            DrawArrows = &kissvg_DrawTriangularArrow;
        else if (arrow_type == kissvg_LatexArrow)
            DrawArrows = &kissvg_DrawLatexArrow;
        else
        {
            puts("Error Encountered: KissVG\n"
                "\tFunction: kissvg_DrawPolygonalArrows\n\n"
                "Illegal arrow type selected.\n\n");
            exit(0);
        }

        pos = kissvg_ArrowPosition(arrow);
        line_color = kissvg_LineColor(arrow);
        fill_color = kissvg_FillColor(arrow);
        arrow_size = kissvg_ArrowSize(arrow);
        reverse_arrow = kissvg_ArrowIsReversed(arrow);
        arrow_line_width = kissvg_LineWidth(arrow);

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

    canvas = kissvg_GetCanvas(path);
    path_size = kissvg_Path2DNumberOfPoints(path);

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

    cairo_set_line_width(cr, kissvg_LineWidth(path));

    color = kissvg_LineColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

    cairo_stroke(cr);

    if (kissvg_HasArrows(path))
        kissvg_DrawPolygonalArrows(cr, path);
}

void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;
    kissvg_Color *color;
    kissvg_Canvas2D *canvas;

    canvas = kissvg_GetCanvas(path);
    path_size = kissvg_Path2DNumberOfPoints(path);

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
    color = kissvg_FillColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_set_line_width(cr, kissvg_LineWidth(path));

    color = kissvg_LineColor(path);

    if (kissvg_ColorIsTransparent(color))
    {
        cairo_set_source_rgba(cr,
                              kissvg_ColorRed(color),
                              kissvg_ColorGreen(color),
                              kissvg_ColorBlue(color),
                              kissvg_ColorAlpha(color));
    }
    else
    {
        cairo_set_source_rgb(cr,
                             kissvg_ColorRed(color),
                             kissvg_ColorGreen(color),
                             kissvg_ColorBlue(color));
    }

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

    kissvg_SetLineColor(path, kissvg_LineColor(circle));
    kissvg_SetLineWidth(path, kissvg_LineWidth(circle));
    kissvg_SetClosedPath(path, kissvg_True);

    if (kissvg_HasArrows(circle))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(circle);
        path->arrows = circle->arrows;
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

    kissvg_SetLineColor(path, kissvg_LineColor(circle));
    kissvg_SetLineWidth(path, kissvg_LineWidth(circle));
    kissvg_SetFillColor(path, kissvg_FillColor(circle));

    if (kissvg_HasArrows(circle))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(circle);
        path->arrows = circle->arrows;
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
    double height, semi_height, semi_semi_height;
    double dist;

    path = kissvg_CreatePath2D(axis->start, axis->canvas);

    kissvg_AppendPath2D(path, axis->finish);
    kissvg_SetLineColor(path, kissvg_LineColor(axis));
    kissvg_SetLineWidth(path, kissvg_LineWidth(axis));

    if (kissvg_HasArrows(axis))
    {
        kissvg_SetHasArrows(path, kissvg_True);
        path->N_Arrows = kissvg_NumberOfArrows(axis);
        path->arrows = axis->arrows;
    }

    if (kissvg_Axis2DHasTicks(axis))
    {
        dist = kissvg_Axis2DTickDistance(axis);
        if (dist <= 0.0)
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
        height = tick_factor * kissvg_Axis2DTickHeight(axis);
        semi_height = tick_factor * kissvg_Axis2DTickSemiHeight(axis);
        semi_semi_height = tick_factor * kissvg_Axis2DTickSemiSemiHeight(axis);

        tick = kissvg_EuclideanOrthogonalVector2D(dxtick);

        dxtick = kissvg_TwoVectorScale(dist/norm, dxtick);
        tick_perp = kissvg_TwoVectorScale(height, tick);
        tick_perp_semi = kissvg_TwoVectorScale(semi_height, tick);
        tick_perp_semi_semi = kissvg_TwoVectorScale(semi_semi_height, tick);

        N_Ticks = (long)(norm/dist);

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

            kissvg_SetLineWidth(tick_path, kissvg_Axis2DTickWidth(axis));
            kissvg_SetLineColor(tick_path, kissvg_Axis2DTickColor(axis));
            kissvg_DrawPolygon2D(cr, tick_path);
            kissvg_DestroyPath2D(tick_path);
            tick = kissvg_TwoVectorAdd(tick, dxtick);
        }
    }

    kissvg_DrawPolygon2D(cr, path);
    kissvg_SetHasArrows(path, kissvg_False);
    kissvg_DestroyPath2D(path);
    return;
}
