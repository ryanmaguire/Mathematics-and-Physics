// Boiler plate stuff.
import settings;
import tube;
import graph3;
settings.outformat   = "pdf";


// Size of output. Should be power of two or strange black lines appear. This
// problem seems device specific (Appears with Debian, not with OSX). Known
// issue with "graph3" module. Setting maxtile to (256, 256) seems to resolve
// this. Proceed with fingers crossed.
size(256);

// Camera setup.
currentprojection=perspective(
    camera  = (0, 0, 25),
    up      = (0, 0, 1),
    target  = (0, 0, 0),
    zoom    = 1.0
);

// Create light source.
currentlight = light(diffuse  = new pen[] {white},
                     specular = new pen[] {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

// Lavender Blue
currentlight.background = rgb(204, 212, 255);

// Material used for the band and boundary, respectively.
material blob = material(diffusepen  = blue+lightgreen,
                         emissivepen = gray(0.1),
                         specularpen = gray(0.1));

material pipe = material(diffusepen  = blue+lightgreen,
                         emissivepen = gray(0.32),
                         specularpen = gray(0.10));

// Function that parameterizes a trefoil.
triple f(real t){
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));
}

// "Furthest distance" function, draw a straight line from a given point on the
// trefoil to the point that is furthest away on the trefoil in the sense of the
// above parameterization. This occurs when x = y+pi.
triple surf(pair t) {
    return (t.x*f(t.y)+(1-t.x)*f(t.y+pi));
}

// Create the band and the boundary.
surface s = surface(surf, (0, 0), (1, 2pi), 10, 20, Spline);
path3 p   = graph(f, 0, 2pi, n=500, operator ..);

// Draw everything.
draw(s, render(merge=true), light=currentlight, surfacepen=blob);
draw(tube(p, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);
