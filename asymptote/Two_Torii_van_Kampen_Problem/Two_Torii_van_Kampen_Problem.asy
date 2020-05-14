// Boilerplate stuff.
import settings;
import graph3;
import tube;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (20, 80, 25), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(256);

// Pen for drawing.
pen mpen = black+linewidth(0.1pt);

// Radii of the torus.
real R = 4;
real a = 1;
real pipR = 0.05;

// Number of samples in the figure.
int samples = 24;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.75),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material pipe0 = material(diffusepen=black,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

surface s;

triple f(pair t) {
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

// Some contour lines.
triple c0(real t){return f((t, pi/2));}

s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, meshpen=mpen, render(merge=true));
draw(shift(0, 0, 2*a)*s, surfacepen=blob, meshpen=mpen, render(merge=true));

path3 q=graph(c0, 0, 2pi, 100, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe0, render(merge=true));
