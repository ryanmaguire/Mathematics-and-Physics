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
pair F = (0, -4.2);
pair V = (0, 5.846);
pair C = (0, 0.676);

path p;

// Label the x, y, and z axes for the top picture.
draw(Label("$y$", pos, align=N),  O--( 3,  0), SharpArrow(arsize));
draw(Label("$z$", pos, align=E),  O--( 0,  3), SharpArrow(arsize));
draw(Label("$x$", pos, align=NW), O--(-2, -2), SharpArrow(arsize));

// Path for the dashed ellipse.
p = scale(1.91, 0.8)*arc(C, 1.0, AngleA, AngleB)--
                     arc(O, Radius, AngleC, AngleD)--cycle;
filldraw(p, gray(0.5)+opacity(0.5), opacity(0.0));
draw(scale(1.91, 0.8)*arc(C, 1.0, AngleA, AngleB), longdashed+thin());

// Draw the globe and label the top half.
draw(circle(O, Radius), thin());
label("$\mathcal{U}_{z}^{+}$", (1, 1));

// Path for the cone representing the observer.
p = V--scale(1.91, 0.8)*arc(C, 1.0, AngleA, 370)--cycle;
axialshade(p, gray(0.5)+opacity(0.4), V, white+opacity(0.5), C);
draw(Radius*expi(AngleC*pi/180)--V--Radius*expi(AngleD*pi/180), thin());
dot(V);

// Draw the equator on the globe.
draw(scale(1, 0.41)*arc(O, Radius, 180, 360), thin());

// Projection mapping from the sphere to the floor.
draw(Label("$\pi_{z}$", 0.5*pos, align=E), (0, -2.2)--(0, -3.2),
     Arrow(arsize));

// Axes for the floor.
draw(Label("$y$", pos, align=N),  (-3, -4.2)--( 3, -4.2), SharpArrow(arsize));
draw(Label("$x$", pos, align=NW), ( 1, -3.2)--(-1, -5.2), SharpArrow(arsize));

// Fill the projection of what is observed and the projection of the equator.
filldraw(ellipse(F, 1.8, 0.72), gray(0.7)+opacity(0.5), longdashed+thin());
draw(ellipse((0, -4.2), 2.0, 0.8), thin());
