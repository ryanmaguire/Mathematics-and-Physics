#include "nf.h"

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;
    fp = fopen("newton_fractal_on_sphere.ppm", "w");

    /*  Struct for the roots.                                                 */
    root_struct *roots_of_f = get_roots();

    unsigned int n_roots = roots_of_f->n_roots;
    complex double *roots = roots_of_f->roots;

    /*  The colors for the drawing.                                           */
    unsigned char **colors = get_colors();

    three_vec u = normalize_three_vec(camera_pos);
    three_vec p;
    two_vec Z, proj_p;

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

                    /*  Allow MaxIters number of iterations of Newton-Raphson.*/
                    for (iters=0; iters<MaxIters; ++iters)
                    {
                        /*  Perfrom Newton-Raphson on the polynomial f.       */
                        root = z - f(z)/f_prime(z);

                        /*  Checks for convergence.                           */
                        if (cabs(root - z) < 10e-10)
                            break;

                        z = root;
                    }

                    /*  Find which roots the final iteration is closest too.  */
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

                        /*  Color the current pixel.                          */
                        color(brightness[0], brightness[1], brightness[2], fp);
                    }
                }
            }
            else
                color((char)0, (char)0, (char)0, fp);
        }
    }

    /*  Free the memory allocated to colors before returning.                 */
    destroy_colors(colors);
    destroy_roots(roots_of_f);
    return 0;
}
