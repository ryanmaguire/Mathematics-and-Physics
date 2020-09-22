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
 *                            rss_ringoccs_math                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This header file allows for compatibility of KissVG for users         *
 *      of the C89/C90 math.h header file, and the C99/C11 math.h. The later  *
 *      versions of math.h provide the following:                             *
 *          funcf:                                                            *
 *              Float version of func.                                        *
 *          funcl:                                                            *
 *              Long double version of func.                                  *
 *      For example, sinf, sinl, fabsf, fabsl, etc. The older C89/C90 math.h  *
 *      do not provide these functions, and rather if a function recieves a   *
 *      non-double (like passing a float to cos), then an implicit type       *
 *      conversion occurs, which may be computationally expensive. The funcf  *
 *      and funcl versions are meant to rid of this conversion step.          *
 *      For float and long double functions KissVG uses, if available,        *
 *      these functions. Here we provide aliases for the functions in math.h  *
 *      depending on whether or not the __HAS_C99_MATH_H__ macro is defined   *
 *      (it's defined in this file before the #include <math.h> statement).   *
 *      The functions have the following aliases if __HAS_C99_MATH_H__ is set:*
 *          Func_Float      = funcf                                           *
 *          Func_Double     = func                                            *
 *          Func_LongDouble = funcl                                           *
 *      If not, we do type conversion:                                        *
 *          Func_Float(x)      = func((double)x)                              *
 *          Func_Double(x)     = func(x)                                      *
 *          Func_LongDouble(x) = func((double)x)                              *
 *                                                                            *
 *      This also provides NAN and INFINITY macros if they are not set.       *
 *      NOTE:                                                                 *
 *          INFINITY is set as the standard macro HUGE_VAL defined in math.h  *
 *          and for most implementations this should do. Indeed, this is the  *
 *          same manner the Py_HUGE_VAL is set. The python source code issues *
 *          the following warning (cpython/Include/pymath.h):                 *
 *              HUGE_VAL is supposed to expand to a positive double infinity. *
 *              Python uses Py_HUGE_VAL instead because some platforms are    *
 *              broken in this respect.  We used to embed code in pyport.h to *
 *              try to worm around that, but different platforms are broken   *
 *              in conflicting ways.  If you're on a platform where HUGE_VAL  *
 *              is defined incorrectly, fiddle your Python config to          *
 *              #define Py_HUGE_VAL to something that works on your platform. *
 *                                                                            *
 *          Similarly, NAN is defined as HUGE_VAL * 0, which should be        *
 *          infinity times zero, which is Not-A-Number. Python does this as   *
 *          well, issuing the following warning:                              *
 *              Py_NAN                                                        *
 *              A value that evaluates to a NaN. On IEEE 754 platforms INF*0  *
 *              or INF/INF works. Define Py_NO_NAN in pyconfig.h if your      *
 *              platform doesn't support NaNs.                                *
 *          If necessary, redefine NAN here to whatever your platform allows. *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  If your implementation supports the C89/C90 math.h header file, and is    *
 *  lacking the extra function declarations, you will need to comment out the *
 *  #define __HAS_C99_MATH_H__ statement or you will have compiler errors.    *
 *  If HUGE_VAL and HUGE_VAL*0 don't correspond to infinity and nan,          *
 *  respectively, on your system you will need to alter those macros. This    *
 *  has worked on macOS and linux system when tested, however the GNU glibc   *
 *  implementation provides those macros already, so no extra effort needed.  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) math.h:                                                               *
 *      Standard library for mathematical functions like sin, cos, atan.      *
 *  2.) float.h:                                                              *
 *      Standard library which contains macros for the smallest and largest   *
 *      values allowed by your system.                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 21, 2020                                            *
 ******************************************************************************/

/*  Include guard for this file to prevent including this twice.              */
#ifndef _KISSVG_MATH_H
#define _KISSVG_MATH_H

/*  It is assumed your compiler/implementation has support for the C99 math.h *
 *  header file which has more functions than the C89 math.h header. This     *
 *  includes float/long double support for many functions like sin, cos, fabs *
 *  more, defining them as sinf, sinl, cosf, cosl, fabsf, fabsl, etc. If you  *
 *  do NOT have the C99 math.h available but do have C89 math.h, then you     *
 *  must #undef the macro __HAS_C99_MATH_H__ or comment it out.               */

/*  Assuming you have C99 math.h, so defining the macro __HAS_C99_MATH_H__.   */
#ifndef __HAS_C99_MATH_H__
#define __HAS_C99_MATH_H__ 1
#endif

/*  This number is needed for computing the smallest value which will yield   *
 *  INFINITY or HUGE_VAL with the exponential function.                       */
#define NATURAL_LOG_OF_10 2.302585092994045684017991

/*  Include the standard library header math.h. We're only going to alias     *
 *  functions we ever use in rss_ringoccs, sin, cos, fabs, exp, atan2.        */
#include <math.h>

/*  And this header file contains macros for the smallest and largest allowed *
 *  values for your system.                                                   */
#include <float.h>

/*  Macros for the largest values of float, double, and long double,          *
 *  respectively, that will not return INFINITY when exp(x) is computed.      */
#define MAX_FLOAT_BASE_E FLT_MAX_10_EXP*NATURAL_LOG_OF_10
#define MAX_DOUBLE_BASE_E DBL_MAX_10_EXP*NATURAL_LOG_OF_10
#define MAX_LDOUBLE_BASE_E LDBL_MAX_10_EXP*NATURAL_LOG_OF_10

/*  Aliases for the sine trig function found in math.h. First, undef these    *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef Sin_Float
#undef Sin_Float
#endif
#ifdef Sin_Double
#undef Sin_Double
#endif
#ifdef Sin_LongDouble
#undef Sin_LongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#ifdef __HAS_C99_MATH_H__
#define Sin_Float(x) sinf(x)
#define Sin_Double(x) sin(x)
#define Sin_LongDouble(x) sinl(x)
#else
#define Sin_Float(x) sin((double)x)
#define Sin_Double(x) sin(x)
#define Sin_LongDouble(x) sin((double)x)
#endif

/*  Aliases for the cosine trig function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef Cos_Float
#undef Cos_Float
#endif
#ifdef Cos_Double
#undef Cos_Double
#endif
#ifdef Cos_LongDouble
#undef Cos_LongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#ifdef __HAS_C99_MATH_H__
#define Cos_Float(x) cosf(x)
#define Cos_Double(x) cos(x)
#define Cos_LongDouble(x) cosl(x)
#else
#define Cos_Float(x) cos((double)x)
#define Cos_Double(x) cos(x)
#define Cos_LongDouble(x) cos((double)x)
#endif

/*  Aliases for the square root function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef Sqrt_Float
#undef Sqrt_Float
#endif
#ifdef Sqrt_Double
#undef Sqrt_Double
#endif
#ifdef Sqrt_LongDouble
#undef Sqrt_LongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#ifdef __HAS_C99_MATH_H__
#define Sqrt_Float(x) sqrtf(x)
#define Sqrt_Double(x) sqrt(x)
#define Sqrt_LongDouble(x) sqrtl(x)
#else
#define Sqrt_Float(x) sqrt((double)x)
#define Sqrt_Double(x) sqrt(x)
#define Sqrt_LongDouble(x) sqrt((double)x)
#endif

/*  Aliases for the exponential function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef Exp_Float
#undef Exp_Float
#endif
#ifdef Exp_Double
#undef Exp_Double
#endif
#ifdef Exp_LongDouble
#undef Exp_LongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#ifdef __HAS_C99_MATH_H__
#define Exp_Float(x) expf(x)
#define Exp_Double(x) exp(x)
#define Exp_LongDouble(x) expl(x)
#else
#define Exp_Float(x) exp((double)x)
#define Exp_Double(x) exp(x)
#define Exp_LongDouble(x) exp((double)x)
#endif

/*  Aliases for the absolute value function found in math.h. First, undef     *
 *  these names if they're already in use to preventing #define'ing twice.    */
#ifdef Abs_Float
#undef Abs_Float
#endif
#ifdef Abs_Double
#undef Abs_Double
#endif
#ifdef Abs_LongDouble
#undef Abs_LongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#ifdef __HAS_C99_MATH_H__
#define Abs_Float(x) fabsf(x)
#define Abs_Double(x) fabs(x)
#define Abs_LongDouble(x) fabsl(x)
#else
#define Abs_Float(x) fabs((double)x)
#define Abs_Double(x) fabs(x)
#define Abs_LongDouble(x) fabs((double)x)
#endif

/*  If INFINITY is not defined, set it to the HUGE_VAL macro that is          *
 *  specified in math.h. Most compilers already have an INFINITY macro, but   *
 *  it is not required in the C89 standard.                                   */
#ifndef INFINITY
#define INFINITY HUGE_VAL
#endif

/*  If NAN is not defined, we'll use the CPYTHON method of defining NAN, the  *
 *  source code of which is contained in python/cpython/Include/pymath.h.     */
#ifndef NAN
#define NAN (INFINITY * 0.0)
#endif

#endif
/*  End of include guard.                                                     */
