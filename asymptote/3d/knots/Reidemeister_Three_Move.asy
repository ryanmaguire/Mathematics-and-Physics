import settings;
import tube;
import graph3;
import palette;
settings.render=8;

size(128);

currentprojection=orthographic(camera = (0, 0, 100), up   = (0, 0, 1),
                               target = (0, 0, 0),   zoom = 0.85);

triple f(real t){
    if (t < 0.0)
        return (1.0, t, 0.0);
    else if (t > 1.0)
        return (1.0, t-1.0, 1.0);
    else
        return (cos(2pi*t), sin(2pi*t), t);
}

triple g(real t)
{
    return (4.0, t, 0.0);
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material pipe = material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.20),
                         specularpen = gray(0.20));

path3 g0 = (0, 0, 0)--(5, 5, 0);
path3 g1 = (5, 0, 1)--(0, 5, 1);
path3 g2 = (-1, 1, 3)--(6, 1, 3);
draw(tube(g0, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(g1, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(g2, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);

path3 g0 = (07, 0, 0)--(12, 5, 0);
path3 g1 = (12, 0, 1)--(7, 5, 1);
path3 g2 = (6, 4, 3)--(13, 4, 3);
draw(tube(g0, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(g1, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(g2, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);