import settings;
import tube;
import graph3;
settings.render = 8;
settings.outformat = "pdf";

/*  Size of the image. Make this a power of 2 to avoid horizontal black lines.*/
size(256);

/*  Camera setup.                                                             */
currentprojection = perspective(0.0, 1.0, 5.0);

/*  Light source and setup.                                                   */
currentlight = light(
    diffuse  = new pen[]    {white},
    specular = new pen[]    {white},
    position = new triple[] {(1.0, 2.0, 10.0)}
);

/*  Parameters for drawing the rectangles along the curve.                    */
real dx = 0.2;
real dy = 0.2;
real dz = 0.2;

/*  Material the knot is made of.                                             */
material pipe = material(
    diffusepen  = blue+0.25*green,
    emissivepen = gray(0.20),
    specularpen = gray(0.20)
);

/*  Material the plane is made of.                                            */
material blob = material(
    diffusepen  = gray(0.6),
    emissivepen = gray(0.20),
    specularpen = gray(0.20)
);

/*  Function for drawing a rectangle at a given point.                        */
void draw_rectangle(triple center)
{
    triple v0 = (dx, 0.0, center.y*dz);
    triple v1 = (0.0, dy, 0.0);

    triple A0 = center + v0 + v1;
    triple A1 = center + v0 - v1;
    triple A2 = center - v0 - v1;
    triple A3 = center - v0 + v1;
    surface s = surface(A0 -- A1 -- A2 -- A3 -- cycle);
    draw(s, surfacepen=blob, light=currentlight, render(merge=true));
}
/*  End of draw_rectangle.                                                    */

/*  Number of samples used for constructing the knot.                         */
int samples = 100;
real dn = 2.0*pi / (real)(samples);

/*  Parameterization of a Legendrian embedding of the unknot.                 */
triple f(real t)
{
    real u = cos(t);
    real v = sin(t);
    real y = -3.0*u*v;
    real z = v*v*v;
    return (u, y, z);
}

/*  Create the path from the parameteric equation.                            */
path3 p = graph(f, 0.0, 2.0*pi, n=samples, operator ..);

/*  Draw in the knot.                                                         */
draw(tube(p, scale(0.05)*unitcircle), surfacepen=pipe, light=currentlight);

for (int n = 0; n < samples; n += 5)
    draw_rectangle(f(n*dn));
