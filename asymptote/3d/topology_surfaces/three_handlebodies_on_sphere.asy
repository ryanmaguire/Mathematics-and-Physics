// Boilerplate stuff.
import settings;
import three;
import graph3;

settings.render=8;


currentprojection=orthographic(camera = (0.0, 0.0, 20.0), up   = (0, 0, 1),
                               target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(128);

// Radius of the dot and pipes.
real dotR = 0.08;
real R = 0.4;
real a = 0.1;
int samples = 60;
surface s; 

// Parameterization of a torus.
triple f(pair t)
{
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));


draw(unitsphere, surfacepen=blob, render(merge=true));
s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(shift(0.0, 0.9, 0.0)*s, surfacepen=blob, render(merge=true));
draw(shift(0.9, 0.0, 0.0)*s, surfacepen=blob, render(merge=true));
draw(shift(-0.9, 0.0, 0.0)*s, surfacepen=blob, render(merge=true));
