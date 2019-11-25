if(!settings.multipleView) settings.batchView=false;
if(settings.render < 0) settings.render=4;

settings.tex="pdflatex";
defaultfilename="Sea_Shell.pdf";
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

import graph3;
import palette;

// Size of the created image.
size(300,0);

// Set camera location and orientation.
currentprojection=perspective(
    camera=(-2,-5,2),
    up=(0,0,1),
    target=(0,0,0),
    zoom=0.85
);

// Some parameters for the surface.
real R=1;
real N=3.6;
real H=2;
real P=1.9;

triple f(pair t) {
return ((t.x/(2*pi*R))*cos(N*t.x)*(1+cos(t.y)),
        (t.x/(2*pi*R))*sin(N*t.x)*(1+cos(t.y)),
        (-t.x/(2*pi*R))*sin(t.y) - H*(t.x/(2*pi))^P);
}

surface s=surface(f,(0,0),(2pi,2pi),20,20,Spline);
s.colors(palette(s.map(xpart),Gradient(blue,green)));

draw(s,meshpen=black,render(merge=true));