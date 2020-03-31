// Boilder plate stuff for the image.
import settings;
import graph3;
import tube;
settings.render=8;
settings.outformat="pdf";

// Size of the output.
size(200);

// Location of the camera and object.
currentprojection=perspective(camera = (-30, 20, 20), target  = (0,  0,  0));

real R = 3;
real a = 1;

int samples = 52;

material pipe;
surface s;

triple f(pair t) {
     real x = (R+a*cos(t.y))*cos(t.x);
     real y = (R+a*cos(t.y))*sin(t.x);
     real z = a*sin(t.y);
     return (x, y, z);
}

s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, meshpen=gray(0.7)+linewidth(0.15pt), surfacepen=nullpen);

pipe = material(diffusepen  = red,
                emissivepen = gray(0.20),
                specularpen = gray(0.20));

draw(tube(shift(R, 0, 0)*reflect(O, X, Y+Z)*unitcircle3,
     scale(0.01)*unitcircle), surfacepen=pipe);

pipe = material(diffusepen  = blue+0.3*green,
                emissivepen = gray(0.20),
                specularpen = gray(0.20));

draw(tube(shift(0, 0, a)*(scale(R, R, 0)*unitcircle3), scale(0.01)*unitcircle),
     surfacepen=pipe);