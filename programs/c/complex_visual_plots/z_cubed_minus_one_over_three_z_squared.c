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
 *      Plots the function (z^3 - 1)/(3z^2).                                  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/04                                                        *
 ******************************************************************************/

/*  Complex plotting routines given here.                                     */
#include "cvp.h"

/*  The function to be plotted.                                               */
CVP_INLINE struct cvp_complex f(const struct cvp_complex *z)
{
    /*  Compute 2z^3 + 1 using complex functions.                             */
    const struct cvp_complex z_sq = cvp_complex_square(z);
    struct cvp_complex w = cvp_complex_multiply(z, &z_sq);
    cvp_complex_addto_real(-1.0, &w);
    cvp_complex_divideby(&w, &z_sq);
    cvp_complex_multiplyby_real(1.0 / 3.0, &w);
    return w;
}

/*  Routine for plotting the function f(z) = (z^3 - 1)/(3z^2).                */
int main(void)
{
    /*  Name of the output PPM file.                                          */
    const char *name = "z_cubed_minus_one_over_three_z_squared.ppm";

    /*  Create the plots.                                                     */
    cvp_complex_plot(f, cvp_color_wheel_from_complex, name);
    return 0;
}
/*  End of main.                                                              */
