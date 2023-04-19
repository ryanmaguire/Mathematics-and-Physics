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
 *      Provides routines for performing Newton's method on complex functions.*
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_NEWTON_H
#define NF_NEWTON_H

/*  NF_INLINE macro declared here.                                            */
#include "nf_inline.h"

/*  Complex number struct and complex arithmetic provided here.               */
#include "nf_complex.h"

/*  Basic setup parameters used in the computations.                          */
#include "nf_setup.h"

/*  Real polynomial struct provided here with Horner's method evaluations.    */
#include "nf_real_poly.h"

/*  Complex polynomial struct provided here with Horner's method evaluations. */
#include "nf_complex_poly.h"

/*  Typedef for complex-valued functions with complex inputs.                 */
typedef struct nf_complex (*complex_function)(const struct nf_complex *);

/******************************************************************************
 *  Function:                                                                 *
 *      nf_newton                                                             *
 *  Purpose:                                                                  *
 *      Performs Newton's method on a given function with guess z0.           *
 *  Arguments:                                                                *
 *      f (complex_function):                                                 *
 *          The function we're trying to compute the root of.                 *
 *      fp (complex_function):                                                *
 *          The derivative of f, "f-prime".                                   *
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number. This is our initial guess for      *
 *          Newton's method. The resulting root will be stored here.          *
 *  Outputs:                                                                  *
 *      iters (unsigned int):                                                 *
 *          The number of iterations required to get to the desired error.    *
 *  Method:                                                                   *
 *      Newton's method is iterative. We define:                              *
 *                                                                            *
 *          z_{n+1} = z_{n} - f(z_{n}) / f'(z_{n})                            *
 *                                                                            *
 *      This is calculated until |f(z)| is small, or we've performed the      *
 *      maximum number of iterations allowed.                                 *
 ******************************************************************************/
NF_INLINE unsigned int
nf_newton(complex_function f, complex_function fp, struct nf_complex *z0)
{
    /*  Declare a variable for the derivative of f at z0.                     */
    struct nf_complex fp_z0;

    /*  And a variable for f at z0. This variable will serve a few purposes   *
     *  to save on wasteful code, so we'll just label it "factor".            */
    struct nf_complex factor;

    /*  Set the iteration count to zero.                                      */
    unsigned int iters = 0U;

    /*  Perform Newton's method until we've done too many iterations.         */
    while (iters < nf_setup_max_iters)
    {
        /*  Evaluate f at the current guess point.                            */
        factor = f(z0);

        /*  If |f(z0)| is small than z0 is near the root. We can stop.        */
        if (nf_complex_abssq(&factor) < nf_setup_eps_sq)
            break;

        /*  Otherwise perform Newton's method. Compute f'(z0).                */
        fp_z0 = fp(z0);

        /*  Compute f(z0) / f'(z0) and store the result in factor.            */
        nf_complex_divideby(&factor, &fp_z0);

        /*  Compute z0 - f(z0) / f'(z0) and store the result in z0.           */
        nf_complex_subtractfrom(z0, &factor);

        /*  Increment the number of iterations we've performed.               */
        iters++;
    }

    return iters;
}
/*  End of nf_newton.                                                         */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_newton_complex_poly                                                *
 *  Purpose:                                                                  *
 *      Performs Newton's method on a given polynomial with guess z0.         *
 *  Arguments:                                                                *
 *      poly (const struct nf_complex_poly *):                                *
 *          A complex polynomial which represents our function f.             *
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number. This is our initial guess for      *
 *          Newton's method. The resulting root will be stored here.          *
 *  Outputs:                                                                  *
 *      iters (unsigned int):                                                 *
 *          The number of iterations required to get to the desired error.    *
 *  Method:                                                                   *
 *      Newton's method is iterative. We define:                              *
 *                                                                            *
 *          z_{n+1} = z_{n} - f(z_{n}) / f'(z_{n})                            *
 *                                                                            *
 *      This is calculated until |f(z)| is small, or we've performed the      *
 *      maximum number of iterations allowed.                                 *
 ******************************************************************************/
NF_INLINE unsigned int
nf_newton_complex_poly(const struct nf_complex_poly *poly,
                       struct nf_complex *z0)
{
    /*  Declare a variable for the derivative of f at z0.                     */
    struct nf_complex fp_z0;

    /*  And a variable for f at z0. This variable will serve a few purposes   *
     *  to save on wasteful code, so we'll just label it "factor".            */
    struct nf_complex factor;

    /*  Set the iteration count to zero.                                      */
    unsigned int iters = 0U;

    /*  Perform Newton's method until we've done too many iterations.         */
    while (iters < nf_setup_max_iters)
    {
        /*  Evaluate f at the current guess point.                            */
        factor = nf_complex_poly_eval(poly, z0);

        /*  If |f(z0)| is small than z0 is near the root. We can stop.        */
        if (nf_complex_abssq(&factor) < nf_setup_eps_sq)
            break;

        /*  Otherwise perform Newton's method. Compute f'(z0).                */
        fp_z0 = nf_complex_dpoly_eval(poly, z0);

        /*  Compute f(z0) / f'(z0) and store the result in factor.            */
        nf_complex_divideby(&factor, &fp_z0);

        /*  Compute z0 - f(z0) / f'(z0) and store the result in z0.           */
        nf_complex_subtractfrom(z0, &factor);

        /*  Increment the number of iterations we've performed.               */
        iters++;
    }

    return iters;
}
/*  End of nf_newton_complex_poly.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_newton_real_poly                                                   *
 *  Purpose:                                                                  *
 *      Performs Newton's method on a given polynomial with guess z0.         *
 *  Arguments:                                                                *
 *      poly (struct nf_complex_poly *):                                      *
 *          A polynomial with real coefficients which represents our function.*
 *      z0 (struct nf_complex *):                                             *
 *          A pointer to a complex number. This is our initial guess for      *
 *          Newton's method. The resulting root will be stored here.          *
 *  Outputs:                                                                  *
 *      iters (unsigned int):                                                 *
 *          The number of iterations required to get to the desired error.    *
 *  Method:                                                                   *
 *      Newton's method is iterative. We define:                              *
 *                                                                            *
 *          z_{n+1} = z_{n} - f(z_{n}) / f'(z_{n})                            *
 *                                                                            *
 *      This is calculated until |f(z)| is small, or we've performed the      *
 *      maximum number of iterations allowed.                                 *
 ******************************************************************************/
NF_INLINE unsigned int
nf_newton_real_poly(const struct nf_real_poly *poly, struct nf_complex *z0)
{
    /*  Declare a variable for the derivative of f at z0.                     */
    struct nf_complex fp_z0;

    /*  And a variable for f at z0. This variable will serve a few purposes   *
     *  to save on wasteful code, so we'll just label it "factor".            */
    struct nf_complex factor;

    /*  Set the iteration count to zero.                                      */
    unsigned int iters = 0U;

    /*  Perform Newton's method until we've done too many iterations.         */
    while (iters < nf_setup_max_iters)
    {
        /*  Evaluate f at the current guess point.                            */
        factor = nf_real_poly_complex_eval(poly, z0);

        /*  If |f(z0)| is small than z0 is near the root. We can stop.        */
        if (nf_complex_abssq(&factor) < nf_setup_eps_sq)
            break;

        /*  Otherwise perform Newton's method. Compute f'(z0).                */
        fp_z0 = nf_real_dpoly_complex_eval(poly, z0);

        /*  Compute f(z0) / f'(z0) and store the result in factor.            */
        nf_complex_divideby(&factor, &fp_z0);

        /*  Compute z0 - f(z0) / f'(z0) and store the result in z0.           */
        nf_complex_subtractfrom(z0, &factor);

        /*  Increment the number of iterations we've performed.               */
        iters++;
    }

    return iters;
}
/*  End of nf_newton_real_poly.                                               */

#endif
/*  End of include guard.                                                     */
