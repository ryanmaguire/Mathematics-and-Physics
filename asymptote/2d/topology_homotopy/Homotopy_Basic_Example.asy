// Some boiler plate stuff.
import custom_arrows;
import settings;
settings.outformat="pdf";

// Size of the output figure.
size(128);

// Variable for drawing the blobs.
path p;

// Pens used for drawing normal and dashed lines.
pen lpen = black+linewidth(1pt);
pen dpen = black+linewidth(0.5pt)+linetype("8 4");

// Size of the arrow head;
real arsize = 5bp;

// Variable used for the dashed arrows.
real offset = 15;

// Margin for the arrows.
margin margins = TrueMargin(0.6cm, 0.6cm);

// Label for the functions.
Label L;

// Define points for the left blob.
pair A1 = (+0.0, 0.0);
pair B1 = (-0.5, 0.2);
pair C1 = (-1.0, 1.0);
pair D1 = (-0.4, 2.0);
pair E1 = (+0.0, 1.8);
pair F1 = (+0.5, 1.7);
pair G1 = (+1.0, 1.0);
pair H1 = (+0.7, 0.4);

// Set points defining the right blob.
pair A2 = (3.0, 0.0);
pair B2 = (2.5, 0.4);
pair C2 = (2.0, 1.2);
pair D2 = (2.6, 2.1);
pair E2 = (3.0, 2.2);
pair F2 = (3.5, 1.7);
pair G2 = (4.0, 1.0);
pair H2 = (3.7, 0.4);

// Coordinates for labelling the blobs.
pair X = (0.0, 1.0);
pair Y = (3.0, 1.0);

// Labels for the blobs X and Y.
label("$X$", X);
label("$Y$", Y);

// Node indicating this is a homotopy.
label("$H$", 0.5*(X+Y));

// Coordinates for drawing arrows between curves.
pair T1 = (1.1, 0.15);
pair T2 = (1.1, 1.85);
pair T3 = (1.9, 0.15);
pair T4 = (1.9, 1.85);

// Draw the left blob.
p = A1{dir(180)}..B1{dir(140)}..C1{dir(105)}..D1{dir(-10)}..
    E1{dir(-20)}..F1{dir(-20)}..G1{dir(-90)}..H1{dir(-130)}..{dir(180)}cycle;
draw(p, lpen);

// Now the right blob.
p = A2{dir(170)}..B2{dir(130)}..C2{dir(100)}..D2{dir(30)}..
    E2{dir(-10)}..F2{dir(-50)}..G2{dir(-90)}..H2{dir(-135)}..{dir(170)}cycle;
draw(p, lpen);

// Draw arrows indicating f and g.
p = X{dir(60)}..Y;
L = Label("$f$", fontsize(9pt));
draw(L, p, N, lpen, SharpArrow(StealthHead, arsize), margins);
p = X{dir(-60)}..Y;
L = Label("$g$", fontsize(9pt));
draw(L, p, S, lpen, SharpArrow(StealthHead, arsize), margins);

// Adjust margin.
margins = TrueMargin(2pt, 2pt);

// Adjust arrow head size.
arsize = 4bp;

// Draw dashed lines indicating the homotopy
p = T1{dir(90-offset)}..T2;
draw(p, dpen, SharpArrows(StealthHead, arsize), margins);
p = T3{dir(90+offset)}..T4;
draw(p, dpen, SharpArrows(StealthHead, arsize), margins);