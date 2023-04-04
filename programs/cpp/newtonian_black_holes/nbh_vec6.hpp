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
 *      Provides a basic double-precision 6D vector struct (not a class).     *
 *      Used for working in phase space (position, velocity).                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/04                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_VEC6_HPP
#define NBH_VEC6_HPP

/*  3D vectors found here. A 6D vector is two 3D vectors.                     */
#include "nbh_vec3.hpp"

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  A structure for dealing with vectors in R^6. These are thought of as  *
     *  two vectors in R^3, a position vector and a velocity vector.          */
    struct vec6 {

        /*  A vector is defined by its 3D position and 3D velocity.           */
        nbh::vec3 p, v;

        /*  Empty constructor.                                                */
        vec6(void);

        /*  Simple method for creating a vector from the components.          */
        vec6(double x, double y, double z, double vx, double vy, double vz);

        /*  Simple method for creating a vector from two 3D vectors.          */
        vec6(const nbh::vec3 &pos, const nbh::vec3 &vel);

        /*  Operator for vector addition.                                     */
        inline void operator += (const vec6 &u);

        /*  Operator for vector subtraction.                                  */
        inline void operator -= (const vec6 &u);

        /*  Operator for scalar multiplication.                               */
        inline void operator *= (double r);

        /*  Method for computing the dot product with another vector.         */
        inline double dot(const vec6 &u) const;

        /*  Method for computing the Euclidean, or L2, norm of the vector.    */
        inline double norm(void) const;

        /*  Method for the square of the norm. Removes redundant square root. */
        inline double normsq(void) const;
    };

    /*  Empty constructor. Do nothing, just return.                           */
    vec6::vec6(void)
    {
        return;
    }

    /*  Constructor from the Euclidean components.                            */
    vec6::vec6(double x, double y, double z, double vx, double vy, double vz)
    {
        /*  Set each of the components and return.                            */
        p.x = x;
        p.y = y;
        p.z = z;
        v.x = vx;
        v.y = vy;
        v.z = vz;
    }

    /*  Constructor from the position and velocity vectors.                   */
    vec6::vec6(const nbh::vec3 &pos, const nbh::vec3 &vel)
    {
        p = pos;
        v = vel;
    }

    /*  Vector addition, performed component-wise.                            */
    inline vec6 operator + (const vec6 &u0, const vec6 &u1)
    {
        /*  Use vector addition in R^3 and sum the components.                */
        return vec6(u0.p + u1.p, u0.v + u1.v);
    }

    /*  Vector addition where the result is stored in the first variable.     */
    inline void vec6::operator += (const vec6 &u)
    {
        /*  Use vector addition in R^3 and sum the components.                */
        p += u.p;
        v += u.v;
    }

    /*  Vector subtraction, performed component-wise.                         */
    inline vec6 operator - (const vec6 &u0, const vec6 &u1)
    {
        /*  Use vector subtraction in R^3 on each component.                  */
        return vec6(u0.p - u1.p, u0.v - u1.v);
    }

    /*  Vector subtraction where the result is stored in the first variable.  */
    inline void vec6::operator -= (const vec6 &u)
    {
        p -= u.p;
        v -= u.v;
    }

    /*  Scalar multiplication on the left.                                    */
    inline vec6 operator * (double a, const vec6 &u)
    {
        return vec6(a*u.p, a*u.v);
    }

    /*  Scalar multiplication on the right.                                   */
    inline vec6 operator * (const vec6 &u, double a)
    {
        return a*u;
    }

    /*  Scalar multiplication where the result is stored in the struct.       */
    inline void vec6::operator *= (double r)
    {
        p *= r;
        v *= r;
    }

    /*  Dot product, defined as the sum of the component-wise products.       */
    inline double vec6::dot(const vec6 &u) const
    {
        return p.dot(u.p) + v.dot(u.v);
    }

    /*  Operator for the dot product, for shorthand use.                      */
    inline double operator % (const vec6 &u0, const vec6 &u1)
    {
        return u0.dot(u1);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    inline double vec6::normsq(void) const
    {
        /*  Return the sum of the squares of the norms of the components.     */
        return p.normsq() + v.normsq();
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    inline double vec6::norm(void) const
    {
        return std::sqrt(this->normsq());
    }
}
/*  End of namespace nbh.                                                     */

#endif
/*  End of include guard.                                                     */
