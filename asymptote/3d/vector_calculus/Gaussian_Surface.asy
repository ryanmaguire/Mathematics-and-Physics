// Boilerplate stuff.
import graph3;
import palette;
import settings;
settings.outformat="pdf";
settings.render=4;

// Size of the output figure.
size(200);

// Camera angle.
currentprojection=perspective(10, 8, 4);

// Arrow size.
real arsize = 5bp;

// Function to return elevated Gaussin, exp(-x^2-y^2)+1.0.
real f(pair z) {return 1.0+exp(-z.x^2-z.y^2);}

// Create the Gaussian surface.
surface s=surface(f, (-2, -2), (2, 2), nx=100, ny=100, Spline);

// Project the surface onto the xy plane.
surface floor=planeproject(unitsquare3)*s;

// Color the projection based on the height of the original surface.
floor.colors(palette(s.map(zpart),Rainbow()));

// Draw the floor.
draw(floor, nolight, render(merge=true));

// Arrow indicating orientation.
draw(arc(0.12Z, 0.2, 90, 60, 90, 25), Arrow3(arsize));

// Draw axes.
xaxis3(Label("$x$"), 0, 2.3, black, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 2.3, black, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 2.3, black, Arrow3(arsize));

// Draw the Gaussian surface.
draw(s, lightgray+opacity(0.8), nolight, render(merge=true));

// Create a mesh for the surface and draw it.
s=surface(f, (-2, -2), (2, 2), nx=20, ny=20, Spline);
draw(s, opacity(0.0), meshpen=black+thick(), render(merge=true));