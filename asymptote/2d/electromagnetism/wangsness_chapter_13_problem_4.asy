/******************************************************************************
 *                                 LICENSE                                    *
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

/*  Size of the output figure.                                                */
size(128);

/*  Default font size for labels.                                             */
defaultpen(fontsize(8pt));

/*  Some lengths.                                                             */
real xlength = 3.0;
real ylength = 3.0;
real d = 1.0;
real a = 1.0;

/*  The origin, x axis, and y axis.                                           */
pair O = (0.0, 0.0);
pair X = (xlength, 0.0);
pair Y = (0.0, ylength);
pair YStart = (0.0, -0.5);

/*  Smaller font size.                                                        */
real fsize = 6pt;

/*  Length of an arrow.                                                       */
real arlength = 0.2;

/*  Size of a bar used to indicate a tiny displacement dl.                    */
real barsize = 2bp;

/*  Size of arrow heads.                                                      */
real ar = 5bp;

/*  Four points for the wire.                                                 */
pair A = (a, 0.0);
pair B = (a + d, 0.0);
pair C = (a + d, ylength);
pair D = (a, ylength);

/*  Displacements used in the drawing.                                        */
pair dx = (0.07, 0.00);
pair dy = (0.00, 0.07);
pair dl = (a, 0.35*ylength);
pair dlprime = (0.00, 0.5*ylength);
pair rprime = (0.00, 0.5*ylength);

/*  Two paths for drawing arrows used to highlight the displacement.          */
path uparrow = ((dl + dx - dy) - (0.0, arlength)) -- (dl + dx - dy);
path downarrow = ((dl + dx + dy) + (0.0, arlength)) -- (dl + dx + dy);

/*  Margin to prevent lines from overlapping labels.                          */
margin arrowmargin = TrueMargin(0.0, 0.03cm);

/*  Pen for dashed lines, regular drawing, and axes, respectively.            */
pen dpen = black + linewidth(0.5pt) + linetype("4 4");
pen cpen = black + linewidth(0.5pt);
pen apen = black + linewidth(0.7pt);

/*  Draw dashed lines for the x axis, and a solid line for the y axis.        */
draw(O -- X, dpen);
draw(YStart -- Y, cpen);

/*  Draw the wire.                                                            */
draw("I", A -- B, N, apen, SharpArrow(ar, currentpos=0.55));
draw("II", B -- C, W, apen, SharpArrow(ar, currentpos=0.55));
draw("III", C -- D, S, apen, SharpArrow(ar, currentpos=0.6));
draw("IV",  D -- A, E, apen, SharpArrow(ar, currentpos=0.5));

/*  Draw lines for the position vector, primed position vector, and relative  *
 *  position vector.                                                          */
draw("$\mathbf{r}$", O -- dl, NW, cpen);
draw("$\mathbf{r}'$", O -- rprime, W, cpen);
draw("$\mathbf{R}$", rprime -- dl, SW, cpen);

/*  Draw the bar for the displacement.                                        */
Label dEll = Label("$\textrm{d}\ell$", position=0.5, align=2E, fontsize(fsize));
draw(dEll, (dl + dx - dy) -- (dl + dx + dy), bar=Bars(barsize));
draw(downarrow, arrow=SharpArrow(), margin = arrowmargin);
draw(uparrow, arrow=SharpArrow(), margin = arrowmargin);

/*  Add the labels.                                                           */
label("$d$", (0.5*d,   -0.2));
label("$a$", (d+0.5*a, -0.2));
label("$b$", (d+a+0.2, 0.5*ylength));

/*  Draw the displacement for dEll prime.                                     */
dEll = Label("$\textrm{d}\ell'$", position=0.5, align=2W, fontsize(fsize));
uparrow = ((dlprime - dx - dy) - (0.0, arlength)) -- (dlprime-dx-dy);
downarrow = ((dlprime - dx + dy) + (0.0, arlength)) -- (dlprime-dx+dy);

draw(dEll, (dlprime - dx - dy) -- (dlprime - dx + dy), bar=Bars(barsize));
draw(downarrow, arrow=SharpArrow(), margin = arrowmargin);
draw(uparrow, arrow=SharpArrow(), margin = arrowmargin);
