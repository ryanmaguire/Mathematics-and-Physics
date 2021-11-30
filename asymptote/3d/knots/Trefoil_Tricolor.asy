import settings;
import tube;
import graph3;
import palette;
settings.render=8;
settings.outformat = "pdf";

size(128);

currentprojection=perspective(
    camera  = (0,0,-25),
    up      = (0,1,0),
    target  = (0,0,0),
    zoom    = 0.85
);

triple f(real t){
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t), sin(3*t));
}

currentlight = light(
    diffuse  = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {100Z}
);

path section=scale(0.35)*unitcircle;

path3 p1=graph(f,  3pi/13,  32pi/35, n=350, operator ..);
path3 p2=graph(f, 32pi/35,  30pi/19, n=350, operator ..);
path3 p3=graph(f, 30pi/19,  29pi/13, n=350, operator ..);

draw(tube(p1, section), light = currentlight,
     surfacepen = material(diffusepen = green,
                          emissivepen = gray(0.2),
                          specularpen = gray(0.2)));

draw(tube(p2, section), light = currentlight,
     surfacepen = material(diffusepen = red,
                          emissivepen = gray(0.2),
                          specularpen = gray(0.2)));

draw(tube(p3, section), light=currentlight,
     surfacepen=material(diffusepen  = blue+0.3*green,
                         emissivepen = gray(0.2),
                         specularpen = gray(0.2)));
