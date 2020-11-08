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

/*  Radius of the "pipe" wrapping around the torus.                           */
real pipR = 0.04;

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
triple f(pair t)
{
    /*  Declare variables for the three coordinates.                          */
    real x, y, z;

    /*  Variables for precomputing cosine and sine to save computations.      */
    real cx, sx, cy, sy;

    /*  Compute the sines and cosines.                                        */
    cx = cos(t.x);
    cy = cos(t.y);
    sx = sin(t.x);
    sy = sin(t.y);

    /*  Use the standard parameterization for the torus.                      */
    x = (R + a*cy)*cx;
    y = (R + a*cy)*sx;
    z = a*sy;
    return (x, y, z);
}

/*  Line of slope 4/3 on the torus.                                           */
triple g(real t)
{
    return f((3*t, 4*t));
}

surface s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

path3 q=graph(g, 0, 2pi, 100, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe, render(merge=true));
