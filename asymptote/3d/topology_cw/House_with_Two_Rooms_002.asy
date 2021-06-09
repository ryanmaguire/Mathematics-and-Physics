// Boilerplate stuff.
import settings;
import tube;
import three;

if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;

viewportmargin = (2, 2);

currentprojection = perspective(camera = (60, 20, 20), up   = (0, 0, 1),
                                target = (0,  0,  0),  zoom = 1.0);

// Set up the lighting.
currentlight = nolight;

// Size of the output figure.
size(256);

// Dimensions of the house.
real xlength = 1.0;
real ylength = 2.0;
real zlength = 0.5;

// Size of the edges.
path section=scale(0.005)*unitcircle;

// Paths and surfaces for drawing everything.
path3 g;
guide3 g3;
surface s;

// Size of the box.
real boxwidth  = 0.5*xlength;
real boxystart = 0.15*ylength;
real boxxstart = 0.5(xlength-boxwidth);

// Materials used throughout.
material pipe;
pen bgray = gray(0.5)+opacity(0.7);
pen dgray = gray(0.2);
pen mgray = gray(0.4)+opacity(0.8);
pen wgray = gray(0.3)+opacity(0.5);
pen lgray = gray(0.9)+opacity(0.6);


// Material for the curves.
pipe = material(diffusepen=black, emissivepen=gray(0.2), specularpen=gray(0.2));

// Draw the walls.
g = (0.0,     0.0, 0.0)--
    (xlength, 0.0, 0.0)--
    (xlength, 0.0, 2*zlength)--
    (0.0,     0.0, 2*zlength)--cycle;

s = surface(g, planar=true);
draw(s, wgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (0.0, 0.0,     0.0)--
    (0.0, ylength, 0.0)--
    (0.0, ylength, 2*zlength)--
    (0.0, 0.0,     2*zlength)--cycle;

s = surface(g, planar=true);
draw(s, wgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (xlength, ylength, 0.0)--
    (xlength, ylength, 2*zlength)--
    (xlength, 0.0,     2*zlength)--
    (xlength, 0.0,     0.0)--cycle;

s = surface(g, planar=true);
draw(s, wgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (xlength, ylength, 0.0)--
    (0.0,     ylength, 0.0)--
    (0.0,     ylength, 2*zlength)--
    (xlength, ylength, 2*zlength)--cycle;

s = surface(g, planar=true);
draw(s, wgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

// Draw the basement.
g = (0.0,     0.0,     0.0)--
    (xlength, 0.0,     0.0)--
    (xlength, ylength, 0.0)--
    (0.0,     ylength, 0.0)--cycle;

guide3 p2 = (boxxstart,          ylength-boxystart,          0.0)--
            (boxxstart+boxwidth, ylength-boxystart,          0.0)--
            (boxxstart+boxwidth, ylength-boxystart-boxwidth, 0.0)--
            (boxxstart,          ylength-boxystart-boxwidth, 0.0)--cycle;

s = surface(g^^p2, planar=true);
draw(s, dgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

// Draw the roof.
g = (0.0,     0.0,     2*zlength)--
    (xlength, 0.0,     2*zlength)--
    (xlength, ylength, 2*zlength)--
    (0.0,     ylength, 2*zlength)--cycle;

g3 = (boxxstart,          boxystart,          2*zlength)--
     (boxxstart+boxwidth, boxystart,          2*zlength)--
     (boxxstart+boxwidth, boxystart+boxwidth, 2*zlength)--
     (boxxstart,          boxystart+boxwidth, 2*zlength)--cycle;

s = surface(reverse(g)^^g3, planar=true);
draw(s, lgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

// Draw the second floor.
g = (0.0,     0.0,         zlength)--
    (xlength, 0.0,         zlength)--
    (xlength, 0.5*ylength, zlength)--
    (0.0,     0.5*ylength, zlength)--cycle;
g3 = (boxxstart,          boxystart,          2*zlength)--
     (boxxstart+boxwidth, boxystart,          2*zlength)--
     (boxxstart+boxwidth, boxystart+boxwidth, 2*zlength)--
     (boxxstart,          boxystart+boxwidth, 2*zlength)--cycle;

s = surface(reverse(g)^^g3, planar=true);
draw(s, mgray, render(merge=true));

s=reflect((0.0, 0.5*ylength, 0.0),
          (xlength, 0.5*ylength, 0.0),
          (0.5*xlength, 0.5*ylength, zlength))*s;
draw(s, mgray, render(merge=true));

// Draw the boxes.
path section=scale(0.003)*unitcircle;
pipe = material(diffusepen=black+0.3*white,
                emissivepen=gray(0.2),
                specularpen=gray(0.2));

g = (0.5*xlength, 0.0,       zlength)--
    (0.5*xlength, boxystart, zlength)--
    (0.5*xlength, boxystart, 2*zlength)--
    (0.5*xlength, 0.0,       2*zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (boxxstart,          boxystart, zlength)--
    (boxxstart+boxwidth, boxystart, zlength)--
    (boxxstart+boxwidth, boxystart, 2*zlength)--
    (boxxstart,          boxystart, 2*zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = shift(0.0, boxwidth, 0.0)*g;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (boxxstart, boxystart,          zlength)--
    (boxxstart, boxystart+boxwidth, zlength)--
    (boxxstart, boxystart+boxwidth, 2*zlength)--
    (boxxstart, boxystart,          2*zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = shift(boxwidth, 0.0, 0.0)*g;

draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (boxxstart,          ylength-boxystart, 0.0)--
    (boxxstart+boxwidth, ylength-boxystart, 0.0)--
    (boxxstart+boxwidth, ylength-boxystart, zlength)--
    (boxxstart,          ylength-boxystart, zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = shift(0.0, -boxwidth, 0.0)*g;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (boxxstart, ylength-boxystart,          0.0)--
    (boxxstart, ylength-boxystart-boxwidth, 0.0)--
    (boxxstart, ylength-boxystart-boxwidth, zlength)--
    (boxxstart, ylength-boxystart,          zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = shift(boxwidth, 0.0, 0.0)*g;

draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));

g = (0.5*xlength, ylength,           0.0)--
    (0.5*xlength, ylength-boxystart, 0.0)--
    (0.5*xlength, ylength-boxystart, zlength)--
    (0.5*xlength, ylength,           zlength)--cycle;

s=surface(g, planar=true);
draw(s, bgray, render(merge=true));
draw(tube(g, section), surfacepen=pipe, render(merge=true));
