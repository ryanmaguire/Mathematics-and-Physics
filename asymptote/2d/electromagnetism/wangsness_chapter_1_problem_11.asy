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

/*  Needed to draw the sqrt function.                                         */
import graph;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Default pen used for the axes and labels.                                 */
defaultpen(linewidth(0.7pt) + fontsize(7pt));

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Pen for tick marks.                                                       */
pen tpen = linewidth(0.4pt) + fontsize(5pt);

/*  Pen for drawing dashed lines.                                             */
pen dpen = linewidth(0.4pt) + linetype("4 4");

/*  Number of samples for drawing the function.                               */
int n_samples = 10;

/*  Various points used in the drawing.                                       */
pair X = (2.0, 0.0);
pair Y = (0.0, 1.414);
pair P = (2.0, 1.414);
pair O = (0.0, 0.0);

/*  Draw the x and y axes.                                                    */
draw((-0.1, 0.0) -- (2.2, 0.0), SharpArrow(arsize));
draw((0.0, -0.1) -- (0.0, 2.2), SharpArrow(arsize));

/*  Mark the axes with a few numbers.                                         */
draw(Label("$1$", position=1.0), (1.0, 0.03) -- (1.0, -0.03), tpen);
draw(Label("$2$", position=1.0), (2.0, 0.03) -- (2.0, -0.03), tpen);
draw(Label("$1$", position=1.0), (0.03, 1.0) -- (-0.03, 1.0), tpen);
draw(Label("$2$", position=1.0), (0.03, 2.0) -- (-0.03, 2.0), tpen);

/*  Draw dashed lines to indicate the position.                               */
draw(P -- X, dpen);
draw(P -- Y, dpen);

/*  Draw the function.                                                        */
draw(graph(sqrt, 0.0, 2.0, n_samples, operator ..), MidSharpArrow(arsize));

/*  Label the function.                                                       */
label("$y^{2}=x$", (1.0, 0.8));
