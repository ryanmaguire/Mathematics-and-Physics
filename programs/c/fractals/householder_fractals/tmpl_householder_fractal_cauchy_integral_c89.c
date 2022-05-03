#include <stdio.h>
#include <math.h>

struct complex_number {
    double real, imag;
};

static const unsigned int deg = 4U;
static const double arr[5] = {1.0, 0.0, 0.0, 0.0, -1.0};
static const unsigned int order = 10U;
static const struct complex_number root0 = {1.0, 0.0};
static const struct complex_number root1 = {0.0, 1.0};
static const struct complex_number root2 = {-1.0, 0.0};
static const struct complex_number root3 = {0.0, -1.0};

struct color {
    unsigned char red, green, blue;
};

static void write_color(struct color c, FILE *fp)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}

static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}

static double complex_abs(struct complex_number z)
{
    return sqrt(z.real*z.real + z.imag*z.imag);
}

static struct complex_number complex_scale(double a, struct complex_number z)
{
    struct complex_number out;
    out.real = a*z.real;
    out.imag = a*z.imag;
    return out;
}

static struct complex_number
complex_add(struct complex_number z, struct complex_number w)
{
    struct complex_number out;
    out.real = z.real + w.real;
    out.imag = z.imag + w.imag;
    return out;
}

static double complex_dist(struct complex_number z, struct complex_number w)
{
    double dx = z.real - w.real;
    double dy = z.imag - w.imag;
    return sqrt(dx*dx + dy*dy);
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
complex_multiply(struct complex_number z, struct complex_number w)
{
    struct complex_number out;
    out.real = z.real*w.real - z.imag*w.imag;
    out.imag = z.real*w.imag + z.imag*w.real;
    return out;
}

static struct complex_number
complex_reciprocal(struct complex_number z)
{
    struct complex_number out;
    double denom = 1.0 / (z.real*z.real + z.imag*z.imag);

    out.real =  z.real * denom;
    out.imag = -z.imag * denom;
    return out;
}

static struct complex_number
complex_pow(struct complex_number z, unsigned int N)
{
    struct complex_number out = z;
    unsigned int n;

    for (n = 1U; n < N; ++n)
        out = complex_multiply(out, z);

    return out;
}

static struct complex_number
poly(struct complex_number z)
{
    struct complex_number out, coeff;
    unsigned int n;

    out.real = arr[0];
    out.imag = 0.0;
    coeff.imag = 0.0;

    for (n = 1U; n <= deg; ++n)
    {
        coeff.real = arr[n];
        out = complex_add(complex_multiply(out, z), coeff);
    }

    return out;
}

static struct complex_number
rcpr_poly(struct complex_number z)
{
    return complex_reciprocal(poly(z));
}

static struct complex_number
numerical_deriv(struct complex_number z, unsigned int d_order)
{
    unsigned int NInt = 100U;
    struct complex_number out;
    struct complex_number w, coeff, scale_factor, w_prime;
    unsigned int n;
    double dt = 1.0 / (double)NInt;
    double t = 0.0;
    double d0 = complex_dist(z, root0);
    double d1 = complex_dist(z, root1);
    double d2 = complex_dist(z, root2);
    double d3 = complex_dist(z, root3);
    double min = d0;
    double order_factorial;

    if (d1 < min)
        min = d1;

    if (d2 < min)
        min = d2;

    if (d3 < min)
        min = d3;

    if (d_order)
        order_factorial = (double)d_order;
    else
        order_factorial = 1.0;

    for (n = 2U; n < d_order; ++n)
        order_factorial *= (double)n;

    min *= 0.5;
    scale_factor.real = 0.0;
    scale_factor.imag = -order_factorial*0.15915494309189535*dt;
    out.real = 0.0;
    out.imag = 0.0;

    for (n = 0U; n < NInt; ++n)
    {
        w.real = min*cos(6.283185307179586*t);
        w.imag = min*sin(6.283185307179586*t);
        w_prime.real = -6.283185307179586*w.imag;
        w_prime.imag =  6.283185307179586*w.real;

        w.real += z.real;
        w.imag += z.imag;
        coeff = complex_subtract(w, z);
        coeff = complex_reciprocal(coeff);
        coeff = complex_pow(coeff, d_order+1U);
        coeff = complex_multiply(coeff, w_prime);
        coeff = complex_multiply(coeff, rcpr_poly(w));
        out = complex_add(out, coeff);
        t += dt;
    }

    return complex_multiply(out, scale_factor);
}

static struct complex_number
householder_factor(struct complex_number z)
{
    struct complex_number numer = numerical_deriv(z, order-1U);
    struct complex_number denom = complex_reciprocal(numerical_deriv(z, order));
    return complex_scale((double)order, complex_multiply(numer, denom));
}

int main(void)
{
    FILE *fp = fopen("test.ppm", "w");
    unsigned int x, y;
    struct complex_number z, f_z;
    unsigned int width = 1028U;
    unsigned int height = 1028U;
    double z_x, z_y;
    double xmin = -4.0;
    double xmax =  4.0;
    double ymin = -4.0;
    double ymax =  4.0;
    double xfactor = (xmax - xmin) / (double)(width - 1U);
    double yfactor = (ymax - ymin) / (double)(height - 1U);
    const struct color red    = {0xFFU, 0x00U, 0x00U};
    const struct color green  = {0x00U, 0xFFU, 0x00U};
    const struct color blue   = {0x00U, 0x00U, 0xFFU};
    const struct color yellow = {0xFFU, 0xFFU, 0x00U};
    const struct color black  = {0x00U, 0x00U, 0x00U};
    double EPS = 0.4;
    double toler = 0.4;
    unsigned char iters;
    const unsigned char max_iters = 0x20U;
    double scale_factor = 1.0 / (double)max_iters;
    double scale;
    struct color current_color;
    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    for (y = 0U; y < height; ++y)
    {
        z_y = ymax - (double)y * yfactor;
        for (x = 0U; x < width; ++x)
        {
            z_x = ymin + (double)x * xfactor;

            z.real = z_x;
            z.imag = z_y;
            f_z = poly(z);
            iters = 0x00U;

            while ((complex_abs(f_z) > EPS) && (iters < max_iters))
            {
                z = complex_add(z, householder_factor(z));
                f_z = poly(z);
                ++iters;
            }

            scale = 1.0 - (double)iters * scale_factor;
            if (complex_dist(z, root0) < toler)
                current_color = scale_color(red, scale);
            else if (complex_dist(z, root1) < toler)
                current_color = scale_color(green, scale);
            else if (complex_dist(z, root2) < toler)
                current_color = scale_color(blue, scale);
            else if (complex_dist(z, root3) < toler)
                current_color = scale_color(yellow, scale);
            else
                current_color = black;

            write_color(current_color, fp);
        }
        printf("%u\n", y);
    }

    fclose(fp);
    return 0;
}


