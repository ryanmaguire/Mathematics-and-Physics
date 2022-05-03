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
 *                           tmpl_get_high_word64                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains source code for getting the "high word" of an IEEE754        *
 *      double precision 64-bit floating point number. This is the            *
 *      exponent part of the number and the sign.                             *
 *  Method:                                                                   *
 *      Get the unsigned integer equivalent of the double-precision number,   *
 *      bit shift it over 52-binary digits.                                   *
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
 *              provide this.                                                 *
 *          3.) The tmpl_integer.h header file was able to successfully       *
 *              typedef 32-bit and 64-bit integer data types. Compilers       *
 *              supporting the C99 standard are required to provide these     *
 *              data types in stdint.h. C89/C90 compilers may support 32-bit  *
 *              64-bit integers, but are NOT required too. Usually, int is    *
 *              32-bit and long is 64-bit, except with Microsoft's compiler   *
 *              where int and long are 32-bit, and long long is 64-bit.       *
 *      If your compiler supports the C99 version of the C programming        *
 *      language, then this code is portable since 32-bit and 64-bit integers *
 *      are required, and the IEEE754 is recommended in the appendix of the   *
 *      standard. Most compilers will run this code just fine.                *
 *                                                                            *
 *      Endianness shouldn't matter, however the code has only been tested on *
 *      Little Endian systems. Mixed-Endian is not supported.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       January 22, 2021                                              *
 ******************************************************************************/

/*  Definitions, typedefs, and prototypes found here.                         */
#include "tmpl_ieee754.h"

/*  Computes the high word of a 64-bit floating-point number.                 */
tmpl_uint32 tmpl_Get_High_Word64(tmpl_IEEE754_Word64 x)
{
    /*  x.real is a double. Use the union and look at x.integer. This will    *
     *  give us the actual binary value of x.real and we can pretend it is    *
     *  an unsigned long.                                                     */
    tmpl_uint64 out = x.integer;

    /*  The first bit is the sign, the next 11 are the exponent, and the last *
     *  52 are the fractional parts. We don't care about the fractional part  *
     *  since we are trying to get the high-word. Shift the "decimal"         *
     *  (i.e. the "point") over 52 digits. This is equivalent to dividing by  *
     *  2^52 and looking at the integer part, but is a lot faster.            *
     *                                                                        *
     *  To put the problem into decimal, if asked to divide 1000 by 100, you  *
     *  would not perform long division, but rather just shift the decimal    *
     *  point over by 2, giving 10. This is the binary version of this.       */
    out = out >> 52;
    return (tmpl_uint32)out;
}
/*  End of tmpl_Get_High_Word64.                                              */

