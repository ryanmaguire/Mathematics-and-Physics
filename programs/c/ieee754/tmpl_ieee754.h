/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                               tmpl_ieee754                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains tools for manipulating floating point variables for          *
 *      platforms using the IEEE754 format (most do in 2021). All of this is  *
 *      experimental and mostly for the sake of learning, and is not directly *
 *      required for libtmpl. Uses of this header file include accurate       *
 *      and fast logarithmic functions, square roots, and more.               *
 *  NOTES:                                                                    *
 *      While the code is written in ANSI C, this is NOT portable since it    *
 *      assumes various things. This part of the code makes the following     *
 *      assumptions (as stated, use of this code is only optional):           *
 *          1.) Your platform uses IEEE754 format for floating point          *
 *              arithmetic. Most modern computers do.                         *
 *          2.) You have 32-bit float and 64-bit double. This is NOT          *
 *              required by the C89/C90 standard, only minimum sizes are      *
 *              specified. 32-bit/64-bit single and double precision is the   *
 *              most common, but this can break portability. Compilers        *
 *              supporting annex F of the C99 standard are required to        *
 *              provide 32-bit float and 64-bit double.                       *
 *          3.) The tmpl_integer.h file was successfully able to find 32-bit  *
 *              and 64-bit data types. tmpl_integer.h is required for libtmpl *
 *              to successfully run, so this shouldn't be a problem. On       *
 *              unix-based (GNU, Linux, macOS, FreeBSD, etc), unsigned int is *
 *              32-bits and unsigned long is 64-bits, for just about every    *
 *              compiler on those platforms. Microsoft Windows uses a 32-bit  *
 *              unsigned long, and has a 64-bit unsigned long long. However,  *
 *              the C99 standard (and higher) require 32-bit and 64-bit       *
 *              integer data types be provided, so this shouldn't be an issue.*
 *      Endianness shouldn't matter, however the code has only been tested on *
 *      Little Endian systems. There is no support for mixed-endian, only     *
 *      big and little.                                                       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) limits.h:                                                             *
 *          Standard C library header file containing the macros for how      *
 *          large various integer data types are.                             *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       January 22, 2021                                              *
 ******************************************************************************
 *                          Revision History                                  *
 ******************************************************************************
 *  2021/01/22: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2021/04/08: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IEEE754_H
#define TMPL_IEEE754_H

/*  Macros for determining the size of integer data types found here.         */
#include <limits.h>

/*  We'll use the macros defined in limits.h to see if your compiler supports *
 *  a 32-bit integer. This is usually a regular int. The C standard requires  *
 *  long int to be 'at least' 32-bits. In most implementations it is 64-bits, *
 *  except with Microsoft's compiler which implements it as a 32-bit integer. */

#if USHRT_MAX == 0xFFFFFFFF
typedef short unsigned int tmpl_uint32;
typedef short int tmpl_int32;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int tmpl_uint32;
typedef int tmpl_int32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef long unsigned int tmpl_uint32;
typedef long int tmpl_int32;
#elif define(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFF
typedef long long unsigned int tmpl_uint32;
typedef long long int tmpl_int32;
#else
#error "libtmpl: No 32-bit integer type found."
#endif

/*  Lastly, try to find a 64-bit data type.                                   */
#if USHRT_MAX == 0xFFFFFFFFFFFFFFFF
typedef short unsigned int tmpl_uint64;
typedef short int tmpl_int64;
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned int tmpl_uint64;
typedef int tmpl_int64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long unsigned int tmpl_uint64;
typedef long int tmpl_int64;
#elif defined(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long long unsigned int tmpl_uint64;
typedef long long int tmpl_int64;
#else
#error "libtmpl: No 64-bit integer type found."
#endif

/******************************************************************************
 *  For a non-negative integer that is less than 2^64, we can store the       *
 *  number in a computer using binary. That is, 64 bits of zeroes and ones    *
 *  which represent our original base-10 integer. With this we can store      *
 *  every integer between 0 and 2^64-1.                                       *
 *                                                                            *
 *    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx        *
 *    ----------------------------------------------------------------        *
 *                              Integer Part                                  *
 *                                                                            *
 *  If we want to represent a "signed" integer, one that can be negative or   *
 *  positive, or zero, we require more information. The solution is to        *
 *  sacrifice one of the 64 bits and reserve it as the "sign." In doing so we *
 *  we can now store every integer between -(2^63-1) and +(2^63-1). Oddly     *
 *  enough, the difference between these two numbers is 2^64-2, not 2^64-1.   *
 *  In reserving a bit for the sign, we now have two zeroes. A "positive"     *
 *  zero and a "negative" zero, These are called "signed zeroes." When using  *
 *  these, compilers treat them nearly the same, and -0 == +0 returns true.   *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx       *
 *    - ---------------------------------------------------------------       *
 *  Sign                        Integer Part                                  *
 *                                                                            *
 *  Note, the left-most bit does not need to be the signed bit. This will be  *
 *  determined by the "endianness" or your system. To store a real number, or *
 *  to at least approximate, one might guess that we simply insert a point    *
 *  half-way and treat this as a decimal:                                     *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - -------------------------------- -------------------------------      *
 *  Sign         Integer Part                      Fractional Part            *
 *                                                                            *
 *  This turns out to be a very bad idea since we cannot represent very many  *
 *  numbers with this. The largest number is now 2^32-1, or roughly 4 billion.*
 *  Any larger number would be treated as infinity. On the other hand, we     *
 *  only have about 9 significant digits past the decimal point (in decimal)  *
 *  whereas many applications need up to 16. The solution is the IEEE754      *
 *  Floating Point Format. It represents a real number as follows:            *
 *                                                                            *
 *    s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - ----------- ----------------------------------------------------      *
 *  Sign  Exponent                     Fraction                               *
 *                                                                            *
 *  The idea is to use scientific notation in binary, writing a number as     *
 *                                                                            *
 *        y = s * 1.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_2    *
 *              * 2^(eeeeeeeeeee_2 - 1111111111_2)                            *
 *                                                                            *
 *  Where _2 indicates this is all base 2. This "magic number" being          *
 *  subtracted is 2^10-1 = 1023.                                              *
 *                                                                            *
 *  Since we know the first digit in scientific notation is always 1, we don't*
 *  need to waste a bit and can store 53 bits worth of the fractional part    *
 *  using just 52 bits. The eeeeeeeeeee - 1023 needs an explaination. We want *
 *  to store fractional numbers between 0 and 1 and so we need negative       *
 *  exponents. We could reserve a second bit for the sign of the exponent,    *
 *  but the standard is to just subtract 2^32-1 from the exponent. The last   *
 *  thing is to say that all zeroes, or all zeros plus the sign bit,          *
 *  represents zero and not +/- 10^-1023.                                     *
 *                                                                            *
 *  Now for some examples:                                                    *
 *    0 00000000001 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1-1023)                                                          *
 *      = 2^-1022                                                             *
 *      ~ 10^-308                                                             *
 *                                                                            *
 *    This is the smallest positive number.                                   *
 *                                                                            *
 *    0 11111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^1023                                                              *
 *      ~ 10^308                                                              *
 *      = Infinity (according to the standard).                               *
 *                                                                            *
 *    Setting 2^1023 to infinity means we can reserve a number of             *
 *    Not-a-Number (NaN) as follows:                                          *
 *                                                                            *
 *    0 11111111111 1111111111111111111111111111111111111111111111111111      *
 *      = NaN                                                                 *
 *                                                                            *
 *    This is useful for log(-1) or sqrt(-1) or 0.0/0.0. As a final example,  *
 *    the IEEE 754 64-bit representation of 1.0:                              *
 *                                                                            *
 *    0 01111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1023 - 1023)                                                     *
 *      = 2^0                                                                 *
 *      = 1                                                                   *
 ******************************************************************************/

/*  To access the binary representation of a floating point number, we use    *
 *  unions. Unions allows us to have different data types share the same block*
 *  of memory. If we have a union of a floating point and an integer, and then*
 *  set the floating point part to some number, then when we try to access the*
 *  integer part it will already have its bits set (They'll be set by the     *
 *  floating point value). The resulting integer is the actual binary value   *
 *  corresponding to the IEEE754 format.                                      */

/*  Data type for a 32-bit floating point number. This is assumed to          *
 *  correspond to the float data type. Note that float is assumed to be 32    *
 *  bits. If your compiler supports the IEEE 754 format, it is.               */
typedef union _tmpl_IEE754_Word32 {
    float real;
    tmpl_uint32 integer;
} tmpl_IEEE754_Word32;


typedef union _tmpl_IEEE754_Word64 {
    double real;
	  tmpl_uint64 integer;
} tmpl_IEEE754_Word64;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_High_Word32                                                  *
 *  Purpose:                                                                  *
 *      Gets the "high word" of a 32-bit IEEE754 floating point number. This  *
 *      is just the binary value of the exponent part of the number, together *
 *      with the sign. A 64 bit version is also provided.                     *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned integer.             *
 *  Output:                                                                   *
 *      tmpl_uint32 high:                                                     *
 *          The numerical value of the high word of w.real.                   *
 *  Source Code:                                                              *
 *      libtmpl/src/ieee754/tmpl_get_high_word32.c                            *
 *      libtmpl/src/ieee754/tmpl_get_high_word64.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/ieee754/tmpl_get_high_word32_example.c               *
 *      libtmpl/examples/ieee754/tmpl_get_high_word64_example.c               *
 ******************************************************************************/
extern tmpl_uint32
tmpl_Get_High_Word32(tmpl_IEEE754_Word32 w);

extern tmpl_uint32
tmpl_Get_High_Word64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Low_Word32                                                   *
 *  Purpose:                                                                  *
 *      Gets the "low word" of a 32-bit IEEE754 floating point number. This   *
 *      is just the binary value of the fractional part of the number.        *
 *      A 64 bit version is also provided.                                    *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      tmpl_uint32 low:                                                      *
 *          The numerical value of the low word of w.real.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ieee754/tmpl_get_low_word32.c                             *
 *      libtmpl/src/ieee754/tmpl_get_low_word64.c                             *
 *  Examples:                                                                 *
 *      libtmpl/examples/ieee754/tmpl_get_low_word32_example.c                *
 *      libtmpl/examples/ieee754/tmpl_get_low_word64_example.c                *
 ******************************************************************************/
extern tmpl_uint32
tmpl_Get_Low_Word32(tmpl_IEEE754_Word32 w);

extern tmpl_uint64
tmpl_Get_Low_Word64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Base_2_Exp32                                                 *
 *  Purpose:                                                                  *
 *      Gets the exponent of a 32-bit word. This is the value b such that the *
 *      number x is represented by 1.m * 2^b, m being the mantissa.           *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      tmpl_int32 exp:                                                       *
 *          The numerical value of the exponential part of w.real in base 2.  *
 *  Source Code:                                                              *
 *      libtmpl/src/ieee754/tmpl_get_base_2_exp32.c                           *
 *      libtmpl/src/ieee754/tmpl_get_base_2_exp64.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/ieee754/tmpl_get_base_2_exp32_example.c              *
 *      libtmpl/examples/ieee754/tmpl_get_base_2_exp64_example.c              *
 ******************************************************************************/
extern tmpl_int32
tmpl_Get_Base_2_Exp32(tmpl_IEEE754_Word32 w);

extern tmpl_int32
tmpl_Get_Base_2_Exp64(tmpl_IEEE754_Word64 w);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Get_Mantissa32                                                   *
 *  Purpose:                                                                  *
 *      Gets the mantissa of a 32-bit word. This is the value 1.m such that   *
 *      the number x is represented by 1.m * 2^b, b being the exponent.       *
 *  Arguments:                                                                *
 *      tmpl_IEE754_Word32 w:                                                 *
 *          A union for 32-bit float and 32-bit unsigned int.                 *
 *  Output:                                                                   *
 *      float mantissa:                                                       *
 *          The numerical value of the mantissa of w.real.                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ieee754/tmpl_get_mantissa32.c                             *
 *      libtmpl/src/ieee754/tmpl_get_mantissa64.c                             *
 *  Examples:                                                                 *
 *      libtmpl/examples/ieee754/tmpl_get_mantissa32_example.c                *
 *      libtmpl/examples/ieee754/tmpl_get_mantissa64_example.c                *
 ******************************************************************************/
extern float
tmpl_Get_Mantissa32(tmpl_IEEE754_Word32 w);

extern double
tmpl_Get_Mantissa64(tmpl_IEEE754_Word64 w);

#endif
/*  End of include guard.                                                     */

