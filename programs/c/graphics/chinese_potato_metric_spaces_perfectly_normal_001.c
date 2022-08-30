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
 ******************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static double pi_by_2 = 1.5707963267948966;

struct color {
    unsigned char red, green, blue;
};

struct pair {
    double x, y;
};

struct quadrilateral {
    struct pair a, b, c, d;
};

typedef enum {false, true} boolean;

#define N_TU_RECTANGLES 3
#define N_DOU_RECTANGLES 8

static struct quadrilateral tu[N_TU_RECTANGLES] = {
    {{-0.500, 0.000}, {0.5000, 0.000}, {0.500, -0.05}, {-0.50, -0.05}},
    {{-0.025, 0.000}, {-0.025, 0.900}, {0.025, 0.900}, {0.025, 0.000}},
    {{-0.500, 0.475}, {0.5000, 0.475}, {0.500, 0.525}, {-0.50, 0.525}}
};

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

static struct pair new_pair(double x, double y)
{
    struct pair p;
    p.x = x;
    p.y = y;
    return p;
}

static double sign(double x)
{
    return (x > 0.0 ? 1.0 : (x < 0.0 ? -1.0 : x));
}

static double dot_prod(const struct pair *a, const struct pair *b)
{
    return a->x*b->x + a->y*b->y;
}

static struct pair pair_diff(const struct pair *a, const struct pair *b)
{
    struct pair c;
    c.x = a->x - b->x;
    c.y = a->y - b->y;
    return c;
}

static struct pair scale_pair(double r, const struct pair *a)
{
    struct pair b;
    b.x = r*a->x;
    b.y = r*a->y;
    return b;
}

static boolean
is_in_quadrilateral(const struct quadrilateral *A, const struct pair *P)
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

    if ((0.0 <= Q_dot_w0) &&
        (Q_dot_w0 <= v1_dot_w0) &&
        (0.0 <= Q_dot_w1 ) &&
        (Q_dot_w1 <= v0_dot_w1))
        return true;
    return false;
}

static double norm(const struct pair *a)
{
    return sqrt(a->x*a->x + a->y*a->y);
}

static double
angle(const struct pair *a, const struct pair *b, const struct pair *c)
{
    const struct pair v0 = pair_diff(a, b);
    const struct pair v1 = pair_diff(c, b);
    const double norm_v0 = norm(&v0);
    const double norm_v1 = norm(&v1);
    const double v0_dot_v1 = dot_prod(&v0, &v1);
    return acos(v0_dot_v1 / (norm_v0 * norm_v1));
}

static double pair_dist(const struct pair *a, const struct pair *b)
{
    struct pair diff = pair_diff(a, b);
    return norm(&diff);
}

static double
dist_to_line_segment(const struct pair *a,
                     const struct pair *b,
                     const struct pair *P)
{
    if (angle(a, b, P) >= pi_by_2)
        return pair_dist(P, b);
    else if (angle(b, a, P) >= pi_by_2)
        return pair_dist(P, a);
    else
    {
        const struct pair diff = pair_diff(b, a);
        const double seg_length = norm(&diff);
        const double numer = fabs(diff.x*(a->y - P->y) - diff.y*(a->x - P->x));
        return numer / seg_length;
    }
}

static double
dist_to_quadrilateral(const struct quadrilateral *A, const struct pair *P)
{
    const double d0 = dist_to_line_segment(&(A->a), &(A->b), P);
    const double d1 = dist_to_line_segment(&(A->b), &(A->c), P);
    const double d2 = dist_to_line_segment(&(A->c), &(A->d), P);
    const double d3 = dist_to_line_segment(&(A->d), &(A->a), P);
    const double min01 = (d0 > d1 ? d1 : d0);
    const double min23 = (d2 > d3 ? d3 : d2);
    return (min01 > min23 ? min23 : min01);
}

static boolean is_in_tu(const struct pair *P)
{
    int n;
    for (n = 0; n < N_TU_RECTANGLES; ++n)
        if (is_in_quadrilateral(&tu[n], P))
            return true;

    return false;
}

static boolean is_in_dou(const struct pair *P)
{
    int n;
    for (n = 0; n < N_DOU_RECTANGLES; ++n)
        if (is_in_quadrilateral(&dou[n], P))
            return true;

    return false;
}

static double dist_to_tu(const struct pair *P)
{
    int n;
    double tmp = dist_to_quadrilateral(&tu[0], P);
    double min = tmp;

    for (n = 1; n < N_TU_RECTANGLES; ++n)
    {
        tmp = dist_to_quadrilateral(&tu[n], P);

        if (min > tmp)
            min = tmp;
    }
    return min;
}

static double dist_to_dou(const struct pair *P)
{
    int n;
    double tmp = dist_to_quadrilateral(&dou[0], P);
    double min = tmp;

    for (n = 1; n < N_DOU_RECTANGLES; ++n)
    {
        tmp = dist_to_quadrilateral(&dou[n], P);

        if (min > tmp)
            min = tmp;
    }
    return min;
}

static double func(const struct pair *P)
{
    const double a = dist_to_tu(P);
    const double b = dist_to_dou(P);
    const double y = a / (a + b);
    return y;
}

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

    return out;
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

static struct color dark_red = {0xAFU, 0x00U, 0x00U};
static struct color dark_blue = {0x00U, 0x00U, 0xAFU};

int main(void)
{
    const unsigned int width = 2048U;
    const unsigned int height = 2048U;
    const double x_min = -1.0;
    const double x_max = 2.15;
    const double y_min = -1.075;
    const double y_max = 2.075;
    const double y_scale = (y_max - y_min)/((double)height - 1.0);
    const double x_scale = (x_max - x_min)/((double)width - 1.0);
    unsigned int x, y;
    struct pair P;

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
            P.x = x_min + (double)x * x_scale;

            if (is_in_tu(&P))
                write_color(fp, dark_blue);
            else if (is_in_dou(&P))
                write_color(fp, dark_red);
            else
                write_color(fp, get_color(func(&P)));
        }
    }

    fclose(fp);
    return 0;
}
