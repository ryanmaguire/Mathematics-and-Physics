// Seting output format to "pdf".
import settings;
texpreamble("\usepackage{amssymb}");

settings.outformat = "pdf";

// Size of the output.
size(256);

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

real rdot = 0.05;
real fsize = 9pt;

pair A1, A2, A3, A4, A5, A6;

pair A1 = (0, 0);
pair A2 = (0, 1);

draw(A1--A2, spen);
filldraw(circle(A1, rdot), red);
filldraw(circle(A2, rdot), blue);
label("$\mathbb{Z}_{1}*\mathbb{Z}_{1}$", A2, N, fontsize(fsize));

A1 = (1.5, 0);
A2 = (1.0, 1);
A3 = (2, 1);

draw(A2--A1--A3);
filldraw(circle(A1, rdot), red);
filldraw(circle(A2, rdot), blue);
filldraw(circle(A3, rdot), blue);
label("$\mathbb{Z}_{2}*\mathbb{Z}_{1}$",
      MidPoint2D(A2, A3), N, fontsize(fsize));

A1 = (3.0, 0.5);
A2 = (3.5, 0.0);
A3 = (4.0, 0.5);
A4 = (3.5, 1.0);

draw(A1--A2--A3--A4--cycle);
filldraw(circle(A1, rdot), red);
filldraw(circle(A2, rdot), blue);
filldraw(circle(A3, rdot), red);
filldraw(circle(A4, rdot), blue);
label("$\mathbb{Z}_{2}*\mathbb{Z}_{2}$", A4, N, fontsize(fsize));

A1 = (5.0, 1.0);
A2 = (5.5, 1.0);
A3 = (6.0, 1.0);
A4 = (5.0, 0.0);
A5 = (5.5, 0.0);
A6 = (6.0, 0.0);

draw(A1--A4--A2);
draw(A1--A5--A3);
draw(A1--A6--A2);
draw(A4--A3--A6);
draw(A2--A5);

filldraw(circle(A1, rdot), blue);
filldraw(circle(A2, rdot), blue);
filldraw(circle(A3, rdot), blue);
filldraw(circle(A4, rdot), red);
filldraw(circle(A5, rdot), red);
filldraw(circle(A6, rdot), red);
label("$\mathbb{Z}_{3}*\mathbb{Z}_{3}$", A2, N, fontsize(fsize));


