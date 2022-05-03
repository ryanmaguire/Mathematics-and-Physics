/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
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
 *  This file shows the size of all data types in C. I found something very   *
 *  similar to this on stackoverflow and glued bits and pieces together to    *
 *  make this run on clang and GCC with all warnings turned on and in C89,    *
 *  C99, and C18 mode.                                                        *
 ******************************************************************************/

/*  size_t is typedef'd here.                                                 */
#include <stdio.h>

/*  time_t is typedef'd here.                                                 */
#include <time.h>

/*  ptrdiff_t is typedef'd here.                                              */
#include <stddef.h>

/*  C99 and higher defined inttypes.h. Check for this.                        */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#endif

/*  Macro for priting basic types, pointers, and function pointers.           */
#define PRINTTYPE(x) printf("%6u = sizeof(" #x ")\n", (unsigned int)sizeof(x))

/*  Macro for printing structs.                                               */
#define PRINTSTRUCT(x) do {                                                    \
    typedef x mystruct;                                                        \
    printf("%6u = sizeof(" #x ")\n", (unsigned int)sizeof(mystruct));          \
} while (0)

/*  Function for printing the size of all types in C.                         */
int main(void)
{
#ifdef __STDC_VERSION__
	printf("STDC VERSION:\t%ld\n", __STDC_VERSION__);
#else
    puts("__STDC_VERSION__ Macro not defined. This is probably C89/C90.");
#endif

    /* Basic Types                                                            */
    puts("Basic Types:");
    PRINTTYPE(char);
    PRINTTYPE(unsigned char);
    PRINTTYPE(short);
    PRINTTYPE(unsigned short);
    PRINTTYPE(int);
    PRINTTYPE(unsigned int);
    PRINTTYPE(long);
    PRINTTYPE(unsigned long);
    PRINTTYPE(float);
    PRINTTYPE(double);
    PRINTTYPE(long double);
    PRINTTYPE(size_t);
    PRINTTYPE(ptrdiff_t);
    PRINTTYPE(time_t);

    /* Pointers.                                                              */
    puts("Pointers:");
    PRINTTYPE(void *);
    PRINTTYPE(char *);
    PRINTTYPE(short *);
    PRINTTYPE(int *);
    PRINTTYPE(long *);
    PRINTTYPE(float *);
    PRINTTYPE(double *);

    /* Pointers to functions.                                                 */
    puts("Function Pointers:");
    PRINTTYPE(int (*)(void));
    PRINTTYPE(double (*)(void));
    PRINTTYPE(char *(*)(void));

    /* Structures.                                                            */
    puts("Structs:");
    PRINTSTRUCT(struct { char a; });
    PRINTSTRUCT(struct { short a; });
    PRINTSTRUCT(struct { int a; });
    PRINTSTRUCT(struct { long a; });
    PRINTSTRUCT(struct { float a; });
    PRINTSTRUCT(struct { double a; });
    PRINTSTRUCT(struct { char a; double b; });
    PRINTSTRUCT(struct { short a; double b; });
    PRINTSTRUCT(struct { long a; double b; });
    PRINTSTRUCT(struct { char a; char b; short c; });
    PRINTSTRUCT(struct { char a; char b; long c; });
    PRINTSTRUCT(struct { short a; short b; });
    PRINTSTRUCT(struct { char a[3]; char b[3]; });
    PRINTSTRUCT(struct { char a[3]; char b[3]; short c; });
    PRINTSTRUCT(struct { long double a; });
    PRINTSTRUCT(struct { char a; long double b; });

    /* C99 integers.                                                          */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    puts("C99 Types:");
    PRINTTYPE(long long);
    PRINTTYPE(unsigned long long);
    PRINTTYPE(uintmax_t);
    PRINTTYPE(int_least8_t);
    PRINTTYPE(int_least16_t);
    PRINTTYPE(int_least32_t);
    PRINTTYPE(int_least64_t);
    PRINTTYPE(int_fast8_t);
    PRINTTYPE(int_fast16_t);
    PRINTTYPE(int_fast32_t);
    PRINTTYPE(int_fast64_t);
    PRINTTYPE(uintptr_t);
#ifdef INT8_MAX
    PRINTTYPE(int8_t);
#endif
#ifdef INT16_MAX
    PRINTTYPE(int16_t);
#endif
#ifdef INT32_MAX
    PRINTTYPE(int32_t);
#endif
#ifdef INT64_MAX
    PRINTTYPE(int64_t);
#endif
#ifdef INT128_MAX
    PRINTTYPE(int128_t);
#endif
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    puts("C99 Structs:");
    PRINTSTRUCT(struct { char a; long long b; });
    PRINTSTRUCT(struct { char a; uintmax_t b; });
#endif
    return(0);
}
/*  End of main.                                                              */

