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
 *                                    vec2                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a 2D vector struct. Experiments with the asymptote language. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 16, 2023                                            *
 ******************************************************************************/

/*  Struct for vectors in the plane.                                          */
struct Vec2 {

    /*  A point in the plane is represented by Cartesian coordinates.         */
    real x, y;

    /*  Constructor from two real numbers, the x and y coordinates.           */
    void operator init(real x, real y)
    {
        this.x = x;
        this.y = y;
    }

    /*  Initializer with no inputs. Set *this* to the origin.                 */
    void operator init()
    {
        this.x = 0.0;
        this.y = 0.0;
    }

    /**************************************************************************
     *  Method:                                                               *
     *      NormSq                                                            *
     *  Purpose:                                                              *
     *      Computes the square of the Euclidean norm, also called the L2     *
     *      norm, of the vector.                                              *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      norm_sq (real):                                                   *
     *          The square of the distance from the origin to *this*.         *
     *  Method:                                                               *
     *      Use the Pythagorean formula.                                      *
     *                                                                        *
     *          ||P||^2 = ||(x, y)||^2                                        *
     *                  = x^2 + y^2                                           *
     *                                                                        *
     *      Compute this and return.                                          *
     **************************************************************************/
    real NormSq()
    {
        return this.x*this.x + this.y*this.y;
    }
    /*  End of NormSq.                                                        */

    /**************************************************************************
     *  Method:                                                               *
     *      Norm                                                              *
     *  Purpose:                                                              *
     *      Compute the magnitude of the vector.                              *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      norm (real):                                                      *
     *          The distance from the origin to *this*.                       *
     *  Method:                                                               *
     *      Use the Pythagorean formula.                                      *
     *                                                                        *
     *          ||P|| = ||(x, y)||                                            *
     *                = sqrt(x^2 + y^2)                                       *
     *                                                                        *
     *      Compute this and return.                                          *
     **************************************************************************/
    real Norm()
    {
        return sqrt(this.NormSq());
    }
    /*  End of Norm.                                                          */

    /**************************************************************************
     *  Method:                                                               *
     *      PolarAngle                                                        *
     *  Purpose:                                                              *
     *      Computes the angle the vector makes with the positive x axis.     *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      theta (real):                                                     *
     *          The angle *this* makes with the positive x axis.              *
     *  Method:                                                               *
     *      The angle can be computed with the atan2 function. Given (x, y)   *
     *      in the plane, return the value atan2(y, x).                       *
     **************************************************************************/
    real PolarAngle()
    {
        return atan2(this.y, this.x);
    }
    /*  End of PolarAngle.                                                    */

    /**************************************************************************
     *  Method:                                                               *
     *      Dot                                                               *
     *  Purpose:                                                              *
     *      Computes the Euclidean dot product of *this* with another vector. *
     *  Arguments:                                                            *
     *      v (Vec2):                                                         *
     *          A point in the plane.                                         *
     *  Output:                                                               *
     *      dot_prod (real):                                                  *
     *          The dot product of *this* and v.                              *
     *  Method:                                                               *
     *      Compute the sum of the products of the components.                *
     **************************************************************************/
    real Dot(Vec2 v)
    {
        return this.x*v.x + this.y*v.y;
    }
    /*  End of Dot.                                                           */

    /**************************************************************************
     *  Method:                                                               *
     *      AsUnitNormal                                                      *
     *  Purpose:                                                              *
     *      Normalizes a non-zero vector to unit magnitude.                   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      u (Vec2):                                                         *
     *          The unit vector pointing in the direction of *this*.          *
     *  Method:                                                               *
     *      Scale *this* by the reciprocal of its norm.                       *
     **************************************************************************/
    Vec2 AsUnitNormal()
    {
        /*  Avoid division by zero, and a possibly redundant square root      *
         *  call, by computing ||*this*||^2 and checking if it is zero.       */
        real norm_sq = this.NormSq();
        real factor;

        /*  Division by zero is undefined, return a NaN vector.               */
        if (norm_sq == 0.0)
            return Vec2(nan, nan);

        /*  Otherwise compute the scale factor 1 / ||*this*|| and normalize.  */
        factor = 1.0 / sqrt(norm_sq);
        return Vec2(factor*this.x, factor*this.y);
    }
    /*  End of AsUnitNormal.                                                  */

    /**************************************************************************
     *  Method:                                                               *
     *      Normalize                                                         *
     *  Purpose:                                                              *
     *      Normalizes a non-zero vector to unit magnitude.                   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Scale *this* by the reciprocal of its norm.                       *
     **************************************************************************/
    void Normalize()
    {
        /*  Avoid division by zero, and a possibly redundant square root      *
         *  call, by computing ||*this*||^2 and checking if it is zero.       */
        real norm_sq = this.NormSq();
        real factor;

        /*  Division by zero is undefined, set components to NaN.             */
        if (norm_sq == 0.0)
        {
            this.x = nan;
            this.y = nan;
        }

        /*  Otherwise compute the scale factor 1 / ||*this*|| and normalize.  */
        factor = 1.0 / sqrt(norm_sq);
        this.x *= factor;
        this.y *= factor;
    }
    /*  End of Normalize.                                                     */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthogonal                                                        *
     *  Purpose:                                                              *
     *      Computes a vector orthogonal to *this* of the same magnitude.     *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      ortho (Vec2):                                                     *
     *          A vector that is orthogonal to *this* with the same magnitude.*
     *  Method:                                                               *
     *      Return (-this.y, this.x). This follows the right-hand rule.       *
     **************************************************************************/
    Vec2 Orthogonal()
    {
        return Vec2(-this.y, this.x);
    }
    /*  End of Orthogonal.                                                    */

    /*  Alias for the Orthogonal function.                                    */
    Vec2 AsOrthogonal() = Orthogonal;

    /**************************************************************************
     *  Method:                                                               *
     *      AsUnitOrthogonal                                                  *
     *  Purpose:                                                              *
     *      Computes a vector orthogonal to *this* of unit magnitude.         *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      unit_ortho (Vec2):                                                *
     *          A vector that is orthogonal to *this* with unit magnitude.    *
     *  Method:                                                               *
     *      Normalize (-this.y, this.x). This follows the right-hand rule.    *
     **************************************************************************/
    Vec2 AsUnitOrthogonal()
    {
        return this.Orthogonal().AsUnitNormal();
    }
    /*  End of AsUnitOrthogonal.                                              */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthogonalize                                                     *
     *  Purpose:                                                              *
     *      Computes a vector orthogonal to *this* of the same magnitude.     *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Return (-this.y, this.x). This follows the right-hand rule.       *
     **************************************************************************/
    void Orthogonalize()
    {
        /*  Avoid overwriting the data in an unrecoverable way. Save this.x.  */
        real x = this.x;

        /*  Set *this* to an orthogonal vector of the same magnitude.         */
        this.x = -this.y;
        this.y = x;
    }
    /*  End of Orthogonalize.                                                 */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthonormalize                                                    *
     *  Purpose:                                                              *
     *      Computes a vector orthogonal to *this* of unit magnitude.         *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Normalize (-this.y, this.x). This follows the right-hand rule.    *
     **************************************************************************/
    void Orthonormalize()
    {
        /*  Use the Orthogonalize and Normalize methods to complete the task. */
        this.Orthogonalize();
        this.Normalize();
    }
    /*  End of Orthonormalize.                                                */

    /*  Alias for the Orthonormalize function.                                */
    void UnitOrthogonalize() = Orthonormalize;

    /**************************************************************************
     *  Method:                                                               *
     *      AsPair                                                            *
     *  Purpose:                                                              *
     *      Converts a Vec2 object into a pair (asymptote primitive).         *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      P (pair):                                                         *
     *          The ordered pair (this.x, this.y).                            *
     *  Method:                                                               *
     *      Convert *this* into a tuple and return.                           *
     **************************************************************************/
    pair AsPair()
    {
        return (this.x, this.y);
    }
    /*  End of AsPair.                                                        */

    /**************************************************************************
     *  Method:                                                               *
     *      AsTriple                                                          *
     *  Purpose:                                                              *
     *      Converts a Vec2 object into a triple (asymptote primitive).       *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      P (triple):                                                       *
     *          The ordered triple (this.x, this.y, 0.0).                     *
     *  Method:                                                               *
     *      Convert *this* into a tuple and return.                           *
     **************************************************************************/
    triple AsTriple()
    {
        return (this.x, this.y, 0.0);
    }
    /*  End of AsTriple.                                                      */

    /**************************************************************************
     *  Method:                                                               *
     *      LineTo                                                            *
     *  Purpose:                                                              *
     *      Creates a guide for a line from *this* to another vector.         *
     *  Arguments:                                                            *
     *      v (Vec2):                                                         *
     *          Another vector, the end point of the line starting at *this*. *
     *  Output:                                                               *
     *      g (guide):                                                        *
     *          The line from *this* to v.                                    *
     **************************************************************************/
    guide LineTo(Vec2 v)
    {
        /*  Convert the vectors to pairs and use asymptote primitives.        */
        guide g = this.AsPair() -- v.AsPair();
        return g;
    }
    /*  End of LineTo.                                                        */
}

/******************************************************************************
 *  Function:                                                                 *
 *      FromRect                                                              *
 *  Purpose:                                                                  *
 *      Creates a vector from Cartesian, or rectangular, coordinates.         *
 *  Arguments:                                                                *
 *      x (real):                                                             *
 *          The x component of the vector.                                    *
 *      y (real):                                                             *
 *          The y component of the vector.                                    *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          The vector (x, y) in the plane.                                   *
 ******************************************************************************/
Vec2 FromRect(real x, real y)
{
    Vec2 v = new Vec2;
    v.x = x;
    v.y = y;
    return v;
}
/*  End of FromRect.                                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      FromPolar                                                             *
 *  Purpose:                                                                  *
 *      Creates a vector from polar coordinates.                              *
 *  Arguments:                                                                *
 *      r (real):                                                             *
 *          The radial component of the vector.                               *
 *      theta (real):                                                         *
 *          The polar angle of the vector.                                    *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          The point r * e^{i theta} in the plane.                           *
 ******************************************************************************/
Vec2 FromPolar(real r, real theta)
{
    Vec2 v = new Vec2;
    v.x = r * cos(theta);
    v.y = r * sin(theta);
    return v;
}
/*  End of FromPolar.                                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      UnitVectorFromAngle                                                   *
 *  Purpose:                                                                  *
 *      Creates a unit vector from a given polar angle.                       *
 *  Arguments:                                                                *
 *      theta (real):                                                         *
 *          The polar angle of the vector.                                    *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          The point e^{i theta} in the plane.                               *
 ******************************************************************************/
Vec2 UnitVectorFromAngle(real theta)
{
    Vec2 v = new Vec2;
    v.x = cos(theta);
    v.y = sin(theta);
    return v;
}
/*  End of UnitVectorFromAngle.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      FromPair                                                              *
 *  Purpose:                                                                  *
 *      Creates a vector from a pair (native asymptote type).                 *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the plane.                                             *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          The point converted to a Vec2 object.                             *
 ******************************************************************************/
Vec2 FromPair(pair P)
{
    Vec2 v = new Vec2;
    v.x = P.x;
    v.y = P.y;
    return v;
}
/*  End of FromPair.                                                          */

/******************************************************************************
 *  Operator:                                                                 *
 *      init                                                                  *
 *  Purpose:                                                                  *
 *      Constructor for Vec2 objects.                                         *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          An initialized vector.                                            *
 ******************************************************************************/
Vec2 operator init()
{
    /*  The default constructor sets the output to the origin. Use this.      */
    return Vec2();
}
/*  End of init.                                                              */

/******************************************************************************
 *  Operator:                                                                 *
 *      +                                                                     *
 *  Purpose:                                                                  *
 *      Performs vector addition.                                             *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      u (Vec2):                                                             *
 *          Another vector in the plane.                                      *
 *  Output:                                                                   *
 *      sum (Vec2):                                                           *
 *          The vector sum of v and u.                                        *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is:                 *
 *                                                                            *
 *          v + u = (vx, vy) + (ux, uy)                                       *
 *                = (vx + ux, vy + uy)                                        *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator + (Vec2 v, Vec2 u)
{
    return Vec2(v.x + u.x, v.y + u.y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      -                                                                     *
 *  Purpose:                                                                  *
 *      Performs vector subtraction.                                          *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      u (Vec2):                                                             *
 *          Another vector in the plane.                                      *
 *  Output:                                                                   *
 *      diff (Vec2):                                                          *
 *          The vector difference of v and u.                                 *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is:              *
 *                                                                            *
 *          v - u = (vx, vy) - (ux, uy)                                       *
 *                = (vx - ux, vy - uy)                                        *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator - (Vec2 v, Vec2 u)
{
    return Vec2(v.x - u.x, v.y - u.y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication with the scalar on the left.           *
 *  Arguments:                                                                *
 *      r (real):                                                             *
 *          A real number, the scalar multiplier.                             *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *  Output:                                                                   *
 *      rv (Vec2):                                                            *
 *          The scalar product of r and v.                                    *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is:           *
 *                                                                            *
 *          r*v = r*(vx, vy)                                                  *
 *              = (r*vx, r*vy)                                                *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator * (real r, Vec2 v)
{
    return Vec2(r*v.x, r*v.y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication with the scalar on the right.          *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      r (real):                                                             *
 *          A real number, the scalar multiplier.                             *
 *  Output:                                                                   *
 *      rv (Vec2):                                                            *
 *          The scalar product of r and v.                                    *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is:           *
 *                                                                            *
 *          v*r = (vx, vy)*r                                                  *
 *              = (vx*r, vy*r)                                                *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator * (Vec2 v, real r)
{
    return Vec2(v.x*r, v.y*r);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      /                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar division.                                             *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      r (real):                                                             *
 *          A real number, the scalar divider.                                *
 *  Output:                                                                   *
 *      v_by_r (Vec2):                                                        *
 *          The scalar product of 1/r and v.                                  *
 *  Method:                                                                   *
 *      Scalar division is performed component-wise. That is:                 *
 *                                                                            *
 *          v/r = (vx, vy)/r                                                  *
 *              = (vx/r, vy/r)                                                *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator / (Vec2 v, real r)
{
    /*  Variable for 1 / r. We need to check if this is safe to compute.      */
    real rcpr;

    /*  If the input is zero the result is undefined. Return a NaN vector.    */
    if (r == 0.0)
        return Vec2(nan, nan);

    /*  Otherwise compute 1 / r and perform scalar multiplication with this.  */
    rcpr = 1.0 / r;
    return Vec2(rcpr*v.x, rcpr*v.y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs component-wise multiplication.                               *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      u (Vec2):                                                             *
 *          Another vector in the plane.                                      *
 *  Output:                                                                   *
 *      vu (Vec2):                                                            *
 *          The component-wise product of v and u.                            *
 *  Method:                                                                   *
 *      Component-wise multiplication is performed component-wise. That is:   *
 *                                                                            *
 *          v*u = (vx, vy)*(ux, uy)                                           *
 *              = (vx*ux, vy*uy)                                              *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator * (Vec2 v, Vec2 u)
{
    return Vec2(v.x*u.x, v.y*u.y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      /                                                                     *
 *  Purpose:                                                                  *
 *      Performs component-wise division.                                     *
 *  Arguments:                                                                *
 *      v (Vec2):                                                             *
 *          A vector in the plane.                                            *
 *      u (Vec2):                                                             *
 *          Another vector in the plane.                                      *
 *  Output:                                                                   *
 *      v_by_u (Vec2):                                                        *
 *          The component-wise division of v and u.                           *
 *  Method:                                                                   *
 *      Component-wise division is performed component-wise. That is:         *
 *                                                                            *
 *          v/u = (vx, vy)/(ux, uy)                                           *
 *              = (vx/ux, vy/uy)                                              *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Vec2 operator / (Vec2 v, Vec2 u)
{
    /*  Avoid division by zero. We'll store a NaN in the output component if  *
     *  the corresponding component for u is zero.                            */
    real x, y;

    /*  Check if we can divide. Return NaN if not.                            */
    if (u.x == 0.0)
        x = nan;
    else
        x = v.x / u.x;

    /*  Similar check for the y-component.                                    */
    if (u.y == 0.0)
        y = nan;
    else
        y = v.y / u.y;

    return Vec2(x, y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      cast                                                                  *
 *  Purpose:                                                                  *
 *      Converts a pair to a Vec2 object.                                     *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the plane.                                             *
 *  Output:                                                                   *
 *      v (Vec2):                                                             *
 *          The same point as a vector.                                       *
 ******************************************************************************/
Vec2 operator cast(pair P)
{
    return FromPair(P);
}
/*  End of cast.                                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      PolygonThroughPoints                                                  *
 *  Purpose:                                                                  *
 *      Creates a piece-wise linear curve through points in the plane.        *
 *  Arguments:                                                                *
 *      v (Vec2[]):                                                           *
 *          An (ordered) array of points.                                     *
 *  Keywords:                                                                 *
 *      closed (bool):                                                        *
 *          Boolean determining if the returned polygon is closed or not.     *
 *  Outputs:                                                                  *
 *      g (guide):                                                            *
 *          A polygonal curve through the points of v.                        *
 ******************************************************************************/
guide PolygonThroughPoints(Vec2[] v, bool closed = false)
{
    /*  Variable for the polygonal curve. We'll loop through v in a bit.      */
    guide g;

    /*  Dummy variable for indexing over the points in v.                     */
    int n;

    /*  There needs to be at least 2 points to create a curve.                */
    assert(v.length > 1);

    /*  Initialize the curve to start at the zeroth point.                    */
    g = v[0].AsPair();

    /*  Loop through the remaining points of the curve and draw lines.        */
    for (n = 1; n < v.length; ++n)
        g = g -- v[n].AsPair();

    /*  If the closed Boolean is set, cycle back to the start of the path.    */
    if (closed)
        g = g -- cycle;

    return g;
}
/*  End of PolygonThroughPoints.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      ClosedPolygonThroughPoints                                            *
 *  Purpose:                                                                  *
 *      Creates a closed piece-wise linear curve through points in the plane. *
 *  Arguments:                                                                *
 *      v (Vec2[]):                                                           *
 *          An (ordered) array of points.                                     *
 *  Outputs:                                                                  *
 *      g (guide):                                                            *
 *          A closed polygonal curve through the points of v.                 *
 ******************************************************************************/
guide ClosedPolygonThroughPoints(Vec2[] v)
{
    return PolygonThroughPoints(v, closed = true);
}
/*  End of ClosedPolygonThroughPoints.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      CurveThroughPoints                                                    *
 *  Purpose:                                                                  *
 *      Creates a smooth curve through points in the plane.                   *
 *  Arguments:                                                                *
 *      v (Vec2[]):                                                           *
 *          An (ordered) array of points.                                     *
 *  Keywords:                                                                 *
 *      closed (bool):                                                        *
 *          Boolean determining if the returned curve is closed or not.       *
 *  Outputs:                                                                  *
 *      g (guide):                                                            *
 *          A smooth curve through the points of v.                           *
 ******************************************************************************/
guide CurveThroughPoints(Vec2[] v, bool closed = false)
{
    /*  Variable for the output smooth curve.                                 */
    guide g;

    /*  Dummy variable for indexing over the points of v.                     */
    int n;

    /*  We need at least two points to create a curve.                        */
    assert(v.length > 1);

    /*  Initialize the curve using the first two points. If there are only    *
     *  two points, the output curve will be the straight line between these. */
    g = v[0].AsPair() .. v[1].AsPair();

    /*  Loop over the remaining points of v and add them to the curve.        */
    for (n = 2; n < v.length; ++n)
        g = g .. v[n].AsPair();

    /*  If the closed Boolean is set, cycle back to the start of the path.    */
    if (closed)
        g = g .. cycle;

    return g;
}
/*  End of CurveThroughPoints.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      ClosedCurveThroughPoints                                              *
 *  Purpose:                                                                  *
 *      Creates a closed smooth curve through points in the plane.            *
 *  Arguments:                                                                *
 *      v (Vec2[]):                                                           *
 *          An (ordered) array of points.                                     *
 *  Outputs:                                                                  *
 *      g (guide):                                                            *
 *          A closed smooth curve through the points of v.                    *
 ******************************************************************************/
guide ClosedCurveThroughPoints(Vec2[] v)
{
    return CurveThroughPoints(v, closed = true);
}
/*  End of ClosedCurveThroughPoints.                                          */

/*  Useful directions saved as constants.                                     */
Vec2 NorthEast = UnitVectorFromAngle(0.25 * pi);
Vec2 NorthWest = UnitVectorFromAngle(0.75 * pi);
Vec2 SouthWest = UnitVectorFromAngle(1.25 * pi);
Vec2 SouthEast = UnitVectorFromAngle(1.75 * pi);
Vec2 East = Vec2(1.0, 0.0);
Vec2 North = Vec2(0.0, 1.0);
Vec2 West = Vec2(-1.0, 0.0);
Vec2 South = Vec2(0.0, -1.0);

/*  Value used to scale the axes in the ProjectXYZ function below.            */
private real shear_factor = -0.4;

/******************************************************************************
 *  Function:                                                                 *
 *      ResetShear                                                            *
 *  Purpose:                                                                  *
 *      Resets the shear factor to a user defined value.                      *
 *  Arguments:                                                                *
 *      shear (real):                                                         *
 *          The new shear factor.                                             *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
void ResetShear(real shear)
{
    shear_factor = shear;
}
/*  End of ResetShear.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      ProjectXYZ                                                            *
 *  Purpose:                                                                  *
 *      Mimics points in 3D using a 2D canvas by projecting and shearing.     *
 *  Arguments:                                                                *
 *      x (real):                                                             *
 *          The x component of the point.                                     *
 *      y (real):                                                             *
 *          The y component of the point.                                     *
 *      z (real):                                                             *
 *          The z component of the point.                                     *
 *  Outputs:                                                                  *
 *      P (Vec2):                                                             *
 *          The point (x, y, z) representing as a 2D point by projecting.     *
 ******************************************************************************/
Vec2 ProjectXYZ(real x, real y, real z)
{
    /*  The x component is computed from the y and z axes by shearing.        */
    Vec2 X = Vec2(shear_factor*x, shear_factor*x);

    /*  The y and z axes are unchanged by the projection.                     */
    Vec2 Y = Vec2(y, 0.0);
    Vec2 Z = Vec2(0.0, z);

    /*  The final result (the projection) is the sum of the three terms.      */
    return X + Y + Z;
}
/*  End of ProjectXYZ.                                                        */

void DrawDot(Vec2 v, real r, pen fillpen = black, pen drawpen = black)
{
    filldraw(circle(v.AsPair(), r), fillpen = fillpen, drawpen = drawpen);
}

void AddLabel(picture pic = currentpicture, Label L, Vec2 v,
              align a = NoAlign, pen p = currentpen, filltype f = NoFill)
{
    label(pic = pic, L, v.AsPair(), align = a, p = p, filltype = f);
}
