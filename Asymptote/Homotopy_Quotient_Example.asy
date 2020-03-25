// Some boiler plate stuff.
import settings;
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

// Circle with string.
pair Origin  = (0.0,  0.0);
pair nPole   = (0.0,  1.0);
pair sPole   = (0.0, -1.0);
pair equator = (1.0,  0.0);
pair mid     = (1.5,  0.0);


real r = 0.6;
real r_mid = sqrt(1-(1-r)^2);
pair AA = (0, r+r_mid)*0.5;

// Normal pen.
pen npen = black+linewidth(1pt);

// Thicker pen.
pen tpen = black+linewidth(2pt);

path p;
real xshift = 4.0;
real yshift = 1.8;
real arsize = 5bp;

draw(arc((0,0), 1, 90, 270), npen);
draw(arc((0,0), 1, 90, -90), tpen);

draw(nPole{N}..mid{S}..sPole{N}, tpen);
draw(scale(1.0, 0.3)*arc(Origin, 1, 180, 360));
draw(scale(1.0, 0.3)*arc(Origin, 1, 0, 180), dashed);
filldraw(circle(nPole, 0.03));
filldraw(circle(sPole, 0.03));

// Kettle Bell.
draw(shift(xshift, yshift)*unitcircle, npen);

p = equator{N}..mid{S}..equator{N};

draw(shift(xshift, yshift)*p, npen);
draw(shift(xshift, yshift)*scale(1.0, 0.3)*arc(Origin, 1, 180, 360));
draw(shift(xshift, yshift)*scale(1.0, 0.3)*arc(Origin, 1, 0, 180), dashed);
dot(shift(xshift, yshift)*equator);

// Squished torus.
yshift = -yshift;

draw(shift(xshift, yshift)*unitcircle, npen);
draw(shift(xshift+1-r, yshift)*scale(r)*unitcircle, npen);

p = arc((-r, 0), 1-r, 0, 180);
draw(shift(xshift, yshift)*scale(1.0, 0.4)*p, dashed);
p = arc((-r, 0), 1-r, 180, 360);
draw(shift(xshift, yshift)*scale(1.0, 0.4)*p);

p = arc(AA, (r_mid-r)*0.5, 90, 270);
draw(shift(xshift+1-r, yshift)*(scale(0.4, 1)*p));
draw(shift(xshift+1-r, yshift-r-r_mid)*(scale(0.4, 1)*p));
p = arc(((0, r)+(0, r_mid))*0.5, (r_mid-r)*0.5, 90, -90);
draw(shift(xshift+1-r, yshift)*(scale(0.4, 1)*p), dashed);
draw(shift(xshift+1-r, yshift-r-r_mid)*(scale(0.4, 1)*p), dashed);