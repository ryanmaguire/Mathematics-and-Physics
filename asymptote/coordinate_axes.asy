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
arrowbar default_arrow = arrows.SharpArrow(8bp);

/*  Default axis pen. Adequate for most drawings.                             */
pen default_axis_pen = black + linewidth(1.0pt) + fontsize(12pt);

/*  Default tick pen used to label and draw tick marks on the axes.           */
pen default_tick_pen = black + linewidth(0.4pt) + fontsize(12pt);

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
                                arrowbar arrow = default_arrow,
                                string x_string = "x",
                                string y_string = "y")
{
    /*  Start and end of the x axis, given by the start and end parameters.   */
    pair left = (start.x, 0.0);
    pair right = (end.x, 0.0);

    /*  Similarly provide the start and end of the y axis.                    */
    pair bottom = (0.0, start.y);
    pair top = (0.0, end.y);

    /*  Create labels for the two axes.                                       */
    Label x_label = Label("$" + x_string + "$", position = 1.0);
    Label y_label = Label("$" + y_string + "$", position = 1.0);

    /*  Draw the coordinate axes with labels.                                 */
    draw(x_label, left -- right, x_label_dir, axis_pen, arrow);
    draw(y_label, bottom -- top, y_label_dir, axis_pen, arrow);
}
/*  End of DrawAndLabelCoordinateAxes.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      DrawAndLabelSquareCoordinateAxes                                      *
 *  Purpose:                                                                  *
 *      Draw x and y axes with the same lengths.                              *
 *  Arguments:                                                                *
 *      axis_length (real):                                                   *
 *          The length of the x and y axes.                                   *
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
void DrawAndLabelSquareCoordinateAxes(real axis_length,
                                      pair x_label_dir = S,
                                      pair y_label_dir = E,
                                      pen axis_pen = default_axis_pen,
                                      arrowbar arrow = default_arrow,
                                      string x_string = "x",
                                      string y_string = "y")
{
    /*  Compute the start and end points of the axes.                         */
    pair start = (-axis_length, -axis_length);
    pair end = (axis_length, axis_length);

    /*  Pass these points to the main axes functions.                         */
    DrawAndLabelCoordinateAxes(start, end, x_label_dir = x_label_dir,
                               y_label_dir = y_label_dir,
                               axis_pen = axis_pen, arrow = arrow,
                               x_string = x_string, y_string = y_string);
}
/*  End of DrawAndLabelSquareCoordinateAxes.                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      DrawAndLabelRectangularCoordinateAxes                                 *
 *  Purpose:                                                                  *
 *      Draw x and y axes with the same lengths.                              *
 *  Arguments:                                                                *
 *      axis_start (real):                                                    *
 *          Starting value of the x and y axes.                               *
 *      axis_end (real):                                                      *
 *          Final value of the x and y axes.                                  *
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
void DrawAndLabelRectangularCoordinateAxes(real axis_start, real axis_end,
                                           pair x_label_dir = S,
                                           pair y_label_dir = E,
                                           pen axis_pen = default_axis_pen,
                                           arrowbar arrow = default_arrow,
                                           string x_string = "x",
                                           string y_string = "y")
{
    /*  Compute the start and end points of the axes.                         */
    pair start = (axis_start, axis_start);
    pair end = (axis_end, axis_end);

    /*  Pass these points to the main axes functions.                         */
    DrawAndLabelCoordinateAxes(start, end, x_label_dir = x_label_dir,
                               y_label_dir = y_label_dir,
                               axis_pen = axis_pen, arrow = arrow,
                               x_string = x_string, y_string = y_string);
}
/*  End of DrawAndLabelRectangularCoordinateAxes.                             */

/******************************************************************************
 *  Function:                                                                 *
 *      DrawAndLabelCoordinateAxesWithTickMarks                               *
 *  Purpose:                                                                  *
 *      Draw the x and y axes and gives them labels with tick marks.          *
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
void DrawAndLabelCoordinateAxesWithTickMarks(pair start, pair end,
                                             pair x_label_dir = S,
                                             pair y_label_dir = E,
                                             pen axis_pen = default_axis_pen,
                                             arrowbar arrow = default_arrow,
                                             real x_tick_length = 0.1,
                                             real y_tick_length = 0.1,
                                             pen tick_pen = default_tick_pen,
                                             bool label_ticks = true,
                                             int x_skip = 1,
                                             int y_skip = 1,
                                             string x_prefix = "",
                                             string x_suffix = "",
                                             string y_prefix = "",
                                             string y_suffix = "",
                                             string x_string = "x",
                                             string y_string = "y")
{
    /*  Variable for indexing over the tick mark.                             */
    int n;

    /*  Indices representing the start and end values for the tick marks.     */
    int start_x, end_x, start_y, end_y;

    /*  Draw the coordinate axes using the previous function.                 */
    DrawAndLabelCoordinateAxes(
        start, end, x_label_dir = x_label_dir,
        y_label_dir = y_label_dir, axis_pen = axis_pen,
        arrow = arrow, x_string = x_string, y_string = y_string
    );

    /*  Compute the starting indices for the tick marks in both axes.         */
    start_x = (int)(start.x);
    end_x = (int)(end.x);
    start_y = (int)(start.y);
    end_y = (int)(end.y);

    /*  Loop through and draw the lines for the x axes.                       */
    for (n = start_x; n <= end_x; n += x_skip)
    {
        /*  If n is zero, do not draw tick marks. The labels overlap with the *
         *  axes lines and it isn't pretty.                                   */
        if (n == 0)
            continue;

        /*  Otherwise, draw in tick marks and labels.                         */
        else
        {
            /*  End points for the tick marks.                                */
            pair top = (n, x_tick_length);
            pair bottom = (n, -x_tick_length);

            /*  Tick labels are optional. Check if the user requested them.   */
            if (label_ticks)
            {
                /*  A label for the tick mark.                                */
                string tick_str = x_prefix + string(n) + x_suffix;
                Label tick_label = Label("$" + tick_str + "$", position = 1.0);

                /*  Draw and label the tick marks.                            */
                draw(tick_label, top -- bottom, tick_pen);
            }

            /*  Otherwise draw the tick marks without labels.                 */
            else
                draw(top -- bottom, tick_pen);
        }
    }
    /*  End of for-loop drawing the x-tick-marks.                             */

    /*  Loop through and draw the lines for the y axes.                       */
    for (n = start_y; n <= end_y; n += y_skip)
    {
        /*  If n is zero, do not draw tick marks. The labels overlap with the *
         *  axes lines and it isn't pretty.                                   */
        if (n == 0)
            continue;

        /*  Otherwise, draw in tick marks and labels.                         */
        else
        {
            /*  End points for the tick marks.                                */
            pair left = (-y_tick_length, n);
            pair right = (y_tick_length, n);

            /*  Tick labels are optional. Check if the user requested them.   */
            if (label_ticks)
            {
                /*  A label for the tick mark.                                */
                string tick_str = y_prefix + string(n) + y_suffix;
                Label tick_label = Label("$" + tick_str + "$", position=1.0);

                /*  Draw and label the tick marks.                            */
                draw(tick_label, right -- left, tick_pen);
            }

            /*  Otherwise draw the tick marks without labels.                 */
            else
                draw(right -- left, tick_pen);
        }
    }
    /*  End of for-loop drawing the y-tick-marks.                             */
}
/*  End of DrawAndLabelCoordinateAxes.                                        */
