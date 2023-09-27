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

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as custom_arrows;

/*  The size of an image for size_512_default_settings is... 512.             */
size(512);

/*  Default types, font sizes, and pen sizes that are most commonly used.     */
pen label_size = fontsize(14pt);
pen dash_type = linetype("4 4");
pen thin_line_width = linewidth(0.5pt);
pen line_width = linewidth(0.8);
pen thick_line_width = linewidth(1.2);

/*  Create the default pen that is called by "draw" when no pen is specified. */
defaultpen(black + line_width + label_size);

/*  Thinner and thicker alternatives that are commonly required.              */
pen thin_pen = black + thin_line_width + label_size;
pen thick_pen = black + thick_line_width + label_size;

/*  Dashed variants of the previous pens.                                     */
pen thin_dash_pen = thin_pen + dash_type;
pen dash_pen = defaultpen + dash_type;
pen thick_dash_pen = thick_pen + dash_type;

/*  Blue varients of the previously defined pens.                             */
pen blue_thin_pen = blue + thin_line_width + label_size;
pen blue_pen = blue + line_width + label_size;
pen blue_thick_pen = blue + thick_line_width + label_size;

pen blue_thin_dash_pen = blue_thin_pen + dash_type;
pen blue_dash_pen = blue_pen + dash_type;
pen blue_thick_dash_pen = blue_thick_pen + dash_type;

/*  Green varients of the previously defined pens.                            */
pen green_thin_pen = green + thin_line_width + label_size;
pen green_pen = green + line_width + label_size;
pen green_thick_pen = green + thick_line_width + label_size;

pen green_thin_dash_pen = green_thin_pen + dash_type;
pen green_dash_pen = green_pen + dash_type;
pen green_thick_dash_pen = green_thick_pen + dash_type;

/*  Red varients of the previously defined pens.                              */
pen red_thin_pen = red + thin_line_width + label_size;
pen red_pen = red + line_width + label_size;
pen red_thick_pen = red + thick_line_width + label_size;

pen red_thin_dash_pen = red_thin_pen + dash_type;
pen red_dash_pen = red_pen + dash_type;
pen red_thick_dash_pen = red_thick_pen + dash_type;

/*  Default size of arrow heads.                                              */
real arrow_size = 5bp;

/*  The default arrow head uses the "tikz-stealth" style in custom_arrows.    */
arrowbar sharp_arrow = custom_arrows.SharpArrow(arrow_size);

/*  Radius used for creating dots to label points.                            */
real dot_radius = 0.07;