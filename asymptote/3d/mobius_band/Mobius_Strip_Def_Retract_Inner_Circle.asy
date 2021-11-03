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


blob = material(diffusepen=gray(0.8),
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

triple boundary(real t){return surf((t, 1));}
triple inner_circle(real t){return surf((t, 0));}

p=graph(boundary, 0, 4pi, n=500, operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));

section = scale(0.01)*unitcircle;
pipe = material(diffusepen=blue+lightgreen,
                emissivepen=gray(0.4),
                specularpen=gray(0.1));

p=graph(inner_circle, 0, 2pi, n=250, operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));

surface s=surface(surf, (0,-1), (2pi,1), 500, 20,Spline);
draw(s,render(merge=true), surfacepen=blob);

for(i=0; i<n; ++i){
    phi = 4*pi*i/n;
    triple retract(real t){return surf((phi, t));}
    p=graph(retract, 1, 0, n=10, operator ..);
    draw(p, arrow=Arrow3(arsize), TrueMargin3(0.15cm, 0.15cm));
}