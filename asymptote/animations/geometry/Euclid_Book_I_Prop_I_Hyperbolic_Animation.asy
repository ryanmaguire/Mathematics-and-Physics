import settings;
if(settings.render < 0)
    settings.render = 4;

if(!settings.multipleView)
    settings.batchView = false;

settings.outformat   = "gif";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;
settings.bw          = false;
settings.cmyk        = false;
viewportmargin       = (2, 2);

// Pen used for labels and drawing.
defaultpen(black+linewidth(0.5pt)+fontsize(10pt));

// Default size of arrowheads.
real arsize = 5bp;

// Needed for the use of mathbb and mathcal commands.
texpreamble("\usepackage{amssymb}");

// Commonly used pens.
pen thinp  = black + linewidth(0.3pt);

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import _euc_geo_2d;
import _complex_math;
import graph;
import animation;

// Size of the output figure.
size(512);

int images = 50;
int samples = 50;
int i;

real dx = 1.0/images;
real rDot = 0.015;

pair A, B;
pair Q1, Q2, Q3;
pair P1, P2, P3;
pair C1, C2, C3;
pair D1, D2, D3;
pair CenterQ1, CenterQ2;

pair[] Intersections;

real radius, r1, r2, t;

path g;

animation a;

A = scale(2.0)*expi(3pi/4);
B = scale(1.5)*expi(pi/3);

Q1 = PlaneToDisk(A);
Q2 = PlaneToDisk(B);

P2 = MobiusTransform(Q2, Q1);

radius = EucNormTwo(P2);

C1 = HyperbolicCircle(Q1, radius, 0.0);
C2 = HyperbolicCircle(Q1, radius, 1.0);
C3 = HyperbolicCircle(Q1, radius, 2.0);
CenterQ1 = FindCenterTwo(C1, C2, C3);

D1 = HyperbolicCircle(Q2, radius, 0.0);
D2 = HyperbolicCircle(Q2, radius, 1.0);
D3 = HyperbolicCircle(Q2, radius, 2.0);
CenterQ2 = FindCenterTwo(D1, D2, D3);

r1 = EucNormTwo(CenterQ1-Q2);
r2 = EucNormTwo(CenterQ2-Q1);
Intersections = CircleCircleIntersection(CenterQ1, r1, CenterQ2, r2);

assert(!isnan(Intersections[0].x));
Q3 = Intersections[1];

pair center = FindCenterTwo(Q1, Q2, Q3);

P1 = MobiusTransform(Q1, center);
P2 = MobiusTransform(Q2, center);
P3 = MobiusTransform(Q3, center);

pair Q1_to_P1(real t){return HyperbolicPath(t, Q1, P1);}
pair Q2_to_P2(real t){return HyperbolicPath(t, Q2, P2);}
pair Q3_to_P3(real t){return HyperbolicPath(t, Q3, P3);}

for (i=0; i<images; ++i)
{
    save();
    t = i*dx;

    C1 = Q1_to_P1(t);
    C2 = Q2_to_P2(t);
    C3 = Q3_to_P3(t);

    pair path_1(real t){return HyperbolicPath(t, C1, C2);}
    pair path_2(real t){return HyperbolicPath(t, C2, C3);}
    pair path_3(real t){return HyperbolicPath(t, C3, C1);}

    g = graph(path_1, 0, 1, samples, operator ..);
    g = g--graph(path_2, 0, 1, samples, operator ..);
    g = g--graph(path_3, 0, 1, samples, operator ..);
    g = g--cycle;

    draw(circle((0, 0), 1));
    filldraw(g, green, thinp);
    filldraw(circle(C1, rDot), black);
    filldraw(circle(C2, rDot), black);
    filldraw(circle(C3, rDot), black);

    a.add();
    restore();
}

for (i=0; i<3; ++i)
{
    save();
    draw(circle((0, 0), 1));
    filldraw(g, green, thinp);
    filldraw(circle(C1, rDot), black);
    filldraw(circle(C2, rDot), black);
    filldraw(circle(C3, rDot), black);

    a.add();
    restore();
}

// Render the gif.
write("Rendering GIF...");
a.movie(delay=40);
