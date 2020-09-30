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
#ifndef _KISSVG_MATH_H_
#define _KISSVG_MATH_H_

/*  It is assumed your compiler/implementation has support for the C99 math.h *
 *  header file which has more functions than the C89 math.h header. This     *
 *  includes float/long double support for many functions like sin, cos, fabs *
 *  more, defining them as sinf, sinl, cosf, cosl, fabsf, fabsl, etc. If you  *
 *  do NOT have the C99 math.h available but do have C89 math.h, then you     *
 *  must #undef the macro __HAS_C99_MATH_H__ or comment it out.               */

/*  Assuming you have C89 math.h, so defining the macro __HAS_C99_MATH_H__ to *
 *  be zero.                                                                  */
#ifndef __HAS_C99_MATH_H__
#define __HAS_C99_MATH_H__ 0
#endif

/*  This number is needed for computing the smallest value which will yield   *
 *  INFINITY or HUGE_VAL with the exponential function.                       */
#define NATURAL_LOG_OF_10 2.302585092994045684017991

/*  Include the standard library header math.h. We're only going to alias     *
 *  functions we ever use in rss_ringoccs, sin, cos, fabs, exp, atan2.        */
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
#ifdef kissvg_SinFloat
#undef kissvg_SinFloat
#endif
#ifdef kissvg_SinDouble
#undef kissvg_SinDouble
#endif
#ifdef kissvg_SinLongDouble
#undef kissvg_SinLongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#if (__HAS_C99_MATH_H__ == 1)
#define kissvg_SinFloat(x) sinf(x)
#define kissvg_SinDouble(x) sin(x)
#define kissvg_SinLongDouble(x) sinl(x)
#else
#define kissvg_SinFloat(x) sin((double)x)
#define kissvg_SinDouble(x) sin(x)
#define kissvg_SinLongDouble(x) sin((double)x)
#endif

/*  Aliases for the cosine trig function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef kissvg_CosFloat
#undef kissvg_CosFloat
#endif
#ifdef kissvg_CosDouble
#undef kissvg_CosDouble
#endif
#ifdef kissvg_CosLongDouble
#undef kissvg_CosLongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#if (__HAS_C99_MATH_H__ == 1)
#define kissvg_CosFloat(x) cosf(x)
#define kissvg_CosDouble(x) cos(x)
#define kissvg_CosLongDouble(x) cosl(x)
#else
#define kissvg_CosFloat(x) cos((double)x)
#define kissvg_CosDouble(x) cos(x)
#define kissvg_CosLongDouble(x) cos((double)x)
#endif

/*  Aliases for the square root function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef kissvg_SqrtFloat
#undef kissvg_SqrtFloat
#endif
#ifdef kissvg_SqrtDouble
#undef kissvg_SqrtDouble
#endif
#ifdef kissvg_SqrtLongDouble
#undef kissvg_SqrtLongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#if (__HAS_C99_MATH_H__ == 1)
#define kissvg_SqrtFloat(x) sqrtf(x)
#define kissvg_SqrtDouble(x) sqrt(x)
#define kissvg_SqrtLongDouble(x) sqrtl(x)
#else
#define kissvg_SqrtFloat(x) sqrt((double)x)
#define kissvg_SqrtDouble(x) sqrt(x)
#define kissvg_SqrtLongDouble(x) sqrt((double)x)
#endif

/*  Aliases for the exponential function found in math.h. First, undef these  *
 *  names if they're already in use to preventing #define'ing twice.          */
#ifdef kissvg_ExpFloat
#undef kissvg_ExpFloat
#endif
#ifdef kissvg_ExpDouble
#undef kissvg_ExpDouble
#endif
#ifdef kissvg_ExpLongDouble
#undef kissvg_ExpLongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#if (__HAS_C99_MATH_H__ == 1)
#define kissvg_ExpFloat(x) expf(x)
#define kissvg_ExpDouble(x) exp(x)
#define kissvg_ExpLongDouble(x) expl(x)
#else
#define kissvg_ExpFloat(x) exp((double)x)
#define kissvg_ExpDouble(x) exp(x)
#define kissvg_ExpLongDouble(x) exp((double)x)
#endif

/*  Aliases for the absolute value function found in math.h. First, undef     *
 *  these names if they're already in use to preventing #define'ing twice.    */
#ifdef kissvg_AbsFloat
#undef kissvg_AbsFloat
#endif
#ifdef kissvg_AbsDouble
#undef kissvg_AbsDouble
#endif
#ifdef kissvg_AbsLongDouble
#undef kissvg_AbsLongDouble
#endif

/*  Set aliases depending on if __HAS_C99_MATH_H__ is defined.                */
#if (__HAS_C99_MATH_H__ == 1)
#define kissvg_AbsFloat(x) fabsf(x)
#define kissvg_AbsDouble(x) fabs(x)
#define kissvg_AbsLongDouble(x) fabsl(x)
#else
#define kissvg_AbsFloat(x) fabs((double)x)
#define kissvg_AbsDouble(x) fabs(x)
#define kissvg_AbsLongDouble(x) fabs((double)x)
#endif

#ifdef kissvg_Infinity
#undef kissvg_Infinity
#endif

#ifndef INFINITY
#define kissvg_Infinity HUGE_VAL
#else
#define kissvg_Infinity INFINITY
#endif

#ifdef kissvg_IsInf
#undef kissvg_IsInf
#endif
#define kissvg_IsInf(x) (x == (x+1))

#ifdef kissvg_NaN
#undef kissvg_NaN
#endif

#ifndef NAN
#define kissvg_NaN (HUGE_VAL * 0.0)
#else
#define kissvg_NaN NAN
#endif

#ifdef kissvg_IsNaN
#undef kissvg_IsNaN
#endif
#define kissvg_IsNaN(x) (x != x)

#endif
/*  End of include guard.                                                     */
