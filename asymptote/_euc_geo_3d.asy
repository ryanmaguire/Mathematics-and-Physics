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
