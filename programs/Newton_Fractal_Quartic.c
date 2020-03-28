#include <stdio.h>
#include <complex.h>

#define Root_1 1.0
#define Root_2 1.0*_Complex_I
#define Root_3 -1.0
#define Root_4 -1.0*_Complex_I

/*  Create a variable for the number of roots. z^3-1 has three.               */
#define NRoots 4

void color(char red, char green, char blue)
{
    fputc(red,   stdout);
    fputc(green, stdout);
    fputc(blue,  stdout);
}

int main(int argc, char *argv[])
{
    /* Values for the min and max of the x and y axes.                        */
    double x_min = -1.0;
    double x_max =  1.0;
    double y_min = -1.0;
    double y_max =  1.0;

    /*  The number of pixels in the x and y axes.                             */
    int size  = 4*1024;

    /* MaxIters should be less than 256, or we'll run out of colors.          */
    char MaxIters = 32;
    char factor   = 255/MaxIters;

    /* Dummy variables to loop over.                                          */
    char iters, i, ind;

    /* List the roots of z^3 - 1.                                             */
    complex double roots[NRoots] = {Root_1, Root_2, Root_3, Root_4};

    /*  More dummy variables to loop over.                                     */
    int x, y;

    double z_x, z_y, min;
    complex double z, root;


    printf("P6\n# CREATOR: Ryan / Newton Fractal\n");
    printf("%d %d\n255\n",size,size);

    // Colors for the roots (Red, Green, Blue).
    char colors[NRoots][3] = {
        {255, 0,   30},     // Red
        {0,   255, 30},     // Green
        {0,   30,  255},    // Blue
        {255, 255, 0}       // Yellow
    };
    char brightness[3];

    for (y=0; y<size; ++y){
        z_y = y * (y_max - y_min)/(size - 1) + y_min;

        for (x=0; x<size; ++x){
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x+_Complex_I*z_y;

            // Allow iters number of iterations for Newton-Raphson.
            for (iters=0; iters<MaxIters; ++iters){

                // Perfrom Newton-Raphson on z^4 - 1 (Simplifying as well).
                root = 0.75*z + 1.0/(4.0*z*z*z);

                // Checks for convergence
                if (cabs(root - z) < 10e-10) break;
                z = root;
            }

            /*  Find which roots the final iteration is closest too.          */
            min = cabs(z-roots[0]);
            ind = 0;

            for (i=1; i<NRoots; ++i){
                if (cabs(z - roots[i]) < min) {
                    min = cabs(z-roots[i]);
                    ind = i;
                }
            }

            /* Create a gradient in color to emphasize rate of convergence.   */
            for (i=0; i<3; ++i){
                brightness[i] = colors[ind][i];
            }

            switch (ind)
            {
                case 3:
                    brightness[0] -= iters*factor;
                    brightness[1] -= iters*factor;
                    break;
                default:
                    brightness[ind] -= iters*factor;
                    break;
            }

            // Color the current pixel.
            color(brightness[0], brightness[1], brightness[2]);
        }
    }
    return 0;
}