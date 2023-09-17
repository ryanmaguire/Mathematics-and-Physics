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
 *                                  complex                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a complex number struct.                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 17, 2023                                            *
 ******************************************************************************/

/*  Struct for points in the complex plane.                                   */
struct Complex {

    /*  A point in the plane is represented by real and imaginary parts.      */
    real re, im;

    /*  Constructor from two real numbers, the x and y coordinates.           */
    void operator init(real x, real y)
    {
        this.re = x;
        this.im = y;
    }

    /*  Initializer with no inputs. Set *this* to the origin.                 */
    void operator init()
    {
        this.re = 0.0;
        this.im = 0.0;
    }

    /**************************************************************************
     *  Method:                                                               *
     *      AbsSq                                                             *
     *  Purpose:                                                              *
     *      Computes the square of the modulus of the complex number.         *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      mod_sq (real):                                                    *
     *          The square of the distance from the origin to *this*.         *
     *  Method:                                                               *
     *      Use the Pythagorean formula.                                      *
     *                                                                        *
     *          ||P||^2 = ||x + iy||^2                                        *
     *                  = x^2 + y^2                                           *
     *                                                                        *
     *      Compute this and return.                                          *
     **************************************************************************/
    real AbsSq()
    {
        return this.re*this.re + this.im*this.im;
    }
    /*  End of AbsSq.                                                         */

    /**************************************************************************
     *  Method:                                                               *
     *      Abs                                                               *
     *  Purpose:                                                              *
     *      Compute the modulus of the complex number.                        *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      mod (real):                                                       *
     *          The distance from the origin to *this*.                       *
     *  Method:                                                               *
     *      Use the Pythagorean formula.                                      *
     *                                                                        *
     *          ||P|| = ||x + iy||                                            *
     *                = sqrt(x^2 + y^2)                                       *
     *                                                                        *
     *      Compute this and return.                                          *
     **************************************************************************/
    real Abs()
    {
        return sqrt(this.AbsSq());
    }
    /*  End of Abs.                                                           */

    /**************************************************************************
     *  Method:                                                               *
     *      Argument                                                          *
     *  Purpose:                                                              *
     *      Computes the angle the point makes with the positive real axis.   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      theta (real):                                                     *
     *          The angle *this* makes with the positive real axis.           *
     *  Method:                                                               *
     *      The angle can be computed with the atan2 function. Given x + iy   *
     *      in the complex plane, return the value atan2(y, x).               *
     **************************************************************************/
    real Argument()
    {
        return atan2(this.im, this.re);
    }
    /*  End of Argument.                                                      */

    /**************************************************************************
     *  Method:                                                               *
     *      Conjugate                                                         *
     *  Purpose:                                                              *
     *      Computes the complex conjugate of *this*.                         *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      z_bar (Complex):                                                  *
     *          The conjugate of *this*.                                      *
     *  Method:                                                               *
     *      Negate this.im.                                                   *
     **************************************************************************/
    Complex Conjugate()
    {
        return Complex(this.re, -this.im);
    }

    /**************************************************************************
     *  Method:                                                               *
     *      Inverse                                                           *
     *  Purpose:                                                              *
     *      Computes the inverse of *this*.                                   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      z_inv (Complex):                                                  *
     *          The inverse of *this* under complex multiplication.           *
     *  Method:                                                               *
     *      Compute conj(z) / |z|^2, conj being the complex conjugate.        *
     **************************************************************************/
    Complex Inverse()
    {
        real abs_sq = this.AbsSq();
        real factor;

        if (abs_sq == 0.0)
            return Complex(nan, nan);

        factor = 1.0 / abs_sq;

        return Complex(this.re * factor, -this.im * factor);
    }

    /**************************************************************************
     *  Method:                                                               *
     *      Invert                                                            *
     *  Purpose:                                                              *
     *      Computes the inverse of *this*.                                   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void):                                                      *
     *  Method:                                                               *
     *      Compute conj(z) / |z|^2, conj being the complex conjugate.        *
     **************************************************************************/
    void Invert()
    {
        real abs_sq = this.AbsSq();
        real factor;

        if (abs_sq == 0.0)
        {
            this.re = nan;
            this.im = nan;
        }

        else
        {
            factor = 1.0 / abs_sq;

            this.re *= factor;
            this.im *= -factor;
        }
    }

    /**************************************************************************
     *  Method:                                                               *
     *      Dot                                                               *
     *  Purpose:                                                              *
     *      Computes the Euclidean dot product of *this* with another point.  *
     *  Arguments:                                                            *
     *      w (Complex):                                                      *
     *          A point in the plane.                                         *
     *  Output:                                                               *
     *      dot_prod (real):                                                  *
     *          The dot product of *this* and w, viewed as 2D vectors.        *
     *  Method:                                                               *
     *      Compute the sum of the products of the components.                *
     **************************************************************************/
    real Dot(Complex w)
    {
        return this.re*w.re + this.im*w.im;
    }
    /*  End of Dot.                                                           */

    /**************************************************************************
     *  Method:                                                               *
     *      AsUnitNormal                                                      *
     *  Purpose:                                                              *
     *      Normalizes a non-zero complex number to unit magnitude.           *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      w (Complex):                                                      *
     *          The unit complex number pointing in the direction of *this*.  *
     *  Method:                                                               *
     *      Scale *this* by the reciprocal of its norm.                       *
     **************************************************************************/
    Complex AsUnitNormal()
    {
        /*  Avoid division by zero, and a possibly redundant square root      *
         *  call, by computing |*this*|^2 and checking if it is zero.         */
        real abs_sq = this.AbsSq();
        real factor;

        /*  Division by zero is undefined, return a NaN complex number.       */
        if (abs_sq == 0.0)
            return Complex(nan, nan);

        /*  Otherwise compute the scale factor 1 / |*this*| and normalize.    */
        factor = 1.0 / sqrt(abs_sq);
        return Complex(factor*this.re, factor*this.im);
    }
    /*  End of AsUnitNormal.                                                  */

    /**************************************************************************
     *  Method:                                                               *
     *      Normalize                                                         *
     *  Purpose:                                                              *
     *      Normalizes a non-zero complex number to unit magnitude.           *
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
         *  call, by computing |*this*|^2 and checking if it is zero.         */
        real abs_sq = this.AbsSq();
        real factor;

        /*  Division by zero is undefined, set components to NaN.             */
        if (abs_sq == 0.0)
        {
            this.re = nan;
            this.im = nan;
        }

        /*  Otherwise compute the scale factor 1 / |*this*| and normalize.    */
        factor = 1.0 / sqrt(abs_sq);
        this.re *= factor;
        this.im *= factor;
    }
    /*  End of Normalize.                                                     */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthogonal                                                        *
     *  Purpose:                                                              *
     *      Computes a complex number orthogonal to *this* of equal magnitude.*
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      ortho (Complex):                                                  *
     *          A complex number that is orthogonal to *this* with the        *
     *          same magnitude.                                               *
     *  Method:                                                               *
     *      Return (-this.im, this.re). This follows the right-hand rule.     *
     **************************************************************************/
    Complex Orthogonal()
    {
        return Complex(-this.re, this.im);
    }
    /*  End of Orthogonal.                                                    */

    /*  Alias for the Orthogonal function.                                    */
    Complex AsOrthogonal() = Orthogonal;

    /**************************************************************************
     *  Method:                                                               *
     *      AsUnitOrthogonal                                                  *
     *  Purpose:                                                              *
     *      Computes a complex number orthogonal to *this* of unit magnitude. *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      unit_ortho (Complex):                                             *
     *          A complex number that is orthogonal to *this* and unit length.*
     *  Method:                                                               *
     *      Normalize (-this.re, this.im). This follows the right-hand rule.  *
     **************************************************************************/
    Complex AsUnitOrthogonal()
    {
        return this.Orthogonal().AsUnitNormal();
    }
    /*  End of AsUnitOrthogonal.                                              */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthogonalize                                                     *
     *  Purpose:                                                              *
     *      Computes a complex number orthogonal to *this* with equal modulus.*
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Return (-this.im, this.re). This follows the right-hand rule.     *
     **************************************************************************/
    void Orthogonalize()
    {
        /*  Avoid overwriting the data in an unrecoverable way. Save this.re. */
        real x = this.re;

        /*  Set *this* to an orthogonal complex number of the same magnitude. */
        this.re = -this.im;
        this.im = x;
    }
    /*  End of Orthogonalize.                                                 */

    /**************************************************************************
     *  Method:                                                               *
     *      Orthonormalize                                                    *
     *  Purpose:                                                              *
     *      Computes a complex number orthogonal to *this* of unit modulus.   *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Normalize (-this.im, this.re). This follows the right-hand rule.  *
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
     *      Converts a Complex object into a pair (asymptote primitive).      *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      P (pair):                                                         *
     *          The ordered pair (this.re, this.im).                          *
     *  Method:                                                               *
     *      Convert *this* into a tuple and return.                           *
     **************************************************************************/
    pair AsPair()
    {
        return (this.re, this.im);
    }
    /*  End of AsPair.                                                        */

    /**************************************************************************
     *  Method:                                                               *
     *      AsTriple                                                          *
     *  Purpose:                                                              *
     *      Converts a Complex object into a triple (asymptote primitive).    *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Output:                                                               *
     *      P (triple):                                                       *
     *          The ordered triple (this.re, this.im, 0.0).                   *
     *  Method:                                                               *
     *      Convert *this* into a tuple and return.                           *
     **************************************************************************/
    triple AsTriple()
    {
        return (this.re, this.im, 0.0);
    }
    /*  End of AsTriple.                                                      */
}

/*  Alternative constructor from two real numbers.                            */
Complex FromRect(real x, real y)
{
    return Complex(x, y);
}

/*  Constructor from the polar representation of the point.                   */
Complex FromPolar(real r, real theta)
{
    return Complex(r * cos(theta), r * sin(theta));
}

/*  Convert a pair (native asymptote data type) into a Complex object.        */
Complex FromPair(pair P)
{
    return Complex(P.x, P.y);
}

/*  Default initializer for the Complex struct. Sets the output to the origin.*/
Complex operator init()
{
    /*  The default constructor sets the output to the origin. Use this.      */
    return Complex();
}

/******************************************************************************
 *  Operator:                                                                 *
 *      +                                                                     *
 *  Purpose:                                                                  *
 *      Performs complex addition.                                            *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      w (Complex):                                                          *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      sum (Complex):                                                        *
 *          The complex sum of z and w.                                       *
 *  Method:                                                                   *
 *      Complex addition is performed component-wise. That is:                *
 *                                                                            *
 *          z + w = (zx + izy) + (wx + iwy)                                   *
 *                = (zx + wx) + i (zy + wy)                                   *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator + (Complex z, Complex w)
{
    return Complex(z.re + w.re, z.im + w.im);
}

Complex operator + (Complex z, real x)
{
    return Complex(z.re + x, z.im);
}

Complex operator + (real x, Complex z)
{
    return Complex(x + z.re, z.im);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      -                                                                     *
 *  Purpose:                                                                  *
 *      Performs complex subtraction.                                         *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      w (Complex):                                                          *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      diff (Complex):                                                       *
 *          The complex difference of z and w.                                *
 *  Method:                                                                   *
 *      Complex addition is performed component-wise. That is:                *
 *                                                                            *
 *          z - w = (zx + izy) - (wx + iwy)                                   *
 *                = (zx - wx) + i (zy - wy)                                   *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator - (Complex z, Complex w)
{
    return Complex(z.re - w.re, z.im - w.im);
}

Complex operator - (Complex z, real x)
{
    return Complex(z.re - x, z.im);
}

Complex operator - (real x, Complex z)
{
    return Complex(x - z.re, -z.im);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication with the scalar on the left.           *
 *  Arguments:                                                                *
 *      a (real):                                                             *
 *          A real number, the scalar multiplier.                             *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      az (Complex):                                                         *
 *          The scalar product of a and z.                                    *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is:           *
 *                                                                            *
 *          a*z = a*(x + iy)                                                  *
 *              = ax + i ay                                                   *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator * (real a, Complex z)
{
    return Complex(a*z.re, a*z.im);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication with the scalar on the right.          *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      a (real):                                                             *
 *          A real number, the scalar multiplier.                             *
 *  Output:                                                                   *
 *      az (Complex):                                                         *
 *          The scalar product of a and z.                                    *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is:           *
 *                                                                            *
 *          a*z = a*(x + iy)                                                  *
 *              = ax + i ay                                                   *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator * (Complex z, real a)
{
    return Complex(a*z.re, a*z.im);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      *                                                                     *
 *  Purpose:                                                                  *
 *      Performs complex multiplication.                                      *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      w (Complex):                                                          *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      zw (Complex):                                                         *
 *          The product of z and w.                                           *
 *  Method:                                                                   *
 *      Multiplication is performed using the distributive law and i^2 = -1.  *
 *                                                                            *
 *          z*w = (zx + i zy) * (wx + i wy)                                   *
 *              = (zx * wx - zy * wy) + i (zx * wy + zy * wx)                 *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator * (Complex z, Complex w)
{
    real x = z.re*w.re - z.im*w.im;
    real y = z.re*w.im + z.im*w.re;
    return Complex(x, y);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      /                                                                     *
 *  Purpose:                                                                  *
 *      Performs complex division.                                            *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      w (Complex):                                                          *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      z_by_w (Complex):                                                     *
 *          The complex division of z and w.                                  *
 *  Method:                                                                   *
 *      Compute z * (1 / w) = z * conj(w) / |w|^2.                            *
 ******************************************************************************/
Complex operator / (Complex z, Complex w)
{
    real w_abs_sq = w.AbsSq();
    real factor, re, im;

    if (w_abs_sq == 0.0)
        return Complex(nan, nan);

    factor = 1.0 / w_abs_sq;

    re = factor * (z.re*w.re + z.im*w.im);
    im = factor * (-z.re*w.im + z.im*w.re);

    return Complex(re, im);
}

/******************************************************************************
 *  Operator:                                                                 *
 *      /                                                                     *
 *  Purpose:                                                                  *
 *      Performs scalar division.                                             *
 *  Arguments:                                                                *
 *      z (Complex):                                                          *
 *          A complex number.                                                 *
 *      a (real):                                                             *
 *          A real number, the scalar divider.                                *
 *  Output:                                                                   *
 *      z_by_a (Complex):                                                     *
 *          The scalar product of 1/a and z.                                  *
 *  Method:                                                                   *
 *      Scalar division is performed component-wise. That is:                 *
 *                                                                            *
 *          z/a = (x + iy)/a                                                  *
 *              = (x/a) + i (y/a)                                             *
 *                                                                            *
 *      Compute this and return.                                              *
 ******************************************************************************/
Complex operator / (Complex z, real a)
{
    /*  Variable for 1 / r. We need to check if this is safe to compute.      */
    real rcpr;

    /*  If the input is zero the result is undefined. Return complex NaN.     */
    if (a == 0.0)
        return Complex(nan, nan);

    /*  Otherwise compute 1 / r and perform scalar multiplication with this.  */
    rcpr = 1.0 / a;
    return Complex(rcpr * z.re, rcpr * z.im);
}

Complex operator / (real x, Complex z)
{
    real z_abs_sq = z.AbsSq();
    real factor;

    if (z_abs_sq == 0.0)
        return Complex(nan, nan);

    factor = x / z_abs_sq;

    return Complex(factor * z.re, -factor * z.im);
}
