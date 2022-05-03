/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This is part of a set of files I made while studying from Peter       *
 *      Shirley's "Ray Tracing in One Weekend", Copyright 2018-2020, Peter    *
 *      Shirley, All rights reserved. The code is my own, but follows the     *
 *      ideas laid out in the text.                                           *
 *                                                                            *
 *      This file presents a basic struct used to represent vectors.          *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/
 
/*  The C++ equivalent of math.h. sqrt is found here.                         */
#include <cmath>

/*  And the equivalent of stdio.h.                                            */
#include <cstdio>

/*  Struct used to represents vectors in R^3.                                 */
struct tmpl_simple_vector {

    /*  The data in a vector is it's Euclidean components.                    */
    double x, y, z;

    /*  Empty constructor. Do not set any of the variables, simply return.    */
    tmpl_simple_vector(void)
    {
        return;
    }
 
    /*  Constructor from three doubles. Set the components to the inputs.     */ 
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
    
    /*  Define the basic operators for the vector. First is vector addition.  */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }
    
    /*  Vector subtraction.                                                   */
    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
    }
    
    /*  Vector negation.                                                      */
    tmpl_simple_vector operator - (void)
    {
        return tmpl_simple_vector(-x, -y, -z);
    }

    /*  Scalar multiplication.                                                */
    tmpl_simple_vector operator * (double a)
    {
        return tmpl_simple_vector(a*x, a*y, a*z);
    }
    
    /*  Scalar division.                                                      */
    tmpl_simple_vector operator / (double a)
    {
        return tmpl_simple_vector(x/a, y/a, z/a);
    }

    /*  Euclidean norm (the length of the vector).                            */    
    double norm(void)
    {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    /*  Square of the Euclidean norm.                                         */
    double normsq(void)
    {
        return x*x + y*y + z*z;
    }

    /*  Euclidean dot product.                                                */
    double dot(tmpl_simple_vector r)
    {
        return r.x*x + r.y*y + r.z*z;
    }
    
    /*  Euclidean cross product in three dimensions.                          */
    tmpl_simple_vector cross(tmpl_simple_vector r)
    {
        return tmpl_simple_vector(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
    }
    
    /*  Unit vector for the given vector.                                     */
    tmpl_simple_vector unit(void)
    {
        return *this / (*this).norm();
    }

    /*  Simple function for printing out the values of the vector.            */
    void print(void)
    {
        std::printf("<%f, %f, %f>", x, y, z);
    }
};
/*  End of tmpl_simple_vector struct.                                         */

/*  Test the tools provided with this struct.                                 */
int main(void)
{
    tmpl_simple_vector p = tmpl_simple_vector(1, 2, 3);
    tmpl_simple_vector q = tmpl_simple_vector(2, 1, 0);
    tmpl_simple_vector s = p.cross(q);

    std::printf("p           = ");
    p.print();
    std::printf("\n");

    std::printf("-p          = ");
    (-p).print();
    std::printf("\n");

    std::printf("q           = ");
    q.print();
    std::printf("\n");

    s = p + q;
    std::printf("p + q       = ");
    s.print();
    std::printf("\n");

    s = p - q;
    std::printf("p - q       = ");
    s.print();
    std::printf("\n");
    
    s = p.cross(q);
    std::printf("p x q       = ");
    s.print();
    std::printf("\n");
    
    printf("p * q       = %f\n", p.dot(q));
    printf("(p x q) * p = %f\n", p.dot(s));
    printf("(p x q) * q = %f\n", q.dot(s));
    
    p = p.unit();
    std::printf("p_hat       = ");
    p.print();
    std::printf("\n");

    q = q.unit();
    std::printf("q_hat       = ");
    q.print();
    std::printf("\n");
    
    printf("||p_hat||   = %f\n", p.norm());
    printf("||q_hat||   = %f\n", q.norm());
    return 0;
}
/*  End of main.                                                              */

