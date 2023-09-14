/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *                                Euclidean 2D                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for two dimensional Euclidean geometry.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      EuclideanNormSquared2D                                                *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm, also called the L2 norm,   *
 *      of a point in the plane.                                              *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      norm_sq_P (real):                                                     *
 *          The square of the distance from the origin to P.                  *
 *  Method:                                                                   *
 *      Use the Pythagorean formula.                                          *
 *                                                                            *
 *          ||P||^2 = ||(x, y)||^2                                            *
 *                  = x^2 + y^2                                               *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
real EuclideanNormSquared2D(pair P)
{
    return P.x*P.x + P.y*P.y;
}

/******************************************************************************
 *  Function:                                                                 *
 *      EuclideanNorm2D                                                       *
 *  Purpose:                                                                  *
 *      Computes of the Euclidean norm, also called the L2 norm,              *
 *      of a point in the plane.                                              *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      norm_P (real):                                                        *
 *          The distance from the origin to P.                                *
 *  Method:                                                                   *
 *      Use the Pythagorean formula.                                          *
 *                                                                            *
 *          ||P|| = ||(x, y)||                                                *
 *                = sqrt(x^2 + y^2)                                           *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
real EuclideanNorm2D(pair P)
{
    return sqrt(EuclideanNormSquared2D(P));
}

/******************************************************************************
 *  Function:                                                                 *
 *      RectToPolar2D                                                         *
 *  Purpose:                                                                  *
 *      Converts a point in the plane from rectangular to polar coordinates.  *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane in Cartesian coordinates.          *
 *  Output:                                                                   *
 *      polar (pair):                                                         *
 *          P in polar coordinates. polar.x = radius, polar.y = angle.        *
 *  Method:                                                                   *
 *      Use various trig identities. From x = r cos(phi) and y = r sin(phi)   *
 *      we can compute r = sqrt(x^2 + y^2) and phi = atan2(y, x).             *
 ******************************************************************************/
pair RectToPolar2D(pair P)
{
    /*  Compute the angle P makes with the x axis.                            */
    real theta = atan2(P.y, P.x);

    /*  Compute the norm of P.                                                */
    real r = EuclideanNorm2D(P);

    /*  The polar representation is just (r, theta), so return this.          */
    return (r, theta);
}
/*  End of RectToPolar2D.                                                     */

/*  Function for converting a polar coordinate to rectangular.                */
pair PolarToRect2D(pair P)
{
    /*  Extract the radius and theta from the polar point P.                  */
    real r = P.x;
    real theta = P.y;

    /*  Compute the x and y coordinates of P and return.                      */
    return (r*cos(theta), r*sin(theta));
}
/*  End of PolarToRect2D.                                                     */

pair Scale2D(real r, pair P)
{
    return (r*P.x, r*P.y);
}

pair MidPoint2D(pair P, pair Q)
{
    return Scale2D(0.5, P + Q);
}

pair PointOnLine2D(real t, pair P, pair Q)
{
    pair X0 = Scale2D(1.0 - t, P);
    pair X1 = Scale2D(t, Q);
    return X0 + X1;
}

pair PlaneToDisk2D(pair P)
{
    real norm_squared = EuclideanNormSquared2D(P);
    real factor = 1.0 / (1.0 + norm_squared);
    return Scale2D(factor, P);
}

