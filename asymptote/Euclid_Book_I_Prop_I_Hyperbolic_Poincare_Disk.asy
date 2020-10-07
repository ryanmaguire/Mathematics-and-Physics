// Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in your
// ASYMPTOTE_DIR environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _euclidean;
import _complex;
import graph;

// Size of the output figure.
size(128);

int samples = 100;

pair A, B;
pair P, Q;
pair P_TranQ;
pair C1, C2, C3;
pair D1, D2, D3;
pair CenterP, CenterQ;

pair[] Intersections;

real radius, r1, r2;

path g;

A = scale(2.0)*expi(3pi/4);
B = scale(1.5)*expi(pi/3);

P = PlaneToDisk(A);
Q = PlaneToDisk(B);

P_TranQ = MobiusTransform(P, Q);

radius = EuclideanNorm2D(P_TranQ);

C1 = HyperbolicCircle(P, radius, 0.0);
C2 = HyperbolicCircle(P, radius, 1.0);
C3 = HyperbolicCircle(P, radius, 2.0);
CenterP = FindCenter2D(C1, C2, C3);

D1 = HyperbolicCircle(Q, radius, 0.0);
D2 = HyperbolicCircle(Q, radius, 1.0);
D3 = HyperbolicCircle(Q, radius, 2.0);
CenterQ = FindCenter2D(D1, D2, D3);

r1 = EuclideanNorm2D(CenterP-Q);
r2 = EuclideanNorm2D(CenterQ-P);

Intersections = CircleCircleIntersection(CenterP, r1, CenterQ, r2);

assert(!isnan(Intersections[0].x));

pair circle_P(real theta){return HyperbolicCircle(P, radius, theta);}
pair circle_Q(real theta){return HyperbolicCircle(Q, radius, theta);}
pair path_PQ(real t){return HyperbolicPath(t, P, Q);}
pair path_QI(real t){return HyperbolicPath(t, Q, Intersections[1]);}
pair path_IP(real t){return HyperbolicPath(t, Intersections[1], P);}

g = graph(path_PQ, 0, 1, samples, operator ..);
g = g--graph(path_QI, 0, 1, samples, operator ..);
g = g--graph(path_IP, 0, 1, samples, operator ..);
g = g--cycle;

draw(circle((0, 0), 1));
draw(graph(circle_P, 0, 2pi, samples, operator ..), thinp);
draw(graph(circle_Q, 0, 2pi, samples, operator ..), thinp);

filldraw(g, green, thinp);
filldraw(circle(P, 0.015), black);
filldraw(circle(Q, 0.015), black);
filldraw(circle(Intersections[1], 0.015), black, black+linewidth(0.2pt));
filldraw(circle((0, 0), 0.015), black, black);

label("$A$", P, scale(2.0)*NW);
label("$B$", Q, scale(2.0)*NE);
label("$C$", Intersections[1], scale(2.8)*N);
label("$O$", (0, 0), SW);
