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
 *                              kissvg_matrix                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide basic linear algebra routines.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

#include <kissvg/include/kissvg.h>
#include <kissvg/include/kissvg_math.h>
#include <kissvg/include/kissvg_bool.h>

/*  NOTE:                                                                     *
 *      Detailed descriptions of the functions are provided in kissvg.h.      */

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                 Begin kissvg_TwoByTwoMatrix Functions                      *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

kissvg_TwoByTwoMatrix kissvg_NewTwoByTwoMatrix(double a, double b,
                                               double c, double d)
{
    kissvg_TwoByTwoMatrix A;

    A.dat[0][0] = a;
    A.dat[0][1] = b;
    A.dat[1][0] = c;
    A.dat[1][1] = d;

    return A;
}

kissvg_TwoVector kissvg_TwoVectorMatrixTransform(kissvg_TwoByTwoMatrix A,
                                                 kissvg_TwoVector P)
{
    kissvg_TwoVector out;
    double x_new, y_new;
    double x0, y0;
    double a, b, c, d;

    x0 = kissvg_TwoVectorXComponent(P);
    y0 = kissvg_TwoVectorYComponent(P);

    a = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    b = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    c = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    d = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    x_new = a*x0 + b*y0;
    y_new = c*x0 + d*y0;

    out = kissvg_NewTwoVector(x_new, y_new);
    return out;
}

kissvg_TwoByTwoMatrix kissvg_RotationMatrix2D(double theta)
{
    double cos_theta, sin_theta;
    kissvg_TwoByTwoMatrix R;

    cos_theta = cos(theta);
    sin_theta = sin(theta);

    R = kissvg_NewTwoByTwoMatrix(cos_theta, -sin_theta, sin_theta, cos_theta);
    return R;
}

kissvg_TwoByTwoMatrix kissvg_TwoByTwoMatrixScale(double r,
                                                 kissvg_TwoByTwoMatrix A)
{
    kissvg_TwoByTwoMatrix out;
    double a00, a01, a10, a11;

    a00 = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    a01 = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    a10 = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    a11 = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    out = kissvg_NewTwoByTwoMatrix(r*a00, r*a01, r*a10, r*a11);
    return out;
}

kissvg_TwoByTwoMatrix kissvg_InverseTwoByTwoMatrix(kissvg_TwoByTwoMatrix A)
{
    double a, b, c, d, det, det_rcp;
    double ainv, binv, cinv, dinv;

    a = kissvg_TwoByTwoMatrixComponent(A, 0, 0);
    b = kissvg_TwoByTwoMatrixComponent(A, 0, 1);
    c = kissvg_TwoByTwoMatrixComponent(A, 1, 0);
    d = kissvg_TwoByTwoMatrixComponent(A, 1, 1);

    det = a*d - b*c;

    if (det == 0)
    {
        ainv = kissvg_NaN;
        binv = kissvg_NaN;
        cinv = kissvg_NaN;
        dinv = kissvg_NaN;
    }
    else
    {
        det_rcp = 1.0/det;
        ainv = d*det_rcp;
        binv = -b*det_rcp;
        cinv = -c*det_rcp;
        dinv = a*det_rcp;
    }
    return kissvg_NewTwoByTwoMatrix(ainv, binv, cinv, dinv);
}
