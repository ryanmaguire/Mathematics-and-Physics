// This creates a rasterized image of a sphere. To run, do:
//      ./circle >> circle.ppm

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// This function colors the current pixel in the format (R, G, B).
void color(int red, int green, int blue)
{
    fputc((char)red,   stdout);
    fputc((char)green, stdout);
    fputc((char)blue,  stdout);
}

// Function for computing the Euclidean distance from z0 to z1.
double norm(double *z0, double *z1){
    double x, y;
    x = z1[0] - z0[0];
    y = z1[1] - z0[1];
    return sqrtl(x*x+y*y);
}

int main(int argc, char *argv[])
{
    // Pixel size of the image to be created.
    int size = 1024;

    // Divide by two before hand to save on division computations.
    double size_by_two = size / 2.0;

    // Radius of the final image.
    double image_radius = 2.0;

    // Radius of the circle to be drawn.
    double circle_radius = 1.0;

    // Scale factor for incrementing through each pixel.
    double scale_factor = 2*image_radius/size;

    // Array for the center of the sphere.
    double center[2];

    // Array for the current point being computed.
    double point[2];

    // Set the the center to the origin (0, 0).
    center[0] = 0;
    center[1] = 0;

    // Variable used for determining how bright a given pixel is.
    int brightness;

    // Variables used for indexing over the x and y coordinates.
    int x, y;

    // Variable used for the distance from point to center.
    double dist;

    printf("P6\n# CREATOR: Ryan Maguire\n");
    printf("%d %d\n255\n", size, size);

    //  Loop through each pixel.
    for(y = 0; y < size; y++){
        for(x = 0; x < size; x++){

            // Calculate the location of the current point.
            point[0] = (x - size_by_two) * scale_factor;
            point[1] = (y - size_by_two) * scale_factor;

            // Compute the distance from point to center.
            dist = norm(point, center);

            // If the point is outside of the circle, skip.
            if(dist > circle_radius) color(255, 255, 255);
            else {
                brightness = (int)255*(1.0-dist/circle_radius);;
                color(brightness, brightness, brightness);
            }
        }
    }
    return 0;
}
