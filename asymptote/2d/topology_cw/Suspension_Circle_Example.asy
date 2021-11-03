// Seting output format to "pdf".
import settings;
texpreamble("\usepackage{amssymb}");
settings.outformat = "pdf";

// Size of the output.
size(128);

/* Find midpoint given two points in the plane.                               */
pair MidPoint2D(pair A, pair B)
{
    /*  Compute the midpoint of A and B using the midpoint formula and return.*/
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    return (x, y);
}

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");
pen dotf = red;
pen dotc = black+linewidth(0.2);

real r = 1;
real rdot = 0.02;
real e = 0.06;
real fsize = 9pt;

pair O = (0, 0);
pair A = (-r, 0);
pair B = (0, r);
pair C = (r, 0);
pair D = (0, -r);

draw(A--B--C--D--cycle);
draw(scale(1, e)*arc(O, r, 180, 360), spen+blue);
draw(scale(1, e)*arc(O, r, 0, 180), dpen+blue);
draw(shift(MidPoint2D(O, B))*(scale(0.5, e)*arc(O, r, 180, 360)), spen);
draw(shift(MidPoint2D(O, B))*(scale(0.5, e)*arc(O, r, 0, 180)), dpen);
draw(shift(MidPoint2D(O, D))*(scale(0.5, e)*arc(O, r, 180, 360)), spen);
draw(shift(MidPoint2D(O, D))*(scale(0.5, e)*arc(O, r, 0, 180)), dpen);

label("$\mathbb{S}^{1}$", C, NE, fontsize(fsize));
label("$S\mathbb{S}^{1}$", MidPoint2D(A, B), NW, fontsize(fsize));

filldraw(circle(B, rdot), dotf, dotc);
filldraw(circle(D, rdot), dotf, dotc);


