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
 *      Implementation of Hubbard, Schleicher, and Sutherland's algorithm for *
 *      finding all roots of a complex polynomial.                            *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/19                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_COMPLEX_ROOTS_H
#define NF_COMPLEX_ROOTS_H

/*  NF_INLINE macro provided here.                                            */
#include "nf_inline.h"

/*  Complex number struct given here.                                         */
#include "nf_complex.h"

/*  Polynomials with real coefficients provided here.                         */
#include "nf_real_poly.h"

/*  Polynomials with complex coefficients given here.                         */
#include "nf_complex_poly.h"

/*  Setup parameters found here.                                              */
#include "nf_setup.h"

/*  malloc and realloc are provided here.                                     */
#include <stdlib.h>

/*  ceil and log functions provided here.                                     */
#include <math.h>

#include "nf_colorers.h"

/*  Struct for the roots of a real or complex polynomial.                     */
struct nf_complex_roots {

    /*  Array for the roots of a polynomial.                                  */
    struct nf_complex *roots;

    /*  The number of elements in the above array.                            */
    unsigned int number_of_roots;
};

NF_INLINE void
nf_complex_roots_destroy(struct nf_complex_roots **root_ptr)
{
    struct nf_complex_roots *roots;
    if (!root_ptr)
        return;
    roots = *root_ptr;

    if (!roots)
        return;

    if (roots->roots)
    {
        free(roots->roots);
        roots->roots = NULL;
    }

    free(roots);
    roots = NULL;
}

NF_INLINE struct nf_complex_roots *
nf_complex_poly_roots(const struct nf_complex_poly *poly)
{
    struct nf_complex_roots *out;
    struct nf_complex p, newton_factor, fprime_p;
    unsigned int circle_ind, sample_ind, n, iter, number_of_circles, samples_per_circle;
    double circle_factor, sample_factor, radius, angle, factor_1, factor_2, min, temp, pow_factor;
    void *tmp;

    /*  If the polynomial was NULL, return NULL. Everything is a root.        */
    if (!poly)
        return NULL;

    /*  Similarly if the data pointer is NULL or the degree is zero.          */
    else if (!poly->coeffs || poly->degree == 0U)
        return NULL;

    /*  Otherwise allocate memory for the root struct.                        */
    out = malloc(sizeof(*out) * poly->degree);

    /*  Check if malloc failed. It returns NULL if it does.                   */
    if (!out)
        return NULL;

    /*  Allocate memory for the roots in the root struct. By the fundamental  *
     *  theorem of algebra there are at most poly->degree roots. We will      *
     *  realloc this struct later if there are less than this many roots.     */
    out->roots = malloc(sizeof(*out->roots) * poly->degree);

    /*  Check if this call to malloc failed. Again, it returns NULL.          */
    if (!out->roots)
    {
        /*  malloc was successful for the previous call, so free out.         */
        free(out);
        return NULL;
    }

    /*  Set the number of roots to zero. We'll count these later.             */
    out->number_of_roots = 0U;

    /*  The number of circles is given by the degree of the polynomials.      */
    circle_factor = ceil(0.26632*log(poly->degree));
    number_of_circles = (unsigned int)circle_factor;

    /*  Similarly, the number of samples is also given by the degree.         */
    sample_factor = ceil(8.32547*poly->degree*log(poly->degree));
    samples_per_circle = (unsigned int)sample_factor;

    /*  Factors that occur in the HSS paper.                                  */
    factor_1 = 1.0 + sqrt(2.0);
    factor_2 = (poly->degree - 1.0) / poly->degree;

    /*  Loop through each circle in the plane.                                */
    for (circle_ind = 0U; circle_ind < number_of_circles; ++circle_ind)
    {

        /*  Fundamental theorem of algebra. If we have "degree" roots, stop.  */
        if (out->number_of_roots >= poly->degree)
            break;

        /*  Radius of the current circle.                                     */
        pow_factor = (2.0*circle_ind + 1.0) / (4.0*number_of_circles);
        radius = factor_1 + pow(factor_2, pow_factor);

        /*  Loop through each sample on the current circle.                   */
        for (sample_ind = 0U; sample_ind < samples_per_circle; ++sample_ind)
        {
            /*  Same skip as before using the fundamental theorem of algebra. */
            if (out->number_of_roots >= poly->degree)
                break;

            /*  Angle of the current sample on the circle.                    */
            angle = 2.0*M_PI*sample_ind/samples_per_circle;

            /*  Compute the point (radius, angle) in polar coordinates.       */
            p.real = radius*cos(angle);
            p.imag = radius*sin(angle);

            /*  Evaluate the polynomial at this point.                        */
            newton_factor = nf_complex_poly_eval(poly, &p);

            /*  Perform Newton's method with this current guess point.        */
            for (iter = 0U; iter < nf_setup_max_iters; ++iter)
            {


                if (nf_complex_abssq(&newton_factor) < nf_setup_eps_sq)
                    break;

                fprime_p = nf_complex_dpoly_eval(poly, &p);
                nf_complex_divideby(&newton_factor, &fprime_p);
                nf_complex_subtractfrom(&p, &newton_factor);
                newton_factor = nf_complex_poly_eval(poly, &p);
            }

            if (nf_complex_abssq(&newton_factor) < nf_setup_eps_sq)
            {
                if (out->number_of_roots == 0U)
                {
                    out->number_of_roots++;
                    out->roots[0] = p;
                }
                else
                {
                    min = nf_complex_dist(&p, &out->roots[0]);
                    for (n = 1U; n < out->number_of_roots; ++n)
                    {
                        temp = nf_complex_dist(&p, &out->roots[n]);

                        if (temp < min)
                            min = temp;
                    }

                    if (min >= 1.0E2 * nf_setup_eps)
                    {
                        out->roots[out->number_of_roots] = p;
                        out->number_of_roots++;
                    }
                }
            }
        }
    }

    /*  If no roots were found, this is an error. Free the memory.            */
    if (out->number_of_roots == 0U)
    {
        free(out->roots);
        out->roots = NULL;
    }

    /*  Otherwise reallocate the array to the number of roots found.          */
    else
    {
        tmp = realloc(out->roots, sizeof(*out->roots)*out->number_of_roots);

        /*  Check if realloc failed.                                          */
        if (tmp)
            out->roots = tmp;
    }

    return out;
}

NF_INLINE struct nf_color *
nf_complex_roots_get_colors(unsigned int number_of_roots)
{
    struct nf_color *out;
    double angle;
    unsigned int n;

    if (number_of_roots == 0U)
        return NULL;

    out = malloc(sizeof(*out) * number_of_roots);

    if (!out)
        return NULL;

    for (n = 0U; n < number_of_roots; ++n)
    {
        angle = (2.0 * M_PI * n) / number_of_roots;
        out[n] = nf_color_wheel_from_complex(angle);
    }
    return out;
}

#endif
/*  End of include guard.                                                     */
