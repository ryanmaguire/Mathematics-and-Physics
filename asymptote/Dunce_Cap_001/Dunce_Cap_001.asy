// Some boiler plate stuff.
import settings;
settings.render = 4;
settings.outformat="pdf";

// Size of the output figure.
size(300);

pair A;

path p;

real a = 1.0;
real h = a*sqrt(3.0)*0.5;

real xshift = 2.0;
real yshift = 0.0;

real yscale = 0.3;
real ellipse_scale = 0.5095;

real arsize = 5bp;
position pos1 = 0.45;
position pos2 = 0.55;
margin TorusMargin;

draw((0.0, 0.0) -- (a,  0.0),  MidArrow(arsize));
draw((0.0, 0.0) -- (0.5*a, h), MidArrow(arsize));
draw((a,   0.0) -- (0.5*a, h), MidArrow(arsize));

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

xshift = 4.0;
yshift = 0.0;

p = (a, 0.0) -- (0.5*a, h) -- (0.0, 0.0)--
    scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 170, 370);
draw(shift(xshift, yshift)*p, Arrow(arsize, position=5.0),
                              BeginArrow(arsize, position=1.5));

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 10, 170);
draw(shift(xshift, yshift)*p, dashed);

xshift = 6.0;

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 170, 370);
draw(shift(xshift, yshift)*p, MidArrow(arsize));

p = scale(1.0, yscale)*arc((0.5*a, -0.1), ellipse_scale*a, 10, 170);
draw(shift(xshift, yshift)*p, dashed);

A = (0.5*a-ellipse_scale*a, -0.1*yscale);

p = A{dir(90)}..(0.0, 0.5*h)..{dir(300)}A--
    A{dir(150)}..(0.0, h)..(a, 0.0){dir(290)};
draw(shift(xshift, yshift)*p, Arrow(arsize, position=1.1));


