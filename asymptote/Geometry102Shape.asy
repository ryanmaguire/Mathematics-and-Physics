// Boilerplate stuff.
import _asy_preamble_3d;
import _euclidean;
size(256);

triple camera_location, origin, up_dir;
real zoom, r, R;
int samples;
pen mpen;
surface s;

camera_location = (200.0, 50.0, 50.0);
origin = (0.0, 0.0, 0.0);
up_dir = (0.0, 0.0, 1.0);
zoom = 1.0;

currentprojection=orthographic(camera = camera_location, target = origin,
                               zoom = zoom, up = up_dir);

currentlight=light(
    gray(0.4),
    specularfactor=1,
    viewport=true,
    (-0.5,-0.25,0.45),
    (0.5,-0.5,0.5),
    (0.5,0.5,0.75)
);

r = 0.1;
R = 10;
samples = 32;
mpen = black+linewidth(0.3pt);


triple f(pair t)
{
    real r, theta, phi;
    real x, y, z;
    phi = t.x;
    r = sin(phi);
    theta = t.y;

    x = (1+r)*cos(theta);
    y = 0.0;
    z = (1+r)*sin(theta);

    return shift(0, 0, -r)*(rotate(180*phi/pi, (0, 0, 1))*(x, y, z));
}

s = surface(f, (0, 0), (pi, 2pi), samples, samples, Spline);
draw(s, meshpen=mpen, surfacepen=blob);
