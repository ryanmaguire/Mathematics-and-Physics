import settings;
import tube;
import graph3;
import palette;
settings.render=4;

outformat="pdf";

// Size of the created image.
size(300);

currentprojection=perspective(
    camera=(50,-60,40),
    up=(0,0,1),
    target=(0,0,0),
    zoom=1
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

material blob = material(diffusepen=blue+lightgreen+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.1));

surface s=surface(f, (0, 0), (2pi, 2pi), 32, 32, Spline);
draw(s,surfacepen=blob, render(merge=false));
