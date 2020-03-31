// Some boiler plate stuff.
import settings;
settings.render = 4;
settings.outformat="pdf";
settings.prc=false;

// Size of the output figure.
size(350);

// Variable for drawing stuff.
path p;

// Shift for the first drawing.
real xshift = 0.3;
real yshift = 0.0;

// Size of the arrow head.
real arsize = 5bp;

// Used for margins when drawing lines.
margin TorusMargin;
margin margins;

// Draw the first square, with orientation indicating a Mobius strip.
p = (0.0,  0.5) -- (1.0,  0.5);
draw(shift(xshift, yshift)*p);
p = (0.0, -0.5) -- (1.0, -0.5);
draw(shift(xshift, yshift)*p);
p = (1,  0.5) -- (1.0, -0.5);
draw(shift(xshift, yshift)*p, MidArrow(arsize));
p = (0, -0.5) -- (0.0,  0.5);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

// Draw a half-twist to align the sides.
p = (0, -0.5) -- (0, 0.5);

// Shift for the second drawing.
real xshift = 1.7;
real yshift = 0.0;

draw(shift(xshift, yshift)*p, MidArrow(arsize));
draw(shift(xshift+1.5, yshift)*p, MidArrow(arsize));

margins = TrueMargin(0.1cm, 0.1cm);

p = (0, -0.5){E}..(1.5, 0.5){E};
draw(shift(xshift, yshift)*p);

p = (0, 0.5){E}..(1.5, -0.5){E};
draw(shift(xshift, yshift)*p, white+4, margins);
draw(shift(xshift, yshift)*p);

xshift = -0.1;
yshift = -1.7;

p = (0.5, -0.2) -- (0.5, 0.2);
draw(shift(xshift, yshift)*p, MidArrow(arsize));
draw(shift(xshift+0.2, yshift)*p, MidArrow(arsize));

p = (0.7, -0.2){E}..(1.0, 0.4)..(0.8, 0.6)..(0.7, 0.6)..(0.5, 0.4)..(0.5, 0.2){E};
draw(shift(xshift, yshift)*p);

p = (0.5, -0.2){W}..(0.2, 0.4)..(0.4, 0.6)..(0.5, 0.6)..(0.7, 0.4)..(0.7, 0.2){W};
draw(shift(xshift, yshift)*p);

xshift =  1.6;
yshift = -1.7;

p = (0.6, -0.2) -- (0.6, 0.2);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

p = (0.6, -0.2){E}..(1.0, 0.4)..(0.8, 0.6)..(0.7, 0.6)..
    (0.5, 0.4)..(0.6, 0.2){E}--(0.6, -0.2){W}..(0.2, 0.4)..
    (0.4, 0.6)..(0.5, 0.6)..(0.7, 0.4)..(0.6, 0.2);
draw(shift(xshift, yshift)*p);