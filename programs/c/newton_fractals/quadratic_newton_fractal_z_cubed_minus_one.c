

#include <stdio.h>
#include <math.h>

struct complex_number {
    double real, imag;
};

static double complex_abs(struct complex_number z)
{
    return sqrt(z.real*z.real + z.imag*z.imag);
}

static double complex_arg(struct complex_number z)
{
    return atan2(z.imag, z.real);
}

static struct complex_number
complex_add(struct complex_number z, struct complex_number w)
{
    struct complex_number out;
    out.real = z.real + w.real;
    out.imag = z.imag + w.imag;
    return out;
}

static struct complex_number
complex_subtract(struct complex_number z, struct complex_number w)
{
    struct complex_number out;
    out.real = z.real - w.real;
    out.imag = z.imag - w.imag;
    return out;
}

static struct complex_number
complex_mult(struct complex_number z, struct complex_number w)
{
    struct complex_number out;
    out.real = z.real*w.real - z.imag*w.imag;
    out.imag = z.real*w.imag + z.imag*w.real;
    return out;
}

static struct complex_number
complex_divide(struct complex_number z, struct complex_number w)
{
    const double denom = 1.0 / (w.real*w.real + w.imag*w.imag);
    struct complex_number out;
    out.real = (z.real*w.real + z.imag*w.imag)*denom;
    out.imag = (z.imag*w.real - z.real*w.imag)*denom;
    return out;
}

static struct complex_number complex_sqrt(struct complex_number z)
{
    struct complex_number out;
    const double r = sqrt(complex_abs(z));
    const double theta = 0.5*complex_arg(z);
    out.real = r*cos(theta);
    out.imag = r*sin(theta);
    return out;
}

static struct complex_number complex_negate(struct complex_number z)
{
    struct complex_number out;
    out.real = -z.real;
    out.imag = -z.imag;
    return out;
}

static struct complex_number complex_scale(double x, struct complex_number z)
{
    struct complex_number out;
    out.real = x*z.real;
    out.imag = x*z.imag;
    return out;
}

static struct complex_number complex_square(struct complex_number z)
{
    struct complex_number out;
    out.real = z.real*z.real - z.imag*z.imag;
    out.imag = 2.0*z.real*z.imag;
    return out;
}

static struct complex_number
complex_quadratic_root_plus(struct complex_number a, struct complex_number b,
                            struct complex_number c)
{
    struct complex_number b_squared_minus_four_a_c, numer;
    struct complex_number negative_b = complex_negate(b);
    struct complex_number b_squared = complex_square(b);
    struct complex_number two_a = complex_scale(2.0, a);
    struct complex_number four_a_c = complex_scale(4.0, complex_mult(a, c));
    b_squared_minus_four_a_c = complex_subtract(b_squared, four_a_c);
    numer = complex_add(negative_b, complex_sqrt(b_squared_minus_four_a_c));
    return complex_divide(numer, two_a);
}

static struct complex_number
complex_quadratic_root_minus(struct complex_number a, struct complex_number b,
                             struct complex_number c)
{
  struct complex_number b_squared_minus_four_a_c, numer;
  struct complex_number negative_b = complex_negate(b);
  struct complex_number b_squared = complex_square(b);
  struct complex_number two_a = complex_scale(2.0, a);
  struct complex_number four_a_c = complex_scale(4.0, complex_mult(a, c));
  b_squared_minus_four_a_c = complex_subtract(b_squared, four_a_c);
  numer = complex_subtract(negative_b, complex_sqrt(b_squared_minus_four_a_c));
  return complex_divide(numer, two_a);
}

static struct complex_number f(struct complex_number z)
{
    struct complex_number out;
    out.real = z.real*(z.real*z.real - 3.0*z.imag*z.imag) - 1.0;
    out.imag = z.imag*(3.0*z.real*z.real - z.imag*z.imag);
    return out;
}

static struct complex_number f_prime(struct complex_number z)
{
    struct complex_number out;
    out.real = 3.0*(z.real*z.real - z.imag*z.imag);
    out.imag = 6.0*z.real*z.imag;
    return out;
}

static struct complex_number f_2prime(struct complex_number z)
{
    struct complex_number out;
    out.real = 6.0*z.real;
    out.imag = 6.0*z.real;
    return out;
}

static struct complex_number next_iter(struct complex_number z)
{
    struct complex_number a = complex_scale(0.5, f_2prime(z));
    struct complex_number b = f_prime(z);
    struct complex_number c = f(z);
    struct complex_number d0 = complex_quadratic_root_plus(a, b, c);
    struct complex_number d1 = complex_quadratic_root_minus(a, b, c);
    d0 = complex_add(d0, z);
    d1 = complex_add(d1, z);

    if (complex_abs(f(d0)) < complex_abs(f(d1)))
        return d0;
    else
        return d1;
}


static double complex_dist(struct complex_number z, struct complex_number w)
{
    const double dx = z.real - w.real;
    const double dy = z.imag - w.imag;
    return sqrt(dx*dx + dy*dy);
}

static void draw_blue(FILE *fp)
{
    fputc(0x00U, fp);
    fputc(0x00U, fp);
    fputc(0xFFU, fp);
}

static void draw_green(FILE *fp)
{
    fputc(0x00U, fp);
    fputc(0xFFU, fp);
    fputc(0x00U, fp);
}

static void draw_red(FILE *fp)
{
    fputc(0xFFU, fp);
    fputc(0x00U, fp);
    fputc(0x00U, fp);
}

static void draw_black(FILE *fp)
{
    fputc(0x00U, fp);
    fputc(0x00U, fp);
    fputc(0x00U, fp);
}

int main(void)
{
    const unsigned int width = 4U*1024U;
    const unsigned int height = 4U*1024U;
    const double xmin = -2.0;
    const double xmax =  2.0;
    const double ymin = -2.0;
    const double ymax =  2.0;
    const double eps = 1.0E-8;
    const unsigned int toler = 200;

    const struct complex_number root0 = {1.0, 0.0};
    const struct complex_number root1 = {-0.5, 0.8660254037844386};
    const struct complex_number root2 = {-0.5, -0.8660254037844386};

    const double xfactor = (xmax - xmin) / (double)(width - 1U);
    const double yfactor = (ymax - ymin) / (double)(height - 1U);
    unsigned int x, y, n;
    struct complex_number z, z0;

    FILE *fp = fopen("quadratic_newton_fractal.ppm", "w");

    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    fprintf(fp, "P6\n%u %u\n255\n", width, height);

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

            z0 = z;

            for (n = 0; n < toler; ++n)
            {
                z0 = next_iter(z0);

                if (complex_abs(f(z0)) < eps)
                    break;
            }

            if (complex_dist(z0, root0) < eps)
                draw_blue(fp);
            else if (complex_dist(z0, root1) < eps)
                draw_red(fp);
            else if (complex_dist(z0, root2) < eps)
                draw_green(fp);
            else
                draw_black(fp);
        }
    }
    fclose(fp);
    return 0;
}
