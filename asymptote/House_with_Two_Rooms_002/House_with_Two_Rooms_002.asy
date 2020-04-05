// Boilerplate stuff.
import settings;
import tube;
import graph3;
import palette;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (20, 60, 20), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Set up the lighting.
currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {3000Z+3000X+3*Y}
);

// Size of the output figure.
size(256);

// Dimensions of the house.
real xlength = 1.0;
real ylength = 2.0;
real zlength = 0.5;

// Size of the box.
real boxwidth = 0.5*xlength;

// Materials used throughout.
material blob, pipe;

// Material for the xy plane.
blob = material(diffusepen=gray(0.5)+opacity(0.5),
                emissivepen=gray(0.2),
                specularpen=gray(0.1));

// Material for the curves.
pipe = material(diffusepen  = black,
                emissivepen = gray(0.20),
                specularpen = gray(0.20));

// Surface for drawing.
surface s;

// Draw the xy plane.
s=surface((0.0,     0.0,     0.0)--
          (xlength, 0.0,     0.0)--
          (xlength, ylength, 0.0)--
          (0.0,     ylength, 0.0)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

// Draw the roof.
s=surface((0.0,     0.0,     2*zlength)--
          (xlength, 0.0,     2*zlength)--
          (xlength, ylength, 2*zlength)--
          (0.0,     ylength, 2*zlength)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

// Draw the walls.
s=surface((0.0,     0.0, 0.0)--
          (xlength, 0.0, 0.0)--
          (xlength, 0.0, 2*zlength)--
          (0.0,     0.0, 2*zlength)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

s=surface((0.0, 0.0,     0.0)--
          (0.0, ylength, 0.0)--
          (0.0, ylength, 2*zlength)--
          (0.0, 0.0,     2*zlength)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

s=surface((xlength, ylength, 0.0)--
          (xlength, ylength, 2*zlength)--
          (xlength, 0.0,     2*zlength)--
          (xlength, 0.0,     0.0)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

s=surface((xlength, ylength, 0.0)--
          (0.0,     ylength, 0.0)--
          (0.0,     ylength, 2*zlength)--
          (xlength, ylength, 2*zlength)--cycle);
draw(s, surfacepen=blob, render(merge=true), light=currentlight);

// Draw in the edges.
draw(tube(((xlength, ylength, 0.0)--(0.0, ylength, 0.0)),
    scale(0.01)*unitcircle), surfacepen=pipe, render(merge=true));

draw(tube(((xlength, ylength, 0.0)--(xlength, 0.0, 0.0)),
    scale(0.01)*unitcircle), surfacepen=pipe, render(merge=true));
