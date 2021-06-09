// Boilerplate stuff.
import settings;
import graph3;
import palette;

if(!settings.multipleView)  settings.batchView=false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;

viewportmargin = (2, 2);

size(256);

currentprojection=orthographic(4, 0, 1);
currentlight=light(gray(0.8), specularfactor=2, viewport=true, (2.0, 2.0, 2.0));

currentprojection=orthographic(2, 2, 1);
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {0.5*white},
                     position = new triple[] {Y+Z});

pen tcolor = blue+0.3*green;

real R = 5;
real a = 1;
int samples = 24;
material blob;
surface s1, s2;

triple f(pair t) {
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

blob = material(diffusepen=opacity(0.0));

s1 = surface(f, (-pi/3,0), (pi/2,2pi), samples, samples, Spline);
s2 = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);

draw(s1, meshpen=blue, surfacepen=blob);

s2.colors(palette(s2.map(xpart),
          Gradient(tcolor, tcolor, tcolor, tcolor,
                   tcolor+opacity(0.7),
                   tcolor+opacity(0.2))));

draw(s2, render(merge=true));

// Draw circle inside torus.
draw(shift(R, 0, 0)*reflect(O, X, Y+Z)*surface(unitcircle), gray(0.5), nolight);