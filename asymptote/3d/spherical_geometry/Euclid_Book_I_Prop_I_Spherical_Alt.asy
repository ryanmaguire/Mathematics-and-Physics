// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;
import three;
settings.render=8;
settings.outformat="pdf";

currentprojection=perspective(
    camera = (100, 50, 20),
    up = (0, 0, 1),
    target = (0,  0,  0),
    zoom = 0.85
);

/* Find midpoint given two points in the plane.                               */
pair MidPoint2D(pair A, pair B)
{
    /*  Compute the midpoint of A and B using the midpoint formula and return.*/
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    return (x, y);
}

/*  Scale a three dimensional vector by a real number.                        */
triple ScaleThreeVector(real r, triple V)
{
    /*  Simply multiply the components and return.                            */
    return (r*V.x, r*V.y, r*V.z);
}

/*  Convert spherical coordinates to rectangular. Note, this uses the         *
 *  physicists convention and NOT the mathematicians (old habbits die hard).  *
 *  r is the distance to the origin, phi is the azimuth angle (the angle in   *
 *  the xy plane), and theta is the zenith angle (the angle made with z).     */
triple SphericalToRect(real r, real phi, real theta)
{
    /*  Pre-compute the trigonometric factors to save excess computations.    */
    real cos_theta = cos(theta);
    real sin_theta = sin(theta);
    real cos_phi = cos(phi);
    real sin_phi = sin(phi);

    /*  Compute the x, y, and z coordinates and return.                       */
    real x = r*cos_phi*sin_theta;
    real y = r*sin_phi*sin_theta;
    real z = r*cos_theta;
    return (x, y, z);
}

/* Returns the Euclidean norm of a 3-dimensional point.                       */
real EuclideanNorm3D(triple A)
{
    /*  Use Pythagoras to compute the length of A.                            */
    return sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
}

/* Returns the Euclidean norm of a 2-dimensional point.                       */
real EuclideanNorm2D(pair A)
{
    /*  Use Pythagoras to compute the length of A.                            */
    return sqrt(A.x*A.x + A.y*A.y);
}

/*  Compute the dot product of two 3-dimensional vectors.                     */
real DotProduct3D(triple A, triple B)
{
    /*  Compute the dot product and return.                                   */
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

/*  Given a non-zero vector, convert it to a unit vector.                     */
triple NormalizeVector3D(triple V)
{
    /*  Compute the norm of the vector V and check that it is non-zero.       */
    real norm = EuclideanNorm3D(V);
    assert(norm>0.0);

    /*  Compute the normalized vector and return.                             */
    return ScaleThreeVector(1.0/norm, V);
}

/*  Compute the cross product of two triples P and Q.                         */
triple CrossProduct(triple P, triple Q)
{
    /*  Compute the components of the cross product.                          */
    real x = P.y*Q.z - P.z*Q.y;
    real y = P.z*Q.x - P.x*Q.z;
    real z = P.x*Q.y - P.y*Q.x;
    return (x, y, z);
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
    return RelAngle3D((0.0, 0.0, 0.0), P, Q);
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
    /*  The vector (-y, x) will be orthgonal to (x, y) since we have          *
     *  <(x, y)|(-y, x)> = x(-y) + yx = 0, so return this.                    */
    return (-V.y, V.x);
}

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

// Pen for drawing.
pen dpen = black+linewidth(1.0pt);
pen bpen = blue+linewidth(0.5pt);
pen rpen = red+linewidth(0.5pt);

// Size of the output figure.
size(128);

triple A = SphericalToRect(1.0, 0.0, pi/2);
triple B = SphericalToRect(1.0, pi/4, pi/2);

triple c1(real t){return SphericalCircle(t, 1.0, A, B);}
triple c2(real t){return SphericalCircle(t, 1.0, B, A);}

radialshade(
    project(
        circle((0,0,0), 1, currentprojection.camera-currentprojection.target)
    ),
    rgb(0.8,0.8,0.8), project(O), 1.0,
    rgb(0.9,0.9,0.9), project(O), 0.2
);

guide3 q1 = graph(c1, -pi, pi, 100, operator ..);
draw(project(q1));
guide3 q1 = graph(c2, -pi, pi, 100, operator ..);
draw(project(q1));

pair C1, C2, C3, D1, D2, D3;

C1 = StereographicProjection(c1(0.0));
C2 = StereographicProjection(c1(1.0));
C3 = StereographicProjection(c1(2.0));
D1 = StereographicProjection(c2(0.0));
D2 = StereographicProjection(c2(1.0));
D3 = StereographicProjection(c2(2.0));

pair CenterA, CenterB;

CenterA = FindCenter2D(C1, C2, C3);
CenterB = FindCenter2D(D1, D2, D3);

real r1 = EuclideanNorm2D(CenterA - C1);
real r2 = EuclideanNorm2D(CenterB - D1);

pair[] Intersections = CircleIntersection(CenterA, r1, CenterB, r2);

if (!isnan(Intersections[0].x))
{
    triple SphereIntersection;
    SphereIntersection = InverseStereographicProjection(Intersections[0]);

    triple c3(real t){return GreatCircle(t, 1.0, A, B);}
    triple c4(real t){return GreatCircle(t, 1.0, B, SphereIntersection);}
    triple c5(real t){return GreatCircle(t, 1.0, SphereIntersection, A);}

    guide3 q1=graph(c3, 0, -1, 100, operator ..);
    guide3 q2=graph(c4, 0, -1, 100, operator ..);
    guide3 q3=graph(c5, 0, -1, 100, operator ..);
    guide3 g=q1--q2--q3--cycle;
    filldraw(project(g), green);

    dot(project(A));
    dot(project(B));
    dot(project(SphereIntersection));

    label("$A$", project(A), SW);
    label("$B$", project(B), SE);
    label("$C$", project(SphereIntersection), N);

}

