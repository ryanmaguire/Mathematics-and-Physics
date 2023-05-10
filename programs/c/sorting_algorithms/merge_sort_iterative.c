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

/*  Global variable for counting the number of pictures drawn.                */
unsigned int current_pic = 0;

/*  Function for drawing a scatter plot of an array arr of length arr_length. */
void draw_pic(double *arr, unsigned int arr_length)
{
    /*  Declare variables for sampling the box we're drawing to.              */
    unsigned int x, y;
    double z_x, z_y;
    double rcpr_factor = 1.0 / (double)arr_length;

    /*  Set the boundaries of the box.                                        */
    double y_min = 0.0;
    double y_max = 1.0;
    double pixel_width = 0.001;

    /*  Variables for coloring the current pixel.                             */
    unsigned char black = 0U;
    unsigned char white = 255U;

    /*  And a variable for writing to a file.                                 */
    FILE *fp;

    /*  Create the filename. And array of char's acts as a string in C.       */
    char str[80];

    /*  Use the sprintf function in stdio.h to create a formatted string str  *
     *  which will serve as the name of the file we're drawing. We're         *
     *  formatting it by appending the picture counter at the end to prevent  *
     *  overwriting previous drawings. We'll increment this counter at the    *
     *  end of our drawing procedure.                                         */
    sprintf(str, "merge_sort_%u.pgm", current_pic);

    /*  Open the PGM file and write the preamble to it.                       */
    fp = fopen(str, "w");
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

            /*  Otherwise, color the background black.                        */
            else
                fputc(black, fp);
        }
        /*  End of for-loop for the pixels x-coordinate.                      */
    }
    /*  End of for-loop for the pixels y-coordinate.                          */
    fclose(fp);

    /*  Increment the picture counter.                                        */
    ++current_pic;
}
/*  End of draw_pic.                                                          */

/*  Function for merging an unsorted array using a sorted reference array.    *
 *  This is similar to recursive merge sort, but uses an iterative scheme.    */
void merge(double *unsorted, unsigned left, unsigned int right,
           unsigned int end, double *sorted)
{
    /*  Declare variables for indexing.                                       */
    unsigned int m, n, k;

    /*  Like the recursive method, we're going to go left to right and set    *
     *  the current value of the array we're sorting to the lesser of the two *
     *  values we're comparing.                                               */
    m = left;
    n = right;

    /*  Loop over all of the values in the current window we're merging.      */
    for (k = left; k < end; ++k)
    {
        if ((m < right) && ((n >= end) || (unsorted[m] <= unsorted[n])))
        {
            sorted[k] = unsorted[m];
            ++m;
        }
        else
        {
            sorted[k] = unsorted[n];
            ++n;
        }
    }
    /*  End of for-loop merging the sorted data.                              */
}
/*  End of merge.                                                             */

/*  Iterative merge-sort algorithm for an array arr of size arr_size.         */
double *merge_sort(double *arr, unsigned int arr_size)
{
    /*  Declare all necessary variables.                                      */
    unsigned int width;
    unsigned int left, right, end, n;
    double *unsorted, *sorted;

    /*  We're going to copy the data in arr into unsorted so as not to        *
     *  potentially corrupt or change the input.                              */
    unsorted = malloc(sizeof(*unsorted) * arr_size);
    sorted   = malloc(sizeof(*sorted) * arr_size);

    /*  Set both sorted and unsorted to the same values as arr.               */
    for (n=0; n<arr_size; ++n)
    {
        unsorted[n] = arr[n];
        sorted[n] = arr[n];
    }

    /*  Draw the starting values of the unsorted data.                        */
    draw_pic(sorted, arr_size);

    /*  We're splitting the array into smaller powers of two. This iterative  *
     *  scheme is equivalent to the recursive one.                            */
    for (width = 1; width < arr_size; width = 2 * width)
    {
        for (left = 0; left < arr_size; left = left + 2 * width)
        {
            /*  Ensure that right hasn't gone beyond the size of the array.   *
             *  This can happen if the array size isn't a power of two.       */
            if ((left + width) < arr_size)
                right = left + width;
            else
                right = arr_size;

            /*  Similarly, ensure that end isn't beyond the array size.       */
            if (left + 2*width < arr_size)
                end = left + 2*width;
            else
                end = arr_size;

            /*  Sort the current window we're looking at.                     */
            merge(sorted, left, right, end, unsorted);
        }

        /*  Merge sorted the sorted data into unsorted. Copy this into sorted.*/
        for (n = 0; n < arr_size; ++n)
            sorted[n] = unsorted[n];

        /*  Draw what the data currently looks like.                          */
        draw_pic(sorted, arr_size);
    }

    /*  Free the malloc'd pointer unsorted and return sorted.                 */
    free(unsorted);
    return sorted;
}
/*  End of merge_sort.                                                        */

/*  Function for returning a random real number in [0, 1].                    */
double real_rand(void)
{
    return (double) rand()/RAND_MAX;
}

/*  Function for testing our sorting algorithm.                               */
int main(void)
{
    /*  Declare a variable for indexing.                                      */
    unsigned int n;

    /*  And the size of the random array we're making. A power of 2 makes the *
     *  algorithm faster, so use this.                                        */
    unsigned int N = 4*1024U;
    double *sorted;

    /*  Allocate memory for the random unsorted array.                        */
    double *x = malloc(sizeof(*x) * N);

    /*  Set the entries of x to random values.                                */
    for (n = 0; n < N; ++n)
        x[n] = real_rand();

    /*  Sort the data.                                                        */
    sorted = merge_sort(x,  N);

    /*  Check if our sort work. If it did, nothing should print.              */
    for (n = 1; n < N; ++n)
    {
        if (sorted[n] < sorted[n-1])
        {
            puts("Not Sorted!");
            break;
        }
    }
    free(sorted);
    return 0;
}
/*  End of main.                                                              */
