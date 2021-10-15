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

pair _Complex_One  = (1.0, 0.0);

pair ComplexFromPolar(real r, real theta)
{
    return (r*cos(theta), r*sin(theta));
}

pair ComplexScale(real r, pair z)
{
    return (r*z.x, r*z.y);
}

pair ComplexAdd(pair z, pair w)
{
    return (z.x + w.x, z.y + w.y);
}

pair ComplexSubtract(pair z, pair w)
{
    return (z.x-w.x, z.y-w.y);
}

pair ComplexMult(pair z, pair w)
{
    return (z.x*w.x - z.y*w.y, z.x*w.y + z.y*w.x);
}

pair ComplexConj(pair z)
{
    return (z.x, -z.y);
}

pair ComplexRcpr(pair z)
{
    real factor;

    factor = z.x*z.x + z.y*z.y;
    assert(factor > 0.0);

    factor = 1.0/factor;

    return ComplexScale(factor, ComplexConj(z));
}

pair ComplexDivide(pair z, pair w)
{
    return ComplexMult(z, ComplexRcpr(w));
}


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

/*  Diffeomorphism from the plane to the unit disk.                           */
pair PlaneToDisk(pair P)
{
    /*  Declare necessary variables.                                          */
    real norm, x_hat, y_hat, scale_factor, x, y;

    /*  The origin maps to the origin, so if P = (0, 0) simply return it.     */
    if (P==(0, 0))
        return P;

    /*  Otherwise, compute the length of P.                                   */
    norm = EuclideanNorm2D(P);

    /*  Extract the values from P.                                            */
    x = P.x;
    y = P.y;

    /*  Compute the inverse of 2x/(1-||x||)(1+||x||).                         */
    scale_factor = (-1.0 + sqrt(4.0*norm^2 + 1.0))/(2.0*norm);

    /*  Since P is not the origin, norm is non-zero so we can divide by it.   */
    x_hat = scale_factor * x / norm;
    y_hat = scale_factor * y / norm;

    return (x_hat, y_hat);
}

pair MobiusTransform(pair z, pair P)
{
    return ComplexDivide(
        ComplexSubtract(z, P),
        ComplexSubtract(_Complex_One, ComplexMult(ComplexConj(P), z))
    );
}

pair InverseMobiusTransform(pair z, pair P)
{
    return ComplexDivide(
        ComplexAdd(z, P),
        ComplexAdd(_Complex_One, ComplexMult(ComplexConj(P), z))
    );
}

pair HyperbolicPath(real t, pair P, pair Q)
{
    pair TransQ, InvPoint;

    TransQ = MobiusTransform(Q, P);
    InvPoint = ComplexScale(t, TransQ);

    return InverseMobiusTransform(InvPoint, P);
}

pair HyperbolicCircle(pair P, real radius, real theta)
{
    pair InvP;

    InvP = ComplexFromPolar(radius, theta);
    return InverseMobiusTransform(InvP, P);
}

pen thinp  = black + linewidth(0.3pt);

int samples = 100;

pair A, B;
pair P, Q;
pair P_TranQ;
pair C1, C2, C3;
pair D1, D2, D3;
pair CenterP, CenterQ;

pair[] Intersections;

real radius, r1, r2;

path g;

A = scale(2.0)*expi(3pi/4);
B = scale(1.5)*expi(pi/3);

P = PlaneToDisk(A);
Q = PlaneToDisk(B);

P_TranQ = MobiusTransform(P, Q);

radius = EuclideanNorm2D(P_TranQ);

C1 = HyperbolicCircle(P, radius, 0.0);
C2 = HyperbolicCircle(P, radius, 1.0);
C3 = HyperbolicCircle(P, radius, 2.0);
CenterP = FindCenter2D(C1, C2, C3);

D1 = HyperbolicCircle(Q, radius, 0.0);
D2 = HyperbolicCircle(Q, radius, 1.0);
D3 = HyperbolicCircle(Q, radius, 2.0);
CenterQ = FindCenter2D(D1, D2, D3);

r1 = EuclideanNorm2D(CenterP-Q);
r2 = EuclideanNorm2D(CenterQ-P);

Intersections = CircleIntersection(CenterP, r1, CenterQ, r2);

assert(!isnan(Intersections[0].x));

pair circle_P(real theta){return HyperbolicCircle(P, radius, theta);}
pair circle_Q(real theta){return HyperbolicCircle(Q, radius, theta);}
pair path_PQ(real t){return HyperbolicPath(t, P, Q);}
pair path_QI(real t){return HyperbolicPath(t, Q, Intersections[1]);}
pair path_IP(real t){return HyperbolicPath(t, Intersections[1], P);}

g = graph(path_PQ, 0, 1, samples, operator ..);
g = g--graph(path_QI, 0, 1, samples, operator ..);
g = g--graph(path_IP, 0, 1, samples, operator ..);
g = g--cycle;

draw(circle((0, 0), 1));
draw(graph(circle_P, 0, 2pi, samples, operator ..), thinp);
draw(graph(circle_Q, 0, 2pi, samples, operator ..), thinp);

filldraw(g, green, thinp);
filldraw(circle(P, 0.015), black);
filldraw(circle(Q, 0.015), black);
filldraw(circle(Intersections[1], 0.015), black, black+linewidth(0.2pt));
filldraw(circle((0, 0), 0.015), black, black);

label("$A$", P, scale(2.0)*NW);
label("$B$", Q, scale(2.0)*NE);
label("$C$", Intersections[1], scale(2.8)*N);
label("$O$", (0, 0), SW);

