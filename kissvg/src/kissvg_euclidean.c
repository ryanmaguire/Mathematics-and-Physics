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
