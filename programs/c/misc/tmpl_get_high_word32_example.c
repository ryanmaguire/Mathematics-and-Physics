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
 *  To compile, simply run:                                                   *
 *      gcc tmpl_get_high_word32_example.c -o test -ltmpl                     *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/                                             *
 *          tmpl_get_high_word32_example.c -o test -ltmpl                     *
 *  We can the run the executable via:                                        *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      High Word of 8.000000: 130                                            *
 *      High Word of 3.333333: 128                                            *
 *      High Word of 0.500000: 126                                            *
 *      High Word of 0.333333: 125                                            *
 *  This was tested on Debian 10 (Buster) GNU/Linux with gcc, tcc, pcc, and   *
 *  clang from the Debian 10 main repository. Version numbers are:            *
 *      gcc: Debian 8.3.0-6                                                   *
 *      pcc: Portable C Compiler 1.2.0.DEVEL 20181216 for x86_64-pc-linux-gnu *
 *      tcc: version 0.9.27 (x86_64 Linux)                                    *
 *      clang: version 7.0.1-8+deb10u2 (tags/RELEASE_701/final)               *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       April 5, 2021                                                 *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_uint32 data type typedef'd here.                                     */
#include <libtmpl/include/tmpl_integer.h>

/*  tmpl_Get_High_Word32 is declared here.                                    */
#include <libtmpl/include/tmpl_ieee754.h>

/*  Function for testing the tmpl_Get_High_Word32 function.                   */
int main(void)
{
    /*  Declare variables for the high words.                                 */
    tmpl_uint32 b0, b1, b2, b3;

    /*  And declare variables for the IEEE 754 float union.                   */
    tmpl_IEEE754_Word32 w0, w1, w2, w3;

    /*  Set the float part of the IEEE 754 union to various values.           */
    w0.real = 8.0F;
    w1.real = 3.333333333F;
    w2.real = 0.5F;
    w3.real = 0.3333333333F;

    /*  Extract the high words from the floating point numbers.               */
    b0 = tmpl_Get_High_Word32(w0);
    b1 = tmpl_Get_High_Word32(w1);
    b2 = tmpl_Get_High_Word32(w2);
    b3 = tmpl_Get_High_Word32(w3);

    /*  Print the results.                                                    */
    printf("High Word of %f: %u\n", (double)w0.real, b0);
    printf("High Word of %f: %u\n", (double)w1.real, b1);
    printf("High Word of %f: %u\n", (double)w2.real, b2);
    printf("High Word of %f: %u\n", (double)w3.real, b3);

    return 0;
}
/*  End of main.                                                              */

