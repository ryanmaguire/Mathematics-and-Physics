import settings;
import graph3;
import palette;
import tube;
settings.render = 8;

outformat="pdf";

size(300);

// Set camera location and orientation.
currentprojection=perspective(camera=(1000, 0, 300), up=(0, 0, 1),
                              target=(0, 0, 0),      zoom=0.85);

currentlight = light(diffuse = new pen[] {white},
                     specular = new pen[] {white},
                     position = new triple[] {100Z+100X+3*Y});

triple f1(pair t) {return (cos(t.x)*sin(t.y), sin(t.x)*sin(t.y), cos(t.y));}

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

triple f4(pair t) {return (t.x*cos(t.y), 9+t.x*sin(t.y), 0.0);}

triple g1(real x) {return f1((x, 0.1));}
triple g2(real x) {return f2((x, 1.0));}
triple g3(real x) {return f3((x, pi/2));}
triple g4(real x) {return f4((1, x));}

material blob = material(diffusepen  = gray(0.6),
                         emissivepen = gray(0.2),
                         specularpen = gray(0.1));

material pipe = material(diffusepen  = blue+lightgreen,
                         emissivepen = gray(0.3),
                         specularpen = gray(0.1));

surface s1=surface(f1, (0, 0.1),  (2pi, pi),  20, 20, Spline);
surface s2=surface(f2, (0, 1.0),  (2pi, pi),  20, 20, Spline);
surface s3=surface(f3, (0, pi/2), (2pi, pi),  20, 20, Spline);
surface s4=surface(f4, (0, 0),    (1,   2pi), 20, 20, Spline);

draw(s1, render(merge=true), light=currentlight, surfacepen=blob);
draw(s2, render(merge=true), light=currentlight, surfacepen=blob);
draw(s3, render(merge=true), light=currentlight, surfacepen=blob);
draw(s4, render(merge=true), light=currentlight, surfacepen=blob);

path3 p1=graph(g1, 0, 2pi, n=100, operator ..);
path3 p2=graph(g2, 0, 2pi, n=100, operator ..);
path3 p3=graph(g3, 0, 2pi, n=100, operator ..);
path3 p4=graph(g4, 0, 2pi, n=100, operator ..);

draw(tube(p1, scale(0.02)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(p2, scale(0.02)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(p3, scale(0.02)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(p4, scale(0.02)*unitcircle), surfacepen=pipe, light=currentlight);