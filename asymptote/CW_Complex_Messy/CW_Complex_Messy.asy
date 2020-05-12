// Boilerplate stuff.
import settings;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
settings.prc=false;
viewportmargin=(2, 2);

pair midpoint(pair A, pair B){return scale(0.5)*(A+B);}

// Default pen for drawing.
defaultpen(black+linewidth(0.5pt));

// Size of the output figure.
size(128);

// Radius of the dot.
real rDot = 0.03;

// Radius of sphere.
real R = 1.0;

// Some points for drawing.
pair O = (0.0,  0.0);
pair A = (1.5,  0.5);
pair B = (1.5, -0.5);
pair C = (2.0,  0.0);
pair D = (3.5,  0.0);
pair F = (2.5,  R);
pair G = (2.5, -R);

// Paths to draw the figures.
path g;

// Draw the sphere.
g = A{dir(30)}..F..D..G..{dir(150)}B--cycle;
axialshade(g, gray(0.5)+opacity(0.4), midpoint(B, C), white+opacity(0.5), D);
draw(g);

// Add elliptical lines making it look 3D.
g = scale(0.3, 1.0)*arc(O, R, 270, 450);
draw(shift(midpoint(F, G))*g);

g = scale(0.3, 1.0)*arc(O, R, 90, 270);
draw(shift(midpoint(F, G))*g, linetype("4 4"));

// Clip the circular part out.
g = O{dir(30)}..A..C..B..{dir(150)}cycle;

// Draw the dot and the circle.
filldraw(circle(O, rDot));
filldraw(g, white);