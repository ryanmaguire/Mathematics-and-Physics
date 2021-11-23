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

// Sphere with string coming out of poles.
path3 p  = (0, 0, R){(0, 0, 1)}..(0, 1.5*R, 0)..(0, 0, -R){(0, 0, 1)};
surface s2 = scale(R, R, R)*surface(unitsphere);
surface s1 = surface(tube(p, scale(0.1)*unitcircle, relstep=0.01));
draw(s2, surfacepen = blob, render(merge=true));
draw(s1, surfacepen = blob, render(merge=true));
