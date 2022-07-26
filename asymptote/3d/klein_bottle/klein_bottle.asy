// Boilerplate stuff.
import graph3;
import palette;
import settings;
settings.outformat = "pdf";

// Size of the created image.
size(256);

currentprojection=perspective(
    camera = (20, -20,40),
    up     = (0,  -1, 0),
    target = (0,   0, 0),
    zoom   =1
);

triple f(pair t) {
    real u = t.x;
    real v = t.y;
    real r = 2-cos(u);
    real x = 3*cos(u)*(1+sin(u))+r*cos(v)*(u < pi ? cos(u) : -1);
    real y = 8*sin(u)+(u < pi ? r*sin(u)*cos(v) : 0);
    real z = r*sin(v);
    return (x,y,z);
}

surface s=surface(f, (0, 0), (2pi, 2pi), 32, 32, Spline);
s.colors(palette(s.map(ypart), Gradient(green, blue)));
draw(s, meshpen=black+linewidth(0.3pt), render(merge=true));
