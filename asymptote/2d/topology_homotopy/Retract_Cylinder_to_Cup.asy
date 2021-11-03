// Seting output format to "pdf".
import settings;
import custom_arrows;
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

pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");

real x = 1.0;
real y = 1.0;
real e = 0.2;
real rdot = 0.01;
real arsize = 4bp;

margin margins = TrueMargin(0, 0.1cm);

pair proj_func(pair P){
    real a;
    if ((fabs(P.x) < P.y)) a = 1.0/fabs(P.x);
    else a = 2/(2-P.y);
    return scale(a)*P + scale(1-a)*(0, 2);
}

pair A = (-x, 0);
pair B = (x, 0);
pair C = (x, y);
pair D = (-x, y);

pair S1 = MidPoint2D(A, B);
pair S2 = MidPoint2D(C, D);

pair O = (0, 2*y);
pair P1 = (0.7*x, 0.95*y);
pair P2 = proj_func(P1);
pair Q1 = (-0.5*x, 0.4*y);
pair Q2 = proj_func(Q1);

path g;

draw(P1--P2, SharpArrow(arsize), margins);
draw(Q1--Q2, SharpArrow(arsize), margins);

g = scale(1, e)*arc(S1, x, 180, 360)--C--
    reverse(shift(MidPoint2D(C, D))*(scale(1, e)*arc(S1, x, 180, 360)))--cycle;

axialshade(g, gray(0.2)+opacity(0.7), (S2.x, S2.y+y), gray(0.9), (S1.x, S1.y-y));
draw(g, spen);
g = scale(1, e)*arc(MidPoint2D(A, B), x, 0, 180);
draw(g, dpen);

g = ellipse(S2, 1, e);
draw(g, spen);
axialshade(g, gray(0.2)+opacity(0.7), (S2.x, S2.y+y), gray(0.9), (S2.x, S2.y-y));

draw(O--P1);
draw(O--Q1);

filldraw(circle(P1, rdot), black);
filldraw(circle(P2, rdot), black);
filldraw(circle(Q1, rdot), black);
filldraw(circle(Q2, rdot), black);
filldraw(circle(O, rdot), black);

label("$\textrm{Cl}(\mathbb{B}^{n})\times{I}$", (-1.1*x, 1.15y), fontsize(9pt));
label("$P$", P1, W, fontsize(9pt));
label("$f(P)$", P2, E, fontsize(9pt));
label("$Q$", Q1, NW, fontsize(9pt));
label("$f(Q)$", Q2, SE, fontsize(9pt));
label("$(\mathbf{0},2)$", O, NE, fontsize(9pt));


