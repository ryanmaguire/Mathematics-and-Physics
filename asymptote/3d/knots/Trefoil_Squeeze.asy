import _asy_preamble_3d;
import tube;

size(256, 256);

// Camera and light setups.
currentprojection=perspective(camera = (0, 0, 100), up   = (0, 0, 1),
                              target = (0, 0, 0),   zoom = 0.85);

currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

real angle1 = 30*pi/180;
real angle2 = 2pi-angle1;
real dr = pi/4;
real scalefact = 0.2;

real scalefunc(real u, real shift){
    return DoubleCutoff(u, angle1, angle1+dr, angle2-dr, angle2)+shift;
}

triple f(real t){
    return scalefunc(t, scalefact)*TrefoilEquation(t);
}

path3 p=graph(f, 0, 2pi, n=300, operator ..);
draw(tube(p, scale(0.15)*unitcircle), surfacepen=bluepipe, light=currentlight);
