/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of KissVG.                                              *
 *                                                                            *
 *  KissVG is free software: you can redistribute it and/or modify it         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  KissVG is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with KissVG.  If not, see <https://www.gnu.org/licenses/>.          *
 ******************************************************************************
 *                              kissvg_vector                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the main tools for working with vectors, both two and three   *
 *      dimensional. The typedef's are provided in kissvg.h.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

#include <kissvg/src/kissvg_math.h>
#include <kissvg/src/kissvg_vector.h>

/*  NOTE:                                                                     *
 *      Detailed descriptions of the functions are provided in kissvg.h.      */

/*  The primary tool for creating new kissvg_TwoVector's.                     */
kissvg_TwoVector kissvg_New_TwoVector(double x, double y)
{
    kissvg_TwoVector new;

    /*  Simply set the zeroth value to x and the first value to y.            */
    new.dat[0] = x;
    new.dat[1] = y;
    return new;
}

/*  Function for computing vector sums of kissvg_TwoVector's.                 */
kissvg_TwoVector kissvg_TwoVector_Add(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    kissvg_TwoVector sum;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    /*  Use the kissvg_TwoVectorXComponent and kissvg_TwoVectorYComponent     *
     *  macros to access the needed values and compute the sums.              */
    x_new = kissvg_TwoVector_X_Component(P) + kissvg_TwoVector_X_Component(Q);
    y_new = kissvg_TwoVector_Y_Component(P) + kissvg_TwoVector_Y_Component(Q);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    sum = kissvg_New_TwoVector(x_new, y_new);
    return sum;
}

/*  Function for computing vector subtraction.                                */
kissvg_TwoVector
kissvg_TwoVector_Subtract(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    kissvg_TwoVector diff;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    /*  Do the same thing as kissvg_TwoVectorAdd, but subtract.               */
    x_new = kissvg_TwoVector_X_Component(P) - kissvg_TwoVector_X_Component(Q);
    y_new = kissvg_TwoVector_Y_Component(P) - kissvg_TwoVector_Y_Component(Q);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    diff = kissvg_New_TwoVector(x_new, y_new);
    return diff;
}

/*  Function for computing scalar multiplication of a scalar with a vector.   */
kissvg_TwoVector kissvg_TwoVector_Scale(double r, kissvg_TwoVector P)
{
    /*  Declare necessary variables.                                          */
    kissvg_TwoVector out;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    x_new = r*kissvg_TwoVector_X_Component(P);
    y_new = r*kissvg_TwoVector_Y_Component(P);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    out = kissvg_New_TwoVector(x_new, y_new);
    return out;
}
