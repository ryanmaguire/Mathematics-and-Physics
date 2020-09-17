// Boilerplate stuff.
import settings;
import smoothcontour3;
import graph3;
import _euc_geo_2d;
import _euc_geo_3d;
import three;

if(!settings.multipleView)
    settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (100, 50, 20), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Pen for drawing.
pen dpen = black+linewidth(1.0pt);
pen bpen = blue+linewidth(0.5pt);
pen rpen = red+linewidth(0.5pt);

// Size of the output figure.
size(128);

triple A = SphericalToRect(0.0, pi/2);
triple B = SphericalToRect(pi/4, pi/2);

triple c1(real t){return spherical_circle(t, A, B);}
triple c2(real t){return spherical_circle(t, B, A);}

radialshade(
    project(
        circle((0,0,0), 1, currentprojection.camera-currentprojection.target)
    ),
    rgb(0.8,0.8,0.8), project(O), 1.0,
    rgb(0.9,0.9,0.9), project(O), 0.2
);

guide3 q1 = graph(c1, -pi, pi, 100, operator ..);
draw(project(q1));
guide3 q1 = graph(c2, -pi, pi, 100, operator ..);
draw(project(q1));

pair C1, C2, C3, D1, D2, D3;

C1 = StereographicProjection(c1(0.0));
C2 = StereographicProjection(c1(1.0));
C3 = StereographicProjection(c1(2.0));
D1 = StereographicProjection(c2(0.0));
D2 = StereographicProjection(c2(1.0));
D3 = StereographicProjection(c2(2.0));

pair CenterA, CenterB;

CenterA = FindCenterTwo(C1, C2, C3);
CenterB = FindCenterTwo(D1, D2, D3);

real r1 = EucNormTwo(CenterA - C1);
real r2 = EucNormTwo(CenterB - D1);

pair[] Intersections = CircleCircleIntersection(CenterA, r1, CenterB, r2);

if (!isnan(Intersections[0].x))
{
    triple SphereIntersection;
    SphereIntersection = InverseStereographicProjection(Intersections[0]);

    triple c3(real t){return great_circle(t, A, B);}
    triple c4(real t){return great_circle(t, B, SphereIntersection);}
    triple c5(real t){return great_circle(t, SphereIntersection, A);}

    guide3 q1=graph(c3, 0, -1, 100, operator ..);
    guide3 q2=graph(c4, 0, -1, 100, operator ..);
    guide3 q3=graph(c5, 0, -1, 100, operator ..);
    guide3 g=q1--q2--q3--cycle;
    filldraw(project(g), green);

    dot(project(A));
    dot(project(B));
    dot(project(SphereIntersection));

    label("$A$", project(A), SW);
    label("$B$", project(B), SE);
    label("$C$", project(SphereIntersection), N);

}
