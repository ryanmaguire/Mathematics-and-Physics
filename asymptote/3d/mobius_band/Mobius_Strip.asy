import settings;
import tube;
import graph3;
import palette;
settings.render=8;
settings.outformat = "pdf";

size(256);

currentprojection=perspective(
    camera=(5, 5, 5),
    up=(0,0,1),
    target=(0,0,0),
    zoom=0.85
);

// One light source
currentlight = light(diffuse = new pen[] {white},
                     specular = new pen[] {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material blob = material(diffusepen=blue+lightgreen,
                         emissivepen=gray(0.3),
                         specularpen=gray(0.1));

material pipe = material(diffusepen=blue+0.2*green,
                         emissivepen=gray(0.4),
                         specularpen=gray(0.1));

path section=scale(0.05)*unitcircle;

triple surf(pair t){
    real u = t.x;
    real v = t.y;
    real z = 1+(v/2)*cos(u/2);
    return (z*cos(u), z*sin(u), (v/2)*sin(u/2));
}

triple f(real t){
    return ((1+0.5*cos(t/2))*cos(t), (1+0.5*cos(t/2))*sin(t), 0.5*sin(t/2));
}

path3 p=graph(f,0,4pi,n=1000,operator ..);
draw(tube(p, section), surfacepen=pipe, render(merge=true));

surface s=surface(surf,(0,-1),(2pi,1),500,20,Spline);
draw(s,render(merge=true),light=currentlight,surfacepen=blob);
