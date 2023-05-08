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
 *      Provides a basic double-precision 2D vector struct.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/08                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NF_VEC2_H
#define NF_VEC2_H

/*  NF_INLINE macro found here.                                               */
#include "nf_inline.h"

/*  sqrt found here.                                                          */
#include <math.h>

/*  Simple struct for a vector in R^2.                                        */
struct nf_vec2 {

    /*  A vector is completely determined by its Cartesian components.        */
    double x, y;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_rect                                                          *
 *  Purpose:                                                                  *
 *      Creates a 2D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x-component of the vector.                                    *
 *      y (double):                                                           *
 *          The y-component of the vector.                                    *
 *  Outputs:                                                                  *
 *      v (struct nf_vec2):                                                   *
 *          The vector (x, y).                                                *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_rect(double x, double y)
{
    /*  Declare necessary variables.                                          */
    struct nf_vec2 v;

    /*  Set the components for the vector and return.                         */
    v.x = x;
    v.y = y;
    return v;
}
/*  End of nf_vec2_rect.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_add                                                           *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^2.                                              *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *      w (const struct nf_vec2 *):                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      sum (struct nf_vec2):                                                 *
 *          The vector sum of v and w.                                        *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is, given two       *
 *      vectors v = (vx, vy) and w = (wx, wy), the sum is:                    *
 *                                                                            *
 *          sum = v + w                                                       *
 *              = (vx, vy) + (wx, wy)                                         *
 *              = (vx + wx, vy + wy)                                          *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_add(const struct nf_vec2 *v, const struct nf_vec2 *w)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nf_vec2 sum;

    /*  Vector addition is performed component-wise.                          */
    sum.x = v->x + w->x;
    sum.y = v->y + w->y;
    return sum;
}
/*  End of nf_vec2_add.                                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_addto                                                         *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^2 and stores the result in the first variable.  *
 *  Arguments:                                                                *
 *      v (struct nf_vec2 *):                                                 *
 *          A pointer to a vector. The sum is stored here.                    *
 *      w (const struct nf_vec2 *):                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform vector addition component-wise and store the result in v.     *
 ******************************************************************************/
NF_INLINE void
nf_vec2_addto(struct nf_vec2 *v, const struct nf_vec2 *w)
{
    /*  Vector addition is done component-wise. Store sum in the first vector.*/
    v->x += w->x;
    v->y += w->y;
}
/*  End of nf_vec2_addto.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_subtract                                                      *
 *  Purpose:                                                                  *
 *      Subtracts two vectors in R^2.                                         *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *      w (const struct nf_vec2 *):                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      diff (struct nf_vec2):                                                *
 *          The vector difference of v and w, v - w.                          *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is, given two    *
 *      vectors v = (vx, vy) and w = (wx, wy), the difference is:             *
 *                                                                            *
 *          diff = v - w                                                      *
 *               = (vx, vy) - (wx, wy)                                        *
 *               = (vx - wx, vy - wy)                                         *
 *                                                                            *
 *      This is computed and the difference is returned.                      *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nf_vec2_subtract(&v, &w)       *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_subtract(const struct nf_vec2 *v, const struct nf_vec2 *w)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nf_vec2 diff;

    /*  Vector subtraction is performed component-wise.                       */
    diff.x = v->x - w->x;
    diff.y = v->y - w->y;
    return diff;
}
/*  End of nf_vec2_subtract.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_subtractfrom                                                  *
 *  Purpose:                                                                  *
 *      Subtracts two vectors and stores the result in the first variable.    *
 *  Arguments:                                                                *
 *      v (struct nf_vec2 *):                                                 *
 *          A pointer to a vector. The difference is stored here.             *
 *      w (const struct nf_vec2 *):                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform vector subtraction component-wise and store the result in v.  *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nf_vec2_subtractfrom(&v, &w)   *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
NF_INLINE void
nf_vec2_subtractfrom(struct nf_vec2 *v, const struct nf_vec2 *w)
{
    /*  Store the difference in the first vector.                             */
    v->x -= w->x;
    v->y -= w->y;
}
/*  End of nf_vec2_subtractfrom.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_scale                                                         *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication.                                       *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      prod (struct nf_vec2):                                                *
 *          The scalar product a*v.                                           *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is, if v is   *
 *      the vector v = (x, y), then the product is:                           *
 *                                                                            *
 *          prod = a*v                                                        *
 *               = a*(x, y)                                                   *
 *               = (a*x, a*y)                                                 *
 *                                                                            *
 *      This is computed and the product is returned.                         *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_scale(double a, const struct nf_vec2 *v)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nf_vec2 prod;

    /*  Scalar multiplication is done component-wise.                         */
    prod.x = a*v->x;
    prod.y = a*v->y;
    return prod;
}
/*  End of nf_vec2_scale.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_scaleby                                                       *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and stores the result in place.        *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      v (struct nf_vec2 *):                                                 *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in v.*
 ******************************************************************************/
NF_INLINE void
nf_vec2_scaleby(double a, struct nf_vec2 *v)
{
    /*  Scalar multiplication is done component-wise.                         */
    v->x *= a;
    v->y *= a;
}
/*  End of nf_vec2_scaleby.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_scaled_add                                                    *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and vector addition, u = v + a*w       *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      w (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      scaled_sum (struct nf_vec2):                                          *
 *          The sum v + a*w.                                                  *
 *  Method:                                                                   *
 *      Perform the operation component-wise.                                 *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_scaled_add(const struct nf_vec2 *v, double a, const struct nf_vec2 *w)
{
    /*  Declare a variable for the output.                                    */
    struct nf_vec2 out;

    /*  Perform the operation component-wise.                                 */
    out.x = v->x + a*w->x;
    out.y = v->y + a*w->y;
    return out;
}
/*  End of nf_vec2_scaled_add.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_scaled_addto                                                  *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and vector addition, v += a*w          *
 *  Arguments:                                                                *
 *      v (struct nf_vec2 *):                                                 *
 *          A pointer to a vector.                                            *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      w (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform the operation component-wise.                                 *
 ******************************************************************************/
NF_INLINE void
nf_vec2_scaled_addto(struct nf_vec2 *v, double a, const struct nf_vec2 *w)
{
    /*  Perform the operation component-wise.                                 */
    v->x += a*w->x;
    v->y += a*w->y;
}
/*  End of nf_vec2_scaled_addto.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_dot_product                                                   *
 *  Purpose:                                                                  *
 *      Performs the Euclidean dot product in R^2.                            *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector.                                            *
 *      w (const struct nf_vec2 *):                                           *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      dot (double):                                                         *
 *          The dot product v . w.                                            *
 *  Method:                                                                   *
 *      The Euclidean dot product sums the products of the components. Given  *
 *      two vectors v = (vx, vy) and w = (wx, wy), the dot product is:        *
 *                                                                            *
 *          v.w = (vx, vy) . (wx, wy)                                         *
 *              = vx*wx + vy*wy                                               *
 *                                                                            *
 *      This is computed and the sum of products is returned.                 *
 ******************************************************************************/
NF_INLINE double
nf_vec2_dot_product(const struct nf_vec2 *v, const struct nf_vec2 *w)
{
    /*  The dot product is the sum of the products of the components.         */
    return v->x*w->x + v->y*w->y;
}
/*  End of nf_vec2_dot_product.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_norm                                                          *
 *  Purpose:                                                                  *
 *      Computes the Euclidean, or L2, norm of a vector in R^2.               *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector in R^2.                                     *
 *  Outputs:                                                                  *
 *      norm_v (double):                                                      *
 *          The norm, or magnitude, or length of the vector v.                *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y) we have:     *
 *                                                                            *
 *          ||v|| = ||(x, y)||                                                *
 *                = sqrt(x^2 + y^2)                                           *
 *                                                                            *
 *      Compute and return the norm.                                          *
 *  Notes:                                                                    *
 *      This function does not use any fancy tricks to avoid overflow. For    *
 *      most implementations of double, if x or y has a magnitude greater     *
 *      than ~10^154, the sum of the squares will overflow and the result is  *
 *      infinite. Such large numbers do not occur in this mini-project.       *
 ******************************************************************************/
NF_INLINE double
nf_vec2_norm(const struct nf_vec2 *v)
{
    /*  Use Pythagoras and compute the square root of the sum of the squares. */
    return sqrt(v->x*v->x + v->y*v->y);
}
/*  End of nf_vec2_norm.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_normsq                                                        *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean, or L2, norm for vectors in R^2. *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          A pointer to a vector in R^2.                                     *
 *  Outputs:                                                                  *
 *      normsq_v (double):                                                    *
 *          The square of the norm, or magnitude, or length of the vector v.  *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y) we have:     *
 *                                                                            *
 *          ||v||^2 = ||(x, y)||^2                                            *
 *                  = x^2 + y^2                                               *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
NF_INLINE double
nf_vec2_normsq(const struct nf_vec2 *v)
{
    /*  Use Pythagoras and compute.                                           */
    return v->x*v->x + v->y*v->y;
}
/*  End of nf_vec2_normsq.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_normalize                                                     *
 *  Purpose:                                                                  *
 *      Normalizes a vector to unit length.                                   *
 *  Arguments:                                                                *
 *      v (const struct nf_vec2 *):                                           *
 *          The vector that is to be normalized.                              *
 *  Outputs:                                                                  *
 *      v_hat (struct nf_vec2):                                               *
 *          The vector pointing in the direction of v with unit length.       *
 *  Method:                                                                   *
 *      Compute the norm of v and divide the components by this value.        *
 *  Notes:                                                                    *
 *      If the input is the zero vector the zero vector will be returned.     *
 ******************************************************************************/
NF_INLINE struct nf_vec2
nf_vec2_normalize(const struct nf_vec2 *v)
{
    /*  Variable for the output.                                              */
    struct nf_vec2 v_hat;

    /*  Save a potentially wasteful square root, compute ||v||^2.             */
    const double norm_sq = nf_vec2_normsq(v);

    /*  If the square of the norm is zero we have the zero vector.            */
    if (norm_sq == 0.0)
        v_hat = *v;

    /*  Otherwise we have a valid non-zero vector that we can normalized.     */
    else
    {
        /*  The scale factor is the reciprocal of the norm.                   */
        const double scale = 1.0 / sqrt(norm_sq);

        /*  Scale the components to normalize v.                              */
        v_hat.x = v->x * scale;
        v_hat.y = v->y * scale;
    }

    return v_hat;
}
/*  End of nf_vec2_normalize.                                                 */


/******************************************************************************
 *  Function:                                                                 *
 *      nf_vec2_normalizeself                                                 *
 *  Purpose:                                                                  *
 *      Normalizes a vector to unit length.                                   *
 *  Arguments:                                                                *
 *      v (struct nf_vec2 *):                                                 *
 *          The vector that is to be normalized.                              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Compute the norm of v and divide the components by this value.        *
 *  Notes:                                                                    *
 *      If the input is the zero vector the zero vector will be returned.     *
 ******************************************************************************/
NF_INLINE void
nf_vec2_normalizeself(struct nf_vec2 *v)
{
    /*  Save a potentially wasteful square root, compute ||v||^2.             */
    const double norm_sq = nf_vec2_normsq(v);

    /*  If the square of the norm is zero we have the zero vector.            */
    if (norm_sq == 0.0)
        return;

    /*  Otherwise we have a valid non-zero vector that we can normalized.     */
    else
    {
        /*  The scale factor is the reciprocal of the norm.                   */
        const double scale = 1.0 / sqrt(norm_sq);

        /*  Scale the components to normalize v.                              */
        v->x *= scale;
        v->y *= scale;
    }
}
/*  End of nf_vec2_normalizeself.                                             */

#endif
/*  End of include guard.                                                     */
