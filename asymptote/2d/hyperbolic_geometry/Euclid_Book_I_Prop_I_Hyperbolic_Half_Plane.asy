// Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in your
// ASYMPTOTE_DIR environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _complex;
import _custom_arrows;
import _euclidean;
import graph;

// Size of the output figure.
size(128);

int samples = 100;

pair A, B;
pair C1, C2, C3;
pair D1, D2, D3;
pair CenterA, CenterB;
pair inter;
path g;

pair[] Intersections;

real xmin, xmax;
real ymin, ymax;
real r1, r2;

xmin = -0.8;
ymin = -0.8;
xmax = 6.0;
ymax = 6.0;

A = scale(2.0)*expi(3pi/4);
B = scale(1.5)*expi(pi/3);

pair A = (1.5, 1.0);
pair B = (2.5, 2.0);

pair c1(real t){return HyperbolicCirclePoincarePlane(t, A, B);}
pair c2(real t){return HyperbolicCirclePoincarePlane(t, B, A);}

C1 = c1(0.0);
C2 = c1(1.0);
C3 = c1(2.0);

D1 = c2(0.0);
D2 = c2(1.0);
D3 = c2(2.0);

CenterA = FindCenter2D(C1, C2, C3);
CenterB = FindCenter2D(D1, D2, D3);

r1 = EuclideanNorm2D(C1 - CenterA);
r2 = EuclideanNorm2D(D1 - CenterB);

Intersections = CircleIntersection(CenterA, r1, CenterB, r2);

inter = Intersections[1];

pair c3(real t){return HyperbolicPathPoincarePlane(t, A, B);}
pair c4(real t){return HyperbolicPathPoincarePlane(t, B, inter);}
pair c5(real t){return HyperbolicPathPoincarePlane(t, inter, A);}

draw(graph(c1, 0, 2pi, 100, operator ..), thinp);
draw(graph(c2, 0, 2pi, 100, operator ..), thinp);

path q1=graph(c3, 0, 1, 100, operator ..);
path q2=graph(c4, 0, 1, 100, operator ..);
path q3=graph(c5, 0, 1, 100, operator ..);
path g=q1--q2--q3--cycle;
filldraw(g, green, thinp);

draw((xmin, 0.0)--(xmax, 0.0), SharpArrow(arsize));
draw((0.0, xmin)--(0.0, ymax), SharpArrow(arsize));

filldraw(circle(A, 0.04), black);
filldraw(circle(B, 0.04), black);
filldraw(circle(inter, 0.04), black);

label("$A$", A, S);
label("$B$", B, E);
label("$C$", inter, W);

