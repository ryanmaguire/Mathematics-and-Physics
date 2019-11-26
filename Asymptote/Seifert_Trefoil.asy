if(!settings.multipleView) settings.batchView=false;
if(settings.render < 0) settings.render=4;

settings.tex="pdflatex";
defaultfilename="Seifert_Trefoil.pdf";
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

import tube;
import graph3;
import palette;

// Size of the created image.
size(500,0);

// Set camera location and orientation.
currentprojection=perspective(
    camera=(10,10,10),
    up=(0,0,1),
    target=(0,0,0),
    zoom=1.0
);

currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {3000Z+3000X+3*Y}
);

path section=scale(0.05)*unitcircle;
material blob = material(diffusepen=gray+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.1));

transform3 T1 = rotate(120, Z);
transform3 T2 = rotate(240, Z);

triple Tube1a(real t) {
    return (cos(pi*t)+3*(t-0.5)/2, sin(pi*t)+0.5, t);
}

triple Tube1b(real t) {
    return (0.5*cos(pi*t)+3*(t-0.5)/2, 0.5*sin(pi*t)+0.5, t);
}

triple Tube2a(real t) {
    return (-0.25, 0.5, 0)*(1-t)+t*(-0.558013, 0.0334936, 0);
}

triple Surf1(pair t) {
    return (t.x*cos(pi*t.y)+3*(t.y-0.5)/2, t.x*sin(pi*t.y)+0.5, t.y);
}

path3 p1=graph(Tube1a,0,1,n=100,operator ..);
path3 p2=graph(Tube1b,0,1,n=100,operator ..);
path3 p3=T1*graph(Tube1a,0,1,n=100,operator ..);
path3 p4=T1*graph(Tube1b,0,1,n=100,operator ..);
path3 p5=T2*graph(Tube1a,0,1,n=100,operator ..);
path3 p6=T2*graph(Tube1b,0,1,n=100,operator ..);
path3 p7=graph(Tube2a,0,1,n=100,operator ..);
path3 p8=T1*graph(Tube2a,0,1,n=100,operator ..);
path3 p9=T2*graph(Tube2a,0,1,n=100,operator ..);
surface s1=surface(Surf1,(0.5,0),(1,1),20,20,Spline);
surface s2=T1*surface(Surf1,(0.5,0),(1,1),20,20,Spline);
surface s3=T2*surface(Surf1,(0.5,0),(1,1),20,20,Spline);

draw(
    tube(p1,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p2,section),
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p3,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p4,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p5,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p6,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p7,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p8,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p9,section), 
    light=currentlight,
    surfacepen=material(diffusepen=green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(s1, render(merge=true), light=currentlight, surfacepen=blob);
draw(s2, render(merge=true), light=currentlight, surfacepen=blob);
draw(s3, render(merge=true), light=currentlight, surfacepen=blob);
