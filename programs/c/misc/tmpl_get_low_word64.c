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
 *                           tmpl_get_low_word64                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains source code for getting the "low word" of an IEEE754         *
 *      double precision 64-bit floating point number. This is the            *
 *      fractional part of the number.                                        *
 *  Method:                                                                   *
 *      Get the unsigned integer equivalent of the double-precision number    *
 *      and perform bitwise AND with the magic number                         *
 *      11111111111111111111111111111111111111111111111111_2                  *
 *          = 4503599627370495                                                *
 *          = 0xFFFFFFFFFFFFF (in hexidecimal).                               *
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

/*  Computes the low word of a 64-bit floating-point number.                  */
tmpl_uint64 tmpl_Get_Low_Word64(tmpl_IEEE754_Word64 x)
{
    /*  x.real is a double. Use the union and look at x.integer. This will    *
     *  give us the actual binary value of x.real and we can pretend it is    *
     *  an unsigned integer.                                                  */
    tmpl_uint64 out = x.integer;

    /*  Bit-wise AND can help us zero out the high-word. If we have:          *
     *  s eeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     *
     *  - ---------- ----------------------------------------------------     *
     *                                                                        *
     *  And then perform bitwise AND with 4503599627370495, we get:           *
     *    s eeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   *
     *  & 0 0000000000 1111111111111111111111111111111111111111111111111111   *
     *  = 0 0000000000 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   *
     *                                                                        *
     *  In other words, we get the low-word.                                  */
    out = out & 0xFFFFFFFFFFFFF;
    return out;
}
/*  End of tmpl_Get_Low_Word64.                                               */

