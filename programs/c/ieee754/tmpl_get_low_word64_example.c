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
 *      gcc tmpl_get_low_word64_example.c -o test -ltmpl                      *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/                                             *
 *          tmpl_get_low_word64_example.c -o test -ltmpl                      *
 *  We can the run the executable via:                                        *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      Low Word of 8.000000: 0                                               *
 *      Low Word of 3.333333: 3002399750829731                                *
 *      Low Word of 0.500000: 0                                               *
 *      Low Word of 0.333333: 1501199875189685                                *
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

/*  tmpl_uint64 data type typedef'd here.                                     */
#include <libtmpl/include/tmpl_integer.h>

/*  tmpl_Get_Low_Word64 is declared here.                                     */
#include <libtmpl/include/tmpl_ieee754.h>

/*  Function for testing the tmpl_Get_Low_Word64 function.                    */
int main(void)
{
    /*  Declare variables for the low words.                                  */
    tmpl_uint64 b0, b1, b2, b3;

    /*  And declare variables for the IEEE 754 double union.                  */
    tmpl_IEEE754_Word64 w0, w1, w2, w3;

    /*  Set the double part of the IEEE 754 union to various values.          */
    w0.real = 8.0;
    w1.real = 3.333333333;
    w2.real = 0.5;
    w3.real = 0.3333333333;

    /*  Extract the low words from the floating point numbers.                */
    b0 = tmpl_Get_Low_Word64(w0);
    b1 = tmpl_Get_Low_Word64(w1);
    b2 = tmpl_Get_Low_Word64(w2);
    b3 = tmpl_Get_Low_Word64(w3);

    /*  Print the results.                                                    */
    printf("Low Word of %f: %lu\n", w0.real, b0);
    printf("Low Word of %f: %lu\n", w1.real, b1);
    printf("Low Word of %f: %lu\n", w2.real, b2);
    printf("Low Word of %f: %lu\n", w3.real, b3);

    return 0;
}
/*  End of main.                                                              */

