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
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Used for graphing functions.                                              */
import graph;

/*  Draw the image on a PDF file.                                             */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Lengths of the axes.                                                      */
real start = -0.4;
real fin = 1.7;

/*  Start and end of the curve.                                               */
real xmin = -0.3;
real xmax =  1.5;

/*  Label for the axes.                                                       */
Label L;

/*  Number of samples used for curves.                                        */
int samples = 20;

/*  Pen used for axes.                                                        */
pen apen = black+linewidth(0.5pt);

/*  Path for drawing curves.                                                  */
path g;

/*  Curve to be drawn.                                                        */
real f(real x)
{
    return exp(x - 1.0);
}

/*  Draw the axes.                                                            */
L = Label("$x$", position=1, S);
draw(L, (start, 0.0)--(fin, 0.0), apen, SharpArrow(arsize));

L = Label("$y$", position=1, W);
draw(L, (0.0, start)--(0.0, fin), apen, SharpArrow(arsize));

/*  Draw a curve.                                                             */
g = graph(f, xmin, xmax, samples, operator ..);
draw(g, deepblue, SharpArrow(StealthHead, arsize));

/*  Add a curve with the same slope as the previous one.                      */
g = reflect((0.0, 0.0), (1.0, 1.0))*g;
draw(g, deepred, SharpArrow(StealthHead, arsize));

/*  Add another curve with the same slope.                                    */
xmax += 0.1;
draw((xmin, xmin) -- (xmax, xmax), deepgreen, SharpArrow(StealthHead, arsize));

/*  Put a dot at the point of interest.                                       */
dot("$p$", (1, 1), S);
