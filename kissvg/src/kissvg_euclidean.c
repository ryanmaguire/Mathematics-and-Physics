/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************
 *                            kissvg_euclidean                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide basic tools for computational Euclidean geometry.             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>

/*  NOTE:                                                                     *
 *      Detailed descriptions of the functions are provided in kissvg.h.      */

/*  Function for computing the length of a two dimensional vector.            */
double kissvg_EuclideanNorm2D(kissvg_TwoVector P)
{
    /*  Declare the necessary variables for the computation.                  */
    double x_comp, y_comp;
    double norm;

    /*  Extract the x and y values of the vector P.                           */
    x_comp = kissvg_TwoVectorXComponent(P);
    y_comp = kissvg_TwoVectorYComponent(P);

    /*  Use kissvg_NewTwoVector to generate the output and return. sqrt is a  *
     *  C standard library function found in math.h, and math.h is included   *
     *  in the header kissvg_math.h. kissvg_SqrtDouble is an alias for this.  */
    norm = kissvg_SqrtDouble(x_comp*x_comp + y_comp*y_comp);
    return norm;
}

/*  Function for computing the standard Euclidean dot product of 2 two        *
 *  dimensional vectors P and Q.                                              */
double kissvg_EuclideanDotProduct2D(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double x0, y0;
    double x1, y1;
    double dot_product;

    /*  Extract the x and y components of the vector P.                       */
    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    /*  Extract the x and y components of the vector Q.                       */
    x1 = kissvg_TwoVectorXComponent(Q);
    y1 = kissvg_TwoVectorYComponent(Q);

    /*  Compute the dot product and return.                                   */
    dot_product = x0*x1 + y0*y1;
    return dot_product;
}

/*  Given a vector V, returns an orthogonal vector U with respect to the      *
 *  standard Euclidean dot product. That is, a vector U with <V|U> = 0        *
 *  (using bra-ket notation).                                                 */
kissvg_TwoVector kissvg_EuclideanOrthogonalVector2D(kissvg_TwoVector V)
{
    /*  Declare necessary variables.                                          */
    kissvg_TwoVector orth;
    double x_comp, y_comp;

    /*  Extract the x and y values from the input vector.                     */
    x_comp = kissvg_TwoVectorXComponent(V);
    y_comp = kissvg_TwoVectorYComponent(V);

    /*  Simply return (-y, x) since this will be orthogonal. That is, the dot *
     *  product is <V|U> = <(x,y)|(-y,x)> = -xy + yx = 0.                     */
    orth = kissvg_NewTwoVector(-y_comp, x_comp);
    return orth;
}

/*  Function for computing the angle between the lines OP and OQ given three  *
 *  kissvg_TwoVector's O, P, and Q.                                           */
double kissvg_EuclideanRelAngle2D(kissvg_TwoVector O,
                                  kissvg_TwoVector P,
                                  kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double dot_prod;
    double abs_prod;
    double rel_angle;

    /*  We to compute the vector from O to P and O to Q, so declare these.    */
    kissvg_TwoVector OP;
    kissvg_TwoVector OQ;

    /*  Compute the vector pointing from O to P, which is simply P-O. Do the  *
     *  same thing for O and Q.                                               */
    OP = kissvg_TwoVectorSubtract(P, O);
    OQ = kissvg_TwoVectorSubtract(Q, O);

    /*  The angle formula is arccos(a dot b / norm(a)norm(b)). First we'll    *
     *  compute the dot product, then check that norm(a)norm(b) is non-zero.  */
    dot_prod = kissvg_EuclideanDotProduct2D(OP, OQ);
    abs_prod = kissvg_EuclideanNorm2D(OP)*kissvg_EuclideanNorm2D(OQ);

    /*  If norm(OP)norm(OQ) is zero, then one of these vectors is the zero    *
     *  vector, meaning the angle is undefined. We then return Not-A-Number.  */
    if (abs_prod == 0.0)
        rel_angle = kissvg_NaN;

    /*  If norm(OP)norm(OQ) is non-zero, we may use the angle formula. Note,  *
     *  acos is a C standard library function found in math.h. This header    *
     *  file is included with kissvg_math.h.                                  */
    else
        rel_angle = acos(dot_prod/abs_prod);

    return rel_angle;
}

/*  Function for determining if three planar vectors are collinear.           */
kissvg_Bool kissvg_EuclideanIsCollinear(kissvg_TwoVector A,
                                        kissvg_TwoVector B,
                                        kissvg_TwoVector C)
{
    /*  The method simply checks the determinant of the matrix formed by      *
     *  the column vector AB and AC. This is equivalent to seeing if the      *
     *  cross product of AB and AC is zero.                                   */
    kissvg_TwoVector AB;
    kissvg_TwoVector AC;
    double ABx, ABy;
    double ACx, ACy;
    double det;

    /*  Compute the vectors pointing from A to B and A to C.                  */
    AB = kissvg_TwoVectorSubtract(B, A);
    AC = kissvg_TwoVectorSubtract(C, A);

    /*  Extract the x and y components of AB.                                 */
    ABx = kissvg_TwoVectorXComponent(AB);
    ABy = kissvg_TwoVectorYComponent(AB);

    /*  Extract the x and y components of AC.                                 */
    ACx = kissvg_TwoVectorXComponent(AC);
    ACy = kissvg_TwoVectorYComponent(AC);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    det = ABx*ACy - ABy*ACx;

    if (det == 0.0)
        return kissvg_True;
    else
        return kissvg_False;
}

/*  Function for computing the midpoint of 2 two dimensional vectors.         */
kissvg_TwoVector kissvg_EuclideanMidPoint2D(kissvg_TwoVector P,
                                            kissvg_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double x0, y0;
    double x1, y1;
    double xmid, ymid;
    kissvg_TwoVector midpoint;

    /*  Extract the x and y components of the vector P.                       */
    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    /*  Extract the x and y components of the vector Q.                       */
    x1 = kissvg_TwoVectorXComponent(Q);
    y1 = kissvg_TwoVectorYComponent(Q);

    /*  Compute the midpoint of P and Q, which is simply 0.5*(P+Q).           */
    xmid = 0.5*(x0 + x1);
    ymid = 0.5*(y0 + y1);

    /*  Use kissvg_NewTwoVector to create the new output and return.          */
    midpoint = kissvg_NewTwoVector(xmid, ymid);
    return midpoint;
}

/*  Function for determining the center of three points in the plane.         */
kissvg_Circle *kissvg_EuclideanFindCenter2D(kissvg_TwoVector A,
                                            kissvg_TwoVector B,
                                            kissvg_TwoVector C)
{
    /*  Declare the necessary variables.                                      */
    kissvg_TwoVector U;
    kissvg_TwoVector V;
    kissvg_TwoVector MidPointAB, MidPointAC;
    kissvg_TwoVector center;
    kissvg_Line2D *L0, *L1;
    kissvg_Circle *circle;
    double radius;

    /*  If A, B, and C are collinear, their center is "at infinity."          */
    if (kissvg_EuclideanIsCollinear(A, B, C))
    {
        center = kissvg_NewTwoVector(kissvg_Infinity, kissvg_Infinity);
        radius = kissvg_Infinity;

        circle = kissvg_CreateCircle(center, radius, NULL);
        kissvg_CircleSetIsLine(circle, kissvg_True);

        V = kissvg_TwoVectorSubtract(A, B);
        U = kissvg_TwoVectorSubtract(A, C);
        kissvg_CircleSetPoint(circle, A);

        if (!(kissvg_EuclideanNorm2D(V) == 0.0))
            kissvg_CircleSetVelocity(circle, V);
        else if (!(kissvg_EuclideanNorm2D(U) == 0.0))
            kissvg_CircleSetVelocity(circle, U);
        else
        {
            if (!(kissvg_EuclideanNorm2D(V) == 0.0))
                kissvg_CircleSetVelocity(circle, V);
            else
            {
                kissvg_SetError(circle, kissvg_True);
                kissvg_SetErrorMessage(circle,
                                       "Error Encountered: KissVG\n"
                                       "\tFunction: kissvg_FindCenter2D\n\n"
                                       "All three points are the same.\n");
                kissvg_CircleSetVelocity(circle, A);
                return circle;
            }
        }
    }

    /*  Otherwise, following Euclid, we compute the bisectors of the lines AB *
     *  and AC, and then find where these intersect.                          */
    else
    {
        U = kissvg_TwoVectorSubtract(A, B);
        V = kissvg_TwoVectorSubtract(A, C);
        MidPointAB = kissvg_EuclideanMidPoint2D(A, B);
        MidPointAC = kissvg_EuclideanMidPoint2D(A, C);

        U = kissvg_EuclideanOrthogonalVector2D(U);
        V = kissvg_EuclideanOrthogonalVector2D(V);

        L0 = kissvg_CreateLineFromPointAndTangent(MidPointAB, U, NULL);
        L1 = kissvg_CreateLineFromPointAndTangent(MidPointAC, V, NULL);

        center = kissvg_LineLineIntersection(L0, L1);
        kissvg_DestroyLine2D(L0);
        kissvg_DestroyLine2D(L1);
        U = kissvg_TwoVectorSubtract(center, A);
        radius = kissvg_EuclideanNorm2D(U);
        circle = kissvg_CreateCircle(center, radius, NULL);
    }

    return circle;
}

kissvg_TwoVector kissvg_ClosestPointOnLine(kissvg_Line2D *L, kissvg_TwoVector P)
{
    kissvg_TwoVector orth;
    kissvg_TwoVector V;
    kissvg_TwoVector out;
    kissvg_Line2D *orthline;

    V = kissvg_Line2DTangent(L);
    orth = kissvg_EuclideanOrthogonalVector2D(V);
    orthline = kissvg_CreateLineFromPointAndTangent(P, orth, NULL);
    out = kissvg_LineLineIntersection(L, orthline);

    kissvg_DestroyLine2D(orthline);
    return out;
}

kissvg_TwoVector kissvg_ClosestPointOnCircle(kissvg_Circle *C,
                                             kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    kissvg_TwoVector center;
    kissvg_TwoVector Pcirc, Vcirc;
    kissvg_Line2D *L;
    kissvg_Bool is_line;
    double radius, norm;

    is_line = kissvg_CircleIsLine(C);

    if (is_line)
    {
        Pcirc = kissvg_CirclePoint(C);
        Vcirc = kissvg_CircleTangent(C);
        L = kissvg_CreateLineFromPointAndTangent(Pcirc, Vcirc, NULL);
        out = kissvg_ClosestPointOnLine(L, P);
        kissvg_DestroyLine2D(L);
    }
    else
    {
        center = kissvg_CircleCenter(C);
        radius = kissvg_CircleRadius(C);
        out = kissvg_TwoVectorSubtract(P, center);
        norm = kissvg_EuclideanNorm2D(out);
        if (norm == 0.0)
            out = kissvg_NewTwoVector(radius, 0.0);
        else
            out = kissvg_TwoVectorScale(radius/norm, out);

        out = kissvg_TwoVectorAdd(out, center);
    }
    return out;
}

kissvg_TwoVector kissvg_FurthestPointOnCircle(kissvg_Circle *C,
                                              kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    kissvg_TwoVector center;
    kissvg_TwoVector Pcirc, Vcirc;
    kissvg_Line2D *L;
    kissvg_Bool is_line;
    double radius, norm;

    is_line = kissvg_CircleIsLine(C);

    if (is_line)
    {
        Pcirc = kissvg_CirclePoint(C);
        Vcirc = kissvg_CircleTangent(C);
        L = kissvg_CreateLineFromPointAndTangent(Pcirc, Vcirc, NULL);
        out = kissvg_ClosestPointOnLine(L, P);
        kissvg_DestroyLine2D(L);
    }
    else
    {
        center = kissvg_CircleCenter(C);
        radius = kissvg_CircleRadius(C);
        out = kissvg_TwoVectorSubtract(P, center);
        norm = kissvg_EuclideanNorm2D(out);
        if (norm == 0.0)
            out = kissvg_NewTwoVector(-radius, 0.0);
        else
            out = kissvg_TwoVectorScale(-radius/norm, out);

        out = kissvg_TwoVectorAdd(out, center);
    }
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

