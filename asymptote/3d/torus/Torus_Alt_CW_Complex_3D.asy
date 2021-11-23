// Boilerplate stuff.
import settings;
import graph3;
import tube;
settings.outformat="pdf";
settings.inlineimage=true;

currentprojection=perspective(camera = (20, -80, 25), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

currentlight=light(
    diffuse = new pen[] {gray(0.38), gray(0.38), gray(0.38)},
    specular = new pen[] {gray(0.38), gray(0.38), gray(0.38)},
    specularfactor = 1.0,
    position = new triple[] {(100, 0, 25), (20, 100, 25), (0,0,1000)}
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
real theta0 = pi/4;
real theta1 = pi/2;

// Number of samples in the figure.
int samplex = 50;
int sampley = 40;

// Radius of the dot and pipes.
real dotR = 0.2;
real pipR = 0.05;

// Material of the pretzel and the sphere.
material blob1 = material(diffusepen=gray(0.3),
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material blob2 = material(diffusepen=gray(0.7),
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

material pipe0 = material(diffusepen=red,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe1 = material(diffusepen=blue,
                          emissivepen=gray(0.2),
                          specularpen=gray(0.2));

material pipe2 = material(diffusepen=blue+0.3*green,
                          emissivepen=gray(0.4),
                          specularpen=gray(0.2));

surface s;

triple f(pair t) {
    real u = t.x;
    real v = t.y;
    return ((R+a*cos(v))*cos(u), (R+a*cos(v))*sin(u), a*sin(v));
}

// Some contour lines.
triple c0(real t){return f((theta0, t));}
triple c1(real t){return f((t, theta1));}
triple c2(real t){return f((theta0+t, theta1+t));}

real maxfunc(real x, real y){
    if (x < y) return y;
    else return x;
}

triple g1(pair p){
    real x;
    real y;
    real m = maxfunc(p.x, p.y);
    x = (p.x-p.y+m)*0.5;
    y = m-x;
    return f((2*pi-x+theta0, y+theta1));
}

triple g2(pair p){
    real x;
    real y;
    real m = maxfunc(p.x, p.y);
    x = (p.y-p.x+m)*0.5;
    y = m-x;
    return f((x+theta0, 2*pi-y+theta1));
}

s = surface(g1, (0,0), (2pi,2pi), samplex, sampley, Spline);
draw(s, surfacepen=blob1, render(merge=true));

s = surface(g2, (0,0), (2pi,2pi), samplex, sampley, Spline);
draw(s, surfacepen=blob2, render(merge=true));

path3 q=graph(c0, 0, 2pi, 100, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe0, render(merge=true));

path3 q=graph(c1, 0, 2pi, 200, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe1, render(merge=true));

path3 q=graph(c2, 0, 2pi, 250, operator ..);
draw(tube(q, scale(pipR)*unitcircle), surfacepen=pipe2, render(merge=true));

s = shift(f((theta0, theta1)))*(scale(dotR, dotR, dotR)*unitsphere);
draw(s, surfacepen=orb, render(merge=true));
