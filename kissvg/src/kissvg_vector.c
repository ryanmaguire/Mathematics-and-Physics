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

#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>

/*  NOTE:                                                                     *
 *      Detailed descriptions of the functions are provided in kissvg.h.      */

/*  The primary tool for creating new kissvg_TwoVector's.                     */
kissvg_TwoVector kissvg_NewTwoVector(double x, double y)
{
    kissvg_TwoVector NewVector;

    /*  Simply set the zeroth value to x and the first value to y.            */
    NewVector.dat[0] = x;
    NewVector.dat[1] = y;

    return NewVector;
}

/*  Function for computing vector sums of kissvg_TwoVector's.                 */
kissvg_TwoVector kissvg_TwoVectorAdd(kissvg_TwoVector P, kissvg_TwoVector Q)
{
    kissvg_TwoVector sum;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    /*  Use the kissvg_TwoVectorXComponent and kissvg_TwoVectorYComponent     *
     *  macros to access the needed values and compute the sums.              */
    x_new = kissvg_TwoVectorXComponent(P) + kissvg_TwoVectorXComponent(Q);
    y_new = kissvg_TwoVectorYComponent(P) + kissvg_TwoVectorYComponent(Q);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    sum = kissvg_NewTwoVector(x_new, y_new);
    return sum;
}

/*  Function for computing vector subtraction.                                */
kissvg_TwoVector kissvg_TwoVectorSubtract(kissvg_TwoVector P,
                                          kissvg_TwoVector Q)
{
    kissvg_TwoVector diff;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    /*  Do the same thing as kissvg_TwoVectorAdd, but subtract.               */
    x_new = kissvg_TwoVectorXComponent(P)-kissvg_TwoVectorXComponent(Q);
    y_new = kissvg_TwoVectorYComponent(P)-kissvg_TwoVectorYComponent(Q);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    diff = kissvg_NewTwoVector(x_new, y_new);
    return diff;
}

/*  Function for computing scalar multiplication of a scalar with a vector.   */
kissvg_TwoVector kissvg_TwoVectorScale(double r, kissvg_TwoVector P)
{
    kissvg_TwoVector out;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    x_new = r*kissvg_TwoVectorXComponent(P);
    y_new = r*kissvg_TwoVectorYComponent(P);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    out = kissvg_NewTwoVector(x_new, y_new);
    return out;
}

kissvg_TwoVector kissvg_PlaneToDiskHomeo(kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double px, py;
    double outx, outy;
    double norm;
    double scale_factor;

    px = kissvg_TwoVectorXComponent(P);
    py = kissvg_TwoVectorYComponent(P);

    if ((px == 0.0) && (py == 0.0))
    {
        outx = 0.0;
        outy = 0.0;
    }
    else
    {
        norm = kissvg_EuclideanNorm2D(P);
        outx = px/norm;
        outy = py/norm;

        scale_factor = (-1.0 + sqrt(4.0*norm*norm + 1.0))/(2.0*norm);

        outx *= scale_factor;
        outy *= scale_factor;
    }
    out = kissvg_NewTwoVector(outx, outy);

    return out;
}

