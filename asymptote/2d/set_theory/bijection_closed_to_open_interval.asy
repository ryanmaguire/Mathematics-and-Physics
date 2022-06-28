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
 *      Draw a bijection from [0, 1] to (0, 1).                               *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

/*  Thicker black pen used for the axes.                                      */
pen axesp = black + linewidth(0.8pt);

/*  Lengths of the x and y axes.                                              */
real minlen = -0.5;
real maxlen = 4.4;

/*  End value for the line to be drawn.                                       */
real xend = 4.0;

/*  Coordinates for various points.                                           */
pair O = (0.0, 0.0);
pair P = (xend, xend);

/*  Variable for indexing and for looping over.                               */
int n;
real x = xend;

/*  The number of dots in the drawing.                                        */
int number_of_dots = 8;

/*  Size of a dot.                                                            */
real rDot = 0.03;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Endpoints of the x and y axes.                                            */
pair[] X = {(minlen, 0.0), (maxlen, 0.0)};
pair[] Y = {(0.0, minlen), (0.0, maxlen)};

/*  Draw the x and y axes.                                                    */
draw(Label("$x$", position=1.0), X[0] -- X[1], N, axesp, SharpArrow(arsize));
draw(Label("$y$", position=1.0), Y[0] -- Y[1], E, axesp, SharpArrow(arsize));

/*  Draw the main line.                                                       */
draw(O -- P);

/*  Draw a dot a f(0).                                                        */
filldraw(circle((0.0, 0.5*xend), rDot), black, black);

/*  Loop over the points to be drawn.                                         */
for (n = 0; n < number_of_dots; ++n)
{
    filldraw(circle((x, x), rDot), white, black);
    filldraw(circle((x, 0.25*x), rDot), black, black);
    x *= 0.5;
}
