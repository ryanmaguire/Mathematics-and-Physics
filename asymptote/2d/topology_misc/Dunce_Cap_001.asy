// Boilerplate stuff.
import settings;
import custom_arrows;
settings.outformat = "pdf";

// Size of the output figure.
size(256);

// Size of the arrow head.
real arsize = 5bp;

pair A;

// Path used for drawing.
path p;

// Length and height of triangle.
real a = 1.0;
real h = a*sqrt(3.0)*0.5;

// Shifts for the second image.
real xshift = 2.0;
real yshift = 0.0;

// Scale for drawing the ellipse.
real yscale = 0.3;
real ellipse_scale = 0.5095;

// Draw the first triangle.
draw((0.0, 0.0) -- (a,  0.0),  MidArrow(arsize));
draw((0.0, 0.0) -- (0.5*a, h), MidArrow(arsize));
draw((a,   0.0) -- (0.5*a, h), MidArrow(arsize));

// Draw the triangle turning into a cone.
p = (a, 0.0) -- (0.5*a, h) -- (0.0, 0.0)--
    scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 170, 250)--
    (0.5*a, h);
draw(shift(xshift, yshift)*p, Arrow(arsize, position=5.5));

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 180, 110);
draw(shift(xshift, yshift)*p, dashed);

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 0, 70);
draw(shift(xshift, yshift)*p, dashed);

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 76, 104);
draw(shift(xshift, yshift)*p);

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 360, 290)--
    (0.5*a, h);
draw(shift(xshift, yshift)*p, Arrow(arsize, position=1.5),
                              BeginArrow(arsize, position=0.5));

// Shift over for the third image.
xshift = 4.0;
yshift = 0.0;

// Draw the cone.
p = (a, 0.0) -- (0.5*a, h) -- (0.0, 0.0)--
    scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 170, 370);
draw(shift(xshift, yshift)*p, Arrow(arsize, position=5.0),
                              BeginArrow(arsize, position=1.5));

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 10, 170);
draw(shift(xshift, yshift)*p, dashed);

// Shift for the final image.
xshift = 6.0;

// Draw the cone with the tip attaching to the bottom.
p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 170, 370);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 10, 170);
draw(shift(xshift, yshift)*p, dashed);

A = (0.5*a-ellipse_scale*a, -0.1*yscale);

p = A{dir(90)}..(0.0, 0.5*h)..{dir(300)}A--
    A{dir(150)}..(0.0, h)..(a, 0.0){dir(290)};
draw(shift(xshift, yshift)*p, Arrow(arsize, position=1.1));
