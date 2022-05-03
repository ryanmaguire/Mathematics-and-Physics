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

/*  6-dimensional vector used in Runge-Kutta computations.                    */
struct tmpl_six_vector {
    tmpl_simple_vector r, v;

    /*  Empty constructor. Simply return.                                     */
    tmpl_six_vector(void)
    {
        return;
    }

    /*  Constructor from two 3-vectors.                                       */
    tmpl_six_vector(tmpl_simple_vector a, tmpl_simple_vector b)
    {
        r = a;
        v = b;
    }

    tmpl_six_vector operator + (tmpl_six_vector u)
    {
        return tmpl_six_vector(r + u.r, v + u.v);
    }

    tmpl_six_vector operator * (double a)
    {
        return tmpl_six_vector(r*a, v*a);
    }
};
/*  End of definition of tmpl_six_vector.                                     */

/*  The acceleration under the force of gravity is given by Newton's          *
 *  universal law of gravitation. This is the inverse square law.             */
static tmpl_simple_vector acc(tmpl_simple_vector p)
{
    /*  Given a vector p, Newton's universal law of gravitation says the      *
     *  acceleration is proportional to p/||p||^3 = p_hat/||p||^2, where p_hat*
     *  is the unit vector for p. We can compute p/||p||^3 in terms of the    *
     *  norm of p and the square of the norm of p. We have:                   */
    double factor = 1.0 / (p.normsq() * p.norm());

    /*  The acceleration is the minus of p times this factor. The reason it   *
     *  is minus p is because gravity pulls inward, so the acceleration is    *
     *  towards the blacks hole.                                              */
    return tmpl_simple_vector(-p.x*factor, -p.y*factor, -p.z*factor);
}

/*  Function for computing the path of a light ray under the influence of     *
 *  the gravity of a black hole using the Runge-Kutta method.                 */
static tmpl_simple_vector
Path(tmpl_simple_vector p, tmpl_simple_vector v, double dt)
{
    /*  This function makes a very naive assumption. Newton's Second Law      *
     *  states the F = ma, where a is the acceleration. So, for gravity, we   *
     *  obtain the vector-valued differential equation:                       *
     *      -GMm p / ||p||^3 = m d^2/dt^2 p                                   *
     *  Where G is the universal gravitational constant, and M is the mass of *
     *  the black hole (m being the mass of the object under consideration).  *
     *  We can take G*M to be 1 for simplicity, since we never specified the  *
     *  units we're in. Now, if m is any non-zero value we can cancel to get: *
     *      p / ||p||^3 = d^2/dt^2 p                                          *
     *  Solving this vector-valued differential equation results in the       *
     *  trajectory of the object. The only problem is, it is generally        *
     *  believed that photons, which are particles of light, have zero mass.  *
     *  So let's pretend they have a mass that is so stupidly small, it would *
     *  be impossible to measure, but not zero. If this were true, we could   *
     *  apply Newtonian mechanics to get a rough idea as to what a black hole *
     *  would look like.                                                      */

    /* The black hole is of radius 1 at the origin, and our detector is the   *
     * plane z = -10. Our source of light (defined in the main routine) is    *
     * some plane z = positive-number. In other words, the light is coming    *
     * down and heading towards our detector. We'll increment time using a    *
     * small value dt, and we'll keep incrementing until the light either     *
     * hits the detector, or is absorbed by the black hole.                   */
    unsigned int N = 0U;

    /*  Factor for Runge-Kutta method.                                        */
    tmpl_six_vector k1, k2, k3, k4, u;
    double h0, h1;
    h0 = 0.5 * dt;
    h1 = dt * 0.1666666666666667;
    k1 = tmpl_six_vector(v, acc(p));
    k2 = tmpl_six_vector(v + k1.v * h0, acc(p + k1.r * h0));
    k3 = tmpl_six_vector(v + k2.v * h0, acc(p + k2.r * h0));
    k4 = tmpl_six_vector(v + k2.v * dt, acc(p + k2.r * dt));
    u  = tmpl_six_vector(p, v);

    while ((p.z > -10.0) && (N < 1E5))
    {
        /* If the light was absorbed by the black hole, abort the computation.*/
        if (p.norm() <= 1.0)
            return p;

        /*  We numerically solve d^2/dt^2 p = F(p) in two steps. First, we    *
         *  compute the velocity dp/dt, meaning we need to solve dv/dt = F(p).*
         *  We solve numerically with the Runge-Kutta method. We use this v to*
         *  compute p via dp/dt = v, solving numerically with Runge-Kutta.    *
         *  method. So long as dt is small, the error should be small as well.*/
        u = u + (k1 + k2*2.0 + k3*2.0 + k4) * h1;
        p = u.r;
        v = u.v;

        /*  Update the Runge-Kutta factors.                                   */
        k1 = tmpl_six_vector(v, acc(p));
        k2 = tmpl_six_vector(v + k1.v * h0, acc(p + k1.r * h0));
        k3 = tmpl_six_vector(v + k2.v * h0, acc(p + k2.r * h0));
        k4 = tmpl_six_vector(v + k2.v * dt, acc(p + k2.r * dt));

        /*  It is possible that a photon was captured into orbit, but not     *
         *  absorbed into the black hole. To avoid an infinite loop, abort    *
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
     *  1/||p||^2 is 1/100. RGB color takes values between 0 and 255, so we   *
     *  need to normalize 1/||p||^2 so that the max value is 255.             */
    double x = 25500.0/p.normsq();

    /*  RGB is Red-Green-Blue. Red is (255, 0, 0).                            */
    std::fputc(int(x), fp);
    std::fputc(0, fp);
    std::fputc(0, fp);
}

/*  Same idea of coloring, but with a gray-to-white gradient.                 */
static void color_white(FILE *fp, tmpl_simple_vector p)
{
    double x = 25500.0/p.normsq();
    std::fputc(int(x), fp);
    std::fputc(int(x), fp);
    std::fputc(int(x), fp);
}

/*  Black represents the black hole.                                          */
static void color_black(FILE *fp)
{
    std::fputc(0, fp);
    std::fputc(0, fp);
    std::fputc(0, fp);
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
    
    /*  The step-size for our increment in time.                              */
    dt = 0.01;

    /*  Set the number of pixels in the detector.                             */
    size = 1024U;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    factor = (end - start) / (double)(size - 1U);

    /*  Open the file "black_hole_runge.ppm" and give it write permissions.   */
    FILE *fp = std::fopen("black_hole_runge.ppm", "w");

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
                color_black(fp);

            /*  Otherwise, use this bitwise AND trick to create a             *
             *  checkerboard pattern of red and white.                        */
            else if ((int)(std::ceil(p.x) + std::ceil(p.y)) & 1)
                color_white(fp, p);

            else
                color_red(fp, p);

        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    std::fclose(fp);
    return 0;
}
/*  End of main.                                                              */

