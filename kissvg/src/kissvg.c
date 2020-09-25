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

kissvg_TwoMatrix kissvg_NewTwoMatrix(double a, double b,
                                     double c, double d)
{
    kissvg_TwoMatrix A;

    A.dat[0][0] = a;
    A.dat[0][1] = b;
    A.dat[1][0] = c;
    A.dat[1][1] = d;

    return A;
}

kissvg_TwoVector kissvg_TwoVectorMatrixTransform(kissvg_TwoMatrix A,
                                                 kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double x_new, y_new;
    double x0, y0;
    double a, b, c, d;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    a = kissvg_TwoMatrixComponent(A, 0, 0);
    b = kissvg_TwoMatrixComponent(A, 0, 1);
    c = kissvg_TwoMatrixComponent(A, 1, 0);
    d = kissvg_TwoMatrixComponent(A, 1, 1);

    x_new = a*x0 + b*y0;
    y_new = c*x0 + d*y0;

    out = kissvg_NewTwoVector(x_new, y_new);
    return out;
}

kissvg_TwoMatrix kissvg_RotationMatrix2D(double theta)
{
    double cos_theta, sin_theta;
    kissvg_TwoMatrix R;

    cos_theta = cos(theta);
    sin_theta = sin(theta);

    R = kissvg_NewTwoMatrix(cos_theta, -sin_theta, sin_theta, cos_theta);
    return R;
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

kissvg_TwoVector kissvg_FindCenter2D(kissvg_TwoVector A,
                                     kissvg_TwoVector B,
                                     kissvg_TwoVector C)
{
    kissvg_TwoVector U;
    kissvg_TwoVector V;
    kissvg_TwoVector center;
    double ax, ay;
    double bx, by;
    double cx, cy;
    double vx, vy;
    double ux, uy;
    double det_factor;
    double centerx, centery;
    double a, b, c, d, t0, t1;
    double AB_Factor, CB_Factor;

    if (kissvg_IsCollinear(A, B, C))
    {
        centerx = kissvg_Infinity;
        centery = kissvg_Infinity;
    }
    else
    {
        ax = kissvg_TwoVectorXComponent(A);
        ay = kissvg_TwoVectorYComponent(A);

        bx = kissvg_TwoVectorXComponent(B);
        by = kissvg_TwoVectorYComponent(B);

        cx = kissvg_TwoVectorXComponent(C);
        cy = kissvg_TwoVectorYComponent(C);

        U = kissvg_MidPoint2D(A, B);
        V = kissvg_MidPoint2D(B, C);

        AB_Factor = by-ay+bx-ax;
        CB_Factor = cy-by+cx-bx;

        if ((AB_Factor == 0.0) || (CB_Factor == 0.0))
        {
            centerx = kissvg_Infinity;
            centery = kissvg_Infinity;
        }
        else
        {
            AB_Factor = 1.0/AB_Factor;
            CB_Factor = 1.0/CB_Factor;

            a =  (by-ay)*AB_Factor;
            b = -(bx-ax)*AB_Factor;
            c =  (cy-by)*CB_Factor;
            d = -(cx-bx)*CB_Factor;

            det_factor = a*d - b*c;

            centerx = kissvg_Infinity;
            centery = kissvg_Infinity;
            det_factor = 1.0/det_factor;
            vx = kissvg_TwoVectorXComponent(V);
            vy = kissvg_TwoVectorYComponent(V);

            ux = kissvg_TwoVectorXComponent(U);
            uy = kissvg_TwoVectorYComponent(U);

            t0 = (d*(vx-ux)-c*(vy-uy))*det_factor;
            t1 = (b*(vx-ux)-a*(vy-uy))*det_factor;

            centerx = ux + t0*a;
            centery = uy + t1*b;
        }
    }
    center = kissvg_NewTwoVector(centerx, centery);
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

void kissvg_Path2DSetErrorMessage(kissvg_Path2D *path, char *message)
{
    strcpy(path->error_message, message);
    return;
}

void kissvg_Path2DSetLineColor(kissvg_Path2D *path, kissvg_Color *color)
{
    path->line_color = color;
    return;
}

void kissvg_Path2DSetFillColor(kissvg_Path2D *path, kissvg_Color *color)
{
    path->fill_color = color;
    return;
}

void kissvg_Path2DSetLineWidth(kissvg_Path2D *path, double line_width)
{
    path->line_width = line_width;
    return;
}

void kissvg_Path2DSetArrowSize(kissvg_Path2D *path, double arrow_size)
{
    path->arrow_size = arrow_size;
    return;
}

void kissvg_Path2DCreateArrow(kissvg_Path2D *path, double pos,
                              kissvg_Color *arrow_fill_color,
                              kissvg_Color *arrow_color)
{
    path->has_arrow = kissvg_True;
    path->N_Arrows = 1;

    path->arrow_pos = malloc(sizeof(*path->arrow_pos));
    path->arrow_color = malloc(sizeof(*path->arrow_color));
    path->arrow_fill_color = malloc(sizeof(*path->arrow_fill_color));

    path->arrow_color[0] = arrow_color;
    path->arrow_fill_color[0] = arrow_fill_color;
    path->arrow_pos[0] = pos;
    return;
}

void kissvg_Path2DAddArrow(kissvg_Path2D *path, double pos,
                           kissvg_Color *arrow_fill_color,
                           kissvg_Color *arrow_color)
{
    path->N_Arrows += 1;

    path->arrow_pos = realloc(sizeof(*path->arrow_pos) * path->N_Arrows);
    path->arrow_color = realloc(sizeof(*path->arrow_color) * path->N_Arrows);
    path->arrow_fill_color = realloc(sizeof(*path->arrow_fill_color) *
                                     path->N_Arrows);

    path->arrow_pos[path->N_Arrows-1] = pos;
    path->arrow_color[path->N_Arrows-1] = arrow_color;
    path->arrow_fill_color[path->N_Arrows-1] = arrow_fill_color;
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
    kissvg_Path2DSetArrowColor(path, kissvg_Black);
    kissvg_Path2DSetArrowFillColor(path, kissvg_Black);
    kissvg_Path2DSetLineWidth(path, kissvg_DefaultPen);

    path->data[0] = start;
    path->N_Pts = 1;

    path->is_closed = kissvg_False;
    path->has_arrow = kissvg_False;
    path->fill_draw = kissvg_False;
    path->kissvg_error_occured = kissvg_False;

    path->canvas = canvas;

    /*  Default arrowsize is zero so no arrow is drawn.                       */
    path->arrow_size = 0.0;
    path->line_width = 1.0;

    /*  By default, all colors are set to black which has rgb = (0, 0, 0).    */
    kissvg_Path2DSetArrowFillColor(path, kissvg_Black);
    kissvg_Path2DSetArrowColor(path, kissvg_Black);
    kissvg_Path2DSetFillColor(path, kissvg_Black);
    kissvg_Path2DSetLineColor(path, kissvg_Black);

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
    free(path->data);

    if (kissvg_Path2DHasArrow(path))
    {
        free(path->arrow_pos);
        free(path->arrow_color);
        free(path->arrow_fill_color);
    }

    free(path);
    return;
}

void kissvg_Axis2DCreateTicks(kissvg_Axis2D *axis,
                              kissvg_TwoVector P,
                              kissvg_TwoVector Q)
{
    axis->has_ticks = kissvg_True;
    axis->tick_start = P;
    axis->tick_finish = Q;
    return;
}

void kissvg_Axis2DSetLineColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->line_color = color;
    return;
}

void kissvg_Axis2DSetArrowColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->arrow_color = color;
    return;
}

void kissvg_Axis2DSetArrowFillColor(kissvg_Axis2D *axis, kissvg_Color *color)
{
    axis->arrow_fill_color = color;
    return;
}

void kissvg_Axis2DSetLineWidth(kissvg_Axis2D *axis, double line_width)
{
    axis->line_width = line_width;
    return;
}

void kissvg_Axis2DSetArrowSize(kissvg_Axis2D *axis, double arrow_size)
{
    axis->arrow_size = arrow_size;
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
    kissvg_Axis2DSetArrowColor(axis, kissvg_Black);
    kissvg_Axis2DSetArrowFillColor(axis, kissvg_Black);
    kissvg_Axis2DSetTickColor(axis, kissvg_Black);
    kissvg_Axis2DSetLineWidth(axis, kissvg_DefaultAxes);
    kissvg_Axis2DSetArrowSize(axis, kissvg_DefaultArrow);
    kissvg_Axis2DSetTickSize(axis, kissvg_DefaultTickSize);
    kissvg_Axis2DSetTickDist(axis, kissvg_DefaultTickDist);
    kissvg_Axis2DSetTickHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiHeight(axis, kissvg_DefaultTickHeight);
    kissvg_Axis2DSetTickSemiSemiHeight(axis, kissvg_DefaultTickHeight);

    axis->start = start;
    axis->finish = finish;
    axis->canvas = canvas;

    axis->has_arrow = kissvg_True;
    axis->has_ticks = kissvg_False;
    axis->up_ticks = kissvg_False;
    axis->down_ticks = kissvg_False;

    return axis;
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
    free(axis);
    return;
}

kissvg_Circle *kissvg_CreateCircle(kissvg_TwoVector P, double r)
{
    kissvg_Circle *circle;

    circle = malloc(sizeof(*circle));

    circle->center = P;
    circle->radius = r;

    return circle;
}

void kissvg_DestroyCircle(kissvg_Circle *circle)
{
    free(circle);
    return;
}

extern kissvg_Circle **kissvg_ApolloniusProblem(kissvg_Circle *circle1,
                                                kissvg_Circle *circle2,
                                                kissvg_Circle *circle3)
{
    kissvg_Circle **solutions;
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
            center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
            radius = kissvg_Infinity;

            solutions[n] = kissvg_CreateCircle(center, radius);
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

            solutions[n] = kissvg_CreateCircle(center, radius);
        }
    }
    return solutions;
}

static void kissvg_DrawEndArrow(cairo_t *cr, kissvg_Path2D *path)
{
    kissvg_TwoVector Q;
    kissvg_TwoVector P0, P1;
    kissvg_TwoVector A0, A1, A2;
    kissvg_TwoMatrix R;
    kissvg_Canvas2D *canvas;
    kissvg_Color *color;
    double norm;
    double x, y;
    long N;

    canvas = kissvg_Path2DCanvas(path);
    N = kissvg_Path2DSize(path);

    P0 = kissvg_Path2DData(path)[N-2];
    P1 = kissvg_Path2DData(path)[N-1];

    Q = kissvg_TwoVectorSubtract(P1, P0);

    norm = kissvg_EuclideanNorm2D(Q);

    if (norm == 0)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tkissvg_DrawEndArrow\n\n"
            "The last two points in the input path are the same.\n"
            "Cannot compute the tangent vector at the end of the path.\n"
        );
        exit(0);
    }

    Q  = kissvg_TwoVectorScale(1.0/norm, Q);
    A0 = kissvg_TwoVectorScale(kissvg_Path2DArrowSize(path), Q);

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
    color = kissvg_Path2DArrowFillColor(path);
    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));

    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, 0.5);
    color = kissvg_Path2DArrowColor(path);
    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));
    cairo_stroke(cr);

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
        kissvg_DrawEndArrow(cr, path);
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

void kissvg_DrawCircle2D(cairo_t *cr, kissvg_TwoVector P, double radius,
                         double line_width, kissvg_Color *color,
                         kissvg_Canvas2D *canvas)
{
    double x, y;
    double scale;

    cairo_set_line_width(cr, line_width);

    scale = 0.5*(kissvg_Canvas2DXScale(canvas) + kissvg_Canvas2DYScale(canvas));
    x = kissvg_TwoVectorXComponent(P);
    y = kissvg_TwoVectorYComponent(P);

    x = kissvg_Canvas2DXShift(canvas) + kissvg_Canvas2DXScale(canvas) * x;
    y = kissvg_Canvas2DYShift(canvas) - kissvg_Canvas2DYScale(canvas) * y;

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(color),
                         kissvg_GreenColor(color),
                         kissvg_BlueColor(color));

    cairo_arc (cr, x, y, scale*radius, 0, 2 * M_PI);

    cairo_stroke(cr);
}

void kissvg_FillDrawCircle2D(cairo_t *cr, kissvg_TwoVector P, double radius,
                             double line_width, kissvg_Color *fill_color,
                             kissvg_Color *line_color, kissvg_Canvas2D *canvas)
{
    double x, y;
    double scale;

    cairo_set_line_width(cr, line_width);

    scale = 0.5*(kissvg_Canvas2DXScale(canvas) + kissvg_Canvas2DYScale(canvas));

    x = kissvg_Canvas2DXShift(canvas) +
        kissvg_Canvas2DXScale(canvas) * kissvg_TwoVectorXComponent(P);
    y = kissvg_Canvas2DYShift(canvas) -
        kissvg_Canvas2DYScale(canvas) * kissvg_TwoVectorYComponent(P);

    cairo_arc (cr, x, y, scale*radius, 0, 2 * M_PI);
    cairo_close_path(cr);

    cairo_save(cr);
    cairo_set_source_rgb(cr,
                         kissvg_RedColor(fill_color),
                         kissvg_GreenColor(fill_color),
                         kissvg_BlueColor(fill_color));
    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_source_rgb(cr,
                         kissvg_RedColor(line_color),
                         kissvg_GreenColor(line_color),
                         kissvg_BlueColor(line_color));
    cairo_stroke(cr);
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
    kissvg_Path2DSetArrowSize(path, axis->arrow_size);
    kissvg_Path2DSetArrowColor(path, axis->arrow_color);
    kissvg_Path2DSetArrowFillColor(path, axis->arrow_fill_color);

    if (axis->has_arrow)
    {
        kissvg_Path2DCreateArrow(path);
        kissvg_Path2DSetArrowSize(path, axis->arrow_size);
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

    if (kissvg_Path2DHasArrow(path))
        kissvg_DrawEndArrow(cr, path);

    kissvg_DestroyPath2D(path);
    return;
}
