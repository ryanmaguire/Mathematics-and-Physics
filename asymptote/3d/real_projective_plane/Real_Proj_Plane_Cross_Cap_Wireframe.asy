// Boilerplate stuff.
import settings;
import graph3;
import palette;
import tube;

if(!settings.multipleView)  settings.batchView=false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;

viewportmargin = (2, 2);

currentprojection=perspective(camera = (20, 80, 30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

currentlight=light(
    diffuse = new pen[] {gray(0.38), gray(0.38), gray(0.38)},
    specular = new pen[] {gray(0.38), gray(0.38), gray(0.38)},
    specularfactor = 2.0,
    position = new triple[] {(-0.5,-0.25,0.45), (0.5,-0.5,0.5), (0.5,0.5,0.75)}
);

// Size of the created image.
size(128);

currentprojection=perspective(camera = (40, -30, 10), target = (0, 0, 0));

// Material for tubes.
material pipe = material(diffusepen = gray(0.7),
                         emissivepen = gray(0.2),
                         specularpen = gray(0.2));

// Cross section of tubes.
path section = scale(0.008)*unitcircle;

real R=1;
real N=3.6;
real H=2;
real P=1.9;

int samples = 40;

real theta;
real theta;

triple f(pair t) {
    real u = t.x;
    real v = t.y;
    return (sin(u)*sin(2*v)/2, sin(2*u)*(cos(v)^2), cos(2*u)*(cos(v)^2));
}

surface s=surface(f, (0, 0), (2pi, pi), 40, 40, Spline);
s.colors(palette(s.map(zpart), Gradient(blue, green)));

int i, j;
int n = 50;

for (i=0; i<n; ++i){
    theta = 2*pi*i/n;
    triple g0(real t){return f((theta, t));}
    triple g1(real t){return f((t, theta));}
    path3 p0 = graph(g0, 0, pi,  samples, operator ..);
    path3 p1 = graph(g1, 0, 2pi, samples, operator ..);
    draw(tube(p0, section), surfacepen=pipe, render(merge=true));
    draw(tube(p1, section), surfacepen=pipe, render(merge=true));
}

section = scale(0.01)*unitcircle;

i = 28;
theta = 2*pi*i/n;
triple g0(real t){return f((theta, t));}
triple g1(real t){return f((t, theta));}

pipe = material(diffusepen  = red,
                emissivepen = gray(0.4),
                specularpen = gray(0.2));

path3 p0 = graph(g0, 0, pi,  samples, operator ..);
draw(tube(p0, section), surfacepen=pipe, render(merge=true));

pipe = material(diffusepen  = blue+0.25*green,
                emissivepen = gray(0.4),
                specularpen = gray(0.2));
path3 p1 = graph(g1, 0, 2pi, samples, operator ..);
draw(tube(p1, section), surfacepen=pipe, render(merge=true));
