#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

/******************************************************************************
 ******************************************************************************
 *                          Begin User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  The number of pixels in the x and y axes.                                 */
const int size = 2*1024;

/*  Maximum number of iterations for the Newton-Raphson method. This must be  *
 *  less than 255, otherwise we'll run out of colors.                         */
const unsigned int MaxIters = 32;

/*  Maximum number of iterations allowed before giving up on the root finding *
 *  algorithm. If no roots are found, the computation aborts.                 */
const unsigned int root_finder_max_iter = 200;

/*  The degree of the polynomial.                                             */
#define deg 10

/*  The coefficients of the polynomial. The zeroth coefficient is for z^deg   *
 *  and the last coefficient is the constant term.                            */
complex double coeffs[deg+1] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};

/******************************************************************************
 ******************************************************************************
 *                            End User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  We'll need the following data types for planar and spherical points.      */
typedef struct root_struct {
    complex double *roots;
    unsigned int n_roots;
} root_struct;

#define N_COLORS 14
const double PI = 3.14159265358979323846264338327950288419716;

/*  Function for setting colors that can be used in a drawing.                */
static unsigned char **get_colors(void)
{
    unsigned int n;
    unsigned char **colors = malloc(sizeof(*colors) * N_COLORS);

    for (n=0; n<N_COLORS; ++n)
        colors[n] = malloc(sizeof(*colors[n]) * 3);

    /*  Red.    */
    colors[0][0] = (unsigned char)255;
    colors[0][1] = (unsigned char)0;
    colors[0][2] = (unsigned char)30;

    /*  Green.  */
    colors[1][0] = (unsigned char)0;
    colors[1][1] = (unsigned char)255;
    colors[1][2] = (unsigned char)30;

    /*  Blue.   */
    colors[2][0] = (unsigned char)0;
    colors[2][1] = (unsigned char)30;
    colors[2][2] = (unsigned char)255;

    /*  Yellow. */
    colors[3][0] = (unsigned char)255;
    colors[3][1] = (unsigned char)255;
    colors[3][2] = (unsigned char)51;

    /*  Light Blue. */
    colors[4][0] = (unsigned char)128;
    colors[4][1] = (unsigned char)212;
    colors[4][2] = (unsigned char)255;

    /*  Magenta.    */
    colors[5][0] = (unsigned char)255;
    colors[5][1] = (unsigned char)29;
    colors[5][2] = (unsigned char)206;

    /*  Teal.   */
    colors[6][0] = (unsigned char)0;
    colors[6][1] = (unsigned char)128;
    colors[6][2] = (unsigned char)128;

    /*  Purple. */
    colors[7][0] = (unsigned char)255;
    colors[7][1] = (unsigned char)0;
    colors[7][2] = (unsigned char)255;

    /*  Orange. */
    colors[8][0] = (unsigned char)255;
    colors[8][1] = (unsigned char)85;
    colors[8][2] = (unsigned char)0;

    /*  Turquoise.  */
    colors[9][0] = (unsigned char)77;
    colors[9][1] = (unsigned char)255;
    colors[9][2] = (unsigned char)195;

    /*  Pine.   */
    colors[10][0] = (unsigned char)0;
    colors[10][1] = (unsigned char)128;
    colors[10][2] = (unsigned char)106;

    /*  Melon.  */
    colors[11][0] = (unsigned char)255;
    colors[11][1] = (unsigned char)191;
    colors[11][2] = (unsigned char)179;

    /*  Mauve.  */
    colors[12][0] = (unsigned char)255;
    colors[12][1] = (unsigned char)179;
    colors[12][2] = (unsigned char)230;

    /*  Midnight Blue.  */
    colors[13][0] = (unsigned char)102;
    colors[13][1] = (unsigned char)51;
    colors[13][2] = (unsigned char)102;

    return colors;
}

static void destroy_colors(unsigned char **colors)
{
    unsigned int n;
    for (n=0; n<N_COLORS; ++n)
        free(colors[n]);

    free(colors);
}

/*  Define the polynomial based on the user provided coefficients. Compute    *
 *  this via Horner's method for speed.                                       */
static complex double f(complex double z)
{
    complex double out;
    int n;

    out = coeffs[0];
    for (n=1; n<=deg; ++n)
        out = z*out + coeffs[n];

    return out;
}

static complex double f_prime(complex double z)
{
    complex double out;
    int n;

    out = deg*coeffs[0];
    for (n=1; n<deg; ++n)
        out = z*out + deg*coeffs[n];

    return out;
}

static complex double f_2prime(complex double z)
{
    complex double out;
    int n;

    out = deg*(deg-1)*coeffs[0];
    for (n=1; n<deg-1; ++n)
        out = z*out + deg*(deg-1)*coeffs[n];

    return out;
}

static complex double f_3prime(complex double z)
{
    complex double out;
    int n;

    out = deg*(deg-1)*(deg-2)*coeffs[0];
    for (n=1; n<deg-2; ++n)
        out = z*out + deg*(deg-1)*(deg-2)*coeffs[n];

    return out;
}

static root_struct *get_roots(void)
{
    root_struct *out = malloc(sizeof(*out));
    complex double p, root, f_p, df_p, d2f_p, d3f_p;
    unsigned int m, n, ell, iter, s, N, n_roots;
    double r, theta, factor_1, factor_2, min, temp;

    out->roots = malloc(sizeof(*out->roots) * deg);

    s = (int)ceil(0.26632*log(deg));
    N = (int)ceil(8.32547*deg*log(deg));
    n_roots = 0;

    factor_1 = 1.0+sqrt(2);
    factor_2 = (deg-1.0)/deg;


    for (m=0; m<s; ++m)
    {
        if (n_roots >= deg)
            break;

        r = factor_1 + pow(factor_2, (2*m+1)/(4*s));

        for (n=0; n<N; ++n)
        {
            if (n_roots >= deg)
                break;

            theta = 2*PI*n/N;
            p = r * (cos(theta) + _Complex_I*sin(theta));

            for (iter=0; iter<root_finder_max_iter; ++iter)
            {
                f_p = f(p);
                df_p = f_prime(p);
                d2f_p = f_2prime(p);
                d3f_p = f_3prime(p);
                root = p - 3 * f_p * (2*df_p * df_p - f_p * d2f_p) /
                    (6*df_p*df_p*df_p - 6*f_p*df_p*d2f_p + f_p*f_p*d3f_p);
                if (cabs(f(root)) < 1.0e-10)
                    break;

                p = root;
            }

            if (cabs(f(root)) < 1.0e-8)
            {
                if (n_roots == 0)
                {
                    n_roots += 1;
                    out->roots[0] = root;
                }
                else
                {
                    min = cabs(root - out->roots[0]);
                    for (ell=1; ell<n_roots; ++ell)
                    {
                        temp = cabs(root - out->roots[ell]);
                        if (temp < min)
                            min = temp;
                    }
                    if (min >= 0.000001)
                    {
                        out->roots[n_roots] = root;
                        n_roots += 1;
                    }
                }
            }
        }
    }

    if (n_roots == 0)
    {
        puts("\nError:");
        puts("\tFailed to find the roots. Aborting.\n");
        exit(0);
    }
    else
        out->n_roots = n_roots;

    printf("Number of roots: %d\n", n_roots);
    for (n=0; n<n_roots; ++n)
        printf(
            "\troot %d: %f + i%f\n", n,
            creal(out->roots[n]), cimag(out->roots[n])
        );

    return out;
}

static void destroy_roots(root_struct *the_roots)
{
    free(the_roots->roots);
    free(the_roots);
}

void color(char red, char green, char blue, FILE *fp)
{
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;
    fp = fopen("householder_fractal.ppm", "w");

    /*  Struct for the roots.                                                 */
    root_struct *roots_of_f = get_roots();

    complex double f_z, df_z, d2f_z, d3f_z;
    unsigned int n_roots = roots_of_f->n_roots;
    complex double *roots = roots_of_f->roots;

    /*  The colors for the drawing.                                           */
    unsigned char **colors = get_colors();

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  Factor for giving the image a gradient.                               */
    unsigned char factor = 255/MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned int iters, ind, n;

    /*  More dummy variables to loop over.                                    */
    int x, y;
    double z_x, z_y, min, temp, scale;
    complex double z, root;

    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    /*  Colors for the roots (Red, Green, Blue).                              */
    unsigned char brightness[3];

    for (y=0; y<size; ++y)
    {
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x + _Complex_I*z_y;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            for (iters=0; iters<MaxIters; ++iters)
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                f_z = f(z);
                df_z = f_prime(z);
                d2f_z = f_2prime(z);
                d3f_z = f_3prime(z);
                root = z - 3 * f_z * (2*df_z*df_z - f_z*d2f_z) /
                    (6*df_z*df_z*df_z - 6*f_z*df_z*d2f_z + f_z*f_z*d3f_z);

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
                color((char)0, (char)0, (char)0, fp);
            else
            {
                scale = (255.0-factor*iters)/255.0;
                for (n=0; n<3; ++n)
                    brightness[n] =
                        (unsigned char)(scale * colors[ind][n]);

                /*  Color the current pixel.                                  */
                color(brightness[0], brightness[1], brightness[2], fp);
            }
        }
    }

    /*  Free the memory allocated to colors before returning.                 */
    destroy_colors(colors);
    destroy_roots(roots_of_f);
    return 0;
}
