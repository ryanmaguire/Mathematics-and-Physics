import settings;
import graph3;
import palette;
import tube;
settings.render=8;

outformat="pdf";
size(300);

currentprojection=orthographic(2.82, 0, 1);
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {0.5*white},
                     position = new triple[] {Y+Z});

pen tcolor = blue+0.3*green;

real R = 5;
real a = 1;
real b = 0.05;
int samples = 24;
surface s;

triple g(pair t) {
    return ((R+a*cos(t.y)*sin(t.x/2))*cos(t.x),
            (R+a*cos(t.y))*sin(t.x),
            sin(t.x/2)*a*sin(t.y));
}

// Squished torus.
s = surface(g, (0, 0), (2pi, 2pi), samples, samples, Spline);
s.colors(palette(s.map(xpart), Gradient(tcolor, tcolor)));

draw(s, render(merge=true));