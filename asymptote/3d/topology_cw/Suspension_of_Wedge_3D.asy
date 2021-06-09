// Boilerplate stuff.
import settings;
import tube;
import graph3;
import three;
import palette;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (0, 60, 20), up = (0, 0, 1),
                              target = (0,  0,  0), zoom = 0.85);

// Size of the output figure.
size(256);

int samplesx = 100;
int samplesy = 6;
material blob, pipe;

// Material for the xy plane.
blob = material(diffusepen=gray(0.7)+opacity(0.8),
                emissivepen=gray(0.2),
                specularpen=gray(0.1));

// Material for the curves.
pipe = material(diffusepen  = blue+0.3*green,
                emissivepen = gray(0.20),
                specularpen = gray(0.20));

triple LineSegment(real t, triple A, triple B){
    return scale(t, t, t)*A + scale(1-t, 1-t, 1-t)*B;
}

triple f(pair t){
    triple P;
    triple A = (cos(t.x)+1, sin(t.x), 0);
    real lambda = fabs(t.y);
    P = (0, 0, 1);
    return LineSegment(lambda, A, P);
}

surface s = surface(f, (0, -1), (2pi, 1), samplesx, samplesy);
draw(s, surfacepen=blob, meshpen=black+linewidth(0.1));

s = reflect((0, 0, 0), (0, 1, 0), (1, 0, 0))*s;
draw(s, surfacepen=blob, meshpen=black+linewidth(0.1));

s = reflect((0, 0, 0), (0, 1, 0), (0, 0, 1))*s;
draw(s, surfacepen=blob, meshpen=black+linewidth(0.1));

s = reflect((0, 0, 0), (0, 1, 0), (1, 0, 0))*s;
draw(s, surfacepen=blob, meshpen=black+linewidth(0.1));
