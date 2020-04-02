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

// Size of the output figure.
size(256);

// Samples for the paths.
int samples = 200;

// Materials used throughout.
material blob, pipe;

// Function for the xy plane.
triple XYPlane(pair t){
    return (t.x, t.y, 0);
}

// The function we are mapping the circle into.
triple bot(real theta){
    real u = cos(1.5*theta);
    u  = 1.0+u*u;
    u *= 0.5;
    real x = u*cos(theta);
    real y = u*sin(theta);
    return (x, y, 0.0);
}

// The circle at the top of the mapping cylinder.
triple top(real theta){
    real x = cos(theta);
    real y = sin(theta);
    return (x, y, 1.0);
}

// The mapping cylinder.
triple f(pair H) {
    real theta = H.x;
    real t     = H.y;
    triple A = top(theta);
    triple B = bot(theta);

    return A*t+(1.0-t)*B;
}


// Material for the xy plane.
blob = material(diffusepen=gray(0.8)+opacity(0.3),
                emissivepen=gray(0.2),
                specularpen=gray(0.1));

// Material for the curves.
pipe = material(diffusepen  = blue+0.3*green,
                emissivepen = gray(0.20),
                specularpen = gray(0.20));


// Draw the xy plane.
surface s=surface(XYPlane, (-1.3, -1.3), (1.3, 1.3), 20, 20, Spline);
draw(s, surfacepen=blob, meshpen=black, render(merge=true));

blob = material(diffusepen=gray(0.7)+opacity(0.8),
                emissivepen=gray(0.2),
                specularpen=gray(0.2));

s=surface(f, (0, 0), (2pi, 1), 20, 10, Spline);
draw(s, opacity(0.0), meshpen=black+linewidth(0.07pt), render(merge=true));

s=surface(f, (0, 0), (2pi, 1), samples, 20, Spline);
draw(s, surfacepen=blob, render(merge=true));

pipe = material(diffusepen=blue+0.3*green,
                emissivepen=gray(0.4),
                specularpen=gray(0.1));

path3 p=graph(bot, 0, 2pi, n=samples, operator ..);
draw(tube(p, scale(0.02)*unitcircle), surfacepen=pipe, render(merge=true));

pipe = material(diffusepen=red,
                emissivepen=gray(0.4),
                specularpen=gray(0.1));

path3 p=graph(top, 0, 2pi, n=samples, operator ..);
draw(tube(p, scale(0.02)*unitcircle), surfacepen=pipe, render(merge=true));
