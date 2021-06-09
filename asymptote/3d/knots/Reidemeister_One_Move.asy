import settings;
import tube;
import graph3;
import palette;
settings.render=8;
outformat="pdf";

size(169, 169);

currentprojection=perspective(camera = (0, 0, 100), up   = (0, 0, 1),
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

path3 p=graph(f, -5, 6, n=1000, operator ..);
path3 q=graph(g, -5, 5, n=3, operator ..);
draw(tube(p, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
draw(tube(q, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
