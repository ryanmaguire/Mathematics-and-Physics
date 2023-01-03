/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************/

/*  Avoid deprecation warnings if using MSVC.                                 */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  malloc and free found here.                                               */
#include <cstdlib>

/*  FILE, fprintf, and fputc found here.                                      */
#include <cstdio>

/*  sqrt function and more found here.                                        */
#include <cmath>

/*  Some implementations of math.h provide a PI macro. Some don't. Check this.*/
#ifndef PI
#define PI 3.141592653589793
#endif

/*  This shouldn't be defined, but check anyways.                             */
#ifndef TWO_BY_PI
#define TWO_BY_PI 0.6366197723675814
#endif

/*  1023 / 2 pi.                                                              */
#define GRADIENT_FACTOR 162.81550678300894

/*  Struct for a complex number. The standard C++ library provides a complex  *
 *  number class that you could also use.                                     */
struct complex_number {
    double real, imag;

    complex_number(void)
    {
        return;
    }

    complex_number(double x, double y)
    {
        real = x;
        imag = y;
    }

    complex_number operator + (complex_number w)
    {
        return complex_number(real + w.real, imag + w.imag);
    }

    complex_number operator * (complex_number w)
    {
        const double re = real*w.real - imag*w.imag;
        const double im = real*w.imag + imag*w.real;
        return complex_number(re, im);
    }

    complex_number operator / (complex_number w)
    {
        double denom = 1.0 / (w.real*w.real + w.imag*w.imag);
        double re = (real*w.real + imag*w.imag)*denom;
        double im = (imag*w.real - real*w.imag)*denom;
        return complex_number(re, im);
    }

    complex_number operator - (double x)
    {
        return complex_number(real - x, imag);
    }

    double abs(void)
    {
        return std::sqrt(real*real + imag*imag);
    }

    double arg(void)
    {
        return std::atan2(imag, real);
    }
};

static complex_number operator * (double x, complex_number z)
{
    return complex_number(x*z.real, x*z.imag);
}

/*  Struct for working with colors in RGB format.                             */
struct color {
    unsigned char red, green, blue;

    color(void)
    {
        return;
    }

    color (unsigned char a, unsigned char b, unsigned char c)
    {
        red = a;
        green = b;
        blue = c;
    }

    /*  PPM files end up corrupted on windows when using the binary format.   *
     *  For windows use the text format. The file size is significantly larger*
     *  but renders correctly.                                                */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    void write(std::FILE *fp)
    {
        std::fprintf(fp, "%u %u %u\n", red, green, blue);
    }
#else
    void write(std::FILE *fp)
    {
        std::fputc(red, fp);
        std::fputc(green, fp);
        std::fputc(blue, fp);
    }
#endif

    color scale(double t)
    {
        color out;
        out.red = static_cast<unsigned char>(t * static_cast<double>(red));
        out.green = static_cast<unsigned char>(t * static_cast<double>(green));
        out.blue = static_cast<unsigned char>(t * static_cast<double>(blue));
        return out;
    }
};

/*  The complex function that is being plotted.                               */
static complex_number f(complex_number z)
{
    return (z*z*z - 1.0)/(3.0*z*z);
}

/*  Given a complex number z, compute the color corresponding to f(z). The    *
 *  color is given by the magnitude and argument of f(z).                     */
static color get_color(complex_number z)
{
    /*  Declare an output struct for the color we're computing.               */
    color out;

    /*  To allow for a large range of intensities, compress the real line     *
     *  to the interval [-1, 1] using the arctan function.                    */
    const double t = TWO_BY_PI * atan(5.0*z.abs());

    /*  Transform the argument from [-pi, pi] to [0, 1023].                   */
    double val = (z.arg() + PI)*GRADIENT_FACTOR;

    /*  Split [0, 1023] into four parts, [0, 255], [256, 511], [512, 767],    *
     *  and [768, 1023]. Create a blue-to-red rainbow gradient from this.     *
     *  The first interval corresponds to blue to blue-green.                 */
    if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = static_cast<unsigned char>(val);
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
        out.blue = static_cast<unsigned char>(256.0 - val);
    }

    /*  Next is green to yellow.                                              */
    else if (val < 768.0)
    {
        /*  Subtract by 512 to get val in [0, 255].                           */
        val -= 512.0;
        out.red = static_cast<unsigned char>(val);
        out.green = 0xFFU;
        out.blue = 0x00U;
    }

    /*  Finally, yellow to red.                                               */
    else
    {
        /*  Subtract by 768 to get val in the range [0, 255].                 */
        val -= 768.0;
        out.red = 0xFFU;
        out.green = static_cast<unsigned char>(256.0 - val);
        out.blue = 0x00U;
    }

    /*  Scale the color by |z| to differentiate complex numbers by intensity. */
    return out.scale(t);
}
/*  End of get_color.                                                         */

/*  Function for drawing the complex plot of f.                               */
int main(void)
{
    /*  Width and height, in pixels, of the output PPM.                       */
    const unsigned int width = 4096U;
    const unsigned int height = 4096U;
    const unsigned int n_pixels = width*height;

    /*  The Cartesian coordinates of the drawing. The rectangle               *
     *  [xmin, xmax] x [ymin, ymax] will be drawn.                            */
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;

    /*  Factors for transforming from Cartesian coordinates to pixels.        */
    const double xfact = (xmax - xmin) / static_cast<double>(width - 1U);
    const double yfact = (ymax - ymin) / static_cast<double>(height - 1U);

    /*  Index for looping over the pixels.                                    */
    unsigned int n;

    /*  The color represented by f(z).                                        */
    color *c = static_cast<color *>(std::malloc(sizeof(*c) * n_pixels));

    /*  Check if malloc failed.                                               */
    if (!c)
    {
        std::puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Open the PPM file and give it write permissions.                      */
    std::FILE *fp = std::fopen("z3_minus_1_over_3z2_cpp_parallel.ppm", "w");

    /*  Check if fopen failed. Abort if it did.                               */
    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");

        /*  malloc was successful, so free the memory before aborting.        */
        std::free(c);
        return -1;
    }

    /*  As mentioned, text-based for Windows, binary for everyone else.       */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    std::fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    std::fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

    /*  Loop over the pixels.                                                 */
#ifdef _OPENMP
    /*  With high resolutions and multicore CPU, we can get a big speed       *
     *  boost by using OpenMP and parallelizing the loop.                     */
#pragma omp parallel for
#endif
    for (n = 0U; n < n_pixels; ++n)
    {
        const unsigned int x = n % width;
        const unsigned int y = n / height;
        const complex_number z = complex_number(xmin + x*xfact, ymax - y*yfact);

        /*  Calculate the color corresponding to f(z).                        */
        c[n] = get_color(f(z));
    }

    /*  Write all of the color data to the PPM file.                          */
    for (n = 0; n < n_pixels; ++n)
        c[n].write(fp);

    /*  Close the file, free the allocated memory, and return.                */
    std::free(c);
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */
