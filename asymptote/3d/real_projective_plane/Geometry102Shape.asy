import three;
import graph3;

size(256);

triple camera_location, origin, up_dir;
real zoom, r, R;
int samples;
pen mpen;
surface s;

camera_location = (50.0, 200.0, 50.0);
origin = (0.0, 0.0, 0.0);
up_dir = (0.0, 0.0, 1.0);
zoom = 1.0;

/*  Commonly used materials in 3D drawing.                                    */
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

currentprojection=orthographic(camera = camera_location, target = origin,
                               zoom = zoom, up = up_dir);

r = 0.1;
R = 10;
samples = 16;
mpen = black+linewidth(0.3pt);

triple f(pair t)
{
    real r, theta, phi;
    real x, y, z;
    phi = t.x;
    r = sin(phi);
    r *= r;
    theta = t.y;
    r = 1.0 / (1+r);

    x = r*cos(theta);
    y = 0.0;
    z = r*sin(theta);

    return shift(0, 0, -r)*(rotate(180*phi/pi, (0, 0, 1))*(x, y, z));
}

s = surface(f, (0, 0), (pi, 2pi), samples, samples, Spline);
draw(s, meshpen=mpen, surfacepen=blob);
