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
 *  This file creates a complex plot of z^3 - 1. A full color wheel           *
 *  red -> yellow -> green -> blue-green -> blue -> purple -> red is used to  *
 *  remove the appearance of discontinuity in the function. That is, the      *
 *  values arg(z) = pi and arg(z) = -pi are glued together. The rainbow is    *
 *  also normalized so that all colors have the same intensity.               *
 *                                                                            *
 *  This file is compliant with the C89 standard and does not use C99         *
 *  features (basic complex number struct is provided here). The only         *
 *  dependencies are math.h and stdio.h, two standard library headers.        *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2022/01/17                                                        *
 ******************************************************************************/

/*  Microsoft "deprecated" the fopen function in favor of the fopen_s         *
 *  function. The actual working group for the C language has not deprecated  *
 *  fopen, and fopen_s was only introduced in the C11 standard, so I will     *
 *  still use fopen. To avoid a "deprecated" warning on Microsoft's MSVC,     *
 *  first check that the user is running Windows, then define this macro.     *
 *  Unix-based (GNU, Linux, macOS, FreeBSD, etc.) platforms yield no warnings.*/
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  fprintf, FILE, and more found here.                                       */
#include <stdio.h>

/*  Basic math routines here.                                                 */
#include <math.h>

/*  Some implementations of math.h provide a PI macro. Some don't. Check this.*/
#ifndef PI
#define PI 3.141592653589793
#endif

/*  This shouldn't be defined, but check anyways.                             */
#ifndef TWO_BY_PI
#define TWO_BY_PI 0.6366197723675814
#endif

/*  1536 / 2 pi.                                                              */
#define GRADIENT_FACTOR 244.46199258915124

/*  Struct for dealing with complex numbers.                                  */
struct complex_number {
    double real, imag;
};

/*  Struct for dealing with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;
};

/*  For reasons completely beyond me, fputc doesn't seem to work correctly on *
 *  Windows 10. The problem seems to arise when too many colors are present   *
 *  in the PPM file. The rendered PPM file is completely corrupted and looks  *
 *  horrible. If the user is running Windows, use fprintf instead of fputc,   *
 *  and use the text-based PPM format instead of the binary based one. The    *
 *  text-based format ends up being around 4x larger than the binary format,  *
 *  but renders properly.                                                     */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fprintf(fp, "%u %u %u\n", c.red, c.green, c.blue);
}
/*  End of write_color.                                                       */

#else
/*  Everyone else (GNU, Linux, macOS, FreeBSD, etc.).                         */

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

#endif
/*  End of #if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER).       */

/*  Function for computing the argument of a complex number.                  */
static double complex_arg(struct complex_number z)
{
    return atan2(z.imag, z.real);
}
/*  End of complex_arg.                                                       */

/*  Function for computing the modulus, or magnitude, of a complex number.    */
static double complex_abs(struct complex_number z)
{
    return sqrt(z.real*z.real + z.imag*z.imag);
}
/*  End of complex_abs.                                                       */

/*  Function for scaling the intensity of a color by a real number.           */
static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue = (unsigned char)(t * (double)c.blue);
    return out;
}
/*  End of scale_color.                                                       */

/*  Normalizes the intensity of a color to 255.                               */
static struct color normalize_color(struct color c)
{
    struct color out;
    const double x = (double)c.red;
    const double y = (double)c.green;
    const double z = (double)c.blue;
    const double r = 255.0 / sqrt(x*x + y*y + z*z);
    out.red = (unsigned char)(x * r);
    out.green = (unsigned char)(y * r);
    out.blue = (unsigned char)(z * r);
    return out;
}
/*  End of normalize_color.                                                   */

/*  Function for creating a continuous gradient of color in the RGB spectrum. */
static struct color get_color(struct complex_number z)
{
    /*  Declare an output struct for the color we're computing.               */
    struct color out;

    /*  The gradient is based on the modulus and argument of the complex      *
     *  number. The argument gives the color, and the modulus gives the       *
     *  intensity. Compute both of these with the routines above.             */
    const double arg_z = complex_arg(z);
    const double abs_z = complex_abs(z);

    /*  To allow for a large range of intensities, compress the real line     *
     *  to the interval [-1, 1] using the arctan function.                    */
    const double t = TWO_BY_PI * atan(5.0*abs_z);

    /*  Transform the argument from [-pi, pi] to [0, 1536].                   */
    double val = (arg_z + PI)*GRADIENT_FACTOR;

    /*  Split [0, 1536] into six parts. Create a color wheel gradient from    *
     *  this. The first interval corresponds to blue to blue-green.           */
    if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = (unsigned char)(val);
        out.blue = 0xFFU;
    }

    /*  Next we do blue-green to green.                                       */
    else if (val < 512.0)
    {
        /*  Subtract 256 from val so that val lies in [0, 255], which are the *
         *  allowed values for an 8-bit unsigned char.                        */
        val -= 256.0;
        out.red = 0x00U;
        out.green = 0xFFU;
        out.blue = (unsigned char)(256.0 - val);
    }

    /*  Next is green to yellow.                                              */
    else if (val < 768.0)
    {
        /*  Subtract by 512 to get val in [0, 255].                           */
        val -= 512.0;
        out.red = (unsigned char)(val);
        out.green = 0xFFU;
        out.blue = 0x00U;
    }

    /*  Next, yellow to red.                                                  */
    else if (val < 1024.0)
    {
        /*  Subtract by 768 to get val in the range [0, 255].                 */
        val -= 768.0;
        out.red = 0xFFU;
        out.green = (unsigned char)(256.0 - val);
        out.blue = 0x00U;
    }

    /*  Then red to purple.                                                   */
    else if (val < 1280.0)
    {
        /*  Subtract by 1024 to get val in the range [0, 255].                */
        val -= 1024.0;
        out.red = 0xFFU;
        out.green = 0x00U;
        out.blue = (unsigned char)val;
    }

    /*  Finally, purple back to blue.                                         */
    else
    {
        /*  Subtract by 1280 to get val in the range [0, 255].                */
        val -= 1280.0;
        out.red = (unsigned char)(256.0 - val);
        out.green = 0x00U;
        out.blue = 0xFFU;
    }

    /*  Normalize the color so that the intensity is 255.                     */
    out = normalize_color(out);

    /*  Scale the color by |z| to differentiate complex numbers by intensity. */
    return scale_color(out, t);
}
/*  End of get_color.                                                         */

/*  The polynomial z^3 - 1.               .                                   */
static struct complex_number f(struct complex_number z)
{
    /*  Declare a variable for the output.                                    */
    struct complex_number out;

    /*  Compute z^3, and then subtract 1 from the real part.                  */
    out.real = z.real*(z.real*z.real - 3.0*z.imag*z.imag) - 1.0;
    out.imag = z.imag*(3.0*z.real*z.real - z.imag*z.imag);
    return out;
}
/*  End of f.                                                                 */

/*  Function for plotting f.                                                  */
int main(void)
{
    /*  The width and height of the image, in pixels.                         */
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;

    /*  The box [x0, x1]x[y0, y1] that is being plotted in the plane.         */
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;

    /*  Variables for indexing over the pixels of the image.                  */
    unsigned int x, y;

    /*  Complex number for looping over points in the plane.                  */
    struct complex_number z;

    /*  Color struct to represent a given point in the plane.                 */
    struct color current_color;

    /*  Scale factors to go from pixel in the image to point in the plane.    */
    const double xfactor = (xmax - xmin) / (double)(width - 1U);
    const double yfactor = (ymax - ymin) / (double)(height - 1U);

    /*  Open a file and give it write permission.                             */
    FILE *fp = fopen("z3_minus_1_color_wheel_normalized.ppm", "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
    {
        puts("fopen failed and return NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file. For Windows users we'll use text  *
     *  based PPM, and for everyone else we'll use binary format.             */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

    /*  Loop over the y coordinates.                                          */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the current imaginary part of z.                          */
        z.imag = ymax - (double)y * yfactor;

        /*  Loop over the x coordinates.                                      */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the real part of z.                                   */
            z.real = xmin + (double)x * xfactor;

            /*  Calculate the color corresponding to f(z).                    */
            current_color = get_color(f(z));

            /*  Write the color to the file.                                  */
            write_color(fp, current_color);
        }
        /*  End of for-loop for x.                                            */
    }
    /*  End of for-loop for y.                                                */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
