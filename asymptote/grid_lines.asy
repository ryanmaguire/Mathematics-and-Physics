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
 *      Functions for drawing grid lines.                                     *
 ******************************************************************************/

/*  Default pens used in grid functions.                                      */
pen default_grid_pen = gray(0.8) + linewidth(0.3pt);
pen default_tick_pen = black + linewidth(0.2pt) + fontsize(12pt);

/******************************************************************************
 *  Function:                                                                 *
 *      DrawGridLines                                                         *
 *  Purpose:                                                                  *
 *      Adds grid lines to a drawing. Useful for plotting real functions.     *
 *  Arguments:                                                                *
 *      grid_start (int):                                                     *
 *          The left-most and bottom-most integer that receives a grid line.  *
 *      grid_end (int):                                                       *
 *          The right-most and top-most integer that receives a grid line.    *
 *      grid_length (real):                                                   *
 *          The length of the grid lines.                                     *
 *      grid_pen (pen):                                                       *
 *          The pen used to draw the grid lines.                              *
 *  Keywords:                                                                 *
 *      grid_skip (int):                                                      *
 *          The number of integers skipped between grid lines. Default is 1.  *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
void DrawGridLines(int grid_start, int grid_end, real grid_length,
                   pen grid_pen = default_grid_pen, int grid_skip = 1)
{
    /*  Variable for indexing over the grid lines.                            */
    int n;

    /*  Loop through and draw the lines for the grid.                         */
    for (n = grid_start; n <= grid_end; n += grid_skip)
    {
        /*  The grid consists of straight lines left-to-right and             *
         *  top-to-bottom. Compute the current set of lines to be drawn.      */
        pair bottom = (n, -grid_length);
        pair top = (n, grid_length);
        pair left = (-grid_length, n);
        pair right = (grid_length, n);

        /*  Draw the current set of grid lines.                               */
        draw(bottom -- top, grid_pen);
        draw(left -- right, grid_pen);
    }
    /*  End of for-loop drawing the guide-grid.                               */
}
/*  End of DrawGridLines.                                                     */

/******************************************************************************
 *  Function:                                                                 *
 *      DrawGridLinesWithTickMarks                                            *
 *  Purpose:                                                                  *
 *      Adds grid lines to a drawing with tick mark labels.                   *
 *  Arguments:                                                                *
 *      grid_start (int):                                                     *
 *          The left-most and bottom-most integer that receives a grid line.  *
 *      grid_end (int):                                                       *
 *          The right-most and top-most integer that receives a grid line.    *
 *      grid_length (real):                                                   *
 *          The length of the grid lines.                                     *
 *  Keywords:                                                                 *
 *      tick_length (real):                                                   *
 *          The length of the tick marks. Default is 0.2.                     *
 *      grid_pen (pen):                                                       *
 *          The pen used to draw the grid lines.                              *
 *      tick_pen (pen):                                                       *
 *          The pen used to draw tick marks.                                  *
 *      label_ticks (bool):                                                   *
 *          Boolean for adding labels to tick marks. Default is true.         *
 *      grid_skip (int):                                                      *
 *          The number of integers skipped between grid lines. Default is 1.  *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
void DrawGridLinesWithTickMarks(int grid_start, int grid_end,
                                real grid_length, real tick_length = 0.1,
                                pen grid_pen = default_grid_pen,
                                pen tick_pen = default_tick_pen,
                                bool label_ticks = true, int grid_skip = 1)
{
    /*  Variable for indexing over the grid lines.                            */
    int n;

    /*  Loop through and draw the lines for the grid.                         */
    for (n = grid_start; n <= grid_end; n += grid_skip)
    {
        /*  The grid consists of straight lines left-to-right and             *
         *  top-to-bottom. Compute the current set of lines to be drawn.      */
        pair bottom = (n, -grid_length);
        pair top = (n, grid_length);
        pair left = (-grid_length, n);
        pair right = (grid_length, n);

        /*  Draw the current set of grid lines.                               */
        draw(bottom -- top, grid_pen);
        draw(left -- right, grid_pen);

        /*  If n is zero, do not draw tick marks. The labels overlap with the *
         *  axes lines and it isn't pretty.                                   */
        if (n == 0)
            continue;

        /*  Otherwise, draw in tick marks and labels.                         */
        else
        {
            /*  End points for the tick marks.                                */
            pair left = (-tick_length, n);
            pair right = (tick_length, n);
            pair top = (n, tick_length);
            pair bottom = (n, -tick_length);

            /*  Tick labels are optional. Check if the user requested them.   */
            if (label_ticks)
            {
                /*  A label for the tick mark.                                */
                Label tick_label = Label("$"+string(n)+"$", position=1.0);

                /*  Draw and label the tick marks.                            */
                draw(tick_label, top -- bottom, tick_pen);
                draw(tick_label, right -- left, tick_pen);
            }

            /*  Otherwise draw the tick marks without labels.                 */
            else
            {
                draw(top -- bottom, tick_pen);
                draw(right -- left, tick_pen);
            }
        }
    }
    /*  End of for-loop drawing the guide-grid.                               */
}
/*  End of DrawGridLinesWithTickMarks.                                        */
