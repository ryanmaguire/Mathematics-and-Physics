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

// Two light sources
// currentlight = light(diffuse = new pen[] {white, white},
//                      specular = new pen[] {white, white},
//                      position = new triple[] {X+Y+Z, -20*X-20*Y+Z});

// One light source
currentlight = light(diffuse = new pen[] {white},
                     specular = new pen[] {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

path3 p=graph(f,0,2pi,n=1000,operator ..);
draw(tube(p,scale(0.5)*unitcircle), blue+0.25*green,light=currentlight);
