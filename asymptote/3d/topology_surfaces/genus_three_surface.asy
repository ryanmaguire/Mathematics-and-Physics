// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;

settings.render=8;

currentprojection=perspective(camera = (20, 80, 30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(256);

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

real lem2(real x, real y)
{
    real u = 0.5*x;
    real factor = 4.0*u*u - 1.0;
    return y*y - factor * factor * (1.0 - u*u);
}

real h = 0.2;
int samples = 100;

// Surface to draw.
real f(real x, real y, real z)
{
    real u = lem2(x, y);
    return u*u + z*z - h*h;
}

surface s = implicitsurface(f, a=(-2.1, -1.2, -0.4), b=(2.1,  1.2,  0.4));
draw(s, surfacepen=blob, samples, render(merge=true));
