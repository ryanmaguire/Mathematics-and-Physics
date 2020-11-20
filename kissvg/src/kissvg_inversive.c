
#include <kissvg/src/kissvg.h>
#include <kissvg/src/kissvg_math.h>
#include <kissvg/src/kissvg_vector.h>
#include <kissvg/src/kissvg_matrix.h>
#include <kissvg/src/kissvg_circle.h>
#include <kissvg/src/kissvg_line.h>
#include <kissvg/src/kissvg_euclidean.h>
#include <kissvg/src/kissvg_inversive.h>


kissvg_TwoVector kissvg_InversiveGeometryPoint(kissvg_Circle *C,
                                               kissvg_TwoVector P)
{
    kissvg_TwoVector OP, invP;
    kissvg_TwoVector center;
    double radius, invradius;
    double norm;

    center = kissvg_Circle_Center(C);
    radius = kissvg_Circle_Radius(C);
    OP = kissvg_TwoVector_Subtract(P, center);
    norm = kissvg_Euclidean_Norm_2D(OP);

    if (norm == 0.0)
        invP = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
    else
    {
        invradius = radius * radius / norm;
        invP = kissvg_TwoVector_Scale(invradius/norm, OP);
        invP = kissvg_TwoVector_Add(invP, center);
    }
    return invP;
}

kissvg_Circle *kissvg_InversiveGeometryCircle(kissvg_Circle *C0,
                                              kissvg_Circle *C1)
{
    kissvg_TwoVector center;
    kissvg_TwoVector closest, furthest;
    kissvg_TwoVector perp;
    kissvg_Circle *out;
    kissvg_Palette *palette;
    double radius;
    double closest_norm, furthest_norm;

    palette = kissvg_Get_Palette(C0);
    center = kissvg_Circle_Center(C0);
    closest = kissvg_Closest_Point_On_Circle(C1, center);
    furthest = kissvg_Furthest_Point_On_Circle(C1, center);

    closest_norm = kissvg_Euclidean_Norm_2D(
        kissvg_TwoVector_Subtract(center, closest)
    );

    furthest_norm = kissvg_Euclidean_Norm_2D(
        kissvg_TwoVector_Subtract(center, furthest)
    );

    if (furthest_norm == 0.0)
    {
        center = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;
        out = kissvg_Create_Circle(center, radius, palette);
    }
    else if (closest_norm == 0.0)
    {
        furthest = kissvg_InversiveGeometryPoint(C0, furthest);
        center = kissvg_New_TwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;
        perp = kissvg_Euclidean_Orthogonal_Vector_2D(furthest);
        out = kissvg_Create_Circle(center, radius, palette);
        kissvg_Circle_Set_Line(out, furthest, perp);
    }
    else
    {
        closest = kissvg_InversiveGeometryPoint(C0, closest);
        furthest = kissvg_InversiveGeometryPoint(C0, furthest);
        radius = 0.5*kissvg_Euclidean_Norm_2D(
            kissvg_TwoVector_Subtract(closest, furthest)
        );

        center = kissvg_Euclidean_Midpoint_2D(closest, furthest);
        out = kissvg_Create_Circle(center, radius, palette);
    }
    return out;
}

kissvg_Circle *kissvg_InversiveGeometryLine(kissvg_Circle *C,
                                             kissvg_Line2D *L)
{
    kissvg_TwoVector center;
    kissvg_TwoVector P;
    kissvg_Circle *out_circle;
    kissvg_Palette *palette;
    double radius;

    palette = kissvg_Get_Palette(L);
    center = kissvg_Circle_Center(C);
    P = kissvg_Closest_Point_On_Line2D(L, center);
    P = kissvg_InversiveGeometryPoint(C, P);

    center = kissvg_Euclidean_Midpoint_2D(center, P);
    radius = kissvg_Euclidean_Norm_2D(kissvg_TwoVector_Subtract(P, center));
    out_circle = kissvg_Create_Circle(center, radius, palette);
    return out_circle;
}
