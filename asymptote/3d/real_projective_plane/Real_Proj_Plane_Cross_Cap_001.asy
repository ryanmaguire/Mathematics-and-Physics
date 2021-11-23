// Boilerplate stuff.
import settings;
import graph3;
import palette;
settings.render      = 8;
settings.outformat   = "pdf";


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

real R=1;
real N=3.6;
real H=2;
real P=1.9;

triple f(pair t) {
    real u = t.x;
    real v = t.y;
    return (sin(u)*sin(2*v)/2, sin(2*u)*(cos(v)^2), cos(2*u)*(cos(v)^2));
}

surface s=surface(f, (0, 0), (2pi, pi), 40, 40, Spline);
s.colors(palette(s.map(zpart), Gradient(blue, green)));
draw(s, meshpen=black+linewidth(0.3pt), render(merge=true));
