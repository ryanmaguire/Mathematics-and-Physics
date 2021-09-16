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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.2mm) + fontsize(8pt));

/*  Variable for indexing.                                                    */
int n;

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -9;
int grid_end = 9;

/*  Variables for drawing the grid, and drawing the axes.                     */
pair top, bottom, left, right;

/*  Length of the grid lines.                                                 */
real length = 10.2;

/*  Length of the axes.                                                       */
real axeslength = 10.5;

/*  Length of tick marks.                                                     */
real ticklength = 0.2;

/*  Size of the labels for the tick marks.                                    */
real tickfont = 5pt;

/*  Label for the tick marks.                                                 */
Label ticklabel;

/*  Thin grey pen used for the grid.                                          */
pen thingreyp = gray(0.8) + linewidth(0.3pt);

/*  Thicker black pen used for the axes.                                      */
pen axesp = black + linewidth(0.8pt);

/*  Black pen used for tick marks.                                            */
pen tickp = black + linewidth(0.2pt);

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Pen for labels.                                                           */
pen labelp = fontsize(6pt);

/*  Path for drawing square roots and parabolas.                              */
path g;

/*  Loop through and draw the lines for the grid.                             */
for (n = grid_start; n <= grid_end; ++n)
{
    /*  The grid consists of straight lines left-to-right and top-to-bottom.  *
     *  Compute the current set of lines to be drawn and draw them.           */
    bottom = (n, -length);
    top = (n, length);
    left = (-length, n);
    right = (length, n);

    draw(bottom -- top, thingreyp);
    draw(left -- right, thingreyp);

    /*  If n is zero, do not draw tick marks. The labels overlap with the     *
     *  axes lines and it isn't pretty.                                       */
    if (n == 0)
        continue;

    /*  Otherwise, draw in tick marks and labels.                             */
    else
    {
        ticklabel = Label("$"+string(n)+"$", position=1.0, fontsize(tickfont));
        draw(ticklabel, (n, ticklength) -- (n, -ticklength), tickp);
        draw(ticklabel, (ticklength, n) -- (-ticklength, n), tickp);
    }
}
/*  End of for-loop drawing the guide-grid.                                   */

/*  Draw the axes.                                                            */
bottom = (0.0, -axeslength);
top = (0.0, axeslength);
left = (-axeslength, 0.0);
right = (axeslength, 0.0);

draw(Label("$y$", position=1.0), bottom -- top, E, axesp, SharpArrows(arsize));
draw(Label("$x$", position=1.0), left -- right, S, axesp, SharpArrows(arsize));

/*  Draw the function |x - 3|.                                                */
draw((-7.0, 10.0) -- (3.0, 0.0) -- (10.0, 7.0), blue, SharpArrows(arsize));

/*  Several straight lines.                                                   */
draw((-3.0, -10.0) -- (-3.0, 10.0), green, SharpArrows(arsize));
draw((-10.0, 2.0) -- (10.0, 2.0), purple, SharpArrows(arsize));
draw((-7.5, 10.0) -- (10.0, -1.667), cyan, SharpArrows(arsize));
draw((-4.6666, -10.0) -- (8.6666, 10.0), pink, SharpArrows(arsize));
draw((0.0, -10.0) -- (10.0, 0.0), red, SharpArrows(arsize));

/*  Draw the parabola 2-x^2.                                                  */
g = (-3.4641, -10.0) .. (-3.0, -7.0) .. (-2.0, -2.0) .. (-1.0, 1.0) ..
    (0.0, 2.0) .. (1.0, 1.0) .. (2.0, -2.0) .. (3.0, -7.0) .. (3.4641, -10.0);
draw(g, orange, SharpArrows(arsize));

/*  Lastly, the function sqrt(2 - x).                                         */
g = (2.0, 0.0) .. (1.0, 1.0) .. (0.0, 1.4141) ..
    (-2.0, 2.0) .. (-7.0, 3.0) .. (-10.0, 3.4641);
draw(g, brown, SharpArrow(arsize));

/*  Label all of the functions.                                               */
label("$|x-3|$", (8.0, 3.7), blue + labelp);
label("$x=-3$", (-4.1, 4.5), green + labelp);
label("$y=2$", (8.0, 2.5), purple + labelp);
label("$y=-\frac{2}{3}x+5$", (3.0, 4.5), cyan + labelp);
label("$3x-2y=6$", (6.0, 8.4), pink + labelp);
label("$y=-x^{2}+2$", (4.2, -3.2), orange + labelp);
label("$y=x-10$", (7.2, -4.5), red + labelp);
label("$y=\sqrt{2-x}$", (-7.0, 3.5), brown + labelp);
