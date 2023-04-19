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
 *      Provides a polynomial struct with real coefficients.                  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_REAL_POLY_H
#define NF_REAL_POLY_H

/*  NF_INLINE macro provded here.                                             */
#include "nf_inline.h"

/*  Complex number struct provided here.                                      */
#include "nf_complex.h"

/*  Struct for working with real polynomials.                                 */
struct nf_real_poly {

    /*  An array of real numbers representing the coefficients.               */
    double *coeffs;

    /*  The degree of the polynomial. There should be degree + 1 coefficients.*/
    unsigned int degree;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_real_poly_complex_eval                                             *
 *  Purpose:                                                                  *
 *      Evaluates a polynomial at a complex number via Horners method.        *
 *  Arguments:                                                                *
 *      poly (const struct nf_real_poly *):                                   *
 *          A pointer to a polynomial with real coefficients.                 *
 *      z (const struct nf_complex *):                                        *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      poly_z (struct nf_complex):                                           *
 *          The polynomial evaluated at the input z.                          *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial at z.                  *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_real_poly_complex_eval(const struct nf_real_poly *poly,
                          const struct nf_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex out;

    /*  Variable for looping over the coefficients of the polynomial.         */
    unsigned int ind;

    /*  If the pointer is NULL return zero. The empty polynomial is zero.     */
    if (!poly)
        return nf_complex_zero;

    /*  Similarly if the data pointer is NULL.                                */
    else if (!poly->coeffs)
        return nf_complex_zero;

    /*  Otherwise initialize the output to the highest term.                  */
    out.real = poly->coeffs[poly->degree];
    out.imag = 0.0;

    /*  Perform Horner's method for the remaining terms.                      */
    for (ind = 1U; ind <= poly->degree; ++ind)
    {
        nf_complex_multiplyby(&out, z);
        out.real += poly->coeffs[poly->degree - ind];
    }

    return out;
}
/*  End of nf_real_poly_complex_eval.                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_real_dpoly_complex_eval                                            *
 *  Purpose:                                                                  *
 *      Evaluates the derivative of a polynomial via Horners method.          *
 *  Arguments:                                                                *
 *      poly (const struct nf_real_poly *):                                   *
 *          A pointer to a polynomial with real coefficients.                 *
 *      z (const struct nf_complex *):                                        *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      dpoly_z (struct nf_complex):                                          *
 *          The derivative of the polynomial evaluated at the input z.        *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the derivative at z.                  *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_real_dpoly_complex_eval(const struct nf_real_poly *poly,
                           const struct nf_complex *z)
{
    /*  Declare a variable for the output.                                    */
    struct nf_complex out;

    /*  Variable for looping over the coefficients of the polynomial.         */
    unsigned int ind;

    /*  If the pointer is NULL return zero. The empty polynomial is zero.     */
    if (!poly)
        return nf_complex_zero;

    /*  Similarly if the data pointer is NULL.                                */
    else if (!poly->coeffs)
        return nf_complex_zero;

    /*  Lastly, if the degree is zero the output is zero.                     */
    else if (poly->degree == 0U)
        return nf_complex_zero;

    /*  Otherwise initialize the output to the highest term.                  */
    out.real = poly->degree*poly->coeffs[poly->degree];
    out.imag = 0.0;

    /*  Perform Horner's method for the remaining terms.                      */
    for (ind = poly->degree - 1U; ind > 0U; --ind)
    {
        nf_complex_multiplyby(&out, z);
        out.real += ind*poly->coeffs[ind];
    }

    return out;
}
/*  End of nf_real_dpoly_complex_eval.                                        */

#endif
/*  End of include guard.                                                     */
