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
 *      Provides a basic double-precision 6D vector struct.                   *
 *      Used for working in phase space (position, velocity).                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/04                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_VEC6_H
#define NBH_VEC6_H

/*  NBH_INLINE macro found here.                                              */
#include "nbh_inline.h"

/*  3D vectors found here. A 6D vector is two 3D vectors.                     */
#include "nbh_vec3.h"

/*  sqrt found here.                                                          */
#include <math.h>

/*  Simple struct for a vector in R^6.                                        */
struct nbh_vec6 {

    /*  A 6D vector is made of two 3D vectors.                                */
    struct nbh_vec3 p, v;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_from_reals                                                   *
 *  Purpose:                                                                  *
 *      Creates a 6D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x-component of the position vector.                           *
 *      y (double):                                                           *
 *          The y-component of the position vector.                           *
 *      z (double):                                                           *
 *          The z-component of the position vector.                           *
 *      vx (double):                                                          *
 *          The x-component of the velocity vector.                           *
 *      vy (double):                                                          *
 *          The y-component of the velocity vector.                           *
 *      vz (double):                                                          *
 *          The z-component of the velocity vector.                           *
 *  Outputs:                                                                  *
 *      u (struct nbh_vec6):                                                  *
 *          The vector (x, y, z, vx, vy, vz).                                 *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_vec6_from_reals(double x, double y, double z,
                    double vx, double vy, double vz)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec6 u;

    /*  Set the components of the position vector.                            */
    u.p.x = x;
    u.p.y = y;
    u.p.z = z;

    /*  Set the components of the velocity vector.                            */
    u.v.x = vx;
    u.v.y = vy;
    u.v.z = vz;
    return u;
}
/*  End of nbh_vec6_from_reals.                                               */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_from_vectors                                                 *
 *  Purpose:                                                                  *
 *      Creates a 6D vector from two 3D vectors.                              *
 *  Arguments:                                                                *
 *      p (const struct nbh_vec3 *p):                                         *
 *          The position vector.                                              *
 *      v (const struct nbh_vec3 *v):                                         *
 *          The velocity vector.                                              *
 *  Outputs:                                                                  *
 *      u (struct nbh_vec6):                                                  *
 *          The vector (p, v).                                                *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_vec6_from_vectors(const struct nbh_vec3 *p, const struct nbh_vec3 *v)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec6 u;

    /*  Set the two vectors and return.                                       */
    u.p = *p;
    u.v = *v;
    return u;
}
/*  End of nbh_vec6_from_vectors.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_add                                                          *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^6.                                              *
 *  Arguments:                                                                *
 *      u0 (const struct nbh_vec6 *):                                         *
 *          A pointer to a vector.                                            *
 *      u1 (const struct nbh_vec6 *):                                         *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      sum (struct nbh_vec6):                                                *
 *          The vector sum of u0 and u1.                                      *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is, given two       *
 *      vectors u0 = (p0, v0) and u1 = (p1, v1), the sum is:                  *
 *                                                                            *
 *          sum = u0 + u1                                                     *
 *              = (p0, v0) + (p1, v1)                                         *
 *              = (p0 + p1, v0 + v1)                                          *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_vec6_add(const struct nbh_vec6 *u0, const struct nbh_vec6 *u1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec6 sum;

    /*  Vector addition is performed component-wise.                          */
    sum.p = nbh_vec3_add(&u0->p, &u1->p);
    sum.v = nbh_vec3_add(&u0->v, &u1->v);
    return sum;
}
/*  End of nbh_vec6_add.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_addto                                                        *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^6 and stores the result in the first variable.  *
 *  Arguments:                                                                *
 *      u0 (struct nbh_vec6 *):                                               *
 *          A pointer to a vector. The sum is stored here.                    *
 *      u1 (const struct nbh_vec6 *):                                         *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform vector addition component-wise and store the result in u0.    *
 ******************************************************************************/
NBH_INLINE void
nbh_vec6_addto(struct nbh_vec6 *u0, const struct nbh_vec6 *u1)
{
    /*  Vector addition is done component-wise. Store sum in the first vector.*/
    nbh_vec3_addto(&u0->p, &u1->p);
    nbh_vec3_addto(&u0->v, &u1->v);
}
/*  End of nbh_vec6_addto.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_subtract                                                     *
 *  Purpose:                                                                  *
 *      Subtracts two vectors in R^6.                                         *
 *  Arguments:                                                                *
 *      u0 (const struct nbh_vec6 *):                                         *
 *          A pointer to a vector.                                            *
 *      u1 (const struct nbh_vec6 *):                                         *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      diff (struct nbh_vec6):                                               *
 *          The vector difference of u0 and u1, u0 - u1.                      *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is, given two    *
 *      vectors u0 = (p0, v0) and u1 = (p1, v1), the difference is:           *
 *                                                                            *
 *          diff = u0 - u1                                                    *
 *               = (p0, v0) - (p1, v1)                                        *
 *               = (p0 - p1, v0 - v1)                                         *
 *                                                                            *
 *      This is computed and the difference is returned.                      *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nbh_vec6_subtract(&u0, &u1)    *
 *      computes the difference u0 - u1 (and not u1 - u0).                    *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_vec6_subtract(const struct nbh_vec6 *u0, const struct nbh_vec6 *u1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec6 diff;

    /*  Vector subtraction is performed component-wise.                       */
    diff.p = nbh_vec3_subtract(&u0->p, &u1->p);
    diff.v = nbh_vec3_subtract(&u0->v, &u1->v);
    return diff;
}
/*  End of nbh_vec6_subtract.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_subtractfrom                                                 *
 *  Purpose:                                                                  *
 *      Subtracts two vectors and stores the result in the first variable.    *
 *  Arguments:                                                                *
 *      u0 (struct nbh_vec6 *):                                               *
 *          A pointer to a vector. The difference is stored here.             *
 *      u1 (const struct nbh_vec6 *):                                         *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform vector subtraction component-wise and store the result in u0. *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nbh_vec6_subtractfrom(&u0, &u1)*
 *      computes the difference u0 - u1 (and not u1 - u0).                    *
 ******************************************************************************/
NBH_INLINE void
nbh_vec6_subtractfrom(struct nbh_vec6 *u0, const struct nbh_vec6 *u1)
{
    /*  Store the difference in the first vector.                             */
    nbh_vec3_subtractfrom(&u0->p, &u1->p);
    nbh_vec3_subtractfrom(&u0->v, &u1->v);
}
/*  End of nbh_vec6_subtractfrom.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_scale                                                        *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication.                                       *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      u (const struct nbh_vec6 *):                                          *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      prod (struct nbh_vec6):                                               *
 *          The scalar product a*u.                                           *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is, if u is   *
 *      the vector u = (p, v), then the product is:                           *
 *                                                                            *
 *          prod = a*u                                                        *
 *               = a*(p, v)                                                   *
 *               = (a*p, a*v)                                                 *
 *                                                                            *
 *      This is computed and the product is returned.                         *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_vec6_scale(double a, const struct nbh_vec6 *u)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec6 prod;

    /*  Scalar multiplication is done component-wise.                         */
    prod.p = nbh_vec3_scale(a, &u->p);
    prod.v = nbh_vec3_scale(a, &u->v);
    return prod;
}
/*  End of nbh_vec6_scale.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_scaleby                                                      *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and stores the result in place.        *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      v (struct nbh_vec6 *):                                                *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in v.*
 ******************************************************************************/
NBH_INLINE void
nbh_vec6_scaleby(double a, struct nbh_vec6 *u)
{
    /*  Scalar multiplication is done component-wise.                         */
    nbh_vec3_scaleby(a, &u->p);
    nbh_vec3_scaleby(a, &u->v);
}
/*  End of nbh_vec6_scaleby.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_dot_product                                                  *
 *  Purpose:                                                                  *
 *      Performs the Euclidean dot product in R^6.                            *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec6 *):                                          *
 *          A pointer to a vector.                                            *
 *      w (const struct nbh_vec6 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      dot (double):                                                         *
 *          The dot product v . w.                                            *
 *  Method:                                                                   *
 *      The Euclidean dot product sums the products of the components. Given  *
 *      two vectors u0 = (p0, v0) and u1 = (p1, v1), the dot product is:      *
 *                                                                            *
 *          u0 . u1 = (p0, v0) . (p1, v1)                                     *
 *                  = (p0 . p1) + (v0 . v1)                                   *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
NBH_INLINE double
nbh_vec6_dot_product(const struct nbh_vec6 *u0, const struct nbh_vec6 *u1)
{
    /*  The dot product is the sum of the products of the components.         */
    return nbh_vec3_dot_product(&u0->p, &u1->p) +
           nbh_vec3_dot_product(&u0->v, &u1->v);
}
/*  End of nbh_vec6_dot_product.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_normsq                                                       *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean, or L2, norm for vectors in R^6. *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          A pointer to a vector in R^6.                                     *
 *  Outputs:                                                                  *
 *      normsq_u (double):                                                    *
 *          The square of the norm, or magnitude, or length of the vector u.  *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given u = (p, v) we have:     *
 *                                                                            *
 *          ||u||^2 = ||(p, v)||^2                                            *
 *                  = ||p||^2 + ||v||^2                                       *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
NBH_INLINE double
nbh_vec6_normsq(const struct nbh_vec6 *u)
{
    /*  Use Pythagoras and compute.                                           */
    return nbh_vec3_normsq(&u->p) + nbh_vec3_normsq(&u->v);
}
/*  End of nbh_vec6_normsq.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec6_norm                                                         *
 *  Purpose:                                                                  *
 *      Computes the Euclidean, or L2, norm for vectors in R^6.               *
 *  Arguments:                                                                *
 *      u (const struct nbh_vec6 *):                                          *
 *          A pointer to a vector in R^6.                                     *
 *  Outputs:                                                                  *
 *      normsq_u (double):                                                    *
 *          The norm, or magnitude, or length of the vector u.                *
 *  Method:                                                                   *
 *      Return the square root of the nbh_vec6_normsq function.               *
 ******************************************************************************/
NBH_INLINE double
nbh_vec6_norm(const struct nbh_vec6 *u)
{
    /*  Use Pythagoras and compute.                                           */
    return sqrt(nbh_vec6_normsq(u));
}
/*  End of nbh_vec6_norm.                                                     */

#endif
/*  End of include guard.                                                     */
