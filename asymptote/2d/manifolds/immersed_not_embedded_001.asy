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

/*  Used for graphing parameterized curves.                                   */
import graph;

/*  Draw the image on a PDF file.                                             */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Pens used for drawing.                                                    */
pen dpen = deepblue + linewidth(0.4pt);
pen bpen = black + linewidth(0.4pt);

/*  Margin for the lemniscate arrows.                                         */
margin margins = TrueMargin(0.05cm, 0.05cm);

/*  Label for the axes.                                                       */
Label L;

/*  Size of the arrow head.                                                   */
real arsize = 5bp;

/*  Lengths of the axes.                                                      */
real xlen = 1.2;
real ylen = 1.2;

/*  Variable used for drawing the curve.                                      */
path p;

/*  Parametric equation for the lemiscate.                                    */
pair f(real theta)
{
    return (sin(theta), sin(2.0*theta));
}

/*  Draw the x and y axes and label them.                                     */
L = Label("$x$", position=1, S, fontsize(9pt));
draw(L, (-xlen, 0.0)--(xlen, 0.0), bpen, SharpArrow(arsize));

L = Label("$y$", position=1, W, fontsize(9pt));
draw(L, (0.0, -ylen)--(0.0, ylen), bpen, SharpArrow(arsize));

/*  Draw the lemniscate.                                                      */
p = graph(f, -pi, pi, 300, operator ..);
draw(p, dpen, SharpArrows(StealthHead, arsize), margins);
