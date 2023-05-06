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
 *      Provides basic routines for rational functions.                       *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/06                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COMPLEX_RATIONAL_H
#define NF_COMPLEX_RATIONAL_H

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Complex number struct provided here.                                      */
#include "nf_complex.h"

/*  Complex polynomials found here.                                           */
#include "nf_complex_poly.h"

/*  Struct for working with complex rational functions.                       */
struct nf_complex_rational {

    /*  A complex rational function is the quotient of two polynomials.       */
    struct nf_complex_poly num, den;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_rational_eval                                              *
 *  Purpose:                                                                  *
 *      Evaluates a rational function at a complex number.                    *
 *  Arguments:                                                                *
 *      rat (const struct nf_complex_rational *):                             *
 *          The rational function.                                            *
 *      z (const struct nf_complex *):                                        *
 *          The complex number where the rational is to be evaluated.         *
 *  Outputs:                                                                  *
 *      rat_z (struct nf_complex):                                            *
 *          The rational function evaluated at z.                             *
 *  Method:                                                                   *
 *      Use Horner's method twice, once for the numerator and once for the    *
 *      denominator, and divide the two values.                               *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_complex_rational_eval(const struct nf_complex_rational *rat,
                         const struct nf_complex *z)
{
    /*  Compute the evaluation for the numerator and denominator.             */
    const struct nf_complex num_z = nf_complex_poly_eval(&rat->num, z);
    const struct nf_complex den_z = nf_complex_poly_eval(&rat->den, z);

    /*  Divide the two values and return.                                     */
    return nf_complex_divide(&num_z, &den_z);
}
/*  End of nf_complex_rational_eval.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_drational_eval                                             *
 *  Purpose:                                                                  *
 *      Evaluates the derivative of a rational function at a complex number.  *
 *  Arguments:                                                                *
 *      rat (const struct nf_complex_rational *):                             *
 *          The rational function.                                            *
 *      z (const struct nf_complex *):                                        *
 *          The complex number where the rational is to be evaluated.         *
 *  Outputs:                                                                  *
 *      drat_z (struct nf_complex):                                           *
 *          The derivative of the rational function evaluated at z.           *
 *  Method:                                                                   *
 *      Use the quotient rule in combination with Horner's method.            *
 ******************************************************************************/
NF_INLINE struct nf_complex
nf_complex_drational_eval(const struct nf_complex_rational *rat,
                          const struct nf_complex *z)
{
    /*  Compute the evaluation for the numerator and denominator.             */
    const struct nf_complex num_z = nf_complex_poly_eval(&rat->num, z);
    const struct nf_complex den_z = nf_complex_poly_eval(&rat->den, z);

    /*  Evaluate the derivatives as well.                                     */
    const struct nf_complex dnum_z = nf_complex_dpoly_eval(&rat->num, z);
    const struct nf_complex dden_z = nf_complex_dpoly_eval(&rat->den, z);

    /*  Apply the quotient rule.                                              */
    const struct nf_complex den = nf_complex_square(&den_z);
    const struct nf_complex nprime_d = nf_complex_multiply(&dnum_z, &den_z);
    const struct nf_complex n_dprime = nf_complex_multiply(&num_z, &dden_z);
    const struct nf_complex num = nf_complex_subtract(&nprime_d, &n_dprime);

    /*  Divide the two values and return.                                     */
    return nf_complex_divide(&num, &den);
}
/*  End of nf_complex_drational_eval.                                         */

#endif
/*  End of include guard.                                                     */
