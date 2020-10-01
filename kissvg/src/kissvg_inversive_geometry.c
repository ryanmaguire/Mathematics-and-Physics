
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>

kissvg_TwoVector kissvg_InversiveGeometryPoint(kissvg_Circle *C,
                                               kissvg_TwoVector P)
{
    kissvg_TwoVector OP, invP;
    kissvg_TwoVector center;
    double radius, invradius;
    double norm;

    center = kissvg_CircleCenter(C);
    radius = kissvg_CircleRadius(C);
    OP = kissvg_TwoVectorSubtract(P, center);
    norm = kissvg_EuclideanNorm2D(OP);

    if (norm == 0.0)
        invP = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
    else
    {
        invradius = radius * radius / norm;
        invP = kissvg_TwoVectorScale(invradius/norm, OP);
        invP = kissvg_TwoVectorAdd(invP, center);
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
    kissvg_Canvas2D *canvas;
    double radius;
    double closest_norm, furthest_norm;

    canvas = kissvg_GetCanvas(C0);
    center = kissvg_CircleCenter(C0);
    closest = kissvg_ClosestPointOnCircle(C1, center);
    furthest = kissvg_FurthestPointOnCircle(C1, center);

    closest_norm = kissvg_EuclideanNorm2D(
        kissvg_TwoVectorSubtract(center, closest)
    );

    furthest_norm = kissvg_EuclideanNorm2D(
        kissvg_TwoVectorSubtract(center, furthest)
    );

    if (furthest_norm == 0.0)
    {
        center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;
        out = kissvg_CreateCircle(center, radius, canvas);
    }
    else if (closest_norm == 0.0)
    {
        furthest = kissvg_InversiveGeometryPoint(C0, furthest);
        center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;
        out = kissvg_CreateCircle(center, radius, canvas);
        kissvg_CircleSetIsLine(out, kissvg_True);
        perp = kissvg_EuclideanOrthogonalVector2D(furthest);

        kissvg_CircleSetPoint(out, furthest);
        kissvg_CircleSetVelocity(out, perp);
    }
    else
    {
        closest = kissvg_InversiveGeometryPoint(C0, closest);
        furthest = kissvg_InversiveGeometryPoint(C0, furthest);
        radius = 0.5*kissvg_EuclideanNorm2D(
            kissvg_TwoVectorSubtract(closest, furthest)
        );

        center = kissvg_EuclideanMidPoint2D(closest, furthest);
        out = kissvg_CreateCircle(center, radius, canvas);
    }
    return out;
}

kissvg_Circle *kissvg_InversiveGeometryLine(kissvg_Circle *C,
                                            kissvg_Line2D *L)
{
    kissvg_TwoVector center;
    kissvg_TwoVector P;
    kissvg_Circle *out_circle;
    kissvg_Canvas2D *canvas;
    double radius;

    canvas = kissvg_GetCanvas(L);

    center = kissvg_CircleCenter(C);
    P = kissvg_ClosestPointOnLine(L, center);
    P = kissvg_InversiveGeometryPoint(C, P);

    center = kissvg_EuclideanMidPoint2D(center, P);
    radius = kissvg_EuclideanNorm2D(kissvg_TwoVectorSubtract(P, center));
    out_circle = kissvg_CreateCircle(center, radius, canvas);
    return out_circle;
}
