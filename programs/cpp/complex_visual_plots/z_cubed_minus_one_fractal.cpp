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
 *      Creates a complex plot for the Newton iteration of z^3 - 1.           *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/18                                                        *
 ******************************************************************************/

/*  Plotting routines given here.                                             */
#include "cvp.hpp"

/*  The Newton iteration for z^3 - 1.                                         */
static inline cvp::complex f(cvp::complex z)
{
    return z - (z*z*z - 1.0)/(3.0*z*z);
}

/*  Routine for plotting the first three iterations of Newton's method.       */
int main(void)
{
    /*  Name of the output PPM file.                                          */
    const char *name = "z_cubed_minus_one_fractal.ppm";

    /*  Create the plots.                                                     */
    cvp::iters_plot(f, 3, cvp::color_wheel_from_complex, name);
    return 0;
}
/*  End of main.                                                              */
