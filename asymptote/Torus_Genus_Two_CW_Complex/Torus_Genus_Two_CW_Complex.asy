// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

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
material blob = material(diffusepen=gray(0.7)+opacity(0.8),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
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

// Some contour lines.
triple c1(real t){
    real u  = cos(t);
    u       = sign(u)*sqrt(abs(u))*sqrt(SQRT_H);

    real v  = sin(t)*RCP_SQRT_Z*SQRT_H;
    return (0.0, u, v);
}

triple c2(real t){
    t = t % 2pi;
    bool positive;
    if (!((t>=0.5*pi) && (t<=1.5*pi))) positive = true;
    else {
        positive = false;
        t = pi - t;
    }
    real u  = cos(t);
    u = 0.5-0.5*sqrt(1.0-4.0*SQRT_H*u);

    if (positive) u = sqrt(abs(u))*RCP_X;
    else u = -1.0*sqrt(abs(u))*RCP_X;

    real v  = sin(t)*RCP_SQRT_Z*SQRT_H;
    return (u, 0.0, v);
}

triple c3(real t){
    real u = xfactor*cos(t);

    real v = SQRT_H-u^4+u^2;
    if (t<pi) v = sqrt(abs(v));
    else      v = -sqrt(abs(v));

    return (RCP_X*u, v, 0.0);
}

triple c4(real t){
    real factor = sqrt(0.25-SQRT_H);
    real u = sqrt(factor*cos(t)+0.5);

    real v = factor*sin(t);

    return (RCP_X*u, v, 0.0);
}

triple c5(real t){
    real factor = sqrt(0.25-SQRT_H);
    real u = -sqrt(factor*cos(t)+0.5);

    real v = factor*sin(t);

    return (RCP_X*u, v, 0.0);
}

surface s = implicitsurface(f, a=(-1.2, -1, -0.4), b=( 1.2,  1,  0.4));

draw(s, surfacepen=blob, render(merge=true));

path3 q=graph(c1, 0, 2pi, 100, operator ..);
draw(q, dpen, render(merge=true));

path3 q=graph(c2, 0, 2pi, 100, operator ..);
draw(q, dpen, render(merge=true));

path3 q=graph(c3, 0, 2pi, 200, operator ..);
draw(q, dpen, render(merge=true));

path3 q=graph(c4, 0, 2pi, 100, operator ..);
draw(q, dpen, render(merge=true));

path3 q=graph(c5, 0, 2pi, 100, operator ..);
draw(q, dpen, render(merge=true));

s = scale(R, R, R)*unitsphere;

draw(shift( xshift,  0.0,     0.0)*s,    surfacepen=orb, render(merge=true));
draw(shift(-xshift,  0.0,     0.0)*s,    surfacepen=orb, render(merge=true));
draw(shift(0.0,      yshift,  0.0)*s,    surfacepen=orb, render(merge=true));
draw(shift(0.0,     -yshift,  0.0)*s,    surfacepen=orb, render(merge=true));
draw(shift(0.0,      0.0,     zshift)*s, surfacepen=orb, render(merge=true));
draw(shift(0.0,      0.0,    -zshift)*s, surfacepen=orb, render(merge=true));