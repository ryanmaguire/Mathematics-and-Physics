// Boilerplate stuff.
import settings;
import graph3;
import palette;
import tube;

if(!settings.multipleView)  settings.batchView=false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;

viewportmargin = (2, 2);

size(128);

currentprojection=orthographic(4, 0, 1);
currentlight=light(gray(0.8), specularfactor=2, viewport=true, (2.0, 2.0, 2.0));

pen tcolor = blue+0.3*green;

real R = 5;
surface s1, s2;
path3 p;

// Kettle bell.
s2=scale(R, R, R)*surface(unitsphere);
s2.colors(palette(s2.map(xpart), Gradient(tcolor, tcolor)));

p  = (0, R, 0){(0, 0, 0.5)}..(0, 2*R, 0)..(0, R, 0){(0, 0, 0.5)};
s1 = surface(tube(p, scale(0.1)*unitcircle, relstep=0.01));
s1.colors(palette(s1.map(xpart), Gradient(tcolor, tcolor)));

draw(s2, render(merge=true));
draw(s1, render(merge=true));