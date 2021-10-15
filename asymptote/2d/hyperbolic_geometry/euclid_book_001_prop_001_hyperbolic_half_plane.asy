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

/*  Used for drawing parameterized curves.                                    */
import graph;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/* Find midpoint given two points in the plane.                               */
pair MidPoint2D(pair A, pair B)
{
    /*  Compute the midpoint of A and B using the midpoint formula and return.*/
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    return (x, y);
}
/*  End of MidPoint2D.                                                        */

/*  Return a 2D vector orthogonal to the input.                               */
pair Orthogonal2D(pair V)
{
    /*  The vector (-y, x) will be orthgonal to (x, y) since we have          *
     *  <(x, y)|(-y, x)> = x(-y) + yx = 0, so return this.                    */
    real x = -V.y;
    real y = V.x;
    return (x, y);
}
/*  End of Orthogonal2D.                                                      */

/* Returns the Euclidean norm of a 2-dimensional point.                       */
real EuclideanNorm2D(pair A)
{
    /*  Get the values from the input pair A.                                 */
    real x = A.x;
    real y = A.y;

    /*  Using Pythagoras, we simply compute sqrt(x^2 + y^2).                  */
    real norm = sqrt(x*x + y*y);
    return norm;
}
/*  End of EuclideanNorm2D.                                                   */

/*  Function for determining if three points in the plane are collinear.      */
bool IsCollinear(pair A, pair B, pair C)
{
    /*  To determine if A, B, and C are collinear, we need the vectors AB and *
     *  AC. Compute this using the extracted values.                          */
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

/*  Compute the intersection of two lines L0 and L1 in the format             *
 *  L0(t) = P0 + V0t, L1(t) = P1 + V1t.                                       */
pair LineIntersect2D(pair P0, pair V0, pair P1, pair V1)
{
    /*  Declare necessary variables.                                          */
    real a, b, c, d, diffx, diffy, t0, det, intersectx, intersecty, inva, invb;

    /*  We will solve this by finding the solution to t0*V0 - t1*V1 = P1 - P0 *
     *  and then return P0 + t0*V0. To do this we'll set this up as a matrix  *
     *  equation, so first we'll compute the matrix values.                   */
    a = V0.x;
    b = -V1.x;
    c = V0.y;
    d = -V1.y;

    /*  The solution exists if and only if the determinant is non-zero.       */
    det = a*d - b*c;
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
    return (intersectx, intersecty);
}
/*  End of LineIntersect2D.                                                   */

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
    dU = Orthogonal2D(B-A);

    V = MidPoint2D(A, C);
    dV = Orthogonal2D(C-A);

    center = LineIntersect2D(U, dU, V, dV);
    return center;
}
/*  End of FindCenter2D.                                                      */

/*  Compute the intersection of two circles given the centers and radii.      */
pair[] CircleIntersection(pair P0, real r0, pair P1, real r1)
{
    /*  Declare necessary variables.                                          */
    real dist, a, h, x0, y0, x1, y1;
    pair[] intersections;
    real P2x, P2y, factorx, factory;

    /*  r0 and r1 must be positive to define valid circles.                   */
    assert(r0 > 0.0);
    assert(r1 > 0.0);

    /*  Compute the distance from P0 to P1.                                   */
    dist = EuclideanNorm2D(P1-P0);

    /*  If dist > r0+r1, there is no solution.                                */
    assert(dist <= (r0 + r1));

    /*  Similarly if dist < |r1-r0|.                                          */
    assert(dist >= fabs(r1-r0));

    /*  If dist = 0 then the two circles have the same center. There are      *
     *  either no solutions or infinitely many.                               */
    assert(dist != 0.0);

    /*  We'll need to following for the computation. The above assertions     *
     *  ensure these values are well defined.                                 */
    a = (r0*r0 - r1*r1 + dist*dist) / (2.0*dist);
    h = sqrt(r0*r0 - a*a);

    /*  Compute the factor which determines the number of solutions.          */
    P2x = P0.x + (a/dist) * (P1-P0).x;
    P2y = P0.y + (a/dist) * (P1-P0).y;

    factorx = h*(P1.y - P0.y)/dist;
    factory = h*(P1.x - P0.x)/dist;

    /*  Compute the intersections and return.                                 */
    x0 = P2x + factorx;
    y0 = P2y - factory;
    x1 = P2x - factorx;
    y1 = P2y + factory;
    intersections[0] = (x0, y0);
    intersections[1] = (x1, y1);
    return intersections;
}
/*  End of CircleIntersection.                                                */

pair HyperbolicCirclePoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x1, y1, x0, y, m, dist;

    pair center;

    x1 = B.x;
    y1 = B.y;

    x0 = A.x;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x + c2)*(A.x + c2);

        m = -(x1 + c2)/sqrt(c1 - (x1+c2)*(x1+c2));

        y = y1 + m*(x0-x1);
        center = (x0, y);

        dist = EuclideanNorm2D(center - B);

        return center + scale(dist)*(cos(t), sin(t));
    }
    else
        return A;
}

pair HyperbolicPathPoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x, y;

    x = A.x*(1.0-t) + B.x*t;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x+ c2)*(A.x + c2);

        y = sqrt(c1 - (x+c2)*(x+c2));
    }
    else
        y = A.y*(1.0-t) + B.y*t;

    return (x, y);
}

pair HyperbolicLinePoincarePlane(real t, pair A, pair B)
{
    pair C;
    pair P, Q, O;

    O = (0.0, 0.0);

    real x, dist;

    P = MidPoint2D(A, B);

    if (A.x != B.x)
    {
        C = (A.y-B.y, B.x-A.x);

        x = P.x - C.x*P.y/C.y;
        Q = (x, 0.0);
        dist = EuclideanNorm2D(Q - A);

        return Q + scale(dist)*(cos(t), sin(t));
    }
    else
        return scale(1-t)*A + scale(t)*B;
}

pen thinp = black + linewidth(0.4pt);
real arsize = 5bp;
int samples = 100;

real xmin = -0.8;
real ymin = -0.8;
real xmax = 6.0;
real ymax = 6.0;

pair A = (1.5, 1.0);
pair B = (2.5, 2.0);

pair c1(real t){return HyperbolicCirclePoincarePlane(t, A, B);}
pair c2(real t){return HyperbolicCirclePoincarePlane(t, B, A);}

pair C1 = c1(0.0);
pair C2 = c1(1.0);
pair C3 = c1(2.0);
pair D1 = c2(0.0);
pair D2 = c2(1.0);
pair D3 = c2(2.0);

pair CenterA = FindCenter2D(C1, C2, C3);
pair CenterB = FindCenter2D(D1, D2, D3);

real r1 = EuclideanNorm2D(C1 - CenterA);
real r2 = EuclideanNorm2D(D1 - CenterB);
pair[] Intersections = CircleIntersection(CenterA, r1, CenterB, r2);
pair inter = Intersections[1]; 

pair c3(real t){return HyperbolicPathPoincarePlane(t, A, B);}
pair c4(real t){return HyperbolicPathPoincarePlane(t, B, inter);}
pair c5(real t){return HyperbolicPathPoincarePlane(t, inter, A);}

path g1 = graph(c3, 0, 1, 100, operator ..);
path g2 = graph(c4, 0, 1, 100, operator ..);
path g3 = graph(c5, 0, 1, 100, operator ..);
path g = g1 -- g2 -- g3 -- cycle;

draw(graph(c1, 0, 2pi, 100, operator ..), thinp);
draw(graph(c2, 0, 2pi, 100, operator ..), thinp);
filldraw(g, green, thinp);

draw((xmin, 0.0)--(xmax, 0.0), SharpArrow(arsize));
draw((0.0, xmin)--(0.0, ymax), SharpArrow(arsize));

filldraw(circle(A, 0.04), black);
filldraw(circle(B, 0.04), black);
filldraw(circle(inter, 0.04), black);

label("$A$", A, S);
label("$B$", B, E);
label("$C$", inter, W);

