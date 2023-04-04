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
 *      Provides a basic double-precision 3D vector struct.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/03                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_VEC3_H
#define NBH_VEC3_H

/*  NBH_INLINE macro found here.                                              */
#include "nbh_inline.h"

/*  sqrt found here.                                                          */
#include <math.h>

/*  Simple struct for a vector in R^3.                                        */
struct nbh_vec3 {

    /*  A vector is completely determined by its Cartesian components.        */
    double x, y, z;
};

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_rect                                                         *
 *  Purpose:                                                                  *
 *      Creates a 3D vector from "rectangular", or Cartesian, coordinates.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x-component of the vector.                                    *
 *      y (double):                                                           *
 *          The y-component of the vector.                                    *
 *      z (double):                                                           *
 *          The z-component of the vector.                                    *
 *  Outputs:                                                                  *
 *      v (struct nbh_vec3):                                                  *
 *          The vector (x, y, z).                                             *
 *  Method:                                                                   *
 *      Set the individual components for the struct and return.              *
 ******************************************************************************/
NBH_INLINE struct nbh_vec3
nbh_vec3_rect(double x, double y, double z)
{
    /*  Declare necessary variables.                                          */
    struct nbh_vec3 v;

    /*  Set the components for the vector and return.                         */
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
/*  End of nbh_vec3_rect.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_add                                                          *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^3.                                              *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector.                                            *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      sum (struct nbh_vec3):                                                *
 *          The vector sum of v and w.                                        *
 *  Method:                                                                   *
 *      Vector addition is performed component-wise. That is, given two       *
 *      vectors v = (vx, vy, vz) and w = (wx, wy, wz), the sum is:            *
 *                                                                            *
 *          sum = v + w                                                       *
 *              = (vx, vy, vz) + (wx, wy, wz)                                 *
 *              = (vx + wx, vy + wy, vz + wz)                                 *
 *                                                                            *
 *      This is computed and the sum is returned.                             *
 ******************************************************************************/
NBH_INLINE struct nbh_vec3
nbh_vec3_add(const struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec3 sum;

    /*  Vector addition is performed component-wise.                          */
    sum.x = v->x + w->x;
    sum.y = v->y + w->y;
    sum.z = v->z + w->z;
    return sum;
}
/*  End of nbh_vec3_add.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_addto                                                        *
 *  Purpose:                                                                  *
 *      Adds two vectors in R^3 and stores the result in the first variable.  *
 *  Arguments:                                                                *
 *      v (struct nbh_vec3 *):                                                *
 *          A pointer to a vector. The sum is stored here.                    *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void):                                                          *
 *  Method:                                                                   *
 *      Perform vector addition component-wise and store the result in v.     *
 ******************************************************************************/
NBH_INLINE void
nbh_vec3_addto(struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Vector addition is done component-wise. Store sum in the first vector.*/
    v->x += w->x;
    v->y += w->y;
    v->z += w->z;
}
/*  End of nbh_vec3_addto.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_subtract                                                     *
 *  Purpose:                                                                  *
 *      Subtracts two vectors in R^3.                                         *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector.                                            *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      diff (struct nbh_vec3):                                               *
 *          The vector difference of v and w, v - w.                          *
 *  Method:                                                                   *
 *      Vector subtraction is performed component-wise. That is, given two    *
 *      vectors v = (vx, vy, vz) and w = (wx, wy, wz), the difference is:     *
 *                                                                            *
 *          diff = v - w                                                      *
 *               = (vx, vy, vz) - (wx, wy, wz)                                *
 *               = (vx - wx, vy - wy, vz - wz)                                *
 *                                                                            *
 *      This is computed and the difference is returned.                      *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nbh_vec3_subtract(&v, &w)      *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
NBH_INLINE struct nbh_vec3
nbh_vec3_subtract(const struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec3 diff;

    /*  Vector subtraction is performed component-wise.                       */
    diff.x = v->x - w->x;
    diff.y = v->y - w->y;
    diff.z = v->z - w->z;
    return diff;
}
/*  End of nbh_vec3_subtract.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_subtractfrom                                                 *
 *  Purpose:                                                                  *
 *      Subtracts two vectors and stores the result in the first variable.    *
 *  Arguments:                                                                *
 *      v (struct nbh_vec3 *):                                                *
 *          A pointer to a vector. The difference is stored here.             *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void):                                                          *
 *  Method:                                                                   *
 *      Perform vector subtraction component-wise and store the result in v.  *
 *  Notes:                                                                    *
 *      Vector subtraction is not commutative. nbh_vec3_subtractfrom(&v, &w)  *
 *      computes the difference v - w (and not w - v).                        *
 ******************************************************************************/
NBH_INLINE void
nbh_vec3_subtractfrom(struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Store the difference in the first vector.                             */
    v->x -= w->x;
    v->y -= w->y;
    v->z -= w->z;
}
/*  End of nbh_vec3_subtractfrom.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_scale                                                        *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication.                                       *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector.                                            *
 *  Outputs:                                                                  *
 *      prod (struct nbh_vec3):                                               *
 *          The scalar product a*v.                                           *
 *  Method:                                                                   *
 *      Scalar multiplication is performed component-wise. That is, if v is   *
 *      the vector v = (x, y, z), then the product is:                        *
 *                                                                            *
 *          prod = a*v                                                        *
 *               = a*(x, y, z)                                                *
 *               = (a*x, a*y, a*z)                                            *
 *                                                                            *
 *      This is computed and the product is returned.                         *
 ******************************************************************************/
NBH_INLINE struct nbh_vec3
nbh_vec3_scale(double a, const struct nbh_vec3 *v)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec3 prod;

    /*  Scalar multiplication is done component-wise.                         */
    prod.x = a*v->x;
    prod.y = a*v->y;
    prod.z = a*v->z;
    return prod;
}
/*  End of nbh_vec3_scale.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_scaleby                                                      *
 *  Purpose:                                                                  *
 *      Performs scalar multiplication and stores the result in place.        *
 *  Arguments:                                                                *
 *      a (double):                                                           *
 *          A real number.                                                    *
 *      v (struct nbh_vec3 *):                                                *
 *          A pointer to a vector. The product is stored here.                *
 *  Outputs:                                                                  *
 *      None (void):                                                          *
 *  Method:                                                                   *
 *      Perform scalar multiplication component-wise, storing the result in v.*
 ******************************************************************************/
NBH_INLINE void
nbh_vec3_scaleby(double a, struct nbh_vec3 *v)
{
    /*  Scalar multiplication is done component-wise.                         */
    v->x *= a;
    v->y *= a;
    v->z *= a;
}
/*  End of nbh_vec3_scaleby.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_dot_product                                                  *
 *  Purpose:                                                                  *
 *      Performs the Euclidean dot product in R^3.                            *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector.                                            *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      dot (double):                                                         *
 *          The dot product v . w.                                            *
 *  Method:                                                                   *
 *      The Euclidean dot product sums the products of the components. Given  *
 *      two vectors v = (vx, vy, vz) and w = (wx, wy, wz), the dot product is:*
 *                                                                            *
 *          v.w = (vx, vy, vz) . (wx, wy, wz)                                 *
 *              = vx*wx + vy*wy + vz*wz                                       *
 *                                                                            *
 *      This is computed and the sum of products is returned.                 *
 ******************************************************************************/
NBH_INLINE double
nbh_vec3_dot_product(const struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  The dot product is the sum of the products of the components.         */
    return v->x*w->x + v->y*w->y + v->z*w->z;
}
/*  End of nbh_vec3_dot_product.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_cross_product                                                *
 *  Purpose:                                                                  *
 *      Performs the Euclidean cross product in R^3.                          *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector.                                            *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      cross (struct nbh_vec3):                                              *
 *          The cross product v x w.                                          *
 *  Method:                                                                   *
 *      The Euclidean cross is given by the right-hand rule. v x w is the     *
 *      the unique vector orthogonal to v and w with right-handed orientation *
 *      and magnitude given by ||v|| ||w|| sin(theta), theta being the angle  *
 *      between v and w. This can be computed explicitly as follows. Given    *
 *      v = (vx, vy, vz) and w = (wx, wy, wz), the cross product is:          *
 *                                                                            *
 *          cross = v x w                                                     *
 *                = (vx, vy, vz) x (wx, wy, wz)                               *
 *                = (vy*wz - wz*vy, vz*wx - vx*wz, vx*wy - vy*wx)             *
 *                                                                            *
 *      These components are computed and the cross product is returned.      *
 ******************************************************************************/
NBH_INLINE struct nbh_vec3
nbh_vec3_cross_product(const struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    struct nbh_vec3 cross;

    /*  Compute each component of the cross product and return.               */
    cross.x = v->y*w->z - v->z*w->y;
    cross.y = v->z*w->x - v->x*w->z;
    cross.z = v->x*w->y - v->y*w->x;
    return cross;
}
/*  End of nbh_vec3_cross_product.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_crosswith                                                    *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vector in-place.                    *
 *  Arguments:                                                                *
 *      v (struct nbh_vec3 *):                                                *
 *          A pointer to a vector. The cross product is stored here.          *
 *      w (const struct nbh_vec3 *):                                          *
 *          Another pointer to a vector.                                      *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Compute the cross product component-wise and store the resut in v.    *
 ******************************************************************************/
NBH_INLINE void
nbh_vec3_crosswith(struct nbh_vec3 *v, const struct nbh_vec3 *w)
{
    /*  Naively computing the cross product and storing the result in v will  *
     *  cause overwrite problems and we will not get the correct result. To   *
     *  avoid this first save the x and y components of v before computing.   */
    const double x = v->x;
    const double y = v->y;

    /*  Perform the cross product component-wise.                             */
    v->x = y*w->z - v->z*w->y;
    v->y = v->z*w->x - x*w->z;
    v->z = x*w->y - y*w->x;
}
/*  End of nbh_vec3_crosswith.                                                */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_norm                                                         *
 *  Purpose:                                                                  *
 *      Computes the Euclidean, or L2, norm of a vector in R^3.               *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector in R^3.                                     *
 *  Outputs:                                                                  *
 *      norm_v (double):                                                      *
 *          The norm, or magnitude, or length of the vector v.                *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          ||v|| = ||(x, y, z)||                                             *
 *                = sqrt(x^2 + y^2 + z^2)                                     *
 *                                                                            *
 *      Compute and return the norm.                                          *
 *  Notes:                                                                    *
 *      This function does not use any fancy tricks to avoid overflow. For    *
 *      most implementations of double, if x, y, or z has a magnitude greater *
 *      than ~10^154, the sum of the squares will overflow and the result is  *
 *      infinite. Such large numbers do not occur in this mini-project.       *
 ******************************************************************************/
NBH_INLINE double
nbh_vec3_norm(const struct nbh_vec3 *v)
{
    /*  Use Pythagoras and compute the square root of the sum of the squares. */
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}
/*  End of nbh_vec3_norm.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_normsq                                                       *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean, or L2, norm for vectors in R^3. *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector in R^3.                                     *
 *  Outputs:                                                                  *
 *      normsq_v (double):                                                    *
 *          The square of the norm, or magnitude, or length of the vector v.  *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          ||v||^2 = ||(x, y, z)||^2                                         *
 *                  = x^2 + y^2 + z^2                                         *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
NBH_INLINE double
nbh_vec3_normsq(const struct nbh_vec3 *v)
{
    /*  Use Pythagoras and compute.                                           */
    return v->x*v->x + v->y*v->y + v->z*v->z;
}
/*  End of nbh_vec3_normsq.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_rho                                                          *
 *  Purpose:                                                                  *
 *      Computes the magnitude of the azimuthal part of a vector.             *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector in R^3.                                     *
 *  Outputs:                                                                  *
 *      rho (double):                                                         *
 *          The magnitude of the azimuthal part of v. This is the cylindrical *
 *          radius of v in cylindrical coordinates.                           *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          rho = ||(x, y)||                                                  *
 *              = sqrt(x^2 + y^2)                                             *
 *                                                                            *
 *      Compute and return.                                                   *
 *  Notes:                                                                    *
 *      This function does not use any fancy tricks to avoid overflow. For    *
 *      most implementations of double, if x or y has a magnitude greater     *
 *      than ~10^154, the sum of the squares will overflow and the result is  *
 *      infinite. Such large numbers do not occur in this mini-project.       *
 ******************************************************************************/
NBH_INLINE double
nbh_vec3_rho(const struct nbh_vec3 *v)
{
    /*  Use Pythagoras and compute the square root of the sum of the squares. */
    return sqrt(v->x*v->x + v->y*v->y);
}
/*  End of nbh_vec3_rho.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_vec3_rhosq                                                        *
 *  Purpose:                                                                  *
 *      Computes the square of the azimuthal part of a vector.                *
 *  Arguments:                                                                *
 *      v (const struct nbh_vec3 *):                                          *
 *          A pointer to a vector in R^3.                                     *
 *  Outputs:                                                                  *
 *      rho (double):                                                         *
 *          The square of the azimuthal part of v.                            *
 *  Method:                                                                   *
 *      Use the Pythagorean theorem to compute. Given v = (x, y, z) we have:  *
 *                                                                            *
 *          rho^2 = ||(x, y)||^2                                              *
 *                = x^2 + y^2                                                 *
 *                                                                            *
 *      Compute and return.                                                   *
 ******************************************************************************/
NBH_INLINE double
nbh_vec3_rhosq(const struct nbh_vec3 *v)
{
    /*  Use Pythagoras and compute.                                           */
    return v->x*v->x + v->y*v->y;
}
/*  End of nbh_vec3_rhosq.                                                    */

#endif
/*  End of include guard.                                                     */
