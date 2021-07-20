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

/*  Think grey pen used for the grid.                                         */
pen thingreyp = gray(0.8) + linewidth(0.3pt);

/*  Thicker black pen used for the axes.                                      */
pen axesp = black + linewidth(0.8pt);

/*  Black pen used for tick marks.                                            */
pen tickp = black + linewidth(0.2pt);

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

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
