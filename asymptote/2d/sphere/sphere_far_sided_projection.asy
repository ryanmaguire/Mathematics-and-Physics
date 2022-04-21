// Some boiler plate stuff.
import settings;
import custom_arrows;
settings.outformat="pdf";

// Size of the output figure.
size(256);

// Variables used throughout to draw circles, cones, and ellipses.
real AngleA = 170;
real AngleB = 370;
real AngleC = 20;
real AngleD = 160;
real Radius = 2;

// Variables for size of arrows and position of labels along arrows.
real arsize = 5bp;
position pos = 1.0;

// Coordinates for the origin, floor, vertex, and center of dashed ellipse.
pair O = (0, 0);
pair F = (0, -2.0);
pair V = (0, 5.846);
pair C = (0, 0.676);

// Points used for the x and y axes.
pair xend = (-sqrt(2), -sqrt(2)-2);
pair yend = (4.000, -2.000);

// Endpoints used for the cone.
pair rCone = ( 2.856, -2.0);
pair lCone = (-2.856, -2.0);

path p;

// Axes for the floor.
draw(Label("$y$", pos, align=N),  F--yend, SharpArrow(arsize));
draw(Label("$x$", pos, align=NW), F--xend, SharpArrow(arsize));

// Path for the cone representing the observer.
p = V--lCone--shift(F)*scale(2.856, 0.8)*arc(O, 1.0, 180, 360)--rCone--cycle;
axialshade(p, gray(0.5)+opacity(0.5), V, white+opacity(0.1), F);
draw(p, thin());
dot(V);
filldraw(ellipse(F, 2.856, 0.8), gray(0.5)+opacity(0.5), opacity(0.0)+thin());

// Path for the dashed ellipse.
p = scale(1.91, 0.8)*arc(C, 1.0, AngleA, AngleB)--
                     arc(O, Radius, AngleC, AngleD-360)--cycle;
filldraw(p, gray(0.8), opacity(0.0));
draw(scale(1.91, 0.8)*arc(C, 1.0, AngleA, AngleB), longdashed+thin());

// Draw the equator on the globe.
draw(scale(1, 0.41)*arc(O, Radius, 180, 360), thin());

// Draw the globe.
draw(circle(O, Radius), thin());