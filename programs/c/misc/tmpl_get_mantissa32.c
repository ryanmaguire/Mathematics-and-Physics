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
 *                           tmpl_get_mantissa32                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains source code for getting the mantissa of an IEEE754 single    *
 *      precision floating point number. Given the number 1.m * 2^b, this     *
 *      returns 1.m. The value "b" is the exponent.                           *
 *  Method:                                                                   *
 *      Extract the low-word via bitwise AND with the magic number            *
 *      0x007FFFFF and then add 0x3F800000, which is the hexidecimal          *
 *      representation for 1.0 in IEEE754. Treat this integer as a float      *
 *      according to the IEEE754 format and return.                           *
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
 *  Date:       April 7, 2021                                                 *
 ******************************************************************************/

/*  Definitions, typedefs, and prototypes found here.                         */
#include "tmpl_ieee754.h"

/*  Function for extracting the mantissa from a 32-bit floating point number. */
float tmpl_Get_Mantissa32(tmpl_IEEE754_Word32 w)
{
    /*  Use the IEEE 754 32-bit union to convert between float and binary.    */
    tmpl_IEEE754_Word32 out;

    /*  Use bitwise AND with 0x007FFFFF to extract the low word. Then add     *
     *  0x3F800000 which is the hexidecimal representation of 1.0. This will  *
     *  give use 1.0 + 0.m = 1.m, which is what we want.                      */
    out.integer = (w.integer & 0x007FFFFF) | 0x3F800000;

    /*  Return the float part from the IEEE 754 union data type.              */
    return out.real;
}
/*  End of tmpl_Get_Mantissa32.                                               */

