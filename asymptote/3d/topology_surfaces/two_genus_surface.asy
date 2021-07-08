// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;

settings.render=8;

currentprojection=perspective(camera = (20, 80, 30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(256);

// Pen for drawing.
pen dpen = black+linewidth(1.5pt);

// Scalez for the x and x axis.
real xscale = 1.0;
real zscale = 1.5;
real h = 0.03;

// Variables used through.
real SQRT_H     = sqrt(h);
real RCP_SQRT_Z = 1.0/sqrt(zscale);
real RCP_X      = 1.0/xscale;

real xshift = sqrt(0.5*(1-sqrt(1.0-4.0*SQRT_H)))*RCP_X;
real yshift = sqrt(SQRT_H);
real zshift = SQRT_H*RCP_SQRT_Z;

real xfactor = sqrt(0.5*(1+sqrt(1.0+4.0*SQRT_H)));

// Radius of the dot.
real R = 0.02;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

real sign(real x){
    if (x == 0.0) return 0.0;
    else return x/abs(x);
}

// Lemniscate of Gerono
real lem2(real x, real y){
    real u = xscale*x;
    return u^4 - u^2 + y^2;
}

// Surface to draw.
real f(real x, real y, real z) {return lem2(x, y)^2+zscale*z^2-h;}

surface s = implicitsurface(f, a=(-1.2, -1, -0.4), b=( 1.2,  1,  0.4));

draw(s, surfacepen=blob, render(merge=true));
