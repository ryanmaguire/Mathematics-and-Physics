// Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in your
// ASYMPTOTE_DIR environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _euc_geo_2d;
import _complex_math;
import _custom_arrows;
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

pair HyperbolicPathPoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x, y;

    x = A.x*(1.0-t) + B.x*t;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x+ c2)*(A.x + c2);

        y = sqrt(c1 - (x+c2)*(x+c2));
    }
    else
        y = A.y*(1.0-t) + B.y*t;

    return (x, y);
}

pair HyperbolicLinePoincarePlane(real t, pair A, pair B)
{
    pair C;
    pair P, Q, O;

    O = (0.0, 0.0);

    real x, dist;

    P = MidPointTwo(A, B);

    if (A.x != B.x)
    {
        C = (A.y-B.y, B.x-A.x);

        x = P.x - C.x*P.y/C.y;
        Q = (x, 0.0);
        dist = EucNormTwo(Q - A);

        return Q + scale(dist)*(cos(t), sin(t));
    }
    else
        return scale(1-t)*A + scale(t)*B;
}

pair HyperbolicCirclePoincarePlane(real t, pair A, pair B)
{
    real c1, c2;
    real x1, y1, x0, y, m, dist;

    pair center;

    x1 = B.x;
    y1 = B.y;

    x0 = A.x;
    if (A.x != B.x)
    {
        c2 = (B.y*B.y - A.y*A.y + B.x*B.x - A.x*A.x)/(2.0*(A.x - B.x));
        c1 = A.y*A.y + (A.x + c2)*(A.x + c2);

        m = -(x1 + c2)/sqrt(c1 - (x1+c2)*(x1+c2));

        y = y1 + m*(x0-x1);
        center = (x0, y);

        dist = EucNormTwo(center - B);

        return center + scale(dist)*(cos(t), sin(t));
    }
    else
        return A;
}

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

CenterA = FindCenterTwo(C1, C2, C3);
CenterB = FindCenterTwo(D1, D2, D3);

r1 = EucNormTwo(C1 - CenterA);
r2 = EucNormTwo(D1 - CenterB);

Intersections = CircleCircleIntersection(CenterA, r1, CenterB, r2);

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
