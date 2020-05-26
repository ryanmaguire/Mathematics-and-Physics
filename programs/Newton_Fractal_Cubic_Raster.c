#include <stdio.h>
#include <complex.h>

#define Half_Sqrt_3_I 0.8660254037844386*_Complex_I
#define Two_Thirds    0.6666666666666666

#define ROOT_1 1.0
#define ROOT_2 -0.5+Half_Sqrt_3_I
#define ROOT_3 -0.5-Half_Sqrt_3_I

/*  Create a variable for the number of roots. z^3-1 has three.               */
#define NRoots 3

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
    complex double roots[NRoots] = {ROOT_1, ROOT_2, ROOT_3};

    /*  More dummy variables to loop over.                                     */
    int x, y;

    double z_x, z_y, min;
    complex double z, root;


    printf("P6\n# CREATOR: Ryan / Newton Fractal\n");
    printf("%d %d\n255\n",size,size);

    // Colors for the roots (Red, Green, Blue).
    char colors[NRoots][3] = {{255, 0, 30}, {0, 255, 30}, {0, 30, 255}};
    char brightness[3];

    for (y=0; y<size; ++y){
        z_y = y * (y_max - y_min)/(size - 1) + y_min;

        for (x=0; x<size; ++x){
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x+_Complex_I*z_y;

            // Allow iters number of iterations for Newton-Raphson.
            for (iters=0; iters<MaxIters; ++iters){

                // Perfrom Newton-Raphson on z^3 - 1 (Simplifying as well).
                root = Two_Thirds*z + 1.0/(3.0*z*z);

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

            for (i=0; i<3; ++i){
                brightness[i] = colors[ind][i];
            }

            // Create a gradient in color to emphasize rate of convergence.
            brightness[ind] -= factor*iters;

            // Color the current pixel.
            color(brightness[0], brightness[1], brightness[2]);
        }
    }
    return 0;
}