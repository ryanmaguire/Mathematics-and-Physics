// Boilerplate stuff.
import settings;
import graph3;
import tube;
settings.render = 8;
settings.outformat = "pdf";
size(128);

currentprojection = orthographic(4, 0, 1);

currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {X+Y+Z}
);

material blob = material(
    diffusepen = blue + 0.15*green,
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

real R = 5;
real a = 1;
real b = 0.05;
int samples = 24;
surface s;

triple g(pair t) {
    return ((R+a*cos(t.y)*sin(t.x/2))*cos(t.x),
            (R+a*cos(t.y))*sin(t.x),
            sin(t.x/2)*a*sin(t.y));
}

// Squished torus.
s = surface(g, (0, 0), (2pi, 2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));
