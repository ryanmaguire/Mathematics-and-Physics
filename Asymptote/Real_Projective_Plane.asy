import settings;
import tube;
import graph3;
import palette;

outformat="pdf";

// Size of the created image.
size(300, 300);

currentprojection=perspective(
    camera=(20,20,15),
    up=(0,0,-1),
    target=(0,0,0),
    zoom=0.85
);

real R=1;
real N=3.6;
real H=2;
real P=1.9;

triple f(pair t) {
return (sin(t.x)*sin(2*t.y)/2,
        sin(2*t.x)*(cos(t.y)^2),
        cos(2*t.x)*(cos(t.y)^2));
}

surface s=surface(f,(0,0),(2pi,pi),20,20,Spline);
s.colors(palette(s.map(xpart),Gradient(red,blue)));

draw(s,render(merge=true));