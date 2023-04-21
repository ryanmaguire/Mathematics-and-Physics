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
 *      Creates paths from functions.                                         *
 ******************************************************************************/

/*  Function for producing a path from a real-valued function.                */
path PathFromFunction(real func(real), real a, real b, int n_samples)
{
    /*  Declare necessary variables.                                          */
    path g;
    real dx, x, start, end;

    /*  There must be at least two samples to create a path.                  */
    assert(n_samples >= 2);

    /*  The end points can not be equal.                                      */
    assert(a != b);

    /*  Set the starting point. This is whichever value is smaller.           */
    if (a < b)
    {
        start = a;
        end = b;
    }
    else
    {
        start = b;
        end = a;
    }

    /*  The samples are uniformly spaced throughout the interval (start, end).*/
    dx = (end - start) / (real)n_samples;
    x = start;

    /*  Initialize the path to the starting point.                            */
    g = (x, func(x));
    x += dx;

    /*  Loop over the samples and append them to the path.                    */
    while (x < end)
    {
        g = g .. (x, func(x));
        x += dx;
    }

    /*  Add the end point to the path.                                        */
    g = g .. (end, func(end));

    /*  If a < b, then start = a and end = b. Return as normal.               */
    if (a < b)
        return g;

    /*  Otherwise, start = b and end = a. Reverse the path and return.        */
    else
        return reverse(g);
}
/*  End of PathFromFunction.                                                  */
