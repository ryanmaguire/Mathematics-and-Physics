import settings;
settings.outformat="gif";
settings.render=0;

import graph3;
import tube;
import animation;
currentprojection=perspective(camera = (0, 50, 30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

pen mpen = black+linewidth(0.1pt);
int samplex = 10;
int sampley = 40;

int i;
int n = 100;

real dx = 1.0/n;
real r = 0.0;
real pipR = 0.01;

animation a;
surface s;
material blob = material(diffusepen=gray(0.7),
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe = material(diffusepen=gray(0.0),
                         emissivepen=gray(0.1),
                         specularpen=gray(0.1));

triple f(pair Z){
    real u = Z.x;
    real v = Z.y;
    triple center = (v*cos(2*pi*v), v*sin(2*pi*v), v);
    real r = 1-v;
    real x = r*cos(u)+center.x;
    real y = r*sin(u)+center.y;
    real R = sqrt(x*x+y*y);
    real z = v*v*(1.0-R^2);
    return (x, y, z);
}

triple g(real t){return f((t, 0));}

s = surface(f, (0, 0.0), (2pi, 1), samplex, sampley, Spline);
draw(s, invisible);
path3 q=graph(g, 0, 2pi, 250, operator ..);
draw(tube(q, scale(pipR)*unitcircle), invisible);

for (i = 0; i < n; ++i) {
    save();
    write("Computing image with " + (string)i + " dominoes toppled.");

    s = surface(f, (0, 0.0), (2pi, r), samplex, sampley, Spline);
    draw(s, surfacepen=blob, meshpen=mpen, render(merge=true));

    path3 q=graph(g, 0, 2pi, 250, operator ..);
    draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe, render(merge=true));
    r += dx;

    a.add();
    restore();
}

a.movie(delay=40);