if(!settings.multipleView) settings.batchView=false;
if(settings.render < 0) settings.render=4;

settings.tex="pdflatex";
defaultfilename="Trefoil_Tricolor.pdf";
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

import tube;
import graph3;
import palette;

size(300,0);
currentprojection=perspective(
    camera=(0,0,-25),
    up=(0,1,0),
    target=(0,0,0),
    zoom=0.85
);

triple f(real t){
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));
}

currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {-Z}
);

path section=scale(0.5)*unitcircle;

path3 p1=graph(f,2pi/9,8pi/9,n=350,operator ..);
path3 p2=graph(f,8pi/9,29pi/18,n=350,operator ..);
path3 p3=graph(f,29pi/18,9pi/4,n=350,operator ..);

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
    surfacepen=material(diffusepen=red,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);

draw(
    tube(p3,section),
    light=currentlight,
    surfacepen=material(diffusepen=blue+0.25*green,
                        emissivepen=gray(0.1),
                        specularpen=gray(0.3))
);
