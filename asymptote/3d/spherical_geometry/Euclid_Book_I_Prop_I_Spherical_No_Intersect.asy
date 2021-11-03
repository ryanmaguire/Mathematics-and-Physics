// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;
import three;
settings.render = 8;
settings.outformat = "pdf";

currentprojection = perspective(
    camera = (100, 50, 20),
    up = (0, 0, 1),
    target = (0,  0,  0),
    zoom = 0.85
);

/* Returns the Euclidean norm of a 3-dimensional point.                       */
real EuclideanNorm3D(triple A)
{
    /*  Use Pythagoras to compute the length of A.                            */
    return sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
}

/*  Compute the dot product of two 3-dimensional vectors.                     */
real DotProduct3D(triple A, triple B)
{
    /*  Compute the dot product and return.                                   */
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

/*  Scale a three dimensional vector by a real number.                        */
triple ScaleThreeVector(real r, triple V)
{
    /*  Simply multiply the components and return.                            */
    return (r*V.x, r*V.y, r*V.z);
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
triple B = SphericalToRect(1.0, 3pi/4, pi/2);

triple c1(real t){return SphericalCircle(t, 1.0, A, B);}
triple c2(real t){return SphericalCircle(t, 1.0, B, A);}

// Radius of the dot and pipes.
real dotR = 0.08;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.5),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.5),
                        specularpen=gray(0.5));

draw(unitsphere, surfacepen=blob, render(merge=true));

surface s = scale(dotR, dotR, dotR)*unitsphere;
draw(shift(A)*s, surfacepen=orb, render(merge=true));
draw(shift(B)*s, surfacepen=orb, render(merge=true));

draw(graph(c1, -pi, pi, 100, operator ..), blue);
draw(graph(c2, -pi, pi, 100, operator ..), blue);
