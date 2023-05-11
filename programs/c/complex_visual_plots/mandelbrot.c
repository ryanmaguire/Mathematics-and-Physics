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
 *      Plots the sixth iteration of the Mandelbrot sequence.                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/11                                                        *
 ******************************************************************************/

/*  Complex plotting routines given here.                                     */
#include "cvp.h"

/*  The function to be plotted.                                               */
CVP_INLINE struct cvp_complex f(const struct cvp_complex *z)
{
    /*  The standard Mandelbrot set corresponds to z^2 + c. Set f(z) = z^2.   */
    return cvp_complex_square(z);
}

/*  Routine for plotting six iterations of the Mandelbrot sequence.           */
int main(void)
{
    /*  Name of the output PPM file.                                          */
    const char *name = "mandelbrot_six_iters.ppm";

    /*  The Mandelbrot iteration diverges rapidly for points outside of the   *
     *  Mandelbrot set. Do not set this value too high or most of the screen  *
     *  will be black.                                                        */
    const unsigned int iters = 6U;

    /*  Create the plot.                                                      */
    cvp_mandel_plot(f, iters, cvp_color_wheel_from_complex, name);
    return 0;
}
/*  End of main.                                                              */
