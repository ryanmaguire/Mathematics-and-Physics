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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************
 *                           Euclidean Geometry                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for planar geometry. In addition there are routines  *
 *      for drawing polygons and smooth curves through points.                *
 ******************************************************************************
 *  Functions:                                                                *
 *      CircleCircleIntersection (pair P0, real r0, pair P1, real r1):        *
 *          Given two points and two radii, finds the intersections of the    *
 *          circles centered about each with the respective radii. If the     *
 *          two circles are identical, or if the are no intersection points,  *
 *          it returns an array with a single element (nan, nan).             *
 *      EucNormTwo (pair A):                                                  *
 *          Compute the Euclidean norm of a point in the plane.               *
 *      FindCenterTwo (pair A, pair B, pair C):                               *
 *          Find the center of three non-colinear points in the plane. If the *
 *          points provided are colinear, the function will abort. This       *
 *          returns the point that is equidistant to A, B, and C.             *
 *      PathFromPoints (pair[] Pts, int ArSize, bool closed):                 *
 *          Given an array of points Pts and size ArSize, returns a smooth    *
 *          curve through them. If the bool closed is set, it returns a       *
 *          closed path.                                                      *
 *      PathFromPointsAndAngles (pair[] Pts, real[] Dirs,                     *
 *                               int ArSize, bool closed):                    *
 *          Similar to PathFromPoints but allows the user to specify the out  *
 *          angle at each point, rather than relying on the curve fitting     *
 *          algorithm to do that for you.                                     *
 *      PolyFromPoints (pair[] Pts, int ArSize, bool closed):                 *
 *          Same as PathFromPoints, but instead of a smooth curve it returns  *
 *          a polygonal curve.                                                *
 *      MidPointTwo (pair A, pair B):                                         *
 *          Compute the midpoint of two points in the plane A and B.          *
 *      PlaneToDisk (pair A):                                                 *
 *          Homeomorphism from the plane to the unit disk, useful if one is   *
 *          doing hyperbolic geometry.                                        *
 *      RelAngleTwo (pair O, pair X, pair Y):                                 *
 *          Compute the relative angle of the points X and Y with respect to  *
 *          the point O.                                                      *
 ******************************************************************************/

/* Find midpoint given two points in the plane.                               */
pair MidPointTwo(pair A, pair B)
{
    real x, y;
    x = 0.5*(A.x + B.x);
    y = 0.5*(A.y + B.y);

    return (x, y);
}

/* Returns the Euclidean norm of a 2-dimensional point.                       */
real EucNormTwo(pair A)
{
    real x, y;
    x = A.x;
    y = A.y;

    return sqrt(x*x + y*y);
}

/* Returns the angle between X and Y relative to the point O.                 */
real RelAngleTwo(pair O, pair X, pair Y)
{
    pair P = X-O;
    pair Q = Y-O;
    real dot_prod = P.x*Q.x+P.y*Q.y;
    real abs_prod = abs(P)*abs(Q);

    if (abs_prod == 0.0)
        return nan;
    else
        return acos(dot_prod/abs_prod);
}

/* Given three non-colinear points in the plane returns their center.         */
pair FindCenterTwo(pair A, pair B, pair C)
{
    pair U = MidPointTwo(A, B);
    pair V = MidPointTwo(B, C);

    real a =  (B.y-A.y)/(B.y-A.y+B.x-A.x);
    real b = -(B.x-A.x)/(B.y-A.y+B.x-A.x);
    real c =  (C.y-B.y)/(C.y-B.y+C.x-B.x);
    real d = -(C.x-B.x)/(C.y-B.y+C.x-B.x);
    real t0 = (c*(V.y-U.y)-d*(V.x-U.x))/(b*c-a*d);
    real t1 = (a*(V.y-U.y)-b*(V.x-U.x))/(b*c-a*d);
    return (U.x+t0*a, U.y+t0*b);
}

/* Given an array of pairs, draw a smooth curve through the points.           */
path PathFromPoints(pair[] Pts, int ArSize, bool closed)
{
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]..Pts[1];

    // Loop through the array and construct the path.
    for (i=2; i<ArSize; ++i) g = g..Pts[i];

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g..cycle;
    return g;
}

/* Given an array of pairs, draw a polygonal curve through the point.         */
path PolyFromPoints(pair[] Pts, int ArSize, bool closed)
{
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]--Pts[1];

    // Loop through the array and construct the path.
    for (i=2; i<ArSize; ++i) g = g--Pts[i];

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g--cycle;
    return g;
}

/* Given an array of pairs and an array of reals, draw a path between the     *
 * pairs with angle specified by the array of reals.                          */
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, int ArSize, bool closed)
{
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]{dir(Dirs[0])}..Pts[1]{dir(Dirs[1])};

    // Loop through the arrays and construct the path.
    for (i=2; i<ArSize; ++i) g = g..Pts[i]{dir(Dirs[i])};

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g..cycle;
    return g;
}

pair PlaneToDisk(pair P)
{
    if (P==(0, 0))
        return P;

    real norm = EucNormTwo(P);
    real x_hat = P.x/norm;
    real y_hat = P.y/norm;
    real scale_factor = (-1.0 + sqrt(4.0*norm^2 + 1.0))/(2.0*norm);
    return (scale_factor*x_hat, scale_factor*y_hat);
}

pair[] CircleCircleIntersection(pair P0, real r0, pair P1, real r1)
{
    assert(r0 > 0.0);
    assert(r1 > 0.0);

    real dist = EucNormTwo(P1-P0);

    pair[] intersections = {(nan, nan)};

    if ((dist > (r0 + r1)) || dist < fabs(r1-r0) || (dist == 0.0))
        return intersections;

    real a = (r0^2 - r1^2 + dist^2) / (2.0*dist);
    real h = sqrt(r0^2 - a^2);

    real x1, y1, x2, y2;

    pair P2 = P0 + scale(a/dist) * (P1-P0);

    x1 = P2.x + h*(P1.y - P0.y)/dist;
    y1 = P2.y - h*(P1.x - P0.x)/dist;

    x2 = P2.x - h*(P1.y - P0.y)/dist;
    y2 = P2.y + h*(P1.x - P0.x)/dist;

    pair[] intersections = {(x1, y1), (x2, y2)};

    return intersections;
}

// Find midpoint given two points in the plane.
triple MidPointThree(triple A, triple B)
{
    return scale(0.5, 0.5, 0.5)*(A+B);
}

// Returns the Euclidean norm of a 2-dimensional point.
real EucNormThree(triple A)
{
    return sqrt(A.x^2+A.y^2+A.z^2);
}

real DotProductThree(triple A, triple B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

// Returns the angle between X and Y relative to the point O.
real RelAngleTwo(triple O, triple X, triple Y)
{
    triple P = X-O;
    triple Q = Y-O;
    real dot_prod = DotProductThree(P, Q);
    real abs_prod = EucNormThree(P)*EucNormThree(Q);
    return acos(dot_prod/abs_prod);
}

triple SpaceToBall(triple P)
{
    if (P==(0, 0))
        return P;

    real norm = EucNormThree(P);
    real x_hat = P.x/norm;
    real y_hat = P.y/norm;
    real z_hat = P.z/norm;
    real scale_factor = (-1.0 + sqrt(4.0*norm^2 + 1.0))/(2.0*norm);
    return (scale_factor*x_hat, scale_factor*y_hat, scale_factor*z_hat);
}

triple SphericalToRect(real phi, real theta)
{
    return (cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta));
}

pair RectToSpherical(real x, real y, real z)
{
    real rho_norm  = sqrt(x*x + y*y);
    real phi = atan2(y, x);
    real theta = pi - atan2(z, rho_norm);
    return (phi, theta);
}

real DotProductThree(triple p, triple q)
{
    return p.x*q.x + p.y*q.y + p.z*q.z;
}

triple CrossProduct(triple p, triple q)
{
    return (p.y*q.z - p.z*q.y, p.z*q.x - p.x*q.z, p.x*q.y - p.y*q.x);
}

triple proj_point_to_line(triple q, triple p, triple v)
{
    real norm_v = EucNormThree(v);
    assert(norm_v>0);

    triple pq = q-p;
    real scale = DotProductThree(pq, v)/(norm_v * norm_v);

    return scale(scale, scale, scale)*v + p;
}


triple great_circle(real t, triple P, triple Q)
{
    triple e1 = P;
    triple e2 = CrossProduct(e1, Q);
    triple e3 = CrossProduct(e1, e2);
    e1 = e1/EucNormThree(e1);
    e3 = e3/EucNormThree(e3);

    real tau, theta;

    theta = asin(DotProductThree(P, Q)/(EucNormThree(P)*EucNormThree(Q)));
    tau = t*theta;

    real u = cos(tau);
    real v = sin(tau);

    return scale(u, u, u)*e1 + scale(v, v, v)*e3;
}

triple spherical_circle(real t, triple P, triple Q)
{
    triple proj = proj_point_to_line(Q, (0,0,0), P);
    triple proj_to_Q = Q - proj;
    real radius = EucNormThree(proj_to_Q);

    triple cross = CrossProduct(P, proj_to_Q);
    assert(EucNormThree(cross) > 0.0);
    real factor = radius/EucNormThree(cross);
    cross = scale(factor, factor, factor)*cross;

    real cos_t = cos(t);
    real sin_t = sin(t);

    return proj+scale(cos_t, cos_t, cos_t)*proj_to_Q +
                scale(sin_t, sin_t, sin_t)*cross;
}

pair StereographicProjection(triple P)
{
    assert(P.z != 1.0);
    real denom = 1.0 / (1.0 - P.z);

    return (P.x * denom, P.y * denom);
}

triple InverseStereographicProjection(pair P)
{
    real denom = 1.0/(1.0 + P.x^2 + P.y^2);
    return (2.0*P.x*denom, 2.0*P.y*denom, (-1.0+P.x^2+P.y^2)*denom);
}
