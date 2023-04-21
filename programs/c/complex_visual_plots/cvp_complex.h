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
 *  Purpose:                                                                  *
 *      Provide a double-precision complex number struct without C99 features.*
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/21                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_COMPLEX_H
#define CVP_COMPLEX_H

/*  CVP_INLINE macro is defined here.                                         */
#include "cvp_inline.h"

/*  sqrt and atan2 functions found here.                                      */
#include <math.h>

/*  Basic struct for working with complex numbers.                            */
struct cvp_complex {

    /*  A complex number is determined by its real and imaginary parts.       */
    double real, imag;
};

/*  Useful constants that are commonly used.                                  */
static const struct cvp_complex cvp_complex_zero = {0.0, 0.0};
static const struct cvp_complex cvp_complex_one = {1.0, 0.0};
static const struct cvp_complex cvp_complex_minus_one = {-1.0, 0.0};
static const struct cvp_complex cvp_complex_i = {0.0, 1.0};

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_create                                                    *
 *  Purpose:                                                                  *
 *      Creates a complex number from two real numbers.                       *
 *  Arguments:                                                                *
 *      real (double):                                                        *
 *          The real part of the complex number.                              *
 *      imag (double):                                                        *
 *          The imaginary part of the complex number.                         *
 *  Outputs:                                                                  *
 *      z (struct cvp_complex):                                               *
 *          The complex number z = real + i*imag = (real, imag).              *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_create(double real, double imag)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex z;

    /*  Set the real and imaginary parts and return.                          */
    z.real = real;
    z.imag = imag;
    return z;
}
/*  End of cvp_complex_create.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_conjugate                                                 *
 *  Purpose:                                                                  *
 *      Computes the complex conjugate of the input.                          *
 *  Arguments:                                                                *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      z_bar (struct cvp_complex):                                           *
 *          The complex conjugate of z.                                       *
 *  Method:                                                                   *
 *      Copy the real part and negate the imaginary part.                     *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_conjugate(const struct cvp_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex z_bar;

    /*  The conjugate simply negates the imaginary part.                      */
    z_bar.real = z->real;
    z_bar.imag = -z->imag;
    return z_bar;
}
/*  End of cvp_complex_conjugate.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_conjugateself                                             *
 *  Purpose:                                                                  *
 *      Computes the conjugate of z and stores it in the input.               *
 *  Arguments:                                                                *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Negate the imaginary component.                                       *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_conjugateself(struct cvp_complex *z)
{
    /*  The complex conjugate is computed by negating the imaginary part.     */
    z->imag = -z->imag;
}
/*  End of cvp_complex_conjugateself.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_add                                                       *
 *  Purpose:                                                                  *
 *      Adds two complex numbers.                                             *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      sum (struct cvp_complex):                                             *
 *          The sum of z0 and z1.                                             *
 *  Method:                                                                   *
 *      Complex addition is defined the same way vector addition is performed *
 *      in the plane. Given z0 = x0 + i*y0 and z1 = x1 + i*y1 we have:        *
 *                                                                            *
 *            sum = z0 + z1                                                   *
 *                = (x0 + i*y0) + (x1 + i*y1)                                 *
 *                = (x0 + x1) + i*(y0 + y1)                                   *
 *                                                                            *
 *      That is, complex addition is performed component-wise.                *
 *  Notes:                                                                    *
 *      With three dimensional vectors it is almost always faster to pass     *
 *      vectors to a function by address (i.e. using pointers) than           *
 *      passing the entire struct itself. With two dimensional vectors, and   *
 *      with complex numbers, the speed differences may be minimal since the  *
 *      struct is small enough already (it's just two doubles). Nevertheless  *
 *      this function takes pointers to complex numbers, instead of the       *
 *      complex numbers themselves.                                           *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_add(const struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex sum;

    /*  Complex addition is done component-wise.                              */
    sum.real = z0->real + z1->real;
    sum.imag = z0->imag + z1->imag;
    return sum;
}
/*  End of cvp_complex_add.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_addto                                                     *
 *  Purpose:                                                                  *
 *      Adds two complex numbers and stores the result in the first variable. *
 *  Arguments:                                                                *
 *      z0 (struct cvp_complex *):                                            *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex addition as before and store the result in z0.        *
 *  Notes:                                                                    *
 *      This gives the complex struct a "+=" operator.                        *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_addto(struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Complex addition is done component-wise.                              */
    z0->real += z1->real;
    z0->imag += z1->imag;
}
/*  End of cvp_complex_addto.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_add_real                                                  *
 *  Purpose:                                                                  *
 *      Adds a real number to a complex one.                                  *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Output:                                                                   *
 *      sum (struct cvp_complex):                                             *
 *          The sum of z and a.                                               *
 *  Method:                                                                   *
 *      Add the double to the real part of z and return.                      *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_add_real(double a, const struct cvp_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex sum;

    /*  Add the real number to the real part of z and copy the imaginary part.*/
    sum.real = z->real + a;
    sum.imag = z->imag;
    return sum;
}
/*  End of cvp_complex_add_real.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_addto_real                                                *
 *  Purpose:                                                                  *
 *      Adds a real number to a complex one.                                  *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Add the double to the real part of z and return.                      *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_addto_real(double a, struct cvp_complex *z)
{
    /*  Add the real number to the real part of z and return.                 */
    z->real += a;
}
/*  End of cvp_complex_addto_real.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_subtract                                                  *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers.                                        *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      diff (struct cvp_complex):                                            *
 *          The difference of z0 and z1.                                      *
 *  Method:                                                                   *
 *      Complex subtraction is defined the same way vector subtraction is     *
 *      performed in the Euclidean plane. Given z0 = x0 + i*y0 and            *
 *      z1 = x1 + i*y1 we have:                                               *
 *                                                                            *
 *            diff = z0 - z1                                                  *
 *                 = (x0 + i*y0) - (x1 + i*y1)                                *
 *                 = (x0 - x1) + i*(y0 - y1)                                  *
 *                                                                            *
 *      That is, complex subtraction is performed component-wise.             *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_subtract(const struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex diff;

    /*  Complex subtraction is done component-wise.                           */
    diff.real = z0->real - z1->real;
    diff.imag = z0->imag - z1->imag;
    return diff;
}
/*  End of cvp_complex_subtract.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_subtractfrom                                              *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers and stores the result in the first      *
 *      variable.                                                             *
 *  Arguments:                                                                *
 *      z0 (struct cvp_complex *):                                            *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex subtraction as before and store the result in z0.     *
 *  Notes:                                                                    *
 *      This gives the complex struct a "-=" operator.                        *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_subtractfrom(struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Complex subtraction is done component-wise.                           */
    z0->real -= z1->real;
    z0->imag -= z1->imag;
}
/*  End of cvp_complex_subtractfrom.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_subtract_real                                             *
 *  Purpose:                                                                  *
 *      Subtracts a complex number from a real one.                           *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Output:                                                                   *
 *      diff (struct cvp_complex):                                            *
 *          The difference of a and z, a - z.                                 *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_subtract_real(double a, const struct cvp_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex diff;

    /*  Subtract the real part of z from a and negate the imaginary part.     */
    diff.real = a - z->real;
    diff.imag = -z->imag;
    return diff;
}
/*  End of cvp_complex_subtract_real.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_subtractfrom_real                                         *
 *  Purpose:                                                                  *
 *      Subtracts a complex number from a real one.                           *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_subtractfrom_real(double a, struct cvp_complex *z)
{
    /*  Subtract the real part of z from a and negate the imaginary part.     */
    z->real = a - z->real;
    z->imag = -z->imag;
}
/*  End of cvp_complex_subtractfrom_real.                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_multiply                                                  *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers.                                       *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      prod (struct cvp_complex):                                            *
 *          The product of z0 and z1.                                         *
 *  Method:                                                                   *
 *      Write "i" as a variable such that i^2 = -1 and use the distributive   *
 *      law. Given z0 = x0 + i*y0 and z1 = x1 + i*y1 we have:                 *
 *                                                                            *
 *          prod = z0*z1                                                      *
 *               = (x0 + i*y0)*(x1 + i*y1)                                    *
 *               = x0*x1 + i^2*y0*y1 + i*x0*y1 + i*x1*y0                      *
 *               = (x0*x1 - y0*y1) + i*(x0*y1 + x1*y0)                        *
 *                                                                            *
 *      The components are computed individually and the result is returned.  *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_multiply(const struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex prod;

    /*  Perform the product using the rule i^2 = -1.                          */
    prod.real = z0->real*z1->real - z0->imag*z1->imag;
    prod.imag = z0->real*z1->imag + z0->imag*z1->real;
    return prod;
}
/*  End of cvp_complex_multiply.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_multiplyby                                                *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers and stores the result in the first     *
 *      variable.                                                             *
 *  Arguments:                                                                *
 *      z0 (struct cvp_complex *):                                            *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex multiplication and store the result in z0.            *
 *  Notes:                                                                    *
 *      This function is equivalent to a "*=" operator.                       *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_multiplyby(struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Avoid overwriting the data by copying it to two local variables.      */
    const double real = z0->real;
    const double imag = z0->imag;

    /*  Perform the product using the rule i^2 = -1.                          */
    z0->real = real*z1->real - imag*z1->imag;
    z0->imag = real*z1->imag + imag*z1->real;
}
/*  End of cvp_complex_multiplyby.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_multiply_real                                             *
 *  Purpose:                                                                  *
 *      Multiplies a complex number by a real one.                            *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      prod (struct cvp_complex):                                            *
 *          The product a*z.                                                  *
 *  Method:                                                                   *
 *      Scale the real and imaginary parts of z by a.                         *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_multiply_real(double a, const struct cvp_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex prod;

    /*  Scale the real and imaginary parts of z by a and return.              */
    prod.real = a*z->real;
    prod.imag = a*z->imag;
    return prod;
}
/*  End of cvp_complex_multiply_real.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_multiplyby_real                                           *
 *  Purpose:                                                                  *
 *      Multiplies a complex number by a real one.                            *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Scale the real and imaginary parts of z by a.                         *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_multiplyby_real(double a, struct cvp_complex *z)
{
    /*  Scale the real and imaginary parts of z by a and return.              */
    z->real *= a;
    z->imag *= a;
}
/*  End of cvp_complex_multiplyby_real.                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_divide                                                    *
 *  Purpose:                                                                  *
 *      Divides two complex numbers.                                          *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      quot (struct cvp_complex):                                            *
 *          The quotient of z0 and z1.                                        *
 *  Method:                                                                   *
 *      The inverse of z can be written using the complex conjugate z_bar.    *
 *                                                                            *
 *          z^-1 = z_bar / |z|^2                                              *
 *                                                                            *
 *      To compute z0 / z1 we compute z0 * z1^-1.                             *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_divide(const struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Declare a variable for the quotient.                                  */
    struct cvp_complex quot;

    /*  The quotient z0 / z1 can be written as z0 * (1/z1). Use this.         */
    double denom = 1.0 / (z1->real*z1->real + z1->imag*z1->imag);

    /*  Compute z0 * z1_bar / |z1|^2.                                         */
    quot.real = (z0->real*z1->real + z0->imag*z1->imag)*denom;
    quot.imag = (z0->imag*z1->real - z0->real*z1->imag)*denom;
    return quot;
}
/*  End of cvp_complex_divide.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_divideby                                                  *
 *  Purpose:                                                                  *
 *      Divides two complex numbers and stores the result in the first input. *
 *  Arguments:                                                                *
 *      z0 (struct cvp_complex *):                                            *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      The inverse of z can be written using the complex conjugate z_bar.    *
 *                                                                            *
 *          z^-1 = z_bar / |z|^2                                              *
 *                                                                            *
 *      To compute z0 / z1 we compute z0 * z1^-1.                             *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_divideby(struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Avoid overwriting the data by copying it to two local variables.      */
    const double real = z0->real;
    const double imag = z0->imag;

    /*  The quotient z0 / z1 can be written as z0 * (1/z1). Use this.         */
    double denom = 1.0 / (z1->real*z1->real + z1->imag*z1->imag);

    /*  Compute z0 * z1_bar / |z1|^2.                                         */
    z0->real = (real*z1->real + imag*z1->imag)*denom;
    z0->imag = (imag*z1->real - real*z1->imag)*denom;
}
/*  End of cvp_complex_divideby.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_divide_real                                               *
 *  Purpose:                                                                  *
 *      Divides a real number by a complex one.                               *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      quot (struct cvp_complex):                                            *
 *          The quotient of a and z.                                          *
 *  Method:                                                                   *
 *      The inverse of z can be written using the complex conjugate z_bar.    *
 *                                                                            *
 *          z^-1 = z_bar / |z|^2                                              *
 *                                                                            *
 *      To compute a / z we compute a * z^-1.                                 *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_divide_real(double a, const struct cvp_complex *z)
{
    /*  Declare a variable for the quotient.                                  */
    struct cvp_complex quot;

    /*  The quotient a / z can be written as a * (1/z). Use this.             */
    const double denom = 1.0 / (z->real*z->real + z->imag*z->imag);

    /*  Compute a * z_bar / |z|^2.                                            */
    quot.real = a*z->real*denom;
    quot.imag = -a*z->imag*denom;
    return quot;
}
/*  End of cvp_complex_divide_real.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_divideby_real                                             *
 *  Purpose:                                                                  *
 *      Divides a real number by a complex one.                               *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      The inverse of z can be written using the complex conjugate z_bar.    *
 *                                                                            *
 *          z^-1 = z_bar / |z|^2                                              *
 *                                                                            *
 *      To compute a / z we compute a * z^-1.                                 *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_divideby_real(double a, struct cvp_complex *z)
{
    /*  The quotient a / z can be written as a * (1/z). Use this.             */
    const double denom = 1.0 / (z->real*z->real + z->imag*z->imag);

    /*  Compute a * z_bar / |z|^2.                                            */
    z->real = a*z->real*denom;
    z->imag = -a*z->imag*denom;
}
/*  End of cvp_complex_divideby_real.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_square                                                    *
 *  Purpose:                                                                  *
 *      Computes the square of a complex number.                              *
 *  Arguments:                                                                *
 *      z (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      square (struct cvp_complex):                                          *
 *          The square of z.                                                  *
 *  Method:                                                                   *
 *      Use the multiplication formula with z0 = z1.                          *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_square(const struct cvp_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex square;

    /*  Compute z*z using i^2 = -1.                                           */
    square.real = z->real*z->real - z->imag*z->imag;
    square.imag = 2.0*z->real*z->imag;
    return square;
}
/*  End of cvp_complex_square.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_squareself                                                *
 *  Purpose:                                                                  *
 *      Computes the square of a complex number and stores it in the input.   *
 *  Arguments:                                                                *
 *      z (struct cvp_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Use the multiplication formula with z0 = z1.                          *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_squareself(struct cvp_complex *z)
{
    /*  Avoid overwriting the data by copying it to two local variables.      */
    const double real = z->real;
    const double imag = z->imag;

    /*  Compute z*z using i^2 = -1.                                           */
    z->real = real*real - imag*imag;
    z->imag = 2.0*real*imag;
}
/*  End of cvp_complex_squareself.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_abs                                                       *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a complex number.                      *
 *  Arguments:                                                                *
 *      z (const struct cvp_complex *):                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      abs_z (double):                                                       *
 *          The modulus, or absolute value, of z.                             *
 *  Method:                                                                   *
 *      Invoke the Pythagoras theorem. If z = x + i*y = (x, y) we have:       *
 *                                                                            *
 *            |z| = sqrt(x^2 + y^2)                                           *
 *                                                                            *
 *      This is computed and returned.                                        *
 *  Notes:                                                                    *
 *      This is the "unsafe" way of computing the absolute value. If x or y   *
 *      are larger than 10^154 their square overflows to infinity. This       *
 *      almost never occurs with numbers used in practice, so this method of  *
 *      computing |z| is fine.                                                *
 ******************************************************************************/
CVP_INLINE double
cvp_complex_abs(const struct cvp_complex *z)
{
    /*  Use the Pythagorean formula and return.                               */
    return sqrt(z->real*z->real + z->imag*z->imag);
}
/*  End of cvp_complex_abs.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_abssq                                                     *
 *  Purpose:                                                                  *
 *      Computes the square of the absolute value of a complex number.        *
 *  Arguments:                                                                *
 *      z (const struct cvp_complex *):                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      abs_sq_z (double):                                                    *
 *          The square of the modulus, or absolute value, of z.               *
 *  Method:                                                                   *
 *      Invoke the Pythagoras theorem. If z = x + i*y = (x, y) we have:       *
 *                                                                            *
 *            |z|^2 = x^2 + y^2                                               *
 *                                                                            *
 *      This is computed and returned.                                        *
 ******************************************************************************/
CVP_INLINE double
cvp_complex_abssq(const struct cvp_complex *z)
{
    /*  Use the Pythagorean formula and return.                               */
    return z->real*z->real + z->imag*z->imag;
}
/*  End of cvp_complex_abssq.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_dist                                                      *
 *  Purpose:                                                                  *
 *      Computes the distance between two points in the complex plane.        *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      distance (double):                                                    *
 *          The Euclidean distance between z0 and z1.                         *
 *  Method:                                                                   *
 *      Compute |z0 - z1| and return.                                         *
 ******************************************************************************/
CVP_INLINE double
cvp_complex_dist(const struct cvp_complex *z0, const struct cvp_complex *z1)
{
    /*  Compute the displacements in the real and imaginary axes.             */
    const double dx = z0->real - z1->real;
    const double dy = z0->imag - z1->imag;

    /*  Invoke Pythagoras to compute the distance.                            */
    return sqrt(dx*dx + dy*dy);
}
/*  End of cvp_complex_dist.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_arg                                                       *
 *  Purpose:                                                                  *
 *      Computes the argument, of phase, of a complex number.                 *
 *  Arguments:                                                                *
 *      z (const struct cvp_complex *):                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      arg_z (double):                                                       *
 *          The azimuthal angle of z.                                         *
 *  Method:                                                                   *
 *      Compute the angle the point (x, y) makes with the x axis using atan2. *
 ******************************************************************************/
CVP_INLINE double
cvp_complex_arg(const struct cvp_complex *z)
{
    /*  Compute the angle the complex number makes with the x axis via atan2. */
    return atan2(z->imag, z->real);
}
/*  End of cvp_complex_arg.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_affine_transform                                          *
 *  Purpose:                                                                  *
 *      Performs z = z0 + a*z2.                                               *
 *  Arguments:                                                                *
 *      z0 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *      a (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      out (struct cvp_complex):                                             *
 *          The transformation out = z0 + a*z2;                               *
 *  Method:                                                                   *
 *      Use the product and sum rules as before.                              *
 ******************************************************************************/
CVP_INLINE struct cvp_complex
cvp_complex_affine_transform(const struct cvp_complex *z0,
                            const struct cvp_complex *a,
                            const struct cvp_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct cvp_complex out;

    /*  Perform the product using the rule i^2 = -1.                          */
    out.real = z0->real + (a->real*z1->real - a->imag*z1->imag);
    out.imag = z0->imag + (a->real*z1->imag + a->imag*z1->real);
    return out;
}
/*  End of cvp_complex_affine_transform.                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      cvp_complex_affine_transformself                                      *
 *  Purpose:                                                                  *
 *      Performs z0 += a*z2.                                                  *
 *  Arguments:                                                                *
 *      z0 (struct cvp_complex *):                                            *
 *          A pointer to a complex number.                                    *
 *      a (const struct cvp_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct cvp_complex *):                                      *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Use the product and sum rules as before.                              *
 ******************************************************************************/
CVP_INLINE void
cvp_complex_affine_transformself(struct cvp_complex *z0,
                                const struct cvp_complex *a,
                                const struct cvp_complex *z1)
{
    /*  Perform the product using the rule i^2 = -1.                          */
    z0->real += a->real*z1->real - a->imag*z1->imag;
    z0->imag += a->real*z1->imag + a->imag*z1->real;
}
/*  End of cvp_complex_affine_transformself.                                  */

#endif
/*  End of include guard.                                                     */
