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
 *      Plots the first 6 iterations of the Mandelbrot function.              *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/15                                                        *
 ******************************************************************************/

package main

/*  The Mandebrot set is defined by F_{c}(z) = z^2 + c. Set f(z) = z^2.       */
func mandel(z complex128) complex128 {
    return z*z
}

/*  Plot six iterations of the function.                                      */
func main() {

    /*  Name of the output PPM file.                                          */
    var name string = "mandelbrot_six_iters.ppm"

    /*  The number of iterations to perform.                                  */
    var iters uint32 = 6

    /*  Plot the results.                                                     */
    MandelPlot(mandel, iters, ColorWheelFromComplex, name)
}
