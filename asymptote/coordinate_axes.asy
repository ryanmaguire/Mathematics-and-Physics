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
 *      Functions for drawing coordinate axes (x and y axes).                 *
 ******************************************************************************/

/*  Sharp tikz-style arrows found here.                                       */
access "custom_arrows.asy" as arrows;

/*  Default arrow head.                                                       */
arrowbar default_arrow = arrows.SharpArrow(5bp);

/*  Default axis pen. Adequate for most drawings.                             */
pen default_axis_pen = black + linewidth(0.8pt);

/******************************************************************************
 *  Function:                                                                 *
 *      DrawAndLabelCoordinateAxes                                            *
 *  Purpose:                                                                  *
 *      Draw the x and y axes and gives them labels.                          *
 *  Arguments:                                                                *
 *      start (pair):                                                         *
 *          The smallest values for the x and y axes. The x axis will begin   *
 *          at start.x and the y axis at start.y.                             *
 *      end (pair):                                                           *
 *          The largest values for the x and y axes. The x axis will end at   *
 *          end.x and the y axis ends at end.y.                               *
 *  Keywords:                                                                 *
 *      x_label_dir (pair):                                                   *
 *          The direction of the label for the x axis. Default is South.      *
 *      y_label_dir (pair):                                                   *
 *          The direction of the label for the y axis. Default is East.       *
 *      axis_pen (pen):                                                       *
 *          Pen used to draw the axis.                                        *
 *      arrow (arrowbar):                                                     *
 *          Arrow used to end the axes.                                       *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
void DrawAndLabelCoordinateAxes(pair start, pair end,
                                pair x_label_dir = S,
                                pair y_label_dir = E,
                                pen axis_pen = default_axis_pen,
                                arrowbar arrow = default_arrow)
{
    /*  Start and end of the x axis, given by the start and end parameters.   */
    pair left = (start.x, 0.0);
    pair right = (end.x, 0.0);

    /*  Similarly provide the start and end of the y axis.                    */
    pair bottom = (0.0, start.x);
    pair top = (0.0, end.x);

    /*  Create labels for the two axes.                                       */
    Label x_label = Label("$x$", position = 1.0);
    Label y_label = Label("$y$", position = 1.0);

    /*  Draw the coordinate access with labels.                               */
    draw(x_label, left -- right, x_label_dir, axis_pen, arrow);
    draw(y_label, bottom -- top, y_label_dir, axis_pen, arrow);
}
/*  End of DrawAndLabelCoordinateAxes.                                        */
