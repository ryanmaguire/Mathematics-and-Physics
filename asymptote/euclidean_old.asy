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
 *                             Euclidean Geometry                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for two dimensional Euclidean geometry.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************/

/*  Convert rectangular coordinates to polar.                                 */
pair RectToPolar(pair P)
{
    /*  Declare points for the unit x vector and the origin.                  */
    pair O = (0.0, 0.0);
    pair X = (1.0, 0.0);

    /*  Compute the angle P makes with the x axis.                            */
    real theta = atan2(P.y, P.x);

    /*  Compute the norm of P.                                                */
    real r = EuclideanNorm2D(P);

    /*  The polar representation is just (r, theta), so return this.          */
    return (r, theta);
}
/*  End of RectToPolar.                                                       */

/*  Function for converting a polar coordinate to rectangular.                */
pair PolarToRect(pair P)
{
    /*  Extract the radius and theta from the polar point P.                  */
    real r = P.x;
    real theta = P.y;

    /*  Compute the x and y coordinates of P and return.                      */
    return (r*cos(theta), r*sin(theta));
}
/*  End of PolarToRect.                                                       */

/******************************************************************************
 ******************************************************************************
 *                     Begin Three Dimensional Functions                      *
 ******************************************************************************
 ******************************************************************************/

/*  Get a point on the line PQ with respect to the parameter t.               */
triple PointOnLine3D(real t, triple P, triple Q)
{
    /*  Compute the vector (1-t)P + tQ.                                       */
    triple X0 = ScaleThreeVector(1.0 - t, P);
    triple X1 = ScaleThreeVector(t, Q);

    /*  Compute the output and return it.                                     */
    return X0 + X1;
}
/*  End of PointOnLine3D.                                                     */

/* Find midpoint given two points in space.                                   */
triple MidPoint3D(triple A, triple B)
{
    /*  Compute the midpoint using the midpoint formula.                      */
    return ScaleThreeVector(0.5, A+B);
}
/*  End of MidPoint3D.                                                        */

/*  Diffeomorphism from R^3 to the unit ball.                                 */
triple SpaceToBall(triple P)
{
    /*  Compute the length of P.                                              */
    real norm_squared = EuclideanNormSquared3D(P);

    /*  The scale factor is 1 / (1 + ||P||^2). Compute this.                  */
    real scale_factor = 1.0 / (1.0 + norm_squared);
    return ScaleThreeVector(scale_factor, P);
}
/*  End of SpaceToBall.                                                       */

/*  Convert Cartesian to spherical coordinates.                               */
triple RectToSpherical(real x, real y, real z)
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
/*  End of RectToSpherical.                                                   */
