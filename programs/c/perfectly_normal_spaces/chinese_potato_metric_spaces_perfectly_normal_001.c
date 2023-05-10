/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Demonstrates that metric spaces are perfectly normal using characters *
 *      from simplified Chinese. The characters spell potato, a running joke  *
 *      between a few of my students.                                         *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2022/08/30                                                        *
 ******************************************************************************/

/*  Microsoft's MSVC "deprecated" many of the standard library functions      *
 *  found in stdio.h. To avoid warnings, declare this macro.                  */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

/*  Set to 1 to ensure all colors have magnitude 255. Set to zero to allow    *
 *  variable color magnitudes (max of sqrt(2)*255, min of 255).               */
#ifndef NORMALIZE_COLOR
#define NORMALIZE_COLOR 1
#endif

/*  Let y = dist(x, A) / (dist(x, A) + dist(x, B)). Set value to zero for     *
 *  func to return y. Set to one to return y^2. Set to two to return sqrt(y). */
#ifndef DIST_FUNC_TYPE
#define DIST_FUNC_TYPE 0
#endif

/*  The characters "tu" and "dou" stick out better if darker. Set this to     *
 *  one to use darker coloring and zero to use default.                       */
#ifndef USE_DARKER_COLORS
#define USE_DARKER_COLORS 1
#endif

/*  Needed for sqrt and fabs.                                                 */
#include <math.h>

/*  fopen, FILE, fprintf, and fputc are all found here.                       */
#include <stdio.h>

/*  90 degrees, but in radians, to double precision.                          */
static const double pi_by_2 = 1.5707963267948966;

/*  Struct for working with colors in RGB format for the PPM file.            */
struct color {
    unsigned char red, green, blue;
};

/*  Struct for ordered pairs representing points in the plane.                */
struct pair {
    double x, y;
};

/*  A quadrilateral formed by four points. The line segments representing the *
 *  polygon are a -> b, b -> c, c -> d, and d -> a.                           */
struct quadrilateral {
    struct pair a, b, c, d;
};

/*  Simple typedef for Booleans. false = 0, true = 1.                         */
typedef enum {false = 0, true = 1} boolean;

/*  The character "tu" is represented with 3 rectangles.                      */
#define N_TU_RECTANGLES 3

/*  The character "dou" is represented with 8 rectangles.                     */
#define N_DOU_RECTANGLES 8

/*  The three rectangles that make up the character "tu".                     */
static struct quadrilateral tu[N_TU_RECTANGLES] = {
    {{-0.500, 0.000}, {0.5000, 0.000}, {0.500, -0.05}, {-0.50, -0.05}},
    {{-0.025, 0.000}, {-0.025, 0.900}, {0.025, 0.900}, {0.025, 0.000}},
    {{-0.500, 0.475}, {0.5000, 0.475}, {0.500, 0.525}, {-0.50, 0.525}}
};

/*  Similarly, the eight rectangles for the character "dou".                  */
static struct quadrilateral dou[N_DOU_RECTANGLES] = {
    {{0.650, 0.000}, {1.650, 0.000}, {1.650, -0.05}, {0.650, -0.05}},
    {{0.650, 0.850}, {1.650, 0.850}, {1.650, 0.800}, {0.650, 0.800}},
    {{0.775, 0.350}, {0.825, 0.350}, {0.825, 0.700}, {0.775, 0.700}},
    {{1.525, 0.350}, {1.475, 0.350}, {1.475, 0.700}, {1.525, 0.700}},
    {{0.775, 0.325}, {1.525, 0.325}, {1.525, 0.375}, {0.775, 0.375}},
    {{0.775, 0.725}, {1.525, 0.725}, {1.525, 0.675}, {0.775, 0.675}},
    {{0.950, 0.050}, {1.000, 0.070}, {0.920, 0.270}, {0.870, 0.250}},
    {{1.250, 0.000}, {1.300, -0.02}, {1.420, 0.280}, {1.370, 0.300}}
};

/*  Function for creating a pair from two real numbers.                       */
static struct pair new_pair(double x, double y)
{
    /*  Set the x and y components to the corresponding inputs and return.    */
    struct pair p;
    p.x = x;
    p.y = y;
    return p;
}
/*  End of new_pair.                                                          */

/*  Compute the sign of a number. +1 for positive, -1 for negative, 0 else.   */
static double sign(double x)
{
    /*  If the input is positive, return 1. If not, check if the input is     *
     *  negative, returning -1 if so. The last case is either zero for the    *
     *  input or NaN (not-a-number). Return the input in either case.         */
    return (x > 0.0 ? 1.0 : (x < 0.0 ? -1.0 : x));
}
/*  End of sign.                                                              */

/*  Computes the Euclidean dot product of two points in the plane.            */
static double dot_prod(const struct pair *a, const struct pair *b)
{
    /*  Given (x0, y0), and (x1, y1), the dot product is x0*x1 + y0*y1.       */
    return a->x*b->x + a->y*b->y;
}
/*  End of dot_prod.                                                          */

/*  Computes the vector difference of two points in the plane.                */
static struct pair pair_diff(const struct pair *a, const struct pair *b)
{
    /*  Vector subtraction is done component-wise. Compute this.              */
    struct pair c;
    c.x = a->x - b->x;
    c.y = a->y - b->y;
    return c;
}
/*  End pair_diff.                                                            */

/*  Function for performing scalar multiplication of a vector with a number.  */
static struct pair scale_pair(double r, const struct pair *a)
{
    /*  Scalar multiplication is also done component-wise.                    */
    struct pair b;
    b.x = r*a->x;
    b.y = r*a->y;
    return b;
}
/*  End of scale_pair.                                                        */

/*  Given a parallelogram, represented by a quadrilateral struct, determine   *
 *  if the point P lies on the interior (or boundary) or not.                 */
static boolean
is_in_parallelogram(const struct quadrilateral *A, const struct pair *P)
{
    const struct pair v0 = pair_diff(&(A->b), &(A->a));
    const struct pair v1 = pair_diff(&(A->d), &(A->a));
    const struct pair u0 = new_pair(-v0.y, v0.x);
    const struct pair u1 = new_pair(-v1.y, v1.x);
    const double sign_v0u1 = sign(dot_prod(&v0, &u1));
    const double sign_v1u0 = sign(dot_prod(&v1, &u0));
    const struct pair w0 = scale_pair(sign_v1u0, &u0);
    const struct pair w1 = scale_pair(sign_v0u1, &u1);
    const struct pair Q = pair_diff(P, &(A->a));
    const double Q_dot_w0 = dot_prod(&Q, &w0);
    const double Q_dot_w1 = dot_prod(&Q, &w1);
    const double v1_dot_w0 = dot_prod(&v1, &w0);
    const double v0_dot_w1 = dot_prod(&v0, &w1);

    if ((0.0 <= Q_dot_w0) && (Q_dot_w0 <= v1_dot_w0) &&
        (0.0 <= Q_dot_w1) && (Q_dot_w1 <= v0_dot_w1))
        return true;
    return false;
}
/*  End of is_in_parallelogram.                                               */

/*  Compute the Euclidean norm of a 2D vector.                                */
static double norm(const struct pair *a)
{
    return sqrt(a->x*a->x + a->y*a->y);
}
/*  End of norm.                                                              */

/*  Given three points in the plane, a, b, and c, compute the angle between   *
 *  the line segments ab and bc.                                              */
static double
angle(const struct pair *a, const struct pair *b, const struct pair *c)
{
    /*  Treat the point b as the origin. Get the vector from b to a and the   *
     *  vector going from b to c.                                             */
    const struct pair v0 = pair_diff(a, b);
    const struct pair v1 = pair_diff(c, b);

    /*  The angle formula is acos(v . w / ||v|| ||w||) where . is the dot     *
     *  product and ||v|| is the Euclidean norm of v. Compute this.           */
    const double norm_v0 = norm(&v0);
    const double norm_v1 = norm(&v1);
    const double v0_dot_v1 = dot_prod(&v0, &v1);
    return acos(v0_dot_v1 / (norm_v0 * norm_v1));
}
/*  End of angle.                                                             */

/*  Compute the Euclidean distance between two points in the plane.           */
static double pair_dist(const struct pair *a, const struct pair *b)
{
    /*  The Euclidean metric is d(v, w) = ||v - w||. Compute this.            */
    struct pair diff = pair_diff(a, b);
    return norm(&diff);
}
/*  End of pair_dist.                                                         */

/*  Given a line segment between points a and b, and a point P, compute the   *
 *  minimum distance between P and ab.                                        */
static double
dist_to_line_segment(const struct pair *a,
                     const struct pair *b,
                     const struct pair *P)
{
    /*  If the angle abP is obtuse, the shortest distance is from P to b.     */
    if (angle(a, b, P) >= pi_by_2)
        return pair_dist(P, b);

    /*  If the angle baP is obtuse, the shortest distance is from P to a.     */
    else if (angle(b, a, P) >= pi_by_2)
        return pair_dist(P, a);

    /*  If both angles are acute, the shortest distance is obtained by        *
     *  computing which point c on the line segment creates a 90 degree angle *
     *  acP (and similarly bcP). This has the following formula.              */
    else
    {
        const struct pair diff = pair_diff(b, a);
        const double seg_length = norm(&diff);
        const double numer = fabs(diff.x*(a->y - P->y) - diff.y*(a->x - P->x));
        return numer / seg_length;
    }
}
/*  End of dist_to_line_segment.                                              */

/*  Compute the distance from a point P to the boundary of a quadrilateral.   */
static double
dist_to_quadrilateral(const struct quadrilateral *A, const struct pair *P)
{
    /*  Compute the minimum distance from the point to the four lines.        */
    const double d0 = dist_to_line_segment(&(A->a), &(A->b), P);
    const double d1 = dist_to_line_segment(&(A->b), &(A->c), P);
    const double d2 = dist_to_line_segment(&(A->c), &(A->d), P);
    const double d3 = dist_to_line_segment(&(A->d), &(A->a), P);
    const double min01 = (d0 > d1 ? d1 : d0);
    const double min23 = (d2 > d3 ? d3 : d2);
    return (min01 > min23 ? min23 : min01);
}
/*  End of dist_to_quadrilateral.                                             */

/*  Function for determining if a point is in the set "tu".                   */
static boolean is_in_tu(const struct pair *P)
{
    /*  Variable for looping over the rectangles that make the set "tu".      */
    int n;

    /*  Loop over the defining parallelograms and check if they contain P.    */
    for (n = 0; n < N_TU_RECTANGLES; ++n)
        if (is_in_parallelogram(&tu[n], P))
            return true;

    return false;
}
/*  End of is_in_tu.                                                          */

/*  Function for determining if a point is in the set "dou".                  */
static boolean is_in_dou(const struct pair *P)
{
    /*  Variable for looping over the rectangles that make the set "dou".     */
    int n;

    /*  Loop over the defining parallelograms and check if they contain P.    */
    for (n = 0; n < N_DOU_RECTANGLES; ++n)
        if (is_in_parallelogram(&dou[n], P))
            return true;

    return false;
}
/*  End of is_in_dou.                                                         */

/*  Distance function from a point P in the plane to the set "tu".            */
static double dist_to_tu(const struct pair *P)
{
    /*  Variable for looping over the rectangles that make the set "tu".      */
    int n;

    /*  Compute the distance by computing the minimum distances between the   *
     *  point P and the defining parallelograms.                              */
    double min = dist_to_quadrilateral(&tu[0], P);
    double tmp;

    /*  Loop over the remaining parallelograms.                               */
    for (n = 1; n < N_TU_RECTANGLES; ++n)
    {
        tmp = dist_to_quadrilateral(&tu[n], P);

        /*  Check if this new value is smaller, resetting min if it is.       */
        if (min > tmp)
            min = tmp;
    }
    return min;
}
/*  End of dist_to_tu.                                                        */

/*  Distance function from a point P in the plane to the set "dou".           */
static double dist_to_dou(const struct pair *P)
{
    /*  Variable for looping over the rectangles that make the set "dou".     */
    int n;

    /*  Compute the distance by computing the minimum distances between the   *
     *  point P and the defining parallelograms.                              */
    double min = dist_to_quadrilateral(&dou[0], P);
    double tmp;

    /*  Loop over the remaining parallelograms.                               */
    for (n = 1; n < N_DOU_RECTANGLES; ++n)
    {
        tmp = dist_to_quadrilateral(&dou[n], P);

        /*  Check if this new value is smaller, resetting min if it is.       */
        if (min > tmp)
            min = tmp;
    }
    return min;
}
/*  End of dist_to_dou.                                                       */

/*  Continuous function separating "tu" and "dou".                            */
static double func(const struct pair *P)
{
    /*  The function is dist(x, A) / (dist(x, A) + dist(x, B)), where A is    *
     *  the closed set "tu" in the plane and B is the closed set "dou".       */
    const double a = dist_to_tu(P);
    const double b = dist_to_dou(P);
    const double y = a / (a + b);

    /*  Depending on the gradient requested, return one of the following.     */
#if DIST_FUNC_TYPE == 0
    return y;
#elif DIST_FUNC_TYPE == 1
    return y*y;
#else
    return sqrt(y);
#endif
/*  End of #if DIST_FUNC_TYPE == 0.                                           */
}
/*  End of func.                                                              */

/*  The following function is only used if color normalization is requested.  */
#if NORMALIZE_COLOR == 1

/*  Function for normalizing a color to magnitude 0xFF = 255.                 */
static struct color normalize_color(struct color c)
{
    /*  Convert the rgb values to doubles.                                    */
    const double x = (double)c.red;
    const double y = (double)c.green;
    const double z = (double)c.blue;

    /*  Compute the normalizing factor, which is 255 divided by the norm of   *
     *  the vector (x, y, z). The value 255 comes from the fact that we are   *
     *  representing colors with 8-bit numbers, and 255 = 2^8 - 1.            */
    const double val = 255.0/sqrt(x*x + y*y + z*z);

    /*  Compute the normalized colors.                                        */
    struct color out;
    out.red = (unsigned char)(x*val);
    out.green = (unsigned char)(y*val);
    out.blue = (unsigned char)(z*val);
    return out;
}
/*  End of normalize_color.                                                   */

#endif
/*  End of #if NORMALIZE_COLOR == 1.                                          */

/*  Function for creating a continuous gradient of color in the RGB spectrum. */
static struct color get_color(double x)
{
    double val = 1023.0*x;
    struct color out;

    /*  Split [0, 1023] into four parts, [0, 255], [256, 511], [512, 767],    *
     *  and [768, 1023]. Create a blue-to-red rainbow gradient from this.     *
     *  The first interval corresponds to blue to blue-green.                 */
    if (val < 256.0)
    {
        out.red = 0x00U;
        out.green = (unsigned char)(val);
        out.blue = 0xFFU;
    }

    /*  Next we do blue-green to green.                                       */
    else if (val < 512.0)
    {
        /*  Subtract 256 from val so that val lies in [0, 255], which are the *
         *  allowed values for an 8-bit unsigned char.                        */
        val -= 256.0;
        out.red = 0x00U;
        out.green = 0xFFU;
        out.blue = (unsigned char)(256.0 - val);
    }

    /*  Next is green to yellow.                                              */
    else if (val < 768.0)
    {
        /*  Subtract by 512 to get val in [0, 255].                           */
        val -= 512.0;
        out.red = (unsigned char)(val);
        out.green = 0xFFU;
        out.blue = 0x00U;
    }

    /*  Finally, yellow to red.                                               */
    else
    {
        /*  Subtract by 768 to get val in the range [0, 255].                 */
        val -= 768.0;
        out.red = 0xFFU;
        out.green = (unsigned char)(256.0 - val);
        out.blue = 0x00U;
    }

#if NORMALIZE_COLOR == 1
    return normalize_color(out);
#else
    return out;
#endif
}
/*  End of get_color.                                                         */

/*  For reasons completely beyond me, fputc doesn't seem to work correctly on *
 *  Windows 10. The problem seems to arise when too many colors are present   *
 *  in the PPM file. The rendered PPM file is completely corrupted and looks  *
 *  horrible. If the user is running Windows, use fprintf instead of fputc,   *
 *  and use the text-based PPM format instead of the binary based one. The    *
 *  text-based format ends up being around 4x larger than the binary format,  *
 *  but renders properly.                                                     */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fprintf(fp, "%u %u %u\n", c.red, c.green, c.blue);
}
/*  End of write_color.                                                       */

#else
/*  Everyone else (GNU, Linux, macOS, FreeBSD, etc.).                         */

/*  Function for writing a color to a PPM file.                               */
static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}
/*  End of write_color.                                                       */

#endif
/*  End of #if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER).       */

/*  Colors for the two sets "tu" and "dou".                                   */
#if USE_DARKER_COLORS == 0
static struct color dark_red = {0xFFU, 0x00U, 0x00U};
static struct color dark_blue = {0x00U, 0x00U, 0xFFU};
#else
static struct color dark_red = {0xBFU, 0x00U, 0x00U};
static struct color dark_blue = {0x00U, 0x00U, 0xBFU};
#endif
/*  End of #if USE_DARKER_COLORS == 0.                                        */

/*  Function for creating the PPM file.                                       */
int main(void)
{
    /*  Width and height of the image, in pixels.                             */
    const unsigned int width = 2048U;
    const unsigned int height = 2048U;

    /*  The boundaries of the image in the xy plane (the numerical values).   */
    const double x_min = -1.0;
    const double x_max = 2.15;
    const double y_min = -1.075;
    const double y_max = 2.075;

    /*  Scale factors to convert from pixels to points in the plane.          */
    const double y_scale = (y_max - y_min)/((double)height - 1.0);
    const double x_scale = (x_max - x_min)/((double)width - 1.0);

    /*  Variables for looping over points in the plane.                       */
    unsigned int x, y;
    struct pair P;

    /*  Open the file and give it write permissions.                          */
    FILE *fp = fopen("potato.ppm", "w");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
    {
        puts("fopen failed and return NULL. Aborting.");
        return -1;
    }

    /*  Write the preamble to the PPM file. For Windows users we'll use text  *
     *  based PPM, and for everyone else we'll use binary format.             */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P3\n%u %u\n255\n", width, height);
#else
    fprintf(fp, "P6\n%u %u\n255\n", width, height);
#endif

    /*  Loop over the y coordinates.                                          */
    for (y = 0U; y < height; ++y)
    {
        /*  Compute the current y part of the point P.                        */
        P.y = y_max - (double)y * y_scale;

        /*  Loop over the x coordinates.                                      */
        for (x = 0U; x < width; ++x)
        {
            /*  Compute the corresponding x coordinate.                       */
            P.x = x_min + (double)x * x_scale;

            /*  If the point is in tu, color it dark blue.                    */
            if (is_in_tu(&P))
                write_color(fp, dark_blue);

            /*  If it's in the set dou, color it dark red.                    */
            else if (is_in_dou(&P))
                write_color(fp, dark_red);

            /*  For all other points use an rgb gradient based on func.       */
            else
                write_color(fp, get_color(func(&P)));
        }
    }

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
