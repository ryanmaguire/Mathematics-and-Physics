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
 *      Plots 6 iterations of the Mandelbrot set for f_{c}(z) = z^2 + c.      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/18                                                        *
 ******************************************************************************/

/*  Plotting routines given here.                                             */
#include "cvp.hpp"

/*  The function to be plotted.                                               */
static inline cvp::complex f(cvp::complex z)
{
    return z*z;
}

/*  Routine for plotting six iterations of the Mandelbrot set.                */
int main(void)
{
    /*  Name of the output PPM file.                                          */
    const char *name = "mandelbrot_six_iters.ppm";

    /*  The number of iterations to perform.                                  */
    const unsigned int iters = 6U;

    /*  Create the plots.                                                     */
    cvp::mandelbrot_plot(f, iters, cvp::color_wheel_from_complex, name);
    return 0;
}
/*  End of main.                                                              */
