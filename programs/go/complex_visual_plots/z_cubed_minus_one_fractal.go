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
 *  Date:   2023/04/15                                                        *
 ******************************************************************************/

package main

func g(z complex128) complex128 {
    return z - (z*z*z - 1.0)/(3.0*z*z)
}

func f(z complex128) complex128 {

    var w complex128 = g(z)
    for n := 0; n < 3; n += 1 {
        w = g(w);
    }

    return w
}

func main() {
    ComplexPlot(f, ColorWheelFromComplex, "z_cubed_minus_one.ppm")
}
