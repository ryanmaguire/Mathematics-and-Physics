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
 *      Generates a Newton fractal for p(z) = z^10 - 1.                       *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/04                                                        *
 ******************************************************************************/

/*  Functions for creating Newton fractals.                                   */
#include "nf.h"

/*  Routine for plotting the Newton fractal for z^10 - 1.                     */
int main(void)
{
    /*  The coefficients for the polynomial p(z) = -1 + z^8.                  */
    double coeffs[11] = {-1.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.0};

    /*  Name of the output PPM file.                                          */
    const char *name = "newton_fractal_z10_minus_one.ppm";

    /*  Reset the number of iterations for this more complex fractal.         */
    nf_reset_max_iters(224U);

    /*  Create the Newton fractal.                                            */
    NF_REAL_NEWTON_FRACTAL(coeffs, name);
    return 0;
}
/*  End of main.                                                              */
