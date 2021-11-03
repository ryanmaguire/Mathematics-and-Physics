import settings;
import tube;
import graph3;
import palette;
settings.render=8;
settings.outformat="pdf";

size(169, 169);

currentprojection=perspective(
    camera=(100, 5, 100),
    up=(0,0,1),
    target=(0,0,0),
    zoom=0.85
);

// One light source
currentlight = light(diffuse = new pen[] {white},
                     specular = new pen[] {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

// Index used for looping over arrows.
int i;

// Total number of arrows to draw.
int n = 32;

// Variable to looping over angles.
real phi;

// Path for drawing tubes.
path3 p;

// Size of the arrow head.
real arsize = 5bp;

// Materials for the surface of the mobius strip and the boundary.
material blob, pipe;


blob = material(diffusepen=gray(0.8)+opacity(0.7),
                emissivepen=gray(0.3),
                specularpen=gray(0.1));

pipe = material(diffusepen=gray(0.3),
                emissivepen=gray(0.4),
                specularpen=gray(0.1));

path section=scale(0.03)*unitcircle;

triple surf(pair t){
    real u = t.x;
    real v = t.y;
    real z = 1+(v/2)*cos(u/2);
    return (z*cos(u), z*sin(u), (v/2)*sin(u/2));
}

triple cyl(pair t){
    real u = t.x;
    real v = t.y;
    return (cos(u), sin(u), v);
}

triple boundary(real t){return surf((t, 1));}
triple inner_circle(real t){return surf((t, 0));}

p=graph(boundary, 0, 4pi, n=500, operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));

triple boundary(real t){return cyl((t, 1));}
p=graph(boundary, 0, 4pi, n=500, operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));

surface s=surface(surf, (0,-1), (2pi,1), 20, 20,Spline);
draw(s, meshpen=black+linewidth(0.1pt), render(merge=true), surfacepen=blob);

surface s=surface(cyl, (0,0), (2pi,1), 20, 10, Spline);
draw(s, meshpen=black+linewidth(0.1pt), render(merge=true), surfacepen=blob);

section = scale(0.02)*unitcircle;
pipe = material(diffusepen=blue+lightgreen,
                emissivepen=gray(0.4),
                specularpen=gray(0.1));

p=graph(inner_circle, 0, 2pi, n=250, operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));