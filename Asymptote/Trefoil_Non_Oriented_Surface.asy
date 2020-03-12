import settings;
import tube;
import graph3;
import palette;
settings.render=8;
outformat="pdf";

size(169, 169);

currentprojection=perspective(
    camera  = (0, 0, 25),
    up      = (0, 0, 1),
    target  = (0, 0, 0),
    zoom    = 0.85
);

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material blob = material(diffusepen  = blue+lightgreen,
                         emissivepen = gray(0.1),
                         specularpen = gray(0.1));

material pipe = material(diffusepen  = blue+lightgreen,
                         emissivepen = gray(0.3),
                         specularpen = gray(0.1));

triple f(real t){return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));}

triple surf(pair t) {return (t.x*f(t.y)+(1-t.x)*f(t.y+pi));}

surface s = surface(surf, (0, 0), (1, 2pi), 10, 20, Spline);
path3 p = graph(f, 0, 2pi, n=500, operator ..);

draw(s, render(merge=true), light=currentlight, surfacepen=blob);
draw(tube(p, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);
