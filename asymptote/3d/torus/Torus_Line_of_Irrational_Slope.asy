/*  Boilerplate stuff.                                                        */
import settings;
import graph3;
import tube;

if(!settings.multipleView)
    settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

/*  Set up the camera and the orientation of the figure.                      */
currentprojection=perspective(camera = (20, 80, 25), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

/*  Size of the output figure.                                                */
size(256);

/*  Radii of the torus.                                                       */
real R = 4;
real a = 1;

/*  Set a constant for the golden ration phi = (1 + sqrt(5))/2.               */
real phi = 1.6180339887498948482045868343656381177203091798057628621354486227;

/*  Radius of the "pipe" wrapping around the torus.                           */
real pipR = 0.01;

/*  Number of samples used in the splining of the torus.                      */
int samples = 24;

/*  Material of the torus and the pipe.                                       */
material blob = material(diffusepen=gray(0.7)+opacity(0.85),
                         emissivepen=gray(0.1),
                         specularpen=gray(0.1));


material pipe = material(diffusepen=deepred,
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

/*  Parameterization of the torus.                                            */
triple f(pair t) {
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

/*  Line of slope phi on the torus.                                           */
triple g(real t)
{
    return f((phi*t, t));
}

surface s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

path3 q=graph(g, 0, 300, 2500, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe, render(merge=true));
