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
        rel_angle = NAN;
    else
        rel_angle = acos(dot_prod/abs_prod);

    return rel_angle;
}

kissvg_bool kissvg_IsCollinear(kissvg_TwoVector A,
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
        return kissvg_true;
    else
        return kissvg_false;
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
        centerx = INFINITY;
        centery = INFINITY;
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
            centerx = INFINITY;
            centery = INFINITY;
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

            if (det_factor == 0)
            {
                centerx = INFINITY;
                centery = INFINITY;
            }
            else
            {
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

kissvg_TwoVector *kissvg_CircleCircleIntersection(kissvg_TwoVector P0,
                                                  double r0,
                                                  kissvg_TwoVector P1,
                                                  double r1);

kissvg_bool CircleCircleIntersectionIsEmpty(kissvg_TwoVector *Intersect);
kissvg_bool CircleCircleIntersectionIsAll(kissvg_TwoVector *Intersect);

kissvg_Path2D *kissvg_CreatePath2D(kissvg_TwoVector start)
{
    kissvg_Path2D *path;
    path = malloc(sizeof(*path));

    path->data = malloc(sizeof(*path->data));
    path->data[0] = start;
    path->N_Pts = 1;
    path->is_closed = kissvg_false;

    return path;
}

void kissvg_AppendPath2D(kissvg_Path2D *path, kissvg_TwoVector P)
{
    long new_path_size;

    if (path == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_AppendPath2D\n\n"
             "Input path is NULL. Aborting.");
        exit(0);
    }

    new_path_size = kissvg_Path2DSize(path) + 1;
    path->data = realloc(path->data, sizeof(*path->data) * new_path_size);

    if (path->data == NULL)
    {
        kissvg_Path2DSetError(path);
        kissvg_Path2DSetErrorMessage(path, "Error Encountered: KissVG\n"
                                           "\tFunction: kissvg_AppendPath2D\n\n"
                                           "Realloc failed and retured NULL.");
    }
    else
    {
        path->data[new_path_size-1] = P;
        path->N_Pts = new_path_size;
    }

    path->is_closed = kissvg_false;
    path->kissvg_error_occured = kissvg_false;
    path->filldraw = kissvg_false;
    path->linewidth = 3;
    path->red   = 0.0;
    path->green = 0.0;
    path->blue  = 0.0;
    return;
}

void kissvg_DestroyPath2D(kissvg_Path2D *path)
{
    free(path->data);
    free(path);
    return;
}

void kissvg_Path2DSetColors(kissvg_Path2D *path,
                            double red,
                            double green,
                            double blue)
{
    path->red = red;
    path->green = green;
    path->blue = blue;
    return;
}

void kissvg_Path2DSetLineWidth(kissvg_Path2D *path, double linewidth)
{
    path->linewidth = linewidth;
    return;
}


void kissvg_DrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;

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
    x = kissvg_TwoVectorXComponent(Pn);
    y = kissvg_TwoVectorYComponent(Pn);

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];
        x = kissvg_TwoVectorXComponent(Pn);
        y = kissvg_TwoVectorYComponent(Pn);
        cairo_line_to(cr, x, y);
    }

    if (kissvg_Path2DIsClosed(path))
        cairo_close_path(cr);

    cairo_set_line_width(cr, kissvg_Path2DLineWidth(path));
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
}

void kissvg_FillDrawPolygon2D(cairo_t *cr, kissvg_Path2D *path)
{
    double x, y;
    long n, path_size;
    kissvg_TwoVector Pn;

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
    x = kissvg_TwoVectorXComponent(Pn);
    y = kissvg_TwoVectorYComponent(Pn);

    cairo_move_to(cr, x, y);

    for (n=1; n<path_size; ++n)
    {
        Pn = kissvg_Path2DData(path)[n];
        x = kissvg_TwoVectorXComponent(Pn);
        y = kissvg_TwoVectorYComponent(Pn);
        cairo_line_to(cr, x, y);
    }

    cairo_close_path(cr);
    cairo_save(cr);
    cairo_set_source_rgb(cr,
                         kissvg_Path2DRed(path),
                         kissvg_Path2DGreen(path),
                         kissvg_Path2DBlue(path));
    cairo_fill_preserve(cr);
    cairo_restore(cr);

    cairo_set_line_width(cr, kissvg_Path2DLineWidth(path));
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
}
