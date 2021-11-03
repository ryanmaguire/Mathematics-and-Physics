// Boilerplate stuff.
import graph3;
import palette;

// Size of the created image.
size(128);

material blob = material(diffusepen=gray(0.7) + opacity(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

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

surface s=surface(f, (0, 0), (2pi, 2pi), 200, 200, Spline);
draw(s, surfacepen=blob, render(merge=true));
