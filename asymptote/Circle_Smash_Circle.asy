// Boilerplate stuff.
import settings;
import graph3;
import tube;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (-10, 100, 30), up = (0, 0, 1), target = (-10, 0, 0));

currentlight=light(gray(0.38), specularfactor=1, viewport=true,
                   (100, 0, 25), (20, 100, 25), (0, 0, 1000)
);

// Size of the output figure.
size(256);

// Pen for drawing.
pen dpenr = deepred+linewidth(1.2pt);
pen dpenb = deepblue+linewidth(1.2pt);

// Radii of the torus.
real R = 4;
real a = 1;

// Angles of the dot.
real theta0 = 3pi/4;
real theta1 = pi;

// Number of samples in the figure.
int samples = 24;

// Radius of the dot and pipes.
real pipR = 0.05;

// Material of the pretzel and the sphere.
material blob = material(diffusepen=gray(0.7),
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe0 = material(diffusepen=red,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe1 = material(diffusepen=blue+0.3*green,
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

path3 q=graph(c0, 0, 2pi, 100, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe0, render(merge=true));

path3 q=graph(c1, 0, 2pi, 400, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe1, render(merge=true));

R = a;
triple f(pair t) {
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}
s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(shift(-8, 0, 0)*s, surfacepen=blob, render(merge=true));

path3 q=graph(c0, 0, 2pi, 100, operator ..);
draw(shift(-8, 0, 0)*tube(q, scale(pipR)*unitcircle), surfacepen=pipe0, render(merge=true));

triple f(pair t) {
    real D = sin((t.x-theta0)/2);
    real Rad = R*D;
    return (D*(Rad+a*cos(t.y))*cos(t.x),
            D*(Rad+a*cos(t.y))*sin(t.x),
            D*a*sin(t.y));
}


s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(shift(-13, 0, 0)*s, surfacepen=blob, render(merge=true));