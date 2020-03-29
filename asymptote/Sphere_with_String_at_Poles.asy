import settings;
import graph3;
import palette;
import tube;
settings.render=8;

outformat="pdf";
size(150);

currentprojection=orthographic(4, 0, 1);
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {0.5*white},
                     position = new triple[] {Y+Z});

pen tcolor = blue+0.3*green;

real R = 5;
surface s1, s2;
path3 p;

// Sphere with string coming out of poles.
s2 = scale(R, R, R)*surface(unitsphere);
s2.colors(palette(s2.map(xpart), Gradient(tcolor, tcolor)));

p  = (0, 0, R){(0, 0, 0.3)}..(0, 1.5*R, 0)..(0, 0, -R){(0, 0, 0.3)};
s1 = surface(tube(p, scale(0.1)*unitcircle, relstep=0.01));
s1.colors(palette(s1.map(xpart), Gradient(tcolor, tcolor)));

draw(s2, render(merge=true));
draw(s1, render(merge=true));