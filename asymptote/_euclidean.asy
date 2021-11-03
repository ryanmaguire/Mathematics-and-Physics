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
 *                           Euclidean Geometry                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for two and three dimensional Euclidean geometry.    *
 ******************************************************************************
 *  Functions:                                                                *
 *      CircleIntersection (pair P0, real r0, pair P1, real r1):              *
 *          Given two points and two radii, finds the intersections of the    *
 *          circles centered about each with the respective radii. If the     *
 *          two circles are identical, or if the are no intersection points,  *
 *          an assert will raise an error and about the computation.          *
 *      EuclideanNorm2D (pair A):                                             *
 *          Compute the Euclidean norm of a point in the plane.               *
 *      FindCenter2D (pair A, pair B, pair C):                                *
 *          Find the center of three non-collinear points in the plane. If    *
 *          the points provided are collinear, the function will abort. This  *
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
 *      MidPoint2D (pair A, pair B):                                          *
 *          Compute the midpoint of two points in the plane A and B.          *
 *      PlaneToDisk (pair A):                                                 *
 *          Diffeomorphism from the plane to the unit disk, useful if one is  *
 *          doing hyperbolic geometry.                                        *
 *      RelAngle2D (pair O, pair X, pair Y):                                  *
 *          Compute the relative angle of the points X and Y with respect to  *
 *          the point O.                                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 17, 2020                                            *
 ******************************************************************************/

/******************************************************************************
 ******************************************************************************
 *                      Begin Two Dimensional Functions                       *
 ******************************************************************************
 ******************************************************************************/

/* Find midpoint given two points in the plane.                               */
pair MidPoint2D(pair A, pair B)
{
    /*  Declare necessary variables.                                          */
    real Ax, Ay, Bx, By, x, y;

    /*  Get the values from A and B.                                          */
    Ax = A.x;
    Ay = A.y;
    Bx = B.x;
    By = B.y;

    /*  Compute the midpoint of A and B using the midpoint formula and return.*/
    x = 0.5*(Ax + Bx);
    y = 0.5*(Ay + By);
    return (x, y);
}

/*  Compute the dot product of two 2-dimensional vectors.                     */
real DotProduct2D(pair A, pair B)
{
    /*  Declare necessary variables.                                          */
    real Ax, Ay, Bx, By, dot_prod;

    /*  Extract the values from the pairs A and B.                            */
    Ax = A.x;
    Ay = A.y;
    Bx = B.x;
    By = B.y;

    /*  Compute the Euclidean dot product and return.                         */
    dot_prod = Ax*Bx + Ay*By;
    return dot_prod;
}

/* Returns the angle between X and Y relative to the point O.                 */
real RelAngle2D(pair O, pair X, pair Y)
{
    /*  Declare necessary variables.                                          */
    pair P, Q;
    real dot_prod, abs_prod;

    /*  Compute the vectors from O to X and O to Y, respectively.             */
    P = X-O;
    Q = Y-O;

    /*  Compute the dot product of P and Q.                                   */
    dot_prod = DotProduct2D(P, Q);

    /*  Compute the product of the norms of P and Q as well.                  */
    abs_prod = EuclideanNorm2D(P)*EuclideanNorm2D(Q);

    /*  If abs_prod is 0, either P = O, or Q = O. In either case the angle is *
     *  undefined, so return Not-a-Number.                                    */
    if (abs_prod == 0.0)
        return nan;

    /*  Otherwise, use the fact that <a|b> = ||a|| ||b|| cos(theta), where    *
     *  <a|b> denotes the dot product of a and b, and ||a|| represents the    *
     *  Euclidean norm of a. Using this, we solve for theta.                  */
    else
        return acos(dot_prod/abs_prod);
}

/*  Convert rectangular coordinates to polar.                                 */
pair RectToPolar(pair P)
{
    /*  Declare necessary variables.                                          */
    real theta, r;
    pair O, X;

    /*  Declare points for the unit x vector and the origin.                  */
    O = (0.0, 0.0);
    X = (1.0, 0.0);

    /*  Compute the angle P makes with the x axis.                            */
    theta = RelAngle2D(O, X, P);

    /*  Compute the norm of P.                                                */
    r = EuclideanNorm2D(P);

    /*  The polar representation is just (r, theta), so return this.          */
    return (r, theta);
}

/*  Function for converting a polar coordinate to rectangular.                */
pair PolarToRect(pair P)
{
    /*  Declare necessary variables.                                          */
    real x, y, r, theta;

    /*  Extract the radius and theta from the polar point P.                  */
    r = P.x;
    theta = P.y;

    /*  Compute the x and y coordinates of P and return.                      */
    x = r*cos(theta);
    y = r*sin(theta);

    return (x, y);
}

/*  Function for determining if three points in the plane are collinear.      */
bool IsCollinear(pair A, pair B, pair C)
{
    /*  Declare necessary variables.                                          */
    real Ax, Ay, Bx, By, Cx, Cy, a, b, c, d, det;

    /*  Extract the values from the input pairs.                              */
    Ax = A.x;
    Ay = A.y;
    Bx = B.x;
    By = B.y;
    Cx = C.x;
    Cy = C.y;

    /*  To determine if A, B, and C are collinear, we need the vectors AB and *
     *  AC. Compute this using the extracted values.                          */
    a = Bx - Ax;
    b = Cx - Ax;
    c = By - Ay;
    d = Cy - Ay;

    /*  A, B, and C are collinear if and only if the determinant of the       *
     *  matrix formed by a, b, c, d is zero. Compute this.                    */
    det = a*d - b*c;

    if (det == 0.0)
        return true;
    else
        return false;
}

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

/*  Return a 2D vector orthogonal to the input.                               */
pair Orthogonal2D(pair V)
{
    /*  Declare necessary variables.                                          */
    real x, y;

    /*  The vector (-y, x) will be orthgonal to (x, y) since we have          *
     *  <(x, y)|(-y, x)> = x(-y) + yx = 0, so return this.                    */
    x = -V.y;
    y = V.x;
    return (x, y);
}

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

/* Given an array of pairs, draw a smooth curve through the points.           */
path PathFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0]..Pts[1];

    /* Loop through the array and construct the path.                         */
    for (i=2; i<ArSize; ++i)
        g = g..Pts[i];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g..cycle;

    return g;
}

/* Given an array of pairs, draw a polygonal curve through the point.         */
path PolyFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0]--Pts[1];

    /* Loop through the array and construct the path.                         */
    for (i=2; i<ArSize; ++i)
        g = g--Pts[i];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g--cycle;

    return g;
}

/* Given an array of pairs and an array of reals, draw a path between the     *
 * pairs with angle specified by the array of reals.                          */
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Set the start of the path.                                            */
    g = Pts[0]{dir(Dirs[0])}..Pts[1]{dir(Dirs[1])};

    /* Loop through the arrays and construct the path.                        */
    for (i=2; i<ArSize; ++i)
        g = g..Pts[i]{dir(Dirs[i])};

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g..cycle;

    return g;
}

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

/******************************************************************************
 ******************************************************************************
 *                     Begin Three Dimensional Functions                      *
 ******************************************************************************
 ******************************************************************************/

/*  Get a point on the line PQ with respect to the parameter t. This is the   *
 *  equation L(t) = (1-t)*P + t*Q;                                            */
triple LinePQ3D(real t, triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    triple X0, X1, out;

    /*  Compute the vector (1-t)P + tQ.                                       */
    X0 = ScaleThreeVector(1.0-t, P);
    X1 = ScaleThreeVector(t, Q);

    /*  Compute the output and return it.                                     */
    out = X0 + X1;
    return out;
}

/* Find midpoint given two points in space.                                   */
triple MidPoint3D(triple A, triple B)
{
    /*  Declare necessary variables.                                          */
    triple out;

    /*  Compute the midpoint using the midpoint formula.                      */
    out = ScaleThreeVector(0.5, A+B);
    return out;
}



/*  Given a non-zero vector, convert it to a unit vector.                     */
triple NormalizeVector3D(triple V)
{
    /*  Declare necessary variables.                                          */
    real norm;
    triple out;

    /*  Compute the norm of the vector V and check that it is non-zero.       */
    norm = EuclideanNorm3D(V);
    assert(norm>0.0);

    /*  Compute the normalized vector and return.                             */
    out = ScaleThreeVector(1.0/norm, V);
    return out;
}

/*  Compute the dot product of two 3-dimensional vectors.                     */
real DotProduct3D(triple A, triple B)
{
    /*  Declare necessary variables.                                          */
    real Ax, Ay, Az, Bx, By, Bz, dot_prod;

    /*  Extract values from the triples A and B.                              */
    Ax = A.x;
    Ay = A.y;
    Az = A.z;
    Bx = B.x;
    By = B.y;
    Bz = B.z;

    /*  Compute the dot product and return.                                   */
    dot_prod = Ax*Bx + Ay*By + Az*Bz;
    return dot_prod;
}

/* Returns the angle between X and Y relative to the point O.                 */
real RelAngle3D(triple O, triple X, triple Y)
{
    /*  Declare necessary variables.                                          */
    triple P, Q;
    real dot_prod, abs_prod;

    /*  Get the vectors from O to X and from O to Y, respectively.            */
    P = X-O;
    Q = Y-O;

    /*  Compute the dot product and the product of their norms.               */
    dot_prod = DotProduct3D(P, Q);
    abs_prod = EuclideanNorm3D(P)*EuclideanNorm3D(Q);

    /*  If abs_prod = 0, either O = X or O = Y. In either case, the angle is  *
     *  undefined, so return not-a-number.                                    */
    if (abs_prod == 0.0)
        return nan;

    /*  Otherwise use the standard angle formula and return.                  */
    else
        return acos(dot_prod/abs_prod);
}

/*  Return the angle between P and Q relative to the origin.                  */
real Angle3D(triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    triple O;
    real theta;

    /*  Set a variable for the origin.                                        */
    O = (0.0, 0.0, 0.0);

    theta = RelAngle3D(O, P, Q);
    return theta;
}

/*  Diffeomorphism from R^3 to the unit ball.                                 */
triple SpaceToBall(triple P)
{
    /*  Declare necessary variables.                                          */
    real norm, scale_factor;
    triple out;

    /*  If P is the origin, simply return it since the diffeormorphism fixes  *
     *  this point.                                                           */
    if (P==(0, 0))
        return P;

    /*  Otherwise, compute the length of P.                                   */
    norm = EuclideanNorm3D(P);

    /*  Compute the inverse of 2r / (1+||r||)(1-||r||).                       */
    scale_factor = (-1.0 + sqrt(4.0*norm*norm + 1.0))/(2.0*norm*norm);
    out = ScaleThreeVector(scale_factor, P);
    return out;
}


/*  Convert Cartesian to spherical coordinates.                               */
triple RectToSpherical(real x, real y, real z)
{
    /*  Declare necessary variables.                                          */
    real r, rho, phi, theta;

    /*  Compute the projection in the xy plane (rho), and r.                  */
    rho = sqrt(x*x + y*y);
    r   = sqrt(rho*rho + z*z);

    /*  Compute the azimuth and zenith angles, and return (r, phi, theta).    */
    phi = atan2(y, x);
    theta = pi-atan2(z, rho);
    return (r, phi, theta);
}

/*  Compute the dot product of two 3-dimensional vectors.                     */
real DotProduct3D(triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    real Px, Py, Pz, Qx, Qy, Qz, dot_prod;

    /*  Extract values from the triples P and Q.                              */
    Px = P.x;
    Py = P.y;
    Pz = P.z;
    Qx = Q.x;
    Qy = Q.y;
    Qz = Q.z;

    /*  Compute the Euclidean dot product and return.                         */
    dot_prod = Px*Qx + Py*Qy + Pz*Qz;
    return dot_prod;
}

/*  Compute the cross product of two triples P and Q.                         */
triple CrossProduct(triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    real Px, Py, Pz, Qx, Qy, Qz, x, y, z;

    /*  Extract the values from P and Q.                                      */
    Px = P.x;
    Py = P.y;
    Pz = P.z;
    Qx = Q.x;
    Qy = Q.y;
    Qz = Q.z;

    /*  Compute the components of the cross product.                          */
    x = Py*Qz - Pz*Qy;
    y = Pz*Qx - Px*Qz;
    z = Px*Qy - Py*Qx;
    return (x, y, z);
}

/*  Given a point Q, and a line in the form P + tV, computes the projection   *
 *  of Q onto this line. That is, the closest point on the line to Q.         */
triple ProjPointToLine(triple Q, triple P, triple V)
{
    /*  Declare necessary variables.                                          */
    real normV, scale;
    triple PQ, out;

    /*  Compute the norm of V. V needs to be non-zero to unambiguously define *
     *  a straight line, so we'll check for this.                             */
    normV = EuclideanNorm3D(V);
    assert(normV>0.0);

    /*  Get the vector pointing from P to Q.                                  */
    PQ = Q-P;

    /*  Compute the scale which is used for the projection of Q onto the line.*/
    scale = DotProduct3D(PQ, V)/(normV * normV);

    /*  Compute the x, y, and z values and return.                            */
    out = ScaleThreeVector(scale, V) + P;
    return out;
}

/*  Compute the equation of a great circle on a sphere of radius r given the  *
 *  vectors pointing in the P and Q directions.                               */
triple GreatCircle(real t, real r, triple P, triple Q)
{
    /*  Declare necessary variables.                                          */
    real u, v, tau, theta;
    triple e0, e1, e2, out;

    /*  Get three orthogonal vectors from the inputs P and Q.                 */
    e0 = P;
    e1 = CrossProduct(e0, Q);
    e2 = CrossProduct(e0, e1);

    /*  Normalize e0, e1, and e2. If P and Q lie on the same line through the *
     *  origin this step will fail and the computation will abort.            */
    e0 = NormalizeVector3D(e0);
    e1 = NormalizeVector3D(e1);
    e2 = NormalizeVector3D(e2);

    /*  Get the angle between P and Q and scale this by t.                    */
    theta = Angle3D(P, Q);
    tau = t*theta;

    /*  Values for parameterizing the great circle.                           */
    u = cos(tau);
    v = sin(tau);

    /*  Scale e0 and e2 by u and v, respectively.                             */
    e0 = ScaleThreeVector(u, e0);
    e2 = ScaleThreeVector(v, e2);

    /*  Compute the output point and return.                                  */
    out = ScaleThreeVector(r, e0+e2);
    return out;
}

triple SphericalCircle(real t, real r, triple P, triple Q)
{
    triple proj, projQ, cross, out;
    real cross_norm, radius, cos_t, sin_t, factor;

    /*  Normalize P and Q so that they are unit vectors.                      */
    P = NormalizeVector3D(P);
    Q = NormalizeVector3D(Q);

    /*  Now rescale them so that the lie on the sphere of radius r.           */
    P = ScaleThreeVector(r, P);
    Q = ScaleThreeVector(r, Q);

    /*  Project Q onto the line through the origin and P.                     */
    proj = ProjPointToLine(Q, (0,0,0), P);

    /*  Get the vector from the projection point to Q.                        */
    projQ = Q - proj;

    /*  The length of projQ is the radius of the circle we wish to compute,   *
     *  with projQ as the center. So compute this value.                      */
    radius = EuclideanNorm3D(projQ);

    /*  Compute the cross product of P and projQ.                             */
    cross = CrossProduct(P, projQ);
    cross_norm = EuclideanNorm3D(cross);

    /*  The norm of the cross product should not be zero, so check this.      */
    assert(cross_norm > 0.0);

    /*  Scale factor for the final circle.                                    */
    factor = radius/EuclideanNorm3D(cross);
    cross = ScaleThreeVector(factor, cross);

    /*  Precompute the sine and cosine of t.                                  */
    cos_t = cos(t);
    sin_t = sin(t);

    /*  And lastly, compute the point on the circle corresponding to t.       */
    out = proj+ScaleThreeVector(cos_t, projQ)+ScaleThreeVector(sin_t, cross);
    return out;
}

/*  Compute the stereographic projection of a 3-dimensional vector P. P does  *
 *  not need to lie on the unit sphere, and the stereographic projection will *
 *  occur with respect to the sphere of radius equal to the norm of P.        */
pair StereographicProjection(triple P)
{
    /*  Declare necessary values.                                             */
    real norm, denom;
    pair out;

    /*  Compute the norm of P to find the radius of the sphere it lies on.    */
    norm = EuclideanNorm3D(P);

    /*  The z component of P cannot be equal to the radius, so check this.    */
    assert(P.z != norm);

    /*  Compute the denominator of the stereographic projection.              */
    denom = norm / (norm - P.z);

    /*  Perform the computation and return.                                   */
    out = (P.x * denom, P.y * denom);
    return out;
}

/*  Compute the inverse stereographic projection of a point in the plane.     *
 *  computes the inverse projection with respect to the unit sphere. If you   *
 *  used StereographicProjection on a vector that did not have length 1, this *
 *  will not return it's inverse.                                             */
triple InverseStereographicProjection(pair P)
{
    /*  Declare necessary variables.                                          */
    real norm, denom, x, y;
    triple out;

    /*  Extract the values from the pair P.                                   */
    x = P.x;
    y = P.y;

    /*  Get the length of the vector P.                                       */
    norm = EuclideanNorm2D(P);

    /*  Compute the denominator for the inverse stereographic projection.     */
    denom = 1.0/(1.0 + norm*norm);

    /*  Compute the corresponding point on the unit sphere and return.        */
    out = (2.0*x, 2.0*y, -1.0 + x*x + y*y);
    out = ScaleThreeVector(denom, out);
    return out;
}
