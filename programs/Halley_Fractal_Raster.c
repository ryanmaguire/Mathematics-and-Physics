#include <stdio.h>
#include <math.h>
#include <complex.h>

/******************************************************************************
 ******************************************************************************
 *                          Begin User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  The number of pixels in the x and y axes.                                 */
static const int size = 1024;

/*  Maximum number of iterations for the Newton-Raphson method. This must be  *
 *  less than 255, otherwise we'll run out of colors.                         */
static const unsigned int MaxIters = 32;

/*  Maximum number of iterations allowed before giving up on the root finding *
 *  algorithm. If no roots are found, the computation aborts.                 */
static const unsigned int root_finder_max_iter = 200;

/*  The coefficients of the polynomial. The zeroth coefficient is for z^deg   *
 *  and the last coefficient is the constant term.                            */
static const complex double coeffs[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};

/******************************************************************************
 ******************************************************************************
 *                            End User Input                                  *
 ******************************************************************************
 ******************************************************************************/

static const unsigned int DEG = sizeof(coeffs)/sizeof(coeffs[0]) - 1U;
static const double PI = 3.14159265358979323846264338327950288419716;

struct color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/*  Define the polynomial based on the user provided coefficients. Compute    *
 *  this via Horner's method for speed.                                       */
static complex double poly_eval(complex double z)
{
    complex double out;
    unsigned int n;

    out = coeffs[0];
    for (n = 1U; n <= DEG; ++n)
        out = z*out + coeffs[n];

    return out;
}

static complex double poly_prime_eval(complex double z)
{
    complex double out;
    unsigned int n;

    out = DEG*coeffs[0];
    for (n = 1U; n < DEG; ++n)
        out = z*out + DEG*coeffs[n];

    return out;
}

static complex double poly_double_prime_eval(complex double z)
{
    complex double out;
    unsigned int n;

    out = DEG*(DEG-1)*coeffs[0];
    for (n = 1U; n < DEG - 1U; ++n)
        out = z*out + DEG*(DEG-1)*coeffs[n];

    return out;
}

static unsigned int get_roots(unsigned int deg, complex double *roots)
{
    complex double p, root, f_p, df_p, d2f_p;
    unsigned int m, n, ell, iter, s, N, n_roots;
    double r, theta, factor_1, factor_2, min, temp, N_real, s_real;
    const complex double dbl_I = (complex double)_Complex_I;

    if (roots == NULL)
        return 0U;

    if (deg == 0U)
        return 0U;

    s_real = ceil(0.26632*log(deg));
    N_real = ceil(8.32547*deg*log(deg));

    s = (unsigned int )s_real;
    N = (unsigned int)N_real;
    n_roots = 0;

    factor_1 = 1.0 + sqrt(2.0);
    factor_2 = (deg - 1.0) / deg;
    root = 0.0;


    for (m = 0U; m < s; ++m)
    {
        if (n_roots >= deg)
            break;

        r = factor_1 + pow(factor_2, (2*m+1)/(4*s));

        for (n=0; n<N; ++n)
        {
            if (n_roots >= deg)
                break;

            theta = 2*PI*n/N;
            p = r * (cos(theta) + dbl_I*sin(theta));

            for (iter = 0U; iter < root_finder_max_iter; ++iter)
            {
                f_p = poly_eval(p);
                df_p = poly_prime_eval(p);
                d2f_p = poly_double_prime_eval(p);
                root = p - 2.0*f_p * df_p / (2*df_p*df_p - f_p * d2f_p);
                if (cabs(poly_eval(root)) < 1.0e-10)
                    break;

                p = root;
            }

            if (cabs(poly_eval(root)) < 1.0E-8)
            {
                if (n_roots == 0)
                {
                    n_roots += 1;
                    roots[0] = root;
                }
                else
                {
                    min = cabs(root - roots[0]);
                    for (ell=1; ell<n_roots; ++ell)
                    {
                        temp = cabs(root - roots[ell]);
                        if (temp < min)
                            min = temp;
                    }

                    if (min >= 0.000001)
                    {
                        roots[n_roots] = root;
                        n_roots += 1;
                    }
                }
            }
        }
    }

    return n_roots;
}

static void color(struct color c, FILE *fp)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;

    complex double f_z, df_z, d2f_z, z, root, roots[DEG];
    unsigned int n_roots;
    const complex double dbl_I = (complex double)_Complex_I;
    int x, y;
    double z_x, z_y, min, temp, scale;

    /*  The colors for the drawing.                                           */
    struct color colors[14] = {

        /*  Red. RGB = (255, 0, 30).                                          */
        {0xFFU, 0x00U, 0x1EU},  

        /*  Green. RGB = (0, 255, 30).                                        */
        {0x00U, 0xFFU, 0x1EU},


        /*  Blue. RGB = (0, 30, 255).                                         */
        {0x00U, 0x1EU, 0xFFU},

        /*  Yellow. RGB = (255, 255, 51).                                     */
        {0xFF, 0xFF, 0x33U},

        /*  Light Blue. RGB = (128, 212, 255).                                */
        {0x80U, 0xD4U, 0xFFU},

        /*  Magenta. RGB = (255, 29, 206).                                    */
        {0xFFu, 0x1DU, 0xCEU},

        /*  Teal. RGB = (0, 128, 128).                                        */
        {0x00U, 0x80U, 0x80U},

        /*  Purple. RGB = (255, 0, 255).                                      */
        {0xFFU, 0x00U, 0xFFU},

        /*  Orange. RGB = (255, 85, 0).                                       */
        {0xFFU, 0x55U, 0x00U},

        /*  Turquoise.  RGB = (77, 255, 196).                                 */
        {0x4DU, 0xFFU, 0xC4U},

        /*  Pine. RGB = (0, 128, 106).                                        */
        {0x00U, 0x80U, 0x6AU},

        /*  Melon. RGB = (255, 191, 179).                                     */
        {0xFFU, 0xBFU, 0xB3U},

        /*  Mauve. RGB = (255, 179, 230).                                     */
        {0xFFU, 0xB3U, 0xE6U},

        /*  Midnight Blue. RGB = (102, 51, 102).                              */
        {0x66U, 0x33U, 0x66U}
    };

    /*  Colors for the roots (Red, Green, Blue).                              */
    struct color brightness;
    const struct color black = {0x00U, 0x00U, 0x00U};

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  Factor for giving the image a gradient.                               */
    unsigned char factor = 255/MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned int iters, ind, n;

    n_roots = get_roots(DEG, roots);

    if (n_roots == 0U)
    {
        puts("No Roots Found. Aborting.");
        return -1;
    }
    else if (roots == NULL)
    {
        puts("get_roots returned NULL for roots pointer. Aborting.");
        return -1;
    }

    fp = fopen("halley_fractal.ppm", "w");
    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    for (y=0; y<size; ++y)
    {
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x + dbl_I*z_y;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            for (iters=0; iters<MaxIters; ++iters)
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                f_z = poly_eval(z);
                df_z = poly_prime_eval(z);
                d2f_z = poly_double_prime_eval(z);
                root = z - 2.0*f_z * df_z / (2*df_z*df_z - f_z * d2f_z);

                /*  Checks for convergence.                                   */
                if (cabs(root - z) < 10e-10)
                    break;

                z = root;
            }

            /*  Find which roots the final iteration is closest too.          */
            min = cabs(z-roots[0]);
            ind = 0;

            for (n=1; n<n_roots; ++n)
            {
                temp = cabs(z - roots[n]);
                if (temp < min)
                {
                    min = temp;
                    ind = n;
                }
            }

            if (min > 0.1)
                color(black, fp);
            else
            {
                scale = (255.0-factor*iters)/255.0;
                brightness.red = (unsigned char)(scale * colors[ind].red);
                brightness.green = (unsigned char)(scale * colors[ind].green);
                brightness.blue = (unsigned char)(scale * colors[ind].blue);

                /*  Color the current pixel.                                  */
                color(brightness, fp);
            }
        }
    }

    return 0;
}
