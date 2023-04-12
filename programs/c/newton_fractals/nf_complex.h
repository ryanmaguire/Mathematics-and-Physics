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
 *  Date:   2023/04/12                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COMPLEX_H
#define NF_COMPLEX_H

/*  NF_INLINE macro is defined here.                                          */
#include "nf_inline.h"

/*  Basic struct for working with complex numbers.                            */
struct nf_complex {

    /*  A complex number is determined by its real and imaginary parts.       */
    double real, imag;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_create                                                     *
 *  Purpose:                                                                  *
 *      Creates a complex number from two real numbers.                       *
 *  Arguments:                                                                *
 *      real (double):                                                        *
 *          The real part of the complex number.                              *
 *      imag (double):                                                        *
 *          The imaginary part of the complex number.                         *
 *  Outputs:                                                                  *
 *      z (struct nf_complex):                                                *
 *          The complex number z = real + i*imag = (real, imag).              *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_complex_create(double real, double imag)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex z;

    /*  Set the real and imaginary parts and return.                          */
    z.real = real;
    z.imag = imag;
    return z;
}
/*  End of nf_complex_create.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_add                                                        *
 *  Purpose:                                                                  *
 *      Adds two complex numbers.                                             *
 *  Arguments:                                                                *
 *      z0 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      sum (struct nf_complex):                                              *
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
NF_INLINE struct nf_complex
nf_complex_add(const struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex sum;

    /*  Complex addition is done component-wise.                              */
    sum.real = z0->real + z1->real;
    sum.imag = z0->imag + z1->imag;
    return sum;
}
/*  End of nf_complex_add.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_addto                                                      *
 *  Purpose:                                                                  *
 *      Adds two complex numbers and stores the result in the first variable. *
 *  Arguments:                                                                *
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex addition as before and store the result in z0.        *
 *  Notes:                                                                    *
 *      This gives the complex struct a "+=" operator.                        *
 ******************************************************************************/
NF_INLINE void
nf_complex_addto(struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Complex addition is done component-wise.                              */
    z0->real += z1->real;
    z0->imag += z1->imag;
}
/*  End of nf_complex_addto.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_subtract                                                   *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers.                                        *
 *  Arguments:                                                                *
 *      z0 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      diff (struct nf_complex):                                             *
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
NF_INLINE struct nf_complex
nf_complex_subtract(const struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex diff;

    /*  Complex subtraction is done component-wise.                           */
    diff.real = z0->real - z1->real;
    diff.imag = z0->imag - z1->imag;
    return diff;
}
/*  End of nf_complex_subtract.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_subtractfrom                                               *
 *  Purpose:                                                                  *
 *      Subtracts two complex numbers and stores the result in the first      *
 *      variable.                                                             *
 *  Arguments:                                                                *
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex subtraction as before and store the result in z0.     *
 *  Notes:                                                                    *
 *      This gives the complex struct a "-=" operator.                        *
 ******************************************************************************/
NF_INLINE void
nf_complex_subtractfrom(struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Complex subtraction is done component-wise.                           */
    z0->real -= z1->real;
    z0->imag -= z1->imag;
}
/*  End of nf_complex_subtractfrom.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_multiply                                                   *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers.                                       *
 *  Arguments:                                                                *
 *      z0 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      prod (struct nf_complex):                                             *
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
NF_INLINE struct nf_complex
nf_complex_multiply(const struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex prod;

    /*  Perform the product using the rule i^2 = -1.                          */
    prod.real = z0->real*z1->real - z0->imag*z1->imag;
    prod.imag = z0->real*z1->imag + z0->imag*z1->real;
    return prod;
}
/*  End of nf_complex_multiply.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_multiplyby                                                 *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers and stores the result in the first     *
 *      variable.                                                             *
 *  Arguments:                                                                *
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          Another pointer to a complex number.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform complex multiplication and store the result in z0.            *
 *  Notes:                                                                    *
 *      This function is equivalent to a "*=" operator.                       *
 ******************************************************************************/
NF_INLINE void
nf_complex_multiplyby(struct nf_complex *z0, const struct nf_complex *z1)
{
    /*  Avoid overwriting the data by copying it to two local variables.      */
    const double real = z0->real;
    const double imag = z0->imag;

    /*  Perform the product using the rule i^2 = -1.                          */
    z0->real = real*z1->real - imag*z1->imag;
    z0->imag = real*z1->imag + imag*z1->real;
}
/*  End of nf_complex_multiplyby.                                             */

#endif
/*  End of include guard.                                                     */
