// Some boiler plate stuff.
import settings;
import custom_arrows;
settings.outformat="pdf";

// Size of the output figure.
size(256);

// Circle with string.
pair Origin  = (0.0,  0.0);
pair nPole   = (0.0,  1.0);
pair sPole   = (0.0, -1.0);
pair equator = (1.0,  0.0);
pair mid     = (1.5,  0.0);

// Radius of inner circle for croissant.
real r = 0.6;

// Distance from top in inner croissant circle to top of outter (Pythagoras).
real r_mid = sqrt(1-(1-r)^2);

// The midpoint from the inner and outer circles of the croissant.
pair AA = (0, r+r_mid)*0.5;

// Normal pen.
pen npen = black+linewidth(1pt);

// Thicker pen.
pen tpen = black+linewidth(2pt);

// Path for drawing blobs.
path p;

// Shift values for the kettle bell.
real xshift = 4.0;
real yshift = 1.8;

// Arrow size.
real arsize = 10bp;

// Margins for the arrows.
margin margins = TrueMargin(3cm, 2cm);

// For labelling quotients.
Label L;

// Draw the sphere with string attached to the poles.
draw(arc((0,0), 1, 90, 270), npen);

L = Label("$A$", position=1.5, fontsize(12pt));
draw(L, arc((0,0), 1, 90, -90), SW, tpen);

// Draw the string.
L = Label("$B$", position=0.5, fontsize(12pt));
draw(L, nPole{N}..mid{S}..sPole{N}, NE, tpen);

// Draw the equator of the sphere.
draw(scale(1.0, 0.3)*arc(Origin, 1, 180, 360));
draw(scale(1.0, 0.3)*arc(Origin, 1, 0, 180), dashed);

// Label for the space.
label("$X$", scale(1.3)*expi(2pi/3));

// Draw the kettle bell.
draw(shift(xshift, yshift)*unitcircle, npen);

// Path for the handle part of the kettle bell.
p = equator{N}..mid{S}..equator{N};

// Draw the handle.
draw(shift(xshift, yshift)*p, npen);

// Draw the equator of the sphere.
draw(shift(xshift, yshift)*scale(1.0, 0.3)*arc(Origin, 1, 180, 360));
draw(shift(xshift, yshift)*scale(1.0, 0.3)*arc(Origin, 1, 0, 180), dashed);

// Draw arrow from sphere with string to kettle bettle.
p = Origin--shift(xshift, yshift)*Origin;
L = Label(rotate(180*atan2(yshift, xshift)/pi)*"Mod A", position=0.5);
draw(L, p, N, npen, SharpArrow(arsize), margins);

// Label the kettle bell.
label("$X/A$", shift(xshift, yshift)*(scale(1.3)*expi(2pi/3)));

// Negate the yshift so we can draw the squished torus (croissant).
yshift = -yshift;

// Draw the outer circle.
draw(shift(xshift, yshift)*unitcircle, npen);

// And the inner circle.
draw(shift(xshift+1-r, yshift)*scale(r)*unitcircle, npen);

// Arc for the "equator" of the croissant.
p = arc((-r, 0), 1-r, 0, 180);
draw(shift(xshift, yshift)*scale(1.0, 0.4)*p, dashed);
p = arc((-r, 0), 1-r, 180, 360);
draw(shift(xshift, yshift)*scale(1.0, 0.4)*p);

// Arcs for the upper and lower hemispheres.
p = arc(AA, (r_mid-r)*0.5, 90, 270);
draw(shift(xshift+1-r, yshift)*(scale(0.4, 1)*p));
draw(shift(xshift+1-r, yshift-r-r_mid)*(scale(0.4, 1)*p));

p = arc(AA, (r_mid-r)*0.5, 90, -90);
draw(shift(xshift+1-r, yshift)*(scale(0.4, 1)*p), dashed);
draw(shift(xshift+1-r, yshift-r-r_mid)*(scale(0.4, 1)*p), dashed);

// Draw arrow from sphere with string to croissant.
p = Origin--shift(xshift, yshift)*Origin;
L = Label(rotate(180*atan2(yshift, xshift)/pi)*"Mod B", position=0.5);
draw(L, p, S, npen, SharpArrow(arsize), margins);

// Label the croissant..
label("$X/B$", shift(xshift, yshift)*(scale(1.3)*expi(-2pi/3)));