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
 *  This is my first poor attempt at raytracing a torus using the implicit    *
 *  equation of a torus. It is slow, not optimized, and does not use          *
 *  parallel processing.                                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2022/03/02                                                    *
 ******************************************************************************/

/*  Needed for the FILE data type and fprintf function.                       */
#include <stdio.h>

/*  Square root function found here.                                          */
#include <math.h>

/*  A simple structure for dealing with vectors. Used for rays of light.      */
struct tmpl_simple_vector {

    /*  A vector will be defined by it's Euclidean components, x, y, z.       */
    double x, y, z;

    /*  Empty constructor for the tmpl_simple_vector.                         */
    tmpl_simple_vector(void)
    {
        return;
    }

    /*  Main constructor. Set x, y, and z to a, b, and c, respectively.       */
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  Vector addition. This is done component-wise.                         */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }

    /*  Vector subtraction. Again, done component-wise.                       */
    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
    }

    /*  Scalar multiplication.                                                */
    tmpl_simple_vector operator * (double r)
    {
        return tmpl_simple_vector(x*r, y*r, z*r);
    }

    /*  Euclidean dot product of two vectors.                                 */
    double operator % (tmpl_simple_vector r)
    {
        return x*r.x + y*r.y + z*r.z;
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double norm(void)
    {
        return sqrt(x*x + y*y + z*z);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double normsq(void)
    {
        return x*x + y*y + z*z;
    }

    tmpl_simple_vector unit_vector(void)
    {
        double rcpr = 1.0 / sqrt(x*x + y*y + z*z);
        return tmpl_simple_vector(x*rcpr, y*rcpr, z*rcpr);
    }
};
/*  End of definition of tmpl_simple_vector.                                  */

/*  Struct for working with colors in RGB format.                             */
struct tmpl_simple_color {
    unsigned char red, green, blue;

    tmpl_simple_color(void)
    {
        return;
    }

    tmpl_simple_color(unsigned char a, unsigned char b, unsigned char c)
    {
        red = a;
        green = b;
        blue = c;
    }

    tmpl_simple_color operator * (double a)
    {
        unsigned char r = static_cast<unsigned char>(a*red);
        unsigned char g = static_cast<unsigned char>(a*green);
        unsigned char b = static_cast<unsigned char>(a*blue);
        return tmpl_simple_color(r, g, b);
    }

    /*  Function for writing a color to a PPM file.                           */
    void write(FILE *fp)
    {
        fputc(red, fp);
        fputc(green, fp);
        fputc(blue, fp);
    }
};

static tmpl_simple_color sky_color(double zenith)
{
    tmpl_simple_color out;
    double factor;
    if (zenith < 0.1745)
        return tmpl_simple_color(0xFFU, 0xFFU, 0x00U);

    factor = cos(zenith);
    out.blue = 255U;
    out.red = static_cast<unsigned char>(factor * 135.0);
    out.green = static_cast<unsigned char>(factor * 206.0);
    return out;
}

static const double Inner_Radius = 1.0;
static const double Outer_Radius = 2.0;
static const unsigned int max_iters = 1000U;
static const double threshold = 0.01;

static double torus_implicit(tmpl_simple_vector p)
{
    double a = sqrt(p.x*p.x + p.y*p.y) - Outer_Radius;
    return a*a + p.z*p.z - Inner_Radius*Inner_Radius;
}

static tmpl_simple_vector torus_gradient(tmpl_simple_vector p)
{
    double rho = sqrt(p.x*p.x + p.y*p.y);
    double factor = 2.0*(rho - Outer_Radius) / rho;
    return tmpl_simple_vector(factor * p.x, factor * p.y, 2.0 * p.z);
}

static tmpl_simple_color
sampler(tmpl_simple_vector p, tmpl_simple_vector v, double dt)
{
    tmpl_simple_color out;
    tmpl_simple_vector grad_p;
    unsigned int iters = 0U;

    while ((iters < max_iters) && (p.z > -Inner_Radius))
    {
        if (fabs(torus_implicit(p)) <= threshold)
        {
            grad_p = torus_gradient(p).unit_vector();
            v = v - (grad_p * 2.0*(v % grad_p));
            return sampler(p, v, dt) * 0.8;
        }
        else
            p = p + v*dt;

        ++iters;
    }

    if (v.z <= 0.0)
    {
        double t = -(p.z - Inner_Radius) / v.z;
        tmpl_simple_vector intesect = p + v*t;

        if (int(ceil(intesect.x) + ceil(intesect.y)) & 1)
            return tmpl_simple_color(0xFFU, 0xFFU, 0xFFU);
        else
            return tmpl_simple_color(0xFFU, 0x00U, 0x00U);
    }
    else
    {
        double rho = sqrt(v.x*v.x + v.y*v.y);
        double zenith = M_PI_2 - atan(v.z / rho);
        out = sky_color(zenith);
    }
    return out;
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
    const double val = 0.7071067811865476;
    tmpl_simple_vector v = tmpl_simple_vector(0.0, -val, -val);
    tmpl_simple_vector u0 = tmpl_simple_vector(1.0,  0.0,  0.0);
    tmpl_simple_vector u1 = tmpl_simple_vector(0.0,  val, -val);
    tmpl_simple_vector eye = v * 11.0;
    unsigned int x, y;

    /*  Set the values for the size of the detector.                          */
    const double start = -2.0;
    const double end =  2.0;
    const double dt = 0.01;

    /*  Set the number of pixels in the detector.                             */
    const unsigned int size = 1024U;

    /*  And compute the factor that allows us to convert between a pixel      *
     *  and the corresponding point on the detector.                          */
    const double factor = (end - start) / static_cast<double>(size);
    const double prog_factor = 100.0 / static_cast<double>(size);

    /*  Open the file "black.ppm" and give it write permissions.              */
    FILE *fp = fopen("black_hole.ppm", "w");

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
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  We can NOT do parallel processing with the creation of our PPM file   *
     *  since the order the values are computed is essential.                 */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  We're incrementing p across our detector.                     */
            tmpl_simple_vector p = u0*(start + x*factor) +
                                   u1*(start + y*factor) +
                                   v*val;
            tmpl_simple_vector dir = (p - eye).unit_vector();
            tmpl_simple_color c = sampler(p, dir, dt);
            c.write(fp);
        }
        if ((y % 20) == 0)
            fprintf(stderr, "Progress: %.4f%%\r", prog_factor*y);
    }

    fclose(fp);
    return 0;
}
/*  End of main.                                                              */

