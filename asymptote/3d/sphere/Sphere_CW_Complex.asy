// Boilerplate stuff.
import settings;
import three;

settings.render=8;


currentprojection=perspective(camera = (20, -40, 20), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(64);

// Radius of the dot and pipes.
real dotR = 0.08;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

draw(unitsphere, surfacepen=blob, render(merge=true));

surface s = scale(dotR, dotR, dotR)*unitsphere;
draw(shift(0, 0, 1)*s, surfacepen=orb, render(merge=true));