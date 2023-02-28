/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_VECTOR_H
#define NBH_VECTOR_H

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

        /*  Method for computing the dot product with another vector.         */
        inline double dot(const vec3 &v) const;

        /*  Method for computing the Euclidean, or L2, norm of the vector.    */
        inline double norm(void) const;

        /*  Method for the square of the norm. Removes redundant square root. */
        inline double normsq(void) const;
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

    /*  Operator for the dot product, for shorthand use.                      */
    inline double operator % (const vec3 &v, const vec3 &u)
    {
        return v.dot(u);
    }

    /*  Dot product, defined as the sum of the component-wise products.       */
    inline double vec3::dot(const vec3 &v) const
    {
        return v.x*x + v.y*y + v.z*z;
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double vec3::norm(void) const
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double vec3::normsq(void) const
    {
        return x*x + y*y + z*z;
    }
}
/*  End of namespace nbh.                                                     */

#endif
/*  End of include guard.                                                     */
