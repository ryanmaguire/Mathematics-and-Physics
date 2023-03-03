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
 *  Attempt of a proof of concept of computing the Jones' polynomial from     *
 *  the Gauss code of a knot.                                                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/09/30                                                        *
 ******************************************************************************/

/*  printf found here.                                                        */
#include <stdio.h>

/*  malloc, calloc, realloc, and free are here.                               */
#include <stdlib.h>

/*  Crossing signs are negative and positive. This assumes the knot has been  *
 *  given an orientation.                                                     */
enum crossing_sign {negative_crossing, positive_crossing};

/*  Crossing type for the Gauss code. Is the current strand over or under.    */
enum crossing_type {under_crossing, over_crossing};

/*  The direction is stored as an unsigned char. There are two possibilities: *
 *  forwards and backwards.                                                   */
static unsigned char backward = 0x00U;
static unsigned char forward = 0x01U;

/*  Extended Gauss code. This contains crossing number, sign, and type.       */
struct knot {
    unsigned int number_of_crossings;
    enum crossing_sign *sign;
    enum crossing_type *type;
    unsigned int *crossing_number;
};

/*  Laurent polynomials, i.e. polynomials with negative exponents allowed.    */
struct laurent_polynomial {
    signed int lowest_degree;
    signed int highest_degree;
    signed int *coeffs;
};

/*  This struct is used for keeping track of which crossing number            *
 *  corresponds to which indices.                                             */
struct CrossingIndices {
    unsigned int under;
    unsigned int over;
};

/*  Basic algorithm for computing the Hamming weight of an unsigned integer   *
 *  that is sizeof(unsigned int) * CHAR_BIT bits long. There are faster       *
 *  methods, but this does not assume 32-bit int and is more portable.        */
static unsigned int hamming_weight(unsigned int val)
{
    unsigned int result = 0U;

    /*  Loop over the bits of the input.                                      */
    while(val != 0U)
    {
        /*  val & 1U returns 0 if the last bit is zero, and 1 if the last     *
         *  bit is one. Summing over these gives us the Hamming weight.       */
        result += val & 1U;

        /*  Move the input 1 bit to the right.                                */
        val = val >> 1U;
    }

    return result;
}
/*  End of hamming_weight.                                                    */

/*  Returns an array ind where ind[n] is a struct containing the indices of   *
 *  the under and over crossings of the nth crossing.                         */
static struct CrossingIndices *get_indices(struct knot *K)
{
    unsigned int n;
    struct CrossingIndices *ind;

    /*  Check for invalid inputs.                                             */
    if (!K)
        return NULL;

    /*  If there are no crossings, return an empty array (a NULL pointer).    */
    if (K->number_of_crossings == 0U)
        return NULL;

    /*  Allocate memory for the array.                                        */
    ind = malloc(sizeof(*ind)*K->number_of_crossings);

    /*  Check if malloc failed.                                               */
    if (!ind)
        return NULL;

    /*  Loop through and save the indices.                                    */
    for (n = 0U; n < 2U * K->number_of_crossings; ++n)
    {
        if (K->type[n] == over_crossing)
            ind[K->crossing_number[n]].over = n;
        else
             ind[K->crossing_number[n]].under = n;
    }

    return ind;
}
/*  End of get_indices.                                                       */

static unsigned int
number_of_circles_in_resolution(struct knot *K,
                                struct CrossingIndices *ind,
                                unsigned int resolution)
{
    unsigned int number_of_circles, n, k, m;
    unsigned char dir, crossing_resolution;
    unsigned char *have_visited;

    /*  The empty knot has zero circles.                                      */
    if (!K)
        return 0U;

    /*  The unknot has 1 circle.                                              */
    if (K->number_of_crossings == 0U)
        return 1U;

    /*  If ind is a NULL pointer, there's nothing that can be done.           */
    if (!ind)
        return 0U;

    /*  Create an array of zeros with calloc.                                 */
    have_visited = calloc(sizeof(*have_visited), 4U*K->number_of_crossings);

    /*  Check if calloc failed.                                               */
    if (!have_visited)
        return 0U;

    /*  Initialize number_of_circles to zero.                                 */
    number_of_circles = 0U;

    for (n = 0U; n < 2U*K->number_of_crossings; ++n)
    {
        k = 4U*K->crossing_number[n];

        /*  Each crossing has four entrances. Bottom left, bottom right, top  *
         *  left, top right. Check which one's we have visited.               */
        for (m = 0U; m < 3; ++m)
        {
            if (!have_visited[k])
                break;
            else
                ++k;
        }

        if (have_visited[k])
            continue;

        if (m < 2U)
            dir = forward;
        else
            dir = backward;

        m = n;
        while (!have_visited[k])
        {
            crossing_resolution = (resolution >> K->crossing_number[m]) & 0x01U;
            have_visited[k] = 0x01U;

            if (K->sign[m] == positive_crossing)
            {
                if (K->type[m] == over_crossing)
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 3U;
                        else
                            k = 4U*K->crossing_number[m] + 1U;
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 1U;
                        else
                            k = 4U*K->crossing_number[m] + 3U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].under;
                }
                else
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 2U;
                        else
                            k = 4U*K->crossing_number[m];
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m];
                        else
                            k = 4U*K->crossing_number[m] + 2U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].over;
                }
            }
            else
            {
                if (K->type[m] == over_crossing)
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 2U;
                        else
                            k = 4U*K->crossing_number[m];
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m];
                        else
                            k = 4U*K->crossing_number[m] + 2U;

                        dir = 0x01U - dir;
                    }

                    m = ind[K->crossing_number[m]].under;
                }
                else
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 3U;
                        else
                            k = 4U*K->crossing_number[m] + 1U;
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 1U;
                        else
                            k = 4U*K->crossing_number[m] + 3U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].over;
                }
            }

            if (dir == forward)
            {
                if (m == 2U*K->number_of_crossings - 1U)
                    m = 0U;
                else
                    ++m;
            }
            else
            {
                if (m == 0U)
                    m = 2U*K->number_of_crossings - 1U;
                else
                    --m;
            }

            have_visited[k] = 0x01U;

            k = 4U*K->crossing_number[m];
            if (K->sign[m] == positive_crossing)
            {
                if (K->type[m] == over_crossing)
                {
                    if (dir == backward)
                        k += 2U;
                }
                else
                {
                    if (dir == forward)
                        k += 1U;
                    else
                        k += 3U;
                }
            }
            else
            {
                if (K->type[m] == over_crossing)
                {
                    if (dir == forward)
                        k += 1U;
                    else
                        k += 3U;
                }
                else
                {
                    if (dir == backward)
                        k += 2U;
                }
            }
        }
        ++number_of_circles;
    }
    free(have_visited);
    return number_of_circles;
}

static void
print_poly(struct laurent_polynomial P)
{
    signed int n, N;

    if (!P.coeffs)
    {
        puts("0");
        return;
    }

    N = P.highest_degree - P.lowest_degree + 1;

    if (P.coeffs[0] == 1)
        printf("q^%d", P.lowest_degree);
    else if (P.coeffs[0] == -1)
        printf("-q^%d", P.lowest_degree);
    else
        printf("%dq^%d", P.coeffs[0], P.lowest_degree);

    for (n = 1; n < N; ++n)
    {
        if (P.coeffs[n] == 0)
            continue;
        else if (P.coeffs[n] == 1)
            printf(" + q^%d", P.lowest_degree + n);
        else if (P.coeffs[n] == -1)
            printf(" - q^%d", P.lowest_degree + n);
        else if (P.coeffs[n] > 1)
            printf(" + %dq^%d", P.coeffs[n], P.lowest_degree + n);
        else
            printf(" - %dq^%d", -P.coeffs[n], P.lowest_degree + n);
    }

    printf("\n");
}

static void
poly_add(struct laurent_polynomial P,
         struct laurent_polynomial Q,
         struct laurent_polynomial *sum)
{
    unsigned int n, N, Pstart, Pend, Qstart, Qend;
    signed int *tmp, *Pcoeffs, *Qcoeffs;

    if (!sum)
    {
        puts("Error: poly_add\n\tsum is NULL.");
        exit(0);
    }

    if (P.lowest_degree < Q.lowest_degree)
    {
        sum->lowest_degree = P.lowest_degree;
        Pstart = 0U;
        Qstart = (unsigned int)(Q.lowest_degree - P.lowest_degree);
    }
    else
    {
        sum->lowest_degree = Q.lowest_degree;
        Qstart = 0U;
        Pstart = (unsigned int)(P.lowest_degree - Q.lowest_degree);
    }

    if (P.highest_degree < Q.highest_degree)
    {
        sum->highest_degree = Q.highest_degree;
        Pend = (unsigned int)(P.highest_degree - sum->lowest_degree) + 1U;
        Qend = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    }
    else
    {
        sum->highest_degree = P.highest_degree;
        Qend = (unsigned int)(Q.highest_degree - sum->lowest_degree) + 1U;
        Pend = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    }

    if (!P.coeffs)
    {
        puts("Error: poly_add\n\tP coeffs is NULL.");
        exit(0);
    }
    else if (!Q.coeffs)
    {
        puts("Error: poly_add\n\tQ coeffs is NULL.");
        exit(0);
    }

    Pcoeffs = malloc(sizeof(*Pcoeffs) * (Pend - Pstart + 1U));
    Qcoeffs = malloc(sizeof(*Qcoeffs) * (Qend - Qstart + 1U));

    for (n = 0; n <= Pend - Pstart; ++n)
        Pcoeffs[n] = P.coeffs[n];

    for (n = 0; n <= Qend - Qstart; ++n)
        Qcoeffs[n] = Q.coeffs[n];

    N = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    tmp = realloc(sum->coeffs, sizeof(*sum->coeffs) * N);

    if (!tmp)
    {
        puts("Error: poly_add\n\trealloc failed.\n");
        exit(0);
    }
    else
        sum->coeffs = tmp;

    for (n = 0U; n < N; ++n)
        sum->coeffs[n] = 0;

    for (n = Pstart; n < Pend; ++n)
        sum->coeffs[n] += Pcoeffs[n - Pstart];

    for (n = Qstart; n < Qend; ++n)
        sum->coeffs[n] += Qcoeffs[n - Qstart];

    free(Pcoeffs);
    free(Qcoeffs);
}

/*  Function for multiplying two polynomials.                                 */
static void
poly_multiply(struct laurent_polynomial P,
              struct laurent_polynomial Q,
              struct laurent_polynomial *prod)
{
    /*  Declare variables for indexing.                                       */
    unsigned int n, k;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    struct laurent_polynomial first, second;
    signed int *first_coeffs, *second_coeffs;
    unsigned int first_deg, second_deg, sum_deg;
    signed int shift;

    /*  Temporary variable used in case realloc is needed.                    */
    signed int *tmp;

    /*  If prod is NULL, nothing can be done.                                 */
    if (prod == NULL)
    {
        puts("Error: poly_multiply\n\tprod is NULL.");
        exit(0);
    }

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if (!P.coeffs)
    {
        puts("Error: poly_add\n\tP coeffs is NULL.");
        exit(0);
    }
    else if (!Q.coeffs)
    {
        puts("Error: poly_add\n\tQ coeffs is NULL.");
        exit(0);
    }

    shift = P.lowest_degree + Q.lowest_degree;
    P.highest_degree -= P.lowest_degree;
    P.lowest_degree = 0;
    Q.highest_degree -= Q.lowest_degree;
    Q.lowest_degree = 0;

    /*  Order the polynomials by degree.                                      */
    if (P.highest_degree <= Q.highest_degree)
    {
        first = P;
        second = Q;
    }
    else
    {
        first = Q;
        second = P;
    }

    first_deg = (unsigned int)first.highest_degree;
    first_coeffs = malloc(sizeof(*first_coeffs) * (first_deg + 1));

    /*  Check if malloc failed.                                               */
    if (first_coeffs == NULL)
    {
        puts("Error: poly_multiply\n\tmalloc failed for first_coeffs.");
        exit(0);
    }

    /*  If malloc was successful, copy the data from first.                   */
    for (n = 0; n <= first_deg; ++n)
        first_coeffs[n] = first.coeffs[n];

    /*  Do the same thing with the second pointer.                            */
    second_deg = (unsigned int)second.highest_degree;
    second_coeffs = malloc(sizeof(*second_coeffs) * (second_deg + 1));

    /*  Check if malloc failed.                                               */
    if (second_coeffs == NULL)
    {
        /*  Free the memory allocated to first_coeffs, since malloc was       *
         *  successful for that one.                                          */
        free(first_coeffs);
        return;
    }

    /*  Otherwise, copy the data.                                             */
    for (n = 0; n <= second_deg; ++n)
        second_coeffs[n] = second.coeffs[n];

    /*  The degree of a product is the sum of the degrees.                    */
    sum_deg = first_deg + second_deg;
    prod->lowest_degree = 0;
    prod->highest_degree = (signed int)sum_deg;
    tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*(sum_deg + 1U));

    /*  Check if realloc failed.                                              */
    if (tmp == NULL)
    {
        puts("Error: poly_multiply\n\trealloc failed.\n");
        free(first_coeffs);
        free(second_coeffs);
        exit(0);
    }
    else
        prod->coeffs = tmp;

    for (n = 0; n < first_deg; ++n)
    {
        prod->coeffs[n] = first_coeffs[n] * second_coeffs[0];
        for (k = 1; k <= n; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    for (n = first_deg; n < second_deg; ++n)
    {
        prod->coeffs[n] = 0;
        for (k = n - first_deg; k <= n; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    for (n = second_deg; n <= sum_deg; ++n)
    {
        prod->coeffs[n] = 0;
        for (k = n - first_deg; k <= second_deg; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    /*  Free the memory allocated to first and second.                        */
    free(first_coeffs);
    free(second_coeffs);
    prod->lowest_degree += shift;
    prod->highest_degree += shift;
    return;
}
/*  End of tmpl_Create_Zero_PolynomialZ.                                      */

static struct laurent_polynomial
kauffman_bracket(struct knot *K)
{
    unsigned int n, m, weight, n_circles, deg;
    signed int coeffs[3] = {1, 0, 1};
    signed int onecoeffs[1] = {1};
    struct laurent_polynomial P, tmp, out, one;
    struct CrossingIndices *ind = get_indices(K);

    P.lowest_degree = -1;
    P.highest_degree = 1;
    P.coeffs = coeffs;
    one.lowest_degree = 0;
    one.highest_degree = 0;
    one.coeffs = onecoeffs;

    out.lowest_degree = 0;
    out.highest_degree = 0;
    out.coeffs = calloc(sizeof(*out.coeffs), 1);
    tmp.lowest_degree = 0;
    tmp.highest_degree = 0;
    tmp.coeffs = calloc(sizeof(*out.coeffs), 1);

    for (n = 0; n < (1U << K->number_of_crossings); ++n)
    {
        weight = hamming_weight(n);
        n_circles = number_of_circles_in_resolution(K, ind, n);
        if (n_circles == 1U)
            poly_multiply(P, one, &tmp);
        else if (n_circles == 2U)
            poly_multiply(P, P, &tmp);
        else
        {
            poly_multiply(P, P, &tmp);
            poly_multiply(P, tmp, &tmp);
        }

        if (weight & 0x01U)
        {
            deg = (unsigned int)(tmp.highest_degree - tmp.lowest_degree);
            for (m = 0U; m <= deg; ++m)
                tmp.coeffs[m] *= -1;
        }

        tmp.lowest_degree += (signed int)weight;
        tmp.highest_degree += (signed int)weight;

        poly_add(tmp, out, &out);
    }

    free(ind);
    free(tmp.coeffs);
    return out;
}

int main(void)
{
    struct laurent_polynomial out;
    struct knot K;
    enum crossing_sign s[6] = {
        positive_crossing, positive_crossing, positive_crossing,
        positive_crossing, positive_crossing, positive_crossing
    };
    unsigned int c[6] = {0U, 1U, 2U, 0U, 1U, 2U};

    enum crossing_type t[6] = {
        over_crossing, under_crossing, over_crossing,
        under_crossing, over_crossing, under_crossing
    };

    K.number_of_crossings = 3;
    K.sign = s;
    K.type = t;
    K.crossing_number = c;
    out = kauffman_bracket(&K);
    print_poly(out);
    free(out.coeffs);
    return 0;
}
