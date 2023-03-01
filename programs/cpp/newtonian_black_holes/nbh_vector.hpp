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
 *      Provides a basic double-precision 3D vector struct (not a class).     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_VECTOR_HPP
#define NBH_VECTOR_HPP

/*  sqrt found here.                                                          */
#include <cmath>

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  A structure for dealing with vectors. Vectors are treated as rays of  *
     *  light moving under the influence of the gravity of a black hole.      */
    struct vec3 {

        /*  A vector is defined by it's Euclidean components, x, y, z.        */
        double x, y, z;

        /*  Empty constructor.                                                */
        vec3(void);

        /*  Simple method for creating a vector from the components.          */
        vec3(double a, double b, double c);

        /*  Operator for vector addition.                                     */
        inline void operator += (const vec3 &v);

        /*  Operator for vector subtraction.                                  */
        inline void operator -= (const vec3 &v);

        /*  Operator for scalar multiplication.                               */
        inline void operator *= (double r);

        /*  Operator for the cross product.                                   */
        inline void operator ^= (const vec3 &u);

        /*  Method for computing the dot product with another vector.         */
        inline double dot(const vec3 &v) const;

        /*  Three-Dimensional Euclidean cross-product.                        */
        inline vec3 cross(const vec3 &v) const;

        /*  Cross-product where the result is stored in this struct.          */
        inline void crosswith(const vec3 &v);

        /*  Method for computing the Euclidean, or L2, norm of the vector.    */
        inline double norm(void) const;

        /*  Method for the square of the norm. Removes redundant square root. */
        inline double normsq(void) const;

        /*  Computes the azimuthal radius, sqrt(x^2 + y^2).                   */
        inline double rho(void) const;

        /*  Computes the square of the azimuthal radius, x^2 + y^2.           */
        inline double rhosq(void) const;
    };

    /*    Empty constructor. Do nothing, just return.                         */
    vec3::vec3(void)
    {
        return;
    }

    /*    Constructor from the Euclidean components.                          */
    vec3::vec3(double a, double b, double c)
    {
        /*  Set each of the components and return.                            */
        x = a;
        y = b;
        z = c;
    }

    /*  Vector addition, performed component-wise.                            */
    inline vec3 operator + (const vec3 &v, const vec3 &u)
    {
        return vec3(v.x + u.x, v.y + u.y, v.z + u.z);
    }

    /*  Vector addition where the result is stored in the first variable.     */
    inline void vec3::operator += (const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    /*  Vector subtraction, performed component-wise.                         */
    inline vec3 operator - (const vec3 &v, const vec3 &u)
    {
        return vec3(v.x - u.x, v.y - u.y, v.z - u.z);
    }

    /*  Vector subtraction where the result is stored in the first variable.  */
    inline void vec3::operator -= (const vec3 &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    /*  Scalar multiplication on the left.                                    */
    inline vec3 operator * (double a, const vec3 &v)
    {
        return vec3(a*v.x, a*v.y, a*v.z);
    }

    /*  Scalar multiplication on the right.                                   */
    inline vec3 operator * (const vec3 &v, double a)
    {
        return a*v;
    }

    /*  Scalar multiplication where the result is stored in the struct.       */
    inline void vec3::operator *= (double r)
    {
        x *= r;
        y *= r;
        z *= r;
    }

    /*  Dot product, defined as the sum of the component-wise products.       */
    inline double vec3::dot(const vec3 &v) const
    {
        return v.x*x + v.y*y + v.z*z;
    }

    /*  Operator for the dot product, for shorthand use.                      */
    inline double operator % (const vec3 &v, const vec3 &u)
    {
        return v.dot(u);
    }

    /*  Three-dimensional cross-product.                                      */
    inline vec3 vec3::cross(const vec3 &v) const
    {
        return vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    /*  Cross-product where the result is stored in the struct.               */
    inline void vec3::crosswith(const vec3 &v)
    {
        /*  Save these variables for later.                                   */
        const double a = x;
        const double b = y;

        /*  Compute the three components of the cross product.                */
        x = b*v.z - z*v.y;
        y = z*v.x - a*v.z;
        z = a*v.y - b*v.x;
    }

    /*  Shorthand operator for the cross-product. The "wedge" product is a    *
     *  generalization of the cross-product, so it is fitting to use ^.       */
    inline vec3 operator ^ (const vec3 &v, const vec3 &u)
    {
        return v.cross(u);
    }

    /*  Similar operator for the cross product. Result is stored in struct.   */
    inline void vec3::operator ^= (const vec3 &u)
    {
        this->crosswith(u);
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    inline double vec3::norm(void) const
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    inline double vec3::normsq(void) const
    {
        return x*x + y*y + z*z;
    }

    /*  Computes the azimuthal radius, sqrt(x^2 + y^2).                       */
    inline double vec3::rho(void) const
    {
        return std::sqrt(x*x + y*y);
    }

    /*  Computes the square of the azimuthal radius, x^2 + y^2.               */
    inline double vec3::rhosq(void) const
    {
        return x*x + y*y;
    }
}
/*  End of namespace nbh.                                                     */

#endif
/*  End of include guard.                                                     */
