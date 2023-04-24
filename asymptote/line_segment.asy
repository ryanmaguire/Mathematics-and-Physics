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
 *      Functions for plotting linear equations.                              *
 ******************************************************************************/

/*  Simple struct for working with lines in the plane.                        */
struct LineSegment {

    /*  A line segment is defined by two points, the start and end.           */
    pair start, end;

    /*  Constructor from two points in the plane.                             */
    static LineSegment line2D(pair A, pair B)
    {
        LineSegment line_segment = new LineSegment;
        line_segment.start = A;
        line_segment.end = B;
        return line_segment;
    }
}

/******************************************************************************
 *  Function:                                                                 *
 *      LineSegmentFromPosAndVel                                              *
 *  Purpose:                                                                  *
 *      Creates a line2D struct from two points in the plane.                 *
 *  Arguments:                                                                *
 *      P (pair):                                                             *
 *          A point in the plane.                                             *
 *      V (pair):                                                             *
 *          A velocity vector in the plane starting at P.                     *
 *  Outputs:                                                                  *
 *      line_segment (LineSegment):                                           *
 *          The line segment from P to P + V.                                 *
 ******************************************************************************/
LineSegment LineSegmentFromPosAndVel(pair P, pair V)
{
    /*  Declare a variable for the output.                                    */
    LineSegment line_segment;

    /*  The starting point is the point P.                                    */
    line_segment.start = P;

    /*  The end point is given by the velocity vector V.                      */
    line_segment.end = P + V;
    return line_segment;
}
/*  End of LineSegmentFromPosAndVel.                                          */
