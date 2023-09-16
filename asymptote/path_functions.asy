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

/* Given an array of pairs, draw a smooth curve through the points.           */
path PathFromPoints(pair[] Pts, bool closed = false)
{
    /*  Declare necessary variables.                                          */
    path g;
    int n;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(Pts.length > 1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0] .. Pts[1];

    /* Loop through the array and construct the path.                         */
    for (n = 2; n < Pts.length; ++n)
        g = g .. Pts[n];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g .. cycle;

    return g;
}
/*  End of PathFromPoints.                                                    */

/* Given an array of pairs, draw a polygonal curve through the point.         */
path PolyFromPoints(pair[] Pts, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int n;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(Pts.length > 1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0] -- Pts[1];

    /* Loop through the array and construct the path.                         */
    for (n = 2; n < Pts.length; ++n)
        g = g -- Pts[n];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g -- cycle;

    return g;
}
/*  End of PolyFromPoints.                                                    */

/* Given an array of pairs and an array of reals, draw a path between the     *
 * pairs with angle specified by the array of reals.                          */
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int n;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(Pts.length > 1);

    /*  The point and direction arrays must be the same size.                 */
    assert(Pts.length == Dirs.length);

    /*  Set the start of the path.                                            */
    g = Pts[0]{dir(Dirs[0])} .. Pts[1]{dir(Dirs[1])};

    /* Loop through the arrays and construct the path.                        */
    for (n = 2; n < Pts.length; ++n)
        g = g .. Pts[n]{dir(Dirs[n])};

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g .. cycle;

    return g;
}
/*  End of PathFromPointsAndAngles.                                           */
