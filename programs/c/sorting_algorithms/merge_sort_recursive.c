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

/*  Function for merging two SORTED lists into one. It is assumed the pointer *
 *  out has already been allocated sufficient memory for this problem. LA and *
 *  LB are two arrays of lengths a and b, respectively.                       */
void merge(double *out, double *LA, double *LB, unsigned int a, unsigned int b)
{
    /*  We'll need two extended arrays equal to LA and LB, respectively, with *
     *  an additional "infinity" tacked on the end.                           */
    double *LAE, *LBE;

    /* Three variables for indexing.                                          */
    unsigned int k, m, n;

    /*  LAE needs the same number of entries as LA, plus 1 for infinity.      *
     *  Similarly for LBE.                                                    */
    LAE = malloc(sizeof(*LAE) * (a+1));
    LBE = malloc(sizeof(*LBE) * (b+1));

    /*  Check the malloc didn't fail.                                         */
    if (LAE == NULL)
    {
        puts("merge: Malloc returned NULL for LAE. Returning\n");
        return;
    }
    else if  (LBE == NULL)
    {
        puts("merge: Malloc returned NULL for LBE. Returning\n");
        return;
    }

    /*  Set the values of the extended arrays LAE and LBE.                    */
    for (m = 0; m < a; ++m)
        LAE[m] = LA[m];

    /*  Append infinity at the end. The macro HUGE_VAL in math.h will do.     */
    LAE[a] = HUGE_VAL;

    /*  Do the same for LBE.                                                  */
    for (n = 0; n < b; ++n)
        LBE[n] = LB[n];

    LBE[b] = HUGE_VAL;

    /*  Reset n and m to zero since we used them in the above for loop and    *
     *  then start the sort.                                                  */
    m = 0;
    n = 0;
    k = 0;
    while (k < (a+b))
    {
        /*  We're sorting in increasing order, so choose the smaller value.   */
        if (LAE[m] <= LBE[n])
        {
            out[k] = LAE[m];
            ++m;
        }
        else
        {
            out[k] = LBE[n];
            ++n;
        }
        ++k;
    }
    /*  End of while-loop sorting the data.                                   */

    /*  And don't forget to free the pointers we malloc'd.                    */
    free(LAE);
    free(LBE);
}
/*  End of merge.                                                             */

/*  Merge sort algorithm for an array of length arr_length.                   */
double *merge_sort(double *arr, unsigned int arr_length)
{
    /*  Declare all necessary variables.                                      */
    double *LA, *LB, *LAS, *LBS, *out;
    unsigned int a, b, n;

    /*  We can't sort an empty array, so check.                               */
    if (arr == NULL)
    {
        puts("merge_sort: input array is NULL. Returning.");
        return NULL;
    }

    /*  Base case for the recursion.                                          */
    if (arr_length == 1)
        return arr;

    /*  Divide the array roughly in half and store in LA and LB.              */
    a = (unsigned int) floor(0.5 * arr_length);
    b = arr_length - a;

    /*  Allocate memory for LA and LB.                                        */
    LA = malloc(sizeof(*LA) * a);
    LB = malloc(sizeof(*LB) * b);

    /*  Check that malloc didn't fail.                                        */
    if (LA == NULL)
    {
        puts("merge_sort: Malloc returned NULL for LA. Returning\n");
        return NULL;
    }
    else if  (LB == NULL)
    {
        puts("merge_sort: Malloc returned NULL for LB. Returning\n");
        return NULL;
    }

    /*  Fill the arrays LA and LB with the left and right sides of the input  *
     *  array arr, respectively.                                              */
    for (n = 0; n < a; ++n)
        LA[n] = arr[n];

    for (n = 0; n < b; ++n)
        LB[n] = arr[n+a];

    /*  Use recursion on the two halves of arr.                               */
    LAS = merge_sort(LA, a);
    LBS = merge_sort(LB, b);

    /*  Allocate memory for the output array and merge.                       */
    out = malloc(sizeof(*out) * arr_length);
    merge(out, LAS, LBS, a, b);

    /*  Free the LA and LB pointers we malloc'd above.                        */
    free(LA);
    free(LB);

    /*  If a is 1, merge_sort didn't allocate memory for LAS but instead      *
     *  simply returned LA, so LAS = LA. We already freed the LA pointer, so  *
     *  be careful not to crash the program by freeing the same pointer twice.*
     *  Check the values of a and b before freeing.                           */
    if (a != 1)
        free(LAS);
    if (b != 1)
        free(LBS);

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
    unsigned int n;

    /*  Size of the random array we'll be testing.                            */
    unsigned int N = 1000U;

    /*  Pointers for the sorted and unsorted arrays.                          */
    double *sorted;
    double *unsorted = malloc(sizeof(*unsorted) * N);

    /*  Make unsorted an array of random real numbers.                        */
    for (n = 0; n < N; ++n)
        unsorted[n] = real_rand();

    /*  Run the sorting algorithm, storing the outcome in sorted.             */
    sorted = merge_sort(unsorted,  N);

    /*  Check that the algorithm worked. If it does, nothing should print.    */
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
