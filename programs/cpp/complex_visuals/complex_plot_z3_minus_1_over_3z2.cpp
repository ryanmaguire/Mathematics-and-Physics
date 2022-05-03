
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <cstdio>
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

static complex_number f(complex_number z)
{
    return (z*z*z - 1.0)/(3.0*z*z);
}

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


int main(void)
{
    const unsigned int width = 1024U;
    const unsigned int height = 1024U;
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;
    const double xfactor = (xmax - xmin) / static_cast<double>(width - 1U);
    const double yfactor = (ymax - ymin) / static_cast<double>(height - 1U);
    unsigned int x, y;
    complex_number z;
    color c;

    std::FILE *fp = std::fopen("z3_minus_1_over_3z2_cpp.ppm", "w");

    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    std::fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    std::fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

    z.imag = ymax;

    /*  Loop over the y coordinates.                                          */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the current imaginary part of z.                          */
        z.imag -= yfactor;
        z.real = xmin;

        /*  Loop over the x coordinates.                                      */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the real part of z.                                   */
            z.real += xfactor;

            /*  Calculate the color corresponding to f(z).                    */
            c = get_color(f(z));

            /*  Write the color to the file.                                  */
            c.write(fp);
        }
        /*  End of for-loop for x.                                            */
    }
    /*  End of for-loop for y.                                                */

    std::fclose(fp);
    return 0;
}
