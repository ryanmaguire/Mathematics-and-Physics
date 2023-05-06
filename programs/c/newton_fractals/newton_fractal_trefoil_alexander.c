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
 *      Generates a Newton fractal for the trefoil Alexander polynomial.      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/06                                                        *
 ******************************************************************************/

/*  Functions for creating Newton fractals.                                   */
#include "nf.h"

/*  Routine for plotting the Newton fractal for the Trefoil knot.             */
int main(void)
{
    /*  The coefficients for the Alexander polynomial.                        */
    double num_coeffs[3] = {1.0, -1.0, 1.0};
    double den_coeffs[2] = {0.0, 1.0};

    /*  Name of the output PPM file.                                          */
    const char *name = "newton_fractal_trefoil_alexander.ppm";

    /*  Create the Newton fractal.                                            */
    NF_REAL_RAT_NEWTON_FRACTAL(num_coeffs, den_coeffs, name);
    return 0;
}
/*  End of main.                                                              */
