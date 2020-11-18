#include <stdio.h>
#include <math.h>
#include <complex.h>

/*  We'll need the following data types for planar and spherical points.      */
typedef struct two_vec {
    double dat[2];
} two_vec;

typedef struct three_vec {
    double dat[3];
} three_vec;

/******************************************************************************
 ******************************************************************************
 *                          Begin User Input                                  *
 ******************************************************************************
 ******************************************************************************/

/*  The roots of z^3 - 1.                                                     */
const complex double ROOT_1 = 1.0;
const complex double ROOT_2 = -0.5 + 0.8660254037844386*_Complex_I;
const complex double ROOT_3 = -0.5 - 0.8660254037844386*_Complex_I;

/*  Create a variable for the number of roots. z^3-1 has three.               */
#define NRoots 3

/* List the roots of z^3 - 1.                                                 */
complex double roots[NRoots] = {ROOT_1, ROOT_2, ROOT_3};

/*  Define the camera angle for the image of the sphere. This is where the    *
 *  observer looking at the sphere will be placed. The output image is        *
 *  normalized to take up the entire screen, so u and lambda*u will have the  *
 *  same result for any positive lambda. u and -u will have different results.*/
three_vec camera_pos = {{0.0, 0.0, 1.0}};

/*  Define the polynomial z^3 - 1 and it's derivative. You can change this    *
 *  polynomial to whatever you want, but you will need to adjust the roots.   */
static complex double f(complex double z)
{
    return z*z*z - 1.0;
}

static complex double f_prime(complex double z)
{
    return 3.0*z*z;
}

/*  The colors used for drawing. We're setting this as red, green, blue. If   *
 *  you have a polynomial with more than three roots, you'll need more than   *
 *  three colors.                                                             */
unsigned char colors[NRoots][3] = {
    {255, 0, 30}, {0, 255, 30}, {0, 30, 255}
};

/******************************************************************************
 ******************************************************************************
 *                            End User Input                                  *
 ******************************************************************************
 ******************************************************************************/

static three_vec normalize_three_vec(three_vec p)
{
    three_vec out;
    double norm, rcpr_norm;

    norm = sqrt(p.dat[0]*p.dat[0] + p.dat[1]*p.dat[1] + p.dat[2]*p.dat[2]);
    rcpr_norm = 1.0/norm;

    out.dat[0] = p.dat[0]*rcpr_norm;
    out.dat[1] = p.dat[1]*rcpr_norm;
    out.dat[2] = p.dat[2]*rcpr_norm;

    return out;
}

static three_vec cross_product(three_vec p, three_vec q)
{
    three_vec out;

    out.dat[0] = p.dat[1]*q.dat[2] - p.dat[2]*q.dat[1];
    out.dat[1] = p.dat[2]*q.dat[0] - p.dat[0]*q.dat[2];
    out.dat[2] = p.dat[0]*q.dat[1] - p.dat[1]*q.dat[0];

    return out;
}

static three_vec scale_three_vec(double x, three_vec p)
{
    three_vec out;

    out.dat[0] = x*p.dat[0];
    out.dat[1] = x*p.dat[1];
    out.dat[2] = x*p.dat[2];

    return out;
}

static three_vec sum_three_vec(three_vec p, three_vec q)
{
    three_vec out;

    out.dat[0] = p.dat[0] + q.dat[0];
    out.dat[1] = p.dat[1] + q.dat[1];
    out.dat[2] = p.dat[2] + q.dat[2];

    return out;
}

static two_vec stereographic_projection(three_vec p)
{
    double X, Y, denom;
    two_vec out;

    denom = 1.0/(1.0-p.dat[2]);
    X = p.dat[0]*denom;
    Y = p.dat[1]*denom;

    out.dat[0] = X;
    out.dat[1] = Y;

    return out;
}

static three_vec inverse_orthographic_projection(two_vec p, three_vec u)
{
    double ux, uy, x, y, z;
    three_vec out, X, Y;

    ux = u.dat[0];
    uy = u.dat[1];

    if (ux == 0.0)
    {
        X.dat[0] = 1.0;
        X.dat[1] = 0.0;
        X.dat[2] = 0.0;
    }
    else
    {
        if (uy == 0.0)
        {
            X.dat[0] = 0.0;
            X.dat[1] = 1.0;
            X.dat[2] = 0.0;
        }
        else
        {
            X.dat[0] = 1.0;
            X.dat[1] = -uy/ux;
            X.dat[2] = 0.0;
        }

        X = normalize_three_vec(X);
    }

    Y = cross_product(X, u);
    x = p.dat[0];
    y = p.dat[1];
    z = sqrt(1.0 - x*x - y*y);

    out = sum_three_vec(
        sum_three_vec(scale_three_vec(x, X), scale_three_vec(y, Y)),
        scale_three_vec(z, u)
    );

    return out;
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
    fp = fopen("newton_cubic_fractal_on_sphere.ppm", "w");

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    three_vec u = normalize_three_vec(camera_pos);
    three_vec p;
    two_vec Z, proj_p;

    /*  The number of pixels in the x and y axes.                             */
    int size  = 2*1024;

    /* MaxIters should be less than 256, or we'll run out of colors.          */
    unsigned char MaxIters = 32;
    unsigned char factor   = 255/MaxIters;

    /* Dummy variables to loop over.                                          */
    int iters, ind, n;

    /*  More dummy variables to loop over.                                    */
    int x, y;
    double z_x, z_y, min;
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

            if ((z_x*z_x + z_y*z_y) <= 1.0)
            {
                Z.dat[0] = z_x;
                Z.dat[1] = z_y;

                p = inverse_orthographic_projection(Z, u);

                if (p.dat[2] >= 0.999999)
                    color(0, 0, 0, fp);
                else
                {

                    proj_p = stereographic_projection(p);
                    z = proj_p.dat[0] + _Complex_I*proj_p.dat[1];

                    /*  Allow iters number of iterations for Newton-Raphson.  */
                    for (iters=0; iters<MaxIters; ++iters)
                    {
                        /*  Perfrom Newton-Raphson on z^3 - 1.                */
                        root = z - f(z)/f_prime(z);

                        /*  Checks for convergence.                           */
                        if (cabs(root - z) < 10e-10)
                            break;

                        z = root;
                    }

                    /*  Find which roots the final iteration is closest too.  */
                    min = cabs(z-roots[0]);
                    ind = 0;

                    for (n=1; n<NRoots; ++n)
                    {
                        if (cabs(z - roots[n]) < min)
                        {
                            min = cabs(z-roots[n]);
                            ind = n;
                        }
                    }

                    for (n=0; n<3; ++n)
                        brightness[n] = colors[ind][n];

                    /*  Create a gradient to emphasize rate of convergence.   */
                    brightness[ind] -= (unsigned char)factor*iters;

                    /*  Color the current pixel.                              */
                    color(brightness[0], brightness[1], brightness[2], fp);
                }
            }
            else
                color((char)0, (char)0, (char)0, fp);
        }
    }
    return 0;
}
