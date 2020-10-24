/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************
 *                              kissvg_complex                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Define kissvg_ComplexDouble data type and provide various             *
 *      functions for creating complex variables and performing basic         *
 *      arithmetic. If complex.h is available, we simply #include this.       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) complex.h (if your compiler supports C99. None otherwise):            *
 *      Standard library for complex types.                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef _KISSVG_COMPLEX_H_
#define _KISSVG_COMPLEX_H_

/*  C99 requires complex.h, but C11 makes it optional. If you are using a     *
 *  compiler that supports the C99 standard, we can just #include complex.h.  *
 *  If you're compiler supports the C11 standard, we should check that the    *
 *  __STDC_NO_COMPLEX__ macro is not set. If both are true, we have support   *
 *  for complex.h and we should just make aliases for the various routines.   */
#if __STDC_VERSION__ >= 199001L && !defined(__STDC_NO_COMPLEX__)

#include <complex.h>
typedef double _Complex kissvg_ComplexDouble;
#define kissvg_ComplexAbs cabs
#define kissvg_ComplexRealPart creal
#define kissvg_ComplexImagPart cimag
#define kissvg_ComplexExp cexp
#define kissvg_ComplexSqrt csqrt
#define kissvg_ComplexConjugate cong
#define kissvg_ImaginaryUnit _Complex_I
#define kissvg_ComplexZero 0.0
#define kissvg_ComplexOne 1.0

/*  Your compiler does not support complex.h, so we'll create a complex       *
 *  variable data type and some useful functions.                             */
#else

/*  The GNU Scientific Library (GSL) v2.6 defined complex variables via a     *
 *  data structure containing a single array double dat[2];. If you are using *
 *  the GSL v2.6, you can use rss_ringoccs functions with that library.       *
 *  NOTE:                                                                     *
 *      You should never try to access the elements of kissvg_ComplexDouble   *
 *      directly via z.dat[0] or z.dat[1]. For one, if your compiler supports *
 *      complex.h, then kissvg_ComplexDouble is just an alias for the         *
 *      built-in double _Complex type. Secondly, functions for accessing and  *
 *      manipulating the data are provided and their use adds clarity to code.*/
typedef struct kissvg_ComplexDouble {
    double dat[2];
} kissvg_ComplexDouble;

/*  This function is equivalent to the cabs function in complex.h (C99).      */
extern double kissvg_ComplexAbs(kissvg_ComplexDouble z);

/*  Equivalents of creal and cimag functions in complex.h (C99).              */
extern double kissvg_ComplexRealPart(kissvg_ComplexDouble z);
extern double kissvg_ComplexImagPart(kissvg_ComplexDouble z);

/*  Equivalents of cexp and cqrt. Note, our csqrt only computes the           *
 *  principal square root, and so it assumes your polar representation of     *
 *  z has -pi < theta < pi. Because of this there is a branch cut along the   *
 *  negative real axis.                                                       */
extern kissvg_ComplexDouble kissvg_ComplexExp(kissvg_ComplexDouble z);
extern kissvg_ComplexDouble kissvg_ComplexSqrt(kissvg_ComplexDouble z);

/*  Function for computating the complex conjugate. Equivalent to conj if     *
 *  complex.h is available.                                                   */
extern kissvg_ComplexDouble kissvg_ComplexConjugate(kissvg_ComplexDouble z);

const kissvg_ComplexDouble kissvg_ImaginaryUnit = {{0.0, 1.0}};
const kissvg_ComplexDouble kissvg_ComplexZero   = {{0.0, 0.0}};
const kissvg_ComplexDouble kissvg_ComplexOne    = {{1.0, 0.0}};
#endif

/*  In C99 you can simply do double _Complex z = x + _Complex_I*y since       *
 *  complex variables are primitive data types, but in C89 we need to create  *
 *  a struct for them (as above). Structs can't be added, so we need a        *
 *  function for creating a complex number from two doubles.                  */
extern kissvg_ComplexDouble kissvg_ComplexRect(double x, double y);

/*  Return a complex data type from its polar expression.                     */
extern kissvg_ComplexDouble rssringoccs_ComplexPolar(double r, double theta);

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 + z2. Structs can't be added,  *
 *  so we need a function for computing the sum of two complex values.        */
extern kissvg_ComplexDouble
kissvg_ComplexAdd(kissvg_ComplexDouble z1, kissvg_ComplexDouble z2);

extern kissvg_ComplexDouble
kissvg_ComplexSubtract(kissvg_ComplexDouble z1, kissvg_ComplexDouble z2);

extern kissvg_ComplexDouble
kissvg_ComplexMultiply(kissvg_ComplexDouble z1, kissvg_ComplexDouble z2);

extern kissvg_ComplexDouble kissvg_ComplexReciprocal(kissvg_ComplexDouble z);

extern kissvg_ComplexDouble
kissvg_ComplexDivide(kissvg_ComplexDouble z1, kissvg_ComplexDouble z2);

extern kissvg_ComplexDouble
kissvg_ComplexScale(double x, kissvg_ComplexDouble z);

extern kissvg_ComplexDouble
kissvg_PoincareDiskMobiusTransform(kissvg_ComplexDouble z,
                                   kissvg_ComplexDouble w);

extern kissvg_ComplexDouble
kissvg_PoincareDiskInverseMobiusTransform(kissvg_ComplexDouble z,
                                          kissvg_ComplexDouble w);

#endif
/*  End of include guard.                                                     */
