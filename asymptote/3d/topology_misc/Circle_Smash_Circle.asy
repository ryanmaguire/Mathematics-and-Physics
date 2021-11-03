import graph3;
import tube;

// Specify the camera setup and light.
currentprojection=perspective(camera=(-10,100,30),up=(0,0,1),target=(-10,0,0));

// Size of the output figure.
size(256);

// Radii of the torus and width of the contour pipes.
real R = 4;
real a = 1;
real pipR = 0.05;

// Angles for the contour lines.
real theta0 = 3pi/4;
real theta1 = pi;

// Number of samples in the figure, and variables used for drawing.
int samples = 24;
surface s;
path3 q1, q2;

material blob = material(
    diffusepen=gray(0.7),
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

material redpipe = material(
    diffusepen=red,
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

material bluepipe = material(
    diffusepen=blue+0.3*green,
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

/*  The equation for a torus centered at the origin with inner radius iR and  *
 *  outer radius oR. The pair t should lie in [0,2pi]x[0,2pi]                 */
triple TorusEquation(pair t, real iR, real oR)
{
    return ((oR+iR*cos(t.y))*cos(t.x), (oR+iR*cos(t.y))*sin(t.x), iR*sin(t.y));
}

// Create three functions based on the torus.
triple f(pair t){return TorusEquation(t, a, R);}
triple g(pair t){return TorusEquation(t, a, a);}
triple h(pair t) {
    real D = sin((t.x-theta0)/2);
    return (a*D*(D+cos(t.y))*cos(t.x), a*D*(D+cos(t.y))*sin(t.x), a*D*sin(t.y));
}

// Functions for drawing contour lines.
triple c0(real t){return f((theta0, t));}
triple c1(real t){return f((t, theta1));}
triple c2(real t){return g((theta0, t));}

// Transforms for shifting and scaling.
transform3 T1 = shift(-8, 0, 0);
transform3 T2 = shift(-13, 0, 0);
transform S1 = scale(pipR);

// Draw everything.
s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
q1 = graph(c0, 0, 2pi, 100, operator ..);
q2 = graph(c1, 0, 2pi, 400, operator ..);
draw(s, surfacepen=blob, render(merge=true));
draw(tube(q1, S1*unitcircle), surfacepen=redpipe, render(merge=true));
draw(tube(q2, S1*unitcircle), surfacepen=bluepipe, render(merge=true));

s = surface(g, (0,0), (2pi,2pi), samples, samples, Spline);
q1 = graph(c2, 0, 2pi, 100, operator ..);
draw(T1*s, surfacepen=blob, render(merge=true));
draw(T1*tube(q1, S1*unitcircle), surfacepen=redpipe, render(merge=true));

s = surface(h, (0,0), (2pi,2pi), samples, samples, Spline);
draw(shift(-13, 0, 0)*s, surfacepen=blob, render(merge=true));