// Boilerplate stuff.
import settings;
import graph3;
import palette;

if(!settings.multipleView)  settings.batchView=false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;

viewportmargin = (2, 2);

size(256);

currentprojection=orthographic(4, 0, 1);
currentlight=light(gray(0.8), specularfactor=2, viewport=true, (2.0, 2.0, 2.0));

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