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

/*  Functions for converting angles on the circle to colors.                  */
#include "nf_colorers.h"

/*  Setup parameters found here.                                              */
#include "nf_setup.h"

/*  malloc and realloc are provided here.                                     */
#include <stdlib.h>

/*  ceil and log functions provided here.                                     */
#include <math.h>

/*  Struct for the roots of a real or complex polynomial.                     */
struct nf_complex_roots {

    /*  Array for the roots of a polynomial.                                  */
    struct nf_complex *roots;

    /*  The number of elements in the above array.                            */
    unsigned int number_of_roots;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_roots_destroy                                              *
 *  Purpose:                                                                  *
 *      Safely frees the memory in a root struct and sets pointers to NULL.   *
 *  Arguments:                                                                *
 *      root_ptr (struct nf_complex_roots **):                                *
 *          A pointer to a pointer to a root struct. The pointer *root_ptr    *
 *          will be freed and set to NULL, as will the array of roots.        *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
NF_INLINE void
nf_complex_roots_destroy(struct nf_complex_roots **root_ptr)
{
    /*  Variable for the pointer with root_ptr points too.                    */
    struct nf_complex_roots *roots;

    /*  If the input is NULL there is nothing to do.                          */
    if (!root_ptr)
        return;

    /*  Dereference the root pointer and save it to roots.                    */
    roots = *root_ptr;

    /*  If this pointer is NULL there is also nothing to be done.             */
    if (!roots)
        return;

    /*  If the array of roots is not NULL it needs to be freed.               */
    if (roots->roots)
    {
        free(roots->roots);

        /*  Common trick to avoid double-frees. Set the pointer to NULL.      */
        roots->roots = NULL;
    }

    /*  Lastly free the root pointer itself and set it to NULL.               */
    free(roots);
    roots = NULL;
}
/*  End of nf_complex_roots_destroy.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_poly_roots                                                 *
 *  Purpose:                                                                  *
 *      Finds all roots in worst-case O(d log(d)^2) for a polynomial of       *
 *      degree d where all roots are known to lie in the closed unit disk.    *
 *  Arguments:                                                                *
 *      poly (const struct nf_complex_poly *):                                *
 *          A pointer to a polynomial. This is the polynomial whose roots     *
 *          we are trying to find.                                            *
 *  Outputs:                                                                  *
 *      out (struct nf_complex_roots *):                                      *
 *          A pointer to a root struct whose array contains the roots of poly.*
 *  Method:                                                                   *
 *      Use the algorithm by Hubbard, Schleicher, and Sutherland (HSS) to     *
 *      compute all roots of the polynomial using Newton's method.            *
 ******************************************************************************/
NF_INLINE struct nf_complex_roots *
nf_complex_poly_roots(const struct nf_complex_poly *poly)
{
    /*  Pointer for the output roots.                                         */
    struct nf_complex_roots *out;

    /*  Complex numbers for the sample point and the Newton iteration.        */
    struct nf_complex p, newton_factor, fprime_p;

    /*  Variables for the number of circles and number of samples required.   */
    unsigned int number_of_circles, samples_per_circle;

    /*  Index for the circles and samples on the circle.                      */
    unsigned int circle_ind, sample_ind;

    /*  Index used for Newton's method and creating the array of roots.       */
    unsigned int ind;

    /*  The circle factor is used to calculate the number of circles needed.  */
    double circle_factor;

    /*  Similarly the sample factor helps computes the number of samples.     */
    double sample_factor;

    /*  Variables for the radius and angles of the samples.                   */
    double radius, angle;

    /*  Constant factors that appear in the HSS paper.                        */
    double factor_1, factor_2, pow_factor;

    /*  Variables for computing the minimum distance between sets of points.  */
    double min, temp;

    /*  And lastly a variable for checking if realloc failed.                 */
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
            angle = (2.0 * M_PI * sample_ind) / samples_per_circle;

            /*  Compute the point (radius, angle) in polar coordinates.       */
            p.real = radius*cos(angle);
            p.imag = radius*sin(angle);

            /*  Evaluate the polynomial at this point.                        */
            newton_factor = nf_complex_poly_eval(poly, &p);

            /*  Perform Newton's method with this current guess point.        */
            for (ind = 0U; ind < nf_setup_max_iters; ++ind)
            {
                /*  If the polynomial at this point is small, we have a root. */
                if (nf_complex_abssq(&newton_factor) < nf_setup_eps_sq)
                    break;

                /*  Otherwise update the guess using Newton's method.         */
                fprime_p = nf_complex_dpoly_eval(poly, &p);
                nf_complex_divideby(&newton_factor, &fprime_p);
                nf_complex_subtractfrom(&p, &newton_factor);
                newton_factor = nf_complex_poly_eval(poly, &p);
            }
            /*  End of for loop for Newton's method.                          */

            /*  Check if this point converged to a root.                      */
            if (nf_complex_abssq(&newton_factor) < nf_setup_eps_sq)
            {
                /*  If this is the first root, add it too our list.           */
                if (out->number_of_roots == 0U)
                {
                    out->number_of_roots++;
                    out->roots[0] = p;
                }

                /*  Otherwise we need to check if this root was found before. */
                else
                {
                    /*  Compute the minimum distance of p to the other roots. */
                    min = nf_complex_dist(&p, &out->roots[0]);

                    /*  Loop through the array of other roots to get the      *
                     *  minimum distance. If this minimum distance is larger, *
                     *  we have found a new root for the polynomial.          */
                    for (ind = 1U; ind < out->number_of_roots; ++ind)
                    {
                        /*  Compute the distance to the given root.           */
                        temp = nf_complex_dist(&p, &out->roots[ind]);

                        /*  Update min if temp is a smaller value.            */
                        if (temp < min)
                            min = temp;
                    }

                    /*  If the minimum distance is large, we have a new root. */
                    if (min >= 1.0E2 * nf_setup_eps)
                    {
                        /*  Add this root to the array.                       */
                        out->roots[out->number_of_roots] = p;

                        /*  We found a new root, so increment the counter.    */
                        out->number_of_roots++;
                    }
                    /*  End of if for minimum distance.                       */
                }
                /*  End of if for number of roots found being zero.           */
            }
            /*  End of if for magnitude of final iteration being small.       */
        }
        /*  End of for loop for samples on a given circle.                    */
    }
    /*  End of for loop over the circles in the algorithm.                    */

    /*  If no roots were found, this is an error. Free the memory.            */
    if (out->number_of_roots == 0U)
    {
        free(out->roots);
        out->roots = NULL;
    }

    /*  Otherwise reallocate the array to the number of roots found.          */
    else if (out->number_of_roots != poly->degree)
    {
        /*  Shrink the array to removed the uninitialized elements.           */
        tmp = realloc(out->roots, sizeof(*out->roots)*out->number_of_roots);

        /*  Check if realloc failed.                                          */
        if (tmp)
            out->roots = tmp;
    }

    return out;
}
/*  End of nf_complex_poly_roots.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_complex_roots_get_colors                                           *
 *  Purpose:                                                                  *
 *      Retrieves an array of colors to correspond to roots in a root struct. *
 *  Arguments:                                                                *
 *      number_of_roots (unsigned int):                                       *
 *          The number of roots we're getting colors for.                     *
 *  Outputs:                                                                  *
 *    out (struct nf_color *):                                                *
 *        An array of number_of_roots distinct colors.                        *
 ******************************************************************************/
NF_INLINE struct nf_color *
nf_complex_roots_get_colors(unsigned int number_of_roots)
{
    /*  Variable for the output.                                              */
    struct nf_color *out;

    /*  Variable for looping over angles in the color wheel.                  */
    double angle;

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  If the input is zero we need no colors. Return NULL.                  */
    if (number_of_roots == 0U)
        return NULL;

    /*  Allocate memory for the color array.                                  */
    out = malloc(sizeof(*out) * number_of_roots);

    /*  And make sure malloc didn't fail.                                     */
    if (!out)
        return NULL;

    /*  Loop over angles in the color wheel and add these colors to the array.*/
    for (n = 0U; n < number_of_roots; ++n)
    {
        /*  Split the circle 0 -> 2 pi into number_of_roots segments.         */
        angle = (2.0 * M_PI * n) / number_of_roots;

        /*  Get a color for this angle.                                       */
        out[n] = nf_color_wheel_from_angle(angle);
    }

    return out;
}
/*  End of nf_complex_roots_get_colors.                                       */

#endif
/*  End of include guard.                                                     */
