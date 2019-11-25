if(!settings.multipleView) settings.batchView=false;
if(settings.render < 0) settings.render=4;

settings.tex="pdflatex";
defaultfilename="Klein_Bottle.pdf";
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

import graph3;
import palette;

// Size of the created image.
size(500,0);

currentprojection=perspective(
    camera=(50,-60,40),
    up=(0,0,1),
    target=(0,0,0),
    zoom=1
);

triple f(pair t) {
    real u=t.x;
    real v=t.y;
    real r=2-cos(u);
    real x=3*cos(u)*(1+sin(u))+r*cos(v)*(u < pi ? cos(u) : -1);
    real y=8*sin(u)+(u < pi ? r*sin(u)*cos(v) : 0);
    real z=r*sin(v);
    return (x,y,z);
}

material blob = material(orange+yellow, specularpen=gray(0.1));

surface s=surface(f,(0,0),(2pi,2pi),8,8,Spline);
draw(s,surfacepen=blob,render(merge=true));
