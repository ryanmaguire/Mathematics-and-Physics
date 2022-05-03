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
 *                           tmpl_get_base_2_exp32                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the exponent part of a 32-bit floating point value that is   *
 *      represented using the IEEE 754 single precision format. That is,      *
 *      given a floating point number x = 1.m * 2^b, this function returns    *
 *      b. The value 1.m is called the mantissa.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Get_Base_2_Exp32:                                                *
 *  Purpose:                                                                  *
 *      Get's the base-2 exponent of a 32-bit floating point number.          *
 *  Arguments:                                                                *
 *      w (tmpl_IEEE754_Word32).                                              *
 *          A union representing a 32-bit floating point value in binary.     *
 *  Output:                                                                   *
 *      exp (tmpl_int32):                                                     *
 *          A 32-bit signed integer corresponding to the exponent of          *
 *          the input.                                                        *
 *  Method:                                                                   *
 *      Extract the high word of the floating point number and subtract 127   *
 *      from this, as specified in the IEEE 754 format.                       *
 *  NOTES:                                                                    *
 *      While the code is written in ANSI C, this is NOT portable since it    *
 *      assumes various things. This part of the code makes the following     *
 *      assumptions (as stated, use of this code is only optional):           *
 *          1.) Your platform uses IEEE 754 format for floating point         *
 *              arithmetic. Most modern compilers do.                         *
 *          2.) You have 32-bit float and 64-bit double. This is NOT          *
 *              required by the C89/C90 standard, only minimum sizes are      *
 *              specified. 32-bit/64-bit single and double precision is the   *
 *              most common, but this can break portability. Compilers        *
 *              supporting the IEEE 754 format are required to have 32-bit    *
 *              and 64-bit float and double, respectively.                    *
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
 *      Little Endian systems. Mixed-endian is not supported.                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_integer.h:                                                       *
 *          This file provides 32-bit and 64-bit signed and unsigned data     *
 *          types. This assumes these are available. They are required by     *
 *          compilers supporting stdint.h (C99 and higher), and most C89/C90  *
 *          compilers provide integers of these sizes.                        *
 *  2.) tmpl_ieee754.h:                                                       *
 *          Header file that contains union data types for working with       *
 *          floating point numbers using 32 and 64 bit integer data types.    *
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
 *  Date:       February 27, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/02/27: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2021/03/31: Ryan Maguire                                                  *
 *      Soft freeze for alpha release of libtmpl.                             *
 ******************************************************************************/

/*  Function prototype and tmpl_IEEE754_Word32 data type defined here.        */
#include "tmpl_ieee754.h"

/*  Function for extracting the exponent value of a 32-bit float.             */
tmpl_int32 tmpl_Get_Base_2_Exp32(tmpl_IEEE754_Word32 w)
{
    /*  We need to set the signed bit of the float to zero since we don't     *
     *  need this information. The signed bit is the zeroth bit, so we just   *
     *  need to use a bitwise AND with the hexidecimal number 0x7FFFFFFF.     *
     *  0x7FFFFFFF is the hexidecimal number representing 0 in the zeroth bit *
     *  and 1 in the next 31 bits. Using bitwise AND with this number simply  *
     *  zeroes out the zeroth bit. We then need to extract the high word,     *
     *  which is the last 9 bits. To do this, we bit-shift to the right using *
     *  the >> operator, bit-shifting 23 bits. The bitwise AND is performed   *
     *  via the & operator.                                                   */
    tmpl_uint32 highword = (0x7FFFFFFF & w.integer) >> 23;

    /*  The IEEE 754 format specifies that the exponent value of a 32-bit     *
     *  floating point number is the high word minus 127 (which is 2^7 - 1).  *
     *  The high word is an unsigned (non-negative) integer. Subtracting 127  *
     *  from the high word allows for negative exponents, which is useful for *
     *  fractional values like 0.5.                                           */
    tmpl_int32 out = (tmpl_int32)highword - 127;
    return out;
}
/*  End of tmpl_Get_Base_2_Exp32.                                             */

