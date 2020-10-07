// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;
import _euclidean;
import three;

if(!settings.multipleView)
    settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (100, 50, 20), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Pen for drawing.
pen dpen = black+linewidth(1.0pt);
pen bpen = blue+linewidth(0.5pt);
pen rpen = red+linewidth(0.5pt);

// Size of the output figure.
size(128);

triple A = SphericalToRect(1.0, 0.0, pi/2);
triple B = SphericalToRect(1.0, 3pi/4, pi/2);

triple c1(real t){return SphericalCircle(t, 1.0, A, B);}
triple c2(real t){return SphericalCircle(t, 1.0, B, A);}

// Radius of the dot and pipes.
real dotR = 0.08;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.5),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.5),
                        specularpen=gray(0.5));

draw(unitsphere, surfacepen=blob, render(merge=true));

surface s = scale(dotR, dotR, dotR)*unitsphere;
draw(shift(A)*s, surfacepen=orb, render(merge=true));
draw(shift(B)*s, surfacepen=orb, render(merge=true));

draw(graph(c1, -pi, pi, 100, operator ..), blue);
draw(graph(c2, -pi, pi, 100, operator ..), blue);
