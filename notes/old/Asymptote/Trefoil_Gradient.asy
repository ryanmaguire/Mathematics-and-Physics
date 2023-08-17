import settings;
import tube;
import graph3;
import palette;

outformat="pdf";

size(300, 300);

currentprojection=perspective(
    camera=(0,0,25),
    up=(0,0,1),
    target=(0,0,0),
    zoom=0.85
);

triple f(real t){
return (2*sin(2*t)-sin(t),
        2*cos(2*t)+cos(t),
        sin(3*t));
}

pen pen(real t){
    return interp(red,blue,sin(t*2pi/500)^2);
}


path section=scale(0.5)*unitcircle;

path3 p=graph(f,0,2pi,n=1000,operator ..);
draw(tube(p,coloredpath(section,pen)));