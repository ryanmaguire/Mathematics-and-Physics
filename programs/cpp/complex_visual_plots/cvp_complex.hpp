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
 *      Provides a complex number class.                                      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/16                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef CVP_COMPLEX_HPP
#define CVP_COMPLEX_HPP

/*  FILE, fprintf, and fputc found here.                                      */
#include <cstdio>

/*  sqrt function and more found here.                                        */
#include <cmath>

/*  Namespace for the project. "complex visual plots."                        */
namespace cvp {

    /*  Class for working with complex numbers (doesn't use std::complex).    */
    class complex {
        public:
            /*  The data is the real and imaginary parts of the number.       */
            double real, imag;

            /*  Empty constructor.                                            */
            complex(void);

            /*  Constructor from the real and imaginary parts.                */
            complex(double x, double y);

            /*  Returns the real part of the class.                           */
            inline double re(void);

            /*  Returns the imaginary part of the class.                      */
            inline double im(void);

            /*  Computes the complex conjugate of z.                          */
            inline complex conjugate(void);

            /*  Computes the complex conjugate and stores the result in z.    */
            inline void conjugateself(void);

            /*  Method for computing the inverse of z.                        */
            inline complex rcpr(void);

            /*  Method for inverting z and storing the result in z.           */
            inline void invert(void);

            /*  Method for computing the square of the modulus.               */
            inline double abssq(void);

            /*  Method for computing the modulus of a complex number.         */
            inline double abs(void);

            /*  Method for computing the argument of a complex number.        */
            inline double arg(void);
    };
    /*  End of "complex" class.                                               */
}
/*  End of namespace "cvp".                                                   */

/*  Empty constructor, simply return.                                         */
cvp::complex::complex(void)
{
    return;
}

/*  Constructor from the real and imaginary parts.                            */
cvp::complex::complex(double x, double y)
{
    real = x;
    imag = y;
}

/*  Returns the real part of the class.                                       */
inline double cvp::complex::re(void)
{
    return real;
}

/*  Returns the imaginary part of the class.                                  */
inline double cvp::complex::im(void)
{
    return imag;
}

/*  Complex addition. This is performed component-wise.                       */
inline cvp::complex operator + (cvp::complex z, cvp::complex w)
{
    return cvp::complex(z.real + w.real, z.imag + w.imag);
}

/*  Addition of a real and complex number. Add to the real part of z.         */
inline cvp::complex operator + (cvp::complex z, double a)
{
    return cvp::complex(z.real + a, z.imag);
}

/*  Addition of a real and complex number. Add to the real part of z.         */
inline cvp::complex operator + (double a, cvp::complex z)
{
    return cvp::complex(a + z.real, z.imag);
}

/*  Subtraction of complex numbers. Subtract component-wise.                  */
inline cvp::complex operator - (cvp::complex z, cvp::complex w)
{
    return cvp::complex(z.real - w.real, z.imag - w.imag);
}

/*  Subtraction of a complex number and a real one. Subtract real part.       */
inline cvp::complex operator - (cvp::complex z, double a)
{
    return cvp::complex(z.real - a, z.imag);
}

/*  Subtraction of a real number and complex one. Negate complex number.      */
inline cvp::complex operator - (double a, cvp::complex z)
{
    return cvp::complex(a - z.real, -z.imag);
}

/*  Multiplication of two complex number. Compute using i^2 = -1.             */
inline cvp::complex operator * (cvp::complex z, cvp::complex w)
{
    const double real = z.real*w.real - z.imag*w.imag;
    const double imag = z.real*w.imag + z.imag*w.real;
    return cvp::complex(real, imag);
}

/*  Multiplication of a real and complex number. Scale the components.        */
inline cvp::complex operator * (double a, cvp::complex z)
{
    return cvp::complex(a*z.real, a*z.imag);
}

/*  Multiplication of a real and complex number. Scale the components.        */
inline cvp::complex operator * (cvp::complex z, double a)
{
    return cvp::complex(z.real*a, z.imag*a);
}

/*  Division of complex numbers. Use z^{-1} = conj(z) / |z|^2.                */
inline cvp::complex operator / (cvp::complex z, cvp::complex w)
{
    const double denom = 1.0 / (w.real*w.real + w.imag*w.imag);
    const double real = z.real*w.real + z.imag*w.imag;
    const double imag = z.imag*w.real - z.real*w.imag;
    return cvp::complex(real*denom, imag*denom);
}

/*  Division of complex and real numbers. Divide component-wise.              */
inline cvp::complex operator / (cvp::complex z, double a)
{
    /*  Compute the reciprocal and scale the real and imaginary parts.        */
    const double rcpr = 1.0 / a;
    return cvp::complex(z.real * rcpr, z.imag * rcpr);
}

/*  Division of a complex number and real number. Compute z^{-1} and scale.   */
inline cvp::complex operator / (double a, cvp::complex z)
{
    const double denom = 1.0 / (z.real*z.real + z.imag*z.imag);
    return cvp::complex(a*z.real*denom, -a*z.imag*denom);
}

/*  Computes the complex conjugate of the class.                              */
inline cvp::complex cvp::complex::conjugate(void)
{
    /*  The complex conjugate negates the imaginary part.                     */
    return cvp::complex(real, -imag);
}

/*  Conjugates the class and stores the result in itself.                     */
inline void cvp::complex::conjugateself(void)
{
    /*  We only need to negate the imaginary part.                            */
    imag = -imag;
}

/*  Computes the reciprocal, or inverse, of a complex number.                 */
inline cvp::complex cvp::complex::rcpr(void)
{
    /*  The inverse can be computed via conj(z) / |z|^2.                      */
    const double denom = 1.0 / (real*real + imag*imag);
    return cvp::complex(real*denom, -imag*denom);
}

/*  Computes the reciprocal, or inverse, of a complex number.                 */
inline void cvp::complex::invert(void)
{
    /*  The inverse can be computed via conj(z) / |z|^2.                      */
    const double denom = 1.0 / (real*real + imag*imag);
    real *= denom;
    imag *= -denom;
}

/*  Computes the square of the modulus of a complex number.                   */
inline double cvp::complex::abssq(void)
{
    return real*real + imag*imag;
}

/*  Computes the modulus of a complex number.                                 */
inline double cvp::complex::abs(void)
{
    /*  Use the Pythagoras formula on the vector (real, imag).                */
    return std::sqrt(real*real + imag*imag);
}

/*  Computes the argument, or azimuthal angle, of the complex number.         */
inline double cvp::complex::arg(void)
{
    /*  Treat z as a vector (real, imag) and compute the azimuthal angle.     */
    return std::atan2(imag, real);
}

#endif
/*  End of include guard.                                                     */
