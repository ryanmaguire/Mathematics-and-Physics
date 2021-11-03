// Boilerplate stuff.
import graph3;
import settings;
settings.outformat = "pdf";
settings.render = 8;

size(512);

real r, R;
int samples;
pen mpen;
surface s1, s2, s3;

currentprojection=orthographic(
    camera = (0.0, 1000.0, 200.0),
    target = (0.0, 0.0, 0.0),
    zoom = 1.0,
    up = (0.0, 0.0, 1.0)
);

material blob = material(
    diffusepen=gray(0.7),
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

/* Returns the Euclidean norm of a 2-dimensional point.                       */
real EuclideanNorm2D(pair A)
{
    /*  Using Pythagoras, we simply compute sqrt(x^2 + y^2).                  */
    return sqrt(A.x*A.x + A.y*A.y);
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

/*  The equation for a torus centered at the origin with inner radius iR and  *
 *  outer radius oR. The pair t should lie in [0,2pi]x[0,2pi]                 */
triple TorusEquation(pair t, real iR, real oR)
{
    return ((oR+iR*cos(t.y))*cos(t.x), (oR+iR*cos(t.y))*sin(t.x), iR*sin(t.y));
}

/* Returns the Euclidean norm of a 3-dimensional point.                       */
real EuclideanNorm3D(triple A)
{
    /*  Use Pythagoras to compute the length of A.                            */
    return sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
}

/*  Scale a three dimensional vector by a real number.                        */
triple ScaleThreeVector(real r, triple V)
{
    /*  Simply multiply the components and return.                            */
    return (r*V.x, r*V.y, r*V.z);
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


r = 0.1;
R = 10;
samples = 32;
mpen = black+linewidth(0.3pt);

triple f(pair t)
{
    return SphericalToRect(1, t.x, t.y);
}

triple g(pair t)
{
    if (t.y == 0.0)
        return (0.0, 0.0, 1.0);
    else
        return InverseStereographicProjection(
            StereographicProjection(
                SphericalToRect(R, t.x, t.y)
            )
        );
}

triple h(pair t)
{
    if (t.y == 0.0)
        return (0.0, 0.0, 1.0);
    else
        return InverseStereographicProjection(
            StereographicProjection(
                SphericalToRect(r, t.x, t.y)
            )
        );
}

s1 = surface(f, (0, 0.01), (2pi, pi), samples, samples, Spline);
s2 = surface(g, (0, 0.01), (2pi, pi), samples, samples, Spline);
s3 = surface(h, (0, 0.01), (2pi, pi), samples, samples, Spline);
draw(shift(+0, 0, 0)*s1, meshpen=mpen, surfacepen=blob);
draw(shift(-3, 0, 0)*s2, meshpen=mpen, surfacepen=blob);
draw(shift(+3, 0, 0)*s3, meshpen=mpen, surfacepen=blob);
