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
 *      Draws a triangle inside a circle. The triangle is defined as the      *
 *      convex hull of three given points. The circle is also described by    *
 *      these three (non-colinear) points.                                    *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  The opacity will not render correctly for EPS format, so use PDF.         */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  A thinner pen for drawing.                                                */
pen thinp = black + linewidth(0.3pt);

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Pen for drawing axes.                                                     */
pen axesp = black + linewidth(0.7pt) + fontsize(9pt);

/*  Size of dots used for labels.                                             */
real rDot = 0.015;

/*  Filler for the triangles.                                                 */
pen fillp = red + opacity(0.5);

/*  Given an array of pairs, draw a polygonal curve through the points.       */
path PolyFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int n;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize > 1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0] -- Pts[1];

    /*  Loop through the array and construct the path.                        */
    for (n = 2; n < ArSize; ++n)
        g = g -- Pts[n];

    /*  If the closed Boolean is true, close the path into a cycle.           */
    if (closed)
        g = g -- cycle;

    return g;
}
/*  End of PolyFromPoints.                                                    */

/*  Compute the intersection of two lines L0 and L1 in the format             *
 *  L0(t) = P0 + V0t, L1(t) = P1 + V1t.                                       */
pair LineIntersect2D(pair P0, pair V0, pair P1, pair V1)
{
    /*  Declare necessary variables.                                          */
    real diffx, diffy, t0, det, intersectx, intersecty, inva, invb;
    pair out;

    /*  We will solve this by finding the solution to t0*V0 - t1*V1 = P1 - P0 *
     *  and then return P0 + t0*V0. To do this we'll set this up as a matrix  *
     *  equation, so first we'll compute the matrix values.                   */
    real a = V0.x;
    real b = -V1.x;
    real c = V0.y;
    real d = -V1.y;

    /*  The solution exists if and only if the determinant is non-zero.       */
    real det = a*d - b*c;
    assert(det != 0.0);

    /*  If the determinant is non-zero, compute the upper row of the inverse  *
     *  matrix. We will not need the bottom row.                              */
    inva = d/det;
    invb = -b/det;

    /*  The right-side of the equation is P1 - P0, so compute this.           */
    diffx = P1.x - P0.x;
    diffy = P1.y - P0.y;

    /*  Solve for t0.                                                         */
    t0 = inva*diffx + invb*diffy;

    /*  Compute the intersection using t0 and return.                         */
    intersectx = P0.x + t0*V0.x;
    intersecty = P0.y + t0*V0.y;
    out = (intersectx, intersecty);
    return out;
}
/*  End of LineIntersect2D.                                                   */

/*  Function for computing the Euclidean norm of a 2D vector.                 */
real EuclideanNorm2D(pair V)
{
    /*  Use the Pythagorean formula to compute the norm.                      */
    return sqrt(V.x*V.x + V.y*V.y);
}
/*  End of EuclideanNorm2D.                                                   */

/*  Return a 2D vector orthogonal to the input.                               */
pair Orthogonal2D(pair V)
{
    /*  The vector (-y, x) will be orthgonal to (x, y) since we have          *
     *  <(x, y)|(-y, x)> = x(-y) + yx = 0, so return this.                    */
    pair orth = (-V.y, V.x);
    return orth;
}
/*  End of Orthogonal2D.                                                      */

/*  Function for determining if three points in the plane are collinear.      */
bool IsCollinear(pair A, pair B, pair C)
{
    /*  To determine if A, B, and C are collinear, we need the vectors AB and *
     *  AC. Compute these.                                                    */
    real a = B.x - A.x;
    real b = C.x - A.x;
    real c = B.y - A.y;
    real d = C.y - A.y;

    /*  A, B, and C are collinear if and only if the determinant of the       *
     *  matrix formed by a, b, c, d is zero. Compute this.                    */
    real det = a*d - b*c;

    if (det == 0.0)
        return true;
    else
        return false;
}
/*  End of IsCollinear.                                                       */

/* Find midpoint given two points in the plane.                               */
pair MidPoint2D(pair A, pair B)
{
    /*  Compute the midpoint of A and B using the midpoint formula and return.*/
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    pair out = (x, y);
    return out;
}
/*  End of MidPoint2D.                                                        */

/* Given three non-collinear points in the plane, returns their center.       */
pair FindCenter2D(pair A, pair B, pair C)
{
    /*  Declare necessary variables.                                          */
    pair U, V, dU, dV, center;

    /*  If A, B, and C are collinear there is no solution.                    */
    assert(!IsCollinear(A, B, C));

    /*  Compute the bisectors of AB and AC and find there intersection. This  *
     *  point is the center of A, B, and C.                                   */
    U = MidPoint2D(A, B);
    dU = Orthogonal2D(B - A);

    V = MidPoint2D(A, C);
    dV = Orthogonal2D(C - A);

    center = LineIntersect2D(U, dU, V, dV);
    return center;
}
/*  End of FindCenter2D.                                                      */

/*  Lengths of the axes.                                                      */
real min = 0.2;
real max = 1.2;

/*  Draw axes.                                                                */
draw((-max, 0.0) -- (min, 0.0), axesp);
draw((0.0, -min) -- (0.0, max), axesp);

/*  The three points on the circle we care about.                             */
pair[] TriPts = {(-1.0, 0.0), (0.0, 1.0), (0.1, 0.0)};
int TriN = 3;

/*  Obtain the center of the circle these points define and compute radius.   */
pair P = FindCenter2D(TriPts[0], TriPts[1], TriPts[2]);
real R = EuclideanNorm2D(P - TriPts[0]);

/*  Draw and fill in the triangle.                                            */
filldraw(PolyFromPoints(TriPts, TriN, true), fillp, defaultpen);

/*  Draw the circle and mark the three points.                                */
draw(circle(P, R));
filldraw(circle(TriPts[0], rDot), black);
filldraw(circle(TriPts[1], rDot), black);
filldraw(circle(TriPts[2], rDot), black);

/*  Label points on the x and y axes.                                         */
label("$-1$", (-1.02, -0.1));
label("$1$",  (0.10, 1.0));
