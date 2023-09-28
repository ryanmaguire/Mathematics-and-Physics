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
 *      Provides default pens, arrows, and more for size(512) images.         *
 ******************************************************************************/

/*  Default margin sizes that are commonly used provided here.                */
include default_margins;

/*  Sharp tikz style arrows provided here.                                    */
include default_arrows;

/*  The size of an image for size_512_default_settings is... 512.             */
size(512);

/*  Radius used for creating dots to label points.                            */
real dot_radius = 0.07;

/*  Default types, font sizes, and pen sizes that are most commonly used.     */
pen label_size = fontsize(14pt);
pen dash_type = linetype("4 4");
pen thin_line_width = linewidth(0.5pt);
pen line_width = linewidth(0.8);
pen thick_line_width = linewidth(1.2);

/*  Dashed pens, colored pens, and dashed colored pens defined in this file.  */
include default_pens;
