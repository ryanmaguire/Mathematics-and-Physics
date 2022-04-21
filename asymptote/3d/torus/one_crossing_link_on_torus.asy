// Boilerplate stuff.
import settings;
import graph3;
import tube;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat = "pdf";

currentprojection=perspective(camera = (20, 80, 25), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Size of the output figure.
size(256);

// Pen for drawing.
pen dpenr = deepred+linewidth(1.2pt);
pen dpenb = deepblue+linewidth(1.2pt);

// Radii of the torus.
real R = 4;
real a = 1;

// Angles of the dot.
real theta0 = pi/4;
real theta1 = pi/2;

// Number of samples in the figure.
int samples = 24;

// Radius of the dot and pipes.
real dotR = 0.2;
real pipR = 0.05;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7)+opacity(0.85),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

material pipe0 = material(diffusepen=deepred,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe1 = material(diffusepen=deepblue,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

surface s;

triple f(pair t) {
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

// Some contour lines.
triple c0(real t){return f((theta0, t));}
triple c1(real t){return f((t, theta1));}

s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

draw(graph(c0, 0.55*pi, 2.45*pi, 100, operator ..), deepred, render(merge=true));
draw(graph(c1, 0, 2pi, 400, operator ..), deepblue, render(merge=true));

