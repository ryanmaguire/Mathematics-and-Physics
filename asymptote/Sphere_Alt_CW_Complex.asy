// Boilerplate stuff.
import settings;
import tube;
import three;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (20, -40, 20), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(64);

// Radius of the dot and pipes.
real dotR = 0.08;
real pipR = 0.02;

path section=scale(pipR)*unitcircle;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

material pipe = material(diffusepen=black,
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

draw(unitsphere, surfacepen=blob, render(merge=true));

surface s = scale(dotR, dotR, dotR)*unitsphere;
draw(shift(1, 0,  0)*s, surfacepen=orb, render(merge=true));

draw(tube(unitcircle3, section), surfacepen=pipe, render(merge=true));