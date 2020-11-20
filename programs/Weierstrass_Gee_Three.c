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
const int size = 4*1024;
const unsigned int MaxIters = 100;

/******************************************************************************
 ******************************************************************************
 *                            End User Input                                  *
 ******************************************************************************
 ******************************************************************************/

const double PI = 3.14159265358979323846264338327950288419716;
const double g_fac = 284.856057355645759120065020341457747812508897;
double *divisor_quintic_table;

static double divisor_quintic(int N)
{
    int n;
    double out;

    out = 0.0;
    for (n=1; n<=N; ++n)
        if ((N % n) == 0)
            out += n*n*n*n*n;

    return out;
}

static complex double gee_three(complex double z)
{
    complex double sum, q, q_power;
    unsigned int n;

    if (cabs(z) >= 1.0)
        return 0.0;

    q = z*z;
    q_power = 1.0;
    sum = 0.0;

    for (n=0; n<MaxIters; ++n)
    {
        q_power *= q;
        sum += divisor_quintic_table[n]*q_power;
    }
    return g_fac*(1.0 - 504.0*sum);
}

static double *get_divisors(unsigned int N)
{
    unsigned int n;
    double *out;
    out = malloc(sizeof(*out) * N);

    for (n=1; n<=N; ++n)
        out[n-1] = divisor_quintic(n);

    return out;
}

static void set_color(unsigned char *color, double x)
{
    unsigned char val;
    x = ceil(pow(10*fabs(x), 0.25));

    if (x > 255)
        val = 255;
    else
        val = (unsigned char) x;

    color[0] = (unsigned char)val;
    color[1] = (unsigned char)val;
    color[2] = (unsigned char)val;
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
    FILE *g3_re, *g3_im;
    g3_re = fopen("gee_three_real.ppm", "w");
    g3_im = fopen("gee_three_imag.ppm", "w");

    divisor_quintic_table = get_divisors(MaxIters);

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  More dummy variables to loop over.                                    */
    int x, y;
    double z_x, z_y, remin, remax, immin, immax, re, im;
    complex double z, g;
    remin = 0;
    remax = 0;
    immin = 0;
    immax = 0;


    fprintf(g3_re, "P6\n%d %d\n255\n", size, size);
    fprintf(g3_im, "P6\n%d %d\n255\n", size, size);

    /*  Colors for the roots (Red, Green, Blue).                              */
    unsigned char *brightness = malloc(sizeof(*brightness) * 3);

    for (y=0; y<size; ++y)
    {
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x + _Complex_I*z_y;

            if (cabs(z) >= 1.0)
            {
                color((char)0, (char)0, (char)0, g3_re);
                color((char)0, (char)0, (char)0, g3_im);
            }
            else
            {
                g = gee_three(z);

                re = creal(g);
                im = cimag(g);

                if (re > remax)
                    remax = re;

                if (re < remin)
                    remin = re;

                if (im > immax)
                    immax = re;

                if (re < remin)
                    immin = re;


                /*  Color the current pixel.                                  */
                set_color(brightness, re);
                color(brightness[0], brightness[1], brightness[2], g3_re);

                set_color(brightness, im);
                color(brightness[0], brightness[1], brightness[2], g3_im);
            }
        }
    }

    printf("%f %f\t\t%f %f\n", remin, remax, immin, immax);


    /*  Free the memory allocated to colors before returning.                 */
    free(divisor_quintic_table);
    return 0;
}
