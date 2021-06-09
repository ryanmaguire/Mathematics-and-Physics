// Boilerplate stuff.
import _asy_preamble_3d;
import _euclidean;
size(256);

triple camera_location, origin, up_dir;
real zoom, r, R;
int samples;
pen mpen;
surface s1, s2, s3;

camera_location = (0.0, 1000.0, 200.0);
origin = (0.0, 0.0, 0.0);
up_dir = (0.0, 0.0, 1.0);
zoom = 1.0;

currentprojection=orthographic(camera = camera_location, target = origin,
                               zoom = zoom, up = up_dir);


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
