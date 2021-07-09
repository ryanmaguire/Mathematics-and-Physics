import settings;
import tube;
import graph3;
import palette;
settings.render=8;

size(128);

currentprojection=perspective(camera = (0, 0, 100), up   = (0, 0, 1),
                              target = (0, 0, 0),   zoom = 0.85);

triple f(real t)
{
    return (t*t - 1.0, t*t*t - t, t);
}

triple g(real t)
{
    return (2.0, t, 0.0);
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material pipe = material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.20),
                         specularpen = gray(0.20));

path3 p=graph(f, -1.4, 1.4, n=500, operator ..);
path3 q=graph(g, -1.6, 1.6, n=2, operator --);
draw(tube(p, scale(0.15)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(q, scale(0.15)*unitcircle), surfacepen=pipe, light=currentlight);
