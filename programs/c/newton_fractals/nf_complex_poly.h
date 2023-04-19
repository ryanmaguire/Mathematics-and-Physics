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
 *      Provides a polynomial struct with complex coefficients.               *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COMPLEX_POLY_H
#define NF_COMPLEX_POLY_H

/*  NF_INLINE macro provded here.                                             */
#include "nf_inline.h"

/*  Complex number struct provided here.                                      */
#include "nf_complex.h"

/*  Struct for working with complex polynomials.                              */
struct nf_complex_poly {

    /*  An array of complex numbers representing the coefficients.            */
    struct nf_complex *coeffs;

    /*  The degree of the polynomial. There should be degree + 1 coefficients.*/
    unsigned int degree;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_horner_update                                              *
 *  Purpose:                                                                  *
 *      Performs a = z0 + a*z1. This is used in Horner's method since the     *
 *      iterative term is out = coeff[n] + out*z.                             *
 *  Arguments:                                                                *
 *      z0 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      a (struct nf_complex *):                                              *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Use the product and sum rules for complex numbers.                    *
 ******************************************************************************/
NF_INLINE void
nf_complex_horner_update(const struct nf_complex *z0,
                         struct nf_complex *a,
                         const struct nf_complex *z1)
{
    /*  Avoid overwriting the data by saving the real part of a.              */
    const double real = a->real;

    /*  Use complex arithmetic to compute a = z0 + a*a1.                      */
    a->real = z0->real + (real*z1->real - a->imag*z1->imag);
    a->imag = z0->imag + (real*z1->imag + a->imag*z1->real);
}
/*  End of nf_complex_horner_update.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_horner_deriv                                               *
 *  Purpose:                                                                  *
 *      Performs a = deg*z0 + a*z1. This is used in Horner's method since the *
 *      iterative term is out = deg*coeff[n] + out*z.                         *
 *  Arguments:                                                                *
 *      z0 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      a (struct nf_complex *):                                              *
 *          A pointer to a complex number.                                    *
 *      z1 (const struct nf_complex *):                                       *
 *          A pointer to a complex number.                                    *
 *      deg (unsigned int):                                                   *
 *          The degree of the term.                                           *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Use the product and sum rules for complex numbers.                    *
 ******************************************************************************/
NF_INLINE void
nf_complex_horner_deriv(const struct nf_complex *z0,
                        struct nf_complex *a,
                        const struct nf_complex *z1,
                        unsigned int deg)
{
    /*  Avoid overwriting the data by saving the real part of a.              */
    const double real = a->real;

    /*  Use complex arithmetic to compute a = z0 + a*a1.                      */
    a->real = deg*z0->real + (real*z1->real - a->imag*z1->imag);
    a->imag = deg*z0->imag + (real*z1->imag + a->imag*z1->real);
}
/*  End of nf_complex_horner_deriv.                                           */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_poly_eval                                                  *
 *  Purpose:                                                                  *
 *      Evaluates a complex polynomial via Horners method.                    *
 *  Arguments:                                                                *
 *      poly (const struct nf_complex_poly *):                                *
 *          A pointer to a polynomial with complex coefficients.              *
 *      z (const struct nf_complex *):                                        *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      poly_z (struct nf_complex):                                           *
 *          The polynomial evaluated at the input z.                          *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial at z.                  *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_complex_poly_eval(const struct nf_complex_poly *poly,
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
    out = poly->coeffs[poly->degree];

    /*  Perform Horner's method for the remaining terms.                      */
    for (ind = 1U; ind <= poly->degree; ++ind)
        nf_complex_horner_update(&poly->coeffs[poly->degree - ind], &out, z);

    return out;
}
/*  End of nf_complex_poly_eval.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_dpoly_eval                                                 *
 *  Purpose:                                                                  *
 *      Evaluates the derivative of acomplex polynomial via Horners method.   *
 *  Arguments:                                                                *
 *      poly (const struct nf_complex_poly *):                                *
 *          A pointer to a polynomial with complex coefficients.              *
 *      z (const struct nf_complex *):                                        *
 *          A pointer to a complex number.                                    *
 *  Outputs:                                                                  *
 *      dpoly_z (struct nf_complex):                                          *
 *          The derivative of the polynomial evaluated at the input z.        *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the derivative at z.                  *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_complex_dpoly_eval(const struct nf_complex_poly *poly,
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
    out.real = poly->degree*poly->coeffs[poly->degree].real;
    out.imag = poly->degree*poly->coeffs[poly->degree].imag;

    /*  Perform Horner's method for the remaining terms.                      */
    for (ind = poly->degree - 1U; ind > 0U; --ind)
        nf_complex_horner_deriv(&poly->coeffs[ind], &out, z, ind);

    return out;
}
/*  End of nf_complex_dpoly_eval.                                             */

#endif
/*  End of include guard.                                                     */
