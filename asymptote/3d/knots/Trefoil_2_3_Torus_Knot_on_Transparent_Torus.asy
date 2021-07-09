import settings;
import tube;
import graph3;
import palette;
settings.render=8;

size(128);

// Radii of the torus.
real R = 1.5;
real a = 1.0;

currentprojection=perspective(camera = (100, 0, 100), up   = (0, 0, 1),
                              target = (0, 0, 0),   zoom = 0.85);

triple f(real t)
{
    return ((1.5+cos(3*t))*cos(2*t), (1.5+cos(3*t))*sin(2*t), sin(3*t));
}

triple g(pair t)
{
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});



// Number of samples in the figure.
int samples = 24;

material pipe = material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.20),
                         specularpen = gray(0.20));

material blob = material(diffusepen=gray(0.7) + opacity(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

path3 p=graph(f, 0, 2pi, n=1000, operator ..);
draw(tube(p, scale(0.1)*unitcircle), surfacepen=pipe, light=currentlight);


surface s = surface(g, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));