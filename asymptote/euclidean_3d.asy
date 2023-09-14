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
 *                                Euclidean 3D                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for three dimensional Euclidean geometry.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 13, 2023                                            *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      EuclideanNormSquared3D                                                *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm, also called the L2 norm,   *
 *      of a point in space.                                                  *
 *  Arguments:                                                                *
 *      P (triple):                                                           *
 *          A point in Euclidean space.                                       *
 *  Output:                                                                   *
 *      norm_sq_P (real):                                                     *
 *          The square of the distance from the origin to P.                  *
 *  Method:                                                                   *
 *      Use the Pythagorean formula.                                          *
 *                                                                            *
 *          ||P||^2 = ||(x, y, z)||^2                                         *
 *                  = x^2 + y^2 + z^2                                         *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
real EuclideanNormSquared3D(triple P)
{
    return P.x*P.x + P.y*P.y + P.z*P.z;
}

/******************************************************************************
 *  Function:                                                                 *
 *      EuclideanNorm3D                                                       *
 *  Purpose:                                                                  *
 *      Computes of the Euclidean norm, also called the L2 norm,              *
 *      of a point in space.                                                  *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in Euclidean space.                                       *
 *  Output:                                                                   *
 *      norm_P (real):                                                        *
 *          The distance from the origin to P.                                *
 *  Method:                                                                   *
 *      Use the Pythagorean formula.                                          *
 *                                                                            *
 *          ||P|| = ||(x, y, z)||                                             *
 *                = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
real EuclideanNorm3D(triple P)
{
    return sqrt(EuclideanNormSquared3D(P));
}

triple Scale3D(real r, triple P)
{
    return (r*P.x, r*P.y, r*P.z);
}

/*  Get a point on the line PQ with respect to the parameter t.               */
triple PointOnLine3D(real t, triple P, triple Q)
{
    /*  Compute the vector (1-t)P + tQ.                                       */
    triple X0 = Scale3D(1.0 - t, P);
    triple X1 = Scale3D(t, Q);

    /*  Compute the output and return it.                                     */
    return X0 + X1;
}
/*  End of PointOnLine3D.                                                     */

/* Find midpoint given two points in space.                                   */
triple MidPoint3D(triple A, triple B)
{
    /*  Compute the midpoint using the midpoint formula.                      */
    return Scale3D(0.5, A+B);
}
/*  End of MidPoint3D.                                                        */

real CylindricalComponentSquared3D(triple P)
{
    return P.x*P.x + P.y*P.y;
}

real CyldindricalComponent3D(triple P)
{
    return sqrt(CylindricalComponentSquared3D(P));
}

/*  Diffeomorphism from R^3 to the unit ball.                                 */
triple SpaceToBall3D(triple P)
{
    /*  Compute the length of P.                                              */
    real norm_squared = EuclideanNormSquared3D(P);

    /*  The scale factor is 1 / (1 + ||P||^2). Compute this.                  */
    real factor = 1.0 / (1.0 + norm_squared);
    return Scale3D(factor, P);
}
/*  End of SpaceToBall3D.                                                     */

/*  Convert Cartesian to spherical coordinates.                               */
triple RectToSpherical3D(real x, real y, real z)
{
    /*  Compute the projection in the xy plane (rho), and r.                  */
    real rho_squared = x*x + y*y;
    real rho = sqrt(rho_squared);
    real r = sqrt(rho_squared + z*z);

    /*  Compute the azimuth and zenith angles, and return (r, phi, theta).    */
    real phi = atan2(y, x);
    real theta = pi - atan2(z, rho);
    return (r, phi, theta);
}
/*  End of RectToSpherical3D.                                                 */
