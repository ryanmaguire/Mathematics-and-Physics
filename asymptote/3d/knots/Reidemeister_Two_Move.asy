import settings;
import tube;
import graph3;
import palette;
settings.render=8;

size(169, 169);

currentprojection=perspective(camera = (0, 0, 100), up   = (0, 0, 1),
                              target = (0, 0, 0),   zoom = 0.85);

triple f0(real t)
{
    return (0.6*t*t, t, 0.0);
}

triple f1(real t)
{
    return (1-0.6*t*t, t, 1.0);
}

triple g0(real t)
{
    return (4.0, t, 0.0);
}

triple g1(real t)
{
    return (5.5, t, 0.0);
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material pipe = material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.20),
                         specularpen = gray(0.20));

path3 p=graph(f0, -1.5, 1.5, n=10, operator ..);
path3 q=graph(f1, -1.5, 1.5, n=10, operator ..);
draw(tube(p, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(q, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);

path3 p=graph(g0, -1.5, 1.5, n=10, operator ..);
path3 q=graph(g1, -1.5, 1.5, n=10, operator ..);
draw(tube(p, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(q, scale(0.2)*unitcircle), surfacepen=pipe, light=currentlight);
