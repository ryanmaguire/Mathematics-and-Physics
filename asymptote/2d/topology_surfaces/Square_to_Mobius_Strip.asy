import settings;
settings.outformat = "pdf";

// Seting output format to "pdf".
import graph;

// Size of the output figure.
size(256);

// Variable for drawing stuff.
path p;

// Shift for the first drawing.
real xshift = 0.3;
real yshift = 0.0;

real xlength = 1.0;
real ylength = 1.0;

// Size of the arrow head.
real arsize = 5bp;

// Used for margins when drawing lines.
margin TorusMargin;
margin margins;

// Draw the first square, with orientation indicating a Mobius strip.
p = (0.0, 0.0) -- (xlength, 0.0);
draw(shift(xshift, yshift)*p);

p = (0.0, ylength) -- (xlength, ylength);
draw(shift(xshift, yshift)*p);

p = (0.0, 0.0) -- (0.0, ylength);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

p = (xlength, ylength) -- (xlength, 0.0);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

// Shift for the second drawing.
xshift = 2.0;

// Rescale for new object.
xlength = 1.3;

// Draw a half-twist to align the sides.
p = (0.0, 0.0) -- (0, ylength);

draw(shift(xshift, yshift)*p, MidArrow(arsize));
draw(shift(xshift+xlength, yshift)*p, MidArrow(arsize));

margins = TrueMargin(0.1cm, 0.1cm);

p = (0.0, 0.0){E}..(xlength, ylength){E};
draw(shift(xshift, yshift)*p);

p = (0.0, ylength){E}..(xlength, 0.0){E};
draw(shift(xshift, yshift)*p, white+4, margins);
draw(shift(xshift, yshift)*p);

// Shift for the third drawing.
xshift += 1.7;

// Drag the band downwards.
p = (xlength/2, 0.0) -- (0.0, 0.0);
draw(shift(xshift, yshift)*p, MidArrow(arsize));
p = (xlength, 0.0) -- (3*xlength/2, 0.0);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

margins = TrueMargin(0.1cm, 0.1cm);

p = (xlength/2, 0.0){N}..(xlength, ylength){E}..(3*xlength/2, 0.0){S};
draw(shift(xshift, yshift)*p);

p = (0.0, 0.0){N}..(xlength/2, ylength){E}..(xlength, 0.0){S};
draw(shift(xshift, yshift)*p, white+4, margins);
draw(shift(xshift, yshift)*p);

// Shift for the fourth drawing.
xshift =  1.7;
yshift = -1.5;

// Scales for the fourth object.
xlength = 0.3;
ylength = 0.75;

p = (0.0, 0.7*ylength) -- (0.0, 0.0);
draw(shift(xshift, yshift)*p, MidArrow(arsize));
draw(shift(xshift+xlength, yshift)*p, MidArrow(arsize));

p = (xlength, 0.0){E}..(4*xlength, ylength)..(0.5*xlength, 1.5*ylength)..
    (-xlength, ylength){S}..(0, 0.7*ylength){E};
draw(shift(xshift, yshift)*p);

p = (0.0, 0.0){W}..(-3*xlength, ylength)..(0.5*xlength, 1.5*ylength)..
    (2*xlength, ylength){S}..{W}(xlength, 0.7*ylength);
draw(shift(xshift, yshift)*p, white+4, margins);
draw(shift(xshift, yshift)*p);

// Shift for the fifth drawing.
xshift += 2.6;

p = (0.0, 0.7*ylength) -- (0.0, 0.0);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

p = (0, 0.0){E}..(3*xlength, ylength)..(-0.5*xlength, 1.5*ylength)..
    (-2*xlength, ylength){S}..(0, 0.7*ylength){E};
draw(shift(xshift, yshift)*p);

p = (0.0, 0.0){W}..(-3*xlength, ylength)..(0.5*xlength, 1.5*ylength)..
    (2*xlength, ylength){S}..{W}(0, 0.7*ylength);
draw(shift(xshift, yshift)*p, white+4, margins);
draw(shift(xshift, yshift)*p);
