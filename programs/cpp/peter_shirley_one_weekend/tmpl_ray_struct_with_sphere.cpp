/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *      This is part of a set of files I made while studying from Peter       *
 *      Shirley's "Ray Tracing in One Weekend", Copyright 2018-2020, Peter    *
 *      Shirley, All rights reserved. The code is my own, but follows the     *
 *      ideas laid out in the text.                                           *
 *                                                                            *
 *      Presents a simple struct for working with rays in raytracing.         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 10, 2021                                                  *
 ******************************************************************************/

/*  The C++ equivalent of math.h. sqrt is found here.                         */
#include <cmath>

/*  And the equivalent of stdio.h.                                            */
#include <cstdio>

/*  A color is an ordered triple (r, g, b) of the amount of red, green, and   *
 *  blue present in the color.                                                */
struct tmpl_simple_color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    /*  Empty constructor.                                                    */
    tmpl_simple_color(void)
    {
        return;
    }

    /*  Constructor from three values, RGB.                                   */
    tmpl_simple_color(unsigned char r, unsigned char g, unsigned char b)
    {
        red   = r;
        green = g;
        blue  = b;
    }

    /*  Operator for adding colors.                                           */
    tmpl_simple_color operator + (tmpl_simple_color r)
    {
        /*  Two colors are added by averaging their components.               */
        unsigned char out_red, out_green, out_blue;

        /*  Cast to doubles and compute the sum.                              */
        out_red   = (unsigned char)(0.5*((double)r.red   + (double)red));
        out_green = (unsigned char)(0.5*((double)r.green + (double)green));
        out_blue  = (unsigned char)(0.5*((double)r.blue  + (double)blue));

        /*  Use the constructor to return the sum from the RGB values.        */
        return tmpl_simple_color(out_red, out_green, out_blue);
    }

    /*  Scaling a color by a real number.                                     */
    tmpl_simple_color operator * (double a)
    {
        unsigned char r, g, b;
        r = (unsigned char)(a * (double)red);
        g = (unsigned char)(a * (double)green);
        b = (unsigned char)(a * (double)blue);

        return tmpl_simple_color(r, g, b);
    }

    /*  Function for writing the color to a PPM file.                         */
    void write(FILE *fp)
    {
        std::fputc(red, fp);
        std::fputc(green, fp);
        std::fputc(blue, fp);
    }
};
/*  End of tmpl_simple_color.                                                 */

/*  Struct used to represents vectors in R^3.                                 */
struct tmpl_simple_vector {

    /*  The data in a vector is it's Euclidean components.                    */
    double x, y, z;

    /*  Empty constructor. Do not set any of the variables, simply return.    */
    tmpl_simple_vector(void)
    {
        return;
    }

    /*  Constructor from three doubles. Set the components to the inputs.     */
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  Define the basic operators for the vector. First is vector addition.  */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }

    /*  Vector subtraction.                                                   */
    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
    }

    /*  Vector negation.                                                      */
    tmpl_simple_vector operator - (void)
    {
        return tmpl_simple_vector(-x, -y, -z);
    }

    /*  Scalar multiplication.                                                */
    tmpl_simple_vector operator * (double a)
    {
        return tmpl_simple_vector(a*x, a*y, a*z);
    }

    /*  Scalar division.                                                      */
    tmpl_simple_vector operator / (double a)
    {
        return tmpl_simple_vector(x/a, y/a, z/a);
    }

    /*  Euclidean norm (the length of the vector).                            */
    double norm(void)
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    /*  Square of the Euclidean norm.                                         */
    double normsq(void)
    {
        return x*x + y*y + z*z;
    }

    /*  Euclidean dot product.                                                */
    double dot(tmpl_simple_vector r)
    {
        return r.x*x + r.y*y + r.z*z;
    }

    /*  Euclidean cross product in three dimensions.                          */
    tmpl_simple_vector cross(tmpl_simple_vector r)
    {
        return tmpl_simple_vector(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
    }

    /*  Unit vector for the given vector.                                     */
    tmpl_simple_vector unit(void)
    {
        return *this / (*this).norm();
    }

    /*  Simple function for printing out the values of the vector.            */
    void print(void)
    {
        std::printf("<%f, %f, %f>", x, y, z);
    }
};
/*  End of tmpl_simple_vector struct.                                         */

/*  Struct for rays, which are Affine subspaces of R^3, L = {A+tB, t real}.   */
struct tmpl_simple_ray {

    /*  A ray is the set of all points of the form p + tv, where p and v are  *
     *  vectors and t is a real number.                                       */
    tmpl_simple_vector p, v;

    /*  Empty construct, simply return.                                       */
    tmpl_simple_ray(void)
    {
        return;
    }

    /*  Constructor from a starting point and a direction.                    */
    tmpl_simple_ray(tmpl_simple_vector A, tmpl_simple_vector B)
    {
        p = A;
        v = B;
    }

    /*  Function for compute the point p + tv on the ray.                     */
    tmpl_simple_vector point_on_ray(double t)
    {
        return p + v*t;
    }

    /*  Function for creating a ray from two points on the ray.               */
    tmpl_simple_ray
    ray_from_two_points(tmpl_simple_vector A, tmpl_simple_vector B)
    {
        /*  A tangent vector for the ray is given by the relative positive    *
         *  vector going from A to B. Compute this ray.                       */
        return tmpl_simple_ray(A, B-A);
    }
};
/*  End of tmpl_simple_ray definition.                                        */

/*  Struct for dealing with spheres.                                          */
struct tmpl_simple_sphere {

    /*  A sphere is defined by its radius and its center.                     */
    double radius;
    tmpl_simple_vector center;

    /*  Empty constructor. Return NULL.                                       */
    tmpl_simple_sphere(void)
    {
        return;
    }

    /*  Main constructor.                                                     */
    tmpl_simple_sphere(double r, tmpl_simple_vector c)
    {
        radius = r;
        center = c;
    }
};
/*  End of definition of tmpl_simple_sphere.                                  */

/*  Since a sphere satisfies (x-x0)^2 + (y-y0)^2 + (z-z0)^2 = r^2, given a    *
 *  ray L(t) = p + tv, solving for which values of t satisfy the sphere's     *
 *  equation amounts to solving a quadratic equation.                         */
bool sphere_is_hit(tmpl_simple_ray r, tmpl_simple_sphere s)
{
    tmpl_simple_vector oc = r.p - s.center;
    double a = (r.v).normsq();
    double b = 2.0 * (r.v).dot(oc);
    double c = oc.normsq() - s.radius*s.radius;
    double D = b*b - 4.0*a*c;

    if (D > 0.0)
    {
        if (a*(-b + sqrt(D)) > 0.0)
            return true;
        else
            return false;
    }
    else
        return false;
}
/*  End of sphere_is_hit.                                                     */

/*  Function for coloring the background with a gradient.                     */
static tmpl_simple_color sky_gradient(tmpl_simple_ray r)
{
    tmpl_simple_vector v = (r.v).unit();
    double t = 0.5 * (v.y + 1.0);

    /*  Create a gradient from sky blue to white.                             */
    tmpl_simple_color sky_blue = tmpl_simple_color(128U, 180U, 255U);
    tmpl_simple_color white    = tmpl_simple_color(255U, 255U, 255U);
    return (white*(1.0 - t) + sky_blue*t)*2.0;
}
/*  End of sky_gradient.                                                      */

/*  Function for drawing a sky with a red ball in it.                         */
int main(void)
{
    unsigned int m, n;
    FILE *fp;
    double width_factor, height_factor, u, v;
    tmpl_simple_ray r;
    tmpl_simple_color color;
    tmpl_simple_vector direction;
    const double aspect_ratio = 16.0 / 9.0;
    const unsigned int image_width  = 1920U;
    const unsigned int image_height
        = (unsigned int)((double)image_width / aspect_ratio);

    double viewport_height = 2.0;
    double viewport_width  = viewport_height * aspect_ratio;
    double focal_length = 1.0;
    tmpl_simple_color red = tmpl_simple_color(255U, 0U, 0U);

    tmpl_simple_sphere s = tmpl_simple_sphere(0.5, tmpl_simple_vector(0, 0, -1));

    tmpl_simple_vector origin = tmpl_simple_vector(0.0, 0.0, 0.0);
    tmpl_simple_vector horizontal, vertical, lower_left_corner;
    horizontal = tmpl_simple_vector(viewport_width, 0.0, 0.0);
    vertical   = tmpl_simple_vector(0.0, viewport_height, 0.0);

    lower_left_corner = origin - (horizontal*0.5) - (vertical*0.5) -
                        tmpl_simple_vector(0.0, 0.0, focal_length);

    fp = std::fopen("tmpl_test_ray.ppm", "w");

    if (!fp)
    {
        std::puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    std::fprintf(fp, "P6\n%u %u\n255\n", image_width, image_height);
    width_factor  = 1.0 / (double)(image_width - 1U);
    height_factor = 1.0 / (double)(image_height - 1U);

    for (m = image_height; m > 0; --m)
    {
        for (n = 0U; n < image_width; ++n)
        {
            u = (double)n * width_factor;
            v = (double)m * height_factor;
            direction = lower_left_corner + horizontal*u + vertical*v - origin;
            r = tmpl_simple_ray(origin, direction);

            if (sphere_is_hit(r, s))
                color = red;
            else
                color = sky_gradient(r);

            color.write(fp);
        }
    }

    return 0;
}

