import settings;
import tube;
import graph3;
settings.render = 8;
settings.outformat = "pdf";

/*  Size of the image. Make this a power of 2 to avoid horizontal black lines.*/
size(256);

/*  Camera setup.                                                             */
currentprojection = orthographic(0, 1.0, 0.0);

/*  Light source and setup.                                                   */
currentlight = light(
    diffuse  = new pen[]    {white},
    specular = new pen[]    {white},
    position = new triple[] {(1.0, 2.0, 10.0)}
);

/*  Number of samples used for constructing the knot.                         */
int samples = 100;

/*  Parameterization of a Legendrian embedding of the unknot.                 */
triple f(real t)
{
    real u = cos(t);
    real v = sin(t);
    real y = -3.0*u*v;
    real z = v*v*v;
    return (u, y, z);
}

/*  Material the knot is made of.                                             */
material pipe = material(
    diffusepen  = blue+0.25*green,
    emissivepen = gray(0.20),
    specularpen = gray(0.20)
);

/*  Create the path from the parameteric equation.                            */
path3 p = graph(f, 0.0, 2.0*pi, n=samples, operator ..);

/*  Draw in the knot.                                                         */
draw(tube(p, scale(0.1)*unitcircle), surfacepen=pipe, light=currentlight);
