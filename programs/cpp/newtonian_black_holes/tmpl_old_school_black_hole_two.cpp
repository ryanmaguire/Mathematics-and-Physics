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
 *      Perform a simple raytracing of a binary system of two black holes.    *
 *      This naively uses Newtonian mechanics, and not relativity.            *
 *  Notes:                                                                    *
 *      This file is an "extra" and is not compiled as a part of the libtmpl  *
 *      library. It is also written in C++, just to mix things up a bit.      *
 *      I checked GNU's g++ with pedantic compiler warnings against C++98,    *
 *      C++11, and C++17 and recieved no warnings.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 6, 2021                                                   *
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

    /*  This operator represents vector subtraction.                          */
    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
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

/*  Set the following vectors to represent the centers of the black holes.    */
tmpl_simple_vector b1 = tmpl_simple_vector(-3.0, 0.0, 0.0);
tmpl_simple_vector b2 = tmpl_simple_vector(+3.0, 0.0, 0.0);

/*  The acceleration under the force of gravity is given by Newton's          *
 *  universal law of gravitation. This is the inverse square law.             */
static tmpl_simple_vector acc(tmpl_simple_vector p)
{
    /*  We'll use the principle of superposition for the two black holes.     */
    tmpl_simple_vector r1, r2;
    tmpl_simple_vector f1, f2;
    double factor1, factor2;

    /*  The force from one black hole is -R / ||R||^3, where R is the         *
     *  relative position vector from the point p to the center of the black  *
     *  hole. Compute this expression for both black holes.                   */
    r1 = b1 - p;
    r2 = b2 - p;

    factor1 = 1.0 / (r1.normsq() * r1.norm());
    factor2 = 1.0 / (r2.normsq() * r2.norm());

    f1 = r1 * factor1;
    f2 = r2 * factor2;

    /*  The net force is computed by the principle of superposition. Simply   *
     *  sum the two individual forces and return.                             */
    return f1 + f2;
}

/*  Function for computing the path of a light ray under the influence of     *
 *  the gravity of a black hole using Euler's method.                         */
static tmpl_simple_vector
Path(tmpl_simple_vector p, tmpl_simple_vector v, double dt)
{
    /*  After a finite number of iterations of Euler's method, we'll abort.   */
    unsigned int N = 0U;

    /*  The light is coming from the plane z = -10 and coming towards our     *
     *  eyes. We work backwards to see where an individual photon came from.  *
     *  Once we work backwards to z = -10, we've hit our light source and can *
     *  stop the computation. If the computation takes to long, it is trapped *
     *  within this binary system and will never reach z = -10.               */
    while ((p.z > -10.0) && (N < 1E6))
    {
        /* If the light was absorbed by a black hole, abort the computation.  */
        if (((b1 - p).norm() <= 1.0) || ((b2 - p).norm() <= 1.0))
            return p;

        /*  We numerically solve d^2/dt^2 p = F(p) in two steps. First, we    *
         *  compute the velocity dp/dt, meaning we need to solve dv/dt = F(p).*
         *  We solve numerically with Euler's method. Then we use this v to   *
         *  compute p via dp/dt = v, again solving numerically with Euler's   *
         *  method. So long as dt is small, the error should be small as well.*/
        p = p + v * dt;
        v = v + acc(p) * dt;

        /*  It is possible that a photon was captured into orbit, but not     *
         *  absorbed into a black hole. To avoid an infinite loop, abort      *
         *  the computation once N gets to large.                             */
        ++N;
    }

    return p;
}
/*  End of Path function.                                                     */

/*  Function for coloring a pixel red.                                        */
static void color_red(FILE *fp, tmpl_simple_vector p)
{
    /*  The amount of light entering a small area goes inversally with the    *
     *  square of the distance between this area and the light source. We     *
     *  illuminate the detector based on this idea to give a gradient of      *
     *  light-intensity to better understand which photons are coming from    *
     *  where. Since the detector is the plane z = -10, the max value of      *
     *  1/||p||^2 is 100. RGB color takes values between 0 and 255, so we     *
     *  need to normalize 1/||p||^2 so that the max value is 255.             */
    double x = 25500.0/p.normsq();

    /*  RGB is Red-Green-Blue. Red is (255, 0, 0).                            */
    fputc(int(x), fp);
    fputc(0, fp);
    fputc(0, fp);
}

/*  Same idea of coloring, but with a gray-to-white gradient.                 */
static void color_white(FILE *fp, tmpl_simple_vector p)
{
    double x = 25500.0/p.normsq();
    fputc(int(x), fp);
    fputc(int(x), fp);
    fputc(int(x), fp);
}

/*  Black represents the black hole.                                          */
static void color_black(FILE *fp)
{
    fputc(0, fp);
    fputc(0, fp);
    fputc(0, fp);
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
    tmpl_simple_vector v = tmpl_simple_vector(0.0, 0.0, -1.0);
    tmpl_simple_vector p;
    unsigned int x, y, size;
    double factor, start, end, dt;

    /*  Set the values for the size of the detector. I've chosen the square   *
     *  [-10, 10]^2.                                                          */
    start = -10.0;
    end = 10.0;

    /*  Set the number of pixels in the detector.                             */
    size = 4U*1024U;
    
    /*  The step-size we're incrementing in time.                             */
    dt = 0.01;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    factor = (end - start) / (double)size;

    /*  Open the file "black_hole_two.ppm" and give it write permissions.     */
    FILE *fp = fopen("black_hole_two.ppm", "w");

    /*  If fopen fails it returns NULL. Check that this didn't happen.        */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Print the preamble to the PPM file. A PPM file wants Pn followed by   *
     *  three numbers. P6 means we're encoding an RGB image in binary format. *
     *  The first two numbers are the number of pixels in the x and y axes.   *
     *  The last number is the size of our color spectrum, which is 255.      */
    fprintf(fp, "P6 %u %u 255\n", size, size);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential.                 */
    for (y = 0U; y<size; ++y)
    {
        for (x = 0U; x<size; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            p = tmpl_simple_vector(start + factor*x, start + factor*y, 10.0);

            /*  Raytrace where the photon that hit p came from.               */
            p = Path(p, v, dt);

            /*  If the photon never made it to the detector, assume it was    *
             *  captured by the black hole and color the pixel black.         */
            if (p.norm() < 9.9)
                color_black(fp);

            /*  Otherwise, use this bitwise AND trick to create a             *
             *  checkerboard pattern of red and white.                        */
            else if ((int)(ceil(p.x) + ceil(p.y)) & 1)
                color_white(fp, p);

            else
                color_red(fp, p);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

