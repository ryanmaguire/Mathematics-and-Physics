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
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));
}

// One light source
currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {0.25*X+0.25*Y+Z});

material pipe = material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.20),
                         specularpen = gray(0.20));

path3 p=graph(f, 0, 2pi, n=1000, operator ..);
draw(tube(p, scale(0.35)*unitcircle), surfacepen=pipe, light=currentlight);
