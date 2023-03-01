/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Perform a simple raytracing of a black hole using classical physics,  *
 *      instead of relativity. Light is given an arbitrarily small mass and   *
 *      we use Newton's universal law of gravitation to see how a black hole  *
 *      would bend the light. This is a very rough estimate of black holes.   *
 *      In addition to the checkerboard pattern, a rainbow gradient is added  *
 *      to the image based on the direction of the photon of light as it      *
 *      hits the detector.                                                    *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as a part of the libtmpl  *
 *      library. It is also written in C++, just to mix things up a bit.      *
 *      I checked GNU's g++ with pedantic compiler warnings against C++98,    *
 *      C++11, and C++17 and recieved no warnings.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 12, 2021                                                  *
 ******************************************************************************/

/*  Needed for the FILE data type and fprintf function.                       */
#include <cstdio>

/*  Square root function found here.                                          */
#include <cmath>

/*  A simple structure for dealing with vectors. Vectors are treated as rays  *
 *  of light moving under the influence of the gravity of a black hole.       */
struct tmpl_simple_vector {

    /*  A vector will be defined by it's Euclidean components, x, y, z.       */
    double x, y, z;

    /*  Empty constructor. Simply return.                                     */
    tmpl_simple_vector(void)
    {
        return;
    }

    /*  Simple method for creating a vector. Simply set the x, y, and z parts *
     *  to the values a, b, and c, respectively.                              */
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  This operator represents vector addition.                             */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }

    /*  And here we have scalar multiplication.                               */
    tmpl_simple_vector operator * (double r)
    {
        return tmpl_simple_vector(x*r, y*r, z*r);
    }

    /*  This operator will denote the Euclidean dot product of two vectors.   */
    double operator % (tmpl_simple_vector r)
    {
        return x*r.x + y*r.y + z*r.z;
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double norm(void)
    {
        return std::sqrt(*this % *this);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double normsq(void)
    {
        return *this % *this;
    }
};
/*  End of definition of tmpl_simple_vector.                                  */

/*  Struct for working with RGB colors.                                       */
struct tmpl_simple_color {

    /*  A color in a computer is defined by its Red, Green, and Blue parts.   */
    unsigned char red, green, blue;

    /*  Empty constructor. Simply return.                                     */
    tmpl_simple_color(void)
    {
        return;
    }

    /*  Set the red, green, and blue components to the given inputs.          */
    tmpl_simple_color(unsigned char r, unsigned char g, unsigned char b)
    {
        red   = r;
        green = g;
        blue  = b;    
    }

    /*  Operator for adding colors. We take the average of the components.    */
    tmpl_simple_color operator + (tmpl_simple_color c)
    {
        /*  To avoid overflows, convert to double and perform the sum.        */
        double x, y, z;
        unsigned char r, g, b;

        /*  Cast the values to doubles and take the average, component-wise.  */
        x = 0.5 * ((double)red   + (double)c.red);
        y = 0.5 * ((double)green + (double)c.green);
        z = 0.5 * ((double)blue  + (double)c.blue);

        /*  Cast the double back to unsigned char's and return.               */
        r = (unsigned char)x;
        g = (unsigned char)y;
        b = (unsigned char)z;
        return tmpl_simple_color(r, g, b);
    }

    /*  Function for writing the color to a PPM file.                         */
    void write(FILE *fp)
    {
        /*  The order we write this matters. PPM wants red-green-blue.        */
        std::fputc(red, fp);
        std::fputc(green, fp);
        std::fputc(blue, fp);
    }
};
/*  End of tmpl_simple_color.                                                 */

/*  Function for creating a rainbow-gradient based on the angle the velocity  *
 *  vector makes with the detector.                                           */ 
static tmpl_simple_color color_gradient(tmpl_simple_vector v)
{
    /*  Declare unsigned char's for computing the output color.               */
    unsigned char red, green, blue;

    /*  And two doubles for dealing with the angle.                           */
    double angle, scaled;

    /*  We want the zenith angle of the velocity vector. This can be computed *
     *  using the cylindrical coordinates of the vector.                      */
    angle = std::atan2(std::fabs(v.z), std::sqrt(v.x*v.x + v.y*v.y));
    
    /*  Scale the angle so that it falls between 0 and 255.                   */
    scaled = 255.0 * angle / M_PI_2;

    /*  Use an RGB rainbow gradient to color the current pixel. We'll set     *
     *  blue to correspond to the least value and red for the greatest, with  *
     *  a continuous gradient in between.                                     */
    if (scaled < 64)
    {
        red   = (unsigned char)0;
        green = (unsigned char)(4.0*scaled);
        blue  = (unsigned char)255;
    }
    else if (scaled < 128)
    {
        red   = (unsigned char)0;
        green = (unsigned char)255;
        blue  = (unsigned char)(255 - 4*(scaled - 64));
    }
    else if (scaled < 192)
    {
        red   = (unsigned char)(4.0*(scaled-128));
        green = (unsigned char)255;
        blue  = (unsigned char)0;
    }
    else if (scaled < 255)
    {
        red   = (unsigned char)255;
        green = (unsigned char)(255 - 4*(scaled-192));
        blue  = (unsigned char)0;
    }
    else
    {
        red   = (unsigned char)255;
        green = (unsigned char)0;
        blue  = (unsigned char)0;
    }
    
    return tmpl_simple_color(red, green, blue);
} 


/*  Main function for performing the raytracing.                              */
int main(void)
{
    /*  The vector v represents the initial velocity vector of a particle of  *
     *  light. Since our light rays are being directed downwards, this vector *
     *  should be (0, 0, -c), where c is the speed of light. We can take this *
     *  to be 1 for simplicity. Adjusting this value would be equivalent to   *
     *  adjusting the strength of Gravity. Smaller values mean stronger       *
     *  gravity, and larger values mean weaker gravity.                       */
    tmpl_simple_vector v, v_start;
    tmpl_simple_color white = tmpl_simple_color(255U, 255U, 255U);
    tmpl_simple_color red   = tmpl_simple_color(255U, 0U, 0U);
    tmpl_simple_color black = tmpl_simple_color(0U, 0U, 0U);
    tmpl_simple_color color;
    tmpl_simple_vector p;
    unsigned int x, y, size;
    double factor, start, end, dt;

    /*  The velocity will change throughout the computation. This is against  *
     *  relativistic physics, which says the speed of light is constant. It   *
     *  will also be possible, in this model, for light to travel faster      *
     *  than the speed of light since gravity will accelerate it. This is why *
     *  our computation is a very rough estimate.                             */
    v_start = tmpl_simple_vector(0.0, 0.0, -1.0);
    v = v_start;

    /*  Set the values for the size of the detector. I've chosen the square   *
     *  [-10, 10]^2.                                                          */
    start = -10.0;
    end   = 10.0;
    
    /*  The step-size for our increment in time.                              */
    dt = 0.01;

    /*  Set the number of pixels in the detector.                             */
    size = 1024U;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    factor = (end - start) / (double)(size - 1U);

    /*  Open the file "black_hole_gradient.ppm" and give write permissions.   */
    FILE *fp = std::fopen("black_hole_gradient.ppm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble to the PPM file. A PPM file wants Pn followed by   *
     *  three numbers. P6 means we're encoding an RGB image in binary format. *
     *  The first two numbers are the number of pixels in the x and y axes.   *
     *  The last number is the size of our color spectrum, which is 255.      */
    std::fprintf(fp, "P6 %u %u\n255\n", size, size);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential. If we wanted to *
     *  introduce parallel processing, we would need to store the colors in   *
     *  an array, and then create the PPM from that array. For the simplicity *
     *  of the code, this is not done.                                        */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            p = tmpl_simple_vector(start + factor*x, start + factor*y, 10.0);

            /*  Raytrace where the photon that hit p came from.               */
            p = Path(p, v, dt);

            /*  If the photon never made it to the detector, assume it was    *
             *  captured by the black hole and color the pixel black.         */
            if (p.norm() < 9.9)
                color = black;

            /*  Otherwise, use this bitwise AND trick to create a             *
             *  checkerboard pattern of red and white.                        */
            else if ((int)(std::ceil(p.x) + std::ceil(p.y)) & 1)
                color = white + color_gradient(v);

            else
                color = red + color_gradient(v);

            /*  Write the color to the PPM file and reset the velocity vector.*/
            color.write(fp);
            v = v_start;

        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */

