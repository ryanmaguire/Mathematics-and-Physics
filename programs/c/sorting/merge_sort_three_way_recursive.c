/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify it      *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This is distributed in the hope that it will be useful,                   *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  Global counter for counting the number of recursions needed.              */
unsigned int counter;

/*  Create a "Boolean" type for the Is_Power_Of_Three function below.         */
typedef enum {False, True} Boolean;

/*  Function for determining if an integer is a power of 3. This may get used *
 *  later for plotting.                                                       */
Boolean Is_Power_Of_Three(unsigned int n)
{
    /*  3486784401 is a "magic number." It is 3^20, which is the largest      *
     *  power of 3 less than 2^32-1, which is the largest value a 32-bit      *
     *  UNSIGNED integer can store. Any power of three less than 3486784401   *
     *  must also divide this magic number. We simply check if                *
     *  3486784401 mod n is zero.                                             */
    if ((n != 0) && ((3486784401U % n) == 0))
        return True;
    else
        return False;
}
/*  End of Is_Power_Of_Three.                                                 */

/*  The complexity is n log(n). This function is for comparing.               */
double x_log_x(double x)
{
    /*  0 * log(0) is undefined, but the limit is zero.                       */
    if (x == 0.0)
        return 0.0;
    else
        return x*log(x);
}
/*  End of x_log_x.                                                           */

/*  Function for drawing a scatter plot of an array arr of length arr_length. */
void draw_pic(double *arr, unsigned int arr_length)
{
    /*  Declare variables for sampling the box we're drawing to.              */
    unsigned int x, y, n;
    double a, sum_n_log_n, sum_arr;
    double z_x, z_y;
    double rcpr_factor = 1.0 / (double)arr_length;

    /*  Set the boundaries of the box.                                        */
    double y_min = 0.0;
    double y_max = 0.5*arr_length;
    double pixel_width = 4.0;

    /*  Variables for coloring the current pixel.                             */
    unsigned char black = 0U;
    unsigned char gray  = 128U;
    unsigned char white = 255U;

    /*  And a variable for writing to a file.                                 */
    FILE *fp;

    /*  Compute a least-squares fit of a*n*ln(n) to the data.                 */
    sum_n_log_n = 0.0;
    sum_arr     = 0.0;
    for (n = 0; n <arr_length; ++n)
    {
        sum_n_log_n += x_log_x((double)n);
        sum_arr     += arr[n];
    }

    /*  Setting the derivative of sqrt(sum (data[n] - a*n*log(n))^2) to       *
     *  zero yields sum (data[n] - a * n * log(n)) = 0. Solving for a we      *
     *  get a = sum data / sum n log(n).                                      */
    a = sum_arr / sum_n_log_n;

    /*  Open the PGM file and write the preamble to it.                       */
    fp = fopen("merge_sort_three_way_efficiency.pgm", "w");
    fprintf(fp, "P5\n%d %d\n255\n", arr_length, arr_length);

    /*  Loop through each pixel.                                              */
    for (y=0; y<arr_length; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = y * (y_max - y_min) * rcpr_factor + y_min;
        z_y = y_max - z_y;

        /*  Loop over every x pixel as well.                                  */
        for (x=0; x<arr_length; ++x)
        {
            /*  No need to center x, just set it as a double.                 */
            z_x = (double)x;

            /*  If arr[x] and z_y are close, color the pixel white meaning    *
             *  we have a point in the plane corresponding to the data.       */
            if (fabs(arr[x] - z_y) < pixel_width)
                fputc(white, fp);

            /*  Plot the asymptotic function as well. Color this gray.        */
            else if (fabs(a*x_log_x(z_x) - z_y) < pixel_width)
                fputc(gray, fp);

            /*  Otherwise, color the background black.                        */
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */
    fclose(fp);
}
/*  End of draw_pic.                                                          */

/*  Function for merging three SORTED lists into one. It is assumed the       *
 *  pointer out has already been allocated sufficient memory for this problem.*
 *  LA, LB, and LC are pointers to arrays of lengths a, b, and c,             *
 *  respectively.                                                             */
void merge(double *out, double *LA, double *LB, double *LC,
           unsigned int a, unsigned int b, unsigned int c)
{
    /*  We'll need three extended arrays equal to LA, LB, and LC,             *
     *  respectively, with an additional "infinity" tacked on the end.        */
    double *LAE, *LBE, *LCE;

    /*  Five variables for indexing, and the size of the output array.        */
    unsigned int k, indA, indB, indC, n, size;

    /*  LAE needs the same number of entries as LA, plus 1 for infinity.      *
     *  Similarly for LBE and LCE.                                            */
    LAE = malloc(sizeof(*LAE) * (a+1));
    LBE = malloc(sizeof(*LBE) * (b+1));
    LCE = malloc(sizeof(*LCE) * (c+1));
    size = a+b+c;

    /*  Check that malloc didn't fail.                                        */
    if ((LAE == NULL) || (LBE == NULL) || (LCE == NULL))
    {
        puts("merge: Malloc returned NULL. Aborting.\n");
        return;
    }

    /*  Set the values of the extended arrays LAE, LBE, and LCE.              */
    for (n = 0; n < a; ++n)
        LAE[n] = LA[n];

    /*  Append infinity at the end. The macro HUGE_VAL in math.h will do.     */
    LAE[a] = HUGE_VAL;

    /*  Do the same for LBE and LCE.                                          */
    for (n = 0; n < b; ++n)
        LBE[n] = LB[n];

    LBE[b] = HUGE_VAL;

    for (n = 0; n < c; ++n)
        LCE[n] = LC[n];

    LCE[c] = HUGE_VAL;

    /*  Set indA, indB, and indC to zero and start the sorting.               */
    indA = 0;
    indB = 0;
    indC = 0;
    k = 0;
    while (k < size)
    {
        /*  We're sorting in increasing order, so choose the smaller value.   */
        if ((LAE[indA] <= LBE[indB]) && (LAE[indA] <= LCE[indC]))
        {
            out[k] = LAE[indA];
            ++indA;
        }
        else if (LBE[indB] <= LCE[indC])
        {
            out[k] = LBE[indB];
            ++indB;
        }
        else
        {
            out[k] = LCE[indC];
            ++indC;
        }
        ++k;
    }
    /*  End of while-loop sorting the data.                                   */

    /*  And don't forget to free the pointers we malloc'd.                    */
    free(LAE);
    free(LBE);
    free(LCE);
}
/*  End of merge.                                                             */

/*  Merge sort algorithm for an array of length arr_length.                   */
double *merge_sort(double *arr, unsigned int arr_length)
{
    /*  Declare all necessary variables.                                      */
    double *LA, *LB, *LC, *LAS, *LBS, *LCS, *out;
    unsigned int a, b, c, n;

    /*  We can't sort an empty array, so check.                               */
    if (arr == NULL)
    {
        puts("merge_sort: input array is NULL. Returning.");
        return NULL;
    }

    /*  Base case for the recursion.                                          */
    if (arr_length <= 1)
        return arr;

    /*  Floor(arr_length/3) will return zero for the case of arr_length = 2   *
     *  so we handle this case separately as well.                            */
    if (arr_length == 2)
    {
        double temp;
        if (arr[0] >= arr[1])
        {
            temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return arr;
    }

    /*  Divide the array roughly into thirds and store in LA, LB, and LC.     */
    a = (unsigned int) floor(0.3334 * arr_length);
    b = (unsigned int) floor(0.3334 * arr_length);
    c = arr_length - (a + b);

    /*  Allocate memory for LA and LB.                                        */
    LA = malloc(sizeof(*LA) * a);
    LB = malloc(sizeof(*LB) * b);
    LC = malloc(sizeof(*LC) * c);

    /*  Check that malloc didn't fail.                                        */
    if ((LA == NULL) || (LB == NULL) || (LC == NULL))
    {
        puts("merge_sort: Malloc returned NULL. Aborting.\n");
        return NULL;
    }

    /*  Fill the arrays LA, LB, and LC with the necessary data in arr.        */
    for (n = 0; n < a; ++n)
        LA[n] = arr[n];

    for (n = 0; n < b; ++n)
        LB[n] = arr[n + a];

    for (n = 0; n < c; ++n)
        LC[n] = arr[n + a + b];

    /*  Use recursion on the three thirds of arr.                             */
    LAS = merge_sort(LA, a);
    LBS = merge_sort(LB, b);
    LCS = merge_sort(LC, c);

    /*  Allocate memory for the output array and merge.                       */
    out = malloc(sizeof(*out) * arr_length);
    merge(out, LAS, LBS, LCS, a, b, c);

    /*  Free the LA and LB pointers we malloc'd above.                        */
    free(LA);
    free(LB);
    free(LC);

    /*  If a <= 2, merge_sort didn't allocate memory for LAS but instead      *
     *  simply returned LA, so LAS = LA. We already freed the LA pointer, so  *
     *  be careful not to crash the program by freeing the same pointer twice.*
     *  Check the values of a, b, and c before freeing.                       */
    if (a > 2)
        free(LAS);
    if (b > 2)
        free(LBS);
    if (c > 2)
        free(LCS);

    ++counter;

    /*  Finally, return the sorted array.                                     */
    return out;
}
/*  End of merge_sort.                                                        */

/*  Same function as before for pseudo-random real numbers in [0, 1].         */
double real_rand(void)
{
    return (double) rand()/RAND_MAX;
}

/*  Function for testing our merge-sort algorithm.                            */
int main(void)
{
    /*  Variable for indexing.                                                */
    unsigned int m, n;

    /*  Size of the random array we'll be testing.                            */
    unsigned int N = 8*1024U;

    /*  Pointers for the sorted and unsorted arrays.                          */
    double *sorted;
    double *unsorted;
    double *arr = malloc(sizeof(*arr) * N);

    for (m = 1; m <= N; ++m)
    {
        unsorted = malloc(sizeof(*unsorted) * m);

        /*  Make unsorted an array of random real numbers.                    */
        for (n = 0; n < m; ++n)
            unsorted[n] = real_rand();

        /*  Run the sorting algorithm, storing the outcome in sorted.         */
        counter = 0;
        sorted = merge_sort(unsorted,  m);

        /*  Check that the algorithm worked. If it does nothing should print. */
        for (n = 1; n < m; ++n)
        {
            if (sorted[n] < sorted[n-1])
            {
                puts("Not Sorted!");
                if (m > 2)
                    free(sorted);
                free(unsorted);
                return -1;
            }
        }
        /*  And of check for the sorting procedure.                           */

        /*  Append counter to the arr pointer so we can plot the number of    *
         *  recursive operations that were needed as a function of array size.*/
        arr[m-1] = (double)counter;

        /*  Don't free sorted is m <= 2 since sorted and unsorted will point  *
         *  to the same block of memory. We'll end up freeing twice.          */
        if (m > 2)
            free(sorted);
        free(unsorted);
    }
    /*  End of for-loop testing our merge sort algorithm.                     */

    /*  Plot the efficiency-vs-array-size image.                              */
    draw_pic(arr, N);

    /*  Finally, free arr and exit the function.                              */
    free(arr);
    return 0;
}
/*  End of main.                                                              */
