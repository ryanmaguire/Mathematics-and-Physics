if(!settings.multipleView) settings.batchView=false;
if(settings.render < 0) settings.render=4;

settings.tex="pdflatex";
defaultfilename="Sphere_to_Disk_Homeo.pdf";
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

import graph3;
import palette;

// Size of the created image.
size(500,0);

// Set camera location and orientation.
currentprojection=perspective(
    camera=(1000,0,400),
    up=(0,0,1),
    target=(0,0,0),
    zoom=0.85
);

currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {3000Z+3000X+3*Y}
);

triple f1(pair t) {
    return (cos(t.x)*sin(t.y), sin(t.x)*sin(t.y), cos(t.y));
}

triple f2(pair t) {
    real u = cos(t.x)*sin(t.y);
    real v = sin(t.x)*sin(t.y);
    real theta0 = 1.0;
    real a = theta0/(pi-theta0);

    return (u, 3+v, cos(t.y-a*(pi-t.y)));
}

triple f3(pair t) {
    real u = cos(t.x)*sin(t.y);
    real v = sin(t.x)*sin(t.y);
    real a = 1/(1.0-sqrt(3));
    real b = sqrt(3)*a+0.5;
    return (u, 6+v, b-a*sqrt(u^2+v^2+1));
}

triple f4(pair t) {
    real u = t.x*cos(t.y);
    real v = t.x*sin(t.y);
    return (u, 9+v, 0.0);
}

surface s1=surface(f1,(0,0.1),(2pi,pi),20,20,Spline);
surface s2=surface(f2,(0,1.0),(2pi,pi),20,20,Spline);
surface s3=surface(f3,(0,pi/2),(2pi,pi),20,20,Spline);
surface s4=surface(f4,(0,0),(1,2pi),20,20,Spline);

material blob = material(diffusepen=gray,
                         emissivepen=gray(0.2),
                         specularpen=gray(0.1));

draw(s1, render(merge=true), light=currentlight, surfacepen=blob);
draw(s2, render(merge=true), light=currentlight, surfacepen=blob);
draw(s3, render(merge=true), light=currentlight, surfacepen=blob);
draw(s4, render(merge=true), light=currentlight, surfacepen=blob);