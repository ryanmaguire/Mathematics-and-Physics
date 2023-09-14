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

/******************************************************************************
 *  Function:                                                                 *
 *      PolarToRect2D                                                         *
 *  Purpose:                                                                  *
 *      Converts a point in the plane from polar to rectangular coordinates.  *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane in polar coordinates.              *
 *  Output:                                                                   *
 *      rect (pair):                                                          *
 *          P in rectangular coordinates.                                     *
 *  Method:                                                                   *
 *      Compute x = r cos(phi) and y = r sin(phi).                            *
 ******************************************************************************/
pair PolarToRect2D(pair P)
{
    /*  Extract the radius and theta from the polar point P.                  */
    real r = P.x;
    real theta = P.y;

    /*  Compute the x and y coordinates of P and return.                      */
    return (r*cos(theta), r*sin(theta));
}
/*  End of PolarToRect2D.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      Scale2D                                                               *
 *  Purpose:                                                                  *
 *      Scales a point in the plane by a real number.                         *
 *  Arguments:                                                                *
 *      r (real):                                                             *
 *          A real number, the scalar being multiplied to the point.          *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      rP (pair):                                                            *
 *          The point r*P, P scaled by r.                                     *
 *  Method:                                                                   *
 *      Multiply component-wise. Given P = (x, y), return (r*x, r*y).         *
 ******************************************************************************/
pair Scale2D(real r, pair P)
{
    return (r*P.x, r*P.y);
}
/*  End of Scale2D.                                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      MidPoint2D                                                            *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in the plane.                     *
 *  Arguments:                                                                *
 *      P (real):                                                             *
 *          A point in the Euclidean plane.                                   *
 *      Q (pair):                                                             *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      mid (pair):                                                           *
 *          The midpoint of P and Q.                                          *
 *  Method:                                                                   *
 *      Compute the average of the vector sum. That is:                       *
 *                                                                            *
 *                P + Q                                                       *
 *          mid = -----                                                       *
 *                  2                                                         *
 *                                                                            *
 *              = (Px, Py) + (Qx, Qy)                                         *
 *                -------------------                                         *
 *                         2                                                  *
 *                                                                            *
 *              = (Px + Qx, Py + Qy)                                          *
 *                ------------------                                          *
 *                        2                                                   *
 *                 -                 -                                        *
 *                | Px + Qx   Py + Qy |                                       *
 *              = | ------- , ------- |                                       *
 *                |    2         2    |                                       *
 *                 -                 -                                        *
 *                                                                            *
 *      This is computed and returned.                                        *
 ******************************************************************************/
pair MidPoint2D(pair P, pair Q)
{
    return Scale2D(0.5, P + Q);
}
/*  End of MidPoint2D.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      PointOnLine2D                                                         *
 *  Purpose:                                                                  *
 *      Computes the point on a line parameterized by two fixed points.       *
 *  Arguments:                                                                *
 *      t (real):                                                             *
 *          The time parameter corresponding to the desired point.            *
 *      P (pair):                                                             *
 *          The starting point for the line, corresponding to t = 0.          *
 *      Q (pair):                                                             *
 *          The finishing point for the line, corresponding to t = 1.         *
 *  Output:                                                                   *
 *      out (pair):                                                           *
 *          The point (1-t)P + tQ.                                            *
 *  Method:                                                                   *
 *      Compute (1-t)*P and t*Q and then compute their sum.                   *
 ******************************************************************************/
pair PointOnLine2D(real t, pair P, pair Q)
{
    pair X0 = Scale2D(1.0 - t, P);
    pair X1 = Scale2D(t, Q);
    return X0 + X1;
}
/*  End of PointOnLine2D.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      PlaneToDisk2D                                                         *
 *  Purpose:                                                                  *
 *      Provides an explicit smooth transformation of the Euclidean plane to  *
 *      the unit disk (i.e. a diffeomorphism).                                *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      out (pair):                                                           *
 *          The point P transformed to the unit disk.                         *
 *  Method:                                                                   *
 *      Compute 1 / (1 + ||P||^2) and scale the input by this.                *
 ******************************************************************************/
pair PlaneToDisk2D(pair P)
{
    real norm_squared = EuclideanNormSquared2D(P);
    real factor = 1.0 / (1.0 + norm_squared);
    return Scale2D(factor, P);
}
/*  End of PlaneToDisk2D.                                                     */

/*  Compute the dot product of two 2-dimensional vectors.                     */
real DotProduct2D(pair P, pair Q)
{
    /*  Compute the Euclidean dot product and return.                         */
    return P.x*Q.x + P.y*Q.y;
}
/*  End of DotProduct2D.                                                      */

/*  Returns the angle between X and Y relative to the point O.                */
real RelAngle2D(pair O, pair X, pair Y)
{
    /*  Compute the relative position vectors from X and Y to O.              */
    pair P = X - O;
    pair Q = Y - O;

    /*  Compute the dot product of P and Q.                                   */
    real dot_prod = DotProduct2D(P, Q);

    /*  Compute the product of the norms of P and Q as well.                  */
    real abs_prod = EuclideanNorm2D(P)*EuclideanNorm2D(Q);

    /*  If abs_prod is 0, either P = O, or Q = O. In either case the angle is *
     *  undefined, so return Not-a-Number.                                    */
    if (abs_prod == 0.0)
        return nan;

    /*  Otherwise, use the fact that <a|b> = ||a|| ||b|| cos(theta), where    *
     *  <a|b> denotes the dot product of a and b, and ||a|| represents the    *
     *  Euclidean norm of a. Using this, we solve for theta.                  */
    return acos(dot_prod / abs_prod);
}
/*  End of RelAngle2D.                                                        */
